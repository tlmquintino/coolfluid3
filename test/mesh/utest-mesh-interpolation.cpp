// Copyright (C) 2010-2011 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Tests mesh interpolation"

#include <boost/test/unit_test.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/assign/std/vector.hpp>

#include "common/OptionArray.hpp"
#include "common/Foreach.hpp"
#include "common/Log.hpp"
#include "common/Core.hpp"

#include "common/FindComponents.hpp"
#include "common/Link.hpp"
#include "common/Root.hpp"

#include "mesh/Mesh.hpp"
#include "mesh/Region.hpp"
#include "mesh/Elements.hpp"
#include "common/Table.hpp"
#include "mesh/Geometry.hpp"
#include "mesh/MeshReader.hpp"
#include "mesh/MeshWriter.hpp"
#include "mesh/Interpolator.hpp"
#include "mesh/Space.hpp"

#include "mesh/actions/CreateSpaceP0.hpp"

using namespace boost;
using namespace boost::assign;
using namespace cf3;
using namespace cf3::mesh;
using namespace cf3::mesh::actions;
using namespace cf3::common;

////////////////////////////////////////////////////////////////////////////////

struct MeshInterpolation_Fixture
{
  /// common setup for each test case
  MeshInterpolation_Fixture()
  {
     // uncomment if you want to use arguments to the test executable
     //int*    argc = &boost::unit_test::framework::master_test_suite().argc;
     //char*** argv = &boost::unit_test::framework::master_test_suite().argv;
  }

  /// common tear-down for each test case
  ~MeshInterpolation_Fixture()
  {
  }

  /// possibly common functions used on the tests below


  /// common values accessed by all tests goes here

};

////////////////////////////////////////////////////////////////////////////////

BOOST_FIXTURE_TEST_SUITE( MeshInterpolation_TestSuite, MeshInterpolation_Fixture )

////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE( Constructors)
{
  Interpolator::Ptr interpolator = build_component_abstract_type<Interpolator>("cf3.mesh.LinearInterpolator","interpolator");
  BOOST_CHECK_EQUAL(interpolator->name(),"interpolator");
}

////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE( Interpolation )
{
  BOOST_CHECK( true );

  // create meshreader
  MeshReader::Ptr meshreader = build_component_abstract_type<MeshReader>("cf3.mesh.neu.Reader","meshreader");

  BOOST_CHECK( true );

  Mesh& source = Core::instance().root().create_component<Mesh>("hextet");
  meshreader->read_mesh_into("../../resources/hextet.neu",source);
  allocate_component<CreateSpaceP0>("create_space_P0")->transform(source);

  BOOST_CHECK_EQUAL( source.geometry().coordinates().row_size() , (Uint)DIM_3D );

  Mesh& target = Core::instance().root().create_component<Mesh>("quadtriag");
  meshreader->read_mesh_into("../../resources/quadtriag.neu",target);
  allocate_component<CreateSpaceP0>("create_space_P0")->transform(target);

  BOOST_CHECK_EQUAL( target.geometry().coordinates().row_size() , (Uint)DIM_2D );

  //  boost::filesystem::path fp_target ("grid_c.cgns");
//	MeshReader::Ptr cgns_meshreader = build_component_abstract_type<MeshReader>("cf3.mesh.CGNS.Reader","cgns_meshreader");
//  Mesh::Ptr target = cgns_meshreader->create_mesh_from(fp_target);


  // Create and configure interpolator.
  Interpolator::Ptr interpolator = build_component_abstract_type<Interpolator>("cf3.mesh.LinearInterpolator","interpolator");
  interpolator->configure_option("ApproximateNbElementsPerCell", (Uint) 1 );
  // Following configuration option has priority over the the previous one.
  std::vector<Uint> divisions = boost::assign::list_of(3)(2)(2);
  //interpolator->configure_option("Divisions", divisions );

  // Create the honeycomb
  interpolator->construct_internal_storage(source);

  BOOST_CHECK(true);

  std::string nvars = "rho_n[1] , V_n[3] , p_n[1]";
  std::string nvars_2;
  std::string evars;
  std::string evars_2;

  nvars_2 = "rho_n_2[1] , V_n_2[3] , p_n_2[1]";
  evars =   "rho_e[1] , V_e[3] , p_e[1]";
  evars_2 = "rho_e_2[1] , V_e_2[3] , p_e_2[1]";

  FieldGroup& source_elem_fields = source.create_space_and_field_group("elems_P0", FieldGroup::Basis::ELEMENT_BASED, "cf3.mesh.LagrangeP0");
  FieldGroup& target_elem_fields = target.create_space_and_field_group("elems_P0", FieldGroup::Basis::ELEMENT_BASED, "cf3.mesh.LagrangeP0");
  FieldGroup& source_node_fields = source.geometry();
  FieldGroup& target_node_fields = target.geometry();


  source_elem_fields.create_coordinates();
  target_elem_fields.create_coordinates();

  // Create empty fields
  Field& s_nodebased   = source_node_fields.create_field( "nodebased",     "rho_n[1],   V_n[3],   p_n[1]" );
  Field& s_elembased   = source_elem_fields.create_field( "elementbased",  "rho_e[1],   V_e[3],   p_e[1]" );

  Field& t_nodebased   = target_node_fields.create_field( "nodebased",     "rho_n[1],   V_n[3],   p_n[1]"   );
  Field& t_nodebased_2 = target_node_fields.create_field( "nodebased_2",   "rho_n_2[1], V_n_2[3], p_n_2[1]" );
  Field& t_elembased   = target_elem_fields.create_field( "elementbased",  "rho_e[1],   V_e[3],   p_e[1]"   );

  BOOST_CHECK(true);

  for ( Uint idx=0; idx!=s_nodebased.size(); ++idx)
  {
    Field::ConstRow coords = s_nodebased.coordinates()[idx];

    Field::Row data = s_nodebased[idx];

    data[0]=coords[XX]+2.*coords[YY]+2.*coords[ZZ];
    data[1]=coords[XX];
    data[2]=coords[YY];
    data[3]=7.0;
    data[4]=coords[XX];

  }

  RealMatrix coordinates;
  boost_foreach( Elements& s_elements, find_components_recursively<Elements>(s_elembased.topology()) )
  {
    Space& space = s_elembased.space(s_elements);
    space.allocate_coordinates(coordinates);

    for (Uint elem_idx = 0; elem_idx<s_elements.size(); ++elem_idx)
    {
      coordinates = space.compute_coordinates( elem_idx );
      cf3_assert(space.indexes_for_element(elem_idx).size() == coordinates.rows());
      boost_foreach(const Uint state, space.indexes_for_element(elem_idx))
      {
        const RealRowVector& coords = coordinates.row(0);
        s_elembased[state][0]=coords[XX]+2.*coords[YY]+2.*coords[ZZ];
        s_elembased[state][1]=coords[XX];
        s_elembased[state][2]=coords[YY];
        s_elembased[state][3]=7.0;
        s_elembased[state][4]=coords[XX];
      }
    }
  }


  BOOST_CHECK(true);

  // Interpolate the source field data to the target field. Note it can be in same or different meshes
  interpolator->interpolate_field_from_to(s_nodebased,s_elembased);
  interpolator->interpolate_field_from_to(s_nodebased,t_nodebased);
  interpolator->interpolate_field_from_to(s_elembased,t_nodebased_2);
  interpolator->interpolate_field_from_to(s_elembased,t_elembased);

  // interpolator->interpolate_field_from_to(source->field("nodebased"),target->field("elementbased"));
  // interpolator->interpolate_field_from_to(source->field("nodebased"),source->field("elementbased"));
  // interpolator->interpolate_field_from_to(source->field("elementbased"),target->field("elementbased_2"));
  // interpolator->interpolate_field_from_to(source->field("elementbased"),target->field("nodebased_2"));

  BOOST_CHECK(true);

  // Write the fields to file.
  MeshWriter::Ptr meshwriter = build_component_abstract_type<MeshWriter>("cf3.mesh.gmsh.Writer","meshwriter");

  BOOST_CHECK(true);

  std::vector<Field::Ptr> s_fields;
  boost_foreach(Field& field, find_components_recursively<Field>(source))
    s_fields.push_back(field.as_ptr<Field>());

  meshwriter->set_fields(s_fields);

  BOOST_CHECK(true);
  meshwriter->write_from_to(source,"source.msh");
  BOOST_CHECK(true);


  std::vector<Field::Ptr> t_fields;
  boost_foreach(Field& field, find_components_recursively<Field>(target))
    t_fields.push_back(field.as_ptr<Field>());

  meshwriter->set_fields(t_fields);
  meshwriter->write_from_to(target,"interpolated.msh");
  BOOST_CHECK(true);

}

////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////


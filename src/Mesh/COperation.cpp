#include "Mesh/COperation.hpp"

/////////////////////////////////////////////////////////////////////////////////////

namespace CF {
namespace Mesh {

///////////////////////////////////////////////////////////////////////////////////////
  
COperation::COperation ( const CName& name ) : 
  Component(name), m_counter(0)
{
    BUILD_COMPONENT;
}
  
///////////////////////////////////////////////////////////////////////////////////////

void COperation::needs(CField& field)
{
  std::vector<CField::Ptr> needed(1);
  needed[0]=field.get_type<CField>();
  needs_fields(needed);
}

void COperation::needs(CField& field1, CField& field2)
{
  std::vector<CField::Ptr> needed(2);
  needed[0]=field1.get_type<CField>();
  needed[1]=field2.get_type<CField>();
  needs_fields(needed);
}

void COperation::needs(CField& field1, CField& field2, CField& field3)
{
  std::vector<CField::Ptr> needed(3);
  needed[0]=field1.get_type<CField>();
  needed[1]=field2.get_type<CField>();
  needed[2]=field3.get_type<CField>();
  needs_fields(needed);
}

void COperation::needs_fields (std::vector<CField::Ptr>& fields) 
{ 
  throw NotImplemented(FromHere(), "fields passed to operation \"" + full_path().string() + "\" but operation doesn't require fields");
}

///////////////////////////////////////////////////////////////////////////////////////

void COperation::needs(CRegion& region)
{
  std::vector<CRegion::Ptr> needed(1);
  needed[0]=region.get_type<CRegion>();
  needs_regions(needed);
}

void COperation::needs(CRegion& region1, CRegion& region2)
{
  std::vector<CRegion::Ptr> needed(2);
  needed[0]=region1.get_type<CRegion>();
  needed[1]=region2.get_type<CRegion>();
  needs_regions(needed);
}

void COperation::needs(CRegion& region1, CRegion& region2, CRegion& region3)
{
  std::vector<CRegion::Ptr> needed(3);
  needed[0]=region1.get_type<CRegion>();
  needed[1]=region2.get_type<CRegion>();
  needed[2]=region3.get_type<CRegion>();
  needs_regions(needed);
}

void COperation::needs_regions (std::vector<CRegion::Ptr>& regions)
{
  throw NotImplemented(FromHere(), "regions passed to operation \"" + full_path().string() + "\" but operation doesn't require regions");
}

///////////////////////////////////////////////////////////////////////////////////////

void COperation::stores(CField& field)
{
  std::vector<CField::Ptr> stored(1);
  stored[0]=field.get_type<CField>();
  stores_fields(stored);
}

void COperation::stores(CField& field1, CField& field2)
{
  std::vector<CField::Ptr> stored(2);
  stored[0]=field1.get_type<CField>();
  stored[1]=field2.get_type<CField>();
  stores_fields(stored);
}

void COperation::stores(CField& field1, CField& field2, CField& field3)
{
  std::vector<CField::Ptr> stored(3);
  stored[0]=field1.get_type<CField>();
  stored[1]=field2.get_type<CField>();
  stored[2]=field3.get_type<CField>();
  stores_fields(stored);
}

void COperation::stores_fields (std::vector<CField::Ptr>& fields)
{
  throw NotImplemented(FromHere(), "fields passed to operation \"" + full_path().string() + "\" but operation doesn't require fields");
}

///////////////////////////////////////////////////////////////////////////////////////

void COperation::setup (CElements& geometry_elements )
{
  throw NotImplemented(FromHere(), "Must create child that overloads this function");
}

///////////////////////////////////////////////////////////////////////////////////////

//void COperation::execute (  Uint index )
//{
//  throw NotImplemented(FromHere(), "Must create child that overloads this function");
//}

///////////////////////////////////////////////////////////////////////////////////////

COperation& COperation::operation()
{
  throw NotImplemented(FromHere(), "Must create child that overloads this function");
}

///////////////////////////////////////////////////////////////////////////////////////

COperation& COperation::create_operation(const std::string operation_type)
{
  // The execuation of operations must be in chronological order, hence
  // they get an alphabetical name
  std::string name = "operation_"+String::to_str(++m_counter);
  COperation::Ptr sub_operation = 
    create_component_abstract_type<COperation>(operation_type,name);
  add_component(sub_operation);
  return *sub_operation;
}

///////////////////////////////////////////////////////////////////////////////////////
  
Common::ObjectProvider < COperationMerge, COperation, MeshLib, NB_ARGS_1 > COperationMergeProvider( "COperationMerge" );

Common::ObjectProvider < COutputField,    COperation, MeshLib, NB_ARGS_1 > COutputFieldProvider( "COutputField" );

Common::ObjectProvider < CComputeVolumes, COperation, MeshLib, NB_ARGS_1 > CComputeVolumeProvider( "CComputeVolumes" );

//
//struct SetX
//{
//  CArray::Ptr x_coord;
//  CArray::Ptr coordinates;
//  CTable::Ptr connectivity_table;
//  
//  SetX () { }
//  
//  void setup (CFieldElements& field_elements )
//  {
//    coordinates = field_elements.get_geometry_elements().coordinates().get_type<CArray>();
//    connectivity_table = field_elements.get_geometry_elements().connectivity_table().get_type<CTable>();
//    x_coord = field_elements.elemental_data().get_type<CArray>();
//  }
//  
//  template < typename SFType >
//  void execute ( Uint elem )
//  {
//    cf_assert(x_coord.get());
//    //std::vector<RealVector> nodes;
//    //fill_node_list( std::inserter(nodes, nodes.begin()), *coordinates, *connectivity_table, elem );
//    
//    
//    //RealVector mapped_coord = RealVector(0.0,SFType::dimension);
//    //RealVector shape_func = RealVector(SFType::nb_nodes);
//    
//    //SFType::shape_function(mapped_coord,shape_func);
//
//    x_coord->array()[elem][0] = 0;
//    for (Uint i=0; i<SFType::nb_nodes; i++)
//    {
//      x_coord->array()[elem][0] += (*coordinates)[ (*connectivity_table)[elem][i] ][XX];
//    }
//    x_coord->array()[elem][0] /= SFType::nb_nodes;
//  }
//  
//};
//  
///////////////////////////////////////////////////////////////////////////////////////
//  
//struct ComputeGradient
//{
//  CArray::Ptr gradx;
//  CArray::Ptr coordinates;
//  CTable::Ptr connectivity_table;
//  
//  ComputeGradient () { }
//  
//  void setup (CFieldElements& field_elements )
//  {
//    gradx = field_elements.elemental_data().get_type<CArray>();
//    
//    coordinates = field_elements.coordinates().get_type<CArray>();
//    connectivity_table = field_elements.connectivity_table().get_type<CTable>();
//    
//  }
//  
//  template < typename SFType >
//  void execute ( Uint elem )
//  {
//    cf_assert(gradx.get());
//    std::vector<RealVector> nodes;
//    fill_node_list( std::inserter(nodes, nodes.begin()), *coordinates, *connectivity_table, elem );
//    
//    RealVector nodal_function_values(SFType::nb_nodes);
//    for (Uint i=0; i<SFType::nb_nodes; i++)
//    {
//      nodal_function_values[i] = (*coordinates)[ (*connectivity_table)[elem][i] ][XX];
//    }
//    
//    RealVector mapped_coords = RealVector(0.0,SFType::dimension);
//    SFType::mapped_coordinates(nodes[0],nodes,mapped_coords);    
//    
//    // Get the gradient in mapped coordinates
//    RealMatrix mapped_grad(SFType::dimensionality,SFType::nb_nodes);
//    SFType::mapped_gradient(mapped_coords,mapped_grad);
//    
//    // The Jacobian adjugate
//    RealMatrix jacobian_adj(SFType::dimension, SFType::dimensionality);
//    SFType::jacobian_adjoint(mapped_coords, nodes, jacobian_adj);
//    
//    // The gradient operator matrix in the absolute frame
//    RealMatrix grad(SFType::dimension,SFType::nb_nodes);
//    grad = (jacobian_adj * mapped_grad) / SFType::jacobian_determinant(mapped_coords, nodes);
//    
//    // Apply the gradient to the function values
//    RealVector result(SFType::dimension);
//    result = grad * nodal_function_values;
//    gradx->set_row(elem,result);
//  }
//  
//};
//  
///////////////////////////////////////////////////////////////////////////////////////
//
//struct ComputeVolumes
//{
//  CArray::Ptr volumes;
//  CArray::Ptr coordinates;
//  CTable::Ptr connectivity_table;
//
//  ComputeVolumes () { }
//  
//  void setup (CFieldElements& field_elements )
//  {
//    volumes = field_elements.elemental_data().get_type<CArray>();
//    volumes->array().resize(boost::extents[field_elements.elements_count()][1]);
//    
//    coordinates = field_elements.get_geometry_elements().coordinates().get_type<CArray>();
//    connectivity_table = field_elements.get_geometry_elements().connectivity_table().get_type<CTable>();
//    
//  }
//  
//  template < typename SFType >
//  void execute ( Uint elem )
//  {
//    cf_assert(volumes.get());
//    std::vector<RealVector> nodes;
//    fill_node_list( std::inserter(nodes, nodes.begin()), *coordinates, *connectivity_table, elem );
//    volumes->array()[elem][0] = SFType::volume( nodes );
//  }
//
//};
//  
///////////////////////////////////////////////////////////////////////////////////////
//
//struct OutputScalarField
//{
//  CArray::Ptr scalars;
//  std::string scalar_name;
//
//  OutputScalarField () { }
//  
//  void setup (CFieldElements& field_elements )
//  {
//    scalar_name = field_elements.get_parent()->get_type<CField>()->field_name();
//    scalars = field_elements.elemental_data().get_type<CArray>();
//    CFinfo << field_elements.full_path().string() << CFendl;
//  }
//  
//  template < typename SFType >
//  void execute ( Uint elem )
//  {
//    cf_assert(scalars.get());
//    CFinfo << "   " << scalar_name << "["<<elem<<"] = " << scalars->array()[elem][0] << CFendl;
//  }
//};
//  
///////////////////////////////////////////////////////////////////////////////////////
//
//struct OutputVectorField
//{
//  CArray::Ptr vectors;
//  std::string vector_name;
//  
//  OutputVectorField () { }
//  
//  void setup (CFieldElements& field_elements )
//  {
//    vector_name = field_elements.get_parent()->get_type<CField>()->field_name();
//    vectors = field_elements.elemental_data().get_type<CArray>();
//    CFinfo << field_elements.full_path().string() << CFendl;
//  }
//  
//  template < typename SFType >
//  void execute ( Uint elem )
//  {
//    cf_assert(vectors.get());
//    CFinfo << "   " << vector_name << "["<<elem<<"] = " << RealVector(vectors->array()[elem]) << CFendl;
//  }
//};
//  
///////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////

} // Mesh
} // CF

////////////////////////////////////////////////////////////////////////////////////


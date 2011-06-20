// Copyright (C) 2010 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Test module for CF::Euler"

#include <boost/test/unit_test.hpp>


#include "Common/Log.hpp"
#include "Common/Core.hpp"
#include "Common/CEnv.hpp"
#include "Euler/Physics.hpp"
#include "Euler/Cons1D.hpp"

using namespace CF;
using namespace CF::Common;
using namespace CF::Euler;

//////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( Euler_Suite )

//////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE( eulercons1d )
{
  Common::Core::instance().environment().configure_property("log_level",(Uint)DEBUG);
  CF_DEBUG_POINT;
  Euler::Cons1D cons_state;
  CF_DEBUG_POINT;
  Solver::Physics p = cons_state.create_physics();

  RealVector state(3); state << 4.696 , 0. , 404400 ;

  cons_state.set_state(state,p);

  RealVector normal(1); normal << 1.;
  RealVector flux(3);
  RealMatrix rv(3,3);
  RealMatrix lv(3,3);
  RealVector ev(3);

  cons_state.compute_flux(p,normal,flux);
  CFLogVar(flux);
  //RealVector F_L(3); F_L << 0., 404400, 0.;

  cons_state.compute_fluxjacobian_eigenvalues(p,normal,ev);
  CFLogVar(ev);
  cons_state.compute_fluxjacobian_right_eigenvectors(p,normal,rv);
  CFLogVar(rv);
  cons_state.compute_fluxjacobian_left_eigenvectors(p,normal,lv);
  CFLogVar(lv);

//  BOOST_CHECK_EQUAL(flux[0], 5.);
//  BOOST_CHECK_EQUAL(ev[0], 1.);
//  BOOST_CHECK_EQUAL(rv(0,0), 1.);
//  BOOST_CHECK_EQUAL(lv(0,0), 1.);

}

////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////

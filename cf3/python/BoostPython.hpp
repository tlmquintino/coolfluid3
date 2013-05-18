// Copyright (C) 2010-2013 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#ifndef CF3_Python_BoostPython_hpp
#define CF3_Python_BoostPython_hpp

// Disable some warnings generated by clang
#if defined __clang__
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Warray-bounds"
#endif

#include <boost/python.hpp>
#include <boost/python/import.hpp>
#include <boost/python/make_function.hpp>
#include <boost/python/raw_function.hpp>
#include <boost/python/object.hpp>
#include <boost/python/str.hpp>

// Reenable those warnings generated by clang
#if defined __clang__
  #pragma clang diagnostic pop
#endif

////////////////////////////////////////////////////////////////////////////////

#endif // CF3_Python_BoostPython_hpp

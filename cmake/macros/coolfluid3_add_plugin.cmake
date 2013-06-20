# Copyright (C) 2010-2013 von Karman Institute for Fluid Dynamics, Belgium
#
# This software is distributed under the terms of the
# GNU Lesser General Public License version 3 (LGPLv3).
# See doc/lgpl.txt and doc/gpl.txt for the license text.

macro( coolfluid3_add_plugin pdir )

    file( GLOB _has_cmakelist "${pdir}/CMakeLists.txt" )

    if( _has_cmakelist )

      file( STRINGS "${pdir}/CMakeLists.txt" _define_plugin REGEX "coolfluid_define_plugin"  )
      list( LENGTH _define_plugin _n_define_plugin )

      if( _n_define_plugin GREATER 0 )

          get_filename_component( plugin_name ${pdir} NAME )
          add_subdirectory( ${pdir} plugins/${plugin_name} )
      
      endif()

    endif()

endmacro()

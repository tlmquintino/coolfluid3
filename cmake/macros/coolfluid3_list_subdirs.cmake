# Copyright (C) 2010-2013 von Karman Institute for Fluid Dynamics, Belgium
#
# This software is distributed under the terms of the
# GNU Lesser General Public License version 3 (LGPLv3).
# See doc/lgpl.txt and doc/gpl.txt for the license text.

##############################################################################
# macro listing subdirs in a directory

macro( coolfluid3_list_subdirs result curdir )

  file(GLOB children RELATIVE ${curdir} ${curdir}/*)
  set(dirlist "")
  foreach(child ${children})
    if(IS_DIRECTORY ${curdir}/${child})
      set(dirlist ${dirlist} ${child})
    endif()
  endforeach()
  set(${result} ${dirlist})

endmacro()

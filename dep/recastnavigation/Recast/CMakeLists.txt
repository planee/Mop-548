# Copyright (C) 2005-2020 Project Spartans <https://www.spartans-wow.com/
# Copyright (C) 2008-2020 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

set(Recast_STAT_SRCS
    Recast.cpp 
    RecastAlloc.cpp 
    RecastArea.cpp 
    RecastContour.cpp 
    RecastFilter.cpp 
    RecastLayers.cpp 
    RecastMesh.cpp 
    RecastMeshDetail.cpp 
    RecastRasterization.cpp 
    RecastRegion.cpp 
	
)
set(Recast_STAT_H
    Recast.h 
    RecastAlloc.h 
)
if(WIN32)
  include_directories(
    ${CMAKE_SOURCE_DIR}/dep/zlib
  )
endif()

add_library(Recast STATIC ${Recast_STAT_SRCS} ${Recast_STAT_H})

target_link_libraries(Recast ${ZLIB_LIBRARIES})
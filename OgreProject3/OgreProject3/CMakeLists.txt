# CMakeList.txt : CMake project for OgreProject3, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("OgreProject3")

set(CMAKE_CXX_STANDARD 11)

# Add source to this project's executable.
add_executable (OgreProject3 "OgreProject3.cpp" "App.cpp" "TileHandler.h" "LaneHandler.h" "LaneHandler.cpp" "Lane.h" "Lane.cpp" "Car.cpp" "Car.h" "CameraHandler.h" "GameController.h" "GameController.cpp" "CameraHandler.cpp")

# TODO: Add tests and install targets if needed.

find_package(OGRE CONFIG REQUIRED)
#find_package(OpenGL REQUIRED COMPONENTS OpenGL)
# Note: 6 target(s) were omitted.
target_link_libraries(OgreProject3 PRIVATE OgreMain OgreBites OgrePaging OgreVolume OgreRTShaderSystem )
#target_link_libraries(OgreProject3 PRIVATE OpenGL)
#target_link_libraries(OgreProject3 PRIVATE ${OGRE_LIBRARIES})

set("OGRE_CONFIG_DIR" "./conf")
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
	message("Build type is Release")
	file(COPY "${OGRE_CONFIG_DIR}/ogre.cfg" "${OGRE_CONFIG_DIR}/plugins.cfg" "${OGRE_CONFIG_DIR}/resources.cfg" DESTINATION "${CMAKE_BINARY_DIR}")
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	message("Build type is Debug")
	file(COPY "${OGRE_CONFIG_DIR}/ogre_d.cfg" "${OGRE_CONFIG_DIR}/plugins_d.cfg" "${OGRE_CONFIG_DIR}/resources.cfg" DESTINATION "${CMAKE_BINARY_DIR}")
else()
	message("Build type is ... Neither?")
endif()

include_directories(${OGRE_INCLUDE_DIRS})
link_directories(${OGRE_LIBRARY_DIRS})

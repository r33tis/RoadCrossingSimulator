# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("PleaseWork2")

set(CMAKE_CXX_STANDARD 11)

# specify which version and components you need
find_package(OGRE 1.12 REQUIRED COMPONENTS Bites RTShaderSystem)
 
set(OGRE_CONFIG_DIR E:/GRAPHICSPROJECT/ogrebuild/sdk/bin)
# copy resource.cfg next to our binaries where OGRE looks for it
file(COPY ${OGRE_CONFIG_DIR}/resources.cfg ${OGRE_CONFIG_DIR}/plugins.cfg DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
 
# add the source files as usual
add_executable(0_PleaseWork2 "BasicTutorial1.cpp")
 
# this also sets the includes and pulls third party dependencies
target_link_libraries(0_PleaseWork2 OgreBites OgreRTShaderSystem)

##
# @file CMakeLists.txt
#
# Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
#

cmake_minimum_required( VERSION 3.0 )

project( pyformat CXX )

set( CMAKE_VERBOSE_MAKEFILE OFF )

add_compile_options( -Wall )
add_compile_options( -pedantic )
add_compile_options( -fPIC )
# add_compile_options( -std=c++11 )

option( PYTHON "Python version" 3 )

if( ${PYTHON} STREQUAL "3" OR NOT ${PYTHON} )

find_package( PythonLibs "3" )
find_package( PythonInterp "3" )

elseif( ${PYTHON} STREQUAL "2")

find_package( PythonLibs   "2.7" REQUIRED )
find_package( PythonInterp "2.7" REQUIRED )

else()

message( STATUS "Did you set -DPYTHON=3 or -DPYTHON=2 ?" )
message( FATAL_ERROR "Invalid option -DPY=${PY} " )

endif()

find_package( Boost COMPONENTS python REQUIRED )

set( Boost_FULL_VERSION ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION} )

execute_process (
    COMMAND ${PYTHON_EXECUTABLE} -c "import distutils.sysconfig as cfg; print(cfg.get_python_lib())"
    OUTPUT_VARIABLE PYTHON_PKG_PATH OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process (
    COMMAND ${PYTHON_EXECUTABLE} -c "import sys; print('boost_python-py%d%d' % sys.version_info[:2])"
    OUTPUT_VARIABLE Boost_PYTHON_LIBRARY OUTPUT_STRIP_TRAILING_WHITESPACE
)

message( STATUS "Python version string: ${PYTHONLIBS_VERSION_STRING}" )
message( STATUS "Python install path:   ${PYTHON_PKG_PATH}" )
message( STATUS "Python include dirs:   ${PYTHON_INCLUDE_DIRS}" )
message( STATUS "Boost include dirs:    ${Boost_INCLUDE_DIRS}" )
message( STATUS "Boost::Python linkage: ${Boost_PYTHON_LIBRARY}" )

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${PYTHON_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)

add_library( pyformat SHARED
    src/PyFormat.cpp
    src/Operator.cpp
    src/Convert.cpp
)

# remove 'lib' prefix
set_target_properties( pyformat PROPERTIES PREFIX "" )

target_link_libraries ( pyformat optimized ${Boost_PYTHON_LIBRARY} )

install(
    TARGETS pyformat
    DESTINATION ${PYTHON_PKG_PATH}
    PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
)

install(
    FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/README.md
    ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE
    DESTINATION /usr/share/pyformat
    PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests
    DESTINATION /usr/share/pyformat
    FILES_MATCHING PATTERN "*.py"
    PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE
)

set( CPACK_GENERATOR "DEB" )

set( CPACK_PACKAGE_VERSION_MAJOR "0" )
set( CPACK_PACKAGE_VERSION_MINOR "1" )
set( CPACK_PACKAGE_VERSION_PATCH "0" )

set( CPACK_DEBIAN_PACKAGE_DESCRIPTION "PyFormat - boost::format python module" )
set( CPACK_DEBIAN_PACKAGE_MAINTAINER "Pavel Schön <pavel@schon.cz>" )
set( CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/pavelschon/PyFormat.git")

if( ${PYTHON} STREQUAL "3" OR NOT ${PY} )

set( CPACK_DEBIAN_PACKAGE_BUILD_DEPENDS "python3-dev (>= ${PYTHON_VERSION_STRING}), libboost-all-dev" )
set( CPACK_DEBIAN_PACKAGE_DEPENDS "python3 (>= ${PYTHON_VERSION_STRING}), libboost-python${Boost_FULL_VERSION}" )

elseif( ${PYTHON} STREQUAL "2")

set( CPACK_DEBIAN_PACKAGE_BUILD_DEPENDS "python-dev (>= 2.7), python-dev (<< 2.8), libboost-all-dev" )
set( CPACK_DEBIAN_PACKAGE_DEPENDS "python (>= 2.7), python (<< 2.8), libboost-python${Boost_FULL_VERSION}" )

endif()


include(CPack)


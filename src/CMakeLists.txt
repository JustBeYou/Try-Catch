cmake_minimum_required( VERSION 3.11 )

## Load CMAKE configuration from environment variables
set( CMAKE_C_COMPILER /usr/bin/gcc CACHE PATH "" FORCE )
set( CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH} )
set( CMAKE_PREFIX_PATH $ENV{CMAKE_PREFIX_PATH} )

## Specify a project name
project( try-catch C)


## Set the build type
if( NOT CMAKE_BUILD_TYPE )
    set( CMAKE_BUILD_TYPE "Debug"
       CACHE STRING "Build configuration 'Release' or 'Debug'."
       FORCE )
endif()

## Install the executable to <install_directory>/bin
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
## Install libraries (if any) to <install_directory>/bin
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(${PROJECT_SOURCE_DIR}/try-catch bin/lib)
add_subdirectory(${PROJECT_SOURCE_DIR}/tests bin)

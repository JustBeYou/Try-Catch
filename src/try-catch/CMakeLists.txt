cmake_minimum_required( VERSION 3.11 )

## Required software
#find_package( <<<name>>> REQUIRED )

## Sources and headers
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include )

## C compiler options
set( CMAKE_C_FLAGS "-Wall -Wextra -std=c11" )
set( CMAKE_C_FLAGS_DEBUG "-g -O0" )
set( CMAKE_C_FLAGS_RELEASE "-O3" )

## Source file containing the "main" function
set( SOURCES exceptions.c catch.c )
## Specify a name for the generated executable file
set( TRY_CATCH_LIB try-catch )


## 1. Compile...
add_library( ${TRY_CATCH_LIB} SHARED ${SOURCES} )

## 2. Link...
#target_link_libraries( ${TRY_CATCH_LIB} )

## 3. Install...
install( TARGETS ${TRY_CATCH_LIB}
        LIBRARY DESTINATION bin/lib
        )


cmake_minimum_required( VERSION 3.11 )

## Required software
#find_package( <<<name>>> REQUIRED )

## Sources and headers
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

## Find all source files to be compiled into object files
file( GLOB SOURCES *.c )

## C compiler options
set( CMAKE_C_FLAGS "-Wall -Wextra" )
set( CMAKE_C_FLAGS_DEBUG "-g -O0" )
set( CMAKE_C_FLAGS_RELEASE "-O3" )

## Source file containing the "main" function
set( MAIN_SOURCES main.c )
## Specify a name for the generated executable file
set( MAIN_EXE_NAME try-catch )


## 1. Compile...
add_executable( ${MAIN_EXE_NAME} ${MAIN_SOURCES}
                                 ${SOURCES}
              )

## 2. Link...
target_link_libraries( ${MAIN_EXE_NAME} )

## 3. Install...
install( TARGETS ${MAIN_EXE_NAME}
         RUNTIME DESTINATION bin )


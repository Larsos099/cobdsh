cmake_minimum_required(VERSION 3.20)
project(obd-cxx VERSION 1.0 LANGUAGES CXX)

# Set default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif()

# Always build the library first -------------------------------------------------
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find dependencies
find_package(PkgConfig REQUIRED)
pkg_check_modules(MUPARSER REQUIRED muparser)

# Create lib directory if needed
file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")

# Library sources
file(GLOB LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/obd2src/*.cpp")

# Create shared library
add_library(obd-cxx SHARED ${LIB_SOURCES})

# Set library properties
set_target_properties(obd-cxx PROPERTIES
    OUTPUT_NAME "obd-cxx"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
    POSITION_INDEPENDENT_CODE ON
)

# Include directories
target_include_directories(obd-cxx PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${MUPARSER_INCLUDE_DIRS}
)

# Link dependencies
target_link_libraries(obd-cxx PRIVATE 
    ${MUPARSER_LINK_LIBRARIES}
)

# Compiler flags
target_compile_options(obd-cxx PRIVATE
    -Wall
    -Wextra
    -fPIC
)

# Debug vs Release flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(obd-cxx PRIVATE -g)
else()
    target_compile_options(obd-cxx PRIVATE -O2)
endif()

# Conditionally build application ------------------------------------------------
set(APP_MAIN_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
set(LIB_OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/lib/libobd-cxx.so")

if(EXISTS "${APP_MAIN_SOURCE}" AND EXISTS "${LIB_OUTPUT}")
    message(STATUS "Library exists, building C++23 application")
    
    set(CMAKE_CXX_STANDARD 23)
    
    file(GLOB APP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
    add_executable(obd-app ${APP_SOURCES})
    
    target_include_directories(obd-app PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    
    target_link_libraries(obd-app PRIVATE 
        obd-cxx
        ${MUPARSER_LINK_LIBRARIES}
    )
    
    target_compile_options(obd-app PRIVATE
        -Wall
        -Wextra
    )
    
    # Make application depend on library
    add_dependencies(obd-app obd-cxx)
endif()
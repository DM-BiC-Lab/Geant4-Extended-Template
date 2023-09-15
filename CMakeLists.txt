# * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# DO NOT MODIFY THIS FILE UNLESS YOU KNOW WHAT YOU ARE DOING
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

# Make sure CMake meets minumum version requirements
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

# Set names of project, main code file, and output executable
# (The following string fields are safe to edit as needed)
set(PROJ_NAME "Geant4Template")
set(MAIN_CODE_FILE "template.cc")
set(OUTPUT_EXE_NAME "template")

# Give the program its assigned name
project(${PROJ_NAME})

# Find all packages. "Geant4" is necessary, "ui_all_ and
# "vis_all" are technically optional
find_package(Geant4 REQUIRED ui_all vis_all)

# Include files at the specified path
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include ${Geant4_INCLUDE_DIR})

# Retrieve C++ files and headers from this directory
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# Create the executable using assigned name and main
# source file, with {sources} and {headers} as supplements
add_executable(${OUTPUT_EXE_NAME} ${MAIN_CODE_FILE} ${sources} ${headers})

# Allow project to access the additional Geant4 libraries
target_link_libraries(${OUTPUT_EXE_NAME} ${Geant4_LIBRARIES})
add_custom_target(${PROJ_NAME} DEPENDS ${OUTPUT_EXE_NAME})

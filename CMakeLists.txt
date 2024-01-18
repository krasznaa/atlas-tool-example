# Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration
#
# Project configuration file.
#

# Set up the project.
cmake_minimum_required(VERSION 3.20)
project(AtlasToolExample VERSION 0.1.0 LANGUAGES CXX)

# Re-check all of the wildcarded expressions on every re-build in this
# project.
set( ATLAS_ALWAYS_CHECK_WILDCARDS TRUE CACHE BOOL
   "(Re-)Check wildcards in file specifications on every build" )

# Find the base release.
set(ATE_BASE_PROJECT "AnalysisBase" CACHE STRING
   "The base project to use for this project.")
set(ATE_BASE_VERSION "24.2" CACHE STRING
   "The minimum version of the base project to use for this project.")
find_package(${ATE_BASE_PROJECT} ${ATE_BASE_VERSION} REQUIRED)

# Generate a compile_commands.json file by default.
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE CACHE BOOL
   "Generate compile_commands.json" FORCE)

# Set up CTest.
atlas_ctest_setup()

# Set up the analysis project from the repository.
atlas_project(USE ${ATE_BASE_PROJECT} ${ATE_BASE_VERSION})

# Generate an environment setup script. This call makes sure that whatever
# "external" we use in this analysis project, is set up correctly in the
# runtime environment.
lcg_generate_env(SH_FILE "${CMAKE_BINARY_DIR}/${ATLAS_PLATFORM}/env_setup.sh")
install(FILES "${CMAKE_BINARY_DIR}/${ATLAS_PLATFORM}/env_setup.sh"
   DESTINATION .)

# Set up CPack. This is necessary to be able to build TGZ files correctly from
# the compiled code. Making it possible to use the code on the grid.
atlas_cpack_setup()

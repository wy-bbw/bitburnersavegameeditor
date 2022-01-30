# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("BitburnerSavegameEditor")

# Include sub-projects.
enable_testing()
add_subdirectory ("BitburnerSavegameEditor")

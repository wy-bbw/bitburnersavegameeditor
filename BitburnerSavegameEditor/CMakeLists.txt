# CMakeList.txt : CMake project for BitburnerSavegameEditor, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# change this for your system
list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.2.2/msvc2019_64")

find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Add source to this project's executable.

set(SOURCEFILES 
"src/main.cpp" 
"src/gui/MainWindow.cpp" 
"src/core/SavefileManager.cpp"  
"src/core/ContentRepository.cpp" 
 "src/core/base64.cpp")

set(UIFILES "src/gui/MainWindow.ui")
add_executable (BitburnerEditor  ${SOURCEFILES} ${UIFILES}  "include/core/base64.h" "src/core/base64.cpp")

target_include_directories(BitburnerEditor
    PUBLIC
    "include/"
    $<$<CONFIG:DEBUG>:${CMAKE_CURRENT_BINARY_DIR}>
    $<$<CONFIG:RELEASE>:${CMAKE_CURRENT_BINARY_DIR}>
)


target_link_libraries(BitburnerEditor Qt6::Widgets)

enable_testing()
add_subdirectory("test/")

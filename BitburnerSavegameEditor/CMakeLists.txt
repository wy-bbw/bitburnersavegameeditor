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
"include/gui/TreeModel.h"
"src/gui/TreeModel.cpp"
"src/main.cpp" 
"src/gui/MainWindow.cpp"
"src/gui/Raw.cpp"
"src/core/SavefileManager.cpp"  
"src/core/base64.cpp"
"src/core/json/Node.cpp"
"src/core/json/JsonParser.cpp")

set(UIFILES 
"src/gui/MainWindow.ui" "src/gui/Raw.ui")

add_executable (BitburnerEditor  ${SOURCEFILES} ${UIFILES} )

target_include_directories(BitburnerEditor
    PUBLIC
    "include/"
)

target_link_libraries(BitburnerEditor Qt6::Widgets)

add_subdirectory("test/")


find_package(Qt6 REQUIRED COMPONENTS Test)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


find_package(Boost 1.68 COMPONENTS unit_test_framework )
find_package(Qt6 COMPONENTS Widgets REQUIRED)
if (Boost_FOUND)
enable_testing(true)
set(SOURCE ../src/core/json/Node.cpp ../src/core/json/JsonParser.cpp)
add_executable(JsonParserTest unit/core/json/JsonParserTest.cpp ${SOURCE})
target_link_libraries(JsonParserTest ${Boost_LIBRARIES} Qt6::Widgets)
target_include_directories(JsonParserTest PUBLIC "../include")
add_test(NAME JsonParserTest COMMAND JsonParserTest)
ENDIF()

#set(CMAKE_AUTOMOC ON)

#add_executable(mainwindowtest "gui/MainWindowTest.cpp")
#add_test(NAME mainwindowtest COMMAND mainwindowtest)
#target_link_libraries(mainwindowtest PRIVATE Qt::Test)
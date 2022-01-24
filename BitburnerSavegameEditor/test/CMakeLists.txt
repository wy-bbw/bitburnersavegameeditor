
find_package(Qt6 REQUIRED COMPONENTS Test)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


find_package(Boost 1.68 COMPONENTS unit_test_framework REQUIRED)

enable_testing(true)

add_executable(JsonParserTest unit/core/json/JsonParserTest.cpp)
target_link_libraries(JsonParserTest ${Boost_LIBRARIES})
add_test(NAME JsonParserTest COMMAND JsonParserTest)

#set(CMAKE_AUTOMOC ON)

#add_executable(mainwindowtest "gui/MainWindowTest.cpp")
#add_test(NAME mainwindowtest COMMAND mainwindowtest)
#target_link_libraries(mainwindowtest PRIVATE Qt::Test)
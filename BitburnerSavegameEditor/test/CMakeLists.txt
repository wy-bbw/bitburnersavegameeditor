
find_package(Qt6 REQUIRED COMPONENTS Test)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(GTest CONFIG REQUIRED)

add_executable(JsonParserTest )
target_link_libraries(JsonParserTest PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
add_test(NAME JsonParserTest COMMAND JsonParserTest)

#set(CMAKE_AUTOMOC ON)

#enable_testing(true)
#add_executable(mainwindowtest "gui/MainWindowTest.cpp")
#add_test(NAME mainwindowtest COMMAND mainwindowtest)
#target_link_libraries(mainwindowtest PRIVATE Qt::Test)
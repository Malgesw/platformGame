# 'Google_test' is the subproject name
project(test)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(RunallTests Maptest.cpp RunallTests.cpp Gamecharactertest.cpp)

target_link_libraries(RunallTests gtest gtest_main core)
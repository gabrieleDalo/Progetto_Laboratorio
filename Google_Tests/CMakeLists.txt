project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# adding the Google_Tests_run target
set(SOURCE_FILES runAllTests.cpp ModelTest.cpp ControllerFixture.cpp)
add_executable(Google_Tests_run ${SOURCE_FILES})

# linking Google_Tests_run

target_link_libraries(Google_Tests_run gtest gtest_main)
project(Google_tests)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_FILES
        main.cpp
        list.cpp
        vector.cpp
        stack.cpp
        queue.cpp
        map.cpp)

add_executable(Google_Tests_run ${TEST_FILES})

add_executable(map_check test.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main testlib)
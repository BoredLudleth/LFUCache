cmake_minimum_required(VERSION 3.0)

project(cache)

set(CMAKE_CXX_STANDARD 20)

include_directories(include/)

add_executable (lfu src/lfu.cpp)
add_executable (perfect src/perfect.cpp)

enable_testing()
find_package(GTest REQUIRED)

add_executable(cache_test src/cache_test.cpp)
target_link_libraries(
    cache_test
  GTest::gtest_main
)

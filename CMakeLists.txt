cmake_minimum_required(VERSION 3.0)

project(cache)

set(CMAKE_CXX_STANDARD 17)

include_directories(include/)

set (HEADERS include/lfu_cache.hpp)
set (SOURCES src/main.cpp src/lfu_cache.cpp)

add_executable (lfu src/lfu.cpp include/lfu_cache.hpp)
add_executable (perfect src/perfect.cpp include/perfect_cache.hpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(cache_test include/cache_test.hpp src/cache_test.cpp)
target_link_libraries(
    cache_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(cache_test)

cmake_minimum_required(VERSION 3.0)

project(cache)

set(CMAKE_CXX_STANDARD 17)

# set(CXX_COMPILE_FLAGS "-Wall -Wextra -Wpedantic -Werror")
# set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${CXX_COMPILE_FLAGS})

include_directories(include/)

set (HEADERS include/lfu_cache.hpp)
set (SOURCES src/main.cpp src/lfu_cache.cpp)

add_executable (lfu src/lfu.cpp include/lfu_cache.hpp)
add_executable (perfect src/perfect.cpp include/perfect_cache.hpp)

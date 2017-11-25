cmake_minimum_required(VERSION 3.8)
project(rakeman_engine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(deps)
add_subdirectory(src)
add_subdirectory(test)

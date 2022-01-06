cmake_minimum_required(VERSION 3.16)
project(src)

set(CMAKE_CXX_STANDARD 17)

add_executable(main my_prog.cpp)
target_link_libraries(main pthread)

cmake_minimum_required(VERSION 3.1)
project(demo)

add_executable(demo main.cpp thread_pool.cpp thread_pool.h)

target_link_libraries(demo pthread)
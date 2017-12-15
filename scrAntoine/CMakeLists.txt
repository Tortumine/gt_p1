cmake_minimum_required(VERSION 3.8.2)
project(path C)

add_subdirectory(cavalier)


set(CMAKE_C_STANDARD 99)

add_executable(path path.c)
target_link_libraries(path cavalier)

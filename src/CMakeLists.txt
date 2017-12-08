cmake_minimum_required(VERSION 3.9)
project(gt_p1 C)

add_subdirectory(graphes)
add_subdirectory(cavalier)


set(CMAKE_C_STANDARD 99)


add_executable(gt_p1 main.c)
target_link_libraries(gt_p1 graphes cavalier)
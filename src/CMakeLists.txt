cmake_minimum_required(VERSION 3.8.2)
project(gt_p1 C)

find_package(OpenMP)
if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
endif()

set(CMAKE_C_STANDARD 99)

add_subdirectory(graphes)
add_subdirectory(cavalier)

add_executable(gt_p1 main.c)
target_link_libraries(gt_p1 graphes cavalier)

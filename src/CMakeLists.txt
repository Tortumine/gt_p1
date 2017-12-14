cmake_minimum_required(VERSION 3.8.2)
project(gt_p1 C)

add_subdirectory(graphes)
add_subdirectory(cavalier)

if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

set(CMAKE_C_STANDARD 99)

add_executable(gt_p1 main.c)
target_link_libraries(gt_p1 graphes cavalier)
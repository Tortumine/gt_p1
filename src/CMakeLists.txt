cmake_minimum_required(VERSION 3.8.2)

project(gt_p1 C)

find_package(OpenMP)
if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
endif()

set(CMAKE_C_STANDARD 99)


add_subdirectory(graphes)
add_subdirectory(bruteforce)
add_subdirectory(Generateur)

add_executable(path path.c)
add_executable(path_all path_all.c)
target_link_libraries(path Generateur)
target_link_libraries(path_all graphes bruteforce)


cmake_minimum_required(VERSION 3.0)

project(Lab2)

add_executable(atlas src/atlas.c src/sortings.c src/wtime.c src/algorithms.c src/parser.c)
add_executable(2dpacking src/2dpacking.c src/sortings.c src/wtime.c src/algorithms.c src/parser.c)
add_executable(game src/lab3.cpp)
target_include_directories(atlas PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(2dpacking PRIVATE ${PROJECT_SOURCE_DIR}/include)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
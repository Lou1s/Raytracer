cmake_minimum_required(VERSION 3.0.0)
project(Raytracer VERSION 0.1.0)


include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

file(GLOB all_SRCS
    "${PROJECT_SOURCE_DIR}/include/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.c"
 )

add_executable(Raytracer ${all_SRCS})
target_link_libraries(Raytracer)
add_subdirectory(tests)
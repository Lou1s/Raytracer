cmake_minimum_required(VERSION 3.5.0)
project(Raytracer VERSION 0.1.0)
set(CMAKE_C_STANDARD 23)

add_compile_options(-Wall -Wextra -Wpedantic)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

file(GLOB all_SRCS
    "${PROJECT_SOURCE_DIR}/include/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.c"
 )

add_executable(Raytracer ${all_SRCS})
find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
    target_link_libraries(Raytracer PUBLIC ${MATH_LIBRARY})
endif()
add_subdirectory(tests)
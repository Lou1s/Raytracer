cmake_minimum_required(VERSION 3.0.0)
project(Raytracer VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(lib/glfw)
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

file(GLOB all_SRCS
    "${PROJECT_SOURCE_DIR}/include/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.c"
    "${PROJECT_SOURCE_DIR}/external/*.h"
    )

add_executable(Raytracer ${all_SRCS})
target_link_libraries(Raytracer glfw)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
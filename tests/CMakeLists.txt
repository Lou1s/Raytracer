enable_testing()
include_directories(
    ${PROJECT_SOURCE_DIR}/include
)
list(APPEND TESTS tupleTest)
list(APPEND TESTS colourTest)
list(APPEND TESTS canvasTest)
list(APPEND TESTS matrixTest)
list(APPEND TESTS rayTest)
list(APPEND TESTS sphereTest)

list(REMOVE_ITEM all_SRCS "${PROJECT_SOURCE_DIR}/src/main.c")
foreach(TEST IN LISTS TESTS)
    add_executable(${TEST} ${TEST}.c ${all_SRCS})
    add_dependencies(${TEST} ${TEST})
    add_test(${TEST} ${TEST})

    if(MATH_LIBRARY)
        target_link_libraries(${TEST} ${MATH_LIBRARY})
    endif()

    target_link_libraries(${TEST} cmocka)
endforeach()
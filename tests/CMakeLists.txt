enable_testing()
include_directories(../include)

list(APPEND TESTS tupleTest)

foreach(TEST IN LISTS TESTS)
    add_executable(${TEST} ${TEST}.c)
    add_dependencies(${TEST} ${TEST})
    add_test(${TEST} ${TEST})
    target_link_libraries(${TEST} cmocka)
endforeach()
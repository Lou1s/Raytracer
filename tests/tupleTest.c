#include "../include/tuple.h"

#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#define EPSILON 0.000001f

static void tuplePointInitTest(void **state) {
    Tuple point = {4.3, -4.2, 3.1, 1.0};
    assert_float_equal(point.x, 4.3, EPSILON);
    assert_float_equal(point.y, -4.2, EPSILON);
    assert_float_equal(point.z, 3.1, EPSILON);
    assert_float_equal(point.w, 1.0, EPSILON);

}

static void tupleVectorInitTest(void **state) {
    Tuple point = {7.0, .2, -2.5, 0.0};
    assert_float_equal(point.x, 7.0, EPSILON);
    assert_float_equal(point.y, .2, EPSILON);
    assert_float_equal(point.z, -2.5, EPSILON);
    assert_float_equal(point.w, 0.0, EPSILON);

}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(tuplePointInitTest),
        cmocka_unit_test(tupleVectorInitTest)
    };
    return cmocka_run_group_tests_name("TupleTest", tests, NULL, NULL);
}
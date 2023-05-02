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

static void pointInitTest(void **state) {
    Tuple p = point(3.1, 2.0, 4.0);
    Tuple pp = {3.1, 2.0, 4.0, 1.0};
    assert_float_equal(p.w, 1.0, EPSILON);
    assert_true(tupleEqual(p, pp));
}

static void vectorInitTest(void **state) {
    Tuple v = vector(0.1, 0.0, 101.1);
    Tuple vv = {0.1, 0.0, 101.1, 0.0};
    assert_float_equal(v.w, 0.0, EPSILON);
    assert_true(tupleEqual(v, vv));
}

static void tupleEqualTest(void **state) {
    Tuple a = {9.0, 5.45, 6.1, 1.0};
    Tuple b = {0.3, 5.45, 6.1, 1.0};
    assert_false(tupleEqual(a, b));
    b.x = 9.0;
    assert_true(tupleEqual(a, b));
    a.y = a.z = a.w = 0.0;
    assert_false(tupleEqual(a, b));
    }

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(tuplePointInitTest),
        cmocka_unit_test(tupleVectorInitTest),
        cmocka_unit_test(pointInitTest),
        cmocka_unit_test(vectorInitTest),
        cmocka_unit_test(tupleEqualTest)
    };
    return cmocka_run_group_tests_name("TupleTest", tests, NULL, NULL);
}
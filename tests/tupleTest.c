#include "../include/tuple.h"

#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static void tuplePointInitTest(void **state) {
    (void) state; /* unused */

    Tuple point = {4.3, -4.2, 3.1, 1.0};
    assert_float_equal(point.x, 4.3, EPSILON);
    assert_float_equal(point.y, -4.2, EPSILON);
    assert_float_equal(point.z, 3.1, EPSILON);
    assert_float_equal(point.w, 1.0, EPSILON);

}

static void tupleVectorInitTest(void **state) {
    (void) state; /* unused */

    Tuple point = {7.0, .2, -2.5, 0.0};
    assert_float_equal(point.x, 7.0, EPSILON);
    assert_float_equal(point.y, .2, EPSILON);
    assert_float_equal(point.z, -2.5, EPSILON);
    assert_float_equal(point.w, 0.0, EPSILON);

}

static void pointInitTest(void **state) {
    (void) state; /* unused */

    Point p = getPoint(3.1, 2.0, 4.0);
    Tuple pp = {3.1, 2.0, 4.0, 1.0};
    assert_float_equal(p.w, 1.0, EPSILON);
    assert_true(tuplesEqual(p, pp));
}

static void vectorInitTest(void **state) {
    (void) state; /* unused */

    Vector v = getVector(0.1, 0.0, 101.1);
    Tuple vv = {0.1, 0.0, 101.1, 0.0};
    assert_float_equal(v.w, 0.0, EPSILON);
    assert_true(tuplesEqual(v, vv));
}

static void tuplesEqualTest(void **state) {
    (void) state; /* unused */

    Tuple a = {9.0, 5.45, 6.1, 1.0};
    Tuple b = {0.3, 5.45, 6.1, 1.0};
    assert_false(tuplesEqual(a, b));
    b.x = 9.0;
    assert_true(tuplesEqual(a, b));
    a.y = a.z = a.w = 0.0;
    assert_false(tuplesEqual(a, b));

    }

static void negateTupleTest(void **state) {
    (void) state; /* unused */

    Point p = getPoint(1.1, 2.3, -4.0);
    Point pp = negateTuple(p);
    assert_float_equal(pp.x, -1.1, EPSILON);
    assert_float_equal(pp.y, -2.3, EPSILON);
    assert_float_equal(pp.z, 4.0, EPSILON);
    assert_float_equal(pp.w, -1.0, EPSILON);

    Vector v = getVector(-1.1, -2.3, 4.0);
    Vector vv = negateTuple(v);
    assert_float_equal(vv.x, 1.1, EPSILON);
    assert_float_equal(vv.y, 2.3, EPSILON);
    assert_float_equal(vv.z, -4.0, EPSILON);
    assert_float_equal(vv.w, 0.0, EPSILON);

    }
static void addTupleTest(void **state) {
    (void) state; /* unused */

    Vector v = getVector(1.0, 2.4, -5.0);
    Point p = getPoint(3.1, -2.4, -20.0);
    Tuple sum = addTuples(v, p);
    Tuple expected = {1.0 + 3.1, 2.4 - 2.4, -5.0 - 20.0, 0.0 + 1.0};
    assert_true(tuplesEqual(expected, sum));
}

static void subtractTupleTest(void **state) {
    (void) state; /* unused */

    Vector v = getVector(1.0, 2.4, -5.0);
    Point p = getPoint(3.1, -2.4, -20.0);
    Tuple diff = subtractTuples(v, p);
    Tuple expected = {1.0 - 3.1, 2.4 + 2.4, -5.0 + 20.0, 0.0 - 1.0};
    assert_true(tuplesEqual(expected, diff));
}

static void multTupleScalarTest(void **state) {
    (void) state; /* unused */

    Tuple t = {1, -2, 3, -4};
    float s = 0.5;
    Tuple result = {0.5, -1, 1.5, -2};
    assert_true(tuplesEqual(result, multTupleScalar(t, s)));
}

static void divideTupleScalarTest(void **state) {
    (void) state; /* unused */

    Tuple t = {1, -2, 3, -4};
    float s = 2;
    Tuple result = {0.5, -1, 1.5, -2};
    assert_true(tuplesEqual(result, divideTupleScalar(t, s)));
}

static void vectorMagnitudeTest(void **state) {
    (void) state; /* unused */

    Vector v = getVector(1, 0, 0);
    assert_float_equal(vectorMagnitude(v), 1.0, EPSILON);
    
    Vector v1 = getVector(0, 1, 0);
    assert_float_equal(vectorMagnitude(v1), 1.0, EPSILON);
    
    Vector v2 = getVector(0, 0, 1);
    assert_float_equal(vectorMagnitude(v2), 1.0, EPSILON);
    
    Vector v3 = getVector(1,2,3);
    assert_float_equal(vectorMagnitude(v3), sqrt(14), EPSILON);
    
    Vector v4 = getVector(-1,-2,-3);
    assert_float_equal(vectorMagnitude(v4), sqrt(14), EPSILON);
}

static void vectorNormaliseTest(void **state) {
    (void) state; /* unused */

    Vector v = getVector(4,0,0);
    assert_true(tuplesEqual(vectorNormalise(v), getVector(1,0,0)));
    v = getVector(1,2,3);
    assert_true(tuplesEqual(vectorNormalise(v), getVector(1/sqrtf(14),2/sqrtf(14),3/sqrtf(14))));
}

static void dotProdVectorsTest(void **state) {
    (void) state; /* unused */

    Vector a = getVector(1, 2, 3);
    Vector b = getVector(2, 3, 4);
    assert_float_equal(dotProdVectors(a, b), 20.0, EPSILON);
}

static void crossProductVectorsTest(void **state) {
    (void) state; /* unused */

    Vector a = getVector(1, 2, 3);
    Vector b = getVector(2, 3, 4);
    assert_true(tuplesEqual(crossProductVectors(a, b), getVector(-1, 2, -1)));
    assert_true(tuplesEqual(crossProductVectors(b, a), getVector(1, -2, 1)));
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(tuplePointInitTest),
        cmocka_unit_test(tupleVectorInitTest),
        cmocka_unit_test(pointInitTest),
        cmocka_unit_test(vectorInitTest),
        cmocka_unit_test(tuplesEqualTest),
        cmocka_unit_test(negateTupleTest),
        cmocka_unit_test(addTupleTest),
        cmocka_unit_test(subtractTupleTest),
        cmocka_unit_test(multTupleScalarTest),
        cmocka_unit_test(divideTupleScalarTest),
        cmocka_unit_test(vectorMagnitudeTest),
        cmocka_unit_test(vectorNormaliseTest),
        cmocka_unit_test(dotProdVectorsTest),
        cmocka_unit_test(crossProductVectorsTest)

    };
    return cmocka_run_group_tests_name("TupleTest", tests, NULL, NULL);
}

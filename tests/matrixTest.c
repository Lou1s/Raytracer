#include "../include/matrix.h"
#include "constants.h"
#include "tuple.h"

#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

void createMatrixTest(void **state) {
    (void) state; /* unused */

    Matrix *m = createMatrix(4, 5);
    assert_int_equal(m->rows,4);
    assert_int_equal(m->columns, 5);
    for (int i = 0; i < 20; i++) {
        assert_float_equal(m->data[i], 0.0, EPSILON);
    }
    destroyMatrix(&m);

    assert_null(m);

}

void getMatrixCellTest_1(void **state) {
    (void) state; /* unused */
    Matrix *m = createMatrix(2, 2);
    m->data[0] = 1.0;
    m->data[1] = 2.0;
    m->data[2] = -40.0;
    m->data[3] = -0.04;

    assert_float_equal(*getMatrixCell(m, 0, 0), 1.0, EPSILON);
    assert_float_equal(*getMatrixCell(m, 0, 1), 2.0, EPSILON);
    assert_float_equal(*getMatrixCell(m, 1, 0), -40.0, EPSILON);
    assert_float_equal(*getMatrixCell(m, 1, 1), -0.04, EPSILON);
    destroyMatrix(&m);
}

void getMatrixCellTest_2(void **state) {
    (void) state; /* unused */

    Matrix *m = createMatrix(4, 4);
    *getMatrixCell(m, 0, 0) = 1.0;
    *getMatrixCell(m, 0, 1) = 3.0;
    *getMatrixCell(m, 0, 2) = 3.0;
    *getMatrixCell(m, 0, 3) = 4.0;
    *getMatrixCell(m, 1, 0) = 5.5;
    *getMatrixCell(m, 1, 1) = 6.5;
    *getMatrixCell(m, 1, 2) = 7.5;
    *getMatrixCell(m, 1, 3) = 8.5;
    *getMatrixCell(m, 2, 0) = 9.0;
    *getMatrixCell(m, 2, 1) = 10.0;
    *getMatrixCell(m, 2, 2) = 11.0;
    *getMatrixCell(m, 2, 3) = 12.0;
    *getMatrixCell(m, 3, 0) = 13.5;
    *getMatrixCell(m, 3, 1) = 14.5;
    *getMatrixCell(m, 3, 2) = 15.5;
    *getMatrixCell(m, 3, 3) = 16.5;


    assert_float_equal(*getMatrixCell(m, 0, 0), 1.0, EPSILON);
    assert_float_equal(*getMatrixCell(m, 0, 3), 4.0, EPSILON);
    assert_float_equal(*getMatrixCell(m, 1, 0), 5.5, EPSILON);
    assert_float_equal(*getMatrixCell(m, 1, 2), 7.5, EPSILON);
    assert_float_equal(*getMatrixCell(m, 2, 2), 11.0, EPSILON);
    assert_float_equal(*getMatrixCell(m, 3, 0), 13.5, EPSILON);
    assert_float_equal(*getMatrixCell(m, 3, 2), 15.5, EPSILON);
    destroyMatrix(&m);
}

void matricesEqualTest(void **state) {
    (void) state; /* unused */

    Matrix *m = createMatrix(4, 4);
    *getMatrixCell(m, 0, 0) = 1.0;
    *getMatrixCell(m, 0, 1) = 2.0;
    *getMatrixCell(m, 0, 2) = 3.0;
    *getMatrixCell(m, 0, 3) = 4.0;
    *getMatrixCell(m, 1, 0) = 5.0;
    *getMatrixCell(m, 1, 1) = 6.0;
    *getMatrixCell(m, 1, 2) = 7.0;
    *getMatrixCell(m, 1, 3) = 8.0;
    *getMatrixCell(m, 2, 0) = 9.0;
    *getMatrixCell(m, 2, 1) = 8.0;
    *getMatrixCell(m, 2, 2) = 7.0;
    *getMatrixCell(m, 2, 3) = 6.0;
    *getMatrixCell(m, 3, 0) = 5.0;
    *getMatrixCell(m, 3, 1) = 4.0;
    *getMatrixCell(m, 3, 2) = 3.0;
    *getMatrixCell(m, 3, 3) = 2.0;

    Matrix *m1 = createMatrix(4, 4);
    *getMatrixCell(m1, 0, 0) = 1.0;
    *getMatrixCell(m1, 0, 1) = 2.0;
    *getMatrixCell(m1, 0, 2) = 3.0;
    *getMatrixCell(m1, 0, 3) = 4.0;
    *getMatrixCell(m1, 1, 0) = 5.0;
    *getMatrixCell(m1, 1, 1) = 6.0;
    *getMatrixCell(m1, 1, 2) = 7.0;
    *getMatrixCell(m1, 1, 3) = 8.0;
    *getMatrixCell(m1, 2, 0) = 9.0;
    *getMatrixCell(m1, 2, 1) = 8.0;
    *getMatrixCell(m1, 2, 2) = 7.0;
    *getMatrixCell(m1, 2, 3) = 6.0;
    *getMatrixCell(m1, 3, 0) = 5.0;
    *getMatrixCell(m1, 3, 1) = 4.0;
    *getMatrixCell(m1, 3, 2) = 3.0;
    *getMatrixCell(m1, 3, 3) = 2.0;

    assert_true(matricesEqual(m, m1));

    destroyMatrix(&m);
    destroyMatrix(&m1);
}

void matricesNotEqualTest(void **state) {
    (void) state; /* unused */

    Matrix *m1 = createMatrix(4, 4);
    *getMatrixCell(m1, 0, 0) = 1.0;
    *getMatrixCell(m1, 0, 1) = 2.0;
    *getMatrixCell(m1, 0, 2) = 3.0;
    *getMatrixCell(m1, 0, 3) = 4.0;
    *getMatrixCell(m1, 1, 0) = 5.0;
    *getMatrixCell(m1, 1, 1) = 6.0;
    *getMatrixCell(m1, 1, 2) = 7.0;
    *getMatrixCell(m1, 1, 3) = 8.0;
    *getMatrixCell(m1, 2, 0) = 9.0;
    *getMatrixCell(m1, 2, 1) = 8.0;
    *getMatrixCell(m1, 2, 2) = 7.0;
    *getMatrixCell(m1, 2, 3) = 6.0;
    *getMatrixCell(m1, 3, 0) = 5.0;
    *getMatrixCell(m1, 3, 1) = 4.0;
    *getMatrixCell(m1, 3, 2) = 3.0;
    *getMatrixCell(m1, 3, 3) = 2.0;

    Matrix *m2 = createMatrix(4, 4);
    *getMatrixCell(m2, 0, 0) = 2.0;
    *getMatrixCell(m2, 0, 1) = 3.0;
    *getMatrixCell(m2, 0, 2) = 4.0;
    *getMatrixCell(m2, 0, 3) = 5.0;
    *getMatrixCell(m2, 1, 0) = 6.0;
    *getMatrixCell(m2, 1, 1) = 7.0;
    *getMatrixCell(m2, 1, 2) = 8.0;
    *getMatrixCell(m2, 1, 3) = 9.0;
    *getMatrixCell(m2, 2, 0) = 8.0;
    *getMatrixCell(m2, 2, 1) = 7.0;
    *getMatrixCell(m2, 2, 2) = 6.0;
    *getMatrixCell(m2, 2, 3) = 5.0;
    *getMatrixCell(m2, 3, 0) = 4.0;
    *getMatrixCell(m2, 3, 1) = 3.0;
    *getMatrixCell(m2, 3, 2) = 2.0;
    *getMatrixCell(m2, 3, 3) = 1.0;

    assert_false(matricesEqual(m1, m2));
    destroyMatrix(&m1);
    destroyMatrix(&m2);

    Matrix *m3 = createMatrix(2, 1);
    Matrix *m4 = createMatrix(1, 2);
    assert_false(matricesEqual(m3, m4));

    destroyMatrix(&m3);
    destroyMatrix(&m4);

}

void multMatrixTest(void **state) {
    (void) state; /* unused */

    Matrix *m1 = createMatrix(4, 4);
    *getMatrixCell(m1, 0, 0) = 1.0;
    *getMatrixCell(m1, 0, 1) = 2.0;
    *getMatrixCell(m1, 0, 2) = 3.0;
    *getMatrixCell(m1, 0, 3) = 4.0;
    *getMatrixCell(m1, 1, 0) = 5.0;
    *getMatrixCell(m1, 1, 1) = 6.0;
    *getMatrixCell(m1, 1, 2) = 7.0;
    *getMatrixCell(m1, 1, 3) = 8.0;
    *getMatrixCell(m1, 2, 0) = 9.0;
    *getMatrixCell(m1, 2, 1) = 8.0;
    *getMatrixCell(m1, 2, 2) = 7.0;
    *getMatrixCell(m1, 2, 3) = 6.0;
    *getMatrixCell(m1, 3, 0) = 5.0;
    *getMatrixCell(m1, 3, 1) = 4.0;
    *getMatrixCell(m1, 3, 2) = 3.0;
    *getMatrixCell(m1, 3, 3) = 2.0;

    Matrix *m2 = createMatrix(4, 4);
    *getMatrixCell(m2, 0, 0) = -2.0;
    *getMatrixCell(m2, 0, 1) = 1.0;
    *getMatrixCell(m2, 0, 2) = 2.0;
    *getMatrixCell(m2, 0, 3) = 3.0;
    *getMatrixCell(m2, 1, 0) = 3.0;
    *getMatrixCell(m2, 1, 1) = 2.0;
    *getMatrixCell(m2, 1, 2) = 1.0;
    *getMatrixCell(m2, 1, 3) = -1.0;
    *getMatrixCell(m2, 2, 0) = 4.0;
    *getMatrixCell(m2, 2, 1) = 3.0;
    *getMatrixCell(m2, 2, 2) = 6.0;
    *getMatrixCell(m2, 2, 3) = 5.0;
    *getMatrixCell(m2, 3, 0) = 1.0;
    *getMatrixCell(m2, 3, 1) = 2.0;
    *getMatrixCell(m2, 3, 2) = 7.0;
    *getMatrixCell(m2, 3, 3) = 8.0;

    Matrix *m3 = multMatrix(m1, m2);

    Matrix *m4 = createMatrix(4, 4);
    *getMatrixCell(m4, 0, 0) = 20.0;
    *getMatrixCell(m4, 0, 1) = 22.0;
    *getMatrixCell(m4, 0, 2) = 50.0;
    *getMatrixCell(m4, 0, 3) = 48.0;
    *getMatrixCell(m4, 1, 0) = 44.0;
    *getMatrixCell(m4, 1, 1) = 54.0;
    *getMatrixCell(m4, 1, 2) = 114.0;
    *getMatrixCell(m4, 1, 3) = 108.0;
    *getMatrixCell(m4, 2, 0) = 40.0;
    *getMatrixCell(m4, 2, 1) = 58.0;
    *getMatrixCell(m4, 2, 2) = 110.0;
    *getMatrixCell(m4, 2, 3) = 102.0;
    *getMatrixCell(m4, 3, 0) = 16.0;
    *getMatrixCell(m4, 3, 1) = 26.0;
    *getMatrixCell(m4, 3, 2) = 46.0;
    *getMatrixCell(m4, 3, 3) = 42.0;

    assert_true(matricesEqual(m3, m4));

    destroyMatrix(&m1);
    destroyMatrix(&m2);
    destroyMatrix(&m3);
    destroyMatrix(&m4);
}

void matTupleMultTest(void ** state) {
    (void) state; /* unused */

    Matrix *m = createMatrix(4, 4);
    *getMatrixCell(m, 0, 0) = 1.0;
    *getMatrixCell(m, 0, 1) = 2.0;
    *getMatrixCell(m, 0, 2) = 3.0;
    *getMatrixCell(m, 0, 3) = 4.0;
    *getMatrixCell(m, 1, 0) = 2.0;
    *getMatrixCell(m, 1, 1) = 4.0;
    *getMatrixCell(m, 1, 2) = 4.0;
    *getMatrixCell(m, 1, 3) = 2.0;
    *getMatrixCell(m, 2, 0) = 8.0;
    *getMatrixCell(m, 2, 1) = 6.0;
    *getMatrixCell(m, 2, 2) = 4.0;
    *getMatrixCell(m, 2, 3) = 1.0;
    *getMatrixCell(m, 3, 0) = 0.0;
    *getMatrixCell(m, 3, 1) = 0.0;
    *getMatrixCell(m, 3, 2) = 0.0;
    *getMatrixCell(m, 3, 3) = 1.0;

    Tuple t = {1.0, 2.0, 3.0, 1.0};
    Tuple res = matTupleMult(m, t);
    Tuple correct_res = {18.0, 24.0, 33.0, 1.0};

    assert_true(tuplesEqual(res, correct_res));
    
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(createMatrixTest),
        cmocka_unit_test(getMatrixCellTest_1),
        cmocka_unit_test(getMatrixCellTest_2),
        cmocka_unit_test(matricesEqualTest),
        cmocka_unit_test(matricesNotEqualTest),
        cmocka_unit_test(multMatrixTest),
        cmocka_unit_test(matTupleMultTest)
    };
    return cmocka_run_group_tests_name("matrixTest", tests, NULL, NULL);
}

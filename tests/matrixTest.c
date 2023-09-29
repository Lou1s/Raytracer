#include "../include/matrix.h"
#include "constants.h"

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

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(createMatrixTest),
        cmocka_unit_test(getMatrixCellTest_1),
        cmocka_unit_test(getMatrixCellTest_2)

    };
    return cmocka_run_group_tests_name("matrixTest", tests, NULL, NULL);
}

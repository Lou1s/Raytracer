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

    Matrix *m = createMatrix();
    for (int x = 0; x < MAT_SIZE; x++) {
        for (int y = 0; y < MAT_SIZE; y++) {
            assert_float_equal(m->data[x][y], 0.0, EPSILON);
        }
    }
    destroyMatrix(&m);
    assert_null(m);
}

void getMatrixCellTest_2(void **state) {
    (void) state; /* unused */

    Matrix *m = createMatrix();
    m->data[0][0] = 1.0;
    m->data[0][1] = 3.0;
    m->data[0][2] = 3.0;
    m->data[0][3] = 4.0;
    m->data[1][0] = 5.5;
    m->data[1][1] = 6.5;
    m->data[1][2] = 7.5;
    m->data[1][3] = 8.5;
    m->data[2][0] = 9.0;
    m->data[2][1] = 10.0;
    m->data[2][2] = 11.0;
    m->data[2][3] = 12.0;
    m->data[3][0] = 13.5;
    m->data[3][1] = 14.5;
    m->data[3][2] = 15.5;
    m->data[3][3] = 16.5;


    assert_float_equal(m->data[0][0], 1.0, EPSILON);
    assert_float_equal(m->data[0][3], 4.0, EPSILON);
    assert_float_equal(m->data[1][0], 5.5, EPSILON);
    assert_float_equal(m->data[1][2], 7.5, EPSILON);
    assert_float_equal(m->data[2][2], 11.0, EPSILON);
    assert_float_equal(m->data[3][0], 13.5, EPSILON);
    assert_float_equal(m->data[3][2], 15.5, EPSILON);
    destroyMatrix(&m);
}

void matricesEqualTest(void **state) {
    (void) state; /* unused */

    Matrix *m = createMatrix();
    m->data[0][0] = 1.0;
    m->data[0][1] = 2.0;
    m->data[0][2] = 3.0;
    m->data[0][3] = 4.0;
    m->data[1][0] = 5.0;
    m->data[1][1] = 6.0;
    m->data[1][2] = 7.0;
    m->data[1][3] = 8.0;
    m->data[2][0] = 9.0;
    m->data[2][1] = 8.0;
    m->data[2][2] = 7.0;
    m->data[2][3] = 6.0;
    m->data[3][0] = 5.0;
    m->data[3][1] = 4.0;
    m->data[3][2] = 3.0;
    m->data[3][3] = 2.0;

    Matrix *m1 = createMatrix();
    m1->data[0][0] = 1.0;
    m1->data[0][1] = 2.0;
    m1->data[0][2] = 3.0;
    m1->data[0][3] = 4.0;
    m1->data[1][0] = 5.0;
    m1->data[1][1] = 6.0;
    m1->data[1][2] = 7.0;
    m1->data[1][3] = 8.0;
    m1->data[2][0] = 9.0;
    m1->data[2][1] = 8.0;
    m1->data[2][2] = 7.0;
    m1->data[2][3] = 6.0;
    m1->data[3][0] = 5.0;
    m1->data[3][1] = 4.0;
    m1->data[3][2] = 3.0;
    m1->data[3][3] = 2.0;

    assert_true(matricesEqual(m, m1));

    destroyMatrix(&m);
    destroyMatrix(&m1);
}

void matricesNotEqualTest(void **state) {
    (void) state; /* unused */

    Matrix *m1 = createMatrix();
    m1->data[0][0] = 1.0;
    m1->data[0][1] = 2.0;
    m1->data[0][2] = 3.0;
    m1->data[0][3] = 4.0;
    m1->data[1][0] = 5.0;
    m1->data[1][1] = 6.0;
    m1->data[1][2] = 7.0;
    m1->data[1][3] = 8.0;
    m1->data[2][0] = 9.0;
    m1->data[2][1] = 8.0;
    m1->data[2][2] = 7.0;
    m1->data[2][3] = 6.0;
    m1->data[3][0] = 5.0;
    m1->data[3][1] = 4.0;
    m1->data[3][2] = 3.0;
    m1->data[3][3] = 2.0;

    Matrix *m2 = createMatrix();
    m2->data[0][0] = 2.0;
    m2->data[0][1] = 3.0;
    m2->data[0][2] = 4.0;
    m2->data[0][3] = 5.0;
    m2->data[1][0] = 6.0;
    m2->data[1][1] = 7.0;
    m2->data[1][2] = 8.0;
    m2->data[1][3] = 9.0;
    m2->data[2][0] = 8.0;
    m2->data[2][1] = 7.0;
    m2->data[2][2] = 6.0;
    m2->data[2][3] = 5.0;
    m2->data[3][0] = 4.0;
    m2->data[3][1] = 3.0;
    m2->data[3][2] = 2.0;
    m2->data[3][3] = 1.0;

    assert_false(matricesEqual(m1, m2));
    destroyMatrix(&m1);
    destroyMatrix(&m2);

    Matrix *m3 = createMatrix();
    Matrix *m4 = createMatrix();
    assert_true(matricesEqual(m3, m4));

    destroyMatrix(&m3);
    destroyMatrix(&m4);
}

void multMatrixTest(void **state) {
    (void) state; /* unused */

    Matrix *m1 = createMatrix();
    m1->data[0][0] = 1.0;
    m1->data[0][1] = 2.0;
    m1->data[0][2] = 3.0;
    m1->data[0][3] = 4.0;
    m1->data[1][0] = 5.0;
    m1->data[1][1] = 6.0;
    m1->data[1][2] = 7.0;
    m1->data[1][3] = 8.0;
    m1->data[2][0] = 9.0;
    m1->data[2][1] = 8.0;
    m1->data[2][2] = 7.0;
    m1->data[2][3] = 6.0;
    m1->data[3][0] = 5.0;
    m1->data[3][1] = 4.0;
    m1->data[3][2] = 3.0;
    m1->data[3][3] = 2.0;

    Matrix *m2 = createMatrix();
    m2->data[0][0] = -2.0;
    m2->data[0][1] = 1.0;
    m2->data[0][2] = 2.0;
    m2->data[0][3] = 3.0;
    m2->data[1][0] = 3.0;
    m2->data[1][1] = 2.0;
    m2->data[1][2] = 1.0;
    m2->data[1][3] = -1.0;
    m2->data[2][0] = 4.0;
    m2->data[2][1] = 3.0;
    m2->data[2][2] = 6.0;
    m2->data[2][3] = 5.0;
    m2->data[3][0] = 1.0;
    m2->data[3][1] = 2.0;
    m2->data[3][2] = 7.0;
    m2->data[3][3] = 8.0;

    Matrix *m3 = multMatrix(m1, m2);

    Matrix *m4 = createMatrix();
    m4->data[0][0] = 20.0;
    m4->data[0][1] = 22.0;
    m4->data[0][2] = 50.0;
    m4->data[0][3] = 48.0;
    m4->data[1][0] = 44.0;
    m4->data[1][1] = 54.0;
    m4->data[1][2] = 114.0;
    m4->data[1][3] = 108.0;
    m4->data[2][0] = 40.0;
    m4->data[2][1] = 58.0;
    m4->data[2][2] = 110.0;
    m4->data[2][3] = 102.0;
    m4->data[3][0] = 16.0;
    m4->data[3][1] = 26.0;
    m4->data[3][2] = 46.0;
    m4->data[3][3] = 42.0;

    assert_true(matricesEqual(m3, m4));

    destroyMatrix(&m1);
    destroyMatrix(&m2);
    destroyMatrix(&m3);
    destroyMatrix(&m4);
}

void matTupleMultTest(void ** state) {
    (void) state; /* unused */

    Matrix *m = createMatrix();
    m->data[0][0] = 1.0;
    m->data[0][1] = 2.0;
    m->data[0][2] = 3.0;
    m->data[0][3] = 4.0;
    m->data[1][0] = 2.0;
    m->data[1][1] = 4.0;
    m->data[1][2] = 4.0;
    m->data[1][3] = 2.0;
    m->data[2][0] = 8.0;
    m->data[2][1] = 6.0;
    m->data[2][2] = 4.0;
    m->data[2][3] = 1.0;
    m->data[3][0] = 0.0;
    m->data[3][1] = 0.0;
    m->data[3][2] = 0.0;
    m->data[3][3] = 1.0;

    Tuple t = {1.0, 2.0, 3.0, 1.0};
    Tuple res = matTupleMult(m, t);
    Tuple correct_res = {18.0, 24.0, 33.0, 1.0};

    assert_true(tuplesEqual(res, correct_res));
    
}

void identityMatrixTest(void ** state) {
    (void) state; /* unused */

    Matrix *m = createMatrix();
    m->data[0][0] = 1.0;
    m->data[0][1] = 2.0;
    m->data[0][2] = 3.0;
    m->data[0][3] = 4.0;
    m->data[1][0] = 2.0;
    m->data[1][1] = 4.0;
    m->data[1][2] = 4.0;
    m->data[1][3] = 2.0;
    m->data[2][0] = 8.0;
    m->data[2][1] = 6.0;
    m->data[2][2] = 4.0;
    m->data[2][3] = 1.0;
    m->data[3][0] = 0.0;
    m->data[3][1] = 0.0;
    m->data[3][2] = 0.0;
    m->data[3][3] = 1.0;

    Matrix *i = getIdentityMatrix();
    assert_true(matricesEqual(multMatrix(m, i), m));

    destroyMatrix(&m);
    destroyMatrix(&i);
}

void transposeMatrixTest(void ** state) {
    (void) state; /* unused */

    Matrix *m = createMatrix();
    m->data[0][0] = 0.0;
    m->data[0][1] = 9.0;
    m->data[0][2] = 3.0;
    m->data[0][3] = 0.0;
    m->data[1][0] = 9.0;
    m->data[1][1] = 8.0;
    m->data[1][2] = 0.0;
    m->data[1][3] = 8.0;
    m->data[2][0] = 1.0;
    m->data[2][1] = 8.0;
    m->data[2][2] = 5.0;
    m->data[2][3] = 3.0;
    m->data[3][0] = 0.0;
    m->data[3][1] = 0.0;
    m->data[3][2] = 5.0;
    m->data[3][3] = 8.0;

    Matrix *t_m = transposeMatrix(m);

    Matrix *m_t = createMatrix();
    m_t->data[0][0] = 0.0;
    m_t->data[0][1] = 9.0;
    m_t->data[0][2] = 1.0;
    m_t->data[0][3] = 0.0;
    m_t->data[1][0] = 9.0;
    m_t->data[1][1] = 8.0;
    m_t->data[1][2] = 8.0;
    m_t->data[1][3] = 0.0;
    m_t->data[2][0] = 3.0;
    m_t->data[2][1] = 0.0;
    m_t->data[2][2] = 5.0;
    m_t->data[2][3] = 5.0;
    m_t->data[3][0] = 0.0;
    m_t->data[3][1] = 8.0;
    m_t->data[3][2] = 3.0;
    m_t->data[3][3] = 8.0;

    assert_true(matricesEqual(t_m, m_t));
}

void transposeIdentityTest(void ** state) {
    (void) state; /* unused */

    Matrix *ident = getIdentityMatrix();
    Matrix *transposed_ident = transposeMatrix(ident);
    assert_true(matricesEqual(ident, transposed_ident));

    destroyMatrix(&ident);
    destroyMatrix(&transposed_ident);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(createMatrixTest),
        cmocka_unit_test(getMatrixCellTest_2),
        cmocka_unit_test(matricesEqualTest),
        cmocka_unit_test(matricesNotEqualTest),
        cmocka_unit_test(multMatrixTest),
        cmocka_unit_test(matTupleMultTest),
        cmocka_unit_test(identityMatrixTest),
        cmocka_unit_test(transposeMatrixTest),
        cmocka_unit_test(transposeIdentityTest)
    };
    return cmocka_run_group_tests_name("matrixTest", tests, NULL, NULL);
}

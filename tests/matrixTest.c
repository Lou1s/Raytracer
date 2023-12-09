#include "../include/matrix.h"
#include "constants.h"
#include "tuple.h"

#include <math.h>
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

void createMat3Test(void **state) {
    (void) state; /* unused */

    Mat3 *m3 = createMat3();
    for (int x = 0; x < MAT3_SIZE; x++) {
        for (int y = 0; y < MAT3_SIZE; y++) {
            assert_float_equal(m3->data[x][y], 0.0, EPSILON);
        }
    }
    destroyMat3(&m3);
    assert_null(m3);    
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

void getDeterminantTest(void ** state) {
    (void) state; /* unused */

    Matrix *m = createMatrix();
    m->data[0][0] = 6.0;
    m->data[0][1] = 4.0;
    m->data[0][2] = 4.0;
    m->data[0][3] = 4.0;
    m->data[1][0] = 5.0;
    m->data[1][1] = 5.0;
    m->data[1][2] = 7.0;
    m->data[1][3] = 6.0;
    m->data[2][0] = 4.0;
    m->data[2][1] = -9.0;
    m->data[2][2] = 3.0;
    m->data[2][3] = -7.0;
    m->data[3][0] = 9.0;
    m->data[3][1] = 1.0;
    m->data[3][2] = 7.0;
    m->data[3][3] = -6.0;

    assert_float_equal(getDeterminant(m), -2120.0, EPSILON);
    destroyMatrix(&m);
}

void nonInvertibleDeterminantTest(void ** state) {
    (void) state; /* unused */

    Matrix *m = createMatrix();
    m->data[0][0] = -4.0;
    m->data[0][1] = 2.0;
    m->data[0][2] = -2.0;
    m->data[0][3] = -2.0;
    m->data[1][0] = 9.0;
    m->data[1][1] = 6.0;
    m->data[1][2] = 2.0;
    m->data[1][3] = 6.0;
    m->data[2][0] = 0.0;
    m->data[2][1] = -5.0;
    m->data[2][2] = 1.0;
    m->data[2][3] = -5.0;
    m->data[3][0] = 0.0;
    m->data[3][1] = 0.0;
    m->data[3][2] = 0.0;
    m->data[3][3] = 0.0;

    assert_float_equal(getDeterminant(m), -0.0, EPSILON);
    destroyMatrix(&m);
}
void getCofactorTest(void ** state) {
    (void) state; /* unused */

    Matrix *m = createMatrix();
    m->data[0][0] = -2.0;
    m->data[0][1] = -8.0;
    m->data[0][2] = 3.0;
    m->data[0][3] = 5.0;
    m->data[1][0] = -3.0;
    m->data[1][1] = 1.0;
    m->data[1][2] = 7.0;
    m->data[1][3] = 3.0;
    m->data[2][0] = 1.0;
    m->data[2][1] = 2.0;
    m->data[2][2] = -9.0;
    m->data[2][3] = 6.0;
    m->data[3][0] = -6.0;
    m->data[3][1] = 7.0;
    m->data[3][2] = 7.0;
    m->data[3][3] = -9.0;

    float actual_cofactor00 = 690.0;
    float actual_cofactor01 = 447;
    float actual_cofactor02 = 210.0;
    float actual_cofactor03 = 51.0;

    assert_float_equal(actual_cofactor00, getCofactor(m, 0, 0), EPSILON);
    assert_float_equal(actual_cofactor01, getCofactor(m, 0, 1), EPSILON);
    assert_float_equal(actual_cofactor02, getCofactor(m, 0, 2), EPSILON);
    assert_float_equal(actual_cofactor03, getCofactor(m, 0, 3), EPSILON);
    destroyMatrix(&m);

}
void inverseMatrixTest(void ** state) {
    (void) state; /* unused */

    Matrix *m = createMatrix();
    m->data[0][0] = -5.0;
    m->data[0][1] = 2.0;
    m->data[0][2] = 6.0;
    m->data[0][3] = -8.0;
    m->data[1][0] = 1.0;
    m->data[1][1] = -5.0;
    m->data[1][2] = 1.0;
    m->data[1][3] = 8.0;
    m->data[2][0] = 7.0;
    m->data[2][1] = 7.0;
    m->data[2][2] = -6.0;
    m->data[2][3] = -7.0;
    m->data[3][0] = 1.0;
    m->data[3][1] = -3.0;
    m->data[3][2] = 7.0;
    m->data[3][3] = 4.0;

    Matrix *res = createMatrix();
    res->data[0][0] = 0.218045;
    res->data[0][1] = 0.451128;
    res->data[0][2] = 0.240602;
    res->data[0][3] = -0.045113;
    res->data[1][0] = -0.808271;
    res->data[1][1] = -1.456767;
    res->data[1][2] = -0.443609;
    res->data[1][3] = 0.520677;
    res->data[2][0] = -0.078947;
    res->data[2][1] = -0.223684;
    res->data[2][2] = -0.052632;
    res->data[2][3] = 0.197368;
    res->data[3][0] = -0.522556;
    res->data[3][1] = -0.813910;
    res->data[3][2] = -0.300752;
    res->data[3][3] = 0.306391;

    Matrix *inv = inverseMatrix(m);
    assert_true(matricesEqual(inv, res));
    destroyMatrix(&m);
    destroyMatrix(&res);

}

void translationTest(void ** state) {
    (void) state; /* unused */

    Matrix *translate_m = getTranslationMat(5.0, -3.0, 2.0);
    Point p = getPoint(-3.0, 4.0, 5.0);
    Point translated_p = matTupleMult(translate_m, p);
    assert_true(tuplesEqual(translated_p, getPoint(2.0, 1.0, 7.0)));
    assert_true(tuplesEqual(translated_p, translate(p, 5.0, -3.0, 2.0)));
    // Translate translated point by the original transforms inverse
    Matrix *inv_translate = inverseMatrix(translate_m);
    assert_true(tuplesEqual(matTupleMult(inv_translate, translated_p), p));
    // Test that translation does not affect vectors
    Vector v = getVector(-3.0,4.0,5.0);
    Vector translated_v = matTupleMult(translate_m, v);
    assert_true(tuplesEqual(v, translated_v));

    destroyMatrix(&inv_translate);
    destroyMatrix(&translate_m);
}

void rotationXTest(void ** state) {
    (void) state; /* unused */

    Point p = getPoint(0.0, 1.0, 0.0);
    Matrix *rot_half_quart = getRotationXMat(M_PI/4.0);
    Matrix *rot_full_quart = getRotationXMat(M_PI/2.0);
    assert_true(tuplesEqual(matTupleMult(rot_half_quart, p), 
            getPoint(0.0 , sqrtf(2.0)/2.0, sqrtf(2.0)/2.0)));
    assert_true(tuplesEqual(matTupleMult(rot_full_quart, p), 
        getPoint(0.0 , 0.0, 1.0)));
    assert_true(tuplesEqual(getPoint(0.0 , 0.0, 1.0), rotateX(p, M_PI/2.0)));
    
    destroyMatrix(&rot_half_quart);
    destroyMatrix(&rot_full_quart);
}
void rotationYTest(void ** state) {
    (void) state; /* unused */
    
    Point p = getPoint(0.0, 0.0, 1.0);
    Matrix *rot_half_quart = getRotationYMat(M_PI/4);
    Matrix *rot_full_quart = getRotationYMat(M_PI/2);
    assert_true(tuplesEqual(matTupleMult(rot_half_quart, p), 
            getPoint(sqrtf(2.0)/2.0, 0.0, sqrtf(2.0)/2.0)));
    assert_true(tuplesEqual(matTupleMult(rot_full_quart, p), 
        getPoint(1.0 , 0.0, 0.0)));
    assert_true(tuplesEqual(getPoint(1.0 , 0.0, 0.0), rotateY(p, M_PI/2.0)));

    destroyMatrix(&rot_half_quart);
    destroyMatrix(&rot_full_quart);
}
void rotationZTest(void ** state) {
    (void) state; /* unused */

    Point p = getPoint(0.0, 1.0, 0.0);
    Matrix *rot_half_quart = getRotationZMat(M_PI/4.0);
    Matrix *rot_full_quart = getRotationZMat(M_PI/2.0);
    assert_true(tuplesEqual(matTupleMult(rot_half_quart, p), 
            getPoint(-sqrtf(2.0)/2.0, sqrtf(2.0)/2.0, 0.0)));
    assert_true(tuplesEqual(matTupleMult(rot_full_quart, p), 
        getPoint(-1.0 , 0.0, 0.0)));
    
    assert_true(tuplesEqual(getPoint(-1.0 , 0.0, 0.0), rotateZ(p, M_PI/2.0)));
    destroyMatrix(&rot_half_quart);
    destroyMatrix(&rot_full_quart);
}

void scaleTest(void ** state) {
    (void) state; /* unused */

    Matrix *scale_m = getScaleMat(-1.0,1.0,1.0);
    Point p = getPoint(2.0, 3.0, 4.0);
    assert_true(tuplesEqual(getPoint(-2.0, 3.0, 4.0), matTupleMult(scale_m, p)));
    assert_true(tuplesEqual(getPoint(-2.0, 3.0, 4.0), scale(p, -1.0, 1.0, 1.0)));
    destroyMatrix(&scale_m);
}

void shearTest(void ** state) {
    (void) state; /* unused */

    Point p = getPoint(2, 3, 4);
    assert_true(tuplesEqual(getPoint(5, 3, 4), shear(p, 1,0,0,0,0,0)));
    assert_true(tuplesEqual(getPoint(6, 3, 4), shear(p, 0,1,0,0,0,0)));
    assert_true(tuplesEqual(getPoint(2, 5, 4), shear(p, 0,0,1,0,0,0)));
    assert_true(tuplesEqual(getPoint(2, 7, 4), shear(p, 0,0,0,1,0,0)));
    assert_true(tuplesEqual(getPoint(2, 3, 6), shear(p, 0,0,0,0,1,0)));
    assert_true(tuplesEqual(getPoint(2, 3, 7), shear(p, 0,0,0,0,0,1)));
}


int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(createMatrixTest),
        cmocka_unit_test(createMat3Test),
        cmocka_unit_test(getMatrixCellTest_2),
        cmocka_unit_test(matricesEqualTest),
        cmocka_unit_test(matricesNotEqualTest),
        cmocka_unit_test(multMatrixTest),
        cmocka_unit_test(matTupleMultTest),
        cmocka_unit_test(identityMatrixTest),
        cmocka_unit_test(transposeMatrixTest),
        cmocka_unit_test(transposeIdentityTest),
        cmocka_unit_test(getDeterminantTest),
        cmocka_unit_test(nonInvertibleDeterminantTest),
        cmocka_unit_test(getCofactorTest),
        cmocka_unit_test(inverseMatrixTest),
        cmocka_unit_test(translationTest),
        cmocka_unit_test(scaleTest),
        cmocka_unit_test(rotationXTest),
        cmocka_unit_test(rotationYTest),
        cmocka_unit_test(rotationZTest),
        cmocka_unit_test(shearTest)
    };
    return cmocka_run_group_tests_name("matrixTest", tests, NULL, NULL);
}

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/matrix.h"
#include "../include/constants.h"
#include "tuple.h"

Matrix* createMatrix() {
    Matrix *m = malloc(sizeof(Matrix));
    if (m == NULL) {
        return NULL;
    }
    memset(m->data, 0.0, sizeof(m->data));
    return m;
}

Mat3* createMat3() {
    Mat3 *m3 = malloc(sizeof(Mat3));
    if (m3 == NULL) {
        return NULL;
    }
    memset(m3->data, 0.0, sizeof(m3->data));
    return m3;
}

bool matricesEqual(const Matrix *m1, const Matrix *m2) {
    for (int y = 0; y < MAT_SIZE; y++) {
        for (int x = 0; x < MAT_SIZE; x++) {
            if (fabs(m1->data[x][y]) - fabs(m2->data[x][y]) > EPSILON) {
                return false;
            }
        }
    }
    return true;
    
}

Matrix* multMatrix(const Matrix *m1, const Matrix *m2) {
    Matrix *mult_result = createMatrix();
    if (mult_result == NULL) {
        return NULL;
    }
    for (int x = 0; x < MAT_SIZE; x++) {
        for (int y = 0; y < MAT_SIZE; y++) {
            for (int i = 0; i < MAT_SIZE; i++) {
                mult_result->data[x][y] += m1->data[x][i] * m2->data[i][y];
            }
        }
    }
    return mult_result;
}

/* Helper functions for letting us loop through a vector/tuple */
static float* getTupleValByIndex(Tuple *t, const int index) {
    switch(index) {
        case 0: return &t->x;
        case 1: return &t->y;
        case 2: return &t->z;
        case 3: return &t->w;
    }
    assert(0);
}

Tuple matTupleMult(const Matrix *m, Tuple v) {
    Tuple result = {0.0, 0.0, 0.0, 0.0};
    for (int i = 0; i < MAT_SIZE; i++) {
        for (int y = 0; y < MAT_SIZE; y++) {
            *getTupleValByIndex(&result, i) += m->data[i][y] * (*getTupleValByIndex(&v, y));
        }
    }
    return result;    
}

Matrix* getIdentityMatrix() {
    Matrix *identity_matrix = createMatrix();
    if (identity_matrix==NULL) {
        return NULL;
    }

    for (int x=0; x < MAT_SIZE; x++) {
        for (int y=0; y < MAT_SIZE; y++) {
            if (x==y){
                identity_matrix->data[x][y] = 1.0;
            }
        }
    }
    return identity_matrix;
}

Matrix* transposeMatrix(const Matrix *m) {
    Matrix *transpose_matrix = createMatrix();
    if (transpose_matrix == NULL) {
        return NULL;
    }
    for (int x = 0; x < MAT_SIZE; x++) {
        for (int y = 0; y < MAT_SIZE; y++) {
            transpose_matrix->data[y][x] = m->data[x][y];
        }
    }
    return transpose_matrix;
}
/* Helper function to quickly compute a Mat3 determinant. Hard coded as it was just easier*/
static float getDeterminantMat3(const Mat3 *m3) {
    return (m3->data[0][0] * m3->data[1][1] * m3->data[2][2]) + (m3->data[0][1] * m3->data[1][2] * m3->data[2][0]) + 
           (m3->data[0][2] * m3->data[1][0] * m3->data[2][1]) - (m3->data[0][0] * m3->data[1][2] * m3->data[2][1]) - 
           (m3->data[0][1] * m3->data[1][0] * m3->data[2][2]) - (m3->data[0][2] * m3->data[1][1] * m3->data[2][0]) ;
}

/*Helper function for producing a sub matrix of size 3x3. */
static Mat3* getSubMatrix(const Matrix *m, int row, int column)  {
    Mat3 *sub_matrix = createMat3();
    int sub_row, sub_col;
    for (int x = 0; x < 3; x++) {
        sub_row = (x < row) ? x: x + 1;
        for (int y = 0; y < 3; y++) {
            sub_col = (y < column) ? y: y + 1;
            sub_matrix->data[x][y] = m->data[sub_row][sub_col];
        }
    }
    return sub_matrix;
}

float getCofactor(const Matrix *m, const int row, const int column) {
    Mat3 *sub_mat = getSubMatrix(m, row, column);
    assert(sub_mat != NULL);

    float sub_mat_det = getDeterminantMat3(sub_mat);
    destroyMat3(&sub_mat);
    // Compute cofactor sign (+/-). Add two to get rid of 0 index for row and col
    float sign = ((row + column + 2) % 2 == 0) ? 1.0 : -1.0;
    return sign * sub_mat_det;    
}

float getDeterminant(const Matrix *m) {
    float determinant = 0.0;
    for (int i = 0; i < MAT_SIZE; i++) {
        determinant += m->data[0][i] * getCofactor(m, 0, i);
    }
    return determinant;
}

Matrix* inverseMatrix(const Matrix *m) {
    float det = getDeterminant(m);
    // Non zero determinant means we can't invert.
    if floatEqual(det, 0.0) {
        return NULL;
    }
    Matrix *inverse = createMatrix();
    if (inverse == NULL) {
        return NULL;
    }
    for (int x = 0; x < MAT_SIZE - 1; x++) {
        for (int y = 0; y < MAT_SIZE - 1; y++) {
            float cofactor = getCofactor(m, x, y);
            inverse->data[y][x] = cofactor/det;
        }
    }
    return inverse;
}

void destroyMat3(Mat3 **m3) {
    free(*m3);
    *m3 = NULL;
}

void destroyMatrix(Matrix **m) {
    free(*m);
    *m = NULL;
}

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

static float getDeterminantMat3(const float mat2[3][3]) {
    return (mat2[0][0] * mat2[1][1] * mat2[2][2]) + (mat2[0][1] * mat2[1][2] * mat2[2][0]) + 
           (mat2[0][2] * mat2[1][0] * mat2[2][1]) - (mat2[0][0] * mat2[1][2] * mat2[2][1]) - 
           (mat2[0][1] * mat2[1][0] * mat2[2][2]) - (mat2[0][2] * mat2[1][1] * mat2[2][0]) ;
}

/*Helper function for producing a sub matrix of size 3x3. Result is passed via input param 
sub_matrix*/
static void getSubMatrix(const Matrix *m, int row, int column, float sub_matrix[3][3])  {

    int sub_row, sub_col;
    for (int x = 0; x < 3; x++) {
        sub_row = (x < row) ? x: x + 1;
        for (int y = 0; y < 3; y++) {
            sub_col = (y < column) ? y: y + 1;
            sub_matrix[x][y] = m->data[sub_row][sub_col];
        }
    }
}

float getDeterminant(const Matrix *m) {
    float determinant = 0.0;
    float sign = 1.0;
    for (int i = 0; i < MAT_SIZE; i++) {
        sign = ((i + 1) % 2 == 0) ? -1.0 : 1.0;
        float sub_mat[3][3];
        getSubMatrix(m, 0, i, sub_mat);
        determinant += sign * m->data[0][i] * getDeterminantMat3(sub_mat);
    }
    return determinant;
}

void destroyMatrix(Matrix **m) {
    free(*m);
    *m = NULL;
}

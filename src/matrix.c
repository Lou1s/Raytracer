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

Tuple matTupleMult(const Matrix *m, Tuple t) {
    Tuple result = {0.0, 0.0, 0.0, 0.0};
    for (int i = 0; i < MAT_SIZE; i++) {
        for (int y = 0; y < MAT_SIZE; y++) {
            *getTupleValByIndex(&result, i) += m->data[i][y] * (*getTupleValByIndex(&t, y));
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
    for (int x = 0; x < MAT_SIZE; x++) {
        for (int y = 0; y < MAT_SIZE; y++) {
            float cofactor = getCofactor(m, x, y);
            inverse->data[y][x] = cofactor/det;
        }
    }
    return inverse;
}

void printMatrix(const Matrix *m) {
    printf("[");
    for (int x = 0; x < MAT_SIZE; x++) {
        for (int y = 0; y < MAT_SIZE; y++) {
            printf("%f", m->data[x][y]);
            if (y < MAT_SIZE - 1) {
                printf(" ");
        }
        }
        if (x < MAT_SIZE - 1) {
            printf("\n");
        }
    }
    printf("]\n");
}

Matrix* getTranslationMat(const float x, const float y, const float z) {
    Matrix *transform = getIdentityMatrix();
    if (transform == NULL) {
        return NULL;
    }

    transform->data[0][3] = x;
    transform->data[1][3] = y;
    transform->data[2][3] = z;
    return transform;
}

Matrix* getScaleMat(const float x, const float y, const float z) {
    Matrix *transform = getIdentityMatrix();
    if (transform == NULL) {
        return NULL;
    }

    transform->data[0][0] = x;
    transform->data[1][1] = y;
    transform->data[2][2] = z;
    return transform;
}

Matrix* getRotationXMat(const float rot) {
    Matrix *rot_mat = getIdentityMatrix();
    if (rot_mat == NULL) {
        return NULL;
    }

    rot_mat->data[1][1] = cos(rot);
    rot_mat->data[1][2] = -sin(rot);
    rot_mat->data[2][1] = sin(rot);
    rot_mat->data[2][2] = cos(rot);

    return rot_mat;
}

Matrix* getRotationYMat(const float rot) {
    Matrix *rot_mat = getIdentityMatrix();
    if (rot_mat == NULL) {
        return NULL;
    }

    rot_mat->data[0][0] = cos(rot);
    rot_mat->data[0][2] = sin(rot);
    rot_mat->data[2][0] = -sin(rot);
    rot_mat->data[2][2] = cos(rot);

    return rot_mat;
}

Matrix* getRotationZMat(const float rot) {
    Matrix *rot_mat = getIdentityMatrix();
    if (rot_mat == NULL) {
        return NULL;
    }

    rot_mat->data[0][0] = cos(rot);
    rot_mat->data[0][1] = -sin(rot);
    rot_mat->data[1][0] = sin(rot);
    rot_mat->data[1][1] = cos(rot);

    return rot_mat;
}

Matrix* getShearMat(const float x_y, const float x_z, const float y_x, const float y_z, 
        const float z_x, const float z_y) {
    Matrix *shear_mat = getIdentityMatrix();
    if (shear_mat == NULL) {
        return NULL;
    }

    shear_mat->data[0][1] = x_y;
    shear_mat->data[0][2] = x_z;
    shear_mat->data[1][0] = y_x;
    shear_mat->data[1][2] = y_z;
    shear_mat->data[2][0] = z_x;
    shear_mat->data[2][1] = z_y;

    return shear_mat;
}

Tuple shear(Tuple t, const float x_y, const float x_z, const float y_x, const float y_z, 
        const float z_x, const float z_y) {
    Matrix *shear_mat = getShearMat(x_y, x_z, y_x, y_z, z_x, z_y);
    assert(shear_mat != NULL);
    Tuple sheared_t = matTupleMult(shear_mat, t);
    destroyMatrix(&shear_mat);
    
    return sheared_t;
}

Tuple translate(const Tuple t, const float x, const float y, const float z) {
    Matrix *translate_mat = getTranslationMat(x, y, z);
    assert(translate_mat != NULL);
    Tuple translated_t = matTupleMult(translate_mat, t);
    destroyMatrix(&translate_mat);
    return translated_t;
}

Tuple scale(const Tuple t, const float x, const float y, const float z) {
    Matrix *scale_mat = getScaleMat(x, y, z);
    assert(scale_mat != NULL);
    Tuple scale_t = matTupleMult(scale_mat, t);
    destroyMatrix(&scale_mat);
    return scale_t;
}

Tuple rotateX(const Tuple t, const float rot) {
    Matrix *rot_mat = getRotationXMat(rot);
    assert(rot_mat != NULL);
    Tuple rot_t = matTupleMult(rot_mat, t);
    destroyMatrix(&rot_mat);
    return rot_t;
}

Tuple rotateY(const Tuple t, const float rot) {
    Matrix *rot_mat = getRotationYMat(rot);
    assert(rot_mat != NULL);
    Tuple rot_t = matTupleMult(rot_mat, t);
    destroyMatrix(&rot_mat);
    return rot_t;
}

Tuple rotateZ(const Tuple t, const float rot) {
    Matrix *rot_mat = getRotationZMat(rot);
    assert(rot_mat != NULL);
    Tuple rot_t = matTupleMult(rot_mat, t);
    destroyMatrix(&rot_mat);
    return rot_t;
}

void destroyMat3(Mat3 **m3) {
    free(*m3);
    *m3 = NULL;
}

void destroyMatrix(Matrix **m) {
    free(*m);
    *m = NULL;
}

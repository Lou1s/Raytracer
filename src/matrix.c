#include <assert.h>
#include <math.h>
#include <stdlib.h>

#include "../include/matrix.h"
#include "../include/constants.h"
#include "tuple.h"


Matrix* createMatrix(const int rows, const int columns) {
    if (rows <= 0 || columns <= 0) {
        return NULL;
    }
    Matrix *m = malloc(sizeof(Matrix));
    if (m == NULL) {
        return NULL;
    }

    m->rows = rows;
    m-> columns = columns;
    // Allocate the matrix data, setting it all to 0;
    int size = rows * columns;
    m->data = calloc(size, size * sizeof(float));
    if (m->data == 0) {
        free(m);
        return NULL;
    }
    return m;
}

float* getMatrixCell(Matrix *m, int row, int column) {
    if (row >= m->rows || row < 0 || column >= m->columns || column < 0) {
        return NULL;
    }
    return &m->data[row*m->columns + column];
}

bool matricesEqual(Matrix *m1, Matrix *m2) {
    if (m1->rows != m2->rows || m1->columns != m2->columns) {
        return false;
    }
    for (int y = 0; y < m1->columns; y++) {
        for (int x = 0; x < m1->rows; x++) {
            if (fabs(*getMatrixCell(m1, x, y)) - fabs(*getMatrixCell(m2, x, y)) > EPSILON) {
                return false;
            }
        }
    }
    return true;
    
}

Matrix* multMatrix(Matrix *m1, Matrix *m2) {
    if (m1->columns != m2->rows) {
        return NULL;
    }

    Matrix *mult_result = createMatrix(m1->rows, m2->columns);
    for (int x = 0; x < m1->rows; x++) {
        for (int y = 0; y < m2->columns; y++) {
            *getMatrixCell(mult_result, x, y) = 0;
            for (int i = 0; i < m2->rows; i++) {
                *getMatrixCell(mult_result, x, y) += (*getMatrixCell(m1, x, i)) * 
                        (*getMatrixCell(m2, i, y));
            }
        }
    }
    return mult_result;
}

static Matrix* TupleToMat(Vector v) {
    Matrix *m = createMatrix(4, 1);
    if (m == NULL) {
        return NULL;
    }
    *getMatrixCell(m, 0, 0) = v.x;
    *getMatrixCell(m, 1, 0) = v.y;
    *getMatrixCell(m, 2, 0) = v.z;
    *getMatrixCell(m, 3, 0) = v.w;

    return m;
}

static Tuple matToTuple(Matrix *m) {
    assert(m->columns == 1 && m->rows == 4);
    Vector v = (Tuple) {*getMatrixCell(m, 0, 0), *getMatrixCell(m, 1, 0), *getMatrixCell(m, 2, 0), 
            *getMatrixCell(m, 3, 0)};
    return v;
}

Tuple matTupleMult(Matrix *m, const Tuple v) {
    /*Convert the vector to a 4x1 matrix and perform matrix mult.*/
    Matrix *mat_tup = TupleToMat(v);
    Matrix *mult_res = multMatrix(m, mat_tup);
    // TODO: ERROR CHECK RESULTS (matrix pointer != NULL)
    if (mult_res == NULL) {
        abort();
    }
    Tuple result = matToTuple(mult_res);
    destroyMatrix(&mat_tup);
    destroyMatrix(&mult_res);
    return result;    
}

Matrix* getIdentityMatrix(int size) {
    Matrix *identity_matrix = createMatrix(size, size);
    if (identity_matrix==NULL) {
        return NULL;
    }

    for (int x=0; x < size; x++) {
        for (int y=0; y < size; y++) {
            if (x==y){
                *getMatrixCell(identity_matrix, x, y) = 1.0;
            }
        }
    }
    return identity_matrix;
}

Matrix* transposeMatrix(Matrix *m) {
    Matrix *transpose_matrix = createMatrix(m->rows, m->columns);
    for (int x = 0; x < m->rows; x++) {
        for (int y = 0; y < m->columns; y++) {
            *getMatrixCell(transpose_matrix, y, x) = *getMatrixCell(m, x, y);
        }
    }
    return transpose_matrix;
}

void destroyMatrix(Matrix **m) {
    free((*m)->data);
    free(*m);
    *m = NULL;
}

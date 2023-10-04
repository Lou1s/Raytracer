#include <math.h>
#include <stdlib.h>

#include "../include/matrix.h"
#include "../include/constants.h"


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

void destroyMatrix(Matrix **m) {
    free((*m)->data);
    free(*m);
    *m = NULL;
}

#include <stdlib.h>

# include "../include/matrix.h"

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

void destroyMatrix(Matrix **m) {
    free((*m)->data);
    free(*m);
    *m = NULL;
}

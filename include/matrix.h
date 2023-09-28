# ifndef MATRIX_H
# define MATRIX_H

typedef struct Matrix{
    int rows;
    int columns;
    float *data;
} Matrix;

Matrix* createMatrix(const int rows, const int columns);

# endif

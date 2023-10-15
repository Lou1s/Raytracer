# ifndef MATRIX_H
# define MATRIX_H

typedef struct Matrix{
    int rows;
    int columns;
    float *data;
} Matrix;

Matrix* createMatrix(const int rows, const int columns);
float* getMatrixCell(Matrix *m, int row, int column);
bool matricesEqual(Matrix *m1, Matrix *m2);
Matrix* multMatrix(Matrix *m1, Matrix *m2);
void destroyMatrix(Matrix **m);


# endif

# ifndef MATRIX_H
# define MATRIX_H

#include "tuple.h"

#define MAT_SIZE 4

typedef struct Matrix{
    float data[MAT_SIZE][MAT_SIZE];
} Matrix;

/* Create a 4x4 matrix and return a pointer to it. Returns NULL if allocation failed*/
Matrix* createMatrix();
/* Compares each elment in m1 and m2, returns false if they are not equal*/
bool matricesEqual(const Matrix *m1, const Matrix *m2);
/* Matrix multiplication, in the order of m1 * m2 (this matters!)*/
Matrix* multMatrix(const Matrix *m1, const Matrix *m2);
/* Matrix vecotr mult, can be seen as a specific case of the multMatrix function*/
Tuple matTupleMult(const Matrix *m, Tuple v);

/* Returns a 4x4 identity matrix*/
Matrix* getIdentityMatrix();
/* Transposes a 4x4 matrix such that m[x][y] = m [y][x]*/
Matrix* transposeMatrix(const Matrix *m);
/* Returns the determinant of a 4x4 matrix*/
float getDeterminant(const Matrix *m);

void destroyMatrix(Matrix **m);


# endif

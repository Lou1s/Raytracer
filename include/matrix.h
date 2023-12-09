# ifndef MATRIX_H
# define MATRIX_H

#include "tuple.h"

#define MAT_SIZE 4
#define MAT3_SIZE 3 // Obvious but why not

typedef struct Matrix{
    float data[MAT_SIZE][MAT_SIZE];
} Matrix;

typedef struct Mat3{
    float data[MAT3_SIZE][MAT3_SIZE];
} Mat3;

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
/* Returns the inverse of the Matrix m*/
Matrix* inverseMatrix(const Matrix *m);
/*Free a Matrix struct*/
void destroyMatrix(Matrix **m);
/* Debug function for printing a *Matrix*/
void printMatrix(const Matrix *m);

/*Transforms*/
/*Translation Matrix*/
Matrix* getTranslationMat(const float x, const float y, const float z);
/*Scale Matrix*/
Matrix* getScaleMat(const float x, const float y, const float z);
/*Rotation around the X axis, in radians*/
Matrix* getRotationX(const float rot);
/*Rotation around the Y axis, in radians*/
Matrix* getRotationY(const float rot);
/*Rotation around the Z axis, in radians*/
Matrix* getRotationZ(const float rot);
/*Helper functions for all transforms that apply the transform then return the Tuple, without needing
to handle a matrix at all*/
/*Returns translated Tuple*/
Tuple translate(const Tuple t, const float x, const float y, const float z);
/* Returns a scaled Tuple*/
Tuple scale(const Tuple t, const float x, const float y, const float z);
/*Returun a tuple rotated around x by 'rot' radians*/
Tuple rotateX(const Tuple t, const float rot);
/*Returun a tuple rotated around y by 'rot' radians*/
Tuple rotateY(const Tuple t, const float rot);
/*Returun a tuple rotated around z by 'rot' radians*/
Tuple rotateZ(const Tuple t, const float rot);

/*Mat3 related functions*/
/*Returns a signed determinant of the submatrix made from the matrix m by ommitting the passed in row
and column.*/
float getCofactor(const Matrix *m, const int row, const int column);
/*Create a 3x3 Matrix*/
Mat3* createMat3();
/*Free a 3x3 Matrix*/
void destroyMat3(Mat3 **m3);

# endif

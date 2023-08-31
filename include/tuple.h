#ifndef TUPLE_H
#define TUPLE_H

#include <stdbool.h>
#include <math.h>

#define EPSILON 0.000001f

/* Generic Tuple data type, used as a basis for both vectors and points*/
typedef struct Tuple {
    float x,y,z,w;
 } Tuple, Vector, Point;

/* Constructors for vectors (Tuple) {x, y, z, 0.0} and points (Tuple) {x, y, z, 1.0}*/
Point point(const float x, const float y, const float z);
Vector vector(const float x, const float y, const float z);

/* Helper function(s) for debugging*/
void printTuple(const Tuple t);

/* General operations performed on two tuples tuples, all operations return a new completely new 
tuple. There is no in place operators. Note that functions will usually describe what kind of Tuple
should be passed in as input, i.e. dotprodVectors is only expecting vectors, whilst multTupleScalar
takes in a generic tuple e.g. a point or a vector. */
bool tuplesEqual(const Tuple a, const Tuple b);
Tuple addTuples(const Tuple a, const Tuple b);
Tuple negateTuple(const Tuple t);
Tuple subtractTuples(const Tuple a, const Tuple b);
Tuple multTupleScalar(const Tuple t, float s);
Tuple divideTupleScalar (const Tuple t, float s);
Vector crossProductVectors(const Vector a, const Vector b);
float dotProdVectors(const Vector a, Vector b);

/* Vector magnitute and normalise functions. Operates under the premise that the input is a vector 
i.e. the w component of the tuple is completely ignored. vectorNormalise also returns a vector, 
deliberately setting w to 0.0. */
float vectorMagnitude(const Vector v);
Vector vectorNormalise(const Vector v);

#endif

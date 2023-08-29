#ifndef TUPLE_H
#define TUPLE_H

#include <stdbool.h>
#include <math.h>

#define EPSILON 0.000001f

typedef struct Tuple {
    float x,y,z,w;
 } Tuple;

Tuple point(const float x, const float y, const float z);
Tuple vector(const float x, const float y, const float z);

void printTuple(const Tuple t);

bool tuplesEqual(const Tuple a, const Tuple b);
Tuple addTuples(const Tuple a, const Tuple b);
Tuple negateTuple(const Tuple t);
Tuple subtractTuples(const Tuple a, const Tuple b);
Tuple multTupleScalar(const Tuple t, float s);
Tuple divideTupleScalar (const Tuple t, float s);
float dotProdVectors(const Tuple a, Tuple b);

float vectorMagnitude(const Tuple v);
Tuple vectorNormalise(const Tuple v);

#endif

#include <stdio.h>
#include <math.h>

#include "../include/tuple.h"

Point point(const float x, const float y, const float z) {
    Point p = {x, y, z, 1.0f};
    return p;
}

Vector vector(const float x, const float y, const float z) {
    Vector v = {x, y, z, 0.0f};
    return v;
}

void printTuple(const Tuple t) {
    printf("(%f, %f, %f, %f)\n", t.x, t.y, t.z, t.w);
}

bool tuplesEqual(const Tuple a, const Tuple b) {
    return fabs(a.x - b.x) <= EPSILON && fabs(a.y - b.y) <= EPSILON && fabs(a.z - b.z) <= EPSILON && 
           fabs(a.w - b.w) <= EPSILON;
}

Tuple addTuples(const Tuple a, const Tuple b) {
    return (Tuple) {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

Tuple negateTuple(const Tuple t) {
    return (Tuple){-t.x, -t.y, -t.z, -t.w};
 
}

Tuple subtractTuples(const Tuple a, const Tuple b) {
    return addTuples(a, negateTuple(b));
}

Tuple multTupleScalar(const Tuple t, float s) {
    return (Tuple){t.x * s, t.y * s, t.z * s, t.w * s};
}

Tuple divideTupleScalar(const Tuple t, float s) {
    return multTupleScalar(t, 1.0/s);
}

float dotProdVectors(const Vector a, Vector b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float vectorMagnitude(const Vector v) {
    return sqrtf(v.x*v.x + v.y * v.y + v.z * v.z);
}

Vector vectorNormalise(const Vector v) {
    float mag = vectorMagnitude(v);
    return vector(v.x/mag, v.y/mag, v.z/mag);
}

Vector crossProductVectors(const Vector a, const Vector b) {
    return vector(a.y * b.z - a.z * b.y,
                  a.z * b.x - a.x * b.z,
                  a.x * b.y - a.y * b.x);
}

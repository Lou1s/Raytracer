#ifndef TUPLE_H
#define TUPLE_H

#include <stdbool.h>
#include <math.h>

#define EPSILON 0.000001f

typedef struct Tuple {
    float x,y,z,w;
 } Tuple;

static inline Tuple point(const float x, const float y, const float z) {
    Tuple p = {x, y, z, 1.0f};
    return p;
}

static inline Tuple vector(const float x, const float y, const float z) {
    Tuple v = {x, y, z, 0.0f};
    return v;
}

static inline bool tuplesEqual(Tuple a, Tuple b) {
    return fabs(a.x - b.x) <= EPSILON && fabs(a.y - b.y) <= EPSILON && fabs(a.z - b.z) <= EPSILON && 
           fabs(a.w - b.w) <= EPSILON;
}


#endif
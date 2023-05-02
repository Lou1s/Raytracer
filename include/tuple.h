#ifndef TUPLE_H
#define TUPLE_H

#include <stdbool.h>

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

static inline bool tupleEqual(Tuple a, Tuple b) {
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}


#endif
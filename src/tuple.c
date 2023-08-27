#include "../include/tuple.h"

Tuple point(const float x, const float y, const float z) {
    Tuple p = {x, y, z, 1.0f};
    return p;
}

Tuple vector(const float x, const float y, const float z) {
    Tuple v = {x, y, z, 0.0f};
    return v;
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

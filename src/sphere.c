#include "../include/sphere.h"
#include "tuple.h"
#include <stdlib.h>

static size_t ID = 0;

Sphere* initSphere() {
    Sphere *s = malloc(sizeof(Sphere));
    if (s == NULL) {
        return NULL;
    }
    s->id = ID++;
    s->origin = getPoint(0.0, 0.0, 0.0);
    return s;
}

void destroySphere(Sphere **s) {
    free(*s);
    *s = NULL;
}

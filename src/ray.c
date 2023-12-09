#include "ray.h"
#include <stdlib.h>
Ray* initRay() {
    Ray *ray = malloc(sizeof(Ray));
    if (ray == NULL) {
        return NULL;
    }

    ray->origin = getPoint(0.0, 0.0, 0.0);
    ray->direction = getVector(0.0, 0.0, 0.0);
    return ray;
}
Ray* getRay(const Point origin, const Vector direction) {
    Ray *ray = initRay();
    if (ray == NULL) {
        return NULL;
    }

    ray->origin = origin;
    ray->direction = direction;
    return ray;
}

void destroyRay(Ray **r) {
    free(*r);
    *r = NULL;
}

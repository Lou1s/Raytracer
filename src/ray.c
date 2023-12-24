#include "ray.h"
#include "tuple.h"
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
Point getRayPosition(const Ray *ray, float time) {
    // origin + direction * time
    return addTuples(ray->origin,  multTupleScalar(ray->direction, time));
}
void destroyRay(Ray **r) {
    free(*r);
    *r = NULL;
}

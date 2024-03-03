#include "ray.h"
#include "constants.h"
#include "tuple.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

static Intersections* getIntersections(const size_t count, const float locations[], const int ids[]) {
    Intersections *i = malloc(sizeof(Intersections));
    if (i==NULL) {
        return NULL;
    }

    i->data = malloc(count * sizeof(Intersection));
    if (i->data == NULL) {
        free(i);
        return NULL;
    }

    i->count = count;
    for (size_t ii = 0; ii < count; ii ++) {
        i->data[ii] = (Intersection) {.object=ids[ii], .t=locations[ii]};
    }
    return i;
}

static Intersections* initIntersections() {
    Intersections *i = malloc(sizeof(Intersections));
    if (i == NULL) {
        return NULL;
    }
    i->count = 0;
    return i;
}

Intersections* intersectsSphere(const Ray *r, const Sphere *s) {
    Vector sphere_to_ray =  subtractTuples(r->origin, s->origin);
    float a = dotProdVectors(r->direction, r->direction);
    float b = 2 * dotProdVectors(r->direction, sphere_to_ray);
    float c = dotProdVectors(sphere_to_ray, sphere_to_ray) - 1.0;

    float discriminant = b*b - 4.0 * a * c;

    if(discriminant < 0.0) {
        return initIntersections();
    }

    float t1 = ((-b - sqrtf(discriminant))/(2.0*a));
    float t2 = ((-b + sqrtf(discriminant))/(2.0*a));

    if (floatEqual(t1, t2)) {
        float loc[1] = {t1};
        int ids[1] = {s->id};
        return getIntersections(1, loc, ids);
    }

    int ids[2] = {s->id};
    float loc[2] = {t1, t2};
    return getIntersections(2, loc, ids);
}

void destroyIntersections(Intersections **Intersections) {
    free(*Intersections);
    *Intersections = NULL;
}

void destroyRay(Ray **r) {
    free(*r);
    *r = NULL;
}

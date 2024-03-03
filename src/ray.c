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

static Intersection* getIntersection(const size_t count, const float locations[], const int ids[]) {
    Intersection *i = malloc(sizeof(Intersection));
    if (i==NULL) {
        return NULL;
    }

    i->locations = malloc(count * sizeof(float));
    if (i->locations == NULL) {
        free(i);
        return NULL;
    }

    i->ids = malloc(count * sizeof(size_t));
    if (i->locations == NULL) {
        free(i->locations);
        free(i);
        return NULL;
    }

    i->count = count;
    memcpy(i->locations, locations, count * sizeof(float));
    memcpy(i->ids, ids, count * sizeof(float));
    return i;
}

static Intersection* initIntersection() {
    Intersection *i = malloc(sizeof(Intersection));
    if (i == NULL) {
        return NULL;
    }
    i->count = 0;
    return i;
}

Intersection* intersectsSphere(const Ray *r, const Sphere *s) {
    Vector sphere_to_ray =  subtractTuples(r->origin, s->origin);
    float a = dotProdVectors(r->direction, r->direction);
    float b = 2 * dotProdVectors(r->direction, sphere_to_ray);
    float c = dotProdVectors(sphere_to_ray, sphere_to_ray) - 1.0;

    float discriminant = b*b - 4.0 * a * c;

    if(discriminant < 0.0) {
        return initIntersection();
    }

    float t1 = ((-b - sqrtf(discriminant))/(2.0*a));
    float t2 = ((-b + sqrtf(discriminant))/(2.0*a));

    if (floatEqual(t1, t2)) {
        float loc[1] = {t1};
        int ids[1] = {s->id};
        return getIntersection(1, loc, ids);
    }

    int ids[2] = {s->id};
    float loc[2] = {t1, t2};
    return getIntersection(2, loc, ids);
}

void destroyIntersection(Intersection **intersection) {
    free(*intersection);
    *intersection = NULL;
}

void destroyRay(Ray **r) {
    free(*r);
    *r = NULL;
}

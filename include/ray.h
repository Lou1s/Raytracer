# ifndef RAY_H
# define RAY_H

#include "tuple.h"
#include "sphere.h"

typedef struct Ray {
    Point origin;
    Vector direction;
} Ray;
/*
Simple struct for holding intersection between a ray and a shape. locations lists all intersection
points in the form of the distance from the origin of the ray (along the direction). ids lists the
ids of the objects the ray hit in the order of locations.
*/
typedef struct Intersection {
    size_t count;
    float* locations;
    int* ids;
} Intersection;

/* Get a Ray with orition of (0,0,0) and a direction of (0,0,0)*/
Ray* initRay();
/* Returns a Ray with the supplied direction and origin*/
Ray* getRay(const Point origin, const Vector direction);
/* Get ray position at time t */
Point getRayPosition(const Ray *ray, float time);
/* Get all intersection points between a ray and a sphere*/
Intersection* intersectsSphere(const Ray *r, const Sphere *s);
/* Free an Intersection from memory*/
void destroyIntersection(Intersection **intersection);
/* Free a Ray from memory*/
void destroyRay(Ray **r);

#endif

# ifndef RAY_H
# define RAY_H

#include "tuple.h"
#include "sphere.h"

typedef struct Ray {
    Point origin;
    Vector direction;
} Ray;

// Simple struct for holding intersection between a ray and a shape. locations lists all intersection
// points in the form of distance from the origin of the ray used to compute the intersection.
typedef struct Intersection {
    size_t count;
    float locations[];
} Intersection;

/* Get a Ray with orition of (0,0,0) and a direction of (0,0,0)*/
Ray* initRay();
/* Returns a Ray with the supplied direction and origin*/
Ray* getRay(const Point origin, const Vector direction);
/* Get ray position at time t */
Point getRayPosition(const Ray *ray, float time);
/*Generate an intersection struct with the given size and location (t values on the ray) array*/
Intersection* getIntersection(const size_t count, const float locations[]);
/* Get all intersection points between a ray and a sphere*/
Intersection* intersectsSphere(const Ray *r, const Sphere *s);
/* Free an Intersection from memory*/
void destroyIntersection(Intersection **intersection);
/* Free a Ray from memory*/
void destroyRay(Ray **r);

#endif

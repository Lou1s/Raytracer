# ifndef RAY_H
# define RAY_H

#include "tuple.h"

typedef struct Ray {
    Point origin;
    Vector direction;
} Ray;

/* Get a Ray with orition of (0,0,0) and a direction of (0,0,0)*/
Ray* initRay();
/* Returns a Ray with the supplied direction and origin*/
Ray* getRay(const Point origin, const Vector direction);
/* Get ray position at time t */
Point getRayPosition(const Ray *ray, float time);
/* Free a Ray from memory*/
void destroyRay(Ray **r);

#endif

# ifndef RAY_H
# define RAY_H

#include "tuple.h"

typedef struct Ray {
    Point origin;
    Vector direction;
} Ray;

/*Get a Ray with orition of (0,0,0) and a direction of (0,0,0)*/
Ray* initRay();
/* Returns a Ray with the supplied direction and origin*/
Ray* getRay(const Point origin, const Vector direction);

#endif

#ifndef SPHERE_H
#define SPHERE_H

#include "tuple.h"
#include <stddef.h>

/*Simple sphere object with a unique id and origin*/
typedef struct Sphere {
    size_t id;
    Point origin;
} Sphere;

/* Returns a basic sphere with origin at (0, 0, 0) */
Sphere* initSphere();
/* Free a Sphere from memory */
void destroySphere(Sphere **s);

#endif

#ifndef COLOUR_H
#define COLOUR_H

#include "constants.h"

#include <stdbool.h>

/* Basic colour struct with rgb floats that should be between 0 and 1*/
typedef struct Colour {
    float red;
    float green;
    float blue;
} Colour;

/* Simple Colour operators */

Colour addColours(const Colour a, const Colour b);
Colour subtractColours(const Colour a, const Colour b);
Colour multColours(const Colour a, const Colour b);
bool coloursEqual(const Colour a, const Colour b);

#endif

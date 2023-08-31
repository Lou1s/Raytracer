#include "../include/colour.h"

#include <math.h>

bool coloursEqual(const Colour a, const Colour b) {
    return fabs(a.red - b.red) <= EPSILON && fabs(a.blue - b.blue) <= EPSILON && 
           fabs(a.green - b.green) <= EPSILON;
}

Colour addColours(const Colour a, const Colour b) {
    return (Colour) {a.red + b.red, a.green + b.green, a.blue + b.blue};
}
Colour subtractColours(const Colour a, const Colour b) {
    return (Colour) {a.red - b.red, a.green - b.green, a.blue - b.blue};
}
Colour multColours(const Colour a, const Colour b) {
    return (Colour) {a.red * b.red, a.green * b.green, a.blue * b.blue};
}

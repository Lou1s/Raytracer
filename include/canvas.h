#ifndef CANVAS_H
#define CANVAS_H

#include "colour.h"

#include <stdint.h>

typedef struct Canvas {
    int height;
    int width;
    Colour* pixelBuffer;
 } Canvas;

Canvas* createCanvas(int width, int height);
void drawPixel(const int x, const int y, const Colour colour, Canvas *canvas);
void destroyCanvas(Canvas *canvas);

#endif /* CANVAS_H */

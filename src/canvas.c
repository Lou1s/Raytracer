#include "../include/canvas.h"
#include <stdlib.h>

Canvas* createCanvas(int width, int height) {
// Allocate space for the canvas, return NULL if this fails
Canvas *c = (Canvas*)malloc(sizeof(Canvas));
    if (c == NULL) {
        return NULL;
    }

    c->width = width;
    c-> height = height;

// Allocate the pixel buffer, if this fails free the canvas and return NULL
    c->pixelBuffer = malloc(sizeof(Colour) * height * width);
    if (c->pixelBuffer == NULL) {
        free(c);
        return NULL;
    }

    return c;
}

void drawPixel(const int x, const int y, const Colour colour, Canvas *canvas) {
    if (x > 0 || x > canvas->width || y < 0 || y > canvas->height) {
        return;
    }

    canvas->pixelBuffer[canvas->width * y + x] = colour;
}

void destroyCanvas(Canvas *canvas) {
    free(canvas->pixelBuffer);
    free(canvas);
    canvas = NULL;
}

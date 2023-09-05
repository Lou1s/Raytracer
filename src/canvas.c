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
    c->pixel_buffer = malloc(sizeof(Colour) * height * width);
    if (c->pixel_buffer == NULL) {
        free(c);
        return NULL;
    }
    
    Colour black = {0.0, 0.0, 0.0};
    for (int i = 0; i < c->width * c->height; i++) {
        c->pixel_buffer[i] = black;
    }

    return c;
}

void drawPixel(const int x, const int y, const Colour colour, Canvas *canvas) {
    if (x < 0 || x >= canvas->width || y < 0 || y >= canvas->height) {
        return;
    }

    canvas->pixel_buffer[canvas->width * y + x] = colour;
}

Colour getPixel(const int x, const int y, Canvas *canvas) {
    return canvas->pixel_buffer[canvas->width * y + x];
}

void destroyCanvas(Canvas **canvas) {
    free((*canvas)->pixel_buffer);
    free(*canvas);
    *canvas = NULL;
}

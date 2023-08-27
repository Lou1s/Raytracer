#include "../include/canvas.h"
#include <stdlib.h>

 Canvas* createCanvas(int width, int height) {
    // allocate space for the canvas, including the pixel buffer
    Canvas *c = (Canvas*)malloc(sizeof(Canvas));
    if (c == NULL) {
      return NULL;
    }
    c->width = width;
    c-> height = height;

    c->pixelBuffer = (uint32_t*) malloc(sizeof(uint32_t) * height * width);
    if (c->pixelBuffer == NULL) {
      free(c);
      return NULL;
    }

    return c;

 }

 void drawPixel(int x, int y, uint32_t colour, Canvas *canvas) {
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
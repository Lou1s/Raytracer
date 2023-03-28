#include "../include/canvas.h"
#include <stdlib.h>

 Canvas* createCanvas(int width, int height) {
    // allocate space for the canvas, including the pixel buffer
    Canvas *c = (Canvas*)malloc(sizeof(Canvas) + sizeof(uint32_t) * height * width);
    c->height = height;
    c-> height = height;
    c->pixelBuffer = (uint32_t*) malloc(sizeof(uint32_t) * height * width);
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
 }
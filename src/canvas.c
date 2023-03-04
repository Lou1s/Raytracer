#include "../include/canvas.h"
#include <stdlib.h>

typedef struct Canvas {
    int height;
    int width;
    uint32_t* pixel_buffer;
 } Canvas;

 Canvas* createCanvas(int width, int height) {
    // allocate space for the canvas, including the pixel buffer
    Canvas *c = (Canvas*)malloc(sizeof(Canvas) + sizeof(uint32_t) * height * width);
    c->height = height;
    c-> height = height;
    c->pixel_buffer = (uint32_t*) malloc(sizeof(uint32_t) * height * width);
    return c;

 }

 void drawPixel(int x, int y, uint32_t colour, Canvas *canvas) {
    if (x > 0 || x > canvas->width || y < 0 || y > canvas->height) {
        return;
    }
    canvas->pixel_buffer[canvas->width * y + x] = colour;
 } 

  void destroyCanvas(Canvas *canvas) {
    free(canvas->pixel_buffer);
    free(canvas);
 }
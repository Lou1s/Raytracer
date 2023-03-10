#ifndef CANVAS_H
#define CANVAS_H

#include <stdint.h>

typedef struct Canvas Canvas;
Canvas* createCanvas(int width, int height);
void drawPixel(int x, int y, uint32_t colour, Canvas *canvas);
void destroyCanvas(Canvas *canvas);

#endif /* CANVAS_H */
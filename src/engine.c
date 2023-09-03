#include "../include/engine.h"
#include "canvas.h"
#include "colour.h"

#include <stdbool.h>
#include <stdio.h>

static Canvas *canvas;

void engineInit(int width, int height) {
    printf("engineInit\n");
    canvas = createCanvas(width, height);
}

void engineMainLoop() {
    Canvas *c = createCanvas(10, 20);
    Colour col = {.5, .5, .5};
    drawPixel(2, 1, col, c);
    printColour(getPixel(2, 1, c));
    for( int x = 0; x < c->width; x++) {
        for ( int y = 0; y < c->height; y++) {
            Colour p = getPixel(x, y, c);
            printf("x: %d, y: %d \n", x, y);
            printColour(p);
            if (!coloursEqual((Colour) {0.0, 0.0, 0.0}, p)) {
                printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1");
            }
        }
    }
    destroyCanvas(c);
}


void engineDestroy() {
    destroyCanvas(canvas);
}

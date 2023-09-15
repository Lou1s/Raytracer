#include "../include/engine.h"
#include "canvas.h"
#include "colour.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static Canvas *canvas;

void engineInit(int width, int height) {
    canvas = createCanvas(width, height);
}

void engineMainLoop() {
    printf("MAINLOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOP\n");
    Canvas *c = createCanvas(5, 3);
    Colour c1 = (Colour) {1.5, 0.0, 0.0};
    Colour c2 = (Colour) {0.0, 0.5, 0.0};
    Colour c3 = (Colour) {-0.5, 0.0, 1.0};

    drawPixel(0, 0, c1, c);
    drawPixel(2,1, c2, c);
    drawPixel(4,2, c3, c);

    char *canv_to_ppm = canvasToPpm(c);
    if (canv_to_ppm == NULL) {
        printf("NULL SAD");
    }
    destroyCanvas(&c);
    
}


void engineDestroy() {
    destroyCanvas(&canvas);
}

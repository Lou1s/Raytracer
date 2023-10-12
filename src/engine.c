#include "../include/engine.h"
#include "canvas.h"
#include "colour.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static Canvas *canvas;

int engineInit(int width, int height) {
    canvas = createCanvas(width, height);
    if (canvas == NULL) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int engineMainLoop() {
     return EXIT_SUCCESS;
}


void engineDestroy() {
    destroyCanvas(&canvas);
}

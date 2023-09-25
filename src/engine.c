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

    
}


void engineDestroy() {
    destroyCanvas(&canvas);
}

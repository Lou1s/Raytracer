#include "../include/engine.h"


#include <stdbool.h>
#include <stdio.h>

static Canvas *canvas;

void engineInit(int width, int height) {
    printf("engineInit\n");
    canvas = createCanvas(width, height);
}

void engineMainLoop() {

}


void engineDestroy() {
    destroyCanvas(canvas);
}

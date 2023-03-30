#include <stdbool.h>
#include <stdio.h>

#include "../include/engine.h"

void engineInit(int width, int height) {
    printf("engineInit\n");

    canvas = createCanvas(width, height);
}

void engineMainLoop() {

}


void engineDestroy() {
    destroyCanvas(canvas);
}
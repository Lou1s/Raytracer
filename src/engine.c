#include <stdbool.h>

#include "../include/engine.h"

void engineInit(int width, int height) {
    printf("engineInit\n");
    initDisplay();
    canvas = createCanvas(width, height);
}

void engineMainLoop() {
    while (!shouldDisplayClose()) {
        //raytrace(canvas)
        // display(canvas)
        glfwPollEvents();
    }
}


void engineDestroy() {
    destroyCanvas(canvas);
    destroyDisplay();
}
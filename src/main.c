
#include <stdio.h>
#include "../include/engine.h"

int main() {
    printf("main loop\n");
    engineInit(1920, 1080);
    engineMainLoop();
    engineDestroy();
    return 0;
}

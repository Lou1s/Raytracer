
#include <stdio.h>
#include <stdlib.h>
#include "../include/engine.h"

int main() {
    printf("main loop\n");
    // Init the engine and return if false
    if (engineInit(1920, 1080)) {
        return EXIT_FAILURE;
    }
    // EXIT_SUCCESS OR EXIT_FAILURE, saving in varialbe So that we cna return it after engineDestroy 
    // is run.
    int main_loop_exit_status = engineMainLoop();
    engineDestroy();
    return main_loop_exit_status;
}

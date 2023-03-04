#include "../include/display.h"
#define NK_IMPLEMENTATION
#include "../external/nuklear.h"

#include "GLFW/glfw3.h"
#include <X11/Xlib.h>


Bool initDisplay() {
    printf("initDisplay\n");
    if (!glfwInit()) {
        printf("GLFW failed to initialise.\n");
        return False;
    }
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    GLFWmonitor *mon = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(mon);
    screenWidth = mode->width;
    screenHeight = mode->height;

    window = glfwCreateWindow(screenWidth, screenHeight, "Raytracer", mon, NULL);

    glfwSetWindowSizeCallback(window, windowSizeChangedCallback);
    glfwSetKeyCallback(window, keyCallback);

    glfwMakeContextCurrent(window);

    if (!window) {
        printf("GLFWwindow failed to initialise.\n");
        glfwTerminate();
        return False;
    }
   
    return True;
}
Bool shouldDisplayClose() {
    if (!window) {
        printf("No window, closing");
        return False;
    }
    return glfwWindowShouldClose(window);
}
// callbacks
void windowSizeChangedCallback(GLFWwindow* window, int width, int height) {
    //do nthing for now, later on we will have to modify this to change the texture and canvas
}

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}


void destroyDisplay() {
    glfwTerminate();
}

#include "../include/display.h"
#include "../include/canvas.h"
#include <GL/gl.h>
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
    // Window stuff, get monitor size then create a window using that size (fullscreen)
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    GLFWmonitor *mon = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(mon);
    screenWidth = mode->width;
    screenHeight = mode->height;

    window = glfwCreateWindow(screenWidth, screenHeight, "Raytracer", mon, NULL);

    // Input/key callback
    glfwSetWindowSizeCallback(window, windowSizeChangedCallback);
    glfwSetKeyCallback(window, keyCallback);

    // Setup the texture we will draw to
    // need to look at gltexStorage2D
    glGenTextures(1, &textureHandle);
    glBindTexture(GL_TEXTURE_2D, textureHandle);
    // Do we want a different height/width here than the screen height? So we can render 
    // out different resolutions eventually    
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
    //do nothing for now, later on we will have to modify this to change the texture and canvas
}

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void drawCanvas(Canvas *canvas) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, canvas->width, canvas->height, 0, GL_RGB, GL_UNSIGNED_BYTE, 
                 canvas->pixelBuffer);
    glEnable(GL_TEXTURE_2D);

    

}


void destroyDisplay() {
    glfwTerminate();
}

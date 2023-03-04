#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdbool.h>

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <X11/Xlib.h>

#include "canvas.h"

Bool initDisplay();
void windowSizeChangedCallback(GLFWwindow* window, int width, int height);
Bool shouldDisplayClose();
void destroyDisplay();
static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

static GLFWwindow *window;
static int screenWidth;
static int screenHeight;



// i'd say the texture goes here too

#endif /* DISPLAY_H */

#ifndef ENGINE_H
#define ENGINE_H

#include "display.h"
#include "canvas.h"
#include <stdbool.h>

static Canvas *canvas;

void engineInit(int width, int height);
void engineMainLoop();
void engineDestroy();

#endif /* ENGINE_H */
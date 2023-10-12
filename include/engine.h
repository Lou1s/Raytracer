#ifndef ENGINE_H
#define ENGINE_H

#include "canvas.h"
#include <stdbool.h>

int engineInit(int width, int height);
int engineMainLoop();
void engineDestroy();

#endif /* ENGINE_H */

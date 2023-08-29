#ifndef ENGINE_H
#define ENGINE_H

#include "canvas.h"
#include <stdbool.h>

void engineInit(int width, int height);
void engineMainLoop();
void engineDestroy();

#endif /* ENGINE_H */

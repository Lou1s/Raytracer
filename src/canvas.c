#include "../include/canvas.h"

#include <stdio.h>
#include <stdlib.h>

# define MAX_COL_VAL 255
# define PPM_TYPE "P3"

Canvas* createCanvas(int width, int height) {
// Allocate space for the canvas, return NULL if this fails
Canvas *c = (Canvas*)malloc(sizeof(Canvas));
    if (c == NULL) {
        return NULL;
    }

    c->width = width;
    c-> height = height;

// Allocate the pixel buffer, if this fails free the canvas and return NULL
    c->pixel_buffer = malloc(sizeof(Colour) * height * width);
    if (c->pixel_buffer == NULL) {
        free(c);
        return NULL;
    }
    
    Colour black = {0.0, 0.0, 0.0};
    for (int i = 0; i < c->width * c->height; i++) {
        c->pixel_buffer[i] = black;
    }

    return c;
}

void drawPixel(const int x, const int y, const Colour colour, Canvas *canvas) {
    if (x < 0 || x >= canvas->width || y < 0 || y >= canvas->height) {
        return;
    }

    canvas->pixel_buffer[canvas->width * y + x] = colour;
}

Colour getPixel(const int x, const int y, Canvas *canvas) {
    return canvas->pixel_buffer[canvas->width * y + x];
}

char* canvasToPpm(Canvas *c) {
    char header[] = "%s\n%d %d\n%d\n";
    // Get header size
    size_t header_size = sizeof(char) * snprintf(NULL, 0, header, PPM_TYPE, c->width, c->height, 
            MAX_COL_VAL);
    // For each r,g and b component of a colour we will need 4 chars (3 numbers and 1 space).
    // There's three of these per colour and we will have width * height amount of colours so
    // We should allocate a buffer of 3 * 4 * width * height chars
    // TODO: get the amount of digits in MAC_COL_VAL and use this + 1 instead of hardcoded 3 value
    size_t buffer_size =  header_size + sizeof(char) * 4 * 3 * c->width * c->height;
    
    // Alocate the char buffer to hold the ppm contents
    char *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        return NULL;
    }
    buffer += snprintf(buffer, header_size, header, PPM_TYPE, c->width, c->height, MAX_COL_VAL);
    for (int y = 0; y < c->height; y++) {
        for (int x = 0; x < c->width; x++) {
            Colour col = getPixel(x, y, c);
            int r = (int) col.red * MAX_COL_VAL;
            int g = (int) col.green * MAX_COL_VAL;
            int b = (int) col.blue * MAX_COL_VAL;
            
            int col_ptr_size = sprintf(buffer, "%d, %d, %d", r, g, b);
            if(col_ptr_size == -1) {
                return NULL;
            }

            buffer += col_ptr_size;
            if (x == c->width - 1) {
                int newline_ptr_size = sprintf(buffer, "\n");
                if (newline_ptr_size == -1) {
                    return NULL;
                }
                buffer += newline_ptr_size;

            }
        }
    }
    return buffer;
}

bool ppmToFile(char *path, char *content) {

}


void destroyCanvas(Canvas **canvas) {
    free((*canvas)->pixel_buffer);
    free(*canvas);
    *canvas = NULL;
}

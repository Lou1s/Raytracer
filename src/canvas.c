#include "../include/canvas.h"
#include "colour.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// PPM Constants
# define MAX_COL_VAL 255
# define MAX_COLOUR_SIZE (int) floor(log10(MAX_COL_VAL)) + 1 // Should this be a macro?
# define MAX_PPM_LINE 70
# define PPM_TYPE "P3"

Canvas* createCanvas(int width, int height) {
// Allocate space for the canvas, return NULL if this fails
Canvas *c = malloc(sizeof(Canvas));
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
        printf("Draw pixel failed\n");
        return;
    }

    canvas->pixel_buffer[canvas->width * y + x] = colour;
}

Colour getPixel(const int x, const int y, Canvas *canvas) {
    return canvas->pixel_buffer[canvas->width * y + x];
}

static float clamp(const float val, const float min, const float max){
    if (val > max) {
        return max;
    }

    else if (val < min) {
        return min;
    }

    else {
        return val;
    }
}

char* canvasToPpm(Canvas *c) {
    char header[] = "%s\n%d %d\n%d\n";
    // Get header size
    size_t header_size = sizeof(char) * snprintf(NULL, 0, header, PPM_TYPE, c->width, c->height, 
            MAX_COL_VAL);
    // For each r,g and b component of a colour we will need MAX_COLOUR_SIZE + 1 chars.
    // There's three of these per colour and we will have width * height amount of colours so
    // We should allocate a buffer of 3 * 4 * width * height chars

    size_t buffer_size =  header_size + sizeof(char) * (MAX_COLOUR_SIZE + 1) * 3 * c->width * c->height + 1;
    // Alocate the char buffer to hold the ppm contents
    char *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        return NULL;
    }

    char *buffer_ptr = buffer + sprintf(buffer, header, PPM_TYPE, c->width, c->height, MAX_COL_VAL);
    for (int y = 0; y < c->height; y++) {
        int line_size = 0;
        for (int x = 0; x < c->width; x++) {
            Colour col = getPixel(x, y, c);
            // Add each R, G, B value individually to see if we have exceeded the max line limit
            for (int i = 0; i < 3; i++) {
                char col_val_buff[MAX_COLOUR_SIZE + 1];
                float col_val = getRGBByIndex(col, i);
                int ppm_col_val = round(clamp(col_val * MAX_COL_VAL, 0.0, (float) MAX_COL_VAL));
                
                int col_val_size = sprintf(col_val_buff, "%d", ppm_col_val);
                if (col_val_size == -1) {
                    return NULL;
                }
                // Add a newline if we hit the max line size allowed
                if (line_size + col_val_size >= MAX_PPM_LINE) {
                    line_size = 0;
                    *buffer_ptr++ = '\n';
                }
                // If we're not at the start of a newline then add a space
                else if (!(*(buffer_ptr -1) == '\n')) {
                    line_size += 1;
                    *buffer_ptr++ = ' ';
                }

                int col_val_to_buffer_size = sprintf(buffer_ptr, "%s", col_val_buff);
                if (col_val_to_buffer_size == -1) {
                    return NULL;
                }
                buffer_ptr += col_val_to_buffer_size;
                line_size += col_val_to_buffer_size;
            }
        }
        // Add a newline at the end of the row
        *buffer_ptr++ = '\n';
    }
    *buffer_ptr = '\0';
    return buffer;
}

bool savePPMToFile(const char file_path[], char *ppm_contents) {
    FILE *fp = fopen(file_path, "w");
    if (fp == NULL) {
        return false;
    }

    int write_results = fputs(ppm_contents, fp);
    fclose(fp);
    if (write_results == EOF) {
        return false;
    }
    
    return true;
}

void destroyCanvas(Canvas **canvas) {
    free((*canvas)->pixel_buffer);
    free(*canvas);
    *canvas = NULL;
}


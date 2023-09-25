#include "../include/canvas.h"
#include "../include/colour.h"

#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>

void createCanvasTest( void **state) {
    (void) state; /* unused */

    Canvas *c = createCanvas(10, 20);
    assert_non_null(c);
    assert_non_null(c->pixel_buffer);
    assert_int_equal(c->width, 10);
    assert_int_equal(c->height, 20);
    // Test all Colours are black
    for (int i = 0; i < c->height * c->width; i++) {
        Colour black = {0.0, 0.0, 0.0};
        assert_true(coloursEqual(black, c->pixel_buffer[i]));
    }
    destroyCanvas(&c);
}

void drawPixelGetPixelTest(void **state) {
    (void) state; /* unused */

    Canvas *c = createCanvas(10, 20);
    Colour col = {.5, .5, .5};
    drawPixel(2, 1, col, c);
    assert_true(coloursEqual(col, c->pixel_buffer[c->width * 1 + 2]));
    assert_true(coloursEqual(c->pixel_buffer[c->width * 1 + 2], getPixel(2, 1, c)));
    destroyCanvas(&c);
}

void destroyCanvasTest( void **state) {
    (void) state; /* unused */

    Canvas *c = createCanvas(10, 20);
    destroyCanvas(&c);
    assert_null(c);
}

void canvasToPpmTest(void **state) {
    (void) state; /* unused */
    
    const char *ppm = "P3\n"
                      "5 3\n"
                      "255\n"
                      "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
                      "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
                      "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";

    Canvas *c = createCanvas(5, 3);
    Colour c1 = (Colour) {1.5, 0.0, 0.0};
    Colour c2 = (Colour) {0.0, 0.5, 0.0};
    Colour c3 = (Colour) {-0.5, 0.0, 1.0};

    drawPixel(0, 0, c1, c);
    drawPixel(2,1, c2, c);
    drawPixel(4,2, c3, c);

    char *canv_to_ppm = canvasToPpm(c);
    assert_string_equal(canv_to_ppm, ppm);

    destroyCanvas(&c);
    free(canv_to_ppm);
}

void ppmLineLengthTest(void **state) {
    (void) state; /* unused */

    const char *ppm = "P3\n"
                      "10 2\n"
                      "255\n"
                      "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
                      "153 255 204 153 255 204 153 255 204 153 255 204 153\n"
                      "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
                      "153 255 204 153 255 204 153 255 204 153 255 204 153\n";
    
    Colour col = (Colour) {1, 0.8, 0.6};
    Canvas *c = createCanvas(10, 2);
    for (int y = 0; y < c->height; y++) {
        for (int x = 0; x < c->width; x++) {
            drawPixel(x, y, col, c);
        }
    }
    char *canv_to_ppm = canvasToPpm(c);
    assert_string_equal(canv_to_ppm, ppm);
    destroyCanvas(&c);
    free(canv_to_ppm);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(createCanvasTest),
        cmocka_unit_test(drawPixelGetPixelTest),
        cmocka_unit_test(destroyCanvasTest),
        cmocka_unit_test(canvasToPpmTest),
        cmocka_unit_test(ppmLineLengthTest)

    };
    return cmocka_run_group_tests_name("canvasTest", tests, NULL, NULL);
}


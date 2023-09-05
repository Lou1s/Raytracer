#include "../include/canvas.h"
#include "../include/colour.h"

#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

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

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(createCanvasTest),
        cmocka_unit_test(drawPixelGetPixelTest),
        cmocka_unit_test(destroyCanvasTest)

    };
    return cmocka_run_group_tests_name("canvasTest", tests, NULL, NULL);
}

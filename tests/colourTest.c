#include "../include/colour.h"

#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

void coloursEqualTest(void **state) {
    (void) state; /* unused */
    Colour a = (Colour) {0.9, 0.6, 0.75};
    Colour b = (Colour) {0.7, 0.1, 0.25};

    assert_false(coloursEqual(a,b));
    Colour c = (Colour) {0.9, 0.6, 0.75};
    assert_true(coloursEqual(a,c));

}

void addColoursTest(void **state) {
    (void) state; /* unused */

    Colour a = (Colour) {0.9, 0.6, 0.75};
    Colour b = (Colour) {0.7, 0.1, 0.25};
    Colour result = (Colour) {1.6, 0.7, 1.0};
    assert_true(coloursEqual(addColours(a,b), result));
}

void subtractColoursTest(void **state) {
    (void) state; /* unused */

    Colour a = (Colour) {0.9, 0.6, 0.75};
    Colour b = (Colour) {0.7, 0.1, 0.25};
    Colour result = (Colour) {0.2, 0.5, 0.5};
    assert_true(coloursEqual(subtractColours(a,b), result));
}

void multColoursTest(void **state) {
    (void) state; /* unused */

    Colour a = (Colour) {0.9, 0.6, 0.75};
    Colour b = (Colour) {0.7, 0.1, 0.25};
    Colour result = (Colour) {0.63, 0.06, 0.1875};
    assert_true(coloursEqual(multColours(a,b), result));
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(coloursEqualTest),
        cmocka_unit_test(addColoursTest),
        cmocka_unit_test(subtractColoursTest),
        cmocka_unit_test(multColoursTest)
    };
    return cmocka_run_group_tests_name("ColourTest", tests, NULL, NULL);
}

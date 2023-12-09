#include "ray.h"

#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>

void createRayTest( void **state) {
    (void) state; /* unused */

}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(createRayTest),
    };
    return cmocka_run_group_tests_name("rayTests", tests, NULL, NULL);
}

#include "sphere.h"
#include "tuple.h"

#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>

void createDestroySphereTest(void **state) {
    (void) state; /* unused */


}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(createDestroySphereTest),
    };
    return cmocka_run_group_tests_name("sphereTests", tests, NULL, NULL);
}

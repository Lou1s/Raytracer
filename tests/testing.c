#include "../include/vector.h"
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static void testing1234(void **state) {
    assert_int_equal(7, 5);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(testing1234),
    };
    return cmocka_run_group_tests_name("Success_test", tests, NULL, NULL);
}
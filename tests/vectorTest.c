#include "../include/vector.h"
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static void test_internal(void **state) {
    assert_int_equal(6, 5);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_internal),
    };
    return cmocka_run_group_tests_name("Success_test", tests, NULL, NULL);
}
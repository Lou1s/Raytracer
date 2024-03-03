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
    Sphere *s = initSphere();
    Sphere *ss = initSphere();
    
    assert_int_equal(s->id, 0);
    assert_int_equal(ss->id, 1);
    assert_true(tuplesEqual(getPoint(0,0,0), s->origin));
    assert_true(tuplesEqual(getPoint(0,0,0), ss->origin));

    destroySphere(&s);
    destroySphere(&ss);
    assert_null(s);
    assert_null(ss);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(createDestroySphereTest),
    };
    return cmocka_run_group_tests_name("sphereTests", tests, NULL, NULL);
}

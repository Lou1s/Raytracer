#include "ray.h"
#include "tuple.h"

#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>

void createDestroyRayTest(void **state) {
    (void) state; /* unused */

    Ray *ray = initRay();
    assert_true(tuplesEqual(ray->origin, getPoint(0.0, 0.0, 0.0)));
    assert_true(tuplesEqual(ray->direction, getVector(0.0, 0.0, 0.0)));
    destroyRay(&ray);
    assert_null(ray);

    ray = getRay(getPoint(1, 2, 3), getVector(4, 5, 6));
    assert_true(tuplesEqual(ray->origin, getPoint(1.0, 2.0, 3.0)));
    assert_true(tuplesEqual(ray->direction, getVector(4.0, 5.0, 6.0)));
    destroyRay(&ray);
    assert_null(ray);
}

void testRayPosition(void **state) {
    (void) state; /* unused */

    Ray *ray = getRay(getPoint(2,3,4), getVector(1, 0, 0));
    assert_true(tuplesEqual(getRayPosition(ray,0), getPoint(2,3,4)));
    assert_true(tuplesEqual(getRayPosition(ray,1), getPoint(3,3,4)));
    assert_true(tuplesEqual(getRayPosition(ray,-1), getPoint(1,3,4)));
    assert_true(tuplesEqual(getRayPosition(ray,2.5), getPoint(4.5,3,4)));

}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(createDestroyRayTest),
        cmocka_unit_test(testRayPosition)
    };
    return cmocka_run_group_tests_name("rayTests", tests, NULL, NULL);
}

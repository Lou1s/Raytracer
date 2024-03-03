#include "ray.h"
#include "constants.h"
#include "sphere.h"
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

void testIntersectionSphere1(void **state) {
    (void) state; /* unused */

    Ray *r = getRay(getPoint(0,0,-5), getVector(0,0,1));
    Sphere *s = initSphere();

    Intersection *i = intersectsSphere(r, s);
    assert_int_equal(i->count, 2);
    assert_float_equal(i->locations[0], 4.0, EPSILON);
    assert_float_equal(i->locations[1], 6.0, EPSILON);

    destroyRay(&r);
    destroySphere(&s);
    destroyIntersection(&i);
}

void testIntersectionSphere2(void **state) {
    (void) state; /* unused */

    Ray *r = getRay(getPoint(0,1,-5), getVector(0,0,1));
    Sphere *s = initSphere();

    Intersection *i = intersectsSphere(r, s);
    assert_int_equal(i->count, 1);
    assert_float_equal(i->locations[0], 5.0, EPSILON);

    destroyRay(&r);
    destroySphere(&s);
    destroyIntersection(&i);
}

void testIntersectionSphere3(void **state) {
    (void) state; /* unused */

    Ray *r = getRay(getPoint(0,2,-5), getVector(0,0,1));
    Sphere *s = initSphere();

    Intersection *i = intersectsSphere(r, s);
    assert_int_equal(i->count, 0);

    destroyRay(&r);
    destroySphere(&s);
    destroyIntersection(&i);
}

void testIntersectionSphere4(void **state) {
    (void) state; /* unused */

    Ray *r = getRay(getPoint(0,0,0), getVector(0,0,1));
    Sphere *s = initSphere();

    Intersection *i = intersectsSphere(r, s);
    assert_int_equal(i->count, 2);
    assert_float_equal(i->locations[0], -1.0, EPSILON);
    assert_float_equal(i->locations[1], 1.0, EPSILON);

    destroyRay(&r);
    destroySphere(&s);
    destroyIntersection(&i);
}

void testIntersectionSphere5(void **state) {
    (void) state; /* unused */

    Ray *r = getRay(getPoint(0,0,5), getVector(0,0,1));
    Sphere *s = initSphere();

    Intersection *i = intersectsSphere(r, s);
    assert_int_equal(i->count, 2);
    assert_float_equal(i->locations[0], -6.0, EPSILON);
    assert_float_equal(i->locations[1], -4.0, EPSILON);
    
    destroyRay(&r);
    destroySphere(&s);
    destroyIntersection(&i);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(createDestroyRayTest),
        cmocka_unit_test(testRayPosition),
        cmocka_unit_test(testIntersectionSphere1),
        cmocka_unit_test(testIntersectionSphere2),
        cmocka_unit_test(testIntersectionSphere3),
        cmocka_unit_test(testIntersectionSphere4),
        cmocka_unit_test(testIntersectionSphere5)
    };
    return cmocka_run_group_tests_name("rayTests", tests, NULL, NULL);
}

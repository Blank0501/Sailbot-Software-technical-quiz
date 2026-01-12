#include "stdio.h"
#include "cutest/CuTest.h"
#include "standard_calc.h"

/**************** Tests for bound_to_180() *******************/
void test_bound_basic1(CuTest *tc) {
    CuAssertDblEquals(tc, 0, bound_to_180(0), 0.0001);
    CuAssertDblEquals(tc, 135, bound_to_180(135), 0.0001);
    CuAssertDblEquals(tc, -160, bound_to_180(200), 0.0001);
}

void test_bound_edges(CuTest *tc) {
    CuAssertDblEquals(tc, -180, bound_to_180(-180), 0.0001);
    CuAssertDblEquals(tc, -180, bound_to_180(180), 0.0001);
}

void test_bound_wrapping(CuTest *tc) {
    CuAssertDblEquals(tc, 0, bound_to_180(360), 0.0001);
    CuAssertDblEquals(tc, -90, bound_to_180(-450), 0.0001);
    CuAssertDblEquals(tc, -180, bound_to_180(-900), 0.0001);
}

/**************** Tests for is_angle_between() *******************/
void test_between_basic1(CuTest *tc) {
    CuAssertTrue(tc, is_angle_between(0, 1, 2));
    CuAssertTrue(tc, is_angle_between(350, 0, 10));
    CuAssertTrue(tc, is_angle_between(90, 135, 180));
    CuAssertTrue(tc, !is_angle_between(45, 90, 270));
    CuAssertTrue(tc, !is_angle_between(0, 180, 90));
    CuAssertTrue(tc, !is_angle_between(0, -90, 90));
}
void test_between_edges(CuTest *tc) {
    CuAssertTrue(tc, !is_angle_between(0, 0, 90));
    CuAssertTrue(tc, !is_angle_between(0, 90, 90));
    CuAssertTrue(tc, !is_angle_between(10, 10, 10));
}

int main(int argc, char const *argv[]) {
    CuString *output = CuStringNew();
    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, test_bound_basic1);
    SUITE_ADD_TEST(suite, test_bound_edges);
    SUITE_ADD_TEST(suite, test_bound_wrapping);
    SUITE_ADD_TEST(suite, test_between_basic1);
    SUITE_ADD_TEST(suite, test_between_edges);

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    return suite->failCount > 0 ? 1 : 0;
}

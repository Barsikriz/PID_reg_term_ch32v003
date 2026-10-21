#include <assert.h>
#include <math.h>

#include "reference.h"

static void test_cooling(void) {
  float result = reference_update(20.0f, 10.0f, 6.0f, 2.0f);

  assert(fabsf(result - 19.8f) < 0.0001f);
}

static void test_heating(void) {
  float result = reference_update(10.0f, 20.0f, 6.0f, 1.0f);

  assert(fabsf(result - 10.1f) < 0.0001f);
}

static void test_target(void) {
  float result = reference_update(-15.0f, -15.0f, 3.0f, 1.0f);

  assert(fabsf(result - (-15.0f)) < 0.0001f);
}

static void test_one_step(void) {
  float result = reference_update(19.98f, 20.0f, 6.0f, 1.0f);

  assert(fabsf(result - 20.0f) < 0.0001f);
}

static void test_zero(void) {
  float result = reference_update(0.05f, -10.0f, 6.0f, 2.0f);

  assert(fabsf(result - -0.15f) < 0.0001f);
}

int main(void) {
  test_cooling();
  test_heating();
  test_one_step();
  test_target();
  test_zero();
  return 0;
}

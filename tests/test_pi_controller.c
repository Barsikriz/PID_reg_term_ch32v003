#include "pi_controller.h"
#include <assert.h>
#include <math.h>

static void test_positive_55(void) {
  pi_controller_t pi = {.kp = 0.1f, .ki = 0.01f, .integral = 0.0f};
  float uk = pi_update(&pi, 30.0f, 25.0f, 1.0f);
  assert(fabsf(uk - 0.55f) <= 0.0001f);
}

static void test_negative_55(void) {
  pi_controller_t pi = {.kp = 0.1f, .ki = 0.01f, .integral = 0.0f};
  float uk = pi_update(&pi, 25.0f, 30.0f, 1.0f);
  assert(fabsf(uk + 0.55f) <= 0.0001f);
}

static void test_integral_accumulates(void) {
  pi_controller_t pi = {.kp = 0.0f, .ki = 0.1f, .integral = 0.0f};

  float first = pi_update(&pi, 1.0f, 0.0f, 1.0f);
  float second = pi_update(&pi, 1.0f, 0.0f, 1.0f);

  assert(fabsf(first - 0.1f) < 0.0001f);
  assert(fabsf(second - 0.2f) < 0.0001f);
}

static void test_positive_1(void) {
  pi_controller_t pi = {.kp = 0.1f, .ki = 0.01f, .integral = 0.0f};
  float uk = pi_update(&pi, 125.0f, 25.0f, 1.0f);
  assert(fabsf(uk - 1.0f) <= 0.0001f);
}

static void test_reset(void) {
  pi_controller_t pi = {.kp = 0.1f, .ki = 0.01f, .integral = 15.0f};
  pi_reset(&pi);
  assert(pi.integral == 0.0f);
}
int main(void) {
  test_positive_55();
  test_negative_55();
  test_integral_accumulates();
  test_positive_1();
  test_reset();

  return 0;
}

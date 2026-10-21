#include "reference.h"

float reference_update(float current, float target, float max_rate, float dt) {

  if (max_rate <= 0 || dt <= 0) {
    return current;
  }

  float error = target - current;
  float max_step = max_rate * dt / 60.0f;

  if (error > max_step) {
    return current + max_step;
  } else if (error < -max_step) {
    return current - max_step;
  }
  return target;
}

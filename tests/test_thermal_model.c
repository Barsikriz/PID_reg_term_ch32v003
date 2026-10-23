#include "thermal_model.h"
#include <assert.h>
#include <math.h>

thermal_params_t params = {
    .ambient_c = 25.0f,
    .heat_capacity_j_per_c = 100.0f,
    .max_power_w = 20.0f,
    .conductance_w_per_c = 1.0f,
};
int main(void) {

  float next = thermal_step(25.0f, 0.5f, 1.0f, &params);

  assert(fabsf(next - 25.1f) < 0.0001f);

  params.ambient_c = 25.0f;

  next = thermal_step(25.0f, 0.0f, 1.0f, &params);

  assert(fabsf(next - 25.0f) < 0.0001f);

  next = thermal_step(30.0f, 0.0f, 1.0f, &params);

  assert(fabsf(next - 29.95f) < 0.0001f);

  next = thermal_step(25.0f, -0.5f, 1.0f, &params);

  assert(fabsf(next - 24.9f) < 0.0001f);

  return 0;
}

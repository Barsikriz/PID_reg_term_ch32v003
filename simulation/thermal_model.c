#include "thermal_model.h"

float thermal_step(float current_c, float control, float dt_s,
                   const thermal_params_t *params) {
  if (dt_s <= 0 || params->heat_capacity_j_per_c <= 0 || control < -1.0f ||
      control > 1.0f) {
    return current_c;
  }

  float new_temp = current_c + (dt_s *
                                ((params->max_power_w * control) -
                                 params->conductance_w_per_c * current_c) /
                                params->heat_capacity_j_per_c);

  return new_temp;
}

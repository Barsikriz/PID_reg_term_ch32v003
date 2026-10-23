#ifndef THERMAL_MODEL_H
#define THERMAL_MODEL_H

typedef struct {
  float ambient_c;
  float heat_capacity_j_per_c;
  float max_power_w;
  float conductance_w_per_c;

} thermal_params_t;

float thermal_step(float current_c, float control, float dt_s,
                   const thermal_params_t *params);

#endif // !THERMAL_MODEL_H

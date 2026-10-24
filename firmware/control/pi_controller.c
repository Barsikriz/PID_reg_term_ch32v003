#include "pi_controller.h"

float pi_update(pi_controller_t *controller, float setpoint_c, float measured_c,
                float dt_s) {
  if (dt_s <= 0) {
    return 0;
  }

  float ek = setpoint_c - measured_c;

  float ik_next = controller->integral + (ek * dt_s);
  float uk = controller->kp * ek + controller->ki * ik_next;

  float uk_sat = uk;
  if (uk_sat > 1.0f) {
    uk_sat = 1.0f;
  } else if (uk_sat < -1.0f) {
    uk_sat = -1.0f;
  }

  int sign_uk = (uk > 0.0f) - (uk < 0.0f);
  int sign_ek = (ek > 0.0f) - (ek < 0.0f);

  if (uk == uk_sat || (sign_uk != sign_ek)) {
    controller->integral = ik_next;
  }

  return uk_sat;
}

void pi_reset(pi_controller_t *controller) { controller->integral = 0.0f; }

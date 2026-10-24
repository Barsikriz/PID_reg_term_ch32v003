#include "pi_controller.h"

float pi_update(pi_controller_t *controller, float setpoint_c, float measured_c,
                float dt_s) {
  float ek = setpoint_c - measured_c;

  float ik = controller->integral + (ek * dt_s);
  float uk = controller->kp * ek + controller->ki * ik;
  if (uk > 1.0f) {
    uk = 1.0f;
  } else if (uk < -1.0f) {
    uk = -1.0f;
  } else {
    controller->integral = ik;
  }

  return uk;
}

void pi_reset(pi_controller_t *controller) { controller->integral = 0.0f; }

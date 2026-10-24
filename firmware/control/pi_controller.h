#ifndef PI_CONTROLLER_H
#define PI_CONTROLLER_H

typedef struct {
  float kp;
  float ki;
  float integral;

} pi_controller_t;

float pi_update(pi_controller_t *controller, float setpoint_c, float measured_c,
                float dt_s);

void pi_reset(pi_controller_t *controller);

#endif // !PI_CONTROLLER_H

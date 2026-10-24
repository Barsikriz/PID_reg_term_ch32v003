#include "pi_controller.h"
#include "reference.h"
#include "thermal_model.h"
#include <stdio.h>

thermal_params_t params = {
    .ambient_c = 25.0f,
    .heat_capacity_j_per_c = 100.0f,
    .max_power_w = 20.0f,
    .conductance_w_per_c = 1.0f,
};

int main(void) {
  FILE *fp = fopen("simulation/simulation.csv", "w");
  if (fp == NULL) {
    perror("Ошибка открытия файла");
    return 1;
  }
  pi_controller_t pi = {.kp = 0.1f, .ki = 0.01f, .integral = 0.0f};
  float target_c = 30.0f;
  float current_c = 25.0f;
  float reference_c = current_c;
  float control = 0.0f;
  float max_rate = 2.0f; // °C/min
  float dt_s = 1.0f;
  fprintf(fp, "time_s,max_target,target_c,temperature_c,control\n");
  for (int i = 1; i <= 600; i++) {
    reference_c = reference_update(reference_c, target_c, max_rate, dt_s);

    control = pi_update(&pi, reference_c, current_c, dt_s);

    current_c = thermal_step(current_c, control, dt_s, &params);

    fprintf(fp, "%d,%.6f,%.6f,%.6f,%.6f\n", i, target_c, reference_c, current_c,
            control);
  }
  fclose(fp);
  printf("Файл simulation.csv успешно создан!\n");
  return 0;
}

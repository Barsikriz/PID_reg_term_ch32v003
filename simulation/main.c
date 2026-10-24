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

  float current_c = 25.0f;
  float control = 0.5f;
  float dt_s = 1.0f;
  fprintf(fp, "%d,%.6f,%.2f\n", 0, current_c, control);
  for (int i = 1; i < 300; i++) {

    current_c = thermal_step(current_c, control, dt_s, &params);
    fprintf(fp, "%d,%.6f,%.2f\n", i, current_c, control);
  }
  fclose(fp);
  printf("Файл simulation.csv успешно создан!\n");
  return 0;
}

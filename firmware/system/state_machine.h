#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <stdbool.h>

typedef enum {
  THERMOSTAT_IDLE,
  THERMOSTAT_RAMP,
  THERMOSTAT_HOLD,
  THERMOSTAT_FAULT,
} thermostat_state_t;

typedef enum {
  THERMOSTAT_START,
  THERMOSTAT_STOP,
  THERMOSTAT_TARGET_CHANGED,
  THERMOSTAT_TARGET_REACHED,
  THERMOSTAT_SENSOR_FAULT,
  THERMOSTAT_RESET_FAULT,
} thermostat_event_t;

thermostat_state_t thermostat_transition(thermostat_state_t current,
                                         thermostat_event_t event,
                                         bool safe_to_run);

#endif

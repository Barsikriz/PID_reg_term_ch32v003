#include "state_machine.h"
#include <stdbool.h>

thermostat_state_t thermostat_transition(thermostat_state_t current,
                                         thermostat_event_t event,
                                         bool safe_to_run) {
  if (event == THERMOSTAT_SENSOR_FAULT) {
    return THERMOSTAT_FAULT;
  }

  switch (current) {
  case THERMOSTAT_IDLE:
    if (event == THERMOSTAT_START && safe_to_run) {
      return THERMOSTAT_RAMP;
    }
    break;
  case THERMOSTAT_RAMP:
    switch (event) {
    case THERMOSTAT_TARGET_REACHED:
      return THERMOSTAT_HOLD;
      break;
    case THERMOSTAT_STOP:
      return THERMOSTAT_IDLE;
      break;
    default:
      break;
    }
    break;
  case THERMOSTAT_HOLD:
    switch (event) {
    case THERMOSTAT_TARGET_CHANGED:
      return THERMOSTAT_RAMP;
      break;
    case THERMOSTAT_STOP:
      return THERMOSTAT_IDLE;
      break;
    default:
      break;
    }
    break;
  case THERMOSTAT_FAULT:
    if (event == THERMOSTAT_RESET_FAULT && safe_to_run) {
      return THERMOSTAT_IDLE;
    }
    break;
  default:
    break;
  }
  return current;
};

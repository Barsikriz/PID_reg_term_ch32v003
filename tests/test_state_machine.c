#include "state_machine.h"

#include <assert.h>
#include <stdbool.h>

static void test_start(void) {
  thermostat_state_t result =
      thermostat_transition(THERMOSTAT_IDLE, THERMOSTAT_START, true);

  assert(result == THERMOSTAT_RAMP);
}

static void test_start_unsafe(void) {
  thermostat_state_t result =
      thermostat_transition(THERMOSTAT_IDLE, THERMOSTAT_START, false);

  assert(result == THERMOSTAT_IDLE);
}

static void test_stop_ramp(void) {
  thermostat_state_t result =
      thermostat_transition(THERMOSTAT_RAMP, THERMOSTAT_STOP, true);

  assert(result == THERMOSTAT_IDLE);
}

static void test_change_target_hold(void) {
  thermostat_state_t result =
      thermostat_transition(THERMOSTAT_HOLD, THERMOSTAT_TARGET_CHANGED, true);

  assert(result == THERMOSTAT_RAMP);
}

static void test_reached_target_ramp(void) {
  thermostat_state_t result =
      thermostat_transition(THERMOSTAT_RAMP, THERMOSTAT_TARGET_REACHED, true);

  assert(result == THERMOSTAT_HOLD);
}

static void test_sensor_fault_hold(void) {
  thermostat_state_t result =
      thermostat_transition(THERMOSTAT_HOLD, THERMOSTAT_SENSOR_FAULT, true);

  assert(result == THERMOSTAT_FAULT);
}

static void test_start_fault(void) {
  thermostat_state_t result =
      thermostat_transition(THERMOSTAT_FAULT, THERMOSTAT_START, true);

  assert(result == THERMOSTAT_FAULT);
}

static void test_reset_fault(void) {
  thermostat_state_t result =
      thermostat_transition(THERMOSTAT_FAULT, THERMOSTAT_RESET_FAULT, false);

  assert(result == THERMOSTAT_FAULT);
}

static void test_reset_safe(void) {
  thermostat_state_t result =
      thermostat_transition(THERMOSTAT_FAULT, THERMOSTAT_RESET_FAULT, true);

  assert(result == THERMOSTAT_IDLE);
}

static void test_unsafe_ramp_hold(void) {
  thermostat_state_t result =
      thermostat_transition(THERMOSTAT_RAMP, THERMOSTAT_SENSOR_FAULT, false);

  assert(result == THERMOSTAT_FAULT);
}

int main(void) {
  test_start();
  test_start_unsafe();
  test_stop_ramp();
  test_change_target_hold();
  test_reached_target_ramp();
  test_sensor_fault_hold();
  test_start_fault();
  test_reset_fault();
  test_reset_safe();
  test_unsafe_ramp_hold();
  return 0;
}

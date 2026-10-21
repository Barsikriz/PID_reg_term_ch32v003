# Laboratory Peltier Thermostat

**Bare-metal temperature control system based on the CH32V003 RISC-V microcontroller.**

An experimental embedded system intended for a laboratory setup that measures the electrical resistance of a sample at controlled temperatures.

The system is being designed to support both heating and cooling using thermoelectric (Peltier) modules, with a PC acting as the supervisory controller.

**Status:** Early development — hardware architecture and final operating requirements are not yet confirmed.

## Project Goals

- Bidirectional temperature control using Peltier modules.
- Configurable temperature ramp limiting.
- Closed-loop temperature regulation using PI/PID control.
- Temperature measurement through an external sensor interface.
- UART communication with a host PC.
- Fault detection and safe actuator shutdown.
- Hardware-independent control algorithms with unit tests and simulation.

## Architecture

The firmware separates temperature control algorithms from hardware-specific peripheral drivers.

| Component | Responsibility |
|---|---|
| `firmware/control/` | Reference generation and PI/PID control |
| `firmware/app/` | Application logic |
| `firmware/system/` | State machine, safety and telemetry |
| `firmware/drivers/` | External device drivers |
| `firmware/hal/` | MCU peripheral interfaces |
| `simulation/` | Thermal system simulation |
| `tests/` | Host-based unit tests |
| `docs/` | Architecture and design documentation |

## Current Progress

- [x] Initial repository structure
- [x] Temperature reference generator with slew-rate limiting
- [x] Basic host-based unit tests
- [ ] Application state machine
- [ ] Thermal simulation
- [ ] PI/PID controller
- [ ] Temperature sensor driver
- [ ] MCU integration
- [ ] Bidirectional power-stage integration
- [ ] Experimental validation

## Building and Testing

The hardware-independent control code can be compiled and tested on a Windows PC using MinGW-w64 GCC.

From the repository root, compile the reference generator tests:

`gcc -std=c11 -Wall -Wextra -Wpedantic -Ifirmware/control tests/test_reference.c firmware/control/reference.c -o test_reference.exe -lm`

Run the tests in PowerShell:

`.\test_reference.exe`

The program exits successfully when all assertions pass.

## Hardware

**Planned controller:** CH32V003 (RISC-V)

The experimental setup may use 4–8 Peltier modules. Final electrical characteristics, power-stage topology and temperature measurement requirements are still under development.

High-power switching, fault handling and thermal protection must be validated before operating the physical installation.

## Development Approach

Control algorithms are developed and tested independently of the microcontroller.

The project follows an incremental workflow:

**Host implementation → Unit tests → Thermal simulation → MCU integration → Hardware validation**

Hardware design decisions and experimental results will be documented as the project develops.

# Description
Simple example of PID controller in C.
PID used in simple aircraft 1D simulation (altitude only) to achieve desired altitude from point of start (0 altitude).

# How to run

Clone project:
```bash
git clone --recursive git@github.com:maxboro/pid-controller-c.git
```

#### Simulation:
```bash
make           # Builds the project
./bin/exec     # Runs the executable
```

#### Clean:
```bash
make clean     # Cleans up build files
```
# Settings
In file settings.txt you can modify simulation parameters.
- dt (default 0.05) - Time step of simulation, s
- simulation_time (default 100) - Total time of simulation, s
- gravity (default 9.81) - g value for simulation in m/s^2
- drag_coefficient (default 0.1) - drag coefficient for simulation, Newtons
- target_altitude (default 10) - desired altitude, m
- pid_kp - PID parameter: Proportional gain
- pid_ki - PID parameter: Integral gain
- pid_kd - PID parameter: Derivative gain
- pid_integral_err_min - PID parameter: Lower bound for integral error
- pid_integral_err_max - PID parameter: Upper bound for integral error
- aircraft_mass - Aircraft parameter: mass, kg
- aircraft_min_thrust - Aircraft parameter: minimal thrust, Neutons
- aircraft_max_thrust - Aircraft parameter: max thrust, Neutons

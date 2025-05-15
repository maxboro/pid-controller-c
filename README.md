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
./exec         # Runs the executable
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
- verbose (default 0) - 1 to print intermediate calculations, 0 only main info
- pid_kp - PID parameter: Proportional gain
- pid_ki - PID parameter: Integral gain
- pid_kd - PID parameter: Derivative gain
- pid_integral_err_min - PID parameter: Lower bound for integral error
- pid_integral_err_max - PID parameter: Upper bound for integral error
- aircraft_mass - Aircraft parameter: mass, kg
- aircraft_min_thrust - Aircraft parameter: minimal thrust, Neutons
- aircraft_max_thrust - Aircraft parameter: max thrust, Neutons

# Example

verbose=0
```terminal
dt is set to 0.100000
simulation_time is set to 100.000000
gravity is set to 9.810000
drag_coefficient is set to 0.010000
target_altitude is set to 20.000000
verbose is set to 0
pid_kp is set to 2.000000
pid_ki is set to 0.500000
pid_kd is set to 1.000000
pid_integral_err_min is set to -1000.000000
pid_integral_err_max is set to 1000.000000
aircraft_mass is set to 1.000000
aircraft_min_thrust is set to 0.000000
aircraft_max_thrust is set to 30.000000
Thrust (PID): 41.000000  Thrust (real): 30.000000  Alt: 0.201900
Thrust (PID): 39.567105  Thrust (real): 30.000000  Alt: 0.605292
Thrust (PID): 37.715132  Thrust (real): 30.000000  Alt: 1.208957
Thrust (PID): 35.444626  Thrust (real): 30.000000  Alt: 2.010878
Thrust (PID): 32.757682  Thrust (real): 30.000000  Alt: 3.008269
Thrust (PID): 29.657796  Thrust (real): 29.657796  Alt: 4.194189
Thrust (PID): 26.190945  Thrust (real): 26.190945  Alt: 5.529855
Thrust (PID): 22.745667  Thrust (real): 22.745667  Alt: 6.977037
Thrust (PID): 19.387284  Thrust (real): 19.387284  Alt: 8.499049
Thrust (PID): 16.170013  Thrust (real): 16.170013  Alt: 10.061496
Thrust (PID): 13.137696  Thrust (real): 13.137696  Alt: 11.632807
Thrust (PID): 10.324787  Thrust (real): 10.324787  Alt: 13.184576
Thrust (PID): 7.757444  Thrust (real): 7.757444  Alt: 14.691739
Thrust (PID): 5.454584  Thrust (real): 5.454584  Alt: 16.132633
Thrust (PID): 3.428860  Thrust (real): 3.428860  Alt: 17.488954
Thrust (PID): 1.687502  Thrust (real): 1.687502  Alt: 18.745654
Thrust (PID): 0.233031  Thrust (real): 0.233031  Alt: 19.890791
Thrust (PID): -0.936157  Thrust (real): 0.000000  Alt: 20.924715
Thrust (PID): -1.938106  Thrust (real): 0.000000  Alt: 21.849848
Thrust (PID): -2.792966  Thrust (real): 0.000000  Alt: 22.668323
Thrust (PID): -3.496745  Thrust (real): 0.000000  Alt: 23.381999
Thrust (PID): -4.045207  Thrust (real): 0.000000  Alt: 23.992482
Thrust (PID): -4.433863  Thrust (real): 0.000000  Alt: 24.501138
Thrust (PID): -4.657963  Thrust (real): 0.000000  Alt: 24.909106
Thrust (PID): -4.712482  Thrust (real): 0.000000  Alt: 25.217310
Thrust (PID): -4.592112  Thrust (real): 0.000000  Alt: 25.426465
Thrust (PID): -4.291245  Thrust (real): 0.000000  Alt: 25.537081
Thrust (PID): -3.803958  Thrust (real): 0.000000  Alt: 25.549476
Thrust (PID): -3.123997  Thrust (real): 0.000000  Alt: 25.463769
Thrust (PID): -2.244755  Thrust (real): 0.000000  Alt: 25.280035
Thrust (PID): -1.161024  Thrust (real): 0.000000  Alt: 24.998539
Thrust (PID): 0.129665  Thrust (real): 0.129665  Alt: 24.621032
Thrust (PID): 1.613737  Thrust (real): 1.613737  Alt: 24.162987
Thrust (PID): 3.127052  Thrust (real): 3.127052  Alt: 23.640211
Thrust (PID): 4.637908  Thrust (real): 4.637908  Alt: 23.068447
...
Thrust (PID): 9.810000  Thrust (real): 9.810000  Alt: 20.000000
Thrust (PID): 9.810000  Thrust (real): 9.810000  Alt: 20.000000
```


verbose=1
```terminal
dt is set to 0.100000
simulation_time is set to 100.000000
gravity is set to 9.810000
drag_coefficient is set to 0.010000
target_altitude is set to 20.000000
verbose is set to 1
pid_kp is set to 2.000000
pid_ki is set to 0.500000
pid_kd is set to 1.000000
pid_integral_err_min is set to -1000.000000
pid_integral_err_max is set to 1000.000000
aircraft_mass is set to 1.000000
aircraft_min_thrust is set to 0.000000
aircraft_max_thrust is set to 30.000000
state_aircraft_ptr->thrust 30.000000
gravity_force 9.810000
abs_velocity -0.000000
drag_force -0.000000
Net force 20.190000
state_aircraft_ptr->acceleration 20.190000
state_aircraft_ptr->velocity 2.019000
Thrust (PID): 41.000000  Thrust (real): 30.000000  Alt: 0.201900
state_aircraft_ptr->thrust 30.000000
gravity_force 9.810000
abs_velocity 2.019000
drag_force 0.040764
Net force 20.149236
state_aircraft_ptr->acceleration 20.149236
state_aircraft_ptr->velocity 4.033924
Thrust (PID): 39.567105  Thrust (real): 30.000000  Alt: 0.605292
state_aircraft_ptr->thrust 30.000000
gravity_force 9.810000
abs_velocity 4.033924
drag_force 0.162725
Net force 20.027275
state_aircraft_ptr->acceleration 20.027275
state_aircraft_ptr->velocity 6.036651
Thrust (PID): 37.715132  Thrust (real): 30.000000  Alt: 1.208957
...
state_aircraft_ptr->thrust 9.810000
gravity_force 9.810000
abs_velocity 0.000000
drag_force 0.000000
Net force -0.000000
state_aircraft_ptr->acceleration -0.000000
state_aircraft_ptr->velocity 0.000000
Thrust (PID): 9.810000  Thrust (real): 9.810000  Alt: 20.000000
```
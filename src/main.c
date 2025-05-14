#include <stdbool.h>
#include <stdio.h>
#include "utils.c"
#include "structs.c"
#include "init.c"
#include "read_settings.c"
#include "altitude_model.c"
#include "pid_controller.c"

int main(){
    bool is_error = false;
    double pid_target_thrust;

    struct PIDParams params_pid;
    struct SimParams params_sim;
    struct AircraftParams params_aircraft;
    struct AircraftState state_aircraft;
    struct PIDState state_pid;
    init_state_aircraft(&state_aircraft);
    init_state_pid(&state_pid);

    // loading settings
    bool load_successful = load_settings(&params_pid, &params_sim, &params_aircraft);
    if (!load_successful){
        fprintf(stderr, "Settings weren't loaded\n");
        return 1;
    }

    for (double t = 0; t <= params_sim.simulation_time; t += params_sim.dt) {
        pid_target_thrust = compute_thrust(&state_pid, &params_pid, params_sim.target_altitude, 
            state_aircraft.altitude, params_sim.dt);
        update_altitude(&params_sim, &params_aircraft, &state_aircraft, pid_target_thrust);

        // print status
        printf("Thrust (PID): %f  Thrust (real): %f  Alt: %f\n", pid_target_thrust, state_aircraft.thrust, state_aircraft.altitude);
    }
    return 0;
}

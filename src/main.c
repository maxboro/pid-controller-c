#include <stdbool.h>
#include <stdio.h>
#include "structs.c"
#include "read_settings.c"
#include "altitude_model.c"

void init_state(struct AircraftState* state_aircraft_ptr){
    state_aircraft_ptr->altitude = 0;
    state_aircraft_ptr->velocity = 0;
    state_aircraft_ptr->acceleration = 0;
    state_aircraft_ptr->thrust = 0;
}

int main(){
    bool is_error = false;
    double pid_target_thrust;

    struct PIDParams params_pid;
    struct SimParams params_sim;
    struct AircraftParams params_aircraft;
    struct AircraftState state_aircraft;
    init_state(&state_aircraft);

    // loading settings
    bool load_successful = load_settings(&params_pid, &params_sim, &params_aircraft);
    if (!load_successful){
        fprintf(stderr, "Settings weren't loaded\n");
        return 1;
    }

    for (double t = 0; t <= params_sim.simulation_time; t += params_sim.dt) {
        pid_target_thrust = 20; // for test
        update_altitude(&params_sim, &params_aircraft, &state_aircraft, pid_target_thrust);

        // print status
        printf("Thrust (PID): %f  Thrust (real): %f  Alt: %f\n", pid_target_thrust, state_aircraft.thrust, state_aircraft.altitude);
    }
    return 0;
}

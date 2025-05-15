#include <stdbool.h>
#include <stdio.h>
#include "utils.c"
#include "structs.c"
#include "init.c"
#include "read_settings.c"
#include "altitude_model.c"
#include "pid_controller.c"

void sim_loop( 
        const struct SimParams* params_sim_ptr,
        const struct PIDParams* params_pid_ptr, 
        const struct AircraftParams* params_aircraft_ptr,
        struct AircraftState* aircraft_state_ptr,
        struct PIDState* state_pid_ptr
        ){
    double pid_target_thrust;
    for (double t = 0; t <= params_sim_ptr->simulation_time; t += params_sim_ptr->dt) {
        pid_target_thrust = compute_thrust(
            state_pid_ptr, params_pid_ptr, 
            params_sim_ptr->target_altitude, 
            aircraft_state_ptr->altitude, params_sim_ptr->dt
        );
        update_altitude(
            params_sim_ptr, params_aircraft_ptr, 
            aircraft_state_ptr, pid_target_thrust
        );

        // print status
        printf("Thrust (PID): %f  Thrust (real): %f  Alt: %f\n", 
            pid_target_thrust, aircraft_state_ptr->thrust, aircraft_state_ptr->altitude);
    }
}

int main(){
    bool is_error = false;

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
        is_error = true;
    } else {
        sim_loop(&params_sim, &params_pid, &params_aircraft, &state_aircraft, &state_pid);
    }

    if (is_error){
        printf("Program terminated with error\n");
    } else {
        printf("Program terminated nominally\n");
    }
    return 0;
}

#include <stdio.h>

void update_altitude(
        const struct SimParams* params_sim_ptr, 
        const struct AircraftParams* params_aircraft_ptr,
        struct AircraftState* state_aircraft_ptr,
        const double pid_target_thrust){
    // Check if PID calculated desired thrust is achievable by particular aircraft
    state_aircraft_ptr->thrust = cap_value(pid_target_thrust, params_aircraft_ptr->min_thrust, params_aircraft_ptr->max_thrust);

    // Physics → Calculate net force
    const double abs_velocity = state_aircraft_ptr->velocity > 0 ? state_aircraft_ptr->velocity : -state_aircraft_ptr->velocity;
    const double gravity_force = params_aircraft_ptr->mass * params_sim_ptr->gravity;
    const double drag_force = params_sim_ptr->drag_coefficient * state_aircraft_ptr->velocity * abs_velocity;
    const double net_force = state_aircraft_ptr->thrust - gravity_force - drag_force;

    if (params_sim_ptr->verbose){
        printf("state_aircraft_ptr->thrust %f\n", state_aircraft_ptr->thrust);
        printf("gravity_force %f\n", gravity_force);
        printf("abs_velocity %f\n", abs_velocity);
        printf("drag_force %f\n", drag_force);
        printf("Net force %f\n", net_force);
    }

    // Update aircraft state
    state_aircraft_ptr->acceleration = net_force / params_aircraft_ptr->mass;
    state_aircraft_ptr->velocity += state_aircraft_ptr->acceleration * params_sim_ptr->dt;
    state_aircraft_ptr->altitude += state_aircraft_ptr->velocity * params_sim_ptr->dt;
    if (params_sim_ptr->verbose){
        printf("state_aircraft_ptr->acceleration %f\n", state_aircraft_ptr->acceleration);
        printf("state_aircraft_ptr->velocity %f\n", state_aircraft_ptr->velocity);
    }
    if (state_aircraft_ptr->altitude < 0){
        state_aircraft_ptr->altitude = 0;
        if (state_aircraft_ptr->velocity < 0){
            state_aircraft_ptr->velocity = 0;
        }
    }
}

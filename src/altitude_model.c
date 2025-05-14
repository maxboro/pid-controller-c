#include <stdio.h>

void update_altitude(
        struct SimParams* sim_params_ptr, 
        struct AircraftParams* aircraft_params_ptr,
        struct AircraftState* aircraft_state_ptr,
        double pid_target_thrust){
    // Check if PID calculated desired thrust is achievable by particular aircraft
    aircraft_state_ptr->thrust = cap_value(pid_target_thrust, aircraft_params_ptr->min_thrust, aircraft_params_ptr->max_thrust);

    // Physics → Calculate net force
    double abs_velocity = aircraft_state_ptr->velocity > 0 ? aircraft_state_ptr->velocity : -aircraft_state_ptr->velocity;
    double gravity_force = aircraft_params_ptr->mass * sim_params_ptr->gravity;
    double drag_force = sim_params_ptr->drag_coefficient * aircraft_state_ptr->velocity * abs_velocity;
    double net_force = aircraft_state_ptr->thrust - gravity_force - drag_force;
    printf("aircraft_state_ptr->thrust %f\n", aircraft_state_ptr->thrust);
    printf("gravity_force %f\n", gravity_force);
    printf("abs_velocity %f\n", abs_velocity);
    printf("drag_force %f\n", drag_force);
    printf("Net force %f\n", net_force);

    // Update aircraft state
    aircraft_state_ptr->acceleration = net_force / aircraft_params_ptr->mass;
    aircraft_state_ptr->velocity += aircraft_state_ptr->acceleration * sim_params_ptr->dt;
    aircraft_state_ptr->altitude += aircraft_state_ptr->velocity * sim_params_ptr->dt;
    printf("aircraft_state_ptr->acceleration %f\n", aircraft_state_ptr->acceleration);
    printf("aircraft_state_ptr->velocity %f\n", aircraft_state_ptr->velocity);
    if (aircraft_state_ptr->altitude < 0){
        aircraft_state_ptr->altitude = 0;
        if (aircraft_state_ptr->velocity < 0){
            aircraft_state_ptr->velocity = 0;
        }
    }
}

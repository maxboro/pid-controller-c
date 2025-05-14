void init_state_aircraft(struct AircraftState* state_aircraft_ptr){
    state_aircraft_ptr->altitude = 0;
    state_aircraft_ptr->velocity = 0;
    state_aircraft_ptr->acceleration = 0;
    state_aircraft_ptr->thrust = 0;
}

void init_state_pid(struct PIDState* state_pid_ptr){
    state_pid_ptr->error_integral = 0;
    state_pid_ptr->error_derivative = 0;
    state_pid_ptr->prev_error = 0;
    state_pid_ptr->is_first_run = true;
}

double compute_thrust(
        struct PIDState* state_pid_ptr,
        const struct PIDParams* params_pid_ptr,
        const double target,
        const double current,
        const double dt
        ){
    const double error = target - current;
    state_pid_ptr->error_integral += error * dt;
    state_pid_ptr->error_integral = cap_value(state_pid_ptr->error_integral, params_pid_ptr->integral_err_min, params_pid_ptr->integral_err_max);

    // derivative
    if (state_pid_ptr->is_first_run){
        state_pid_ptr->is_first_run = false;
    } else {
        state_pid_ptr->error_derivative = (error - state_pid_ptr->prev_error) / dt;
    }
    state_pid_ptr->prev_error = error;

    // all components
    const double p_error = params_pid_ptr->Kp * error;
    const double i_error = params_pid_ptr->Ki * state_pid_ptr->error_integral;
    const double d_error = params_pid_ptr->Kd * state_pid_ptr->error_derivative;
    return p_error + i_error + d_error;
}

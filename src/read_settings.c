#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 128

void trim_newline(char *str) {
    size_t len = strlen(str);
    while (len > 0 && (str[len-1] == '\n' || str[len-1] == '\r')) {
        str[len-1] = '\0';
        len--;
    }
}

bool validate_settings(struct PIDParams* params_pid_ptr, struct SimParams* params_sim_ptr, struct AircraftParams* params_aircraft_ptr){
    if (params_sim_ptr->dt <= 0){
        perror("dt should be positive");
        return false;
    }

    if (params_sim_ptr->simulation_time <= 0){
        perror("simulation_time should be positive");
        return false;
    }

    if (params_sim_ptr->target_altitude <= 0){
        perror("target_altitude should be positive");
        return false;
    }

    if (params_sim_ptr->verbose != 0 && params_sim_ptr->verbose != 1){
        perror("verbose should be 0 or 1");
        return false;
    }

    if (params_pid_ptr->integral_err_min >= params_pid_ptr->integral_err_max){
        perror("pid_integral_err_min should be less than pid_integral_err_max");
        return false;
    }

    if (params_aircraft_ptr->min_thrust >= params_aircraft_ptr->max_thrust){
        perror("aircraft_min_thrust should be less than aircraft_max_thrust");
        return false;
    }

    return true;
}

bool load_settings(struct PIDParams* params_pid_ptr, struct SimParams* params_sim_ptr, struct AircraftParams* params_aircraft_ptr){

    // Opening file in reading mode
    FILE* file_ptr = fopen("settings.txt", "r");

    if (file_ptr == NULL) {
        fprintf(stderr, "file can't be opened \n");
        return false;
    }
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), file_ptr)) {
        trim_newline(line);

        // Split key and value
        char *equals = strchr(line, '=');
        if (!equals) continue;

        *equals = '\0';
        char *key = line;
        char *value = equals + 1;

        // printf("Setting: '%s'  Value: '%s'\n", key, value);
        // TODO: rewrite
        if (strcmp(key, "dt") == 0) {
            params_sim_ptr->dt = atof(value);
        } else if (strcmp(key, "simulation_time") == 0) {
            params_sim_ptr->simulation_time = atof(value);
        } else if (strcmp(key, "gravity") == 0) {
            params_sim_ptr->gravity = atof(value);
        } else if (strcmp(key, "drag_coefficient") == 0) {
            params_sim_ptr->drag_coefficient = atof(value);
        } else if (strcmp(key, "target_altitude") == 0) {
            params_sim_ptr->target_altitude = atof(value);
        } else if (strcmp(key, "verbose") == 0) {
            params_sim_ptr->verbose = atoi(value);
        } else if (strcmp(key, "pid_kp") == 0) {
            params_pid_ptr->Kp = atof(value);
        } else if (strcmp(key, "pid_ki") == 0) {
            params_pid_ptr->Ki = atof(value);
        } else if (strcmp(key, "pid_kd") == 0) {
            params_pid_ptr->Kd = atof(value);
        } else if (strcmp(key, "pid_integral_err_min") == 0) {
            params_pid_ptr->integral_err_min = atof(value);
        } else if (strcmp(key, "pid_integral_err_max") == 0) {
            params_pid_ptr->integral_err_max = atof(value);
        } else if (strcmp(key, "aircraft_mass") == 0) {
            params_aircraft_ptr->mass = atof(value);
        } else if (strcmp(key, "aircraft_min_thrust") == 0) {
            params_aircraft_ptr->min_thrust = atof(value);
        } else if (strcmp(key, "aircraft_max_thrust") == 0) {
            params_aircraft_ptr->max_thrust = atof(value);
        }
    }

    // Closing the file
    fclose(file_ptr);

    // Check
    printf("dt is set to %f\n", params_sim_ptr->dt);
    printf("simulation_time is set to %f\n", params_sim_ptr->simulation_time);
    printf("gravity is set to %f\n", params_sim_ptr->gravity);
    printf("drag_coefficient is set to %f\n", params_sim_ptr->drag_coefficient);
    printf("target_altitude is set to %f\n", params_sim_ptr->target_altitude);
    printf("verbose is set to %d\n", params_sim_ptr->verbose);
    printf("pid_kp is set to %f\n", params_pid_ptr->Kp);
    printf("pid_ki is set to %f\n", params_pid_ptr->Ki);
    printf("pid_kd is set to %f\n", params_pid_ptr->Kd);
    printf("pid_integral_err_min is set to %f\n", params_pid_ptr->integral_err_min);
    printf("pid_integral_err_max is set to %f\n", params_pid_ptr->integral_err_max);
    printf("aircraft_mass is set to %f\n", params_aircraft_ptr->mass);
    printf("aircraft_min_thrust is set to %f\n", params_aircraft_ptr->min_thrust);
    printf("aircraft_max_thrust is set to %f\n", params_aircraft_ptr->max_thrust);

    bool settings_are_ok = validate_settings(params_pid_ptr, params_sim_ptr, params_aircraft_ptr);
    return settings_are_ok;
}

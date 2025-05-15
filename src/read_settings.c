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

bool validate_settings(
        const struct PIDParams* params_pid_ptr,
        const struct SimParams* params_sim_ptr,
        const struct AircraftParams* params_aircraft_ptr
        ){
    char pref[] = "[Invalid setting] ";
    if (params_sim_ptr->dt <= 0){
        fprintf(stderr,"%sdt should be positive\n", pref);
        return false;
    }

    if (params_sim_ptr->simulation_time <= 0){
        fprintf(stderr,"%ssimulation_time should be positive\n", pref);
        return false;
    }

    if (params_sim_ptr->target_altitude <= 0){
        fprintf(stderr,"%starget_altitude should be positive\n", pref);
        return false;
    }

    if (params_sim_ptr->verbose != 0 && params_sim_ptr->verbose != 1){
        fprintf(stderr,"%sverbose should be 0 or 1\n", pref);
        return false;
    }

    if (params_pid_ptr->integral_err_min >= params_pid_ptr->integral_err_max){
        fprintf(stderr,"%spid_integral_err_min should be less than pid_integral_err_max\n", pref);
        return false;
    }

    if (params_aircraft_ptr->min_thrust >= params_aircraft_ptr->max_thrust){
        fprintf(stderr,"%saircraft_min_thrust should be less than aircraft_max_thrust\n", pref);
        return false;
    }

    return true;
}

bool parse_line(
        const char* line,
        struct PIDParams* params_pid_ptr,
        struct SimParams* params_sim_ptr,
        struct AircraftParams* params_aircraft_ptr
        ){
    // Copy the line        
    size_t line_len = strlen(line) + 1;
    char* line_copy = malloc(line_len);
    if (!line_copy){
        fprintf(stderr, "[parse_line] Memory wasn't allocated\n");
        return false;
    }
    memcpy(line_copy, line, line_len);

    // Split key and value
    char *equals = strchr(line_copy, '=');
    if (!equals){
        free(line_copy);
        return true;
    }

    *equals = '\0';
    char *key = line_copy;
    char *value = equals + 1;

    // TODO: try to reduce amount of boilerplate
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
        params_sim_ptr->verbose = (bool)atoi(value);
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

    free(line_copy);
    return true;
}

void print_params(
        const struct PIDParams* params_pid_ptr,    
        const struct SimParams* params_sim_ptr,
        const struct AircraftParams* params_aircraft_ptr
        ){
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
}

bool load_settings(struct PIDParams* params_pid_ptr, struct SimParams* params_sim_ptr, struct AircraftParams* params_aircraft_ptr){

    // Opening file in reading mode
    FILE* file_ptr = fopen("settings.txt", "r");

    if (file_ptr == NULL) {
        fprintf(stderr, "file can't be opened \n");
        return false;
    }
    char line[MAX_LINE];

    bool parsing_successful;
    while (fgets(line, sizeof(line), file_ptr)) {
        trim_newline(line);
        parsing_successful = parse_line(line, params_pid_ptr, params_sim_ptr, params_aircraft_ptr);
        if (!parsing_successful)
            break;
    }

    // Closing the file
    fclose(file_ptr);

    // Check
    if (parsing_successful){
        print_params(params_pid_ptr, params_sim_ptr, params_aircraft_ptr);
    } else {
        return false;
    }

    bool settings_are_ok = validate_settings(params_pid_ptr, params_sim_ptr, params_aircraft_ptr);
    return settings_are_ok;
}

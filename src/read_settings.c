#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 128
#define N_SETTINGS 14

enum ValueType { VT_DOUBLE, VT_BOOL };

struct SettingsMap {
    char* name_file_ptr;
    enum ValueType val_type;
    void* loaded_value_ptr;
};

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
        struct SettingsMap* settings_map_ptr
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

    for (int n_line = 0; n_line < N_SETTINGS; n_line++){
        if (strcmp(key, settings_map_ptr[n_line].name_file_ptr) == 0) {
            switch (settings_map_ptr[n_line].val_type) {
                case VT_DOUBLE:
                    *(double*)settings_map_ptr[n_line].loaded_value_ptr = strtod(value, NULL);
                    break;
                case VT_BOOL:
                    *(bool*)settings_map_ptr[n_line].loaded_value_ptr = (bool)atoi(value);
                    break;
            }
        }
    }

    free(line_copy);
    return true;
}

void print_params(const struct SettingsMap* settings_map_ptr){
    for (int n_line = 0; n_line < N_SETTINGS; n_line++){
        printf(
            "%s is set to %f\n", 
            settings_map_ptr[n_line].name_file_ptr, 
            *(double*)settings_map_ptr[n_line].loaded_value_ptr
        );
    }
}

bool load_settings(struct PIDParams* params_pid_ptr, struct SimParams* params_sim_ptr, struct AircraftParams* params_aircraft_ptr){

    // Setting mapping array
    struct SettingsMap settings_map[N_SETTINGS] = {
        {"dt", VT_DOUBLE, &params_sim_ptr->dt},
        {"simulation_time", VT_DOUBLE, &params_sim_ptr->simulation_time},
        {"gravity", VT_DOUBLE, &params_sim_ptr->gravity},
        {"drag_coefficient", VT_DOUBLE, &params_sim_ptr->drag_coefficient},
        {"target_altitude", VT_DOUBLE, &params_sim_ptr->target_altitude},
        {"verbose", VT_BOOL, &params_sim_ptr->verbose},
        {"pid_kp", VT_DOUBLE, &params_pid_ptr->Kp},
        {"pid_ki", VT_DOUBLE, &params_pid_ptr->Ki},
        {"pid_kd", VT_DOUBLE, &params_pid_ptr->Kd},
        {"pid_integral_err_min", VT_DOUBLE, &params_pid_ptr->integral_err_min},
        {"pid_integral_err_max", VT_DOUBLE, &params_pid_ptr->integral_err_max},
        {"aircraft_mass", VT_DOUBLE, &params_aircraft_ptr->mass},
        {"aircraft_min_thrust", VT_DOUBLE, &params_aircraft_ptr->min_thrust},
        {"aircraft_max_thrust", VT_DOUBLE, &params_aircraft_ptr->max_thrust},
    };

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
        parsing_successful = parse_line(line, settings_map);
        if (!parsing_successful)
            break;
    }

    // Closing the file
    fclose(file_ptr);

    // Check
    if (parsing_successful){
        print_params(settings_map);
    } else {
        return false;
    }

    bool settings_are_ok = validate_settings(params_pid_ptr, params_sim_ptr, params_aircraft_ptr);
    return settings_are_ok;
}

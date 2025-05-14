#include <stdbool.h>
#include "structs.c"
#include "read_settings.c"

int main(){
    bool is_error = false;

    struct PIDParams params_pid;
    struct SimParams params_sim;
    struct AircraftParams params_aircraft;
    struct AircraftState state_aircraft;

    // loading settings
    bool load_successful = load_settings(&params_pid, &params_sim, &params_aircraft);
    if (!load_successful){
        fprintf(stderr, "Settings weren't loaded\n");
        return 1;
    }
    return 0;
}

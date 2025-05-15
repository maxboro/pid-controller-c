#include <stdbool.h>

struct PIDParams {
    double Kp;
    double Ki;
    double Kd;
    double integral_err_min;
    double integral_err_max;
};

struct SimParams {
    double dt;                // s
    double simulation_time;   // s
    double gravity;           // m/s^2
    double drag_coefficient;  // Newtons
    double target_altitude;   // meters
    bool verbose;             // True to print intermediate calculations, False only main info
};

struct AircraftParams {
    double mass;          // kg
    double min_thrust;    // Newtons
    double max_thrust;    // Newtons
};

struct AircraftState {
    double altitude;     // meters
    double velocity;     // m/s
    double acceleration; // m/s^2
    double thrust;       // Newtons
};

struct PIDState {
    double error_integral;
    double error_derivative;
    double prev_error;
    bool is_first_run;
};

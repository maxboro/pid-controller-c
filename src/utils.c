double cap_value(const double value, const double min, const double max){
    if (value > max){
        return max;
    } else if (value < min){
        return min;
    } else {
        return value;
    }
}

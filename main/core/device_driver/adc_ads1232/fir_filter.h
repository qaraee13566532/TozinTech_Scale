#pragma once

#include <stdlib.h>
#include <cmath>
#include <string.h>
#include <string.h>
#include <vector>

class FIR_filter
{
public:
     FIR_filter( int16_t taps=0, double f1=0, double f2=0, int8_t* type=(int8_t*)"", 
                 int8_t* window=(int8_t*)"");
    std::vector<double> getCoefficients();

    double filter(double new_sample);

private:
    std::vector<double> lowPass_coefficient( int16_t taps, double f);
    std::vector<double> highPass_coefficient(int16_t taps, double f);
    std::vector<double> bandPass_coefficient(int16_t taps, double f1, double f2);
    std::vector<double> bandStop_coefficient(int16_t taps, double f1, double f2);

    std::vector<double> window_hammig(int16_t taps);
    std::vector<double> window_triangle(int16_t taps);
    std::vector<double> window_hanning(int16_t taps);
    std::vector<double> window_blackman(int16_t taps);

    std::vector<double> h;       // FIR coefficients
    std::vector<double> samples; // FIR delay

    int16_t idx;        // Round robin index
    int16_t taps;       // Number of taps of the filter
};


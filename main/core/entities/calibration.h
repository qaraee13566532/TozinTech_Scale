
#pragma once

#include "core/constant.h"

namespace CALIBRATION
{
    class Calibration
    {
    public:
        Calibration()
        {
        }

    public:
        unsigned long firstMaxInterval;
        unsigned long secondMaxInterval;
        long zeroAtod;
        unsigned long calibrationLoad;
        double weightFactor;
        unsigned int firstAccuracy;
        unsigned int secondAccuracy;
        unsigned char decimalPointPosition;
        bool isCalibrated;
    };
}
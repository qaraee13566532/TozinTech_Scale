
#pragma once

#include "core/constants/constant.h"

namespace CALIBRATION
{
    class Calibration
    {
    public:
        Calibration()
        {
        }

    public:
        unsigned long maxOfFirstInterval;
        unsigned long maxOfSecondInterval;
        long zeroAtod;
        unsigned long calibrationLoad;
        double weightFactor;
        unsigned int firstAccuracy;
        unsigned int secondAccuracy;
        unsigned char decimalPointPosition;
        bool isCalibrated;
        unsigned char filterLevel;
        unsigned char stableTime;
        unsigned char stableExcentLevel;
    };
}
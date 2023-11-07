
#pragma once

namespace CALIBRATION
{
    class Calibration
    {
    public:
        Calibration()
        {
        }
        void performCalibration(unsigned char platformId);

    public:
        unsigned long firstIntervalMax;
        unsigned long secondIntervalMax;
        long zeroAtod;
        unsigned long calibrationLoad;
        double weightFactor;
        unsigned int firstAccuracy;
        unsigned int secondAccuracy;
        unsigned char decimalPointPosition;
        bool isCalibrated;
    };
}
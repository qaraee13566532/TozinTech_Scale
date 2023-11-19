
#pragma once

#define POSITIVE 1
#define NEGATIVE 0
#define FIRST_PLATFORM  0
#define SECOND_PLATFORM 1
#define THIRD_PLATFORM  2
#define FOURTH_PLATFORM 3

namespace CALIBRATION
{
    enum WeightUnits
    {
        gram,
        kilogram,
        ton,
        pound,
        ounce
    };
    class Calibration
    {
        private: 
        unsigned char _platformId;
    public:
        Calibration(unsigned char platformId)
        {
            _platformId=platformId;
        };
        void performCalibration(void);
        void tuneWeight(bool tuneSign);
        void setZero(void);
        void adcFilter(void);
        unsigned long realCalibrationWeight(unsigned long inputLoad);

    public:
        unsigned long firstIntervalMax;
        unsigned long secondIntervalMax;
        long calibrationAdcOffset;
        unsigned long calibrationLoad;
        double weightFactor;
        unsigned int firstAccuracy;
        unsigned int secondAccuracy;
        unsigned char decimalPointPosition;
        WeightUnits calibrationUnit;
        bool isCalibrated;
        long netAdc;
        
    };
}
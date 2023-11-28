
#pragma once

#define MAX_WEIGHT_BUFFER_LENGHT 30

namespace ADS1232_WEIGHT
{
    class Weight
    {
    public:
        Weight();
        bool setZero(void);
        bool setTare(void);
        bool onHold(void);
        long calcWeight(void);
        long roundWeight(void);
        void filterWeight(void);
        void removeDrift(void);
        void removeBlink(void);
        void checkStability(void);
    public:
        long netAdc;
        long weight;
        long roundedWeight;
        long netWeight;
        unsigned int firstAccuracy;
        unsigned int secondAccuracy;
        unsigned long taredWeight;
        bool isWeightReceived;
        bool isTareRequested;
        bool isWeightStable;
        bool isWeightZero;
        bool isNetWeight;
        bool isFirstInterval;
        bool isSecondInterval;
        bool isWeightNegative;
        bool isOverWeight;
        bool isUnderWeight;
        bool isAdcNegative;
        bool isWeightDrifted;
        long inputWeightBuffer[MAX_WEIGHT_BUFFER_LENGHT];
        unsigned char stableAccuracyExtent;
        unsigned int stableTimeExtent;
        unsigned char filterSensitivity;
        bool isAccuracyOneGram;
    };
}
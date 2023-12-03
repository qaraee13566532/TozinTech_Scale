
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
        int32_t calcWeight(void);
        int32_t roundWeight(void);
        void filterWeight(void);
        void removeDrift(void);
        void removeBlink(void);
        void checkStability(void);
    public:
        int32_t netAdc;
        int32_t weight;
        int32_t roundedWeight;
        int32_t netWeight;
        uint16_t firstAccuracy;
        uint16_t secondAccuracy;
        uint32_t taredWeight;
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
        int32_t inputWeightBuffer[MAX_WEIGHT_BUFFER_LENGHT];
        uint8_t stableAccuracyExtent;
        uint16_t stableTimeExtent;
        uint8_t filterSensitivity;
        bool isAccuracyOneGram;
    };
}
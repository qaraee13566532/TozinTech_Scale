
#pragma once

#define MAX_WEIGHT_BUFFER_LENGHT 30

namespace ADS1232_WEIGHT
{
    class BaseWeight
    {
    public:
        uint8_t platformId;
        uint32_t firstIntervalMax;
        uint32_t secondIntervalMax;
        double weightFactor;
        double weight;
        uint16_t firstAccuracy;
        uint16_t secondAccuracy;
        int32_t netAdc;
        uint8_t decimalPointPosition;
    };

    class Weight : public BaseWeight
    {
    public:
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
        int32_t roundedWeight;
        int32_t netWeight;
        uint32_t taredWeight;
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
    };

}
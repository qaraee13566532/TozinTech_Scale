
#pragma once

#include <iostream>
#include <map>

using std::map;

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
        int32_t adcOffset;
    };

    class Weight : public BaseWeight
    {
        uint8_t driftCount;
        int32_t zeroLimit;
        int32_t startupZeroLimit;
        int32_t driftLimit;
        uint8_t stableLimitValue;
        uint8_t stableLimitSample;
        uint8_t stableCounter;
        uint8_t driftLimitSamples;
        int32_t division;
        int32_t previousRoundWeight;
        int32_t overLimit;
        const map<uint8_t, uint8_t> accuracyMap{{0, 1}, {1, 2}, {2, 5}, {3, 10}, {4, 20}, {5, 50}};

    public:
        uint8_t SetZero(void);
        uint8_t StartupZero(void);
        uint8_t SetTare(void);
        uint8_t RemoveTare(void);
        bool CalcWeight(void);
        void RemoveDrift(void);
        void CheckStability(void);
        void Initialize(void);

    public:
        int32_t roundedWeight;
        int32_t netWeight;
        uint32_t taredWeight;
        bool holdWeight;
        bool isWeightStable;
        bool isWeightZero;
        bool isNetWeight;
        bool isFirstInterval;
        bool isSecondInterval;
        bool isWeightNegative;
        bool isOverWeight;
        bool isUnderWeight;
        bool isRoundingEnabled;
    };

}
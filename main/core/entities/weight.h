
#pragma once

#include "core/constant.h"

namespace WEIGHT
{
    class Weight
    {
    public:
        Weight()
        {
        }

    public:
        long rawAdcNumber;
        long weight;
        long roundedWeight;
        long calibratedZeroNumber;
        long netAdcNumber;
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
        bool isWeightStable;
        bool isOverWeight;
        bool isUnderWeight;
        bool isWeightDrifted;
        long inputWeightBuffer[MAX_WEIGHT_BUFFER_LENGHT];
        unsigned char stableAccuracyExtent;
        unsigned int stableTimeExtent;
        unsigned char filterSensitivity;
        bool isOneGramAccuracy;
    };
}
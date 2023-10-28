
#pragma once

#include "core/constants/constant.h"

namespace WEIGHT
{
    class Weight
    {
    public:
        Weight()
        {
        }

    public:
        long ADC_DATA;
        long weight;
        long Round_Weight;
        long Pre_Weight;
        long offset;
        long ADC_WITHOUT_OFFSET;
        long Temp_Weight;
        long FilterTempWeight;
        long View_Weight;
        long minAdc;
        long maxAdc;
        unsigned int Divition;
        unsigned int Drift_Counter;
        unsigned long Tare_Weight;
        long signal[15];
        bool Zero_Flag;
        bool Net_Flag;
        bool Stable_Flag;
        bool W1_Flag;
        bool W2_Flag;
        bool w_neg;
        bool neg_sign;
        bool Tare_Flag;
        bool Drift_Flag;
        bool Over_Flag;
        bool Under_Flag;
        bool data_completed;
    };
}
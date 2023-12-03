
#pragma once

#include "core/device_driver/adc_ads1232/fir_filter.h"
#include "core/device_driver/adc_ads1232/MedianFilter.h"
#include <iostream>

#define MAX_WEIGHT_BUFFER_LENGHT 30
#define MAX_PLATFORM_NUMBER 2
#define FIRST_PLATFORM 0
#define SECOND_PLATFORM 1
#define MAX_CALIBRATION_STANDARD 2

namespace ADC_ADS1232
{
    class Adc
    {
    public:
        Adc();

    public:
        static inline int32_t rawAdc[MAX_PLATFORM_NUMBER];
        static inline int32_t filterdRawAdc[MAX_PLATFORM_NUMBER];

        static inline bool isAdcDataReceived[MAX_PLATFORM_NUMBER];
        static inline bool isAdcNegative[MAX_PLATFORM_NUMBER];
        static inline uint32_t filteringRange[MAX_PLATFORM_NUMBER];
        static inline uint8_t filteringTaps[MAX_PLATFORM_NUMBER];
        static inline bool useFiltering[MAX_PLATFORM_NUMBER];
        static inline FIR_filter lpFilter[MAX_PLATFORM_NUMBER];
        static inline double adcBuffer[10];
        static inline MedianFilter medianFilter[MAX_PLATFORM_NUMBER];
        

    public:
        static void InitAdc(void);
        static void MakeAdcClock(void);
        static void ReadAdcRawData(void);
    };
}
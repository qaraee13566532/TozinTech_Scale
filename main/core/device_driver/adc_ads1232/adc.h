
#pragma once

#include "core/device_driver/adc_ads1232/fir_filter.h"
#include "core/device_driver/adc_ads1232/MedianFilter.h"

#define MAX_WEIGHT_BUFFER_LENGHT 30
#define MAX_PLATFORM_NUMBER 2
#define FIRST_PLATFORM 0
#define SECOND_PLATFORM 1

namespace ADC_ADS1232
{
    class Adc
    {
    public:
        Adc();

    public:
        static inline long rawAdc[MAX_PLATFORM_NUMBER];
        static inline long filterdRawAdc[MAX_PLATFORM_NUMBER];

        static inline bool isAdcDataReceived[MAX_PLATFORM_NUMBER];
        static inline bool isAdcNegative[MAX_PLATFORM_NUMBER];
        static inline unsigned long filteringRange[MAX_PLATFORM_NUMBER];
        static inline unsigned char filteringTaps[MAX_PLATFORM_NUMBER];
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
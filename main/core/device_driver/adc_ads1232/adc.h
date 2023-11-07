
#pragma once

#define MAX_WEIGHT_BUFFER_LENGHT 30
#define MAX_PLATFORM_NUMBER 2
#define FIRST_PLATFORM 0
#define SECOND_PLATFORM 1

namespace ADC_ADS1232
{
    class Adc
    {
    public:
        Adc()
        {
        }

    public:
        static inline long rawAdc[MAX_PLATFORM_NUMBER];
        static inline long netAdc[MAX_PLATFORM_NUMBER];
        static inline bool isAdcDataReceived[MAX_PLATFORM_NUMBER];
        static inline bool isAdcNegative[MAX_PLATFORM_NUMBER];

    public:
        static void InitAdc(void);
        static void MakeAdcClock(void);
        static void ReadAdcRawData(void);
    };
}
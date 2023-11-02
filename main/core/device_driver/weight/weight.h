
#pragma once

const unsigned char MAX_WEIGHT_BUFFER_LENGHT = 30;

namespace ADS1232_WEIGHT
{
    class Weight
    {
    public:
        Weight()
        {
        }

    public:
        static inline long rawAdcNumber;
        static inline long weight;
        static inline long roundedWeight;
        static inline long calibratedZeroNumber;
        static inline long netAdcNumber;
        static inline long netWeight;
        static inline unsigned int firstAccuracy;
        static inline unsigned int secondAccuracy;
        static inline unsigned long taredWeight;
        static inline bool isWeightReceived;
        static inline bool isTareRequested;
        static inline bool isWeightStable;
        static inline bool isWeightZero;
        static inline bool isNetWeight;
        static inline bool isFirstInterval;
        static inline bool isSecondInterval;
        static inline  bool isWeightNegative;
        static inline bool isOverWeight;
        static inline bool isUnderWeight;
        static inline bool isAdcNegative;
        static inline bool isWeightDrifted;
        static inline long inputWeightBuffer[MAX_WEIGHT_BUFFER_LENGHT];
        static inline unsigned char stableAccuracyExtent;
        static inline unsigned int stableTimeExtent;
        static inline unsigned char filterSensitivity;
        static inline bool isOneGramAccuracy;

    public:
        static void InitAdc(void);
        static void MakeClock(void);
        static void ReadAdcRawData(void);
    };
}
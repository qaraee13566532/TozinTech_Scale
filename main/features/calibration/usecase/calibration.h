
#pragma once

#include "cJSON.h"
#include <iostream>
#include <map>

using std::map;
using std::string;

#define POSITIVE 1
#define NEGATIVE 0
#define FIRST_PLATFORM 0
#define SECOND_PLATFORM 1
#define THIRD_PLATFORM 2
#define FOURTH_PLATFORM 3

namespace CALIBRATION
{
    class Calibration
    {
        cJSON *cjson;

    public:
        void performCalibration(void);
        void tuneWeight(bool tuneSign);
        void setZero(void);
        void adcFilter(void);
        uint32_t realCalibrationWeight(uint32_t inputLoad);
        void toJson();
        void fromJson();
        bool validateAccuracy(uint32_t value);

    public:
        const map<uint8_t, string> calibrationUnitMap{{0, "gram"}, {1, "kilogram"}, {2, "ton"}, {3, "pound"}, {4, "ounce"}};
        const map<uint8_t, string> decimalPoint{{0, "----"}, {1, "0.0"}, {2, "0.00"}, {3, "0.000"}};
        const map<uint8_t, string> calibrationTypeMap{{0, "multi range"}, {1, "multi interval"}};
        string serializedData;
        uint8_t platformId;
        uint32_t firstIntervalMax;
        uint32_t secondIntervalMax;
        int32_t calibrationAdcOffset;
        uint32_t calibrationLoad;
        double weightFactor;
        uint16_t firstAccuracy;
        uint16_t secondAccuracy;
        uint8_t decimalPointPosition;
        uint8_t calibrationUnitIndex;
        bool isCalibrated;
        int32_t netAdc;
        bool hasEstandard;
        uint8_t calibrationType;
    };
}
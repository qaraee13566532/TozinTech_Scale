
#pragma once

#include "cJSON.h"
#include <iostream>
#include <map>
#include "core/weight/weight.h"
#include "core/calibration/usecase/calibration.h"
#include "core/device_driver/adc_ads1232/adc.h"

using namespace ADS1232_WEIGHT;

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
    class Calibration : public BaseWeight
    {
        cJSON *cjson;

    public:
        void performCalibration(uint8_t & Progress,bool & update);
        void tuneWeight(bool tuneSign);
        void setZero(void);
        void adcFilter(void);
        uint32_t realCalibrationWeight(uint32_t inputLoad);
        void toJson();
        void fromJson();
        void calcWeight();
        void InitCalibration(uint8_t & Progress);
        int8_t getStringKey(map<uint8_t, string> map, string value);
        int8_t getIntegerKey(map<uint8_t, uint32_t> map, uint32_t value);
        bool loadParameters(void);

    public:
        const map<uint8_t, string> calibrationUnitMap{{0, "gram"}, {1, "kilogram"}, {2, "ton"}, {3, "pound"}, {4, "ounce"}};
        const map<uint8_t, string> decimalPoint{{0, "----"}, {1, "0.0"}, {2, "0.00"}, {3, "0.000"}};
        const map<uint8_t, string> loadcellTypeMap{{0, "SingL-r"}, {1, "mULTI-r"}, {2, "mULTI-I"}};
        const map<uint8_t, uint8_t> accuracyMap{{0, 1}, {1, 2}, {2, 5}, {3, 10}, {4, 20}, {5, 50}};
        const map<uint8_t, string> calibrationStandardHelperMap{{0, "nonE"}, {1, "oIML"}};

        string serializedData;
        uint32_t calibrationLoad;
        uint8_t calibrationUnitIndex;
        bool isCalibrated;
        uint8_t calibrationStandardIndex;
        uint8_t loadcellTypeIndex;
        uint8_t calibProgress;
        bool isCalibrationSaved;
    };
}

#pragma once

#include <iostream>
#include <string>
#include <map>

using std::cout;
using std::endl;
using std::istringstream;
using std::map;
using std::string;

#define CalibrationInitialize 0
#define SelectPlatform 1
#define SelectCalibrationStandard 2
#define SelectCalibratonType 3
#define SelectCalibrationUnit 4
#define SelectFirstAccuracy 5
#define SelectSecondAccuracy 6
#define SelectDecimalPointPosition 7
#define EnterCalibrationLoad 8
#define EnterFirstMax 9
#define EnterSecondMax 10
#define SaveZeroPoint 11
#define DoCalibration 12
#define SaveCalibration 13
#define EnterData "13"

namespace CALIBRATION
{
    class CalibrationPage
    {
        CalibrationPage();
        static inline uint8_t maxDigits, pageState, currentPlatform,
            keyCode, digitIndex, currentLocation, blinkDigit;
        static inline uint16_t blinkDelay;
        static inline uint32_t Number;
        static inline int dataSize;
        static inline bool keytype,enableToEntering,showHelper,weightReady,isCalibrated;
        static inline string helperMessage;
        static inline string digitsBuffer;
        static inline uint8_t calibProgress;

        static void generalTaks(uint8_t pageState, uint8_t maxDigits, uint8_t currentLocation, string helperMessage, string nextPageTitle, uint32_t nextPageValue);
        static void generalSelectionsTaks(const map<uint8_t, uint32_t> valueMap, const map<uint8_t, string> helperMap, uint8_t pageState, uint8_t maxDigits, uint8_t currentLocation, string helperMessage, string nextPageTitle, uint32_t nextPageValue, bool showHelper);

    public:
        static void RunTasks(void);
        static inline  map<uint8_t, uint32_t> valueMap;
        static inline  map<uint8_t, string> helperMap;
        static inline const map<uint8_t, uint32_t> platformValueMap{{0, 1}, {1, 2}};
        static inline const map<uint8_t, string> standardHelperMap{{0, " nonE  "}, {1, " oIML  "}};
        static inline const map<uint8_t, uint32_t> standardValueMap{{0, 1}, {1, 2}};
        static inline const map<uint8_t, string> calTypeHelperMap{{0, "SingL-r"},{1, "mULTI-r"}, {2, "mULTI-I"}};
        static inline const map<uint8_t, uint32_t> calTypeValueMap{{0, 1}, {1, 2},{2, 3}};
        static inline const map<uint8_t, string> unitHelperMap{{0, " grAm  "}, {1, "  kg   "}, {2, "  ton  "}, {3, " Pound "}, {4, " ounCE "}};
        static inline const map<uint8_t, uint32_t> unitValueMap{{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}};
        static inline const map<uint8_t, string> decimalpointHelperMap{{0, " ----- "}, {1, "  0.0   "}, {2, "  0.00  "}, {3, "  0.000 "}, {4, " 0.0000 "}};
        static inline const map<uint8_t, uint32_t> decimalpointValueMap{{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}};
        static inline const map<uint8_t, uint32_t> accuracyValueMap{{0, 1}, {1, 2}, {2, 5}, {3, 10}, {4, 20}, {5, 50}};
    };
}
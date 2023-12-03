
#pragma once

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::istringstream;
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
        static inline bool keytype;
        static inline string helperMessage;
        static inline string digitsBuffer;

        static void generalTaks(uint8_t pageState, uint8_t maxDigits, uint8_t currentLocation, string helperMessage, string nextPageTitle, uint32_t nextPageValue);

    public:
        static void RunTasks(void);
    };
}
#include "features/calibration/ui/calibration_page.h"
#include "core/definations.h"
#include "core/device_driver/seven_segment_display/seven_segment_display.h"
#include "core/global_variables.h"
#include "core/device_driver/matrix_keyboard/keyboard.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include "core/device_driver/timer/timer.h"
#include "limits.h"
#include "features/calibration/usecase/calibration.h"
#include "core\device_driver\storage\storage.h"

using std::cout;
using std::endl;
using std::istringstream;
using std::string;

using namespace SSEG_DEVICE_DRIVER;
using namespace MATRIX_KEYBOARD;
using namespace GLOBAL_TIMER;
using namespace CALIBRATION;
using namespace STORAGE;

namespace CALIBRATION
{
    void CalibrationPage::generalTaks(uint8_t pageState, uint8_t maxDigits, uint8_t currentLocation, string helperMessage, string nextPageTitle, uint32_t nextPageValue)
    {
        CalibrationPage::pageState = pageState;
        Sseg::BlankDisplay();
        CalibrationPage::maxDigits = maxDigits;
        CalibrationPage::currentLocation = currentLocation;
        CalibrationPage::Number = nextPageValue;
        CalibrationPage::helperMessage = helperMessage;
        digitsBuffer = std::to_string(Number);
        CalibrationPage::digitIndex = 0;
        Sseg::Write_Message_To_Display(nextPageTitle, CalibrationPage::currentLocation, 6, true);
        Sseg::Write_Number_To_Display(Number, CalibrationPage::currentLocation, false, 0, true, true, CalibrationPage::maxDigits, false, false);
    }

    void CalibrationPage::RunTasks(void)
    {
        maxDigits = 1;
        pageState = CalibrationInitialize;
        currentPlatform = 0;
        keyCode = 0;
        digitIndex = 0;
        blinkDigit = 0;
        blinkDelay = 400;
        Number = 0;
        keytype = false;
        Sseg::BlankDisplay();
        Sseg::Scroll_Message("CALIbrAtion", WEIGHT, 6, ScrollMessageDelayMS, 1, false, true);
        helperMessage = "PLAtForm Id .   ";
        DELAY(500);
        while (true)
        {
            switch (pageState)
            {
            case CalibrationInitialize:
                currentLocation = WEIGHT;
                Sseg::Write_Message_To_Display("PFM=", WEIGHT, 6, true);
                Sseg::Write_Number_To_Display(Number, WEIGHT, false, 0, true, true, maxDigits, false, false);
                blinkDigit = Sseg::ReadDisplayBuffer(DisplayPos[currentLocation] + digitIndex);
                pageState = SelectPlatform;
                break;

            case SelectPlatform:
            case SelectCalibrationStandard:
            case SelectCalibratonType:
            case SelectCalibrationUnit:
            case SelectFirstAccuracy:
            case SelectSecondAccuracy:
            case SelectDecimalPointPosition:
            case EnterCalibrationLoad:
            case EnterFirstMax:
            case EnterSecondMax:
                Sseg::viewScrollMessage(helperMessage, TOTAL_PRICE, ScrollMessageDelayMS);
                Sseg::getNumber(digitsBuffer, keyCode, digitIndex, pow(10, maxDigits));
                if (keyCode)
                {
                    istringstream(digitsBuffer) >> Number;
                    Sseg::Write_Number_To_Display(Number, WEIGHT, false, 0, true, true, maxDigits, false, false);
                    keyCode = 0;
                    blinkDigit = Sseg::ReadDisplayBuffer(DisplayPos[currentLocation] + digitIndex);
                }
                Sseg::BlinkDigit(digitIndex, currentLocation, blinkDigit, blinkDelay);
                break;
            default:
                break;
            }
            Keyboard::readKeyBuffer(keyCode, keytype);
            if (keyCode)
            {
                Sseg::ResetBlinkTimer(blinkDelay);
                printf("key code = %d\n", keyCode);
            }
            switch (keyCode)
            {
            case KEY_ZERO:
                break;
            case KEY_RESAULT:
                switch (pageState)
                {

                case SelectPlatform:
                    if (Number <= MAX_PLATFORM_NUMBER && Number > 0)
                    {
                        currentPlatform = Number;
                        weightPlatforms[currentPlatform].platformId = currentPlatform;
                        generalTaks(SelectCalibrationStandard, 1, WEIGHT, "APPLAY EStAndArd .  ", "ESt=", 1);
                    }
                    break;
                case SelectCalibrationStandard:
                    if (Number <= 2 && Number > 0)
                    {
                        weightPlatforms[currentPlatform].hasEstandard = Number;
                        generalTaks(SelectCalibratonType, 1, WEIGHT, "CALIbrAtion typE .  ", "CtyP=", 1);
                    }
                    break;
                case SelectCalibratonType:
                    if (Number <= 2 && Number > 0)
                    {
                        weightPlatforms[currentPlatform].calibrationType = Number;
                        generalTaks(SelectCalibrationUnit, 1, WEIGHT, "CALIbrAtion Unit .  ", "CUnt=", 1);
                    }
                    break;
                case SelectCalibrationUnit:
                    if (Number <= weightPlatforms[currentPlatform].calibrationUnitMap.size())
                    {
                        weightPlatforms[currentPlatform].calibrationUnitIndex = Number;
                        generalTaks(SelectFirstAccuracy, 3, WEIGHT, "FirSt ACCUrACY .  ", "d1=", 1);
                    }
                    break;
                case SelectFirstAccuracy:
                    if (weightPlatforms[currentPlatform].validateAccuracy(Number))
                    {
                        weightPlatforms[currentPlatform].firstAccuracy = Number;
                        generalTaks(SelectSecondAccuracy, 3, WEIGHT, "Second ACCUrACY .  ", "d2=", 1);
                    }
                    break;
                case SelectSecondAccuracy:
                    if (weightPlatforms[currentPlatform].validateAccuracy(Number))
                    {
                        weightPlatforms[currentPlatform].secondAccuracy = Number;
                        generalTaks(SelectDecimalPointPosition, 1, WEIGHT, "dEcimAL Point .  ", "dp=", 1);
                    }
                    break;
                case SelectDecimalPointPosition:
                    if (Number <= weightPlatforms[currentPlatform].decimalPoint.size())
                    {
                        weightPlatforms[currentPlatform].decimalPointPosition = Number;
                        generalTaks(EnterCalibrationLoad, 4, WEIGHT, "CALIbrAtion LoAd .  ", "L=", 1);
                    }
                    break;
                }
                break;
            case KEY_TARE:
                digitIndex++;
                if (digitIndex == maxDigits)
                    digitIndex = 0;
                break;
                Sseg::Write_Number_To_Display(Number, WEIGHT, false, 0, true, true, maxDigits, false, false);
                blinkDigit = Sseg::ReadDisplayBuffer(DisplayPos[currentLocation] + digitIndex);
            default:
                break;
            }
        }
    };
}

/*
                        weightPlatforms[currentPlatform].platformId = currentPlatform;
                        weightPlatforms[currentPlatform].calibrationAdcOffset = 10000;
                        weightPlatforms[currentPlatform].calibrationLoad = 25000;
                        weightPlatforms[currentPlatform].calibrationUnitIndex = 2;
                        weightPlatforms[currentPlatform].decimalPointPosition = 3;
                        weightPlatforms[currentPlatform].firstAccuracy = 5;
                        weightPlatforms[currentPlatform].firstIntervalMax = 15000;
                        weightPlatforms[currentPlatform].isCalibrated = false;
                        weightPlatforms[currentPlatform].netAdc = 78000;
                        weightPlatforms[currentPlatform].secondAccuracy = 10;
                        weightPlatforms[currentPlatform].secondIntervalMax = 30000;
                        weightPlatforms[currentPlatform].weightFactor = 0.33;
                        weightPlatforms[currentPlatform].toJson();
                        dataSize = weightPlatforms[currentPlatform].serializedData.length();
                        cout << weightPlatforms[currentPlatform].serializedData << endl
                             << "size = " << dataSize << endl;
                        Storage::Save(CALIBRATION_PATH, weightPlatforms[currentPlatform].serializedData);
                        Storage::Load(CALIBRATION_PATH, weightPlatforms[currentPlatform].serializedData, dataSize);
                        weightPlatforms[currentPlatform].fromJson();
                        weightPlatforms[currentPlatform].toJson();
                        cout << weightPlatforms[currentPlatform].serializedData << endl;*/

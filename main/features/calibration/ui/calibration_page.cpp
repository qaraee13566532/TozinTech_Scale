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
#include <map>

using std::cout;
using std::endl;
using std::istringstream;
using std::map;
using std::string;

using namespace SSEG_DEVICE_DRIVER;
using namespace MATRIX_KEYBOARD;
using namespace GLOBAL_TIMER;
using namespace CALIBRATION;
using namespace STORAGE;

namespace CALIBRATION
{
    void CalibrationPage::generalSelectionsTaks(const map<uint8_t, uint32_t> valueMap, const map<uint8_t, string> helperMap, uint8_t pageState, uint8_t maxDigits, uint8_t currentLocation, string helperMessage, string nextPageTitle, uint32_t nextPageValue, bool showHelper)
    {
        CalibrationPage::pageState = pageState;
        Sseg::BlankDisplay();
        CalibrationPage::maxDigits = maxDigits;
        CalibrationPage::currentLocation = currentLocation;
        CalibrationPage::Number = nextPageValue;
        CalibrationPage::helperMessage = helperMessage;
        if (showHelper == true)
            Sseg::Write_Message_To_Display(helperMap.at(CalibrationPage::Number), UNIT_PRICE, 7, true);
        Sseg::Write_Message_To_Display(nextPageTitle, CalibrationPage::currentLocation, 6, true);
        Sseg::Write_Number_To_Display(valueMap.at(CalibrationPage::Number), CalibrationPage::currentLocation, false, 0, false, false, maxDigits, false, false);
    }

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
        enableToEntering = false;
        //    Sseg::Write_Number_To_Display(Number, CalibrationPage::currentLocation, false, 0, true, true, CalibrationPage::maxDigits, false, false);
    }

    void CalibrationPage::RunTasks(void)
    {

        pageState = CalibrationInitialize;
        currentPlatform = 0;
        keyCode = 0;
        digitIndex = 0;
        blinkDigit = 0;
        blinkDelay = 400;
        Number = 0;
        keytype = false;
        unsigned char selector = 0;
        map<uint8_t, string> empty;
        Sseg::Scroll_Message("CALIbrAtion", WEIGHT, 6, ScrollMessageDelayMS, 1, false, true);
                
        while (true)
        {
            switch (pageState)
            {
            case CalibrationInitialize:
                maxDigits = 1;
                Sseg::BlankDisplay();
                helperMessage = "PLAtForm Id .   ";
                currentLocation = WEIGHT;
                Sseg::Write_Message_To_Display("PFM=", WEIGHT, 6, true);
                Sseg::Write_Number_To_Display(Number, WEIGHT, false, 0, true, true, maxDigits, false, false);
                blinkDigit = Sseg::ReadDisplayBuffer(DisplayPos[currentLocation] + digitIndex);
                Sseg::Write_Number_To_Display(platformValueMap.at(selector), currentLocation, false, 0, false, false, maxDigits, false, false);
                enableToEntering = false;
                pageState = SelectPlatform;
                break;

            case SelectPlatform:
                Sseg::viewScrollMessage(helperMessage, TOTAL_PRICE, ScrollMessageDelayMS);
                if (keyCode)
                {
                    Sseg::selectItem(platformValueMap, empty, keyCode, currentLocation, maxDigits, Number, false);
                    keyCode = 0;
                }
                break;
            case SelectCalibrationStandard:
                Sseg::viewScrollMessage(helperMessage, TOTAL_PRICE, ScrollMessageDelayMS);
                if (keyCode)
                {
                    Sseg::selectItem(standardValueMap, standardHelperMap, keyCode, currentLocation, maxDigits, Number, true);
                    keyCode = 0;
                }
                break;
            case SelectCalibratonType:
                Sseg::viewScrollMessage(helperMessage, TOTAL_PRICE, ScrollMessageDelayMS);
                if (keyCode)
                {
                    Sseg::selectItem(calTypeValueMap, calTypeHelperMap, keyCode, currentLocation, maxDigits, Number, true);
                    keyCode = 0;
                }
                break;
            case SelectCalibrationUnit:
                Sseg::viewScrollMessage(helperMessage, TOTAL_PRICE, ScrollMessageDelayMS);
                if (keyCode)
                {
                    Sseg::selectItem(unitValueMap, unitHelperMap, keyCode, currentLocation, maxDigits, Number, true);
                    keyCode = 0;
                }
                break;
            case SelectFirstAccuracy:
                Sseg::viewScrollMessage(helperMessage, TOTAL_PRICE, ScrollMessageDelayMS);
                if (keyCode)
                {
                    Sseg::selectItem(accuracyValueMap, empty, keyCode, currentLocation, maxDigits, Number, false);
                    keyCode = 0;
                }
                break;
            case SelectSecondAccuracy:
                Sseg::viewScrollMessage(helperMessage, TOTAL_PRICE, ScrollMessageDelayMS);
                if (keyCode)
                {
                    Sseg::selectItem(accuracyValueMap, empty, keyCode, currentLocation, maxDigits, Number, false);
                    keyCode = 0;
                }
                break;
            case SelectDecimalPointPosition:
                Sseg::viewScrollMessage(helperMessage, TOTAL_PRICE, ScrollMessageDelayMS);
                if (keyCode)
                {
                    Sseg::selectItem(decimalpointValueMap, decimalpointHelperMap, keyCode, currentLocation, maxDigits, Number, true);
                    keyCode = 0;
                }
                break;
            case SaveZeroPoint:
                Sseg::viewScrollMessage(helperMessage, TOTAL_PRICE, ScrollMessageDelayMS);
                break;
            case DoCalibration:
                Sseg::viewScrollMessage(helperMessage, TOTAL_PRICE, ScrollMessageDelayMS);
                break;
            case EnterCalibrationLoad:
            case EnterFirstMax:
            case EnterSecondMax:
                if (keyCode == KEY_TARE && enableToEntering == false)
                {
                    enableToEntering = true;
                    keyCode = 0;
                    Sseg::Write_Number_To_Display(Number, WEIGHT, false, 0, true, true, maxDigits, false, false);
                }
                Sseg::viewScrollMessage(helperMessage, TOTAL_PRICE, ScrollMessageDelayMS);
                if (enableToEntering == true)
                {
                    Sseg::getNumber(digitsBuffer, keyCode, digitIndex, pow(10, maxDigits));
                    if (keyCode)
                    {
                        istringstream(digitsBuffer) >> Number;
                        Sseg::Write_Number_To_Display(Number, WEIGHT, false, 0, true, true, maxDigits, false, false);
                        keyCode = 0;
                        blinkDigit = Sseg::ReadDisplayBuffer(DisplayPos[currentLocation] + digitIndex);
                    }
                    Sseg::BlinkDigit(digitIndex, currentLocation, blinkDigit, blinkDelay);
                }

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
                    currentPlatform = Number;
                    weightPlatforms[currentPlatform].platformId = currentPlatform;
                    generalSelectionsTaks(standardValueMap, standardHelperMap, SelectCalibrationStandard, 1, WEIGHT, "APPLAY EStAndArd .  ", "ESt=", 0, true);
                    break;
                case SelectCalibrationStandard:
                    weightPlatforms[currentPlatform].hasEstandard = Number;
                    generalSelectionsTaks(calTypeValueMap, calTypeHelperMap, SelectCalibratonType, 1, WEIGHT, "CALIbrAtion typE .  ", "CtyP=", 0, true);
                    break;
                case SelectCalibratonType:
                    weightPlatforms[currentPlatform].calibrationType = Number;
                    generalSelectionsTaks(unitValueMap, unitHelperMap, SelectCalibrationUnit, 1, WEIGHT, "CALIbrAtion Unit .  ", "CUnt=", 0, true);
                    break;
                case SelectCalibrationUnit:
                    weightPlatforms[currentPlatform].calibrationUnitIndex = Number;
                    generalSelectionsTaks(accuracyValueMap, empty, SelectFirstAccuracy, 2, WEIGHT, "FirSt ACCUrACY .  ", "d1=", 0, false);

                    break;
                case SelectFirstAccuracy:
                    weightPlatforms[currentPlatform].firstAccuracy = Number;
                    generalSelectionsTaks(accuracyValueMap, empty, SelectSecondAccuracy, 2, WEIGHT, "SEcond ACCUrACY .  ", "d2=", 0, false);
                    break;
                case SelectSecondAccuracy:
                    weightPlatforms[currentPlatform].secondAccuracy = Number;
                    generalSelectionsTaks(decimalpointValueMap, decimalpointHelperMap, SelectDecimalPointPosition, 1, WEIGHT, "dEcimAL Point .  ", "dp=", 0, true);
                    break;
                case SelectDecimalPointPosition:
                    weightPlatforms[currentPlatform].decimalPointPosition = Number;
                    generalTaks(EnterCalibrationLoad, 6, WEIGHT, "CALIbrAtion LoAd .  ", "AdLoAd", 0);
                    break;
                case EnterCalibrationLoad:
                    weightPlatforms[currentPlatform].calibrationLoad = Number;
                    generalTaks(EnterFirstMax, 6, WEIGHT, "FIrSt mAX .  ", "Full-1", 0);
                    break;
                case EnterFirstMax:
                    weightPlatforms[currentPlatform].decimalPointPosition = Number;
                    generalTaks(EnterSecondMax, 6, WEIGHT, "SECOnd mAX .  ", "Full-2", 0);
                    break;
                case EnterSecondMax:
                    weightPlatforms[currentPlatform].decimalPointPosition = Number;
                    generalTaks(SaveZeroPoint, 6, WEIGHT, "SEt ZEro .  ", "noLoAd", 0);
                    break;
                case SaveZeroPoint:
                    weightPlatforms[currentPlatform].setZero();
                    generalTaks(DoCalibration, 6, WEIGHT, "CALIbrAtion .   ", "-VAIt-", 0);
                    break;
                case DoCalibration:
                    pageState = CalibrationInitialize;
                    break;
                }
                break;
            case KEY_TARE:
                if (enableToEntering == true)
                {
                    digitIndex++;
                    if (digitIndex == maxDigits)
                        digitIndex = 0;
                }
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

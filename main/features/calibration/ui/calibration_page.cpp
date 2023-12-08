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
#include "core/device_driver/adc_ads1232/adc.h"
#include <map>
#include <future>
#include <core/device_driver/gpio/gpio.h>

using std::cout;
using std::endl;
using std::future;
using std::istringstream;
using std::map;
using std::string;

using namespace SSEG_DEVICE_DRIVER;
using namespace MATRIX_KEYBOARD;
using namespace GLOBAL_TIMER;
using namespace CALIBRATION;
using namespace STORAGE;
using namespace ADC_ADS1232;
using namespace GPIO;

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
        CalibrationPage::showHelper = showHelper;
        if (showHelper == true)
            Sseg::Write_Message_To_Display(helperMap.at(CalibrationPage::Number), UNIT_PRICE, 7, true);
        Sseg::Write_Message_To_Display(nextPageTitle, CalibrationPage::currentLocation, 6, true);
        Sseg::Write_Number_To_Display(valueMap.at(CalibrationPage::Number), CalibrationPage::currentLocation, false, 0, false, false, maxDigits, false, false);
        CalibrationPage::valueMap = valueMap;
        CalibrationPage::helperMap = helperMap;
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
    }

    void CalibrationPage::RunTasks(void)
    {
        std::future<void> f1;
        pageState = CalibrationInitialize;
        currentPlatform = 0;
        keyCode = 0;
        digitIndex = 0;
        blinkDigit = 0;
        blinkDelay = 400;
        Number = 0;
        weightReady = false;
        keytype = false;
        isCalibrated = false;
        map<uint8_t, string> empty;
        Sseg::Scroll_Message("CALIbrAtion", WEIGHT, 6, ScrollMessageDelayMS, 1, false, true);

        while (true)
        {
            if (Gpio::readCalibrationSwitchStatus()==false)
            {
                if (weightPlatforms[currentPlatform].isCalibrationSaved == false && pageState == DoCalibration && weightPlatforms[currentPlatform].isCalibrated)
                {
                    Gpio::TurnBuzzerOn(500);
                    weightPlatforms[currentPlatform].toJson();
                    Storage::Save(CALIBRATION_PATH, weightPlatforms[currentPlatform].serializedData);
                    weightPlatforms[currentPlatform].isCalibrationSaved = true;
                }
            }
            if (pageState > CalibrationInitialize)
                Sseg::viewScrollMessage(helperMessage, TOTAL_PRICE, ScrollMessageDelayMS);
            switch (pageState)
            {
            case CalibrationInitialize:
                generalSelectionsTaks(platformValueMap, empty, SelectCalibrationStandard, 1, WEIGHT, "PLAtForm Id .   ", "PFM=", 0, false);
                enableToEntering = false;
                pageState = SelectPlatform;
                break;
            case SelectPlatform:
            case SelectCalibrationStandard:
            case SelectCalibratonType:
            case SelectCalibrationUnit:
            case SelectFirstAccuracy:
            case SelectSecondAccuracy:
            case SelectDecimalPointPosition:
                if (keyCode)
                {
                    Sseg::selectItem(valueMap, helperMap, keyCode, currentLocation, maxDigits, Number, showHelper);
                    keyCode = 0;
                }
                break;
            case DoCalibration:
                weightPlatforms[currentPlatform].performCalibration(calibProgress, weightReady);
                if (weightReady)
                {

                    weightReady = false;
                    if (weightPlatforms[currentPlatform].isCalibrated == true)
                    {
                        isCalibrated = true;
                        weightPlatforms[currentPlatform].calcWeight();
                        Sseg::Write_Number_To_Display(weightPlatforms[currentPlatform].weight, WEIGHT, true, weightPlatforms[currentPlatform].decimalPointPosition, true, true, 6, false, false);
                    }
                    else
                        Sseg::Write_Number_To_Display(calibProgress, WEIGHT, false, 0, false, false, 1, false, false);
                }
                break;
            case EnterCalibrationLoad:
            case EnterFirstMax:
            case EnterSecondMax:
                if (keyCode == KEY_TARE && enableToEntering == false)
                {
                    enableToEntering = true;
                    keyCode = 0;
                    Sseg::Write_Number_To_Display(Number, WEIGHT, true, weightPlatforms[currentPlatform].decimalPointPosition, true, true, maxDigits, false, false);
                    blinkDigit = Sseg::ReadDisplayBuffer(DisplayPos[currentLocation] + digitIndex);
                }
                if (enableToEntering == true)
                {
                    Sseg::getNumber(digitsBuffer, keyCode, digitIndex, pow(10, maxDigits));
                    if (keyCode)
                    {
                        istringstream(digitsBuffer) >> Number;
                        Sseg::Write_Number_To_Display(Number, WEIGHT, true, weightPlatforms[currentPlatform].decimalPointPosition, true, true, maxDigits, false, false);
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
                weightPlatforms[currentPlatform]
                    .setZero();
                break;
            case KEY_MUL:
                if (pageState == DoCalibration)
                {
                    isCalibrated = false;
                    weightPlatforms[currentPlatform].InitCalibration(calibProgress);
                    generalTaks(DoCalibration, 1, WEIGHT, "CALIbrAtion .   ", "P=", weightPlatforms[currentPlatform].calibProgress);
                }
                break;
            case KEY_ADD:
                isCalibrated = false;
                weightPlatforms[currentPlatform].InitCalibration(calibProgress);
                generalTaks(EnterCalibrationLoad, 6, WEIGHT, "CALIbrAtion LoAd .  ", "AdLoAd", weightPlatforms[currentPlatform].calibrationLoad);
                break;
            case KEY_FUNC:
                isCalibrated = false;
                weightPlatforms[currentPlatform].InitCalibration(calibProgress);
                generalTaks(SaveZeroPoint, 6, WEIGHT, "SEt ZEro .  ", "noLoAd", 0);
                break;
            case KEY_RESAULT:
                switch (pageState)
                {
                case SelectPlatform:

                    currentPlatform = Number;
                    weightPlatforms[currentPlatform].platformId = currentPlatform;
                    Storage::Load(CALIBRATION_PATH, weightPlatforms[currentPlatform].serializedData, 1024);
                    weightPlatforms[currentPlatform].fromJson();
                    printf("load serilize = %s\n", weightPlatforms[currentPlatform].serializedData.c_str());
                    generalSelectionsTaks(standardValueMap, standardHelperMap, SelectCalibrationStandard, 1, WEIGHT, "APPLAY EStAndArd .  ", "ESt=", weightPlatforms[currentPlatform].calibrationStandardIndex, true);

                    break;
                case SelectCalibrationStandard:
                    weightPlatforms[currentPlatform].calibrationStandardIndex = Number;
                    generalSelectionsTaks(calTypeValueMap, calTypeHelperMap, SelectCalibratonType, 1, WEIGHT, "CALIbrAtion typE .  ", "CtyP=", weightPlatforms[currentPlatform].loadcellTypeIndex, true);
                    break;
                case SelectCalibratonType:
                    weightPlatforms[currentPlatform].loadcellTypeIndex = Number;
                    generalSelectionsTaks(unitValueMap, unitHelperMap, SelectCalibrationUnit, 1, WEIGHT, "CALIbrAtion Unit .  ", "CUnt=", weightPlatforms[currentPlatform].calibrationUnitIndex, true);
                    break;
                case SelectCalibrationUnit:
                    weightPlatforms[currentPlatform].calibrationUnitIndex = Number;
                    if (weightPlatforms[currentPlatform].loadcellTypeIndex == 0)
                        generalSelectionsTaks(accuracyValueMap, empty, SelectFirstAccuracy, 2, WEIGHT, "ACCUrACY .  ", "d=", weightPlatforms[currentPlatform].firstAccuracy, false);
                    else
                        generalSelectionsTaks(accuracyValueMap, empty, SelectFirstAccuracy, 2, WEIGHT, "FirSt ACCUrACY .  ", "d1=", weightPlatforms[currentPlatform].firstAccuracy, false);
                    break;
                case SelectFirstAccuracy:
                    weightPlatforms[currentPlatform].firstAccuracy = Number;
                    if (weightPlatforms[currentPlatform].loadcellTypeIndex == 0)
                        generalSelectionsTaks(decimalpointValueMap, decimalpointHelperMap, SelectDecimalPointPosition, 1, WEIGHT, "dEcimAL Point .  ", "dp=", 0, true);
                    else
                        generalSelectionsTaks(accuracyValueMap, empty, SelectSecondAccuracy, 2, WEIGHT, "SEcond ACCUrACY .  ", "d2=", weightPlatforms[currentPlatform].secondAccuracy, false);
                    break;
                case SelectSecondAccuracy:
                    weightPlatforms[currentPlatform].secondAccuracy = Number;
                    generalSelectionsTaks(decimalpointValueMap, decimalpointHelperMap, SelectDecimalPointPosition, 1, WEIGHT, "dEcimAL Point .  ", "dp=", weightPlatforms[currentPlatform].decimalPointPosition, true);
                    break;
                case SelectDecimalPointPosition:
                    weightPlatforms[currentPlatform].decimalPointPosition = Number;
                    if (weightPlatforms[currentPlatform].loadcellTypeIndex == 0)
                        generalTaks(EnterFirstMax, 6, WEIGHT, "mAX VEigHt .  ", " Full ", weightPlatforms[currentPlatform].firstIntervalMax);
                    else
                        generalTaks(EnterFirstMax, 6, WEIGHT, "FIrSt mAX .  ", "Full-1", weightPlatforms[currentPlatform].firstIntervalMax);
                    break;
                case EnterFirstMax:
                    weightPlatforms[currentPlatform].firstIntervalMax = Number;
                    if (weightPlatforms[currentPlatform].loadcellTypeIndex == 0)
                        generalTaks(SaveZeroPoint, 6, WEIGHT, "SEt ZEro .  ", "noLoAd", 0);
                    else
                        generalTaks(EnterSecondMax, 6, WEIGHT, "SECOnd mAX .  ", "Full-2", weightPlatforms[currentPlatform].secondIntervalMax);
                    break;
                case EnterSecondMax:
                    weightPlatforms[currentPlatform].secondIntervalMax = Number;
                    generalTaks(SaveZeroPoint, 6, WEIGHT, "SEt ZEro .  ", "noLoAd", 0);
                    break;
                case SaveZeroPoint:
                    weightPlatforms[currentPlatform].setZero();
                    generalTaks(EnterCalibrationLoad, 6, WEIGHT, "CALIbrAtion LoAd .  ", "AdLoAd", weightPlatforms[currentPlatform].calibrationLoad);
                    break;
                case EnterCalibrationLoad:
                    weightPlatforms[currentPlatform].calibrationLoad = Number;
                    weightPlatforms[currentPlatform].InitCalibration(calibProgress);
                    generalTaks(DoCalibration, 1, WEIGHT, "CALIbrAtion .   ", "P=", weightPlatforms[currentPlatform].calibProgress);
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
                                        currentPlatform = 0;

                weightPlatforms[currentPlatform].platformId = currentPlatform;
                weightPlatforms[currentPlatform].calibrationStandardIndex = 1;
                weightPlatforms[currentPlatform].loadcellTypeIndex = 2;
                weightPlatforms[currentPlatform].calibrationUnitIndex = 2;
                weightPlatforms[currentPlatform].firstAccuracy = 2;
                weightPlatforms[currentPlatform].secondAccuracy = 3;
                weightPlatforms[currentPlatform].decimalPointPosition = 3;
                weightPlatforms[currentPlatform].firstIntervalMax = 15000;
                weightPlatforms[currentPlatform].secondIntervalMax = 30000;
                weightPlatforms[currentPlatform].calibrationAdcOffset = 65200;
                weightPlatforms[currentPlatform].calibrationLoad = 25000;
                weightPlatforms[currentPlatform].weightFactor = 0.33;
                weightPlatforms[currentPlatform].isCalibrated = false;
                weightPlatforms[currentPlatform].netAdc = 78000;
                weightPlatforms[currentPlatform].toJson();
                dataSize = weightPlatforms[currentPlatform].serializedData.length();
                cout << weightPlatforms[currentPlatform].serializedData << endl
                     << "size = " << dataSize << endl;
                Storage::Save(CALIBRATION_PATH, weightPlatforms[currentPlatform].serializedData);
                Storage::Load(CALIBRATION_PATH, weightPlatforms[currentPlatform].serializedData, dataSize);
                weightPlatforms[currentPlatform].fromJson();
                weightPlatforms[currentPlatform].toJson();
                cout << weightPlatforms[currentPlatform].serializedData << endl;*/

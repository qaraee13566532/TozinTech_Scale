#include <iostream>
#include "core/calibration/usecase/calibration.h"
#include "core/weight/weight.h"
#include "core/device_driver/adc_ads1232/adc.h"
#include "math.h"
#include "cJSON.h"
#include <map>
#include "core/device_driver/timer/timer.h"
#include "core/weight/weight.h"
#include "core/device_driver/storage/storage.h"

using std::cout;
using std::endl;
using std::map;
using std::runtime_error;
using std::string;

using namespace ADC_ADS1232;
using namespace GLOBAL_TIMER;
using namespace STORAGE;

namespace CALIBRATION
{
    void Calibration::toJson()
    {
        cjson = cJSON_CreateObject();
        cJSON_AddNumberToObject(cjson, "platformId", platformId);
        cJSON_AddNumberToObject(cjson, "calibrationStandart", calibrationStandardIndex);
        cJSON_AddNumberToObject(cjson, "loadcellType", loadcellTypeIndex);
        cJSON_AddNumberToObject(cjson, "calibrationUnit", calibrationUnitIndex);
        cJSON_AddNumberToObject(cjson, "firstAccuracy", firstAccuracy);
        cJSON_AddNumberToObject(cjson, "secondAccuracy", secondAccuracy);
        cJSON_AddNumberToObject(cjson, "decimalPointPosition", decimalPointPosition);
        cJSON_AddNumberToObject(cjson, "firstIntervalMax", firstIntervalMax);
        cJSON_AddNumberToObject(cjson, "secondIntervalMax", secondIntervalMax);
        cJSON_AddNumberToObject(cjson, "adcOffset", adcOffset);
        cJSON_AddNumberToObject(cjson, "calibrationLoad", calibrationLoad);
        cJSON_AddNumberToObject(cjson, "weightFactor", weightFactor);
        isCalibrated == true ? cJSON_AddTrueToObject(cjson, "isCalibrated") : cJSON_AddFalseToObject(cjson, "isCalibrated");
        cJSON_AddNumberToObject(cjson, "netAdc", netAdc);
        serializedData = cJSON_Print(cjson);
        cJSON_Delete(cjson);
    }
    int8_t Calibration::getStringKey(map<uint8_t, string> map, string value)
    {
        for (auto entry : map)
        {
            if (entry.second == cJSON_GetObjectItem(cjson, value.c_str())->valuestring)
                return entry.first;
        }
        return -1;
    }
    int8_t Calibration::getIntegerKey(map<uint8_t, uint32_t> map, uint32_t value)
    {
        for (auto entry : map)
        {
            if (entry.second == cJSON_GetObjectItem(cjson, std::to_string(value).c_str())->valueint)
                return entry.first;
        }
        return -1;
    }
    void Calibration::fromJson()
    {
        cjson = cJSON_Parse(serializedData.c_str());
        if (cJSON_GetObjectItem(cjson, "platformId"))
            platformId = cJSON_GetObjectItem(cjson, "platformId")->valueint;
        if (cJSON_GetObjectItem(cjson, "calibrationStandart"))
            calibrationStandardIndex = cJSON_GetObjectItem(cjson, "calibrationStandart")->valueint;
        if (cJSON_GetObjectItem(cjson, "loadcellType"))
            loadcellTypeIndex = cJSON_GetObjectItem(cjson, "loadcellType")->valueint;
        if (cJSON_GetObjectItem(cjson, "calibrationUnit"))
            calibrationUnitIndex = cJSON_GetObjectItem(cjson, "calibrationUnit")->valueint;
        if (cJSON_GetObjectItem(cjson, "firstAccuracy"))
            firstAccuracy = cJSON_GetObjectItem(cjson, "firstAccuracy")->valueint;
        if (cJSON_GetObjectItem(cjson, "secondAccuracy"))
            secondAccuracy = cJSON_GetObjectItem(cjson, "secondAccuracy")->valueint;
        if (cJSON_GetObjectItem(cjson, "decimalPointPosition"))
            decimalPointPosition = cJSON_GetObjectItem(cjson, "decimalPointPosition")->valueint;
        if (cJSON_GetObjectItem(cjson, "firstIntervalMax"))
            firstIntervalMax = cJSON_GetObjectItem(cjson, "firstIntervalMax")->valueint;
        if (cJSON_GetObjectItem(cjson, "secondIntervalMax"))
            secondIntervalMax = cJSON_GetObjectItem(cjson, "secondIntervalMax")->valueint;
        if (cJSON_GetObjectItem(cjson, "adcOffset"))
            adcOffset = cJSON_GetObjectItem(cjson, "adcOffset")->valueint;
        if (cJSON_GetObjectItem(cjson, "calibrationLoad"))
            calibrationLoad = cJSON_GetObjectItem(cjson, "calibrationLoad")->valueint;
        if (cJSON_GetObjectItem(cjson, "weightFactor"))
            weightFactor = cJSON_GetObjectItem(cjson, "weightFactor")->valuedouble;
        if (cJSON_GetObjectItem(cjson, "isCalibrated"))
            isCalibrated = cJSON_GetObjectItem(cjson, "isCalibrated")->valueint;
        if (cJSON_GetObjectItem(cjson, "netAdc"))
            netAdc = cJSON_GetObjectItem(cjson, "netAdc")->valueint;
        cJSON_Delete(cjson);
    }
    void Calibration::calcWeight(void)
    {
        netAdc = Adc::filterdRawAdc[platformId] - adcOffset;
        weight = weightFactor * netAdc;
    }
    void Calibration ::InitCalibration(uint8_t &Progress)
    {
        isCalibrationSaved = false;
        Timer::freeRuningTimerMS = 1000;
        calibProgress = 5;
        Progress = calibProgress;
        isCalibrated = false;
    }
    bool Calibration::loadParameters(void)
    {
        Storage::Load(CALIBRATION_PATH,serializedData, 1024);
        fromJson();
        return true;
    }
    void Calibration ::performCalibration(uint8_t &Progress, bool &update)
    {
        if (Adc::isAdcDataReceived[platformId] == true)
        {
            Adc::isAdcDataReceived[platformId] = false;
            update = true;
            if (isCalibrated == false)
            {
                try
                {
                    double realCalibrationLoad = calibrationLoad * pow(10, 3 - decimalPointPosition);
                    netAdc = Adc::filterdRawAdc[platformId] - adcOffset;
                    if (netAdc <= 64)
                        throw runtime_error("! The ADC digital number is low or negative .");
                    if (calibrationLoad == 0)
                        throw runtime_error("! Calibration load is zero.");
                    weight = weightFactor * netAdc;
              //      printf("weight = %f  -- calibrationLoad = %ld  --  accuracyMap = %d -- abs = %f\n", weight, calibrationLoad, accuracyMap.at(firstAccuracy), fabs(weight - calibrationLoad));
                    if (fabs(weight - calibrationLoad) <= accuracyMap.at(firstAccuracy))
                    {
                        if (Timer::freeRuningTimerMS == 0)
                        {
                            Timer::freeRuningTimerMS = 1000;
                            calibProgress--;
                            Progress = calibProgress;
                            if (calibProgress == 0)
                            {
                                isCalibrated = true;
                                isCalibrationSaved = false;
                            }
                        }
                    }
                    else
                    {
                        weightFactor = realCalibrationLoad / netAdc;
                        InitCalibration(Progress);
                    }
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
        }
    }

    void Calibration::setZero(void)
    {
        adcOffset = Adc::filterdRawAdc[platformId];
    }
}
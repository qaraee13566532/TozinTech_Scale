#include <iostream>
#include "features/calibration/usecase/calibration.h"
#include "features/weight/weight.h"
#include "core/device_driver/adc_ads1232/adc.h"
#include "math.h"
#include "cJSON.h"
#include <map>

using std::cout;
using std::endl;
using std::map;
using std::runtime_error;
using std::string;

using namespace ADC_ADS1232;

namespace CALIBRATION
{
    void Calibration::toJson()
    {
        cjson = cJSON_CreateObject();
        cJSON_AddNumberToObject(cjson, "platformId", platformId);
        cJSON_AddNumberToObject(cjson, "firstIntervalMax", firstIntervalMax);
        cJSON_AddNumberToObject(cjson, "secondIntervalMax", secondIntervalMax);
        cJSON_AddNumberToObject(cjson, "calibrationAdcOffset", calibrationAdcOffset);
        cJSON_AddNumberToObject(cjson, "calibrationLoad", calibrationLoad);
        cJSON_AddNumberToObject(cjson, "weightFactor", weightFactor);
        cJSON_AddNumberToObject(cjson, "firstAccuracy", firstAccuracy);
        cJSON_AddNumberToObject(cjson, "secondAccuracy", secondAccuracy);
        cJSON_AddNumberToObject(cjson, "decimalPointPosition", decimalPointPosition);
        cJSON_AddStringToObject(cjson, "calibrationUnit", calibrationUnitMap.at(calibrationUnitIndex).c_str());
        isCalibrated == true ? cJSON_AddTrueToObject(cjson, "isCalibrated") : cJSON_AddFalseToObject(cjson, "isCalibrated");
        hasEstandard == true ? cJSON_AddTrueToObject(cjson, "hasEstandard") : cJSON_AddFalseToObject(cjson, "hasEstandard");
        cJSON_AddStringToObject(cjson, "calibrationType", calibrationTypeMap.at(calibrationType).c_str());

        cJSON_AddNumberToObject(cjson, "netAdc", netAdc);
        serializedData = cJSON_Print(cjson);
        cJSON_Delete(cjson);
    }
    void Calibration::fromJson()
    {
        cjson = cJSON_Parse(serializedData.c_str());
        if (cJSON_GetObjectItem(cjson, "platformId"))
            platformId = cJSON_GetObjectItem(cjson, "platformId")->valueint;
        if (cJSON_GetObjectItem(cjson, "firstIntervalMax"))
            firstIntervalMax = cJSON_GetObjectItem(cjson, "firstIntervalMax")->valueint;
        if (cJSON_GetObjectItem(cjson, "secondIntervalMax"))
            secondIntervalMax = cJSON_GetObjectItem(cjson, "secondIntervalMax")->valueint;
        if (cJSON_GetObjectItem(cjson, "calibrationAdcOffset"))
            calibrationAdcOffset = cJSON_GetObjectItem(cjson, "calibrationAdcOffset")->valueint;
        if (cJSON_GetObjectItem(cjson, "calibrationLoad"))
            calibrationLoad = cJSON_GetObjectItem(cjson, "calibrationLoad")->valueint;
        if (cJSON_GetObjectItem(cjson, "weightFactor"))
            weightFactor = cJSON_GetObjectItem(cjson, "weightFactor")->valuedouble;
        if (cJSON_GetObjectItem(cjson, "firstAccuracy"))
            firstAccuracy = cJSON_GetObjectItem(cjson, "firstAccuracy")->valueint;
        if (cJSON_GetObjectItem(cjson, "secondAccuracy"))
            secondAccuracy = cJSON_GetObjectItem(cjson, "secondAccuracy")->valueint;
        if (cJSON_GetObjectItem(cjson, "decimalPointPosition"))
            decimalPointPosition = cJSON_GetObjectItem(cjson, "decimalPointPosition")->valueint;
        if (cJSON_GetObjectItem(cjson, "calibrationType"))
            calibrationType = cJSON_GetObjectItem(cjson, "decimalPointPosition")->valueint;
        if (cJSON_GetObjectItem(cjson, "calibrationUnit"))
        {
            for (auto entry : calibrationUnitMap)
            {
                if (entry.second == cJSON_GetObjectItem(cjson, "calibrationUnit")->valuestring)
                {
                    decimalPointPosition = entry.first;
                    break; // Exit from the loop.
                }
            }
        }
        if (cJSON_GetObjectItem(cjson, "isCalibrated"))
            isCalibrated = cJSON_GetObjectItem(cjson, "isCalibrated")->valueint;
        if (cJSON_GetObjectItem(cjson, "hasEstandard"))
            hasEstandard = cJSON_GetObjectItem(cjson, "hasEstandard")->valueint;
        if (cJSON_GetObjectItem(cjson, "netAdc"))
            netAdc = cJSON_GetObjectItem(cjson, "netAdc")->valueint;
        cJSON_Delete(cjson);
    }
    bool Calibration ::validateAccuracy(uint32_t value)
    {
        if (value == 1 || value == 2 || value == 5 || value == 10 || value == 20 || value == 25 ||
            value == 50 || value == 100 || value == 200 || value == 250 || value == 500 )
        {
            return true;
        }
        else
            return false;
    }
    void Calibration ::performCalibration(void)
    {
        if (platformId >= MAX_PLATFORM_NUMBER)
            throw runtime_error("! Unkown platform ID .");
        if (netAdc < 0)
            throw runtime_error("! Adc is Negative .");
        if (decimalPointPosition > 3)
            throw runtime_error("!Unkown decimal point16_t .");
        if (calibrationLoad == 0)
            throw runtime_error("!Unkown calibration load .");
        while (Adc::isAdcDataReceived[platformId] == false)
        {
            Adc::isAdcDataReceived[platformId] = false;
            double realCalibrationLoad = calibrationLoad * pow(10, 3 - decimalPointPosition);
            weightFactor = realCalibrationLoad / netAdc;
        }
    }

    void Calibration::setZero(void)
    {
        if (platformId == 0 || platformId > 2)
            throw runtime_error("Exception in platform ID .");
        if (Adc::isAdcNegative)
            throw runtime_error("!Negative ADC number .");
        calibrationAdcOffset = Adc::rawAdc[platformId];
    }
}
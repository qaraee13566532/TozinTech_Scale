#include <iostream>
#include "features/calibration/usecase/calibration.h"
#include "features/weight/weight.h"
#include "core/device_driver/adc_ads1232/adc.h"
#include "math.h"

using std::cout;
using std::endl;
using std::runtime_error;
using namespace ADC_ADS1232;

namespace CALIBRATION
{
    void Calibration ::performCalibration(void)
    {
        if (_platformId == 0 || _platformId > 2)
            throw runtime_error("! Unkown platform ID .");
        if (netAdc < 0)
            throw runtime_error("! Adc is Negative .");
        if (decimalPointPosition > 3)
            throw runtime_error("!Unkown decimal point .");
        if (calibrationLoad == 0)
            throw runtime_error("!Unkown calibration load .");
        while (Adc::isAdcDataReceived[_platformId] == false)
        {
            Adc::isAdcDataReceived[_platformId] = false;
            double realCalibrationLoad = calibrationLoad * pow(10, 3 - decimalPointPosition);
            weightFactor = realCalibrationLoad / netAdc;
        }
    }

    void Calibration::setZero(void)
    {
        if (_platformId == 0 || _platformId > 2)
            throw runtime_error("Exception in platform ID .");
        if (Adc::isAdcNegative)
            throw runtime_error("!Negative ADC number .");
        calibrationAdcOffset = Adc::rawAdc[_platformId];
    }
}
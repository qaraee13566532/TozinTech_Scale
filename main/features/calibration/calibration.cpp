#include <iostream>
#include "features/calibration/calibration.h"
#include "features/weight/weight.h"
#include "core/device_driver/adc_ads1232/adc.h"
#include "math.h"

using std::cout;
using std::endl;
using std::runtime_error;
using namespace ADC_ADS1232;

namespace CALIBRATION
{

    void Calibration ::performCalibration(unsigned char platformId)
    {
        if (platformId == 0 || platformId > 2)
            throw runtime_error("Exception in platform ID .");
        if (Adc::isAdcDataReceived[platformId])
        {
            Adc::isAdcDataReceived[platformId] = 0;
            double realCalibrationLoad = calibrationLoad * pow(10, 3 - (decimalPointPosition % 3));
            weightFactor = realCalibrationLoad / Adc::netAdc[platformId];
        }
    }

}
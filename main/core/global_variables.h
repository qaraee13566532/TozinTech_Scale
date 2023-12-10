#pragma once

#include "core/weight/weight.h"
#include "core/calibration/usecase/calibration.h"
#include "core//device_driver/adc_ads1232/adc.h"

using namespace ADS1232_WEIGHT;
using namespace CALIBRATION;


Weight weights[MAX_PLATFORM_NUMBER];
Calibration weightPlatforms[MAX_PLATFORM_NUMBER];



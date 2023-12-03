#pragma once

#include "features/weight/weight.h"
#include "features/calibration/usecase/calibration.h"
#include "core//device_driver/adc_ads1232/adc.h"

using namespace ADS1232_WEIGHT;
using namespace CALIBRATION;

Weight firstPlatformWeight();
Weight secondPlatformWeight();
Calibration weightPlatforms[MAX_PLATFORM_NUMBER];



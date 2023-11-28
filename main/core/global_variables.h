#pragma once

#include "features/weight/weight.h"
#include "features/calibration/usecase/calibration.h"

using namespace ADS1232_WEIGHT;
using namespace CALIBRATION;

Weight firstPlatformWeight();
Weight secondPlatformWeight();
Calibration firstPlatform(0);
Calibration secondPlatform(1);

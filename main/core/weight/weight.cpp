#include <core/device_driver/gpio/gpio.h>
#include "core/weight/weight.h"
#include <rom/ets_sys.h>
#include <esp_system.h>
#include "core/weight/weight.h"
#include "definations.h"
#include "core/calibration/usecase/calibration.h"
#include "core/device_driver/adc_ads1232/adc.h"

using namespace CALIBRATION;
using namespace ADC_ADS1232;

extern Calibration weightPlatforms[MAX_PLATFORM_NUMBER];

namespace ADS1232_WEIGHT
{
    bool Weight::CalcWeight(void)
    {
        if (Adc::isAdcDataReceived[platformId] == true)
        {
            Adc::isAdcDataReceived[platformId] = false;
            RemoveDrift();
            CheckStability();
            netAdc = Adc::filterdRawAdc[platformId] - adcOffset;
            weight = weightFactor * netAdc;
            roundedWeight = weight;
            if (isRoundingEnabled == true)
            {
                if (weight <= firstIntervalMax)
                    division = accuracyMap.at(firstAccuracy);
                else
                    division = accuracyMap.at(secondAccuracy);
                roundedWeight > 0 ? roundedWeight += (division / 2) : roundedWeight -= (division / 2);
                roundedWeight /= division;
                roundedWeight *= division;
            }
            if (roundedWeight == 0)
                isWeightZero = true;
            else
                isWeightZero = false;
            if (taredWeight > 0)
                isNetWeight = true;
            else
                isNetWeight = false;
            if (roundedWeight > (int32_t)firstIntervalMax)
                isFirstInterval = true;
            else
                isFirstInterval = false;
            if (roundedWeight > (int32_t)secondIntervalMax)
                isSecondInterval = true;
            else
                isSecondInterval = false;
            if (holdWeight == false)
                netWeight = roundedWeight - taredWeight;
            if (netWeight < 0)
                isWeightNegative = true;
            else
                isWeightNegative = false;
            if (roundedWeight < 0)
                isUnderWeight = true;
            else
                isUnderWeight = false;
            if (roundedWeight >= overLimit)
                isOverWeight = true;
            else
                isOverWeight = false;

            printf("isStable = %d - isZero = %d - isNet =%d -  isFirstInterval =%d -  isSecondInterval =%d -  isNegative =%d -  isUnder =%d -  isOver =%d\n", isWeightStable, isWeightZero, isNetWeight, isFirstInterval, isSecondInterval, isWeightNegative, isUnderWeight, isOverWeight);
            //       printf("netAdc = %ld  -- weight = %f  --  roundedWeight = %ld -- netWeight = %ld- - taredWeight = %ld\n", netAdc, weight, roundedWeight, netWeight, taredWeight);

            return true;
        }
        return false;
    }

    void Weight::Initialize(void)
    {
        platformId = 0;
        weightFactor = weightPlatforms[platformId].weightFactor;
        decimalPointPosition = weightPlatforms[platformId].decimalPointPosition;
        firstIntervalMax = weightPlatforms[platformId].firstIntervalMax;
        secondIntervalMax = weightPlatforms[platformId].secondIntervalMax;
        firstAccuracy = weightPlatforms[platformId].firstAccuracy;
        secondAccuracy = weightPlatforms[platformId].secondAccuracy;
        adcOffset = weightPlatforms[platformId].adcOffset;
        if (weightPlatforms[platformId].loadcellTypeIndex == 0)
        {
            secondAccuracy = firstAccuracy;
            secondIntervalMax = firstIntervalMax;
        }
        driftCount = 0;
        driftLimitSamples = 10;
        isRoundingEnabled = true;
        holdWeight = false;
        isWeightStable = true;
        zeroLimit = (4 * firstIntervalMax / 100);
        startupZeroLimit = (20 * secondIntervalMax / 100);
        driftLimit = accuracyMap.at(firstAccuracy) / 2;
        stableLimitValue = accuracyMap.at(firstAccuracy);
        stableLimitSample = 10;
        overLimit = secondIntervalMax + (9 * accuracyMap.at(secondAccuracy));
    }
    uint8_t Weight::StartupZero(void)
    {
        if (roundedWeight <= startupZeroLimit)
        {
            adcOffset = Adc::filterdRawAdc[platformId];
            return 0;
        }
        return 3;
    }
    uint8_t Weight::SetZero(void)
    {
        if (taredWeight == 0)
        {
            if (labs(roundedWeight) <= zeroLimit)
            {
                if (isWeightStable == true)
                {
                    if (holdWeight == false)
                    {
                        adcOffset = Adc::filterdRawAdc[platformId];
                        return 0;
                    }
                    return 1;
                }
                return 2;
            }
            return 3;
        }
        return 4;
    }
    uint8_t Weight::SetTare(void)
    {
        if (netWeight > 0)
        {
            if (isWeightStable == true)
            {
                if (holdWeight == false)
                {
                    taredWeight = roundedWeight;
                    return 0;
                }
                return 1;
            }
            return 2;
        }
        return 3;
    }
    uint8_t Weight::RemoveTare(void)
    {
        if (netWeight < 0 && taredWeight > 0)
        {
            if (labs(netWeight) == taredWeight)
            {
                if (holdWeight == false)
                {
                    taredWeight = roundedWeight;
                    return 0;
                }
                return 1;
            }
            return 2;
        }
        return 3;
    }
    void Weight::CheckStability(void)
    {
        if (labs(roundedWeight - previousRoundWeight) <= stableLimitValue)
        {
            stableCounter++;
            if (stableCounter == stableLimitSample)
            {
                stableCounter = 0;
                isWeightStable = true;
            }
        }
        else
        {
            previousRoundWeight = roundedWeight;
            stableCounter = 0;
            isWeightStable = false;
        }
    }
    void Weight::RemoveDrift(void)
    {
        if (fabs(weight) <= driftLimit)
        {
            driftCount++;
            if (driftCount == driftLimitSamples)
            {
                adcOffset = Adc::filterdRawAdc[platformId];
                driftCount = 0;
            }
        }
        else
        {
            driftCount = 0;
        }
    }
}
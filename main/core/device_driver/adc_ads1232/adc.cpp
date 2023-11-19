#include <core/device_driver/gpio/gpio.h>
#include "core/device_driver/adc_ads1232/adc.h"
#include <rom/ets_sys.h>
#include <esp_system.h>

namespace ADC_ADS1232
{
    void Adc::ReadAdcRawData(void)
    {
        int Adc_Count;
        long realAdcData;
        if (gpio_get_level(ADS1232_DATA) == 0)
        {
            realAdcData = 0;
            isAdcNegative[FIRST_PLATFORM] = false;
            rawAdc[FIRST_PLATFORM] = 0;
            for (Adc_Count = 0; Adc_Count < 24; ++Adc_Count)
            {
                MakeAdcClock();
                realAdcData *= 2;
                if (gpio_get_level(ADS1232_DATA))
                    realAdcData += 1;
            }
            MakeAdcClock();
            if (realAdcData != (long)(0xffffff) && realAdcData != (long)(0x0) && realAdcData < (long)(0xffffff) && realAdcData > (int)(0))
            {
                if (realAdcData > (long)(0x7fffff))
                {
                    rawAdc[FIRST_PLATFORM] = realAdcData - (long)(0xffffff);
                    isAdcNegative[FIRST_PLATFORM] = true;
                }
                else
                    rawAdc[FIRST_PLATFORM] = realAdcData;

                if (useFiltering[FIRST_PLATFORM] == true)
                {
                    medianFilter[FIRST_PLATFORM].in(rawAdc[FIRST_PLATFORM]);
                    if (labs(medianFilter[FIRST_PLATFORM].getMax() - medianFilter[FIRST_PLATFORM].getMin()) <= filteringRange[FIRST_PLATFORM])
                        filterdRawAdc[FIRST_PLATFORM] = medianFilter[FIRST_PLATFORM].out();
                    else
                        filterdRawAdc[FIRST_PLATFORM] = rawAdc[FIRST_PLATFORM];

                    // filterdRawAdc[FIRST_PLATFORM] = (double)1.2 * lpFilter[FIRST_PLATFORM].filter((double)rawAdc[FIRST_PLATFORM]);
                    // Adc_Count = 5;
                    // do
                    // {
                    //     adcBuffer[Adc_Count] = adcBuffer[Adc_Count - 1];
                    //     Adc_Count--;
                    // } while (Adc_Count > 0);
                    // adcBuffer[0] = filterdRawAdc[FIRST_PLATFORM];
                    // for (Adc_Count = 0; Adc_Count < 5; Adc_Count++)
                    //     finalAdc[FIRST_PLATFORM] += adcBuffer[Adc_Count];
                    // finalAdc[FIRST_PLATFORM] /= 5;
                }
            }
            isAdcDataReceived[FIRST_PLATFORM] = true;
        }
    }

    void Adc::MakeAdcClock(void)
    {
        ets_delay_us(1);
        gpio_set_level(ADS1232_CLOCK, 1);
        ets_delay_us(1);
        gpio_set_level(ADS1232_CLOCK, 0);
    }
    void Adc::InitAdc(void)
    {
        unsigned char loopCounter;
        for (loopCounter = 0; loopCounter < 26; loopCounter++)
            MakeAdcClock();
        useFiltering[FIRST_PLATFORM] = false;
        lpFilter[FIRST_PLATFORM] = FIR_filter(10, 0.1, 0, "lp", "hamming");
        filteringRange[FIRST_PLATFORM] = 100000;
        filteringTaps[FIRST_PLATFORM] = 17;
        medianFilter[FIRST_PLATFORM] = MedianFilter(filteringTaps[FIRST_PLATFORM], 0);
    }
}

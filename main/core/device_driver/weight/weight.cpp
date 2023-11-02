#include <core/device_driver/gpio/gpio.h>
#include "core/device_driver/weight/weight.h"
#include <rom/ets_sys.h>
#include <esp_system.h>

namespace ADS1232_WEIGHT
{
    void Weight::ReadAdcRawData(void)
    {
        int Adc_Count;
        long realAdcData;
        if (gpio_get_level(ADS1232_DATA) == 0)
        {
            realAdcData = 0;
            isAdcNegative = false;
            rawAdcNumber = 0;
            for (Adc_Count = 0; Adc_Count < 24; ++Adc_Count)
            {
                MakeClock();
                realAdcData *= 2;
                if (gpio_get_level(ADS1232_DATA))
                    realAdcData += 1;
            }
            MakeClock();
            if (realAdcData != (long)(0xffffff) && realAdcData != (long)(0x0) && realAdcData < (long)(0xffffff) && realAdcData > (int)(0))
            {
                if (realAdcData > (long)(0x7fffff))
                {
                    rawAdcNumber = realAdcData - (long)(0xffffff);
                    isAdcNegative = true;
                }
                else
                    rawAdcNumber = realAdcData;
            }
            isWeightReceived = true;
        }
    }

    void Weight::MakeClock(void)
    {
        ets_delay_us(1);
        gpio_set_level(ADS1232_CLOCK, 1);
        ets_delay_us(1);
        gpio_set_level(ADS1232_CLOCK, 0);
    }

    void Weight::InitAdc(void)
    {
        unsigned char loopCounter;
        for (loopCounter = 0; loopCounter < 26; loopCounter++)
            MakeClock();
    }

}
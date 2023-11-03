#pragma once

#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_continuous.h"
#include "core/device_driver/gpio/gpio.h"

#define DC_SAMPLE_CHANNEL         ADC_CHANNEL_5
#define BATTERY_SAMPLE_CHANNEL    ADC_CHANNEL_6

namespace CHIP_ADC
{
    class ChipAdc
    {
        static inline adc_oneshot_unit_init_cfg_t init_config1;
        static inline adc_oneshot_unit_handle_t adc1_handle;
        static inline adc_oneshot_chan_cfg_t config;
    public:
        static inline unsigned int DcAdapterVoltage, BatteryVoltage;

    public:
        static void InitChipAdc(void);
        static void internal_adc_tasks(void);
    };
}
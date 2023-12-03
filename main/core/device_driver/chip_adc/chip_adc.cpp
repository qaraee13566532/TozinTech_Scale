#include <core/device_driver/chip_adc/chip_adc.h>
#include "core/definations.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_continuous.h"

#include <iostream>

namespace CHIP_ADC
{
    void ChipAdc::InitChipAdc(void)
    {
        config.bitwidth = ADC_BITWIDTH_DEFAULT;
        config.atten = ADC_ATTEN_DB_11;
        init_config1.unit_id=ADC_UNIT_1;
        ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc1_handle));
        ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, DC_SAMPLE_CHANNEL, &config));
        ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, BATTERY_SAMPLE_CHANNEL, &config));
    }
    void ChipAdc::internal_adc_tasks(void)
    {
        uint16_t value = 0;
        ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, DC_SAMPLE_CHANNEL, (int *)&value));
        DcAdapterVoltage = value;
        DcAdapterVoltage = (DcAdapterVoltage * (uint32_t)178200) / (uint32_t)61425;
        ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, BATTERY_SAMPLE_CHANNEL, (int *)&value));
        BatteryVoltage = value;
        BatteryVoltage = (BatteryVoltage * (uint32_t)178200) / (uint32_t)61425;
    }
}

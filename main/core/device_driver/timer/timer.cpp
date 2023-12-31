#include "core/device_driver/matrix_keyboard/keyboard.h"
#include "core/device_driver/timer/timer.h"
#include "esp_timer.h"
#include "core/device_driver/seven_segment_display/seven_segment_display.h"
#include "core/device_driver/adc_ads1232/adc.h"
#include "core/device_driver/chip_adc/chip_adc.h"
#include "core/device_driver/sntp/sntp.h"

using namespace ADC_ADS1232;
using namespace MATRIX_KEYBOARD;
using namespace SSEG_DEVICE_DRIVER;
using namespace CHIP_ADC;
using namespace SNTP;

namespace GLOBAL_TIMER
{
    void Timer::TimerCallback(void *param)
    {
        Keyboard::GetKeys();
        Sseg::RefreshDisplay();
        if (++externalReadAdcTime > 10)
        {
            externalReadAdcTime = 0;
            Adc::ReadAdcRawData();
        }
        if (++chipAdcReadTime > 200)
        {
            chipAdcReadTime = 0;
            ChipAdc::internal_adc_tasks();
        }
        if (Sntp::isRequestedForDateTime == true)
        {
            Sntp::requestDateTime();
            Sntp::isRequestedForDateTime = false;
            printf("requested.\n");
        }
        if (Sntp::autoAdjustDateTime)
        {
            if (++requestDateTime > 15000)
            {
                requestDateTime = 0;
                Sntp::isRequestedForDateTime = true;
            }
        }
        else
            requestDateTime = 0;
        if (freeRuningTimerMS > 0)
            freeRuningTimerMS--;
        if (AuxfreeRuningTimerMS > 0)
            AuxfreeRuningTimerMS--;
    }

    void Timer::InitTimer(void)
    {
        esp_timer_create_args_t my_timer_args = {
            .callback = &TimerCallback,
            .name = "My Timer"};
        ESP_ERROR_CHECK(esp_timer_create(&my_timer_args, &timer_handler));
        ESP_ERROR_CHECK(esp_timer_start_periodic(timer_handler, 1000));
        externalReadAdcTime = 0;
        chipAdcReadTime = 0;
    }

}
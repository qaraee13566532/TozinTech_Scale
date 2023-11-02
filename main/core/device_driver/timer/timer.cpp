#include "core/device_driver/matrix_keyboard/keyboard.h"
#include "core/device_driver/timer/timer.h"
#include "esp_timer.h"
#include "core/device_driver/seven_segment_display/seven_segment_display.h"

namespace GLOBAL_TIMER
{
    void Timer::TimerCallback(void *param)
    {
        MATRIX_KEYBOARD::Keyboard::GetKeys();
        SSEG_DEVICE_DRIVER::Sseg::RefreshDisplay();
    }

    void Timer::InitTimer(void)
    {
        const esp_timer_create_args_t my_timer_args = {
            .callback = &TimerCallback,
            .name = "My Timer"};
        ESP_ERROR_CHECK(esp_timer_create(&my_timer_args, &timer_handler));
        ESP_ERROR_CHECK(esp_timer_start_periodic(timer_handler, 1000));
    }
}
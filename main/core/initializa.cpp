#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "core/device_driver/matrix_keyboard/keyboard.h"
#include "core/device_driver/timer/timer.h"
#include "core/device_driver/gpio/gpio.h"
#include "core/device_driver/seven_segment_display/seven_segment_display.h"
#include "core/device_driver/weight/weight.h"

using namespace SSEG_DEVICE_DRIVER;
using namespace GLOBAL_TIMER;
using namespace GPIO;
using namespace MATRIX_KEYBOARD;
using namespace ADS1232_WEIGHT;

void initialize(void)
{
    Gpio::InitGpio();
    Keyboard::InitKeyboard();
    Sseg::InitDisplay(7);
    Timer::InitTimer();
    Sseg::DialpayStart();
    vTaskDelay(100 / portTICK_PERIOD_MS);
    Sseg::Write_Message_To_Display("PAnd", WEIGHT, 5, true);
    Sseg::Write_Message_To_Display("ScALE", UNIT_PRICE, 6, true);
    Sseg::Write_Message_To_Display("VEr-1.00", TOTAL_PRICE, 7, true);
    Weight::InitAdc();
}
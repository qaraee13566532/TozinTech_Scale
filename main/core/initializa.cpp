#include "core/device_driver/matrix_keyboard/keyboard.h"
#include "core/device_driver/timer/timer.h"



void initialize(void)
{
    MATRIX_KEYBOARD::Keyboard::InitKeyboard();
    GLOBAL_TIMER::Timer::InitTimer();
}
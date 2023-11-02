#pragma once

#include <driver/gpio.h>
#include "core/device_driver/matrix_keyboard/keyboard.h"


// DISPLAY SEVEN SEGMENT
const gpio_num_t TM1640_CHIP_1_CLOCK = GPIO_NUM_19;
const gpio_num_t TM1640_CHIP_2_CLOCK = GPIO_NUM_8;
const gpio_num_t TM1640_DATA = GPIO_NUM_20;

// ADS1232 main ADC IO
const gpio_num_t ADS1232_CLOCK = GPIO_NUM_1;
const gpio_num_t ADS1232_DATA = GPIO_NUM_2;

// KEYBOARD main ADC IO
const gpio_num_t Key_Row6 = GPIO_NUM_42;
const gpio_num_t Key_Row5 = GPIO_NUM_41;
const gpio_num_t Key_Row4 = GPIO_NUM_37;
const gpio_num_t Key_Row3 = GPIO_NUM_38;
const gpio_num_t Key_Row2 = GPIO_NUM_39;
const gpio_num_t Key_Row1 = GPIO_NUM_40;

// BUZZER IO
const gpio_num_t BUZZER = GPIO_NUM_5;

// UPS CONTROLLER IO
const gpio_num_t UPS_CTRL = GPIO_NUM_4;

// CASH DRAWER
const gpio_num_t CASH = GPIO_NUM_16;

// CALIBRATION KEY
const gpio_num_t CAL_JMP = GPIO_NUM_15;

// OUTPUT RELAYS IO
const gpio_num_t Relay_1 = GPIO_NUM_3;
const gpio_num_t Relay_2 = GPIO_NUM_46;
const gpio_num_t Relay_3 = GPIO_NUM_9;
const gpio_num_t Relay_4 = GPIO_NUM_10;
const gpio_num_t Relay_5 = GPIO_NUM_11;
const gpio_num_t Relay_6 = GPIO_NUM_12;
const gpio_num_t Relay_7 = GPIO_NUM_13;
const gpio_num_t Relay_8 = GPIO_NUM_14;

// KEYBOARD SCAN IO
const gpio_num_t Scan_Port_Address[KEY_COLOUMNS] = {GPIO_NUM_3, GPIO_NUM_46, GPIO_NUM_9, GPIO_NUM_10,
                                                    GPIO_NUM_11, GPIO_NUM_12, GPIO_NUM_13, GPIO_NUM_14,
                                                    GPIO_NUM_21, GPIO_NUM_47, GPIO_NUM_48, GPIO_NUM_45,
                                                    GPIO_NUM_35, GPIO_NUM_36};

namespace GPIO
{
    class Gpio
    {
    public:
        static void InitGpio(void);
    };
}
#pragma once
#include <iostream>
#include <future>
#include <driver/gpio.h>
#include "core/device_driver/matrix_keyboard/keyboard.h"

// DISPLAY SEVEN SEGMENT
#define TM1640_CHIP_1_CLOCK GPIO_NUM_19
#define TM1640_CHIP_2_CLOCK GPIO_NUM_8
#define TM1640_DATA GPIO_NUM_20

// ADS1232 main ADC IO
#define ADS1232_CLOCK GPIO_NUM_1
#define ADS1232_DATA GPIO_NUM_2

// KEYBOARD main ADC IO
#define Key_Row6 GPIO_NUM_42
#define Key_Row5 GPIO_NUM_41
#define Key_Row4 GPIO_NUM_37
#define Key_Row3 GPIO_NUM_38
#define Key_Row2 GPIO_NUM_39
#define Key_Row1 GPIO_NUM_40

// BUZZER IO
#define BUZZER GPIO_NUM_5

// UPS CONTROLLER IO
#define UPS_CTRL GPIO_NUM_4

// CASH DRAWER
#define CASH GPIO_NUM_16

// CALIBRATION KEY
#define CALIBRATION_SWITCH GPIO_NUM_0

// OUTPUT RELAYS IO
#define Relay_1 GPIO_NUM_3
#define Relay_2 GPIO_NUM_46
#define Relay_3 GPIO_NUM_9
#define Relay_4 GPIO_NUM_10
#define Relay_5 GPIO_NUM_11
#define Relay_6 GPIO_NUM_12
#define Relay_7 GPIO_NUM_13
#define Relay_8 GPIO_NUM_14

// KEYBOARD SCAN IO
const gpio_num_t Scan_Port_Address[KEY_COLOUMNS] = {GPIO_NUM_3, GPIO_NUM_46, GPIO_NUM_9, GPIO_NUM_10,
                                                    GPIO_NUM_11, GPIO_NUM_12, GPIO_NUM_13, GPIO_NUM_14,
                                                    GPIO_NUM_21, GPIO_NUM_47, GPIO_NUM_48, GPIO_NUM_45,
                                                    GPIO_NUM_35, GPIO_NUM_36};
#define Relay_8 GPIO_NUM_14
#define Relay_8 GPIO_NUM_14

namespace GPIO
{
    class Gpio
    {
        static inline std::future<void> f1;

    public:
        static void InitGpio(void);
        static void TurnBuzzerOn(uint16_t durationMS);
        static void vpcc(uint16_t durationMS);
        static void TurnCashOn();
        static void TurnCashOff();
        static bool readCalibrationSwitchStatus(void);
    };
}
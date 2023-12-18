
#include "features/splash/ui/splash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "core/device_driver/matrix_keyboard/keyboard.h"
#include "core/device_driver/timer/timer.h"
#include "core/device_driver/gpio/gpio.h"
#include "core/device_driver/seven_segment_display/seven_segment_display.h"
#include "core/device_driver/adc_ads1232/adc.h"
#include "core/device_driver/chip_adc/chip_adc.h"
#include "core/device_driver/commiunication_uart/comm_uart.h"
#include "core/device_driver/printer_uart/printer_uart.h"
#include "core/device_driver/storage/storage.h"
#include "core/device_driver/wifi/wifi.h"
#include "core/device_driver/nvs/nvs.h"
#include "core/device_driver/sntp/sntp.h"
#include "definations.h"
#include "core/calibration/ui/calibration_page.h"
#include <iostream>
#include <future>
#include "core/global_variables.h"

using namespace SSEG_DEVICE_DRIVER;
using namespace GLOBAL_TIMER;
using namespace GPIO;
using namespace MATRIX_KEYBOARD;
using namespace ADC_ADS1232;
using namespace ADS1232_WEIGHT;
using namespace CHIP_ADC;
using namespace COMMIUNICATION_UART;
using namespace PRINTER_UART;
using namespace STORAGE;
using namespace WIFI;
using namespace NVS;
using namespace SNTP;
using namespace CALIBRATION;
using namespace std::chrono_literals;

namespace SPLASH
{
    void Splash::Demo()
    {
        uint32_t loopCounter, showCounter = 0;
        uint8_t character = '9';
        for (loopCounter = 1100; loopCounter > 0 && cancellationToken == false; loopCounter--)
        {
            DELAY(5);
            showCounter++;
            if (showCounter == 100)
            {
                showCounter = 0;
                if (character == '0')
                {
                    Sseg::BlankDisplay();
                    Sseg::Write_Message_To_Display("rEAdy", WEIGHT, 6, true);
                }
                else
                {
                    Sseg::fillDisplay(character);
                    character--;
                }
            }
        }
    }

    void Splash::Initialize(void)
    {
        keyCode = 0;
        keytype = false;
        checkCalibKey = false;
        if (Keyboard::isKeyPressed())
            checkCalibKey = true;
        cancellationToken = false;

        weightPlatforms[0].loadParameters();
        weights[0].Initialize();
        state = SPLASH_RUN_TASK;
        demoDelay = std::async(std::launch::async, &Demo);
    }

    void Splash::RunTasks(uint16_t &appState)
    {
        switch (state)
        {
        case SPLASH_INIT:
            Initialize();
            keyCode = 0;
            break;
        case SPLASH_RUN_TASK:

            if (weights[0].CalcWeight())
                weights[0].StartupZero();
            status = demoDelay.wait_for(0s);
            if (status == std::future_status::ready)
                appState = SALE_PAGE;
            Keyboard::readKeyBuffer(keyCode, keytype);
            if (checkCalibKey == true && keyCode == KEY_ZERO)
            {
                cancellationToken = true;
                appState = CALIBRATION_PAGE;
            }
            switch (keyCode)
            {
            case KEY_ZERO:
                printf("zero key pressed ...");
                break;
            }
            keyCode = 0;
            break;
        }
    }
}

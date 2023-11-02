#include <core/device_driver/gpio/gpio.h>
#include "core/global_constants.h"

namespace GPIO
{
    void Gpio::InitGpio(void)
    {
        uint8_t column_index = 0;
        // ADC IO'S INITIALIZATION
        esp_rom_gpio_pad_select_gpio(ADS1232_CLOCK);
        gpio_set_direction(ADS1232_CLOCK, GPIO_MODE_OUTPUT);
        esp_rom_gpio_pad_select_gpio(ADS1232_DATA);
        gpio_set_direction(ADS1232_DATA, GPIO_MODE_INPUT);
        gpio_pulldown_dis(ADS1232_DATA);
        gpio_pullup_en(ADS1232_DATA);
        // KEYBOARD IO'S INITIALIZATION
        esp_rom_gpio_pad_select_gpio(Key_Row1);
        gpio_set_direction(Key_Row1, GPIO_MODE_INPUT);
        esp_rom_gpio_pad_select_gpio(Key_Row2);
        gpio_set_direction(Key_Row2, GPIO_MODE_INPUT);
        esp_rom_gpio_pad_select_gpio(Key_Row3);
        gpio_set_direction(Key_Row3, GPIO_MODE_INPUT);
        esp_rom_gpio_pad_select_gpio(Key_Row4);
        gpio_set_direction(Key_Row4, GPIO_MODE_INPUT);
        esp_rom_gpio_pad_select_gpio(Key_Row5);
        gpio_set_direction(Key_Row5, GPIO_MODE_INPUT);
        esp_rom_gpio_pad_select_gpio(Key_Row6);
        gpio_set_direction(Key_Row6, GPIO_MODE_INPUT);
        for (column_index = 0; column_index < KEY_COLOUMNS; column_index++)
        {
            esp_rom_gpio_pad_select_gpio(Scan_Port_Address[column_index]);
            gpio_set_direction(Scan_Port_Address[column_index], GPIO_MODE_OUTPUT);
        }
        // BUZZER IO'S INITIALIZATION
        esp_rom_gpio_pad_select_gpio(BUZZER);
        gpio_set_direction(BUZZER, GPIO_MODE_OUTPUT);
        // UPS-CONTROL IO'S INITIALIZATION
        esp_rom_gpio_pad_select_gpio(UPS_CTRL);
        gpio_set_direction(UPS_CTRL, GPIO_MODE_OUTPUT);
        gpio_set_level(UPS_CTRL, 1);
        // 7_SEGMENT IO'S INITIALIZATION
        gpio_reset_pin(TM1640_CHIP_1_CLOCK);
        gpio_reset_pin(TM1640_DATA);
        gpio_reset_pin(TM1640_CHIP_2_CLOCK);
        esp_rom_gpio_pad_select_gpio(TM1640_CHIP_2_CLOCK);
        gpio_set_direction(TM1640_CHIP_2_CLOCK, GPIO_MODE_OUTPUT);
        esp_rom_gpio_pad_select_gpio(TM1640_CHIP_1_CLOCK);
        gpio_set_direction(TM1640_CHIP_1_CLOCK, GPIO_MODE_OUTPUT);
        esp_rom_gpio_pad_select_gpio(TM1640_DATA);
        gpio_set_direction(TM1640_DATA, GPIO_MODE_OUTPUT);
        gpio_set_level(TM1640_CHIP_1_CLOCK, LOW_LEVEL);
        gpio_set_level(TM1640_CHIP_2_CLOCK, LOW_LEVEL);
        gpio_set_level(TM1640_DATA, LOW_LEVEL);
        // RELAY IO'S INITIALIZATION
        esp_rom_gpio_pad_select_gpio(Relay_1);
        gpio_set_direction(Relay_1, GPIO_MODE_OUTPUT);
        esp_rom_gpio_pad_select_gpio(Relay_2);
        gpio_set_direction(Relay_2, GPIO_MODE_OUTPUT);
        esp_rom_gpio_pad_select_gpio(Relay_3);
        gpio_set_direction(Relay_3, GPIO_MODE_OUTPUT);
        esp_rom_gpio_pad_select_gpio(Relay_4);
        gpio_set_direction(Relay_4, GPIO_MODE_OUTPUT);
        esp_rom_gpio_pad_select_gpio(Relay_5);
        gpio_set_direction(Relay_5, GPIO_MODE_OUTPUT);
        esp_rom_gpio_pad_select_gpio(Relay_6);
        gpio_set_direction(Relay_6, GPIO_MODE_OUTPUT);
        esp_rom_gpio_pad_select_gpio(Relay_7);
        gpio_set_direction(Relay_7, GPIO_MODE_OUTPUT);
        esp_rom_gpio_pad_select_gpio(Relay_8);
        gpio_set_direction(Relay_8, GPIO_MODE_OUTPUT);
        // CALIBRATION JAMPER IO'S INITIALIZATION
        esp_rom_gpio_pad_select_gpio(CAL_JMP);
        gpio_set_direction(CAL_JMP, GPIO_MODE_INPUT);
        // CASH IO'S INITIALIZATION
        esp_rom_gpio_pad_select_gpio(CASH);
        gpio_set_direction(CASH, GPIO_MODE_OUTPUT);
        gpio_set_level(CASH, 0);

    }
}
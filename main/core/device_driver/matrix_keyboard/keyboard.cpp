#include "core/device_driver/matrix_keyboard/keyboard.h"
#include "core/hardware_io.h"
#include "core/constant.h"

namespace MATRIX_KEYBOARD
{
    const gpio_num_t Scan_Port_Address[KEY_COLOUMNS] = {GPIO_NUM_3, GPIO_NUM_46, GPIO_NUM_9, GPIO_NUM_10,
                                                        GPIO_NUM_11, GPIO_NUM_12, GPIO_NUM_13, GPIO_NUM_14,
                                                        GPIO_NUM_21, GPIO_NUM_47, GPIO_NUM_48, GPIO_NUM_45,
                                                        GPIO_NUM_35, GPIO_NUM_36};

    void Keyboard::initKeyboard(void)
    {
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
        for (loopCounter = 0; loopCounter < KEY_COLOUMNS; loopCounter++)
        {
            esp_rom_gpio_pad_select_gpio(Scan_Port_Address[loopCounter]);
            gpio_set_direction(Scan_Port_Address[loopCounter], GPIO_MODE_INPUT);
        }
        for (loopCounter = 0; loopCounter < MAX_PRESSED_KEY_BUFFER_SIZE; loopCounter++)
        {
            releasedKeysflag[loopCounter] = true;
            releasedKeysCounter[loopCounter] = 0;
            pressedKeysRowBuffer[loopCounter] = 0;
            pressedKeysColoumnBuffer[loopCounter] = 0;
            pressedKeysBounceCounter[loopCounter] = 0;
            longPressedKeysflag[loopCounter] = false;
            shortPressedKeysflag[loopCounter] = false;
        }
        for (loopCounter = 0; loopCounter < MAX_KEYBOARD_BUFFER_SIZE; loopCounter++)
            KeyCodeBuffer[loopCounter] = 0;
        keyHead = 0;
        keyTail = 0;
        pressedKeysNumber = 0;
    }

    void Keyboard::keyIOSetReset(gpio_num_t Port_Bits, bool SetReset)
    {
        SetReset ? gpio_set_direction(Port_Bits, GPIO_MODE_OUTPUT) : gpio_set_direction(Port_Bits, GPIO_MODE_INPUT);
        SetReset ? gpio_set_level(Port_Bits, 1) : gpio_set_level(Port_Bits, 0);
    }
    bool Keyboard::ifKeyNotExistInBuffer(unsigned char rowId, unsigned char colId)
    {
        for (loopCounter = 0; loopCounter < MAX_PRESSED_KEY_BUFFER_SIZE; loopCounter++)
        {
            if (pressedKeysRowBuffer[loopCounter] == rowId && pressedKeysColoumnBuffer[loopCounter] == colId)
                return false;
        }
        return true;
    }

    unsigned char Keyboard::returnFreeLocation(void)
    {
        for (loopCounter = 0; loopCounter < MAX_PRESSED_KEY_BUFFER_SIZE; loopCounter++)
        {
            if (releasedKeysflag[loopCounter] == true)
                return loopCounter;
        }
        return loopCounter;
    }

    void Keyboard::savePressedKeysToBuffer(gpio_num_t keyRow, unsigned char rowId)
    {
        unsigned char freeBufferLocation;
        freeBufferLocation = returnFreeLocation();
        if (pressedKeysNumber < MAX_PRESSED_KEY_BUFFER_SIZE)
        {
            if (gpio_get_level(keyRow))
            {
                if (releasedKeysflag[freeBufferLocation] == true)
                {
                    if (ifKeyNotExistInBuffer(rowId, keyColumnCounter))
                    {
                        pressedKeysRowBuffer[freeBufferLocation] = rowId;
                        pressedKeysColoumnBuffer[freeBufferLocation] = keyColumnCounter;
                        pressedKeysBounceCounter[freeBufferLocation] = 0;
                        longPressedKeysflag[freeBufferLocation] = false;
                        shortPressedKeysflag[freeBufferLocation] = false;
                        releasedKeysflag[freeBufferLocation] = false;
                        pressedKeysNumber++;
                    }
                }
            }
        }
    }
    gpio_num_t Keyboard::getRowGpio(unsigned char rowId)
    {
        gpio_num_t gpio = Key_Row1;

        switch (rowId)
        {
        case 0x1:
            gpio = Key_Row1;
            break;
        case 0x2:
            gpio = Key_Row2;
            break;
        case 0x4:
            gpio = Key_Row3;
            break;
        case 0x8:
            gpio = Key_Row4;
            break;
        case 0x10:
            gpio = Key_Row5;
            break;
        case 0x20:
            gpio = Key_Row6;
            break;
        }
        return gpio;
    }
    void Keyboard::getKeys(void)
    {
        savePressedKeysToBuffer(Key_Row1, 0x01);
        savePressedKeysToBuffer(Key_Row2, 0x02);
        savePressedKeysToBuffer(Key_Row3, 0x04);
        savePressedKeysToBuffer(Key_Row4, 0x08);
        savePressedKeysToBuffer(Key_Row5, 0x10);
        savePressedKeysToBuffer(Key_Row6, 0x20);

        for (loopCounter = 0; loopCounter < MAX_PRESSED_KEY_BUFFER_SIZE; loopCounter++)
        {
            if (releasedKeysflag[loopCounter] == false)
            {
                if (pressedKeysColoumnBuffer[loopCounter] == keyColumnCounter)
                {
                    if (gpio_get_level(getRowGpio(pressedKeysRowBuffer[loopCounter])))

                    {
                        if (shortPressedKeysflag[loopCounter] == false && longPressedKeysflag[loopCounter] == false)
                        {
                            if (pressedKeysBounceCounter[loopCounter] >= KEY_SHORT_PRESS_TIME)
                            {
                                shortPressedKeysflag[loopCounter] = true;
                            }
                        }
                        if (longPressedKeysflag[loopCounter] == false)
                        {
                            if (pressedKeysBounceCounter[loopCounter] >= KEY_LONG_PRESS_TIME)
                            {
                                longPressedKeysflag[loopCounter] = true;
                                shortPressedKeysflag[loopCounter] = false;
                            }
                        }
                        if (pressedKeysBounceCounter[loopCounter] < KEY_LONG_PRESS_TIME)
                            pressedKeysBounceCounter[loopCounter]++;
                    }
                    else
                        pressedKeysBounceCounter[loopCounter] = 0;
                }
            }

            if (longPressedKeysflag[loopCounter] == true || shortPressedKeysflag[loopCounter] == true)
            {

                if (pressedKeysColoumnBuffer[loopCounter] == keyColumnCounter)
                {
                    if (gpio_get_level(getRowGpio(pressedKeysRowBuffer[loopCounter])) == 0)
                    {
                        if (releasedKeysCounter[loopCounter] < KEY_RELEASE_TIME)
                            releasedKeysCounter[loopCounter]++;
                        else
                        {
                            KeyCodeBuffer[keyHead] = pressedKeysColoumnBuffer[loopCounter] * 8 + pressedKeysRowBuffer[loopCounter];
                            if (shortPressedKeysflag[loopCounter] == true)
                                keyPressedType[keyHead] = false;
                            else
                                keyPressedType[keyHead] = true;
                            printf("read key = %d -- type = %d\n", KeyCodeBuffer[keyHead], keyPressedType[keyHead]);
                            keyHead = keyHead + 1;
                            if (keyHead >= MAX_KEYBOARD_BUFFER_SIZE)
                                keyHead = 0;
                            if (keyHead == keyTail)
                            {
                                if (keyHead == 0)
                                    keyHead = MAX_KEYBOARD_BUFFER_SIZE - 1;
                                else
                                    keyHead = keyHead - 1;
                            }
                            shortPressedKeysflag[loopCounter] = false;
                            longPressedKeysflag[loopCounter] = false;
                            pressedKeysBounceCounter[loopCounter] = 0;
                            releasedKeysflag[loopCounter] = true;
                            pressedKeysRowBuffer[loopCounter] = 0;
                            pressedKeysColoumnBuffer[loopCounter] = 0;
                            if (pressedKeysNumber > 0)
                                pressedKeysNumber--;
                        }
                    }
                    else
                        releasedKeysCounter[loopCounter] = 0;
                }
            }
        }

        keyIOSetReset(Scan_Port_Address[keyColumnCounter], 0);
        keyColumnCounter++;
        if (keyColumnCounter == KEY_COLOUMNS)
            keyColumnCounter = 0;
        keyIOSetReset(Scan_Port_Address[keyColumnCounter], 1);
    }

}
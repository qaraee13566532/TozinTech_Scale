#include "core/device_driver/matrix_keyboard/keyboard.h"
#include "core/device_driver/gpio/gpio.h"

using namespace GPIO;

namespace MATRIX_KEYBOARD
{

    void Keyboard::InitKeyboard(void)
    {
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

    void Keyboard::KeyIOSetReset(gpio_num_t Port_Bits, bool SetReset)
    {
        SetReset ? gpio_set_direction(Port_Bits, GPIO_MODE_OUTPUT) : gpio_set_direction(Port_Bits, GPIO_MODE_INPUT);
        SetReset ? gpio_set_level(Port_Bits, 1) : gpio_set_level(Port_Bits, 0);
    }
    bool Keyboard::IfKeyNotExistInBuffer(uint8_t rowId, uint8_t colId)
    {
        for (loopCounter = 0; loopCounter < MAX_PRESSED_KEY_BUFFER_SIZE; loopCounter++)
        {
            if (pressedKeysRowBuffer[loopCounter] == rowId && pressedKeysColoumnBuffer[loopCounter] == colId)
                return false;
        }
        return true;
    }

    uint8_t Keyboard::ReturnFreeLocation(void)
    {
        for (loopCounter = 0; loopCounter < MAX_PRESSED_KEY_BUFFER_SIZE; loopCounter++)
        {
            if (releasedKeysflag[loopCounter] == true)
                return loopCounter;
        }
        return loopCounter;
    }
    bool Keyboard::isKeyPressed(void)
    {
        if (pressedKeysNumber > 0)
            return true;
        else
            return false;
    }
    bool Keyboard::getPressingKeyCode(uint8_t keyNumber)
    {
        for (loopCounter = 0; loopCounter < MAX_PRESSED_KEY_BUFFER_SIZE; loopCounter++)
        {
            if ((longPressedKeysflag[loopCounter] == true || shortPressedKeysflag[loopCounter] == true) && (pressedKeysColoumnBuffer[loopCounter] * 8 + pressedKeysRowBuffer[loopCounter]) == keyNumber)
                return true;
        }
        return false;
    }
    void Keyboard::SavePressedKeysToBuffer(gpio_num_t keyRow, uint8_t rowId)
    {
        uint8_t freeBufferLocation;
        freeBufferLocation = ReturnFreeLocation();
        if (pressedKeysNumber < MAX_PRESSED_KEY_BUFFER_SIZE)
        {
            if (gpio_get_level(keyRow))
            {
                if (releasedKeysflag[freeBufferLocation] == true)
                {
                    if (IfKeyNotExistInBuffer(rowId, keyColumnCounter))
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
    gpio_num_t Keyboard::GetRowGpio(uint8_t rowId)
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
    void Keyboard::GetKeys(void)
    {
        SavePressedKeysToBuffer(Key_Row1, 0x01);
        SavePressedKeysToBuffer(Key_Row2, 0x02);
        SavePressedKeysToBuffer(Key_Row3, 0x04);
        SavePressedKeysToBuffer(Key_Row4, 0x08);
        SavePressedKeysToBuffer(Key_Row5, 0x10);
        SavePressedKeysToBuffer(Key_Row6, 0x20);

        for (loopCounter = 0; loopCounter < MAX_PRESSED_KEY_BUFFER_SIZE; loopCounter++)
        {
            if (releasedKeysflag[loopCounter] == false)
            {
                if (pressedKeysColoumnBuffer[loopCounter] == keyColumnCounter)
                {
                    if (gpio_get_level(GetRowGpio(pressedKeysRowBuffer[loopCounter])))

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
                    if (gpio_get_level(GetRowGpio(pressedKeysRowBuffer[loopCounter])) == 0)
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
                            Gpio::TurnBuzzerOn(50);
                        }
                    }
                    else
                        releasedKeysCounter[loopCounter] = 0;
                }
            }
        }

        KeyIOSetReset(Scan_Port_Address[keyColumnCounter], 0);
        keyColumnCounter++;
        if (keyColumnCounter == KEY_COLOUMNS)
            keyColumnCounter = 0;
        KeyIOSetReset(Scan_Port_Address[keyColumnCounter], 1);
    }
    void Keyboard::readKeyBuffer(uint8_t &data, bool &type)
    {
        if (keyHead != keyTail)
        {
            data = KeyCodeBuffer[keyTail];
            type = keyPressedType[keyTail];
            keyTail = keyTail + 1;
            if (keyTail >= MAX_PRESSED_KEY_BUFFER_SIZE)
                keyTail = 0;
        }
        else
            data = 0;
    }

}
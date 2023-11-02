#pragma once

#include "core/constant.h"
#include <driver/gpio.h>

namespace MATRIX_KEYBOARD
{

    class Keyboard
    {
    public:
        static inline unsigned char pressedKeysRowBuffer[MAX_PRESSED_KEY_BUFFER_SIZE];
        static inline unsigned char pressedKeysColoumnBuffer[MAX_PRESSED_KEY_BUFFER_SIZE];
        static inline unsigned int pressedKeysBounceCounter[MAX_PRESSED_KEY_BUFFER_SIZE];
        static inline bool longPressedKeysflag[MAX_PRESSED_KEY_BUFFER_SIZE];
        static inline bool shortPressedKeysflag[MAX_PRESSED_KEY_BUFFER_SIZE];
        static inline bool releasedKeysflag[MAX_PRESSED_KEY_BUFFER_SIZE];
        static inline unsigned char releasedKeysCounter[MAX_PRESSED_KEY_BUFFER_SIZE];
        static inline bool keyPressedType[MAX_KEYBOARD_BUFFER_SIZE];
        static inline unsigned char KeyCodeBuffer[MAX_KEYBOARD_BUFFER_SIZE];

        static inline unsigned char pressedKeysNumber, keyRows, keyColumnCounter, loopCounter, keyHead, keyTail;

    public:
        static bool IfKeyNotExistInBuffer(unsigned char rowId,unsigned char colId);
        static void InitKeyboard(void);
        static unsigned char ReturnFreeLocation(void);
        static void Readkeyboard(void);
        static void GetKeys(void);
        static void KeyIOSetReset(gpio_num_t Port_Bits, bool SetReset);
        static void SavePressedKeysToBuffer(gpio_num_t keyRow, unsigned char rowId);
        static gpio_num_t GetRowGpio(unsigned char rowId);
    };
}

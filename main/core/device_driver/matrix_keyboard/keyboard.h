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
        static bool ifKeyNotExistInBuffer(unsigned char rowId,unsigned char colId);
        static void initKeyboard(void);
        static unsigned char returnFreeLocation(void);
        static void readkeyboard(void);
        static void getKeys(void);
        static void keyIOSetReset(gpio_num_t Port_Bits, bool SetReset);
        static void savePressedKeysToBuffer(gpio_num_t keyRow, unsigned char rowId);
        static gpio_num_t getRowGpio(unsigned char rowId);
    };
}

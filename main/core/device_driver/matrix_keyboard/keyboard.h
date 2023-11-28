#pragma once

#include <driver/gpio.h>

#define KEY_COLOUMNS 14
#define KEY_LONG_PRESS_TIME 20
#define KEY_SHORT_PRESS_TIME 4
#define KEY_RELEASE_TIME 2
#define MAX_KEYBOARD_BUFFER_SIZE 5
#define MAX_PRESSED_KEY_BUFFER_SIZE 10

#define KEY_NUMBER_0 65
#define KEY_NUMBER_1 74
#define KEY_NUMBER_2 82
#define KEY_NUMBER_3 90
#define KEY_NUMBER_4 76
#define KEY_NUMBER_5 84
#define KEY_NUMBER_6 96
#define KEY_NUMBER_7 72
#define KEY_NUMBER_8 80
#define KEY_NUMBER_9 88

#define KEY_ZERO 112
#define KEY_TARE 108
#define KEY_CLEAR 81

const unsigned char englishKeyMap[112] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 7, 0, 1, 0, 4, 0, 0, 0,
    8, 0, 2, 0, 5, 0, 0, 0, 9, 0,
    3, 0, 0, 0, 0, 0, 6, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0};

const unsigned char persianKeyMap[112] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0};


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
        static bool IfKeyNotExistInBuffer(unsigned char rowId, unsigned char colId);
        static void InitKeyboard(void);
        static unsigned char ReturnFreeLocation(void);
        static void Readkeyboard(void);
        static void GetKeys(void);
        static void KeyIOSetReset(gpio_num_t Port_Bits, bool SetReset);
        static void SavePressedKeysToBuffer(gpio_num_t keyRow, unsigned char rowId);
        static gpio_num_t GetRowGpio(unsigned char rowId);
        static void readKeyBuffer(unsigned char &data, bool &typ);
    };
}

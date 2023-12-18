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

#define KEY_ZERO    112
#define KEY_TARE    108
#define KEY_CLEAR    81
#define KEY_RESAULT 105
#define KEY_MUL     100
#define KEY_ADD      97
#define KEY_FUNC    104
#define KEY_ONOFF   106




const uint8_t englishKeyMap[112] = {
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

const uint8_t persianKeyMap[112] = {
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
        static inline uint8_t pressedKeysRowBuffer[MAX_PRESSED_KEY_BUFFER_SIZE];
        static inline uint8_t pressedKeysColoumnBuffer[MAX_PRESSED_KEY_BUFFER_SIZE];
        static inline uint16_t pressedKeysBounceCounter[MAX_PRESSED_KEY_BUFFER_SIZE];
        static inline bool longPressedKeysflag[MAX_PRESSED_KEY_BUFFER_SIZE];
        static inline bool shortPressedKeysflag[MAX_PRESSED_KEY_BUFFER_SIZE];
        static inline bool releasedKeysflag[MAX_PRESSED_KEY_BUFFER_SIZE];
        static inline uint8_t releasedKeysCounter[MAX_PRESSED_KEY_BUFFER_SIZE];
        static inline bool keyPressedType[MAX_KEYBOARD_BUFFER_SIZE];
        static inline uint8_t KeyCodeBuffer[MAX_KEYBOARD_BUFFER_SIZE];

        static inline uint8_t pressedKeysNumber, keyRows, keyColumnCounter, loopCounter, keyHead, keyTail;

    public:
        static bool IfKeyNotExistInBuffer(uint8_t rowId, uint8_t colId);
        static void InitKeyboard(void);
        static uint8_t ReturnFreeLocation(void);
        static void Readkeyboard(void);
        static void GetKeys(void);
        static void KeyIOSetReset(gpio_num_t Port_Bits, bool SetReset);
        static void SavePressedKeysToBuffer(gpio_num_t keyRow, uint8_t rowId);
        static gpio_num_t GetRowGpio(uint8_t rowId);
        static void readKeyBuffer(uint8_t &data, bool &typ);
        static bool isKeyPressed(void);
        static bool getPressingKeyCode(uint8_t keyNumber);
    };
}

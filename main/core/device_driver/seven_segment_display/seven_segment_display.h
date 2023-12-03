#pragma once

#include <math.h>
#include <iostream>
#include <map>

using std::string;
using std::map;


#define WEIGHT_POSITION 0
#define TARE_POSITION 7
#define UNIT_PRICE_POSITION 16
#define TOTAL_PRICE_POSITION 23
#define WEIGHT_DIGITS_NO 6
#define TARE_DIGITS_NO 6
#define UNIT_PRICE_DIGITS_NO 7
#define TOTAL_PRICE_DIGITS_NO 8
#define WEIGHT 0
#define TARE 1
#define UNIT_PRICE 2
#define TOTAL_PRICE 3
#define MAX_DISPLAY_DIGITS 32
#define POINT 0x80
#define MINUS 0x40
#define DISPOFF 0x00

const uint8_t DisplayPos[4] = {WEIGHT_POSITION, TARE_POSITION, UNIT_PRICE_POSITION, TOTAL_PRICE_POSITION};
const uint8_t DisplayMaxDigitNo[4] = {WEIGHT_DIGITS_NO, TARE_DIGITS_NO, UNIT_PRICE_DIGITS_NO, TOTAL_PRICE_DIGITS_NO};

const uint8_t Text_Convertion_Table[128] = {

    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x40, 0, 0,
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0, 0, 0, 0x48, 0, 0,
    0, 0x77, 0x7f, 0x39, 0x3f, 0x79, 0x71, 0x3d, 0x76, 0x06, 0x1e, 0x76, 0x38, 0x55, 0x37, 0x3f,
    0x73, 0x67, 0x50, 0x6d, 0x78, 0x3e, 0x3e, 0x6a, 0x76, 0x6e, 0x5b, 0, 0, 0, 0, 0x08,
    0, 0x5f, 0x7c, 0x58, 0x5e, 0x7b, 0x71, 0x6f, 0x74, 0x04, 0x1e, 0x76, 0x06, 0x55, 0x54, 0x5c,
    0x73, 0x67, 0x50, 0x6d, 0x78, 0x1c, 0x1c, 0x6a, 0x76, 0x6e, 0x5b, 0, 0, 0, 0, 0};

namespace SSEG_DEVICE_DRIVER
{

    class Sseg
    {
        static inline uint8_t displayBuffer[MAX_DISPLAY_DIGITS];
        static inline uint8_t sevenSegmentStateMachine, currentChipNumber;
        static inline bool enableRefresh, isPriceComputing;

    public:
        static void InitDisplay(uint8_t intensity);
        static void SetDispBuffer(uint8_t index, uint8_t data);
        static uint8_t ReadDisplayBuffer(uint8_t index);
        static void RefreshDisplay(void);
        static void DialpayStart(void);
        static void DialpayStop(void);
        static void BlankDisplay(void);
        static void Write_Message_To_Display(string Message, uint8_t displayPart, uint8_t posintion, bool cleanFirst);
        static void BlankDisplayPart(uint8_t displayPart);
        static void Write_Number_To_Display(int32_t input, uint8_t displayPart, bool showDecimalPoint, uint8_t decimapPointPosition, bool Show_BackZero, bool Show_Front_Zero, uint8_t digitDisplayNumbers, bool alignCenter, bool cleanFirst);
        static void Scroll_Message(string Message, uint8_t displayPart, uint8_t startPos, int16_t delayMS, int16_t returnKeyCode, bool retunKeyState, bool exitIfCompleted);
        static void viewScrollMessage(string &Message, uint8_t displayPart, int16_t delayMS);
        static void getNumber(string &digitsBuffer, uint8_t &keyCode, uint8_t &digitIndex, uint32_t Max);
        static void BlinkDigit(uint8_t &digitIndex, uint8_t displayPart, uint8_t blinkDigit, uint16_t delayMS);
        static void ResetBlinkTimer(uint16_t delayMS);
        static void selectItem(const map<uint8_t, uint32_t> valueMap,const map<uint8_t, string> helperMap,uint8_t &keyCode, uint8_t displayPart, uint8_t maxDigits, uint32_t &selector,bool showHelper);
        
       
    private:
        static void StartBus(uint8_t chipNumber);
        static void StopBus(uint8_t chipNumber);
        static void WriteToTM1640(uint16_t Data, uint8_t chipNumber);
        static void ClearTM1640(uint8_t chipNumber);
    };
}
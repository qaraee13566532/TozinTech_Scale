#include "seven_segment_display.h"
#include "core/device_driver/gpio/gpio.h"
#include "core/definations.h"
#include "core/device_driver/seven_segment_display/seven_segment_display.h"
#include <rom/ets_sys.h>
#include <string.h>
#include <stdio.h>
#include "core/device_driver/matrix_keyboard/keyboard.h"
#include <iostream>
#include <sstream>
#include <string>
#include "core/device_driver/timer/timer.h"
#include <map>

using std::map;

using std::cout;
using std::endl;
using std::istringstream;
using std::string;

using namespace MATRIX_KEYBOARD;
using namespace GLOBAL_TIMER;

namespace SSEG_DEVICE_DRIVER
{
    void Sseg::StartBus(uint8_t chipNumber)
    {
        switch (chipNumber)
        {
        case 0:
            gpio_set_level(TM1640_CHIP_1_CLOCK, LOW_LEVEL);
            break;
        case 1:
            gpio_set_level(TM1640_CHIP_2_CLOCK, LOW_LEVEL);
            break;
        default:
            break;
        }
        ets_delay_us(1);
        gpio_set_level(TM1640_DATA, LOW_LEVEL);
        ets_delay_us(1);
        gpio_set_level(TM1640_DATA, HICH_LEVEL);
        ets_delay_us(1);
    }
    void Sseg::StopBus(uint8_t chipNumber)
    {
        switch (chipNumber)
        {
        case 0:
            gpio_set_level(TM1640_CHIP_1_CLOCK, LOW_LEVEL);
            break;
        case 1:
            gpio_set_level(TM1640_CHIP_2_CLOCK, LOW_LEVEL);
            break;
        default:
            break;
        }
        ets_delay_us(1);
        gpio_set_level(TM1640_DATA, HICH_LEVEL);
        ets_delay_us(1);
        gpio_set_level(TM1640_DATA, LOW_LEVEL);
        ets_delay_us(1);
    }
    void Sseg::WriteToTM1640(uint16_t Data, uint8_t chipNumber)
    {
        uint8_t LoopCnt;
        for (LoopCnt = 0; LoopCnt < 8; LoopCnt++)
        {
            ets_delay_us(2);
            if (chipNumber == 0)
                gpio_set_level(TM1640_CHIP_1_CLOCK, HICH_LEVEL);
            else
                gpio_set_level(TM1640_CHIP_2_CLOCK, HICH_LEVEL);

            if (Data & 0x01)
                gpio_set_level(TM1640_DATA, LOW_LEVEL);
            else
                gpio_set_level(TM1640_DATA, HICH_LEVEL);
            Data >>= 1;
            ets_delay_us(2);
            if (chipNumber == 0)
                gpio_set_level(TM1640_CHIP_1_CLOCK, LOW_LEVEL);
            else
                gpio_set_level(TM1640_CHIP_2_CLOCK, LOW_LEVEL);
            ets_delay_us(2);
        }
    }
    void Sseg::ClearTM1640(uint8_t chipNumber)
    {
        uint8_t loopCnt = 0;
        StartBus(chipNumber);
        WriteToTM1640(0xC0, chipNumber);
        for (loopCnt = 0; loopCnt < 16; ++loopCnt)
            WriteToTM1640(0x00, chipNumber);
        StopBus(chipNumber);
    }
    void Sseg::InitDisplay(uint8_t intensity)
    {

        isPriceComputing = true;
        sevenSegmentStateMachine = 0;
        enableRefresh = false;
        currentChipNumber = 0;
        BlankDisplay();
        gpio_set_level(TM1640_CHIP_1_CLOCK, LOW_LEVEL);
        gpio_set_level(TM1640_CHIP_2_CLOCK, HICH_LEVEL);
        gpio_set_level(TM1640_DATA, LOW_LEVEL);
        ets_delay_us(50);
        gpio_set_level(TM1640_CHIP_1_CLOCK, HICH_LEVEL);
        gpio_set_level(TM1640_CHIP_2_CLOCK, LOW_LEVEL);
        gpio_set_level(TM1640_DATA, LOW_LEVEL);
        ets_delay_us(50);
        StartBus(0);
        WriteToTM1640(0x40, 0);
        StopBus(0);
        StartBus(0);
        WriteToTM1640(0x88 | (intensity & 7), 0);
        StopBus(0);
        ets_delay_us(5);
        StartBus(1);
        WriteToTM1640(0x40, 1);
        StopBus(1);
        StartBus(1);
        WriteToTM1640(0x88 | (intensity & 7), 1);
        StopBus(1);
    }
    void Sseg::DialpayStart(void)
    {
        enableRefresh = true;
    }
    void Sseg::DialpayStop(void)
    {
        uint8_t loopCounter = 0;
        for (loopCounter = 0; loopCounter < MAX_DISPLAY_DIGITS; loopCounter++)
            displayBuffer[loopCounter] = 0x00;
        enableRefresh = false;
    }
    void Sseg::RefreshDisplay(void)
    {
        if (enableRefresh)
        {
            if (sevenSegmentStateMachine == 0)
            {
                StartBus(currentChipNumber);
                WriteToTM1640(0x40, currentChipNumber);
                StopBus(currentChipNumber);
                sevenSegmentStateMachine = 1;
            }
            else if (sevenSegmentStateMachine == 1)
            {
                StartBus(currentChipNumber);
                WriteToTM1640(0xC0, currentChipNumber);
                sevenSegmentStateMachine = 2;
            }
            else if (sevenSegmentStateMachine >= 2 && sevenSegmentStateMachine <= 17)
            {
                WriteToTM1640(displayBuffer[currentChipNumber * 16 + sevenSegmentStateMachine - 2], currentChipNumber);
                sevenSegmentStateMachine++;
            }
            else
            {
                if (sevenSegmentStateMachine == 18)
                {
                    StopBus(currentChipNumber);
                    sevenSegmentStateMachine = 0;

                    if (currentChipNumber == 0)
                        currentChipNumber = 1;
                    else
                        currentChipNumber = 0;
                }
            }
        }
    }
    void Sseg::BlankDisplay(void)
    {
        uint8_t loopCounter = 0, digitNumber;
        if (isPriceComputing == true)
            digitNumber = 32;
        else
            digitNumber = 6;
        for (loopCounter = 0; loopCounter < digitNumber; loopCounter++)
            displayBuffer[loopCounter] = 0;
    }
    void Sseg::Write_Message_To_Display(string Message, uint8_t displayPart, uint8_t posintion, bool cleanFirst)
    {
        uint16_t loopCnt, DispCnt = 0, pointPos = 0;
        size_t Len;
        uint8_t data = 0;

        posintion += DisplayPos[displayPart];
        if (posintion > 0)
            posintion--;
        pointPos = posintion;
        Len = Message.length() > DisplayMaxDigitNo[displayPart] ? DisplayMaxDigitNo[displayPart] : Message.length();
        if (cleanFirst == true)
            BlankDisplayPart(displayPart);
        for (loopCnt = 0; loopCnt < Len; loopCnt++)
        {
            data = Message.at(loopCnt);
            if (DispCnt < DisplayMaxDigitNo[displayPart])
            {
                if (data != '.')
                {
                    displayBuffer[posintion - DispCnt] = Text_Convertion_Table[data];
                    pointPos = posintion - DispCnt;
                    DispCnt++;
                }
                else
                    displayBuffer[pointPos] |= POINT;
            }
        }
    }
    void Sseg::SetDispBuffer(uint8_t index, uint8_t data)
    {
        displayBuffer[index] = data;
    }
    uint8_t Sseg::ReadDisplayBuffer(uint8_t index)
    {
        return displayBuffer[index];
    }
    void Sseg::BlankDisplayPart(uint8_t displayPart)
    {
        uint16_t loopCnt, posintion;
        posintion = DisplayPos[displayPart];
        for (loopCnt = 0; loopCnt < DisplayMaxDigitNo[displayPart]; loopCnt++)
            displayBuffer[posintion + loopCnt] = 0;
    }
    void Sseg::Write_Number_To_Display(int32_t input, uint8_t displayPart, bool showDecimalPoint, uint8_t decimapPointPosition, bool Show_BackZero, bool Show_Front_Zero, uint8_t digitDisplayNumbers, bool alignCenter, bool cleanFirst)
    {
        uint8_t dcnt, dig_dsp, len = 0, pos;
        int32_t temp_input;
        if (alignCenter == true)
        {
            temp_input = input;
            while (temp_input)
            {
                len++;
                temp_input /= 10;
            }
            len = (DisplayMaxDigitNo[displayPart] - len) / 2;
        }
        else
            len = 0;
        bool sign = false;
        if (input < 0)
        {
            digitDisplayNumbers--;
            sign = true;
            input *= -1;
        }

        if (cleanFirst)
            BlankDisplayPart(displayPart);
        dcnt = DisplayPos[displayPart] + len;
        do
        {
            dig_dsp = input % 10;
            if (input || Show_BackZero)
                displayBuffer[dcnt] = Text_Convertion_Table[dig_dsp + '0'];
            else
            {
                if (Show_Front_Zero == 0)
                {
                    if ((dcnt == DisplayPos[WEIGHT] || dcnt == DisplayPos[TARE] || dcnt == DisplayPos[UNIT_PRICE] || dcnt == DisplayPos[TOTAL_PRICE]) && input == 0)
                        displayBuffer[dcnt] = Text_Convertion_Table[0 + '0'];
                    else
                        displayBuffer[dcnt] = DISPOFF;
                }
                else
                {
                    if (dcnt < Show_Front_Zero + DisplayPos[displayPart])
                        displayBuffer[dcnt] = Text_Convertion_Table[dig_dsp + '0'];
                    else
                        displayBuffer[dcnt] = DISPOFF;
                }
            }
            if (dcnt == decimapPointPosition + DisplayPos[displayPart] && showDecimalPoint)
                displayBuffer[dcnt] |= POINT;
            input /= 10;

            dcnt++;
            pos = DisplayPos[displayPart] + DisplayMaxDigitNo[displayPart];
            if (pos > 0)
                pos--;
            if (sign)
                displayBuffer[pos] |= MINUS;
        } while (dcnt < digitDisplayNumbers + DisplayPos[displayPart]);
    }
    void Sseg::Scroll_Message(string Message, uint8_t displayPart, uint8_t spaceChar, int16_t delayMS, int16_t returnKeyCode, bool retunKeyState, bool exitIfCompleted)
    {
        uint16_t loopCounter, messageCounter;
        uint8_t keydata = 0;
        bool keytype = false;
        size_t Len;
        uint8_t swap;
        bool isCompleted = false;
        Len = Message.length();
        if (exitIfCompleted == true)
            spaceChar = DisplayMaxDigitNo[displayPart];
        string messageData(spaceChar, ' ');
        messageData += Message;

        loopCounter = 0;
        for (;;)
        {
            Write_Message_To_Display(messageData, displayPart, DisplayMaxDigitNo[displayPart], true);
            swap = messageData[0];
            for (messageCounter = 0; messageCounter < Len + spaceChar; messageCounter++)
                messageData[messageCounter] = messageData[messageCounter + 1];
            messageData[Len + spaceChar - 1] = swap;

            if (exitIfCompleted == true)
            {
                DELAY(delayMS);
                loopCounter++;
                if (loopCounter == spaceChar && isCompleted == false)
                    isCompleted = true;
                if (loopCounter == (spaceChar + Len) && isCompleted == true)
                {
                    BlankDisplayPart(displayPart);
                    return;
                }
            }
            else
            {
                for (loopCounter = 0; loopCounter < delayMS; loopCounter++)
                {
                    DELAY(1);
                    Keyboard::readKeyBuffer(keydata, keytype);
                    if (keydata == returnKeyCode && keytype == retunKeyState)
                    {
                        BlankDisplayPart(displayPart);
                        return;
                    }
                }
            }
        }
    }
    void Sseg::viewScrollMessage(string &Message, uint8_t displayPart, int16_t delayMS)
    {
        uint16_t messageCounter;
        size_t Len;
        uint8_t swap;

        if (Timer::AuxfreeRuningTimerMS == 0)
        {
            Timer::AuxfreeRuningTimerMS = delayMS;
            Len = Message.length();
            Write_Message_To_Display(Message, displayPart, DisplayMaxDigitNo[displayPart], true);
            swap = Message[0];
            for (messageCounter = 0; messageCounter < Len; messageCounter++)
                Message[messageCounter] = Message[messageCounter + 1];
            Message[Len - 1] = swap;
        }
    }
    void Sseg::selectItem(const map<uint8_t, uint32_t> valueMap, const map<uint8_t, string> helperMap, uint8_t &keyCode, uint8_t displayPart, uint8_t maxDigits, uint32_t &selector, bool showHelper)
    {
        switch (keyCode)
        {
        case KEY_ZERO:
            selector++;
            if (selector == valueMap.size())
                selector = 0;
            Write_Number_To_Display(valueMap.at(selector), displayPart, false, 0, false, false, maxDigits, false, false);
            if (showHelper == true)
                Write_Message_To_Display(helperMap.at(selector), UNIT_PRICE, 7, true);

            break;
        case KEY_CLEAR:
            selector = 0;
            Write_Number_To_Display(valueMap.at(selector), displayPart, false, 0, false, false, maxDigits, false, false);
            if (showHelper == true)
                Write_Message_To_Display(helperMap.at(selector), UNIT_PRICE, 7, true);
            break;
        }
    }
    void Sseg::getNumber(string &digitsBuffer, uint8_t &keyCode, uint8_t &digitIndex, uint32_t Max)
    {
        uint32_t addValue = 0;
        int32_t number = 0, powerNumber = 0;
        istringstream(digitsBuffer) >> number;

        switch (keyCode)
        {
        case KEY_NUMBER_0:
        case KEY_NUMBER_1:
        case KEY_NUMBER_2:
        case KEY_NUMBER_3:
        case KEY_NUMBER_4:
        case KEY_NUMBER_5:
        case KEY_NUMBER_6:
        case KEY_NUMBER_7:
        case KEY_NUMBER_8:
        case KEY_NUMBER_9:
            number *= 10;
            number += englishKeyMap[keyCode];
            if (number > Max)
                number = englishKeyMap[keyCode];
            digitsBuffer = std::to_string(number);
            keyCode = KEY_ZERO;
            break;
        case KEY_ZERO:
            powerNumber = pow(10, digitIndex + 1);
            addValue = (number % powerNumber);
            powerNumber = pow(10, digitIndex);
            addValue /= powerNumber;
            if (addValue < 9)
                number += powerNumber;
            else
                number -= 9 * powerNumber;
            digitsBuffer = std::to_string(number);
            break;
        case KEY_CLEAR:
            digitsBuffer[0] = 0;
            keyCode = KEY_ZERO;
            digitIndex = 0;
            break;
        }
    }
    void Sseg::ResetBlinkTimer(uint16_t delayMS)
    {
        Timer::freeRuningTimerMS = delayMS;
    }
    void Sseg::BlinkDigit(uint8_t &digitIndex, uint8_t displayPart, uint8_t blinkDigit, uint16_t delayMS)
    {
        static bool visibleDigit = false;
        if (Timer::freeRuningTimerMS == 0)
        {
            if (visibleDigit == false)
            {
                visibleDigit = true;
                SetDispBuffer(DisplayPos[displayPart] + digitIndex, blinkDigit);
            }
            else
            {
                visibleDigit = false;
                SetDispBuffer(DisplayPos[displayPart] + digitIndex, 0);
            }
            Timer::freeRuningTimerMS = delayMS;
        }
    }
}

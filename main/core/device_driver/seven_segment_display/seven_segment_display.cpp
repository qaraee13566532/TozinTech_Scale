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

using std::cout;
using std::endl;
using std::string;
using namespace MATRIX_KEYBOARD;

namespace SSEG_DEVICE_DRIVER
{

    void Sseg::StartBus(unsigned char chipNumber)
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
    void Sseg::StopBus(unsigned char chipNumber)
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
    void Sseg::WriteToTM1640(unsigned int Data, unsigned char chipNumber)
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
    void Sseg::ClearTM1640(unsigned char chipNumber)
    {
        unsigned char loopCnt = 0;
        StartBus(chipNumber);
        WriteToTM1640(0xC0, chipNumber);
        for (loopCnt = 0; loopCnt < 16; ++loopCnt)
            WriteToTM1640(0x00, chipNumber);
        StopBus(chipNumber);
    }
    void Sseg::InitDisplay(unsigned char intensity)
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
        unsigned char loopCounter = 0;
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
        unsigned char loopCounter = 0, digitNumber;
        if (isPriceComputing == true)
            digitNumber = 32;
        else
            digitNumber = 6;
        for (loopCounter = 0; loopCounter < digitNumber; loopCounter++)
            displayBuffer[loopCounter] = 0;
    }
    void Sseg::Write_Message_To_Display(string Message, unsigned char displayPart, unsigned char posintion, bool cleanFirst)
    {
        unsigned int loopCnt, DispCnt = 0, pointPos = 0;
        size_t Len;
        unsigned char data = 0;

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
    void Sseg::SetDispBuffer(unsigned char index, unsigned char data)
    {
        displayBuffer[index] = data;
    }
    unsigned char Sseg::ReadDisplayBuffer(unsigned char index)
    {
        return  displayBuffer[index];
    }
    void Sseg::BlankDisplayPart(unsigned char displayPart)
    {
        unsigned int loopCnt, posintion;
        posintion = DisplayPos[displayPart];
        for (loopCnt = 0; loopCnt < DisplayMaxDigitNo[displayPart]; loopCnt++)
            displayBuffer[posintion + loopCnt] = 0;
    }
    void Sseg::Write_Number_To_Display(long long input, unsigned char displayPart, bool showDecimalPoint, unsigned char decimapPointPosition, bool Show_BackZero, bool Show_Front_Zero, unsigned char digitDisplayNumbers, bool alignCenter, bool cleanFirst)
    {
        unsigned char dcnt, dig_dsp, len = 0, pos;
        long long temp_input;
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
    void Sseg::Scroll_Message(const char *Message, unsigned char displayPart, unsigned char spaceChar, int delayMS, int returnKeyCode, bool retunKeyState, bool exitIfCompleted)
    {
        unsigned int loopCounter, messageCounter;
        unsigned char keydata = 0;
        bool keytype = false;
        size_t Len;
        unsigned char swap;
        bool isCompleted = false;
        Len = strlen(Message);
        if (exitIfCompleted == true)
            spaceChar = DisplayMaxDigitNo[displayPart];
        char *messageData = (char *)malloc(Len + spaceChar);
        for (loopCounter = 0; loopCounter < spaceChar; loopCounter++)
            *(messageData + loopCounter) = ' ';
        *(messageData + loopCounter) = 0;
        strncat(messageData, Message, Len);
        loopCounter = 0;
        for (;;)
        {
            Write_Message_To_Display(messageData, displayPart, DisplayMaxDigitNo[displayPart], true);
            swap = *messageData;
            for (messageCounter = 0; messageCounter < Len + spaceChar; messageCounter++)
                *(messageData + messageCounter) = *(messageData + messageCounter + 1);
            *(messageData + Len + spaceChar - 1) = swap;

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
    void Sseg::viewScrollMessage(string &Message, unsigned char displayPart, int delayMS)
    {
        unsigned int messageCounter;
        static int delayTime;
        size_t Len;
        unsigned char swap;

        if (delayTime == delayMS)
        {
            delayTime = 0;
            Len = Message.length();
            Write_Message_To_Display(Message, displayPart, DisplayMaxDigitNo[displayPart], true);
            swap = Message[0];
            for (messageCounter = 0; messageCounter < Len; messageCounter++)
                Message[messageCounter] = Message[messageCounter + 1];
            Message[Len - 1] = swap;
        }
        else
        {
            DELAY(1);
            delayTime++;
        }
    }
    void Sseg::getNumber(string &digitsBuffer, unsigned char &keyCode, unsigned char &digitIndex, unsigned long Max)
    {
        unsigned long addValue = 0;
        long number = 0, powerNumber = 0;
        std::istringstream(digitsBuffer) >> number;

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
}

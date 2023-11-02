#include "seven_segment_display.h"
#include "core/device_driver/gpio/gpio.h"
#include "core/global_constants.h"
#include "core/device_driver/seven_segment_display/seven_segment_display.h"
#include <rom/ets_sys.h>
#include <string.h>

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
    void Sseg::Write_Message_To_Display(const char *Message, unsigned char displayPart, unsigned char posintion, bool cleanFirst)
    {
        unsigned int loopCnt, DispCnt = 0, pointPos = 0;
        size_t Len;
        unsigned char data = 0;

        posintion += DisplayPos[displayPart];
        if (posintion > 0)
            posintion--;
        Len = strlen(Message);
        // if (Len > DisplayMaxDigitNo[displayPart])
        //     Len = DisplayMaxDigitNo[displayPart];
        if (cleanFirst == true)
            BlankDisplayPart(displayPart);
        for (loopCnt = 0; loopCnt < Len; loopCnt++)
        {
            data = *(Message + loopCnt);
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
    void Sseg::BlankDisplayPart(unsigned char displayPart)
    {
        unsigned int loopCnt, posintion;
        posintion = DisplayPos[displayPart];
        for (loopCnt = 0; loopCnt < DisplayMaxDigitNo[displayPart]; loopCnt++)
            displayBuffer[posintion + loopCnt] = 0;
    }
}

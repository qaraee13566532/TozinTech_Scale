#include "keyboard.h"
#include "core/hardware_io.h"
#include "core/constant.h"

namespace MATRIX_KEYBOARD
{
    void Keyboard::readkeyboard(void)
    {
        unsigned char keyRows = 0,row=0,scanCode=0;
        static unsigned char keyColumnCounter=0,keyReleaseTime=0,
                             lastValidScanCode=0,readKeyCounter=0,
                             keyBuffer[MAX_KEYBOARD_BUFFER_SIZE],keyHead,keyTail;
        
        if (gpio_get_level(Key_Row1))
            keyRows |= 0x1;
        if (gpio_get_level(Key_Row2))
            keyRows |= 0x2;
        if (gpio_get_level(Key_Row3))
            keyRows |= 0x4;
        if (gpio_get_level(Key_Row4))
            keyRows |= 0x8;
        if (gpio_get_level(Key_Row5))
            keyRows |= 0x10;
        if (gpio_get_level(Key_Row6))
            keyRows |= 0x20;

        if (keyRows)
        {
            switch (keyRows)
            {
            case 0x01:
                row = 0x00;
                break;
            case 0x02:
                row = 0x01;
                break;
            case 0x04:
                row = 0x02;
                break;
            case 0x08:
                row = 0x03;
                break;
            case 0x10:
                row = 0x04;
                break;
            case 0x20:
                row = 0x05;
                break;
            }
            scanCode = row + keyColumnCounter * 8;
            if (keyReleaseTime == MAX_KEY_RELEASE_TIME)
            {
                if (scanCode == lastValidScanCode)
                {
                    readKeyCounter = readKeyCounter + 1;
                    if (readKeyCounter == MAX_READ_KEY)
                    {
                        keyBuffer[keyHead] = scanCode;
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
                        keyReleaseTime = 0;
                        lastValidScanCode = 0;
                        readKeyCounter = 0;
                    }
                }
                else
                    lastValidScanCode = scanCode;
            }
            else
                keyReleaseTime = 0;
        }
        else
        {
            if ((scanCode & 0xf8) == (keyColumnCounter * 8))
                if (keyReleaseTime != MAX_KEY_RELEASE_TIME)
                    keyReleaseTime = keyReleaseTime + 1;
        }
        /*
        GeyKey(12, 4, MUL);
        GeyKey(12, 1, ACCUM);
        GeyKey(12, 2, PRINT);
        if (keyReleaseTime == MAX_KEY_RELEASE_TIME && SetupCnt > 0)
            SetupCnt--;
        if (Prog_State == NORMAL_OPERATION && SetupCnt == 0)
            GeyKey(12, 8, MENU);
        if (Relay_En_Index == 0 || (Relay_En_Index && keyColumnCounter > 7))
            output_bit(Scan_Port_Address[keyColumnCounter], 0);
        keyColumnCounter++;
        if (keyColumnCounter == KEY_NO)
            keyColumnCounter = 0;
        if (Relay_En_Index == 0 || (Relay_En_Index && keyColumnCounter > 7))
            output_bit(Scan_Port_Address[keyColumnCounter], 1);*/
    }
}
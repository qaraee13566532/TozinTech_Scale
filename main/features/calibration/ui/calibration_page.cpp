#include "features/calibration/ui/calibration_page.h"
#include "core/definations.h"
#include "core/device_driver/seven_segment_display/seven_segment_display.h"
#include "core/global_variables.h"
#include "core/device_driver/matrix_keyboard/keyboard.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>

using std::string;

using namespace SSEG_DEVICE_DRIVER;
using namespace MATRIX_KEYBOARD;

namespace CALIBRATION
{
    void CalibrationPage::RunTasks(void)
    {
        char *viewBuffer = (char *)malloc(32 * sizeof(unsigned char));
        unsigned char bufferdDigit = 0;
        unsigned long Number = 0;
        bool visibleDigit = false;
        string helperMessage("PLAtForm Id SEttIng .   ");
        string digitsBuffer(20, 0);

        unsigned char pageState = PlatformDefinationInitialize;
        int platform = 0, blinkTime = 0;
        unsigned char keydata = 0, digitIndex = 0, currentLocation = UNIT_PRICE;
        bool keytype = false;
        Sseg::BlankDisplay();
        Sseg::Scroll_Message("CALIbrAtion", WEIGHT, 6, ScrollMessageDelayMS, 1, false, true);
        DELAY(500);

        while (true)
        {
            switch (pageState)
            {
            case PlatformDefinationInitialize:
                Sseg::Write_Message_To_Display("PFM= 1", WEIGHT, 6, true);
                Sseg::Write_Number_To_Display(Number, UNIT_PRICE, false, 0, true, true, DisplayMaxDigitNo[UNIT_PRICE], false, true);
                pageState = PlatformTask;
                bufferdDigit = Sseg::ReadDisplayBuffer(DisplayPos[currentLocation] + digitIndex);
                break;
            case PlatformTask:
                Sseg::viewScrollMessage(helperMessage, TOTAL_PRICE, ScrollMessageDelayMS);
                Sseg::getNumber(digitsBuffer, keydata, digitIndex, 10000000);
                if (keydata)
                {
                    std::istringstream(digitsBuffer) >> Number;
                    Sseg::Write_Number_To_Display(Number, UNIT_PRICE, false, 0, true, true, DisplayMaxDigitNo[UNIT_PRICE], false, false);
                    blinkTime=0;
                    bufferdDigit = Sseg::ReadDisplayBuffer(DisplayPos[currentLocation] + digitIndex);
                    keydata = 0;
                    visibleDigit=true;
                }
                if (blinkTime++ >= 350)
                {
                    blinkTime = 0;
                    if (visibleDigit == false)
                    {
                        visibleDigit = true;
                        Sseg::SetDispBuffer(DisplayPos[currentLocation] + digitIndex, bufferdDigit);
                    }
                    else
                    {
                        visibleDigit = false;
                        bufferdDigit = Sseg::ReadDisplayBuffer(DisplayPos[currentLocation] + digitIndex);
                        Sseg::SetDispBuffer(DisplayPos[currentLocation] + digitIndex, 0);
                    }
                }

                break;
            default:
                break;
            }
            Keyboard::readKeyBuffer(keydata, keytype);
            switch (keydata)
            {
            case KEY_ZERO:
                platform++;
                if (platform > 1)
                    platform = 0;
                sprintf(viewBuffer, "PFM= %d", platform + 1);
                Sseg::Write_Message_To_Display(viewBuffer, WEIGHT, 6, true);
                break;
            case KEY_TARE:
                Sseg::SetDispBuffer(DisplayPos[currentLocation] + digitIndex, bufferdDigit);
                digitIndex++;
                if (digitIndex == DisplayMaxDigitNo[currentLocation])
                    digitIndex = 0;
                blinkTime = 0;
                bufferdDigit = Sseg::ReadDisplayBuffer(DisplayPos[currentLocation] + digitIndex);
                break;
            default:
                break;
            }
        }
    };
}
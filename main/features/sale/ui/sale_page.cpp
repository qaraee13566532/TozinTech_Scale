

#include "features/sale/ui/sale_page.h"
#include "core/weight/weight.h"
#include "core/device_driver/seven_segment_display/seven_segment_display.h"
#include "core/device_driver/adc_ads1232/adc.h"
#include "core/device_driver/matrix_keyboard/keyboard.h"

using namespace ADS1232_WEIGHT;
using namespace SSEG_DEVICE_DRIVER;
using namespace MATRIX_KEYBOARD;

extern Weight weights[MAX_PLATFORM_NUMBER];

namespace SALE
{
    void Sale::Initialize(void)
    {
        state = SALE_RUN_TASK;
        keyCode = 0;
        keytype = false;
    }
    void Sale::RunTasks(uint16_t &appState)
    {
        switch (state)
        {
        case SALE_INIT:
            Initialize();
            break;
        case SALE_RUN_TASK:
            if (weights[0].CalcWeight())
            {
                Sseg::showLedIndicators(0);
                if (weights[0].isUnderWeight == false)
                {
                    if (weights[0].isOverWeight == false)
                        Sseg::Write_Number_To_Display(weights[0].netWeight, WEIGHT, true, weights[0].decimalPointPosition, false, true, 6, false, true);
                    else
                        Sseg::Write_Message_To_Display(" OVEr ", WEIGHT, 6, true);
                }
                else
                    Sseg::Write_Message_To_Display("------", WEIGHT, 6, true);
            }
            Keyboard::readKeyBuffer(keyCode, keytype);
            switch (keyCode)
            {
            case KEY_ZERO:
                printf("resault = %d\n", weights[0].SetZero());
                break;
            case KEY_TARE:
                printf("resault = %d\n", weights[0].SetTare());
                break;
            case KEY_ADD:
                printf("resault = %d\n", weights[0].RemoveTare());
                break;
            case KEY_CLEAR:
                weights[0].holdWeight = !weights[0].holdWeight;
                break;
            }
            keyCode = 0;
            break;
        default:
            break;
        }
    }
}
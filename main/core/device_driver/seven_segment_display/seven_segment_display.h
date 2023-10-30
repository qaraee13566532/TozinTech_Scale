#pragma once

#include "core/constant.h"

namespace SSEG_DEVICE_DRIVER
{

    class Sseg
    {
        static unsigned char sevenSegmentStateMachine, currentChipNumber;
        static bool enableRefresh;

    public:
        static void InitDisplay(unsigned char intensity);
        static void RefreshDisplay(unsigned char displayBuffer[MAX_DISPLAY_DIGITS]);
        static void DialpayStart(void);

    private:
        static void StartBus(unsigned char chipNumber);
        static void StopBus(unsigned char chipNumber);
        static void WriteToTM1640(unsigned int Data, unsigned char chipNumber);
        static void ClearTM1640(unsigned char chipNumber);

    };
}
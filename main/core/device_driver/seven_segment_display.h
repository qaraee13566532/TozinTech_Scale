#pragma once

namespace SSEG_DEVICE_DRIVER
{

    class Sseg
    {
        static unsigned char sevenSegmentStateMachine,currentChipNumber;
        static bool enableRefresh;

    public:
        Sseg()
        {
            sevenSegmentStateMachine = 0;
            enableRefresh = false;
            currentChipNumber=0;
        }
        static void InitSseg(unsigned char intensity, unsigned char chipNumber);

    private:
        static void StartBus(unsigned char chipNumber);
        static void StopBus(unsigned char chipNumber);
        static void WriteToTM1640(unsigned int Data, unsigned char chipNumber);
        static void ClearTM1640(unsigned char chipNumber);
        static void RefreshDisplay(void);
        static void DialpayStart(void);
    };
}
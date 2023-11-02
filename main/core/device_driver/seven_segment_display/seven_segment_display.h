#pragma once

const unsigned char WEIGHT_POSITION = 0;
const unsigned char TARE_POSITION = 7;
const unsigned char UNIT_PRICE_POSITION = 16;
const unsigned char TOTAL_PRICE_POSITION = 23;
const unsigned char WEIGHT_DIGITS_NO = 6;
const unsigned char TARE_DIGITS_NO = 6;
const unsigned char UNIT_PRICE_DIGITS_NO = 7;
const unsigned char TOTAL_PRICE_DIGITS_NO = 8;
const unsigned char WEIGHT = 0;
const unsigned char TARE = 1;
const unsigned char UNIT_PRICE = 2;
const unsigned char TOTAL_PRICE = 3;
const unsigned char MAX_DISPLAY_DIGITS = 32;
const unsigned char DisplayPos[4] = {WEIGHT_POSITION, TARE_POSITION, UNIT_PRICE_POSITION, TOTAL_PRICE_POSITION};
const unsigned char DisplayMaxDigitNo[4] = {WEIGHT_DIGITS_NO, TARE_DIGITS_NO, UNIT_PRICE_DIGITS_NO, TOTAL_PRICE_DIGITS_NO};
const unsigned char POINT = 0x80;
const unsigned char Text_Convertion_Table[128] = {

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
        static inline unsigned char displayBuffer[MAX_DISPLAY_DIGITS];
        static inline unsigned char sevenSegmentStateMachine, currentChipNumber;
        static inline bool enableRefresh, isPriceComputing;

    public:
        static void InitDisplay(unsigned char intensity);
        static void RefreshDisplay(void);
        static void DialpayStart(void);
        static void DialpayStop(void);
        static void BlankDisplay(void);
        static void Write_Message_To_Display(const char *Message, unsigned char displayPart, unsigned char posintion, bool cleanFirst);
        static void BlankDisplayPart(unsigned char displayPart);

    private:
        static void StartBus(unsigned char chipNumber);
        static void StopBus(unsigned char chipNumber);
        static void WriteToTM1640(unsigned int Data, unsigned char chipNumber);
        static void ClearTM1640(unsigned char chipNumber);
    };
}
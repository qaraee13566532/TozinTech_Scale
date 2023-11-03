
#pragma once

#define DATEOFST 79

namespace REALTIME_CLOCK
{
    class Rtc
    {
    public:
        static inline unsigned char dateType, Second, Min, Hour, Day, Month,
            Year;
        static inline char datesmon, datemmon, datesday, datemday, mld[13], shm[13], mm[13], ss[13];
        static inline unsigned long Current_Time, Current_Date;
        static inline int datesyear, datemyear;

    public:
        static void GetDate(void);
        static int  DateConvert(unsigned char type);
        static void InitRtc(void);
        static void UpdateDate(void);
        static void UpdateTime(void);
    };
}
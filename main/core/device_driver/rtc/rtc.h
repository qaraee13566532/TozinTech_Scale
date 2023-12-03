
#pragma once
#include <iostream>
#define DATEOFST 79


namespace REALTIME_CLOCK
{
    class Rtc
    {
    public:
        static inline uint8_t dateType, Second, Min, Hour, Day, Month,
            Year;
        static inline int8_t datesmon, datemmon, datesday, datemday;
        static inline const int8_t mld[13]={0,1,(int8_t)-1,0,0,1,1,2,3,3,4,4,5};
        static inline const int8_t shm[13]={0,1,2,3,4,5,6,6,6,6,6,6,5};
        static inline const int8_t mm[13] ={0,31,28,31,30,31,30,31,31,30,31,30,31};
        static inline const int8_t ss[13] ={0,31,31,31,31,31,31,30,30,30,30,30,29};
        static inline uint32_t Current_Time, Current_Date;
        static inline int16_t datesyear, datemyear;

    public:
        static void GetDate(void);
        static uint8_t  DateConvert(uint8_t type);
        static void UpdateDate(void);
        static void UpdateTime(void);
    };
}

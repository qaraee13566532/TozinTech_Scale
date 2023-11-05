
#pragma once

#define DATEOFST 79


namespace REALTIME_CLOCK
{
    class Rtc
    {
    public:
        static inline unsigned char dateType, Second, Min, Hour, Day, Month,
            Year;
        static inline char datesmon, datemmon, datesday, datemday;
        static inline const char mld[13]={0,1,(char)-1,0,0,1,1,2,3,3,4,4,5};
        static inline const char shm[13]={0,1,2,3,4,5,6,6,6,6,6,6,5};
        static inline const char mm[13] ={0,31,28,31,30,31,30,31,31,30,31,30,31};
        static inline const char ss[13] ={0,31,31,31,31,31,31,30,30,30,30,30,29};
        static inline unsigned long Current_Time, Current_Date;
        static inline int datesyear, datemyear;

    public:
        static void GetDate(void);
        static unsigned char  DateConvert(unsigned char type);
        static void UpdateDate(void);
        static void UpdateTime(void);
    };
}

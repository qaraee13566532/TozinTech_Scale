#include "core\device_driver\rtc\rtc.h"
#include <time.h>
#include <sys/time.h>

namespace REALTIME_CLOCK
{
    void Rtc::UpdateDate(void)
    {
        Year = Current_Date / 10000;
        Month = (Current_Date - (Current_Date / 10000) * 10000) / 100;
        Day = Current_Date % 100;
    }
    void Rtc::UpdateTime(void)
    {
        Hour = Current_Time / 10000;
        Min = (Current_Time - (Current_Time / 10000) * 10000) / 100;
        Second = Current_Time % 100;
    }
    void Rtc::InitRtc(void)
    {
    }
    int Rtc::DateConvert(unsigned char type)
    {
        long datetemp2, datetemp1, datetemp3;
        int ytemp;
        unsigned char datei;
        if (type)
        {
            ytemp = datesyear;
            if ((ytemp < 61 && ytemp > 50) || datesday > 31 || datesmon > 12 || !datesday || !datesmon)
                return 0;
            if (ytemp > 50)
                ytemp += 1300;
            else
                ytemp = ytemp + 1400;
            ytemp -= 1;
            datetemp2 = (long)ytemp;
            datetemp2 -= 1360;
            datetemp1 = datetemp2 * 365;
            if (datetemp2 < 14)
                datetemp1 += ((datetemp2 + 2) / 4);
            else
                datetemp1 += (3 + (datetemp2 - 11) / 4);
            ytemp = (int)datesmon;
            ytemp = 30 * (ytemp - 1) + (int)shm[ytemp - 1] + (int)datesday;
            datetemp1 += (long)ytemp;
            datetemp1 += DATEOFST;
            datetemp2 = 0;
            datetemp3 = 0;
            datei = 0;
            do
            {
                datetemp2 += 365;
                if (datei % 4 == 2)
                    datetemp2 += 1;
                if (datetemp2 >= datetemp1)
                {
                    datemyear = 81 + (int)datei;
                    ytemp = (int)(datetemp1 - datetemp3);
                    break;
                }
                datetemp3 = datetemp2;
                datei++;
            } while (datei < 100);
            datetemp2 = 0;
            datetemp1 = 0;
            datei = 0;
            do
            {
                datetemp1 += (long)mm[datei + 1];
                if (datemyear % 4 == 3 && datei == 1)
                    datetemp1 += 1;
                if ((int)datetemp1 >= ytemp)
                {
                    datemmon = datei;
                    datemday = (char)(ytemp - (int)datetemp2);
                    break;
                }
                datetemp2 = datetemp1;
                datei++;
            } while (datei < 13);
            datemyear = (datemyear + 1) % 100;
            datemmon += 1;
        }
        else
        {
            ytemp = datemyear;
            if ((ytemp < 83 && ytemp > 70) || datemday > 31 || datemmon > 12 || !datemday || !datemmon)
                return 0;
            if (ytemp > 70)
                ytemp += 1900;
            else
                ytemp += 2000;
            ytemp -= 1;
            datetemp2 = (long)ytemp;
            datetemp2 -= 1981;
            datetemp1 = datetemp2 * 365;
            datetemp1 += ((datetemp2 + 1) / 4);
            ytemp = (int)datemmon;
            ytemp = 30 * (ytemp - 1) + (int)mld[ytemp - 1] + (int)datemday;
            if (datemmon > 2 && datetemp2 % 4 == 2)
                ytemp += 1;
            datetemp1 += (long)ytemp;
            datetemp1 -= DATEOFST;
            datetemp2 = 0;
            datetemp3 = 0;
            datei = 0;
            do
            {
                datetemp2 += 365;
                if (datei % 4 == 1 && datei < 13)
                    datetemp2 += 1;
                if (datei % 4 == 2 && datei > 13)
                    datetemp2 += 1;
                if (datetemp2 >= datetemp1)
                {
                    datesyear = 60 + (int)datei;
                    ytemp = (int)(datetemp1 - datetemp3);
                    break;
                }
                datetemp3 = datetemp2;
                datei++;
            } while (datei < 100);
            datetemp2 = 0;
            datetemp1 = 0;
            datei = 0;
            do
            {
                datetemp1 += (long)ss[datei + 1];
                if (datesyear % 4 == 1 && datei == 11 && datesyear < 73)
                    datetemp1 += 1;
                if (datesyear % 4 == 2 && datei == 11 && datesyear > 73)
                    datetemp1 += 1;
                if ((int)datetemp1 >= ytemp)
                {
                    datesmon = datei;
                    datesday = (char)(ytemp - (int)datetemp2);
                    break;
                }
                datetemp2 = datetemp1;
                datei++;
            } while (datei < 13);
            datesyear = (datesyear + 1) % 100;
            datesmon += 1;
        }
        return 1;
    }
    void Rtc::GetDate(void)
    {
        time_t now;
        struct tm timeinfo;
        time(&now);
        setenv("TZ", "IRST-3:30", 1);
        tzset();
        localtime_r(&now, &timeinfo);
        Second = timeinfo.tm_sec;
        Min = timeinfo.tm_min;
        Hour = timeinfo.tm_hour;
        Day = timeinfo.tm_mday;
        Month = timeinfo.tm_mon + 1;
        Year = timeinfo.tm_year;
        datemyear = Year;
        datemmon = Month;
        datemday = Day;
        DateConvert(0);
        Current_Time = (unsigned long)Hour * 10000;
        Current_Time += (unsigned long)Min * 100;
        Current_Time += (unsigned long)Second;
        if (dateType == 0)
        {
            Current_Date = (unsigned long)datesyear * 10000;
            Current_Date += (unsigned long)datesmon * 100;
            Current_Date += (unsigned long)datesday;
        }
        else
        {
            Current_Date = (unsigned long)datemyear * 10000;
            Current_Date += (unsigned long)datemmon * 100;
            Current_Date += (unsigned long)datemday;
        }
    }
}

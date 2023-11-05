
#pragma once

#include <time.h>
#include <sys/time.h>
#include "esp_sntp.h"

#define INET6_ADDRSTRLEN 48

namespace SNTP
{
    class Sntp
    {
        static inline const char *TAG;
    public:
        static inline bool autoAdjustDateTime;
        static inline bool isRequestedForDateTime;
        static inline bool isDateTimeReceived;

    public:
        static void requestDateTime(void);
        static void InitSntp(bool autoAdjust);

    private:
        static void time_sync_notification_cb(struct timeval *tv);
    };
}
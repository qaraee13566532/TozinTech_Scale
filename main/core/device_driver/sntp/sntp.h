
#pragma once

#include <time.h>
#include <sys/time.h>
#include "esp_sntp.h"


#define INET6_ADDRSTRLEN 48

namespace SNTP
{
    class Sntp
    {
        static inline bool autoAdjustDateTime;
        static inline const char *TAG;
        static inline bool isUpdated;

    public:
        static void InitSntp(void);
        static void time_sync_notification_cb(struct timeval *tv);
        static void requestDateTime(void);
    };
}
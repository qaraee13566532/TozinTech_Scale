#pragma once

#include "esp_timer.h"

namespace GLOBAL_TIMER
{

    class Timer
    {
        static inline esp_timer_handle_t timer_handler;
        static inline unsigned char externalReadAdcTime;
    public:
        static void TimerCallback(void *param);
        static void InitTimer(void);
    };
}
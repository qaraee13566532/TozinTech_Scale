#pragma once

#include "esp_timer.h"

namespace GLOBAL_TIMER
{

    class Timer
    {
        static inline esp_timer_handle_t timer_handler;
        static inline uint8_t externalReadAdcTime, chipAdcReadTime;
        static inline uint32_t requestDateTime;

    public:
        static inline uint32_t freeRuningTimerMS;
        static inline uint32_t AuxfreeRuningTimerMS;

    public:
        static void TimerCallback(void *param);
        static void InitTimer(void);
    };
}
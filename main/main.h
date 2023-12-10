#pragma once

#include "esp_timer.h"

namespace MAIN_TASK
{
    class Main
    {
        static inline uint16_t appState;

    public:
        static void RunTasks(void);
        static void Initilize(void);

    };
}
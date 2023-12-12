#pragma once

#include <iostream>

#define SALE_INIT 0
#define SALE_RUN_TASK 1

namespace SALE
{
    class Sale
    {
        static inline uint8_t  keyCode;
        static inline bool  keytype;
    public:
        static inline uint8_t state;
        static void RunTasks(uint16_t &appState);
        static void Initialize(void);
    };
}
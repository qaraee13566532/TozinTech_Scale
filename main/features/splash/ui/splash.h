
#pragma once

#include <atomic>
#include <future>

#define SPLASH_INIT 0
#define SPLASH_RUN_TASK 1

namespace SPLASH
{
    class Splash
    {
        static inline uint8_t keyCode;
        static inline bool keytype;
        static inline bool checkCalibKey;
        static inline std::future<void> demoDelay;
        static inline std::future_status status;

    public:
        static inline uint8_t state;
        static inline std::atomic<bool> cancellationToken;
        static void RunTasks(uint16_t &appState);
        static void Demo();
        static void Initialize(void);
    };
}

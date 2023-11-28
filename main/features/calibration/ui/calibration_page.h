
#pragma once

#define PlatformDefinationInitialize 0
#define PlatformTask 1

namespace CALIBRATION
{
    class CalibrationPage
    {
        CalibrationPage();
    public:
        static void RunTasks(void);
    };
}
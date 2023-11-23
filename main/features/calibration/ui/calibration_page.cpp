#include "features/calibration/ui/calibration_page.h"
#include "core/definations.h"
#include "core/device_driver/seven_segment_display/seven_segment_display.h"
using namespace SSEG_DEVICE_DRIVER;

namespace CALIBRATION
{
    void CalibrationPage::RunTasks(void)
    {
        Sseg::BlankDisplay();
        Sseg::Scroll_Message("CALIbrAtion",TOTAL_PRICE,8,200,1,false);
    };
}
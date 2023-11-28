#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "core/device_driver/matrix_keyboard/keyboard.h"
#include "core/device_driver/timer/timer.h"
#include "core/device_driver/gpio/gpio.h"
#include "core/device_driver/seven_segment_display/seven_segment_display.h"
#include "core/device_driver/adc_ads1232/adc.h"
#include "core/device_driver/chip_adc/chip_adc.h"
#include "core/device_driver/commiunication_uart/comm_uart.h"
#include "core/device_driver/printer_uart/printer_uart.h"
#include "core/device_driver/storage/storage.h"
#include "core/device_driver/wifi/wifi.h"
#include "core/device_driver/nvs/nvs.h"
#include "core/device_driver/sntp/sntp.h"


using namespace SSEG_DEVICE_DRIVER;
using namespace GLOBAL_TIMER;
using namespace GPIO;
using namespace MATRIX_KEYBOARD;
using namespace ADC_ADS1232;
using namespace CHIP_ADC;
using namespace COMMIUNICATION_UART;
using namespace PRINTER_UART;
using namespace STORAGE;
using namespace WIFI;
using namespace NVS;
using namespace SNTP;


void initialize(void)
{
    
    Gpio::InitGpio();
    Keyboard::InitKeyboard();
    Sseg::InitDisplay(1);
    Timer::InitTimer();
    Sseg::DialpayStart();
    ChipAdc::InitChipAdc();
    Adc::InitAdc();
    CommiunicationUart::InitCommUart();
    PrinterUart::InitPrinterUart();
    vTaskDelay(100 / portTICK_PERIOD_MS);
    Sseg::Write_Message_To_Display("PAnd", WEIGHT, 5, true);
    Sseg::Write_Message_To_Display("ScALE", UNIT_PRICE, 6, true);
    Sseg::Write_Message_To_Display("VEr-1.00", TOTAL_PRICE, 7, true);
    Storage::InitStorage();
    Nvs::InitNvs();
    Wifi::InitWifi(WIFI_STA_MODE);
    Sntp::InitSntp(false);
}


#include <codecvt>
#include <cstdint>
#include <iostream>
#include <locale>
#include <string>

#include "features/splash/ui/splash.h"
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
#include "definations.h"
#include "main.h"
#include "core/calibration/ui/calibration_page.h"
#include "features\sale\ui\sale_page.h"
#include "FarsiType.h"

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
using namespace SPLASH;
using namespace CALIBRATION;
using namespace MAIN_TASK;
using namespace SALE;

namespace MAIN_TASK
{

  void Main::Initilize(void)
  {
    Gpio::InitGpio();
    Keyboard::InitKeyboard();
    Sseg::InitDisplay(1);
    Sseg::DialpayStart();
    Timer::InitTimer();
    ChipAdc::InitChipAdc();
    Adc::InitAdc();
    CommiunicationUart::InitCommUart();
    PrinterUart::InitPrinterUart();
    Sseg::Write_Message_To_Display("t-tECH", WEIGHT, 6, true);
    Sseg::Write_Message_To_Display("SCALE", UNIT_PRICE, 6, true);
    Sseg::Write_Message_To_Display("Vr-1.01.01", TOTAL_PRICE, 8, true);
    Storage::InitStorage();
    Nvs::InitNvs();
    // Wifi::InitWifi(WIFI_STA_MODE);
    // Sntp::InitSntp(false);
  }

  void Main::RunTasks(void)
  {
    appState = SPLASH_SCREEN_PAGE;
    while (true)
    {
      switch (appState)
      {
      case SPLASH_SCREEN_PAGE:

        Splash::RunTasks(appState);
        break;
      case SALE_PAGE:
        Sale::RunTasks(appState);
        break;
      case CALIBRATION_PAGE:
        CalibrationPage::RunTasks();
        break;
      }
    }
  }

  extern "C" void app_main(void)
  {
    Main::Initilize();
    Main::RunTasks();
  }
}
// class A
// {
// public:
//   A()
//   { // implicit capture of this is deprecated in c++20
//     m[0] = [this](int v)
//     { F1(v); };
//     m[1] = [this](int v)
//     { F2(v); };
//   }

//   void F1(int v) { std::cout << "F1: " << v << endl; }
//   void F2(int v) { std::cout << "F2: " << v << endl; }
//   void O(int i, int v) { m[i](v); }

// private:
//   map<int, function<void(int)>> m;
// };

// uint8_t keydata = 0, keyState = 0;
// bool keytype = false;
// int16_t cmc = 0;

// A a;
// a.O(0, 16);
// a.O(1, 19);

// cJSON *root;
// string TAG;
// root = cJSON_CreateObject();
// esp_chip_info_t chip_info;
// esp_chip_info(&chip_info);
// cJSON_AddStringToObject(root, "version", IDF_VER);
// cJSON_AddNumberToObject(root, "cores", chip_info.cores);
// cJSON_AddTrueToObject(root, "flag_true");
// cJSON_AddFalseToObject(root, "flag_false");
// string my_json_string = cJSON_Print(root);
// ESP_LOGI(TAG.c_str(), "my_json_string\n%s", my_json_string.c_str());
// cJSON_Delete(root);
// ESP_LOGI(TAG.c_str(), "Deserialize.....");
// cJSON *root2 = cJSON_Parse(my_json_string.c_str());
// if (cJSON_GetObjectItem(root2, "flag_false"))
// {
//   bool flag_false = cJSON_GetObjectItem(root2, "flag_false")->valueint;
//   ESP_LOGI(TAG.c_str(), "flag_false=%d", flag_false);
// }
// cJSON_Delete(root2);

// initialize();
// CalibrationPage::RunTasks();

// int16_t cc = 0;
// int8_t *buf = (int8_t *)malloc(100);

// https://github.com/espressif/esp-idf/tree/master/components/json

// Sntp::isRequestedForDateTime = true;
// Calibration firstPlatform(FIRST_PLATFORM);
// bool ddd = false;

// for (;;)
// {
//   Keyboard::readKeyBuffer(keydata, keytype);
//   try
//   {
//     if (keydata == 1 && keytype == false)
//     {
//       CalibrationPage::RunTasks();
//     }
//     if (keydata == 4 && keytype == false)
//     {
//       Adc::useFiltering[FIRST_PLATFORM] = true;
//       ddd = true;
//     }
//     if (keydata == 2 && keytype == false)
//     {
//       Adc::useFiltering[FIRST_PLATFORM] = false;
//       ddd = false;
//     }
//   }
//   catch (const std::exception &e)
//   {
//     std::cerr << e.what() << '\n';
//   }

// if (Sntp::isDateTimeReceived)
// {
//   Sntp::isDateTimeReceived = false;
//   Rtc::GetDate();
//   printf("data = %d-%d-%d , %ld \n", Rtc::Year, Rtc::Month, Rtc::Day, Rtc::Current_Date);
// }

// if (Adc::isAdcDataReceived[FIRST_PLATFORM])
// {
//   // printf("%ld,%ld\n",Adc::rawAdc[FIRST_PLATFORM],Adc::filterdRawAdc[FIRST_PLATFORM]);
//   ddd == false ? printf("%ld\n", Adc::rawAdc[FIRST_PLATFORM]) : printf("%ld\n", Adc::filterdRawAdc[FIRST_PLATFORM]);
//   // if(cmc++>14)
//   // {
//   //   cmc=0;
//   //   printf("\n");
//   // }
//   ddd == false ? Sseg::Write_Number_To_Display(Adc::rawAdc[FIRST_PLATFORM], TOTAL_PRICE, false, 0, false, false, 8, true, true) : Sseg::Write_Number_To_Display(Adc::filterdRawAdc[FIRST_PLATFORM], TOTAL_PRICE, false, 0, false, false, 8, true, true);

//   Adc::isAdcDataReceived[FIRST_PLATFORM] = 0;
//   //  printf("DC = %d\n", ChipAdc::DcAdapterVoltage);
//   //   printf("BA = %d\n", ChipAdc::BatteryVoltage);
//   // sprintf(buf, "--->  data is %d\n", cc);
//   // CommiunicationUart::CommTransmitData(buf);
//   // PrinterUart::PrinterTransmitData(buf);
//   //   Rtc::GetDate();
//   //   printf("data = %d-%d-%d , %ld \n", Rtc::Year, Rtc::Month, Rtc::Day,Rtc::Current_Date);
// }
// }
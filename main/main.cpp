#include <iostream>

using std::cout;
using std::endl;
using std::runtime_error;

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "core/include/baseCommiunicationEntity.h"
#include "core/include/plu.h"
#include "core/device_driver/matrix_keyboard/keyboard.h"
#include "esp_timer.h"
#include "core/device_driver/seven_segment_display/seven_segment_display.h"
#include "core/device_driver/chip_adc/chip_adc.h"
#include "core/device_driver/commiunication_uart/comm_uart.h"
#include "core/device_driver/printer_uart/printer_uart.h"
#include "core/device_driver/rtc/rtc.h"
#include "core/device_driver/storage/storage.h"
#include "core/device_driver/sntp/sntp.h"
#include "core/device_driver/matrix_keyboard/keyboard.h"
#include "core/device_driver/adc_ads1232/adc.h"
#include "features/calibration/usecase/calibration.h"
#include "features/calibration/ui/calibration_page.h"

// #include "cJSON.h"
// #include "esp_log.h"
// #include "esp_chip_info.h"

extern void initialize(void);

extern "C"
{
  void app_main();
}

using namespace ADC_ADS1232;
using namespace SSEG_DEVICE_DRIVER;
using namespace CHIP_ADC;
using namespace COMMIUNICATION_UART;
using namespace PRINTER_UART;
using namespace REALTIME_CLOCK;
using namespace STORAGE;
using namespace SNTP;
using namespace MATRIX_KEYBOARD;
using namespace CALIBRATION;

void app_main(void)
{

  // unsigned char keydata = 0, keyState = 0;
  // bool keytype = false;
  // int cmc = 0;

  initialize();

  // cJSON *root;
  // root = cJSON_CreateObject();
  // esp_chip_info_t chip_info;
  // esp_chip_info(&chip_info);
  // cJSON_AddStringToObject(root, "version", IDF_VER);
  // cJSON_AddNumberToObject(root, "cores", chip_info.cores);
  // cJSON_AddTrueToObject(root, "flag_true");
  // cJSON_AddFalseToObject(root, "flag_false");
  // char *my_json_string = cJSON_Print(root);
  // ESP_LOGI(TAG, "my_json_string\n%s", my_json_string);
  // cJSON_Delete(root);
  // ESP_LOGI(TAG, "Deserialize.....");
  // cJSON *root2 = cJSON_Parse(my_json_string);
  // if (cJSON_GetObjectItem(root2, "version")) {
  // 	char *version = cJSON_GetObjectItem(root2,"version")->valuestring;
  // 	ESP_LOGI(TAG, "version=%s",version);
  // }
  // if (cJSON_GetObjectItem(root2, "cores")) {
  // 	int cores = cJSON_GetObjectItem(root2,"cores")->valueint;
  // 	ESP_LOGI(TAG, "cores=%d",cores);
  // }
  // if (cJSON_GetObjectItem(root2, "flag_true")) {
  // 	bool flag_true = cJSON_GetObjectItem(root2,"flag_true")->valueint;
  // 	ESP_LOGI(TAG, "flag_true=%d",flag_true);
  // }
  // if (cJSON_GetObjectItem(root2, "flag_false")) {
  // 	bool flag_false = cJSON_GetObjectItem(root2,"flag_false")->valueint;
  // 	ESP_LOGI(TAG, "flag_false=%d",flag_false);
  // }
  // cJSON_Delete(root2);
  // cJSON_free(my_json_string);

  // int cc = 0;
  // char *buf = (char *)malloc(100);

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
  CalibrationPage::RunTasks();
}

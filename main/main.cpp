#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "core/entities/baseCommiunicationEntity.h"
#include "core/entities/plu.h"
#include "core/device_driver/matrix_keyboard/keyboard.h"
#include "esp_timer.h"
#include "core/device_driver/weight/weight.h"
#include "core/device_driver/seven_segment_display/seven_segment_display.h"
#include "core/device_driver/chip_adc/chip_adc.h"
#include "core/device_driver/commiunication_uart/comm_uart.h"
#include "core/device_driver/printer_uart/printer_uart.h"
#include "core/device_driver/rtc/rtc.h"
#include "core/device_driver/storage/storage.h"
#include "cJSON.h"
#include "esp_log.h"
#include "esp_chip_info.h"

extern void initialize(void);
static inline const char *TAG = "example";
extern "C"
{
  void app_main();
}

using namespace ADS1232_WEIGHT;
using namespace SSEG_DEVICE_DRIVER;
using namespace CHIP_ADC;
using namespace COMMIUNICATION_UART;
using namespace PRINTER_UART;
using namespace REALTIME_CLOCK;
using namespace STORAGE;

void app_main(void)
{
  initialize();
  cJSON *root;
  root = cJSON_CreateObject();
  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);
  cJSON_AddStringToObject(root, "version", IDF_VER);
  cJSON_AddNumberToObject(root, "cores", chip_info.cores);
  cJSON_AddTrueToObject(root, "flag_true");
  cJSON_AddFalseToObject(root, "flag_false");
  // const char *my_json_string = cJSON_Print(root);
  char *my_json_string = cJSON_Print(root);
  ESP_LOGI(TAG, "my_json_string\n%s", my_json_string);
  cJSON_Delete(root);

  int cc = 0;
  char *buf = (char *)malloc(100);
  for (;;)
  {
    if (Weight::isWeightReceived)
    {
      //    printf("%ld\n", Weight::rawAdcNumber);
      Sseg::Write_Number_To_Display(Weight::rawAdcNumber, TOTAL_PRICE, false, 0, false, false, 8, true, true);
      Weight::isWeightReceived = 0;
      //  printf("DC = %d\n", ChipAdc::DcAdapterVoltage);
      //   printf("BA = %d\n", ChipAdc::BatteryVoltage);
      // sprintf(buf, "--->  data is %d\n", cc);
      // CommiunicationUart::CommTransmitData(buf);
      // PrinterUart::PrinterTransmitData(buf);
      //  Rtc::GetDate();
      //  printf("second  = %d\n", Rtc::Second);
    }
  }
}

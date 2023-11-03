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

extern void initialize(void);

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


void app_main(void)
{
  initialize();
  int cc = 0;
  char *buf = "                                                   ";
  printf("Initialized successfully .\n");
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  for (;;)
  {
    if (Weight::isWeightReceived)
    {
  //    printf("%ld\n", Weight::rawAdcNumber);
      Sseg::Write_Number_To_Display(Weight::rawAdcNumber, TOTAL_PRICE, false, 0, false, false, 8, true, true);
      Weight::isWeightReceived = 0;
    //  printf("DC = %d\n", ChipAdc::DcAdapterVoltage);
   //   printf("BA = %d\n", ChipAdc::BatteryVoltage);
      sprintf(buf, "--->  data is %d\n", cc);
      //CommiunicationUart::CommTransmitData(buf);
      //PrinterUart::PrinterTransmitData(buf);
    //  Rtc::GetDate();
    //  printf("second  = %d\n", Rtc::Second);
    }
  }
}

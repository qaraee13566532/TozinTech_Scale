#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "core/entities/baseCommiunicationEntity.h"
#include "core/entities/plu.h"
#include "core/device_driver/matrix_keyboard/keyboard.h"
#include "esp_timer.h"
#include "core/device_driver/weight/weight.h"

extern void initialize(void);

extern "C"
{
  void app_main();
}

using namespace ADS1232_WEIGHT;


void app_main(void)
{
  initialize();

  printf("Initialized successfully .\n");
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  for (;;)
  {
    if (Weight::isWeightReceived)
    {
      printf("adc code = %ld\n", Weight::rawAdcNumber);
      Weight::isWeightReceived = 0;
    }
  }
}

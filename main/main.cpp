#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "core/entities/baseCommiunicationEntity.h"
#include "core/entities/plu.h"
#include "core/device_driver/matrix_keyboard/keyboard.h"
#include "esp_timer.h"

extern void initialize(void);
extern "C"
{
  void app_main();
}

void app_main(void)
{
  printf("Initialize .... !\n");
  initialize();
}

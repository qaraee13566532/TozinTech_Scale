#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "core/entities/baseCommiunicationEntity.h"
#include "core/entities/plu.h"
#include "core/device_driver/matrix_keyboard/keyboard.h"
#include "esp_timer.h"

extern "C"
{
  void app_main();
}

void timer_callback(void *param)
{
  MATRIX_KEYBOARD::Keyboard::getKeys();
}

void init_timer(void)
{
	//xTaskCreate(timer_callback, "timer_callback", 2048, NULL, 1, NULL);
	 esp_timer_handle_t timer_handler;
	const esp_timer_create_args_t my_timer_args = {
		.callback = &timer_callback,
		.name = "My Timer"};
	ESP_ERROR_CHECK(esp_timer_create(&my_timer_args, &timer_handler));
	ESP_ERROR_CHECK(esp_timer_start_periodic(timer_handler, 1000));
}



void app_main(void)
{
  printf("Hello world!\n");
  MATRIX_KEYBOARD::Keyboard::initKeyboard();
  init_timer();
}

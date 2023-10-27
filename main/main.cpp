#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "systeminfo.h"
#include "plu.cpp"

extern "C"
{
    void app_main();
}

void app_main(void)
{
    Plu pluData;
    pluData.setData();
    printf("Hello world!\n");
    esp_systeminfo info;
    info.print();
    for (int i = 10; i >= 0; i--)
    {
        printf("Restarting in %d seconds... %d\n", i,pluData.getData());
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
}

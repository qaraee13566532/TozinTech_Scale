
#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include <iostream>
using std::string;

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT BIT1
#define EXAMPLE_ESP_WIFI_SSID            CONFIG_ESP_WIFI_SSID
#define EXAMPLE_ESP_WIFI_PASS            CONFIG_ESP_WIFI_PASSWORD
#define EXAMPLE_ESP_MAXIMUM_RETRY        CONFIG_ESP_MAXIMUM_RETRY
#define EXAMPLE_ESP_WIFI_CHANNEL         CONFIG_ESP_WIFI_CHANNEL
#define EXAMPLE_MAX_STA_CONN             CONFIG_ESP_MAX_STA_CONN
#define WIFI_STA_MODE                    true
#define WIFI_SOFTAP_MODE                 false

#if CONFIG_ESP_WIFI_AUTH_OPEN
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_OPEN
#elif CONFIG_ESP_WIFI_AUTH_WEP
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WEP
#elif CONFIG_ESP_WIFI_AUTH_WPA_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA2_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA_WPA2_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA_WPA2_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA3_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA3_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA2_WPA3_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_WPA3_PSK
#elif CONFIG_ESP_WIFI_AUTH_WAPI_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WAPI_PSK
#endif

namespace WIFI
{
    class Wifi
    {
    public:
        static inline string TAG;
        static inline int16_t s_retry_num = 0;
        static inline EventGroupHandle_t s_wifi_event_group;
        static inline wifi_config_t wifi_config;

    public:
        static void InitWifi(bool StaSoftApMode);
    private:
        static void InitWifiSta(void);
        static void InitWifiSoftAp(void);
        static void sta_wifi_event_handler(void *arg, esp_event_base_t event_base,
                                           int32_t event_id, void *event_data);
        static void softap_wifi_event_handler(void *arg, esp_event_base_t event_base,
                                              int32_t event_id, void *event_data);
    };
}
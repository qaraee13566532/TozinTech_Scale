
#include "core\device_driver\wifi\wifi.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "string.h"
#include "esp_mac.h"
#include <iostream>
using std::string;

namespace WIFI
{

    void Wifi::InitWifi(bool StaSoftApMode)
    {
        switch (StaSoftApMode)
        {
        case true:
            TAG = "wifi station";
            InitWifiSta();
            break;
        case false:
            TAG = "wifi softap";
            InitWifiSoftAp();
            break;
        }
    }
    void Wifi::softap_wifi_event_handler(void *arg, esp_event_base_t event_base,
                                         int32_t event_id, void *event_data)
    {
        if (event_id == WIFI_EVENT_AP_STACONNECTED)
        {
            wifi_event_ap_staconnected_t *event = (wifi_event_ap_staconnected_t *)event_data;
            ESP_LOGI(TAG.c_str(), "station " MACSTR " join, AID=%d",
                     MAC2STR(event->mac), event->aid);
        }
        else if (event_id == WIFI_EVENT_AP_STADISCONNECTED)
        {
            wifi_event_ap_stadisconnected_t *event = (wifi_event_ap_stadisconnected_t *)event_data;
            ESP_LOGI(TAG.c_str(), "station " MACSTR " leave, AID=%d",
                     MAC2STR(event->mac), event->aid);
        }
    }

    void Wifi::InitWifiSoftAp(void)
    {
        ESP_ERROR_CHECK(esp_netif_init());
        ESP_ERROR_CHECK(esp_event_loop_create_default());
        esp_netif_create_default_wifi_ap();

        wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
        ESP_ERROR_CHECK(esp_wifi_init(&cfg));

        ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                            ESP_EVENT_ANY_ID,
                                                            &softap_wifi_event_handler,
                                                            NULL,
                                                            NULL));

        strcpy((char *)wifi_config.ap.ssid, EXAMPLE_ESP_WIFI_SSID);
        wifi_config.ap.ssid_len = strlen(EXAMPLE_ESP_WIFI_SSID);
        wifi_config.ap.channel = EXAMPLE_ESP_WIFI_CHANNEL;
        wifi_config.ap.max_connection = EXAMPLE_MAX_STA_CONN;
        wifi_config.ap.authmode = WIFI_AUTH_WPA_WPA2_PSK;
        wifi_config.ap.pmf_cfg.required = false;
        strcpy((char *)wifi_config.sta.password, EXAMPLE_ESP_WIFI_PASS);

        if (strlen(EXAMPLE_ESP_WIFI_PASS) == 0)
        {
            wifi_config.ap.authmode = WIFI_AUTH_OPEN;
        }

        ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
        ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
        ESP_ERROR_CHECK(esp_wifi_start());

        ESP_LOGI(TAG.c_str(), "wifi_init_softap finished. SSID:%s password:%s channel:%d",
                 EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS, EXAMPLE_ESP_WIFI_CHANNEL);
    }

    void Wifi::sta_wifi_event_handler(void *arg, esp_event_base_t event_base,
                                      int32_t event_id, void *event_data)
    {
        if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
        {
            esp_wifi_connect();
        }
        else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
        {
            if (s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY)
            {
                esp_wifi_connect();
                s_retry_num++;
                ESP_LOGI(TAG.c_str(), "retry to connect to the AP");
            }
            else
            {
                xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
            }
            ESP_LOGI(TAG.c_str(), "connect to the AP fail");
        }
        else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
        {
            ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
            ESP_LOGI(TAG.c_str(), "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
            s_retry_num = 0;
            xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
        }
    }
    void Wifi::InitWifiSta(void)
    {
        s_wifi_event_group = xEventGroupCreate();

        ESP_ERROR_CHECK(esp_netif_init());

        ESP_ERROR_CHECK(esp_event_loop_create_default());
        esp_netif_create_default_wifi_sta();

        wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
        ESP_ERROR_CHECK(esp_wifi_init(&cfg));

        esp_event_handler_instance_t instance_any_id;
        esp_event_handler_instance_t instance_got_ip;
        ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                            ESP_EVENT_ANY_ID,
                                                            &sta_wifi_event_handler,
                                                            NULL,
                                                            &instance_any_id));
        ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                            IP_EVENT_STA_GOT_IP,
                                                            &sta_wifi_event_handler,
                                                            NULL,
                                                            &instance_got_ip));
        strcpy((char *)wifi_config.sta.ssid, EXAMPLE_ESP_WIFI_SSID);
        strcpy((char *)wifi_config.sta.password,EXAMPLE_ESP_WIFI_PASS);
        wifi_config.sta.threshold.authmode = ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD;
        wifi_config.sta.sae_pwe_h2e = WPA3_SAE_PWE_BOTH;

        ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
        ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
        ESP_ERROR_CHECK(esp_wifi_start());

        ESP_LOGI(TAG.c_str(), "wifi_init_sta finished.");

        /* Waiting until either the connection is established (WIFI_CONNECTED_BIT) or connection failed for the maximum
         * number of re-tries (WIFI_FAIL_BIT). The bits are set by event_handler() (see above) */
        EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
                                               WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                               pdFALSE,
                                               pdFALSE,
                                               portMAX_DELAY);

        /* xEventGroupWaitBits() returns the bits before the call returned, hence we can test which event actually
         * happened. */
        if (bits & WIFI_CONNECTED_BIT)
        {
            ESP_LOGI(TAG.c_str(), "connected to ap SSID:%s password:%s",
                     EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
        }
        else if (bits & WIFI_FAIL_BIT)
        {
            ESP_LOGI(TAG.c_str(), "Failed to connect to SSID:%s, password:%s",
                     EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
        }
        else
        {
            ESP_LOGE(TAG.c_str(), "UNEXPECTED EVENT");
        }
    }
}

#include "core\device_driver\sntp\sntp.h"
#include "esp_log.h"

namespace SNTP
{
    void Sntp::time_sync_notification_cb(struct timeval *tv)
    {
        ESP_LOGI(TAG, "Notification of a time synchronization event");
    }

    void Sntp::InitSntp(void)
    {
        if (autoAdjustDateTime == false)
            return;
        ESP_LOGI(TAG, "Initializing SNTP");
        sntp_setoperatingmode(SNTP_OPMODE_POLL);
        sntp_setservername(0, CONFIG_SNTP_TIME_SERVER);
        sntp_setservername(1, "pool.ntp.org"); // set the secondary NTP server (will be used only if SNTP_MAX_SERVERS > 1)
        sntp_set_time_sync_notification_cb(time_sync_notification_cb);
        sntp_init();
        ESP_LOGI(TAG, "List of configured NTP servers:");
        for (uint8_t i = 0; i < SNTP_MAX_SERVERS; ++i)
        {
            if (sntp_getservername(i))
            {
                ESP_LOGI(TAG, "server %d: %s", i, sntp_getservername(i));
            }
            else
            {
                char buff[INET6_ADDRSTRLEN];
                ip_addr_t const *ip = sntp_getserver(i);
                if (ipaddr_ntoa_r(ip, buff, INET6_ADDRSTRLEN) != NULL)
                    ESP_LOGI(TAG, "server %d: %s", i, buff);
            }
        }
    }
}
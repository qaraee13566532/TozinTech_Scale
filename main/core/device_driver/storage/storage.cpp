
#include "core\device_driver\storage\storage.h"
#include "esp_vfs.h"
#include "esp_vfs_fat.h"

namespace STORAGE
{
    void Storage::InitStorage(void)
    {
        s_wl_handle = WL_INVALID_HANDLE;
        TAG = "example";
        esp_vfs_fat_mount_config_t mount_config;
        mount_config.max_files = 10;
        mount_config.format_if_mount_failed = true;
        mount_config.allocation_unit_size = CONFIG_WL_SECTOR_SIZE;
        esp_err_t err = esp_vfs_fat_spiflash_mount_rw_wl(BASE_PATH, "storage", &mount_config, &s_wl_handle);
        if (err != ESP_OK)
        {
            ESP_LOGE(TAG, "Failed to mount FATFS (%s)", esp_err_to_name(err));
            return;
        }
        else
        {
            ESP_LOGI(TAG, "partition mount successfully .");
        }
        InitStorageFiles(PLU_PATH);
        InitStorageFiles(CUSTOMER_PATH);
        InitStorageFiles(CLERK_PATH);
        InitStorageFiles(BARCODE_PATH);
        InitStorageFiles(TAX_PATH);
        InitStorageFiles(DISCOUNT_PATH);
        InitStorageFiles(STORE_PATH);
        InitStorageFiles(REPORT_PATH);
        InitStorageFiles(SETTING_PATH);
        InitStorageFiles(WEIGHT_PATH);
    }
    esp_err_t Storage::InitStorageFiles(const char *path)
    {
        struct stat st;
        if (stat(path, &st) != 0)
        {
            FILE *f = fopen(path, "wb");
            if (f == NULL)
            {
                ESP_LOGE(TAG, "Failed to open storage file for writing");
                return ESP_FAIL;
            }
            fclose(f);
            ESP_LOGI(TAG, "File initialized");
            return ESP_OK;
        }
        else
        {
            ESP_LOGI(TAG, "File Exist ...");
        }
        return ESP_OK;
    }

}
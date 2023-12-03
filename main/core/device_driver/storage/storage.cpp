
#include "core\device_driver\storage\storage.h"
#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include <iostream>
using std::string;

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
        esp_err_t err = esp_vfs_fat_spiflash_mount_rw_wl(BASE_PATH.c_str(), "storage", &mount_config, &s_wl_handle);
        if (err != ESP_OK)
        {
            ESP_LOGE(TAG.c_str(), "Failed to mount FATFS (%s)", esp_err_to_name(err));
            return;
        }
        else
        {
            ESP_LOGI(TAG.c_str(), "partition mount successfully .");
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
    esp_err_t Storage::InitStorageFiles(const string path)
    {
        struct stat st;
        if (stat(path.c_str(), &st) != 0)
        {
            FILE *f = fopen(path.c_str(), "wb");
            if (f == NULL)
            {
                ESP_LOGE(TAG.c_str(), "Failed to open storage file for writing");
                return ESP_FAIL;
            }
            fclose(f);
            ESP_LOGI(TAG.c_str(), "File initialized");
            return ESP_OK;
        }
        else
        {
            ESP_LOGI(TAG.c_str(), "File Exist ...");
        }
        return ESP_OK;
    }
    esp_err_t Storage::Save(const string path, string data)
    {
        FILE *f = fopen(path.c_str(), "wb");
        if (f == NULL)
        {
            ESP_LOGE(TAG.c_str(), "Failed to open storage file for writing");
            return ESP_FAIL;
        }
        fwrite(data.c_str(),data.length(),1,f);
        fclose(f);
        ESP_LOGI(TAG.c_str(), "File Saved Successfully ...");
        return ESP_OK;
    }
    esp_err_t Storage::Load(string path, string &data,int size)
    {
        char * readData = (char *)malloc(size*2);
        FILE *f = fopen(path.c_str(), "rb");
        if (f == NULL)
        {
            ESP_LOGE(TAG.c_str(), "Failed to open storage file for writing");
            return ESP_FAIL;
        }
        fread(readData,size,1,f);
        data=readData;
        fclose(f);
        ESP_LOGI(TAG.c_str(), "File Read Successfully ...");
        return ESP_OK;
    }

}
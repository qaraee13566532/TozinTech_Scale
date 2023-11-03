
#pragma once

#include "esp_vfs.h"
#include "esp_vfs_fat.h"


#define STORAGE_MAX_CHAR_SIZE        128
#define BASE_PATH                    "/spiflash"
#define PLU_PATH                     "/spiflash/plu.csv"
#define CUSTOMER_PATH                "/spiflash/customer.csv"
#define CLERK_PATH                   "/spiflash/clerk.csv"
#define BARCODE_PATH                 "/spiflash/barcode.csv"
#define TAX_PATH                     "/spiflash/tax.csv"
#define DISCOUNT_PATH                "/spiflash/discount.csv"
#define STORE_PATH                   "/spiflash/store.csv"
#define REPORT_PATH                  "/spiflash/reports.csv"
#define SETTING_PATH                 "/spiflash/settings.csv"
#define CALIBRATION_PATH             "/spiflash/calibration.csv"
#define WEIGHT_PATH                  "/spiflash/weight.csv"

namespace STORAGE
{
    class Storage
    {
        static inline wl_handle_t s_wl_handle;
        static inline const char *TAG;

    public:
        static void InitStorage(void);
        static esp_err_t InitStorageFiles(char *path);
    };
}
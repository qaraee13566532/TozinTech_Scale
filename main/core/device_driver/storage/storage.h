
#pragma once

#include "esp_vfs.h"
#include "esp_vfs_fat.h"


#define STORAGE_MAX_CHAR_SIZE              128

inline const char * BASE_PATH           =         "/spiflash";
inline const char * PLU_PATH            =         "/spiflash/plu.json";
inline const char * CUSTOMER_PATH       =         "/spiflash/customer.json";
inline const char * CLERK_PATH          =         "/spiflash/clerk.json";
inline const char * BARCODE_PATH        =         "/spiflash/barcode.json";
inline const char * TAX_PATH            =         "/spiflash/tax.json";
inline const char * DISCOUNT_PATH       =         "/spiflash/discount.json";
inline const char * STORE_PATH          =         "/spiflash/store.json";
inline const char * REPORT_PATH         =         "/spiflash/reports.json";
inline const char * SETTING_PATH        =         "/spiflash/settings.json";
inline const char * CALIBRATION_PATH    =         "/spiflash/calibration.json";
inline const char * WEIGHT_PATH         =         "/spiflash/weight.json";

namespace STORAGE
{
    class Storage
    {
        static inline wl_handle_t s_wl_handle;
        static inline const char *TAG;

    public:
        static void InitStorage(void);
        static esp_err_t InitStorageFiles(const char *path);
    };
}
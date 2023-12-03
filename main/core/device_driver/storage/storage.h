
#pragma once

#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include <iostream>
using std::string;


#define STORAGE_MAX_CHAR_SIZE              128

inline const string BASE_PATH("/spiflash");
inline const string PLU_PATH("/spiflash/plu.json");
inline const string CUSTOMER_PATH("/spiflash/customer.json");
inline const string CLERK_PATH("/spiflash/clerk.json");
inline const string BARCODE_PATH ("/spiflash/barcode.json");
inline const string TAX_PATH("/spiflash/tax.json");
inline const string DISCOUNT_PATH("/spiflash/discount.json");
inline const string STORE_PATH("/spiflash/store.json");
inline const string REPORT_PATH("/spiflash/reports.json");
inline const string SETTING_PATH("/spiflash/settings.json");
inline const string CALIBRATION_PATH("/spiflash/calibration.json");
inline const string WEIGHT_PATH("/spiflash/weight.json");


namespace STORAGE
{
    class Storage
    {
        static inline wl_handle_t s_wl_handle;
        static inline string TAG;

    public:
        static void InitStorage(void);
        static esp_err_t InitStorageFiles(const string path);
        static esp_err_t Save(const string path,string data);
        static esp_err_t Load(const string path,string &data,int size);
    };
}
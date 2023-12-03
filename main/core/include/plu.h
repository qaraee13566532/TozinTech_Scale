#pragma once

#include "core/include/baseCommiunicationEntity.h"

#define   MAX_PLU_NAME_LENGHT   30
#define   MAX_BARCODE_LENGHT   30

namespace PLU
{
    class Plu : public BaseCommiunicationEntity

    {
    public:
        Plu()
        {
        }
        Plu(BaseCommiunicationEntity baseCasEntity) : BaseCommiunicationEntity(baseCasEntity)
        {
        }

    public:
        uint32_t sellPrice;
        uint32_t buyPrice;
        uint32_t pluNumber;
        uint16_t pluName[MAX_PLU_NAME_LENGHT];
        uint8_t barcodeID;
        uint8_t pluType;
        uint8_t pluUnit;
        uint8_t discountID;
        uint8_t taxID;
        bool isDeleted;
        bool isActived;
        uint8_t groupID;
        uint8_t department;
        uint16_t expireDate;
        uint16_t expireTime;
        uint8_t barcode[MAX_BARCODE_LENGHT];

    public:
        void setData(void)
        {
            barcodeID = 10;
        }

    public:
        uint8_t getData(void)
        {
            return barcodeID;
        }
    };
}
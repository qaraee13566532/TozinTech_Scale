#pragma once

#include "core/include/baseCommiunicationEntity.h"

#define MAX_PLU_NAME_LENGHT 30
#define MAX_BARCODE_LENGHT 30

namespace ITEM
{
    class Item : public BaseCommiunicationEntity

    {
    public:
        Item()
        {
        }
        Item(BaseCommiunicationEntity baseCasEntity) : BaseCommiunicationEntity(baseCasEntity)
        {
        }

    public:
        uint32_t sellPrice;
        uint32_t buyPrice;
        uint32_t itemCode;
        uint16_t description[MAX_PLU_NAME_LENGHT];
        uint16_t extendedDscription[MAX_PLU_NAME_LENGHT];
        uint8_t barcodeID;
        uint8_t itemType;
        uint8_t itemUint;
        uint8_t discountID;
        uint8_t taxID;
        bool isDeleted;
        bool isActived;
        uint8_t groupID;
        uint8_t departmentID;
        uint16_t expireDate;
        uint16_t expireTime;
        uint16_t tareValue;
        uint16_t tarepercent;
        uint8_t barcode[MAX_BARCODE_LENGHT];

    public:
    };
}
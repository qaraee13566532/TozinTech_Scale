
#pragma once

#include "core/include/baseCommiunicationEntity.h"
namespace REPORT
{
    class Report : public BaseCommiunicationEntity
    {
    public:
        Report()
        {
        }
        Report(BaseCommiunicationEntity baseCasEntity) : BaseCommiunicationEntity(baseCasEntity)
        {
        }

    public:
        uint32_t totalPrice;
        uint32_t unitPrice;
        uint32_t discountPrice;
        uint32_t taxPrice;
        uint16_t pluNumber;
        uint32_t weight;
        uint8_t itemCode[MAX_ITEM_CODE_LENGHT];
        uint16_t pluName[MAX_PLU_NAME_LENGHT];
        uint16_t qty;
        uint16_t pcs;
        uint16_t ticketNumber;
        uint8_t scaleNumber;
        uint8_t departmentNumber;
        uint8_t storeNumber;
        uint8_t pluType;
        uint8_t pluUnit;
        uint8_t year;
        uint8_t month;
        uint8_t day;
        uint8_t hour;
        uint8_t min;
        uint8_t sec;
        bool pluTicketDataType;
        bool isSynced;
        uint8_t saleStatus;
        uint8_t transactionType;
        uint8_t transactionCounter;
        uint8_t clerkCode;
        uint16_t clerckName[MAX_CLERCK_NAME_LENGHT];
        uint8_t barcode[MAX_BARCODE_LENGHT];
        uint8_t ticketSaleOrder;
    };
}
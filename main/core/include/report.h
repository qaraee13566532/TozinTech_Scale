
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
        unsigned long totalPrice;
        unsigned long unitPrice;
        unsigned long discountPrice;
        unsigned long taxPrice;
        unsigned int pluNumber;
        unsigned long weight;
        unsigned char itemCode[MAX_ITEM_CODE_LENGHT];
        unsigned int pluName[MAX_PLU_NAME_LENGHT];
        unsigned int qty;
        unsigned int pcs;
        unsigned int ticketNumber;
        unsigned char scaleNumber;
        unsigned char departmentNumber;
        unsigned char storeNumber;
        unsigned char pluType;
        unsigned char pluUnit;
        unsigned char year;
        unsigned char month;
        unsigned char day;
        unsigned char hour;
        unsigned char min;
        unsigned char sec;
        bool pluTicketDataType;
        bool isSynced;
        unsigned char saleStatus;
        unsigned char transactionType;
        unsigned char transactionCounter;
        unsigned char clerkCode;
        unsigned int clerckName[MAX_CLERCK_NAME_LENGHT];
        unsigned char barcode[MAX_BARCODE_LENGHT];
        unsigned char ticketSaleOrder;
    };
}
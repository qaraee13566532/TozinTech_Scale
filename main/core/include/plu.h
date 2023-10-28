#pragma once
#include "constant.h"
#include "baseCommiunicationEntity.h"

class Plu : public BaseCommiunicationEntity

{
public:
    unsigned long sellPrice;
    unsigned long buyPrice;
    unsigned long pluNumber;
    unsigned int pluName[MAX_PLU_NAME_LENGHT];
    unsigned char barcodeID;
    unsigned char pluType;
    unsigned char pluUnit;
    unsigned char discountID;
    unsigned char taxID;
    bool isDeleted;
    bool isActived;
    unsigned char groupID;
    unsigned char department;
    unsigned int expireDate;
    unsigned int expireTime;
    unsigned char barcode[MAX_BARCODE_LENGHT];

public:
    Plu(BaseCommiunicationEntity baseCasEntity) : BaseCommiunicationEntity(baseCasEntity)
    {
    }

public:
    void setData(void)
    {
        barcodeID = 10;
    }

public:
    unsigned char getData(void)
    {
        return barcodeID;
    }
};


#pragma once

#include "constant.h"
#include "baseCommiunicationEntity.h"


enum BarcodeStandards
{
    EAN13,
    EAN13A5,
    EAN8,
    I2OF5,
    UPCA,
    UPC13,
    CODE39,
    CODE93,
    CODE128,
    CODEBAR,
    GS1_Omnidrirectional,
    GS1_Stacked,
    GS1_Stacked_Omni,
    GS1_Limited,
    GS1_Expanded,
    QR_Code,
};

class Barcode : public BaseCommiunicationEntity
{
public:
    int Code;
    BarcodeStandards barcodeStandard;
    int TemplateID;
    char *Format;
    int *Description;
};


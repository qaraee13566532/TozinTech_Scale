
#pragma once

#include "core/include/baseCommiunicationEntity.h"

namespace BARCODE
{

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
        Barcode()
        {
        }
        Barcode(BaseCommiunicationEntity baseCasEntity) : BaseCommiunicationEntity(baseCasEntity)
        {
        }

    public:
        int16_t Code;
        BarcodeStandards barcodeStandard;
        int16_t TemplateID;
        int8_t *Format;
        int16_t *Description;
    };
}

#pragma once


#include "core/include/baseCommiunicationEntity.h"
namespace TAX
{
    class Tax : public BaseCommiunicationEntity
    {
    public:
        Tax()
        {
        }
        Tax(BaseCommiunicationEntity baseCasEntity) : BaseCommiunicationEntity(baseCasEntity)
        {
        }

    public:
        uint16_t code;
        uint16_t type;
        uint16_t taxrate;
    };
}
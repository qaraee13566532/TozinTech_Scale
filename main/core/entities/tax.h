
#pragma once

#include "core/constant.h"
#include "core/entities/baseCommiunicationEntity.h"
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
        unsigned int code;
        unsigned int type;
        unsigned int taxrate;
    };
}
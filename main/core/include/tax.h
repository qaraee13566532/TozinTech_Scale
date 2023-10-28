
#pragma once

#include "core/constants/constant.h"
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
        unsigned int code;
        unsigned int type;
        unsigned int taxrate;
    };
}
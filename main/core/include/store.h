
#pragma once

#include "core/include/baseCommiunicationEntity.h"
namespace STORE
{
    class Store : public BaseCommiunicationEntity
    {
    public:
        Store()
        {
        }
        Store(BaseCommiunicationEntity baseCasEntity) : BaseCommiunicationEntity(baseCasEntity)
        {
        }

    public:
        uint16_t code;
        int16_t *description;
        int8_t *phone;
        int16_t *name;
    };
}

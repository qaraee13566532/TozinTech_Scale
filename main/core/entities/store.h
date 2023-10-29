
#pragma once

#include "core/constant.h"
#include "core/entities/baseCommiunicationEntity.h"
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
        unsigned int code;
        int *description;
        char *phone;
        int *name;
    };
}
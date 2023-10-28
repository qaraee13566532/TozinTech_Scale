
#pragma once

#include "core/constants/constant.h"
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
        unsigned int code;
        int *description;
        char *phone;
        int *name;
    };
}

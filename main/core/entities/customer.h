
#pragma once

#include "core/constant.h"
#include "core/entities/baseCommiunicationEntity.h"

namespace CUSTOMER
{
    class Customer : public BaseCommiunicationEntity
    {
    public:
        Customer()
        {
        }
        Customer(BaseCommiunicationEntity baseCasEntity) : BaseCommiunicationEntity(baseCasEntity)
        {
        }

    public:
        int code;
        int *name;
        char *phone;
        int creditLimitAccount;
        int *address1;
        int *address2;
        int *address3;
    };
}
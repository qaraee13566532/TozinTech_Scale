
#pragma once

#include "core/include/baseCommiunicationEntity.h"

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
        int16_t code;
        int16_t *name;
        int8_t *phone;
        int16_t creditLimitAccount;
        int16_t *address1;
        int16_t *address2;
        int16_t *address3;
    };
}
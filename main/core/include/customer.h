
#pragma once

#include "core/constants/constant.h"
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
        int Code;
        int *Name;
        char *Phone;
        int Credit_Limit_Account;
        int *Address1;
        int *Address2;
        int *Address3;
    };
}
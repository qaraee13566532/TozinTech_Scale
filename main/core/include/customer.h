
#pragma once

#include "constant.h"
#include "baseCommiunicationEntity.h"


class Customer : public BaseCommiunicationEntity
{
    //  public : Customer(BaseCommiunicationEntity baseCasEntity)  : BaseCommiunicationEntity()
    //     {

    //     }
public:
    int Code;
    int *Name;
    char *Phone;
    int Credit_Limit_Account;
    int *Address1;
    int *Address2;
    int *Address3;
};

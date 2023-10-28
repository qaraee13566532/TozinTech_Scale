#pragma once

#include "core/constants/constant.h"
#include "core/include/baseCommiunicationEntity.h"

namespace CLERK
{

    class Clerk : public BaseCommiunicationEntity
    {
    public:
        Clerk()
        {
        }
        Clerk(BaseCommiunicationEntity baseCasEntity) : BaseCommiunicationEntity(baseCasEntity)
        {
        }

    public:
        unsigned int Code;
        char *ClerkID;
        int *NickName;
        char *Password;
        unsigned int Level;
    };
}
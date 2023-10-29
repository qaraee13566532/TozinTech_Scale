#pragma once

#include "core/constant.h"
#include "core/entities/baseCommiunicationEntity.h"

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
        unsigned int code;
        char *clerkID;
        int *nickName;
        char *password;
        unsigned int level;
    };
}
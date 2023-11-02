#pragma once

#include "core/entities/baseCommiunicationEntity.h"

const unsigned char MAX_CLERCK_NAME_LENGHT = 30;

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
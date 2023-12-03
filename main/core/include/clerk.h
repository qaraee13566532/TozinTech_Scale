#pragma once

#include "core/include/baseCommiunicationEntity.h"

#define  MAX_CLERCK_NAME_LENGHT       30 

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
        uint16_t code;
        int8_t *clerkID;
        int16_t *nickName;
        int8_t *password;
        uint16_t level;
    };
}
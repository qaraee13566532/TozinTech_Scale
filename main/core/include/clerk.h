#pragma once

#include "constant.h"
#include "baseCommiunicationEntity.h"


class Clerk : public BaseCommiunicationEntity
{
public:
    unsigned int Code;
    char *ClerkID;
    int *NickName;
    char *Password;
    unsigned int Level;
};

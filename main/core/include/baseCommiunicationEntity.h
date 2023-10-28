
#pragma once

#include "core/constants/constant.h"
#include "core/include/baseCommiunicationEntity.h"

class BaseCommiunicationEntity
{
public:
    BaseCommiunicationEntity()
    {
    }
    BaseCommiunicationEntity(const BaseCommiunicationEntity &entity)
    {
    }

    char *sourceIP;
    char *destIP;
    unsigned int serverPort;
    unsigned int devicePort;
    unsigned long id;
    unsigned char type;
    char *identifier;
};
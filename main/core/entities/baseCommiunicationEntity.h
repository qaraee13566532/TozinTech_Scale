
#pragma once

#include "core/constant.h"
#include "core/entities/baseCommiunicationEntity.h"

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
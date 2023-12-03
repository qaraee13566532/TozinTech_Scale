
#pragma once

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

    int8_t *sourceIP;
    int8_t *destIP;
    uint16_t serverPort;
    uint16_t devicePort;
    uint32_t id;
    uint8_t type;
    int8_t *identifier;
};
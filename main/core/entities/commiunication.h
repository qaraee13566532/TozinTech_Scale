
#pragma once

#include "core/entities/baseCommiunicationEntity.h"
#include "core/entities/report.h"

namespace COMMIUNICATION
{

    class Commiunication : public Report, BaseCommiunicationEntity
    {
    public:
        Commiunication()
        {
        }
        Commiunication(BaseCommiunicationEntity baseCasEntity) : BaseCommiunicationEntity(baseCasEntity)
        {
        }
    };
}
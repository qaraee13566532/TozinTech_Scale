
#pragma once

#include "core/constant.h"
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
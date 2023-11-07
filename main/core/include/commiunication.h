
#pragma once

#include "core/include/baseCommiunicationEntity.h"
#include "core/include/report.h"

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
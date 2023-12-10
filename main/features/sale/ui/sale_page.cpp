

#include "features\sale\presentation\sale_page.h"

namespace SALE
{
    void Sale::Initialize(void)
    {
        
    }
    void Sale::RunTasks(uint16_t &appState)
    {
        switch (state)
        {
        case SALE_INIT:
            Initialize();
            break;
        case SALE_RUN_TASK:
            break;
        default:
            break;
        }
    }
}
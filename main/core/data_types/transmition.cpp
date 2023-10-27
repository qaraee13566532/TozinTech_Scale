#include "constant.h"
#include "report.cpp"

class Transmit : public Report
{
    public :
    void SendData(void)
    {
        totalPrice=10;
    }
};
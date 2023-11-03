
#pragma once

#include "core/device_driver/commiunication_uart/comm_uart.h"
#include "driver/uart.h"

namespace COMMIUNICATION_UART
{
    class CommiunicationUart
    {
        static inline uart_config_t uart_config;
        static inline unsigned char *received_buffer;
        static inline unsigned int dataLength;
        static inline bool dataReceived;

    public:
        static void CommTransmitData(char *data);
        static void CommReceiveData(void);
        static void InitCommUart(void);
    };
}
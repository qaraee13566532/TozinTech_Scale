
#pragma once

#include "core/device_driver/commiunication_uart/comm_uart.h"
#include "driver/uart.h"
#include <iostream>
using std::string;

namespace COMMIUNICATION_UART
{
    class CommiunicationUart
    {
        static inline uart_config_t uart_config;
        static inline uint8_t *received_buffer;
        static inline uint16_t dataLength;
        static inline bool dataReceived;

    public:
        static void CommTransmitData(string data);
        static void CommReceiveData(void);
        static void InitCommUart(void);
    };
}
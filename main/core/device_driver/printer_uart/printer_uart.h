
#pragma once

#include "core/device_driver/commiunication_uart/comm_uart.h"
#include "driver/uart.h"
#include <iostream>
using std::string;

namespace PRINTER_UART
{
    class PrinterUart
    {
        static inline uart_config_t uart_config;
        static inline uint8_t *received_buffer;
        static inline uint16_t dataLength;
        static inline bool dataReceived;

    public:
        static void PrinterTransmitData(string data);
        static void PrinterReceiveData(void);
        static void InitPrinterUart(void);
    };
}
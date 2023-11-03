
#pragma once

#include "core/device_driver/commiunication_uart/comm_uart.h"
#include "driver/uart.h"

namespace PRINTER_UART
{
    class PrinterUart
    {
        static inline uart_config_t uart_config;
        static inline unsigned char *received_buffer;
        static inline unsigned int dataLength;
        static inline bool dataReceived;

    public:
        static void PrinterTransmitData(char *data);
        static void PrinterReceiveData(void);
        static void InitPrinterUart(void);
    };
}

#include "core/device_driver/commiunication_uart/comm_uart.h"
#include "driver/uart.h"
#include "core/device_driver/gpio/gpio.h"
#include "string.h"
#include <iostream>
using std::string;


namespace COMMIUNICATION_UART
{
    void CommiunicationUart::InitCommUart(void)
    {
        uart_config.baud_rate = 115200;
        uart_config.data_bits = UART_DATA_8_BITS;
        uart_config.parity = UART_PARITY_DISABLE;
        uart_config.stop_bits = UART_STOP_BITS_1;
        uart_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
        uart_config.source_clk = UART_SCLK_DEFAULT;
        uart_driver_install(UART_NUM_0, 2048, 2048, 0, NULL, 0);
        uart_param_config(UART_NUM_0, &uart_config);
        uart_set_pin(UART_NUM_0, GPIO_NUM_43, GPIO_NUM_44, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
        received_buffer = (uint8_t *)malloc(1024 + 1);
    }

    void CommiunicationUart::CommTransmitData(string data)
    {
        uart_write_bytes(UART_NUM_0, &data, data.length());
    }

    void CommiunicationUart::CommReceiveData(void)
    {
        ESP_ERROR_CHECK(uart_get_buffered_data_len(UART_NUM_0, (size_t *)&dataLength));
        if (dataLength > 0)
        {
            dataLength = uart_read_bytes(UART_NUM_0, received_buffer, 1024, 1000 / portTICK_PERIOD_MS);
            dataReceived = true;
        }
        else
            dataReceived = false;
    }

}
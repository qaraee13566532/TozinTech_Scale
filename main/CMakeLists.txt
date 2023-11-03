idf_component_register(SRCS 

main.cpp 
core/device_driver/seven_segment_display/seven_segment_display.cpp 
core/device_driver/matrix_keyboard/keyboard.cpp
core/initializa.cpp
core/device_driver/timer/timer.cpp
core/device_driver/gpio/gpio.cpp
core/device_driver/weight/weight.cpp
core/device_driver/chip_adc/chip_adc.cpp
core/device_driver/commiunication_uart/comm_uart.cpp
core/device_driver/printer_uart/printer_uart.cpp
core/device_driver/rtc/rtc.cpp

INCLUDE_DIRS 

. 
core 
core/entities 
core/device_driver 
core/device_driver/timer 
core/device_driver/weight
core/device_driver/chip_adc
core/device_driver/gpio
core/device_driver/printer_uart
core/device_driver/rtc
core/device_driver/commiunication_uart
core/device_driver/matrix_keyboard  
core/device_driver/seven_segment_display)

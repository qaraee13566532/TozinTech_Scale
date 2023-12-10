idf_component_register(SRCS 

main.cpp 
core/device_driver/seven_segment_display/seven_segment_display.cpp 
core/device_driver/matrix_keyboard/keyboard.cpp
core/initializa.cpp
features/splash/ui/splash.cpp
core/device_driver/timer/timer.cpp
core/device_driver/gpio/gpio.cpp
core/weight/weight.cpp
core/device_driver/chip_adc/chip_adc.cpp
core/device_driver/adc_ads1232/adc.cpp
core/device_driver/commiunication_uart/comm_uart.cpp
core/device_driver/printer_uart/printer_uart.cpp
core/device_driver/rtc/rtc.cpp
core/device_driver/storage/storage.cpp
core/device_driver/sntp/sntp.cpp
core/device_driver/wifi/wifi.cpp
core/device_driver/nvs/nvs.cpp
core/calibration/usecase/calibration.cpp
core/calibration/ui/calibration_page.cpp
core/device_driver/adc_ads1232/fir_filter.cpp
core/device_driver/adc_ads1232/MedianFilter.cpp


  
INCLUDE_DIRS 

. 
core 
features/splash/ui
core/include 
core/device_driver 
core/device_driver/timer 
core/weight
core/device_driver/chip_adc
core/device_driver/adc_ads1232
core/device_driver/gpio
core/device_driver/printer_uart
core/device_driver/rtc
core/device_driver/nvs
core/device_driver/wifi
core/device_driver/sntp
core/device_driver/storage
core/device_driver/commiunication_uart
core/device_driver/matrix_keyboard  
core/calibration/usecase
core/calibration/ui

core/device_driver/seven_segment_display)

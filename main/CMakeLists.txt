idf_component_register(SRCS main.cpp core/device_driver/seven_segment_display/seven_segment_display.cpp core/device_driver/matrix_keyboard/keyboard.cpp
                        INCLUDE_DIRS . core core/entities core/device_driver 
                        core/device_driver/matrix_keyboard  core/device_driver/seven_segment_display)

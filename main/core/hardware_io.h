#pragma once

#include <driver/gpio.h>

//SevenSegment IO
#define TM1640_CHIP_0_CLOCK             GPIO_NUM_19
#define TM1640_CHIP_1_CLOCK             GPIO_NUM_8
#define TM1640_DATA                     GPIO_NUM_20
//ADS1232 main ADC IO
#define ADS1232_CLOCK                   GPIO_NUM_1
#define ADS1232_DATA                    GPIO_NUM_2
//KEYBOARD main ADC IO
#define Key_Row6                        GPIO_NUM_42
#define Key_Row5                        GPIO_NUM_41
#define Key_Row4                        GPIO_NUM_37
#define Key_Row3                        GPIO_NUM_38
#define Key_Row2                        GPIO_NUM_39
#define Key_Row1                        GPIO_NUM_40
//BUZZER IO
#define BUZZER                          GPIO_NUM_5
//UPS CONTROLLER IO
#define UPS_CTRL                        GPIO_NUM_4
//CASH DRAWER
#define CASH                            GPIO_NUM_16
//CALIBRATION KEY
#define CAL_JMP                         GPIO_NUM_15
//OUTPUT RELAYS IO
#define Relay_1                         GPIO_NUM_3
#define Relay_2                         GPIO_NUM_46
#define Relay_3                         GPIO_NUM_9
#define Relay_4                         GPIO_NUM_10
#define Relay_5                         GPIO_NUM_11
#define Relay_6                         GPIO_NUM_12
#define Relay_7                         GPIO_NUM_13
#define Relay_8                         GPIO_NUM_14
//INTERNAL ADC IO
#define DC_SAMPLE_CHANNEL               ADC_CHANNEL_5
#define BATTERY_SAMPLE_CHANNEL          ADC_CHANNEL_6






/**
  *@file hal.h
  *@date 2019-1-26
  *@author Azusa Katze
  *@brief Included all necessary C file meow
  */

#ifndef RMV3TESTDEMO_HAL_H
#define RMV3TESTDEMO_HAL_H
extern "C" {
#include "main.h"
#include "stm32f4xx_hal.h"
#include "can.h"
#include "dma.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "bsp_imu.h"
#include "test_can.h"
#include "tim.h"
#include "bsp_uart.h"
#include "FreeRTOS.h"
#include "stm32f4xx_it.h"
}
#endif //RMV3TESTDEMO_HAL_H

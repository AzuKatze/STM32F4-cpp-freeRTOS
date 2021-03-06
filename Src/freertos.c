/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  *
  * Copyright (c) 2019 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <memory.h>
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_hal.h"
/* USER CODE BEGIN Includes */
#include "can.h"
#include "usart.h"
#include "test_can.h"
#include "task.h"
#include "../cpp-src/Boot.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
static osThreadId CANTaskHandle;
static osThreadId RemoteTaskHandle;
static osThreadId IMUTaskHandle;
static osThreadId ChassisTaskHandle;
static osThreadId YuntaiTaskHandle;
/* USER CODE BEGIN Variables */
/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */
/* USER CODE BEGIN FunctionPrototypes */
void CANTask(void const * argument);
void IMUTask(void const * argument);
void RemoteTask(void const * argument);
void ChassisTask(void const * argument);
void YuntaiTask(void const * argument);
/* USER CODE END FunctionPrototypes */
/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  KernelStart ();
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */

  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */

  osThreadDef(CANDEF,CANTask,osPriorityRealtime,0,512);
  CANTaskHandle = osThreadCreate (osThread(CANDEF),NULL);

  osThreadDef(IMUDEF,IMUTask,osPriorityNormal,0,512);
  IMUTaskHandle = osThreadCreate (osThread(IMUDEF),NULL);

  osThreadDef(REMOTEDEF,RemoteTask,osPriorityHigh,0,512);
  RemoteTaskHandle = osThreadCreate (osThread(REMOTEDEF),NULL);

  osThreadDef(CHASSISDEF,ChassisTask,osPriorityHigh,0,512);
  ChassisTaskHandle = osThreadCreate (osThread(CHASSISDEF),NULL);

  osThreadDef(YUNTAIDEF, YuntaiTask, osPriorityNormal, 0, 1024);
  YuntaiTaskHandle = osThreadCreate(osThread(YUNTAIDEF), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* USER CODE BEGIN Application */
void CANTask(void const * argument){
    osSignalWait (0x03,100);
    for(;;){
        osCanTask ();
        osDelay (20);
    }
}
void IMUTask(void const * argument){
    for(;;){
        osIMUTask ();
        osDelay (10);

    }
}
void ChassisTask(void const * argument){
    for(;;){
        osChassisTask ();
        osDelay (10);
    }
}
void YuntaiTask(void const * argument){
    for(;;){
        osYuntaiTask ();
        osDelay (10);
    }
}
void RemoteTask(void const *argument){
    osSignalWait (0x05,100);
    for(;;){
        osRemoteTask ();
        osDelay (10);
    }
}
void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan){
    osSignalSet (CANTaskHandle,0x03);
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    osSignalSet (RemoteTaskHandle,0x05);
}

/* USER CODE END Application */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

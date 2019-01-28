

#ifndef __BSP_UART_H__
#define __BSP_UART_H__

#include "usart.h"

#define UART_RX_DMA_SIZE (1024)
#define DBUS_MAX_LEN     (50)
#define DBUS_BUFLEN      (18)
#define DBUS_HUART       huart1 /* for dji remote controler reciever */
/** 
  * @brief  remote control information
  */
#pragma pack (1)
typedef struct {
    /* rocker channel information */
    int16_t ch1;
    int16_t ch2;
    int16_t ch3;
    int16_t ch4;

    /* left and right lever information */
    uint8_t sw1;
    uint8_t sw2;

    int16_t mx;
    int16_t my;
    int16_t mz;
    uint8_t ml;
    uint8_t mr;

    uint16_t kbd;

    uint16_t rev;
} rc_info_t;
#pragma pack ()

void uart_receive_handler(UART_HandleTypeDef *huart);

void dbus_uart_init(void);

void USART_SendData(USART_TypeDef *USARTx, uint16_t Data);

#endif

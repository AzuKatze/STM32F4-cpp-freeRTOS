#ifndef BSP_UART_H
#define BSP_UART_H
#include "stm32f4xx_hal.h"
#include "usart.h"
#include "stm32f4xx_it.h"
#define BSP_USART1_DMA_RX_BUF_LEN 30u
#define BSP_USART6_DMA_RX_BUF_LEN 128u
#define BSP_USART6_DMA_TX_BUF_LEN 30u
#define BSP_USART7_DMA_RX_BUF_LEN 40u
extern uint8_t USART1_DMA_RX_BUF[BSP_USART1_DMA_RX_BUF_LEN];
extern uint8_t USART6_DMA_RX_BUF[BSP_USART6_DMA_RX_BUF_LEN];
extern uint8_t USART6_DMA_TX_BUF[BSP_USART6_DMA_TX_BUF_LEN];
typedef struct
{
    struct
    {
        uint16_t ch0;//通道0 chasis Forward Backward Control
        uint16_t ch1;//通道1 chasis Left Right Control
        uint16_t ch2;//通道2
        uint16_t ch3;//通道3
        uint8_t  s1;//开关1
        uint8_t  s2;//开关2
    }remote;

    struct
    {
        int16_t  x;//鼠标x
        int16_t  y;//鼠标y
        int16_t  z;//鼠标z
        uint8_t  press_l;//鼠标左键
        uint8_t  press_r;//鼠标右键
    }mouse;

    struct
    {
        uint16_t v;//键盘
    }key;
}RemoteCtrl_t;


extern RemoteCtrl_t RemoteCtrlData;

void RemoteCtl_Data_Receive(void);
void RemoteCtl_Data_Receive_Start(void);
void RC_DataHandle(uint8_t *pData);

#endif
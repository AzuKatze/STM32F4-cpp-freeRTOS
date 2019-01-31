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
        uint16_t ch0;//ͨ��0 chasis Forward Backward Control
        uint16_t ch1;//ͨ��1 chasis Left Right Control
        uint16_t ch2;//ͨ��2
        uint16_t ch3;//ͨ��3
        uint8_t  s1;//����1
        uint8_t  s2;//����2
    }remote;

    struct
    {
        int16_t  x;//���x
        int16_t  y;//���y
        int16_t  z;//���z
        uint8_t  press_l;//������
        uint8_t  press_r;//����Ҽ�
    }mouse;

    struct
    {
        uint16_t v;//����
    }key;
}RemoteCtrl_t;


extern RemoteCtrl_t RemoteCtrlData;

void RemoteCtl_Data_Receive(void);
void RemoteCtl_Data_Receive_Start(void);
void RC_DataHandle(uint8_t *pData);

#endif
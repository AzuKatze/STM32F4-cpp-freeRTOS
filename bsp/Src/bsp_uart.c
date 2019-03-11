#include "bsp_uart.h"


uint8_t USART1_DMA_RX_BUF[BSP_USART1_DMA_RX_BUF_LEN];

RemoteCtrl_t RemoteCtrlData;
/**
  * @brief :  接收遥控器数据
  * @param :  None
  * @retval:  None
  * @note  :  位于USART1的中断函数中
  */


void RemoteCtl_Data_Receive(void)
{

    uint32_t rx_data_len = 0;
    if((__HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE)!=RESET))
    {
        __HAL_UART_CLEAR_IDLEFLAG(&huart1);
        (void)USART1->SR;
        (void)USART1->DR;
        __HAL_DMA_CLEAR_FLAG(&hdma_usart1_rx,DMA_FLAG_TCIF2_6);
        HAL_UART_DMAStop(&huart1);
        rx_data_len=BSP_USART1_DMA_RX_BUF_LEN-__HAL_DMA_GET_COUNTER(&hdma_usart1_rx);
        HAL_UART_Receive_DMA(&huart1, USART1_DMA_RX_BUF, BSP_USART1_DMA_RX_BUF_LEN);
        if(rx_data_len == 18)
        {
            RC_DataHandle(USART1_DMA_RX_BUF);
        }
    }
}

/**
  * @brief :  开始串口一不定长中断
  * @param :  None
  * @retval:  None
  * @note  :  位于主函数初始化中
  */

void RemoteCtl_Data_Receive_Start(void)
{
    __HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);
}


/**
  * @brief :  遥控器解码
  * @param :  None
  * @retval:  None
  * @note  :  None
  */


void RC_DataHandle(uint8_t *pData)
{
    if(pData == NULL)
    {
        return;
    }

    RemoteCtrlData.remote.ch0 = ((uint16_t)pData[0] | (uint16_t)pData[1] << 8) & 0x07FF;


    RemoteCtrlData.remote.ch1 = ((uint16_t)pData[1] >> 3 | (uint16_t)pData[2] << 5) & 0x07FF;


    RemoteCtrlData.remote.ch2 = ((uint16_t)pData[2] >> 6 | (uint16_t)pData[3] << 2 | (uint16_t)pData[4] << 10) & 0x07FF;


    RemoteCtrlData.remote.ch3 = ((uint16_t)pData[4] >> 1 | (uint16_t)pData[5] << 7) & 0x07FF;


    RemoteCtrlData.remote.s1  = ((pData[5] >> 6) & 0x03);


    RemoteCtrlData.remote.s2  = ((pData[5] >> 4) & 0x03);


    RemoteCtrlData.mouse.x    = ((int16_t)pData[6] | (int16_t)pData[7] << 8);


    RemoteCtrlData.mouse.y    = ((int16_t)pData[8] | (int16_t)pData[9] << 8);


    RemoteCtrlData.mouse.z    = ((int16_t)pData[10] | (int16_t)pData[11] << 8);


    RemoteCtrlData.mouse.press_l = pData[12];


    RemoteCtrlData.mouse.press_r = pData[13];


    RemoteCtrlData.key.v      = ((int16_t)pData[14]) | ((int16_t)pData[15] << 8);


}
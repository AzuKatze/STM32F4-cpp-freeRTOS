/**
  *@file test_can.c
  *@date 2016-12-12
  *@author Albert.D
  *@brief 
  */

#include "test_can.h"
#include "can.h"
  
uint8_t can1_rx_data[8];
uint8_t can2_rx_data[8];

//can filter must be initialized before use
void CanFilter_Init(CAN_HandleTypeDef* hcan)
{
  CAN_FilterConfTypeDef canfilter;
  
  //create memory to save the message, if not will raise error
  static CanTxMsgTypeDef  Tx1Message;
  static CanRxMsgTypeDef  Rx1Message;
  static CanTxMsgTypeDef  Tx2Message;
  static CanRxMsgTypeDef  Rx2Message;
  
  canfilter.FilterMode = CAN_FILTERMODE_IDMASK;
  canfilter.FilterScale = CAN_FILTERSCALE_32BIT;
  
  //filtrate any ID you want here
  canfilter.FilterIdHigh = 0x0000;
  canfilter.FilterIdLow = 0x0000;
  canfilter.FilterMaskIdHigh = 0x0000;
  canfilter.FilterMaskIdLow = 0x0000;
  
  canfilter.FilterFIFOAssignment = CAN_FilterFIFO0;
  canfilter.FilterActivation = ENABLE;
  canfilter.BankNumber = 14;
  
  //use different filter for can1&can2
  if(hcan == &hcan1)
  {
    canfilter.FilterNumber = 0;
    hcan->pTxMsg = &Tx1Message;
    hcan->pRxMsg = &Rx1Message;
  }
  if(hcan == &hcan2)
  {
    canfilter.FilterNumber = 14;
    hcan->pTxMsg = &Tx2Message;
    hcan->pRxMsg = &Rx2Message;
  }
  
  HAL_CAN_ConfigFilter(hcan, &canfilter);
  
}

////it will be auto callback when can receive msg completely
//void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan)
//{
//  switch(hcan->pRxMsg->StdId)
//  {
//    case TEST_CAN1_ID:
//    {
//      can1_rx_data[0] = hcan->pRxMsg->Data[0];
//    }break;
//    case TEST_CAN2_ID:
//    {
//      can2_rx_data[0] = hcan->pRxMsg->Data[0];
//    }break;
//  }
//
//  HAL_CAN_Receive_IT(&hcan1, CAN_FIFO0);
//  HAL_CAN_Receive_IT(&hcan2, CAN_FIFO0);
//}

//CAN send message test
void Motor_Can_Send_Msg(void)
{


  hcan1.pTxMsg->StdId = 0x200;
  hcan1.pTxMsg->IDE = CAN_ID_STD;
  hcan1.pTxMsg->RTR = CAN_RTR_DATA;
  hcan1.pTxMsg->DLC = 0x08;
  hcan1.pTxMsg->Data[0] = (uint8_t)((int16_t)1000 >> 8);
  hcan1.pTxMsg->Data[1] = (uint8_t)1000;
  hcan1.pTxMsg->Data[2] = (uint8_t)((int16_t)1000 >> 8);
  hcan1.pTxMsg->Data[3] = (uint8_t)1000;
  hcan1.pTxMsg->Data[4] = (uint8_t)((int16_t)1000>> 8);
  hcan1.pTxMsg->Data[5] = (uint8_t)1000;
  hcan1.pTxMsg->Data[6] = (uint8_t)((int16_t)1000>> 8);
  hcan1.pTxMsg->Data[7] = (uint8_t)1000;
  if(0)
  {
    hcan1.pTxMsg->Data[0] = 0;
    hcan1.pTxMsg->Data[1] = 0;
    hcan1.pTxMsg->Data[
            3] = 0;
    hcan1.pTxMsg->Data[4] = 0;
    hcan1.pTxMsg->Data[5] = 0;
    hcan1.pTxMsg->Data[6] = 0;
    hcan1.pTxMsg->Data[7] = 0;
  }
  HAL_CAN_Transmit(&hcan1, 10);
}

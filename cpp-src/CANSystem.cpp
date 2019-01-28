/**
  *@file CANSystem.cpp
  *@date 2019-1-26
  *@author Azusa Katze
  *@brief
  */

#include <cstring>
#include "CANSystem.h"
#include "OI.h"

#define CAN_ID 0x200

CANSystem::CANSystem(int can_id){
}

bool CANSystem::initialize() {

    CAN_HandleTypeDef *hcan = &(can_id==0 ? hcan1 : hcan2);

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
    if(hcan == &hcan1){
        canfilter.FilterNumber = 0;
        hcan->pTxMsg = &Tx1Message;
        hcan->pRxMsg = &Rx1Message;
    }
    if(hcan == &hcan2){
        canfilter.FilterNumber = 14;
        hcan->pTxMsg = &Tx2Message;
        hcan->pRxMsg = &Rx2Message;
    }

    HAL_CAN_ConfigFilter(hcan, &canfilter);

    if(HAL_CAN_Init (hcan)!=HAL_OK)
        Error_Handler ();

    memset(this->can_write_data_, 0, sizeof(this->can_write_data_));
    memset(this->can_recv_data_, 0, sizeof(this->can_recv_data_));
    memset(this->can_recv_data_available_, 0, sizeof(this->can_recv_data_available_));
    memset (this->can1_rx_data_,0,sizeof(this->can1_rx_data_));
    memset (this->can2_rx_data_,0,sizeof(this->can2_rx_data_));
    memset (this->can1_tx_data_,0,sizeof(this->can1_tx_data_));
    memset (this->can2_tx_data_,0,sizeof(this->can2_tx_data_));

    hcan->pTxMsg->StdId = CAN_ID;
    hcan->pTxMsg->IDE = CAN_ID_STD;
    hcan->pTxMsg->RTR = CAN_RTR_DATA;
    hcan->pTxMsg->DLC = 0x08;

    return true;
}

bool CANSystem::destroy() {
    return false;
}

bool CANSystem::update() {
    CAN_HandleTypeDef *hcan=&(can_id==0?hcan1:hcan2);


    for (int i = 0; i < 4; i++) {
        hcan->pTxMsg->Data[ i * 2 ] = (uint8_t) ( can_write_data_[ i ] >> 8 );
        hcan->pTxMsg->Data[ i * 2 + 1 ] = (uint8_t) ( can_write_data_[ i ] );
    }

    HAL_CAN_Transmit (hcan,10);

    for (int j = 0; j < 8; ++j) {
        can_recv_data_[hcan->pRxMsg->StdId-0x201][j] = hcan->pRxMsg->Data[j];
    }


}

bool CANSystem::set(int id, uint16_t data) {
    this->can_write_data_[id] = data;
    return true;
}

uint16_t CANSystem::get(int id , int data_id) {
    return this->can_recv_data_[id][data_id];
}




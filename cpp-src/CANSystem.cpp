/**
  *@file CANSystem.cpp
  *@date 2019-1-26
  *@author Azusa Katze
  *@brief
  */

#include <cstring>
#include "CANSystem.h"
#include "OI.h"
#include "hal.h"
#define CAN_ID 0x200

CANSystem::CANSystem(int can_id){
    this->can_id = can_id;
}

bool CANSystem::initialize() {

    CAN_HandleTypeDef *hcan = &(can_id==0 ? hcan1 : hcan2);

    canfilter.FilterMode = CAN_FILTERMODE_IDMASK;
    canfilter.FilterScale = CAN_FILTERSCALE_32BIT;

    canfilter.FilterIdHigh = 0x0000;
    canfilter.FilterIdLow = 0x0000;
    canfilter.FilterMaskIdHigh = 0x0000;
    canfilter.FilterMaskIdLow = 0x0000;

    canfilter.FilterFIFOAssignment = CAN_FilterFIFO0;
    canfilter.FilterActivation = ENABLE;
    canfilter.BankNumber = 14;

    if(can_id == 0){
        canfilter.FilterNumber = 0;
        hcan1.pTxMsg = &Tx1Message;
        hcan1.pRxMsg = &Rx1Message;
    }
    if(can_id == 1){
        canfilter.FilterNumber = 14;
        hcan2.pTxMsg = &Tx2Message;
        hcan2.pRxMsg = &Rx2Message;
    }

    HAL_CAN_ConfigFilter(hcan, &canfilter);



    memset(this->can_write_data_, 0, sizeof(this->can_write_data_));
    memset(this->can_recv_data_, 0, sizeof(this->can_recv_data_));
    memset(this->can_recv_data_available_, 0, sizeof(this->can_recv_data_available_));
    memset (this->can1_rx_data_,0,sizeof(this->can1_rx_data_));
    memset (this->can2_rx_data_,0,sizeof(this->can2_rx_data_));
    memset (this->can1_tx_data_,0,sizeof(this->can1_tx_data_));
    memset (this->can2_tx_data_,0,sizeof(this->can2_tx_data_));

    hcan->pTxMsg->StdId = CAN_ID;
    hcan->pTxMsg->ExtId = 0x00;
    hcan->pTxMsg->RTR = CAN_RTR_DATA;
    hcan->pTxMsg->IDE = CAN_ID_STD;
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

    HAL_CAN_Receive_IT (hcan,CAN_FIFO0);
}

bool CANSystem::set(int id, int16_t data) {
    this->can_write_data_[id] = data;

    return true;
}

double CANSystem::get(int id ) {

    for (int i = 0; i < 4; ++i) {
        speed[id][i] = speed[id][i+1];
        sum += speed[id][i+1];
    }
    speed[id][4] = (((int16_t)can_recv_data_[id][2]<<8) | ((int16_t)can_recv_data_[id][3]));
    sum +=  speed[id][4];
    sum /= 5;
    sum = sum * 8192 / 60 / 1000;
    if(sum <= 3&&sum >= -3)sum = 0;
    return sum;
}




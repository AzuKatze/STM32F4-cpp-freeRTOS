/**
  *@file CANSystem.h
  *@date 2019-1-26
  *@author Azusa Katze
  *@brief
  */

#ifndef RMV3TESTDEMO_CANSYSTEM_H
#define RMV3TESTDEMO_CANSYSTEM_H

#include "hal.h"

#define CAN_MAX_CAN_ID 8
#define CAN_MAX_DATA_ID 8
#define CAN_MAX_ANGLE 8192

class CANSystem {
private:
    uint16_t can_write_data_[CAN_MAX_CAN_ID + 1];
    uint8_t can_recv_data_[CAN_MAX_CAN_ID +1][CAN_MAX_DATA_ID];
    bool can_recv_data_available_[CAN_MAX_CAN_ID + 1][CAN_MAX_DATA_ID];

    uint8_t can1_rx_data_[8];
    uint8_t can2_rx_data_[8];
    uint8_t can1_tx_data_[8];
    uint8_t can2_tx_data_[8];

    CanRxMsgTypeDef Rx1Message;
    CanRxMsgTypeDef Rx2Message;
    CanTxMsgTypeDef Tx1Message;
    CanTxMsgTypeDef Tx2Message;

    CAN_FilterConfTypeDef canfilter;

    int can_id;
public:

    CANSystem (int can_id);

    bool initialize ();

    bool destroy ();

    bool update ();

    bool set (int id, uint16_t data);

    uint16_t get(int id,int data_id);
};


#endif //RMV3TESTDEMO_CANSYSTEM_H

/**
  *@file RemoteSystem.cpp
  *@date 2019-1-26
  *@author Azusa Katze
  *@brief
  */

#include "RemoteSystem.h"
#include "OI.h"
#include "hal.h"


RemoteSystem::RemoteSystem() {

}

bool RemoteSystem::initialize() {
    RemoteCtl_Data_Receive_Start ();
    return true;
}

int16_t RemoteSystem::getAxis(int id) {
    switch(id) {
        case CTR_CH1:
            return (RemoteCtrlData.remote.ch0-RC_RESOLUTION);
        case CTR_CH2:
            return (RemoteCtrlData.remote.ch1-RC_RESOLUTION);
        case CTR_CH3:
            return (RemoteCtrlData.remote.ch2-RC_RESOLUTION);
        case CTR_CH4:
            return (RemoteCtrlData.remote.ch3-RC_RESOLUTION);
        default:
            return 0;
    }
}

int16_t RemoteSystem::getButton(int id) {
    switch(id) {
        case CTR_SW1:
            return RemoteCtrlData.remote.s1;
        case CTR_SW2:
            return RemoteCtrlData.remote.s2;
        default:
            return 0;
    }
}

bool RemoteSystem::update() {
    oi->chassisSystem->set_speed (-getAxis (CTR_CH2) , -getAxis (CTR_CH1) , getAxis (CTR_CH3));
    oi->yuntaiSystem->setPos (getAxis (CTR_CH4),getAxis (CTR_CH3));
    return true;
}

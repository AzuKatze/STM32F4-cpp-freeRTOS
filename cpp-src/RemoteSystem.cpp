/**
  *@file RemoteSystem.cpp
  *@date 2019-1-26
  *@author Azusa Katze
  *@brief
  */

#include "RemoteSystem.h"
#include "OI.h"

extern rc_info_t rc;

RemoteSystem::RemoteSystem() {

}

bool RemoteSystem::initialize() {
    dbus_uart_init();
    return true;
}

int16_t RemoteSystem::getAxis(int id) {
    switch(id) {
        case CTR_CH1:
            return rc.ch1;
        case CTR_CH2:
            return rc.ch2;
        case CTR_CH3:
            return rc.ch3;
        case CTR_CH4:
            return rc.ch4;
        default:
            return 0;
    }
}

int16_t RemoteSystem::getButton(int id) {
    switch(id) {
        case CTR_SW1:
            return rc.sw1;
        case CTR_SW2:
            return rc.sw2;
        default:
            return 0;
    }
}

bool RemoteSystem::update() {
    oi->chassisSystem->setSpeed (getAxis (CTR_CH1),getAxis (CTR_CH2),getAxis (CTR_CH3));
    oi->yuntaiSystem->setPos (getAxis (CTR_CH4),getAxis (CTR_CH3));
    return true;
}

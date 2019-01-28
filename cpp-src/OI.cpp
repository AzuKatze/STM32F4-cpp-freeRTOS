/**
  *@file OI.cpp
  *@date 2019-1-26
  *@author Azusa Katze
  *@brief
  */

#include "OI.h"
#include <cstdio>
#include "hal.h"
#include "RemoteSystem.h"
#include "IMUSystem.h"
#include "CANSystem.h"
#include "ChassisSystem.h"
#include "YuntaiSystem.h"
OI *oi;

extern "C" void KernelStart() {
    oi = new OI;
    oi->SystemStart ();
}
extern "C" void osChassisTask() {
    oi->ChassisTask ();
}
extern "C" void osYuntaiTask() {
    oi->YuntaiTask ();
}
extern "C" void osRemoteTask() {
    oi->RemoteTask ();
}
extern "C" void osCanTask() {
    oi->CanTask();
}
extern "C" void osIMUTask() {
    oi->IMUTask ();
}


void OI::SystemStart() {
    ///initialize
    this->chassisCanSystem = new CANSystem(0);
    this->yuntaiCanSystem = new CANSystem(1);
    this->imuSystem = new IMUSystem;
    this->chassisSystem = new ChassisSystem;
    this->remoteSystem = new RemoteSystem;
    this->yuntaiSystem = new YuntaiSystem;

    HAL_Delay (10);
}
void OI::CanTask() {
    this->yuntaiCanSystem->update ();
    this->chassisCanSystem->update ();
}
void OI::RemoteTask() {
    this->remoteSystem->update ();
}
void OI::YuntaiTask() {
    this->yuntaiSystem->update ();
}
void OI::ChassisTask() {
    this->chassisCanSystem->update ();
}
void OI::IMUTask() {
    this->imuSystem->update ();
}

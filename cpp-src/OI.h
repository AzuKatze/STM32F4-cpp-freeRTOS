/**
  *@file OI.h
  *@date 2019-1-26
  *@author Azusa Katze
  *@brief
  */

#ifndef RMV3TESTDEMO_OI_H
#define RMV3TESTDEMO_OI_H

#include "CANSystem.h"
#include "YuntaiSystem.h"
#include "ChassisSystem.h"
#include "IMUSystem.h"
#include "RemoteSystem.h"
#include "ShootSystem.h"
#include "hal.h"



class OI {
public:
    OI() : initialized(false){

    }

    void SystemStart();

    void ChassisTask();

    void CanTask();

    void RemoteTask();

    void YuntaiTask();

    void IMUTask();

    void ShootTask();

    CANSystem *chassis_can_system;

    CANSystem *shoot_can_system;

    CANSystem *yuntai_can_system;

    IMUSystem *imuSystem;

    RemoteSystem *remoteSystem;

    ChassisSystem *chassisSystem;

    YuntaiSystem *yuntaiSystem;

    ShootSystem *shootSystem;

    bool initialized;
};

extern OI *oi;



#define OK(x) if (!(x)) while(1)

#endif //RMV3TESTDEMO_OI_H

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

    CANSystem *chassisCanSystem;

    CANSystem *yuntaiCanSystem;

    IMUSystem *imuSystem;

    RemoteSystem *remoteSystem;

    ChassisSystem *chassisSystem;

    YuntaiSystem *yuntaiSystem;

    bool initialized;
};

extern OI *oi;



#define OK(x) if (!(x)) Error_Handler()

#endif //RMV3TESTDEMO_OI_H

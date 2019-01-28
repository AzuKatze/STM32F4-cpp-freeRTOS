/**
  *@file IMUSystem.h
  *@date 2019-1-26
  *@author Azusa Katze
  *@brief
  */

#ifndef RMV3TESTDEMO_IMUSYSTEM_H
#define RMV3TESTDEMO_IMUSYSTEM_H

#include "hal.h"

#define IMU_ROLL 0
#define IMU_PITCH 1
#define IMU_YAW 2

class IMUSystem {
public:

    IMUSystem();

    bool initialize();

    bool destroy();

    bool update();

    float get(int data);

};


#endif //RMV3TESTDEMO_IMUSYSTEM_H

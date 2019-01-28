/**
  *@file CANSystem.cpp
  *@date 2019-1-26
  *@author Azusa Katze
  *@brief
  */

#ifndef RMV3TESTDEMO_CHASSISSYSTEM_H
#define RMV3TESTDEMO_CHASSISSYSTEM_H

#include "PIDSystem.h"
#include "hal.h"

#define CHASSIS_FR_ID 0
#define CHASSIS_FL_ID 1
#define CHASSIS_BL_ID 2
#define CHASSIS_BR_ID 3



class ChassisSystem {
private:
    int16_t BF,LR,ROT;
    IncrPIDSystem<int16_t> IncrPID;
    const double Kp = 3.0, Ki = 0, Kd = 1.5;
    const double output_max = 10000;
public:


    bool initialize();

    bool update();

    bool destroy();

    bool setSpeed(int16_t bf , int16_t lr , int16_t rot);
};


#endif //RMV3TESTDEMO_CHASSISSYSTEM_H

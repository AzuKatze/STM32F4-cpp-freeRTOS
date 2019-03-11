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





class ChassisSystem {
private:
    int16_t BF,LR,ROT;
    PosPIDSystem<double> PosPID;
    const double Kp = 10, Ki = 0, Kd = 0;
    const double output_max = 5000,total_error = 5000;
public:


    bool initialize();

    bool update();

    bool destroy();

    bool set_speed(int16_t bf , int16_t lr , int16_t rot);
};


#endif //RMV3TESTDEMO_CHASSISSYSTEM_H

/**
  *@file CANSystem.cpp
  *@date 2019-1-26
  *@author Azusa Katze
  *@brief MeowMeowMeow
  */

#ifndef RMV3TESTDEMO_YUNTAISYSTEM_H
#define RMV3TESTDEMO_YUNTAISYSTEM_H


#include "PIDSystem.h"
#include "hal.h"
#define PITCH_ID 0
#define YAW_ID 1

class YuntaiSystem {
private:
    int16_t pitch_ref_,yaw_ref_;
    IncrPIDSystem<int16_t>PitchPosPID;
    IncrPIDSystem<int16_t> PitchVelPID;
    IncrPIDSystem<int16_t> YawPosPID;
    IncrPIDSystem<int16_t> YawVelPID;
    const int16_t PitchPosKp=1,PitchPosKi=1,PitchPosKd=1;
    const int16_t PitchVelKp=1,PitchVelKi=1,PitchVelKd=1;
    const int16_t YawPosKp=1,YawPosKi=1,YawPosKd=1;
    const int16_t YawVelKp=1,YawVelKi=1,YawVelKd=1;
    const int16_t output_max=3000;
public:

    YuntaiSystem();

    bool initialize();

    bool update();

    bool destroy();

    bool setPos(int16_t pitch_ref , int16_t yaw_ref);
};


#endif //RMV3TESTDEMO_YUNTAISYSTEM_H

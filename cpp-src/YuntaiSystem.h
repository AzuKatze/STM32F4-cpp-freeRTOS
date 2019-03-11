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


class YuntaiSystem {
private:
    int16_t pitch_ref_, yaw_ref_;
    PosPIDSystem<int16_t>PitchPosPID;
    PosPIDSystem<int16_t> PitchVelPID;
    PosPIDSystem<int16_t> YawPosPID;
    PosPIDSystem<int16_t> YawVelPID;
    const int16_t PitchPosKp=3, PitchPosKi=0, PitchPosKd=0;
    const int16_t PitchVelKp=3, PitchVelKi=0, PitchVelKd=0;
    const int16_t YawPosKp=3, YawPosKi=0, YawPosKd=0;
    const int16_t YawVelKp=3, YawVelKi=0, YawVelKd=0;
    const int16_t output_max=3000;

    kalman_filter_t yaw_kalman_filter;
    kalman_filter_t pitch_kalman_filter;
    kalman_filter_t dist_kalman_filter;

    float *yaw_kf_result, *pitch_kf_result;

public:

    YuntaiSystem();

    bool initialize();

    bool update();

    bool destroy();

    bool setPos(int16_t pitch_ref, int16_t yaw_ref);
};


#endif //RMV3TESTDEMO_YUNTAISYSTEM_H

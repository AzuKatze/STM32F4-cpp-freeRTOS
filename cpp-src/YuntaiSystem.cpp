/**
  *@file CANSystem.cpp
  *@date 2019-1-26
  *@author Azusa Katze
  *@brief MeowMeowMeow
  */

#include "YuntaiSystem.h"
#include "OI.h"

YuntaiSystem::YuntaiSystem() {

}
bool YuntaiSystem::initialize() {
    this->PitchPosPID.inititalize (PitchPosKp,PitchPosKi,PitchPosKd,output_max);
    this->PitchVelPID.inititalize (PitchVelKp,PitchVelKi,PitchVelKd,output_max);
    this->YawPosPID.inititalize (YawPosKp,YawPosKi,YawPosKd,output_max);
    this->YawVelPID.inititalize (YawVelKp,YawVelKi,YawVelKd,output_max);
    oi->yuntaiCanSystem->set (PITCH_ID,0);
    oi->yuntaiCanSystem->set (YAW_ID,0);
    return true;
}

bool YuntaiSystem::update() {
    int16_t PitchRef,YawRef;

    PitchRef = this->pitch_ref_;

    YawRef = this->yaw_ref_;

    int16_t PitchPosReal,YawPosReal,PitchVelReal,YawVelReal;

    PitchPosReal = imu.pit;

    PitchVelReal = imu.wx;

    YawPosReal = imu.yaw;

    YawVelReal = imu.wz;

    int16_t PitchPosOutPut,PitchVelOutPut,YawPosOutPut,YawVelOutPut;

    PitchPosOutPut = this->PitchPosPID.PIDCalc (PitchRef,PitchPosReal);

    PitchVelOutPut = this->PitchVelPID.PIDCalc (PitchPosOutPut,PitchVelReal);

    YawPosOutPut = this->YawPosPID.PIDCalc (YawRef,YawPosReal);

    YawVelOutPut = this->YawVelPID.PIDCalc (YawPosOutPut,YawVelReal);

    oi->yuntaiCanSystem->set (PITCH_ID,PitchVelOutPut);

    oi->yuntaiCanSystem->set (YAW_ID,YawVelOutPut);
}

bool YuntaiSystem::destroy() {
    oi->yuntaiCanSystem->set (PITCH_ID,0);
    oi->yuntaiCanSystem->set (YAW_ID,0);
    return true;
}

bool YuntaiSystem::setPos(int16_t pitch_ref , int16_t yaw_ref) {
    this->pitch_ref_ = pitch_ref;
    this->yaw_ref_ = yaw_ref;
    return true;
}
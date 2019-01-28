/**
  *@file CANSystem.cpp
  *@date 2019-1-26
  *@author Azusa Katze
  *@brief
  */

#include "ChassisSystem.h"
#include "OI.h"




bool ChassisSystem::initialize() {
    IncrPID.inititalize (this->Kp,this->Ki,this->Kd,this->output_max);
    oi->chassisCanSystem->set(CHASSIS_BL_ID,0);
    oi->chassisCanSystem->set(CHASSIS_BR_ID,0);
    oi->chassisCanSystem->set(CHASSIS_FL_ID,0);
    oi->chassisCanSystem->set(CHASSIS_FR_ID,0);
    return true;
}

bool ChassisSystem::update() {
    int16_t outPutRef[4];

    outPutRef[CHASSIS_FR_ID] = BF + LR + ROT;

    outPutRef[CHASSIS_FL_ID] = -BF + LR + ROT;

    outPutRef[CHASSIS_BL_ID] = -BF - LR + ROT;

    outPutRef[CHASSIS_BR_ID] = BF - LR + ROT;

    int16_t outPutReal[4];

    outPutReal[CHASSIS_FR_ID] = (int16_t )oi->chassisCanSystem->get (CHASSIS_FR_ID,2) << 8 \
                                | (int16_t)oi->chassisCanSystem->get (CHASSIS_FR_ID,3);

    outPutReal[CHASSIS_FR_ID] = (int16_t )oi->chassisCanSystem->get (CHASSIS_FL_ID,2) << 8 \
                                | (int16_t)oi->chassisCanSystem->get (CHASSIS_FL_ID,3);

    outPutReal[CHASSIS_FR_ID] = (int16_t )oi->chassisCanSystem->get (CHASSIS_BR_ID,2) << 8 \
                                | (int16_t)oi->chassisCanSystem->get (CHASSIS_BR_ID,3);

    outPutReal[CHASSIS_FR_ID] = (int16_t )oi->chassisCanSystem->get (CHASSIS_BL_ID,2) << 8 \
                                | (int16_t)oi->chassisCanSystem->get (CHASSIS_BL_ID,3);

    int16_t outPut[4];

    outPut[CHASSIS_FR_ID] = this->IncrPID.PIDCalc (outPutRef[CHASSIS_FR_ID],outPutReal[CHASSIS_FR_ID]);

    outPut[CHASSIS_FL_ID] = this->IncrPID.PIDCalc (outPutRef[CHASSIS_FL_ID],outPutReal[CHASSIS_FL_ID]);

    outPut[CHASSIS_BR_ID] = this->IncrPID.PIDCalc (outPutRef[CHASSIS_BR_ID],outPutReal[CHASSIS_BR_ID]);

    outPut[CHASSIS_BL_ID] = this->IncrPID.PIDCalc (outPutRef[CHASSIS_BL_ID],outPutReal[CHASSIS_BL_ID]);

    oi->chassisCanSystem->set (CHASSIS_FR_ID,outPut[CHASSIS_FR_ID]);

    oi->chassisCanSystem->set (CHASSIS_FL_ID,outPut[CHASSIS_FL_ID]);

    oi->chassisCanSystem->set (CHASSIS_BR_ID,outPut[CHASSIS_BR_ID]);

    oi->chassisCanSystem->set (CHASSIS_BL_ID,outPut[CHASSIS_BL_ID]);

}

bool ChassisSystem::destroy() {
    oi->chassisCanSystem->set (CHASSIS_FR_ID,0);
    oi->chassisCanSystem->set (CHASSIS_FL_ID,0);
    oi->chassisCanSystem->set (CHASSIS_BR_ID,0);
    oi->chassisCanSystem->set (CHASSIS_BL_ID,0);
    return true;
}

bool ChassisSystem::setSpeed(int16_t bf ,  int16_t lr , int16_t rot) {
    this->BF = bf;
    this->LR = lr;
    this->ROT = rot;
}
/**
  *@file CANSystem.cpp
  *@date 2019-1-26
  *@author Azusa Katze
  *@brief
  */

#include "ChassisSystem.h"
#include "OI.h"




bool ChassisSystem::initialize() {
    PosPID.inititalize (this->Kp,this->Ki,this->Kd,this->output_max,total_error);
    oi->chassisCanSystem->set(CHASSIS_BL_ID,0);
    oi->chassisCanSystem->set(CHASSIS_BR_ID,0);
    oi->chassisCanSystem->set(CHASSIS_FL_ID,0);
    oi->chassisCanSystem->set(CHASSIS_FR_ID,0);
    return true;
}

bool ChassisSystem::update() {
    int16_t outPutRef[4];

    outPutRef[CHASSIS_FR_ID] = this->BF + this->LR + this->ROT;

    outPutRef[CHASSIS_FL_ID] = -this->BF + this->LR + this->ROT;

    outPutRef[CHASSIS_BL_ID] = -this->BF - this->LR + this->ROT;

    outPutRef[CHASSIS_BR_ID] = this->BF - this->LR + this->ROT;

    int16_t outPutReal[4];

    outPutReal[CHASSIS_FR_ID] = oi->chassisCanSystem->get (CHASSIS_FR_ID);

    outPutReal[CHASSIS_FL_ID] = oi->chassisCanSystem->get (CHASSIS_FL_ID);

    outPutReal[CHASSIS_BR_ID] = oi->chassisCanSystem->get (CHASSIS_BR_ID);

    outPutReal[CHASSIS_BL_ID] = oi->chassisCanSystem->get (CHASSIS_BL_ID);

    int16_t outPut[4];


    outPut[CHASSIS_FR_ID] = this->PosPID.PIDCalc (outPutRef[CHASSIS_FR_ID],outPutReal[CHASSIS_FR_ID]);

    outPut[CHASSIS_FL_ID] = this->PosPID.PIDCalc (outPutRef[CHASSIS_FL_ID],outPutReal[CHASSIS_FL_ID]);

    outPut[CHASSIS_BR_ID] = this->PosPID.PIDCalc (outPutRef[CHASSIS_BR_ID],outPutReal[CHASSIS_BR_ID]);

    outPut[CHASSIS_BL_ID] = this->PosPID.PIDCalc (outPutRef[CHASSIS_BL_ID],outPutReal[CHASSIS_BL_ID]);

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
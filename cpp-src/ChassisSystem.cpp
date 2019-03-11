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
    oi->chassis_can_system->set(CHASSIS_BL_ID,0);
    oi->chassis_can_system->set(CHASSIS_BR_ID,0);
    oi->chassis_can_system->set(CHASSIS_FL_ID,0);
    oi->chassis_can_system->set(CHASSIS_FR_ID,0);
    return true;
}

bool ChassisSystem::update() {
    int16_t output_ref[4];

    output_ref[CHASSIS_FR_ID] = this->BF + this->LR + this->ROT;
    output_ref[CHASSIS_FL_ID] = -this->BF + this->LR + this->ROT;
    output_ref[CHASSIS_BL_ID] = -this->BF - this->LR + this->ROT;
    output_ref[CHASSIS_BR_ID] = this->BF - this->LR + this->ROT;

    int16_t output_fdb[4];

    output_fdb[CHASSIS_FR_ID] = oi->chassis_can_system->get (CHASSIS_FR_ID);
    output_fdb[CHASSIS_FL_ID] = oi->chassis_can_system->get (CHASSIS_FL_ID);
    output_fdb[CHASSIS_BR_ID] = oi->chassis_can_system->get (CHASSIS_BR_ID);
    output_fdb[CHASSIS_BL_ID] = oi->chassis_can_system->get (CHASSIS_BL_ID);

    int16_t output[4];


    output[CHASSIS_FR_ID] = this->PosPID.PIDCalc (output_ref[CHASSIS_FR_ID],output_fdb[CHASSIS_FR_ID]);
    output[CHASSIS_FL_ID] = this->PosPID.PIDCalc (output_ref[CHASSIS_FL_ID],output_fdb[CHASSIS_FL_ID]);
    output[CHASSIS_BR_ID] = this->PosPID.PIDCalc (output_ref[CHASSIS_BR_ID],output_fdb[CHASSIS_BR_ID]);
    output[CHASSIS_BL_ID] = this->PosPID.PIDCalc (output_ref[CHASSIS_BL_ID],output_fdb[CHASSIS_BL_ID]);

    oi->chassis_can_system->set (CHASSIS_FR_ID,output[CHASSIS_FR_ID]);
    oi->chassis_can_system->set (CHASSIS_FL_ID,output[CHASSIS_FL_ID]);
    oi->chassis_can_system->set (CHASSIS_BR_ID,output[CHASSIS_BR_ID]);
    oi->chassis_can_system->set (CHASSIS_BL_ID,output[CHASSIS_BL_ID]);

}

bool ChassisSystem::destroy() {
    oi->chassis_can_system->set (CHASSIS_FR_ID,0);
    oi->chassis_can_system->set (CHASSIS_FL_ID,0);
    oi->chassis_can_system->set (CHASSIS_BR_ID,0);
    oi->chassis_can_system->set (CHASSIS_BL_ID,0);
    return true;
}

bool ChassisSystem::set_speed(int16_t bf , int16_t lr , int16_t rot) {
    this->BF = bf;
    this->LR = lr;
    this->ROT = rot;
}
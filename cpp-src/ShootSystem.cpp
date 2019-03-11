

#include "ShootSystem.h"
#include "OI.h"
#include "hal.h"

bool ShootSystem::initialize() {
    PosPID_R.inititalize (this->Kp, this->ki, this->Kd, this->output_max, this->total_error);
    PosPID_L.inititalize (this->Kp, this->ki, this->Kd, this->output_max, this->total_error);
    PosPID_cap.inititalize (1, this->ki, this->Kd, this->output_max, this->total_error);
    oi->shoot_can_system->set (FRICTWHEEL_LEFT_ID,0);
    oi->shoot_can_system->set (FRICTWHEEL_RIGHT_ID,0);
    oi->shoot_can_system->set(CAPTAIN_ID,0);
}

bool ShootSystem::update() {
    int16_t frict_ref[2], captain_ref;

    frict_ref[FRICTWHEEL_LEFT_ID] = -2000;
    frict_ref[FRICTWHEEL_RIGHT_ID] = 2000;
    captain_ref = 100;

    int16_t frict_fdb[2], captain_fdb;

    frict_fdb[FRICTWHEEL_LEFT_ID] = oi->shoot_can_system->get (FRICTWHEEL_LEFT_ID)*2;
    frict_fdb[FRICTWHEEL_RIGHT_ID] = oi->shoot_can_system->get (FRICTWHEEL_RIGHT_ID)*2;
    captain_fdb = oi->shoot_can_system->get (CAPTAIN_ID);

    int16_t frict_output[2],captain_output;

    frict_output[FRICTWHEEL_LEFT_ID] = this->PosPID_L.PIDCalc (frict_ref[FRICTWHEEL_LEFT_ID],frict_fdb[FRICTWHEEL_LEFT_ID]);
    frict_output[FRICTWHEEL_RIGHT_ID] = this->PosPID_R.PIDCalc (frict_ref[FRICTWHEEL_RIGHT_ID],frict_fdb[FRICTWHEEL_RIGHT_ID]);
    captain_output = this->PosPID_cap.PIDCalc (captain_ref,captain_fdb);

    oi->shoot_can_system->set (FRICTWHEEL_LEFT_ID,frict_output[FRICTWHEEL_LEFT_ID]);
    oi->shoot_can_system->set (FRICTWHEEL_RIGHT_ID,frict_output[FRICTWHEEL_RIGHT_ID]);
    oi->shoot_can_system->set (CAPTAIN_ID,2000);


}

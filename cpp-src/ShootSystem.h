

#ifndef RMV3TESTDEMO_SHOOTSYSTEM_H
#define RMV3TESTDEMO_SHOOTSYSTEM_H

#include "PIDSystem.h"
#include "hal.h"
#define CAPTAIN_ID 2
#define FRICTWHEEL_LEFT_ID 0
#define FRICTWHEEL_RIGHT_ID 1
class ShootSystem {
private:
    PosPIDSystem<float> PosPID_R,PosPID_L,PosPID_cap;
    const float Kp = 22, ki = 0, Kd = 0;
    const float output_max = 5000, total_error = 2000;
public:
    bool initialize();

    bool update();
};


#endif //RMV3TESTDEMO_SHOOTSYSTEM_H

/**
  *@file RemoteSystem.h
  *@date 2019-1-26
  *@author Azusa Katze
  *@brief
  */

#ifndef RMV3TESTDEMO_REMOTESYSTEM_H
#define RMV3TESTDEMO_REMOTESYSTEM_H

#include "hal.h"

#define CTR_CH1 0
#define CTR_CH2 1
#define CTR_CH3 2
#define CTR_CH4 3
#define CTR_SW1 4
#define CTR_SW2 5



class RemoteSystem {
public:
    RemoteSystem ();

    bool initialize ();

    bool destroy ();

    bool update ();

    int16_t getAxis (int id);

    int16_t getButton (int id);
};


#endif //RMV3TESTDEMO_REMOTESYSTEM_H

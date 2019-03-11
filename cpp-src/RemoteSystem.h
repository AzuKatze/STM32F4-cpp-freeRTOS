/**
  *@file RemoteSystem.h
  *@date 2019-1-26
  *@author Azusa Katze
  *@brief
  */

#ifndef RMV3TESTDEMO_REMOTESYSTEM_H
#define RMV3TESTDEMO_REMOTESYSTEM_H

#include "hal.h"

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

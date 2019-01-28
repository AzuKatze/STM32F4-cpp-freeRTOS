/**
  *@file IMUSystem.cpp
  *@date 2019-1-26
  *@author Azusa Katze
  *@brief
  */

#include "IMUSystem.h"

IMUSystem::IMUSystem() {

}

bool IMUSystem::initialize() {
    init_quaternion ();
    mpu_device_init ();
    return true;
}

float IMUSystem::get(int data) {
    switch(data){
        case IMU_ROLL:
            return imu.rol;
        case IMU_PITCH:
            return imu.pit;
        case IMU_YAW:
            return imu.yaw;
        default:
            return 0;

    }
}

bool IMUSystem::update() {
    mpu_get_data();
    imu_ahrs_update();
    imu_attitude_update();
    return true;
}
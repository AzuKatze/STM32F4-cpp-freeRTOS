/**
  *@file CANSystem.cpp
  *@date 2019-1-26
  *@author Azusa Katze
  *@brief
  */

#ifndef RMV3TESTDEMO_PIDSYSTEM_H
#define RMV3TESTDEMO_PIDSYSTEM_H

#include "hal.h"

template <typename T>
class PIDSystem{
protected:
    T kp_,ki_,kd_;
    T output_max_;
public:
    PIDSystem(){

    }

};

template <typename T>
class PosPIDSystem : PIDSystem<T> {
private:
    T total_error_max_;
    T total_error_,prev_error_;
public:
    PosPIDSystem(){

    }
    bool inititalize (T kp ,T ki ,T kd ,T output_max ,T total_error_max){
        this->kp_ = kp;
        this->kd_ = kd;
        this->ki_ = ki;
        this->output_max_ = output_max;
        this->total_error_max_=total_error_max;
        this->prev_error_ = 0;
        this->total_error_ = 0;
        return true;
    }

    T PIDCalc (T ref , T real){
        T error = ref - real;
        T dError = error - prev_error_;
        total_error_ += error;

        if(total_error_ > total_error_max_)
            total_error_ = total_error_max_;
        if(total_error_ < -total_error_max_)
            total_error_ = -total_error_max_;

        T outPut= (this->kp_ * error + this->ki_ * total_error_ + this->kd_ * dError);

        if(outPut > this->output_max_)
            outPut = this->output_max_;
        if(outPut < -this->output_max_)
            outPut = -this->output_max_;

        this->prev_error_ = error;

        return outPut;
    }

    bool reset (){
        this->total_error_ = 0;
        this->prev_error_ = 0;
        return true;
    }
};

template <typename T>
class IncrPIDSystem : PIDSystem<T> {
private:
    T output_max_;
    T prev_error_,last_error_;
public:
    IncrPIDSystem(){

    }
    bool inititalize (T kp ,T ki ,T kd ,T output_max ){
        this->kp_ = kp;
        this->kd_ = kd;
        this->ki_ = ki;
        this->output_max_ = output_max;
        this->last_error_=0;
        this->prev_error_ = 0;
        return true;
    }
    T PIDCalc (T ref , T real){
        T error = ref - real;

        T outPut = (this->kp_*(error - prev_error_) + this->ki_*(error) + this->kd_*(error - 2*prev_error_ + last_error_));

        if(outPut > this->output_max_)
            outPut = this->output_max_;
        if(outPut < -this->output_max_)
            outPut = -this->output_max_;

        this->last_error_ = this->prev_error_;
        this->prev_error_ = error;

        return outPut;
    }

    bool reset (){
        this->prev_error_ = 0;
        this->last_error_ = 0;
        return true;
    }
};


#endif //RMV3TESTDEMO_PIDSYSTEM_H

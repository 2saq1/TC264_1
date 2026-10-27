/*
 * Algorithm.c
 *
 *  Created on: 2026年10月25日
 *      Author: SONG
 */

#include "zf_common_headfile.h"

//***************************************************增量式PID********************************************************************
pid_param_t PID_LM;
pid_param_t PID_RM;

void pid_param_t_init(void)//PID参数初始化
{
    PID_LM.kp = 0;
    PID_LM.ki = 0;
    PID_LM.kd = 0;
    PID_LM.imax = 0;

    PID_RM.kp = 0;
    PID_RM.ki = 0;
    PID_RM.kd = 0;
    PID_RM.imax = 0;
}

void Commen_mode_pid(void)
{
    PID_LM.kp = 1;//后调，一般从1开始
    PID_LM.ki = 1;//先调I,一般从0.1开始
    PID_LM.kd = 0;//增量式PID,不调D
    PID_LM.imax = 10000;

    PID_RM.kp = 1;
    PID_RM.ki = 1;
    PID_RM.kd = 0;
    PID_RM.imax = 10000;
}

float PidIncCtrl(pid_param_t * pid, float error)//增量式PID本体
{
    pid->out_p = pid->kp * (error - pid->last_error);
    pid->out_i = pid->ki * error;
    pid->out_d = pid->kd * ((error - pid->last_error) - pid->last_derivative);

    pid->last_derivative = error - pid->last_error;
    pid->last_error = error;

    pid->out += pid->out_p + pid->out_i + pid->out_d;

    if (pid->out >  pid->imax) pid->out =  pid->imax;
    if (pid->out < -pid->imax) pid->out = -pid->imax;

    return pid->out;
}

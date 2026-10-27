/*
 * Algorithm.h
 *
 *  Created on: 2026年10月25日
 *      Author: SONG
 */

#ifndef CODE_ALGORITHM_H_
#define CODE_ALGORITHM_H_

//***************************************************增量式PID********************************************************************

typedef struct
{
    float              kp;                 //P
    float              ki;                 //I
    float              kd;                 //D
    float              imax;               //积分限幅,越大，速度越快，但容易超调

    float              out_p;              //Kp输出
    float              out_i;              //Ki输出
    float              out_d;              //Kd输出
    float              out;                //pid输出

    float              integrator;         //<积分值
    float              last_error;         //<上次误差
    float              last_derivative;    //<上次误差与上上次误差之差
    unsigned long      last_t;             //<上次时间
}pid_param_t;

extern pid_param_t PID_LM;
extern pid_param_t PID_RM;

void pid_param_t_init(void);//PID参数初始化
void Commen_mode_pid(void);//普通PID
float PidIncCtrl(pid_param_t * pid, float error);//增量式PID本体

#endif /* CODE_ALGORITHM_H_ */

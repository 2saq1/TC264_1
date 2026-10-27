/*
 * Body_ctrl.c
 *
 *  Created on: 2026年10月26日
 *      Author: SONG
 */
#include "zf_common_headfile.h"

int32 LT_SPEED,RT_SPEED = 0;

void Speed_loop(void)//速度环
{
    int32 LT_SPEED = 3;
    int32 RT_SPEED = 3;

    static bool once = false;
    if(!once)
    {
        Commen_mode_pid();
        once = true;
    }

    DRV8701_D_motor_loop_control(LT_SPEED,RT_SPEED);//填入目标速度
}




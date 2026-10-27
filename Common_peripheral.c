/*
 * Common_peripheral.C
 *
 *  Created on: 2026年10月20日
 *      Author: SONG
 */
#include "zf_common_headfile.h"

//*************************************************蜂鸣器***************************************************************
//蜂鸣器初始化
//高电平响，低电平不响(0低电平，1高电平)
void Beep_init(void)
{
    gpio_init(BEEP_PIN , GPO , 0 , GPO_PUSH_PULL);
}

//蜂鸣器自检
void Beep_check(int TIME)
{
    gpio_set_level(BEEP_PIN , 1);//响
    system_delay_ms(TIME);//通过更改形参，来控制响的时间
    gpio_set_level(BEEP_PIN , 0);//不响
}

//**************************************************LED***************************************************************
//板载LED是共阳极，给低电平会亮，高电平会灭
//LED初始化
void LED_init(void)
{
    gpio_init(LED1_PIN , GPO , 1 , GPO_PUSH_PULL);
    gpio_init(LED2_PIN , GPO , 1 , GPO_PUSH_PULL);
    gpio_init(LED3_PIN , GPO , 1 , GPO_PUSH_PULL);
    gpio_init(LED4_PIN , GPO , 1 , GPO_PUSH_PULL);
}

//**************************************************按键***************************************************************

//按键初始化
//按键为接收外界电平，自己为1为0不重要,上拉输入
void Key_init(void)
{
    gpio_init(KEY1_PIN , GPI , 1 , GPI_PULL_UP);
    gpio_init(KEY2_PIN , GPI , 1 , GPI_PULL_UP);
    gpio_init(KEY3_PIN , GPI , 1 , GPI_PULL_UP);
    gpio_init(KEY4_PIN , GPI , 1 , GPI_PULL_UP);
}

int KET1_STATE = 1;//KEY_STATE代表当前按键状态
int KET2_STATE = 1;
int KET3_STATE = 1;
int KET4_STATE = 1;

int KET1_STATE_LAST = 0;//KEY_STATE_LAST代表上一次按键状态
int KET2_STATE_LAST = 0;
int KET3_STATE_LAST = 0;
int KET4_STATE_LAST = 0;

int KET1_FLAG = 0;//KEY_FLAG代表按键触发标志位
int KET2_FLAG = 0;
int KET3_FLAG = 0;
int KET4_FLAG = 0;

//按键扫描
void Key_scan(void)
{
    //记录当前按键状态
    KET1_STATE_LAST = KET1_STATE;
    KET2_STATE_LAST = KET2_STATE;
    KET3_STATE_LAST = KET3_STATE;
    KET4_STATE_LAST = KET4_STATE;

    //更新当前状态
    KET1_STATE = gpio_get_level(KEY1_PIN);
    KET2_STATE = gpio_get_level(KEY2_PIN);
    KET3_STATE = gpio_get_level(KEY3_PIN);
    KET4_STATE = gpio_get_level(KEY4_PIN);

    //比较状态
    if(KET1_STATE && !KET1_STATE_LAST){KET1_FLAG = 1;}
    if(KET2_STATE && !KET2_STATE_LAST){KET2_FLAG = 1;}
    if(KET3_STATE && !KET3_STATE_LAST){KET3_FLAG = 1;}
    if(KET4_STATE && !KET4_STATE_LAST){KET4_FLAG = 1;}

}

//按键清零，并且蜂鸣器响一下
void Key1_clear(void)
{
    KET1_FLAG = 0;
    Beep_check(100);
}

void Key2_clear(void)
{
    KET2_FLAG = 0;
    Beep_check(200);
}

void Key3_clear(void)
{
    KET3_FLAG = 0;
    Beep_check(300);
}

void Key4_clear(void)
{
    KET4_FLAG = 0;
    Beep_check(400);
}

//按键、蜂鸣器测试函数
void Key1_TEXT(void)
{
    Key_scan();
    if(KET1_FLAG)
    {
        Key1_clear();
    }
}

void Key2_TEXT(void)
{
    Key_scan();
    if(KET2_FLAG)
    {
        Key2_clear();
    }
}

void Key3_TEXT(void)
{
    Key_scan();
    if(KET3_FLAG)
    {
        Key3_clear();
    }
}

void Key4_TEXT(void)
{
    Key_scan();
    if(KET4_FLAG)
    {
        Key4_clear();
    }
}
//******************************************************电机驱动***************************************************************
//DRV8701
//转速由PWM引脚控制，转向由IO高低控制

//DRV8701初始化
void DRV8701_init(void)
 {
     gpio_init(L_DIR , GPO , 0 , GPO_PUSH_PULL);
     pwm_init(L_PWM , 17000 , 0);

     gpio_init(R_DIR , GPO , 0 , GPO_PUSH_PULL);
     pwm_init(R_PWM , 17000 , 0);
 }

//DRV8701开环驱动函数
void DRV8701_D_motor_control(int32 L_SPEED,int32 R_SPEED)
{
    L_SPEED=L_SPEED<M_MIN?M_MIN:(L_SPEED>M_MAX)?M_MAX:L_SPEED;//三目运算符，限幅
    R_SPEED=R_SPEED<M_MIN?M_MIN:(R_SPEED>M_MAX)?M_MAX:R_SPEED;

    if(L_SPEED > 0)//人为定义大于0向前转
    {
        gpio_set_level(L_DIR,1);//高电平,向前转
        pwm_set_duty(L_PWM , L_SPEED);
    }
    else
    {
        gpio_set_level(L_DIR,0);//低电平,向后转
        pwm_set_duty(L_PWM , -L_SPEED);
    }

    if(R_SPEED > 0)//人为定义大于0向前转
    {
        gpio_set_level(R_DIR,1);//高电平,向前转
        pwm_set_duty(R_PWM , R_SPEED);
    }
    else
    {
        gpio_set_level(R_DIR,0);//低电平,向后转
        pwm_set_duty(R_PWM , -R_SPEED);
    }

}

//DRV8701闭环驱动函数
void DRV8701_D_motor_loop_control(int32 LT_SPEED,int32 RT_SPEED)
{
    DRV8701_D_motor_control(PidIncCtrl(&PID_LM,(float)LT_SPEED-L_AV),PidIncCtrl(&PID_RM,(float)RT_SPEED-R_AV));
}


void Motor_text(void)//电机驱动测试函数
{
    static int32 L_PSEED = 0,R_PSEED = 0;
    Key_scan();

    if(KET1_FLAG)
    {
        KET1_FLAG = 0;
        L_PSEED += 500;
    }

    if(KET2_FLAG)
    {
        KET2_FLAG = 0;
        L_PSEED -= 500;
    }

    if(KET3_FLAG)
    {
        KET3_FLAG = 0;
        R_PSEED += 500;
    }

    if(KET4_FLAG)
    {
        KET4_FLAG = 0;
        R_PSEED -= 500;
    }

    ips200_show_string(5*0,16*1,"MOTOR_text");
    ips200_show_string(8*0,16*3,"LV:");
    ips200_show_string(8*0,16*4,"RV:");
    ips200_show_int(8*5,16*3,L_PSEED,5);
    ips200_show_int(8*5,16*4,R_PSEED,5);

    DRV8701_D_motor_control(L_PSEED,R_PSEED);

}

//******************************************************舵机********************************************************************
//舵机初始化
void STEER_init(void)
 {
    pwm_init(SERVO_MOTOR_PWM , 300 , (uint32)SERVO_MOTOR_DUTY(SERVO_MOTOR_MID));//这里的初始值是中值
 }

//舵机驱动函数
void STEER_SET(int ANGLE)
 {
    ANGLE=ANGLE<SERVO_MOTOR_RMAX?SERVO_MOTOR_RMAX:(ANGLE>SERVO_MOTOR_LMAX)?SERVO_MOTOR_LMAX:ANGLE;//舵机限幅
    pwm_set_duty(SERVO_MOTOR_PWM , (uint32)SERVO_MOTOR_DUTY(ANGLE));
 }

//舵机测试函数
void STEER_text(void)
{

}


//******************************************************编码器*****************************************************************
//1-L,2-R
void DIR_encode_init(void)
{
    encoder_dir_init(ENCODER_1,ENCODER_1_A,ENCODER_1_B);
    encoder_dir_init(ENCODER_2,ENCODER_2_A,ENCODER_2_B);
}

int32 L_AV=0;//回传真实速度
int32 R_AV=0;
void DIR_encode_pulse_get(void)
{
    L_AV = encoder_get_count(ENCODER_1);
    encoder_clear_count(ENCODER_1);
    R_AV = encoder_get_count(ENCODER_2);
    encoder_clear_count(ENCODER_2);
}

void ENCODR_text(void)//编码器测试函数
{
    static int32 L_PSEED = 0,R_PSEED = 0;
    Key_scan();

    if(KET1_FLAG)
    {
        KET1_FLAG = 0;
        L_PSEED += 500;
    }

    if(KET2_FLAG)
    {
        KET2_FLAG = 0;
        L_PSEED -= 500;
    }

    if(KET3_FLAG)
    {
        KET3_FLAG = 0;
        R_PSEED += 500;
    }

    if(KET4_FLAG)
    {
        KET4_FLAG = 0;
        R_PSEED -= 500;
    }

    ips200_show_string(5*0,16*1,"ENCODER_text");
    ips200_show_string(8*0,16*3,"L_AV:");
    ips200_show_string(8*0,16*4,"R_AV:");
    ips200_show_int(8*5,16*3,L_AV,5);
    ips200_show_int(8*5,16*4,R_AV,5);

    DRV8701_D_motor_control(L_PSEED,R_PSEED);
}

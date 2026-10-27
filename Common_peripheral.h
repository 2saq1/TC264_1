/*
 * Common_peripheral.h
 *
 *  Created on: 2026年10月20日
 *      Author: SONG
 */

#ifndef CODE_COMMON_PERIPHERAL_H_
#define CODE_COMMON_PERIPHERAL_H_

//*************************************************宏定义*****************************************************************
#define BEEP_PIN  P33_10  //蜂鸣器引脚

#define LED1_PIN  P20_1   //LED引脚
#define LED2_PIN  P20_8
#define LED3_PIN  P20_5
#define LED4_PIN  P20_4

#define KEY1_PIN  P20_6   //按键引脚
#define KEY2_PIN  P20_7
#define KEY3_PIN  P20_8
#define KEY4_PIN  P20_9

#define L_DIR  P21_2   //DRV8701引脚
#define L_PWM  ATOM1_CH1_P21_3
#define R_DIR  P21_4
#define R_PWM  ATOM1_CH3_P21_5
#define M_MAX   10000 //限幅
#define M_MIN  -10000


#define SERVO_MOTOR_PWM       (ATOM0_CH1_P33_9) //舵机引脚
#define SERVO_MOTOR_FREQ      (300)  //主板上舵机频率
#define SERVO_MOTOR_LMAX      (180)  //左极限,根据实际情况测试
#define SERVO_MOTOR_RMAX      (0)  //右极限,根据实际情况测试
#define SERVO_MOTOR_MID       (90)  //中值,根据实际情况测试
#define SERVO_MOTOR_DUTY(x)   ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)/90.0)) //舵机占空比计算方式


#define ENCODER_1     (TIM4_ENCODER)            //编码器引脚
#define ENCODER_1_A   (TIM4_ENCODER_CH1_P02_8)//计数
#define ENCODER_1_B   (TIM4_ENCODER_CH2_P00_9)//计数方向

#define ENCODER_2     (TIM3_ENCODER)
#define ENCODER_2_A   (TIM3_ENCODER_CH1_P02_6)//计数
#define ENCODER_2_B   (TIM3_ENCODER_CH2_P02_7)//计数方向


//*******************************************************全局变量*****************************************************************
extern int KET1_FLAG;//KEY_FLAG代表按键触发标志位
extern int KET2_FLAG;
extern int KET3_FLAG;
extern int KET4_FLAG;

extern int32 L_AV;
extern int32 R_AV;
//*************************************************函数声明****************************************************************

//************************************************************蜂鸣器
void Beep_init(void);//蜂鸣器初始化
void Beep_check(int TIME);//蜂鸣器自检（ms）
//************************************************************LED
void LED_init(void);//LED初始化


//************************************************************按键
void Key_init(void);//按键初始化
void Key_scan(void);//按键扫描（调用时记得判断KET_FLAG是否要清零）

void Key1_clear(void);//按键清零，并且蜂鸣器响一下
void Key2_clear(void);
void Key3_clear(void);
void Key4_clear(void);

void Key1_TEXT(void);//按键测试函数
void Key2_TEXT(void);
void Key3_TEXT(void);
void Key4_TEXT(void);

//************************************************************DRV8701
void DRV8701_init(void);//电机驱动初始化
void DRV8701_D_motor_control(int32 L_SPEED,int32 R_SPEED);//开环驱动函数
void DRV8701_D_motor_loop_control(int32 LT_SPEED,int32 RT_SPEED);//闭环驱动函数
void Motor_text(void);//电机测试


//************************************************************舵机
void STEER_init(void);//舵机初始化
void STEER_SET(int ANGLE);//舵机驱动函数
void STEER_text(void);//舵机测试函数


//************************************************************编码器
void DIR_encode_init(void);//编码器初始化
void DIR_encode_pulse_get(void);//速度读取函数
void ENCODR_text(void);//编码器测试函数


#endif /* CODE_COMMON_PERIPHERAL_H_ */

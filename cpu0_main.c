/*********************************************************************************************************************
* TC264 Opensourec Library 即（TC264 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是 TC264 开源库的一部分
*
* TC264 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          cpu0_main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          ADS v1.10.2
* 适用平台          TC264D
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者                备注
* 2022-09-15       pudding            first version
********************************************************************************************************************/
#include "zf_common_headfile.h"
#pragma section all "cpu0_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中

// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设


// **************************** 代码区域 ****************************
int core0_main(void)
{
    clock_init();                   // 获取时钟频率<务必保留>
    debug_init();                   // 初始化默认调试串口
    // 此处编写用户代码 例如外设初始化代码等

   Beep_init();//蜂鸣器初始化
   Key_init();//按键初始化
   LED_init();//;LED初始化
   DRV8701_init();//电机驱动初始化

   //Beep_check(200);//硬件自检

   system_delay_ms(1000);//延迟1000MS

   pit_ms_init(CCU60_CH0,1);//定时器0初始化（中断编号，中断时间）
   pid_param_t_init();//PID参数初始化
   DIR_encode_init();//编码器初始化

   //Beep_check(200);//软件自检

   ips200_init(IPS200_TYPE_SPI);//屏幕初始化
   ips200_full(RGB565_BLACK);
   ips200_set_color(RGB565_WHITE ,  RGB565_BLACK);


    // 此处编写用户代码 例如外设初始化代码等
    cpu_wait_event_ready();         // 等待所有核心初始化完毕

    while (TRUE)
    {


            ips200_show_string(10,10,"a=");
          ips200_show_int(30,10,L_AV,10);
          ips200_show_string(10,30,"OUT:");
                  ips200_show_int(50,30,(int)PID_LM.out,8);
                  ips200_show_string(10,50,"ERR:");
                  ips200_show_int(50,50,(int)(3-L_AV),6);

                  //DRV8701_D_motor_control(3000,3000);


        //Motor_text();
        //ENCODR_text();
//        Key_scan();
//        {
//          if(KET1_FLAG)
//          {
//            a+=10;
//            ips200_full(RGB565_BLACK);
//            ips200_show_string(10,10,"a=");
//            ips200_show_int(30,10,a,10);
//            KET1_FLAG = 0;  //使用时要判断是否清零，不清零可以陷入死循环
//          }
//        }
//
//        Key_scan();
//        {
//          if(KET2_FLAG)
//          {
//            a-=10;
//            ips200_full(RGB565_BLACK);
//            ips200_show_string(10,10,"a=");
//            ips200_show_int(30,10,a,10);
//            KET2_FLAG = 0;  //使用时要判断是否清零，不清零可以陷入死循环
//          }
//        }
//
//        Key_scan();
//        {
//          if(KET3_FLAG)
//          {
//            b+=10;
//            ips200_full(RGB565_BLACK);
//            ips200_show_string(10,10,"b=");
//            ips200_show_int(30,10,b,10);
//            KET3_FLAG = 0;  //使用时要判断是否清零，不清零可以陷入死循环
//           }
//        }
//
//        Key_scan();
//        {
//          if(KET4_FLAG)
//          {
//            b-=10;
//            ips200_full(RGB565_BLACK);
//            ips200_show_string(10,10,"b=");
//            ips200_show_int(30,10,b,10);
//            KET4_FLAG = 0;  //使用时要判断是否清零，不清零可以陷入死循环
//          }
//         }
//
//
//        DRV8701_D_motor_control(a,0);
//
//
    }
}

IFX_INTERRUPT(cc60_pit_ch0_isr, 0, CCU6_0_CH0_ISR_PRIORITY)
{
    interrupt_global_enable(0);                     // 开启中断嵌套
    pit_clear_flag(CCU60_CH0);

    static int32 system_time_count=0;
    system_time_count++;

    if(system_time_count%5==0)//每隔5MS读取一次数值
    {
        Key_scan();
        DIR_encode_pulse_get();
        Speed_loop();
    }

}

#pragma section all restore
// **************************** 代码区域 ****************************

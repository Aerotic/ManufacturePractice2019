/*********************************************************************************************
* 文件: led.c
* 作者：liutong 2015.8.19
* 说明：LED驱动程序头文件
*       D1->PE0;D2->PE1;D3->PE2;D4->PE3;R->PB0;G->PB1;B->PB2
* 修改：chennian 2017.11.02 修改初始化引脚
*       zhoucj   2017.12.18 增加注释
* 注释：
*********************************************************************************************/
#ifndef _LED_H_
#define _LED_H_
/*********************************************************************************************
*头文件
**********************************************************************************************/
#include "stm32f4xx.h"
/*********************************************************************************************
*宏定义
**********************************************************************************************/
#define D1      0X01                                            //宏定义D1数字编号  
#define D2      0X02                                            //宏定义D2数字编号 
#define D3      0X04                                            //宏定义D3数字编号 
#define D4      0X08                                            //宏定义D4数字编号 
#define LEDR    0X10                                            //宏定义红灯数字编号 
#define LEDG    0X20                                            //宏定义绿灯数字编号 
#define LEDB    0X40                                            //宏定义蓝灯数字编号

/*********************************************************************************************
*函数声明
**********************************************************************************************/
void led_init(void);                                            //LED引脚初始化
void turn_on(unsigned char Led);                                //开LED函数
void turn_off(unsigned char Led);                               //关LED函数
unsigned char get_led_status(void);                             //获取LED当前的状态

#endif  /*__LED_H__*/


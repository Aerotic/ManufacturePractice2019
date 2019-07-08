/*********************************************************************************************
*实验现象：
*       LED3、LED4常亮表示系统处于运行状态
*       LED3、LED4长灭表示系统处于休眠状态
*       系统运行一段时间后自动进入休眠状态
*       按下key3按键可以将系统从休眠状态唤醒
*********************************************************************************************/

/*********************************************************************************************
* 头文件
*********************************************************************************************/
#include "stm32f4xx.h"
#include "delay.h"
#include "led.h"
#include "exti.h"
char led_status = 0;                                            //声明一个表示LED灯状态的变量
/*********************************************************************************************
* 名称：main()
* 功能：LED驱动实验逻辑代码
* 参数：无
* 返回：无
* 修改：
*********************************************************************************************/
void main(void)
{
  led_init();                                                   //初始化LED控制管脚
  exti_init();                                                  //初始化按键中断
  turn_on(D3);                                                  //D3开
  turn_on(D4);                                                  //D4开
  while(1){                                                     //循环体
    for(int n=100;n>0;n--)
    {
      delay_count(2000);                                        //延时
    }
    turn_off(D3);                                               //D3关
    __WFI();                                                    //进入睡眠模式
  }
}  
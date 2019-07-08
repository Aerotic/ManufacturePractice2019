/*********************************************************************************************
* 文件：clock.c
* 作者：Meixin 2017.09.27
* 说明：系统时钟驱动代码   
* 修改：
* 注释：
*********************************************************************************************/

/*********************************************************************************************
* 头文件
*********************************************************************************************/
#include "clock.h"

/*********************************************************************************************
* 名称：xtal_init()
* 功能：CC2530时钟初始化
* 参数：无
* 返回：无
* 修改：
* 注释：
*********************************************************************************************/
void xtal_init(void)
{
  CLKCONCMD &= ~0x40;                                           //选择32MHz的外部晶振
  while(CLKCONSTA & 0x40);                                      //晶体振荡器开启且稳定
  CLKCONCMD &= ~0x07;                                           //选择32MH系统时钟
  CLKCONCMD &= ~0x38;                                           //选择32MH定时器时钟
}
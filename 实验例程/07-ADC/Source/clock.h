/*********************************************************************************************
* 文件：sys_init.h
* 作者：Liyw 2017.5.30
* 说明：CC2530通用片上外设驱动代码头文件    
* 修改：
* 注释：
*********************************************************************************************/

/*********************************************************************************************
* 宏条件编译
*********************************************************************************************/
#ifndef __CLOCK_H__
#define __CLOCK_H__

/*********************************************************************************************
* 头文件
*********************************************************************************************/
#include <ioCC2530.h>                                           //引入CC2530所对应的头文件（包含各SFR的定义）

/*********************************************************************************************
* 宏定义
*********************************************************************************************/
#define CLKSPD                  (CLKCONCMD & 0x07)              //宏定义系统时钟分频系数

/*********************************************************************************************
* 内部原型函数
*********************************************************************************************/
void xtal_init(void);                                           //时钟初始化函数

#endif /*__CLOCK_H__*/
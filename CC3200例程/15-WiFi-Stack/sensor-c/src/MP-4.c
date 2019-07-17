/*********************************************************************************************
* 文件：MP-4.c
* 作者：Lixm 2017.10.17
* 说明：可燃气体驱动代码
* 修改：
* 注释：
*********************************************************************************************/

/*********************************************************************************************
* 头文件
*********************************************************************************************/
#include "MP-4.h"
#include "adc.h"
/*********************************************************************************************
* 名称：CombustibleGas_init()
* 功能：可燃气体传感器初始化
* 参数：无
* 返回：无
* 修改：
* 注释：
*********************************************************************************************/
void combustiblegas_init(void)
{
  MAP_PinTypeADC(PIN_60,PIN_MODE_255); //cc3200  ADC使用
  ADCChannelEnable(ADC_BASE, ADC_CH_3);//使能ADC通道3
  ADCTimerConfig(ADC_BASE, 2^17);       //配置ADC内部定时器
  ADCTimerEnable(ADC_BASE);             //使能内部定时器   
  ADCEnable(ADC_BASE);                  //ADC使能
}

/*********************************************************************************************
* 名称：unsigned int get_infrared_status(void)
* 功能：获取可燃气体传感器状态
* 参数：无
* 返回：无
* 修改：
* 注释：
*********************************************************************************************/
unsigned int get_combustiblegas_data(void)
{ 
  static int st = 0;
  
  unsigned int  value = 0;
  while(!ADCFIFOLvlGet(ADC_BASE, ADC_CH_3));
  value = ADCFIFORead(ADC_BASE, ADC_CH_3);
  float v = ((value >> 2 ) & 0x0FFF)*1.467/4096;  //计算电压
  //Report("v %.2f\r\n", v);
  if (st != 0 && v < 0.9) st = 0;
  else if (st==0 && v > 1.2) st = 1;
  return st;
}
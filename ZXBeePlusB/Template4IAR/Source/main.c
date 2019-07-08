#include "stm32f4xx.h"

void LED_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOEʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //ѡ�� 2��3 ������
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; //����ٶ� 2MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //��������
  GPIO_Init(GPIOE, &GPIO_InitStructure); //����������������GPIOE2��GPIOE3
}

void main(void)
{
  LED_Init(); //��ʼ��LED
  GPIO_ResetBits(GPIOE, GPIO_Pin_2) ;//����GPIOE2Ϊ�͵�ƽ
  GPIO_ResetBits(GPIOE, GPIO_Pin_3) ;//����GPIOE3Ϊ�͵�ƽ
  while(1);//��ѭ��
}

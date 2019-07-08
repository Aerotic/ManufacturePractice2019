/*********************************************************************************************
* �ļ���key.c
* ���ߣ�Liyw 2017.5.30
* ˵����K1 ��Ӧ���� PB12
*       K2 ��Ӧ�ܽ� PB13
*       K3 ��Ӧ���� PB14
*       K4 ��Ӧ�ܽ� PB15
* ���ܣ�������������
* �޸ģ�
*********************************************************************************************/

/*********************************************************************************************
* ͷ�ļ�
*********************************************************************************************/
#include "key.h"

/*********************************************************************************************
* ���ƣ�key_init
* ���ܣ�������ʼ��
* ��������
* ���أ���
* �޸ģ���
*********************************************************************************************/
void key_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;                          //����һ��GPIO_InitTypeKef���͵Ľṹ��
  RCC_AHB1PeriphClockCmd(KEY_CLK, ENABLE);                      //����KEY��ص�GPIO����ʱ��
  
  GPIO_InitStructure.GPIO_Pin   = K1_PIN | K2_PIN | 
                                  K3_PIN | K4_PIN;              //ѡ��Ҫ���Ƶ�GPIO����
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                //�������ŵ��������Ϊ����
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;                 //��������ģʽΪ����ģʽ
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;                 //��������Ϊ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;              //������������Ϊ2MHz
  
  GPIO_Init(KEY_PORT, &GPIO_InitStructure);                     //��ʼ��GPIO����
}

/*********************************************************************************************
* ���ƣ�key_gpio_init
* ���ܣ������ܽų�ʼ��
* ��������
* ���أ���
* �޸ģ���
*********************************************************************************************/
signed char key_status(char num)
{
  if(num == K1)
    return GPIO_ReadInputDataBit(KEY_PORT,K1_PIN);              //����K1��״̬

  if(num == K2)
    return GPIO_ReadInputDataBit(KEY_PORT,K2_PIN);              //����K2��״̬
  
  if(num == K3)
    return GPIO_ReadInputDataBit(KEY_PORT,K3_PIN);              //����K3��״̬
  
  if(num == K4)
    return GPIO_ReadInputDataBit(KEY_PORT,K4_PIN);              //����K4��״̬
  
  return -1;
}

/*********************************************************************************************
* �ļ���led.c
* ���ߣ�Liyw 2017.5.30
* ˵����D1 ��Ӧ���� PE0
*       D2 ��Ӧ�ܽ� PE1
*       D3 ��Ӧ���� PE2
*       D4 ��Ӧ�ܽ� PE3
* ���ܣ�led����������
* �޸ģ�
*********************************************************************************************/

/*********************************************************************************************
* ͷ�ļ�
*********************************************************************************************/
#include "led.h"

/*********************************************************************************************
* ���ƣ�led_init
* ���ܣ�led�Ƴ�ʼ��
* ��������
* ���أ���
* �޸ģ���
*********************************************************************************************/
void led_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;                          //����һ��GPIO_InitTypeDef���͵Ľṹ��
  RCC_AHB1PeriphClockCmd(LED_CLK, ENABLE);                      //����LED��ص�GPIO����ʱ��
  
  GPIO_InitStructure.GPIO_Pin = D1_PIN | D2_PIN | 
                                D3_PIN | D4_PIN;                //ѡ��Ҫ���Ƶ�GPIO����
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                //�������ŵ��������Ϊ�������
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                 //��������ģʽΪ���ģʽ
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                  //��������Ϊ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;              //������������Ϊ2MHz
  
  GPIO_Init(LED_PORT, &GPIO_InitStructure);                     //��ʼ��GPIO����
  GPIO_SetBits(LED_PORT,D1_PIN | D2_PIN | 
                        D3_PIN | D4_PIN);                       //����LED_D4��ʼ״̬Ϊ�ر�
}

/*********************************************************************************************
* ���ƣ�led_control
* ���ܣ�led�ƿ���
* ������num------led�Ʊ��,֧�ֶ�λͬʱ����
* ���أ���
* �޸ģ���
*********************************************************************************************/
void led_control(char num)
{
  if(num & D1)
    GPIO_ResetBits(LED_PORT,D1_PIN);                            //����D1Ϊ����
  else
    GPIO_SetBits(LED_PORT,D1_PIN);                              //����D1Ϊ�ر�
  
  if(num & D2)
    GPIO_ResetBits(LED_PORT,D2_PIN);                            //����D2Ϊ����
  else
    GPIO_SetBits(LED_PORT,D2_PIN);                              //����D2Ϊ�ر�
  
  if(num & D3)
    GPIO_ResetBits(LED_PORT,D3_PIN);                            //����D3Ϊ����
  else
    GPIO_SetBits(LED_PORT,D3_PIN);                              //����D3Ϊ�ر�
  
  if(num & D4)
    GPIO_ResetBits(LED_PORT,D4_PIN);                            //����D4Ϊ����
  else
    GPIO_SetBits(LED_PORT,D4_PIN);                              //����D4Ϊ�ر�
}

/*********************************************************************************************
* ���ƣ�led_status
* ���ܣ�led��״̬��ѯ
* ������num------led�Ʊ��
* ���أ���ӦLED״̬��ONΪ������OFFΪ�رգ�-1�ȱ�ʾ�����쳣
* �޸ģ���
*********************************************************************************************/
signed char led_status(char num)
{
  if(num == D1)
    return GPIO_ReadOutputDataBit(LED_PORT,D1_PIN);             //����D1��״̬

  if(num == D2)
    return GPIO_ReadOutputDataBit(LED_PORT,D2_PIN);             //����D2��״̬
  
  if(num == D3)
    return GPIO_ReadOutputDataBit(LED_PORT,D3_PIN);             //����D3��״̬
  
  if(num == D4)
    return GPIO_ReadOutputDataBit(LED_PORT,D4_PIN);             //����D4��״̬
  
  return -1;
}


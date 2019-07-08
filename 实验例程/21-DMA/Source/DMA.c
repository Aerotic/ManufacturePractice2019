/*********************************************************************************************
* �ļ���DMA.c
* ���ߣ�chennian 2017.11.2
* ˵����DMA��������    
* ���ܣ�ͨ��DMAͨ��������A�����ݸ��Ƹ�����B
*       ��λ����ֱ���ʾ����ǰ�͸��ƺ�����A������B������
* �޸ģ�
*********************************************************************************************/
/*********************************************************************************************
* ͷ�ļ�
*********************************************************************************************/
		 
#include "DMA.h"																	   	  
#include "delay.h"
/*********************************************************************************************
* ���ƣ�MYDMA_Config
* ���ܣ�DMAx��ͨ������
* ������DMA_Streamx:DMA������,DMA1_Stream0~7/DMA2_Stream0~7
*       chx:DMAͨ��ѡ��,@ref DMA_channel DMA_Channel_0~DMA_Channel_7
*       par:�����ַ
*       mar:�洢����ַ
*       ndtr:���ݴ����� 
* ���أ���
* �޸ģ���
*********************************************************************************************/
void DMA_Config(DMA_Stream_TypeDef *DMA_Streamx,uint32_t chx,uint32_t par,uint32_t mar,uint16_t ndtr)
{ 

  DMA_InitTypeDef  DMA_InitStructure;
  
  if((uint32_t)DMA_Streamx>(uint32_t)DMA2)                      //�õ���ǰstream������DMA2����DMA1
  {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);         //DMA2ʱ��ʹ��
    
  }else 
    {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);         //DMA1ʱ��ʹ��
    }
    DMA_DeInit(DMA_Streamx);
  
  while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE){}            //�ȴ�DMA������
  
  /* ����DMA Stream */
  DMA_InitStructure.DMA_Channel = chx;                          //ͨ��ѡ��
  DMA_InitStructure.DMA_PeripheralBaseAddr = par;               //DMA�����ַ
  DMA_InitStructure.DMA_Memory0BaseAddr = mar;                  //DMA�洢��0��ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToMemory;           //�洢�����洢��ģʽ
  DMA_InitStructure.DMA_BufferSize = ndtr;                      //���ݴ����� 
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;//���������ģʽ
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;       //�洢������ģʽ
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//�������ݳ���8
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//�洢�����ݳ���8
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                 //ʹ����ͨģʽ  
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;         //�е����ȼ�
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_INC8;     //�洢��ͻ�����δ���
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_INC8;//���赥�δ���
  DMA_Init(DMA_Streamx, &DMA_InitStructure);                    //��ʼ��DMA Stream
  
  
} 
/*********************************************************************************************
* ���ƣ�DMA_Enable
* ���ܣ�����һ��DMA����
* ������DMA_Streamx:DMA������,DMA1_Stream0~7/DMA2_Stream0~7
*       ndtr:���ݴ����� 
* ���أ���
* �޸ģ���
*********************************************************************************************/

void DMA_Enable(DMA_Stream_TypeDef *DMA_Streamx,uint16_t ndtr)
{
  
  DMA_Cmd(DMA_Streamx, DISABLE);                                //�ر�DMA����
  
  while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE){}	        //ȷ��DMA���Ա����� 
  
  DMA_SetCurrDataCounter(DMA_Streamx,ndtr);                     //���ݴ�����
  
  DMA_Cmd(DMA_Streamx, ENABLE);                                 //����DMA����
}	  


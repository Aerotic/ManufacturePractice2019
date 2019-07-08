/*********************************************************************************************
* �ļ���dma.c
* ���ߣ�Meixin 2017.09.26
* ˵����DMA������������    
* �޸ģ�
* ע�ͣ�
*********************************************************************************************/

/*********************************************************************************************
* ͷ�ļ�
*********************************************************************************************/
#include "dma.h"

/*********************************************************************************************
* ���ƣ�
* ���ܣ���������DMA�Ľṹ��
* ��������
* ���أ���
* �޸ģ�
* ע�ͣ�
*********************************************************************************************/
#pragma bitfields=reversed
typedef struct
{
  unsigned char SRCADDRH;                                       //Դ��ַ��8λ
  unsigned char SRCADDRL;                                       //Դ��ַ��8λ
  unsigned char DESTADDRH;                                      //Ŀ�ĵ�ַ��8λ
  unsigned char DESTADDRL;                                      //Ŀ�ĵ�ַ��8λ
  unsigned char VLEN        :3;                                 //������ģʽѡ��
  unsigned char LENH        :5;                                 //���䳤�ȸ��ֽ�
  unsigned char LENL        :8;                                 //���䳤�ȵ��ֽ�
  unsigned char WORDSIZE    :1;                                 //�ֽڣ�byte�����֣�word������
  unsigned char TMODE       :2;                                 //����ģʽѡ��
  unsigned char TRIG        :5;                                 //�����¼�ѡ��
  unsigned char SRCINC      :2;                                 //Դ��ַ������-1/0/1/2
  unsigned char DESTINC     :2;                                 //Ŀ�ĵ�ַ������-1/0/1/2
  unsigned char IRQMASK     :1;                                 //�ж�����
  unsigned char M8          :1;                                 //7��8bit���䳤�ȣ������ֽڴ���ģʽ������
  unsigned char PRIORITY    :2;                                 //���ȼ�
}DMA_CFG;
#pragma bitfields=default

/*********************************************************************************************
* ���ƣ�dma_test()
* ���ܣ�DMA���亯��
* ��������
* ���أ���
* �޸ģ�
* ע�ͣ�
*********************************************************************************************/
void dma_test(void)
{
  DMA_CFG dmaConfig;                                            //�������ýṹ��
  
  char sourceString[]="{data=I'm the sourceString!}\r\n";        //Դ�ַ���
  char destString[sizeof(sourceString)]="{data=I'm the destString!}\r\n";       //Ŀ���ַ���
  
  char i;
  char error=0;
   
  uart1_send_string(sourceString);                               //����ǰ��ԭ�ַ�����
  hal_wait(250);
  hal_wait(250);
  uart1_send_string(destString);                                 //����ǰ��Ŀ���ַ�����
  
  //����DMA�ṹ��
  dmaConfig.SRCADDRH=(unsigned char)((unsigned int)&sourceString >> 8);         //Դ��ַ
  dmaConfig.SRCADDRL=(unsigned char)(((unsigned int)&sourceString)&0xFF);
    
  dmaConfig.DESTADDRH=(unsigned char)((unsigned int)&destString >> 8);          //Ŀ�ĵ�ַ
  dmaConfig.DESTADDRL=(unsigned char)(((unsigned int)&destString)&0xFF);
  
  dmaConfig.VLEN=0x00;                                          //ѡ��LEN��Ϊ���ͳ���
  
  dmaConfig.LENH=(unsigned char)((unsigned int)sizeof(sourceString) >> 8);      //���䳤��
  dmaConfig.LENL=(unsigned char)((unsigned int)sizeof(sourceString));
  
  dmaConfig.WORDSIZE=0x00;                                      //ѡ���ֽڣ�byte������
  
  dmaConfig.TMODE=0x01;                                         //ѡ��鴫�ͣ�block��ģʽ
  
  dmaConfig.TRIG=0;                                             //�޴���(�������Ϊ�ֶ�������
  
  dmaConfig.SRCINC=0x01;                                        //Դ��ַ����Ϊ1
  
  dmaConfig.DESTINC=0x01;                                       //Ŀ�ĵ�ַ����Ϊ1
  
  dmaConfig.IRQMASK=0;                                          //DMA�ж�����
    
  dmaConfig.M8=0x00;                                            //ѡ��8λ�����ֽ�����������
  
  dmaConfig.PRIORITY=0x02;                                      //�������ȼ�Ϊ��
  

  DMA0CFGH=(unsigned char)((unsigned int)&dmaConfig >> 8);      //�����ýṹ����׵�ַ�������SFR
  DMA0CFGL=(unsigned char)((unsigned int)(&dmaConfig)&0xFF);
  
  DMAARM=0x01;                                                  //��������
  
  DMAIRQ=0x00;                                                  //���жϱ�־
  DMAREQ=0x01;                                                  //����DMA����
  
  while(!(DMAIRQ&0x01));                                        //�ȴ��������
  hal_wait(250);
  hal_wait(250);
  for(i=0;i<sizeof(sourceString);i++)                           //У�鴫�����ȷ��
  {
    if(sourceString[i]!=destString[i])
      error++;
  }
  
  if(error==0)                                                  //�����ͨ�����ڴ��䵽PC
  {
    uart1_send_string("{data=Correct!}\r\n");
    hal_wait(250);
    hal_wait(250);
    uart1_send_string(destString);                               //������Ŀ���ַ�����
  }
  else
    uart1_send_string("{data=Error!}\r\n");
  
  hal_wait(250);
  hal_wait(250);
}
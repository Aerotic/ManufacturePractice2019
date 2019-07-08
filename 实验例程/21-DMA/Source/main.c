/*********************************************************************************************
* �ļ���main.c
* ���ߣ�chennian 2017.11.2
* ˵����DMAʵ���߼�����      
* ���ܣ�ͨ��DMAͨ��������A�����ݸ��Ƹ�����B
*       ��λ����ֱ���ʾ����ǰ�͸��ƺ�����A������B������
* �޸ģ�
*********************************************************************************************/

/*********************************************************************************************
* ͷ�ļ�
*********************************************************************************************/
#include "delay.h"
#include "string.h"
#include "led.h"
#include "usart.h"
#include "DMA.h"
#include "key.h"

/*********************************************************************************************
* ����:main()
* ����:
* ����:��
* ����:��
* �޸�:
* ע��:
*********************************************************************************************/
void main(void)
{
  char A[]={'h','e','l','l','o',',','w','o','r','d'};
  char B[10]={'H','E','L','L','O',',','W','O','R','D'};
  int error=0;                                                  //�������
  
  usart_init(115200);                                           //���ڳ�ʼ��
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);               //����ϵͳ�ж����ȼ�����
  key_init();                                                   //������ʼ��
  
  printf("Hello IOT!\r\n\r\n");                                     //���������Ϣ 
  usart_send("Usart is ready!\r\n",strlen("Usart is ready!\r\n"));  //���ڴ�ӡ����ʾ��Ϣ
  printf("\r\n");                                               //���ڴ�ӡ����
  
  DMA_Config(DMA2_Stream7,DMA_Channel_4,(u32)A,(u32)B,SEND_BUF_SIZE);//DMA2����
  
  printf("DMAִ��ǰ:\r\n");                                      //���ڴ�ӡ 
  printf("����A��%s\r\n",A);                                     //���ڴ�ӡ����A
  printf("����B��%s\r\n",B);                                     //���ڴ�ӡ����B
  
  for(;;){
    if(get_key_status()==K3_PREESED){                           //�Ƿ��а������� 
      delay_count(500);                                         //��ʱ����                            
      if(get_key_status()==K3_PREESED){                         //�Ƿ��а�������
        while(get_key_status()==K3_PREESED);                    //�ȴ������ſ�
        printf("\r\nDMAִ�к�:\r\n");                           //���ڴ�ӡ
        
        DMA_Enable(DMA2_Stream7,SEND_BUF_SIZE);                 //����һ��DMA����
        
        while(1){                                               //�ȴ�DMA2_Stream7�������
          if(DMA_GetFlagStatus(DMA2_Stream7,DMA_FLAG_TCIF7)!=RESET){ 
            DMA_ClearFlag(DMA2_Stream7,DMA_FLAG_TCIF7);         //���DMA2_Stream7������ɱ�־
            break; 
          }
        }
        printf("����B��%s  \r\n",B);                               //���ڴ�ӡ
        
        for(int j=0;j<10;j++){                                  //У�鸴�ƽ��
          if(A[j]!=B[j])
            error++;                                              
        }
        printf("error=%d\r\n\r\n",error);                       //���ڴ�ӡ������
      }
    }
    delay_count(10000);                                         //��ʱ     
  }
}
/*********************************************************************************************
* �ļ���main.c
* ���ߣ�chennian 2017.11.20
* ˵�����ⲿflash��д����
* �޸ģ�zhoucj   2017.12.19 ��Ӱ���д�����ݹ��ܣ��޸����flashҺ���������BUG
* ע�ͣ�
*
*********************************************************************************************/
/*********************************************************************************************
* ͷ�ļ�
*********************************************************************************************/
#include "delay.h"
#include "string.h"
#include "w25qxx.h"
#include "led.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
/*********************************************************************************************
* ȫ�ֱ���
*********************************************************************************************/
unsigned int start_addr = 1;                                    //��ʼλ��
unsigned char write[] = "Hello IOT!\r\n";                       //Ҫд�������
unsigned char  read[10];                                        //��ȡ���ݻ�����

/*********************************************************************************************
* ����:main()
* ����:��������flash��д
* ����:��
* ����:��
* �޸�:
* ע��:
*********************************************************************************************/
void main(void) 
{
  led_init();                                                   //LED��ʼ��
  key_init();                                                   //������ʼ��
  delay_init(168);                                              //��ʱ��ʼ��
  usart_init(115200);                                           //��ʼ��
  W25QXX_Init();                                                //�ⲿFLASH��ʼ��
  turn_off(D3);                                                 //�ر�D3 
  turn_off(D4);                                                 //�ر�D4 
  lcd_init(FLASH1);
  
  
  //��Ҫд�������д��100��ַ����������ʼ��ַ��ʼд��
  W25QXX_Write(write,start_addr,strlen((char const *)write));
  
  for(;;){  
    u16 flash_ID=0;                                             //�洢flash ID
    char str[5]={0};                                             
    delay_ms(1000);                                             //��ʱ
    
    if(get_key_status() == (K3_PREESED|K4_PREESED)){            //���K3K4ͬʱ������
      delay_ms(100);                                            //��ʱ����
      if(get_key_status()==(K3_PREESED|K4_PREESED)){            //���K3K4ͬʱ����
        LCDDrawAsciiDot8x16(86, 166,"flash erasing", 0x0000, 0xffff);
        
        W25QXX_Erase_Chip();                                    //��������flash
        LCD_Clear(85,166,319,211,0xffff);                       //lcd���
        LCDDrawAsciiDot8x16(86, 166,"flash erased", 0x0000, 0xffff);
        delay_ms(1000);
      }
    }
    if(get_key_status() == (K1_PREESED|K2_PREESED)){            //���K1K2ͬʱ������
      delay_ms(100);                                            //��ʱ����
      if(get_key_status()==(K1_PREESED|K2_PREESED)){            //���K1K2ͬʱ����
        LCDDrawAsciiDot8x16(86, 166,"flash writing", 0x0000, 0xffff);
        delay_ms(1000);
        W25QXX_Write(write,start_addr,strlen((char const *)write));//д������
        LCD_Clear(85,166,319,211,0xffff);                       //lcd���
        LCDDrawAsciiDot8x16(86, 166,"flash wrote", 0x0000, 0xffff);
        delay_ms(1000);
      }
    }
    turn_on(D3);                                                //����D3��
    turn_on(D4);                                                //����D4��
    W25QXX_Read(read,start_addr,strlen((char const *)write));   //�ӵ���������ʵ��ַ��ʼ��ȡ���ݣ���ȡ����Ϊд�����ݵĳ���
    printf((char*)read);                                        //��ӡflash����
    flash_ID=W25QXX_ReadID();                                   //��ȡflash ID
    sprintf(str,"flash_ID:%d \r\n",flash_ID);                   //��flash_ID ת��Ϊ�ַ����洢��str������
    printf((char*)str);                                         //��ӡflash ID��PC
    
    //��ʾ����������
    LCD_Clear(85,132,319,211,0xffff);                           //��Ļ���
    LCDDrawAsciiDot8x16(86, 132,str, 0x0000, 0xffff);           //��ʾflash ID
    LCDDrawAsciiDot8x16(86, 149,read, 0x0000, 0xffff);          //��ʾflash����
    
    memset((char*)read,0,sizeof(write));                        //��ն�ȡ������
    delay_ms(200);                                              //�Լ���ʱ���õ�D3��D4��˸Ч��
    turn_off(D3);                                               //Ϩ��D3��
    turn_off(D4);                                               //Ϩ��D4��
  }
}

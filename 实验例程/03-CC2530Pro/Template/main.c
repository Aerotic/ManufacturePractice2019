#include <ioCC2530.h>         //����CC2530����Ӧ��ͷ�ļ���������SFR�Ķ��壩

#define D7    P1_0              //����D7ΪP1_0�ڿ���
#define D6    P1_1              //����D6ΪP1_1�ڿ���

void led_init(void);
void led_test(void);
void halWait(unsigned char wait);

/*������
-------------------------------------------------------*/
void main(void)
{
  led_init();
  
  while(1)
  {
    led_test();
  }
}

/*led��ʼ��
-------------------------------------------------------*/
void led_init(void)
{
  P1SEL &= ~0x03;          //P1.0 P1.1Ϊ��ͨ I/O ��
  P1DIR |= 0x03;           //���
  
  D7 = 1;                  //��LED
  D6 = 1;
}

/*led��˸����
-------------------------------------------------------*/
void led_test(void)
{
  D7 = 0;              //D7��˸
  halWait(250);
  D7 = 1;
  halWait(250);
  
  D6 = 0;              //D6��˸
  halWait(250);
  D6 = 1;
  halWait(250);
}

/*��ʱ����
-------------------------------------------------------*/
void halWait(unsigned char wait)
{
  unsigned long largeWait;

  if(wait == 0)
  {return;}
  largeWait = ((unsigned short) (wait << 7));
  largeWait += 114*wait;

  largeWait = (largeWait >> ( CLKCONCMD & 0x07 ));
  while(largeWait--);

  return;
}

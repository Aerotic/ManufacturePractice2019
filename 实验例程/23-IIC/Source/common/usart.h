#ifndef __USART_H
#define __USART_H
#include "stdio.h"
#include <string.h>
#include "stm32f4xx.h"

	
#define USART_REC_MAX 			200  	                        //�����������ֽ��� 200
extern unsigned char Usart_len;                              //��������ǰ���ݳ���
extern unsigned char  USART_RX_BUF[USART_REC_MAX];           //���ջ����� 
extern void usart_init(unsigned int bound);
extern void clean_usart(void);
extern void usart_send(unsigned char *s,unsigned char len);
#endif




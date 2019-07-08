/***********************************************************
* �ļ�: lcdshow.c
* ����:����LCD����ʾ��� 
* ����: liding   2015-9-30
***********************************************************/


#include "lcddis.h"
#include "delay.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "stm32f4xx.h"
int flag1,flag2;
char result1[20],result2[20],result3[20];
/***********************************************************
* ����: border
* ����: ���߿�
* ����: ��
* ����: ��
* �޸�:
* ע��: 
***********************************************************/
void border(){
  int i=10,j=10;
  for(j=i;j<310;j++)     
      LCDDrawPixel(j, i, 0x0000);    //top1
  for(j=i;j<230;j++)
      LCDDrawPixel(i,j , 0x0000);   //left1
  for(j=i;j<230;j++)
      LCDDrawPixel(310,j , 0x0000); //right1
  for(j=i;j<310;j++)
      LCDDrawPixel(j,230 , 0x0000);//bottom1
  
  for(j=i+5;j<305;j++)
      LCDDrawPixel(j, i+5, 0x0000); //top2
  for(j=i+5;j<225;j++)
      LCDDrawPixel(i+5,j , 0x0000);//left2
  for(j=i+5;j<225;j++)
      LCDDrawPixel(305, j, 0x0000);//right2
  for(j=i+5;j<305;j++)
      LCDDrawPixel(j, 225, 0x0000);//bottm2
}
/***********************************************************
* ����: Draw_rect
* ����: ������
* ����: ���Ͻǵ㣬���½ǵ㣬������ɫ
* ����: ��
* �޸�:
* ע��: 
***********************************************************/
void Draw_rect(int x0, int y0,int x1,int y1,int color){
  int temp_x=x0,temp_y=y0;
  while(x0<x1){  
    LCDDrawPixel(x0,y0,color);
    x0++;
  }
  while(y0<y1){
    LCDDrawPixel(x0,y0,color);
    y0++;
  }
  while(x1>temp_x){
    LCDDrawPixel(x1,y1,color);
    x1--;
  }
  while(y1>=temp_y){
    LCDDrawPixel(x1,y1,color);
    y1--;
  }
}
/***********************************************************
* ����: Draw_rect
* ����: ������
* ����: ���Ͻǵ㣬���½ǵ㣬������ɫ
* ����: ��
* �޸�:
* ע��: 
***********************************************************/
void Draw_rectRGB(int x0, int y0,int x1,int y1,s32 color){
  int temp_x=x0,temp_y=y0;
  while(x0<x1){  
    LCDDrawPixel(x0,y0,toRGBShow(color));
    x0++;
  }
  while(y0<y1){
    LCDDrawPixel(x0,y0,toRGBShow(color));
    y0++;
  }
  while(x1>temp_x){
    LCDDrawPixel(x1,y1,toRGBShow(color));
    x1--;
  }
  while(y1>=temp_y){
    LCDDrawPixel(x1,y1,toRGBShow(color));
    y1--;
  }
}
/***********************************************************
* ����: toRGBShow
* ����: ����д��RGB��ʽ��24λ����ɫ�����ӱ���֧�֣�ת��Ϊ����֧�ֵ�16λ��ɫ
* ����: Ҫת����RGB��ɫ
* ����: ת����ɵ�16λ��ɫֵ
* �޸�:
* ע��: 
***********************************************************/
u16 toRGBShow(s32 color){
  u8 R_t,G_t,B_t,R,G,B;
  u16 RGB=0;
  
  B_t=color;
  G_t=color>>8;
  R_t=color>>16;
  
  B=(u8)(31/(255.0/B_t));
  G=(u8)(63/(255.0/G_t));
  R=(u8)(31/(255.0/R_t));
  
  RGB |=R;
  RGB =RGB<<6;
  RGB |=G;
  RGB =RGB<<5;
  RGB |=B;                                    //�������RGB��ɫת��Ϊ��Ļ֧�ֵ�16λɫ
  
  return RGB;
}
/***********************************************************
* ����: LCDShowFnt
* ����: ��ʾ���֣�����Ӣ�ģ�
* ����: x,y:��ʾ������꣬text:Ҫ��ʾ�����ݣ�fnt_color:������ɫ��bg_color:������ɫ��type����ʾ�ķ�ʽ��16x16/24x24��
* ����: ��
* �޸�:
* ע��: ������Ϊ�������ֺͱ�����ɫֵΪ������RGBģʽ�����ϰ����RGBģʽ
        ��������ñ���������eg. ��ɫ �������������ɫ���� #FF0000      ��������ֱ��ʹ��16��������    0xFF0000��
***********************************************************/
void LCDShowFnt(int x,int y,char* text,u32 fnt_color,s32 bg_color,int type){
 // u8 R_t,G_t,B_t,R,G,B;
  
  u16 RGB=0,BG_RGB=-1;
  
  RGB=toRGBShow(fnt_color);
  if(bg_color>=0){
    BG_RGB=toRGBShow(bg_color);
  }
  
//  if(!type)
//    LCDDrawFnt16(x,y,text,RGB,BG_RGB);              //16x16��ʽ��ʾ
//  else{
//    LCDDrawFnt24(x, y, text, RGB, BG_RGB);          //24x24��ʽ��ʾ
//  }
}
/***********************************************************
* ����: Draw_itaLine
* ����: ��б��
* ����: б�ߵ������յ㣬������ɫ
* ����: ��
* �޸�:
* ע��: 
***********************************************************/
void Draw_itaLine(int x0,int y0,int x1,int y1,int color){
  float k=0,b=0;
  int y=0;
  k=(float)(y1-y0)/(x1-x0);
  b=y1-k*x1;
  if(x0<x1){
    for(int i=x0;i<x1;i++){
      y=(int)(k*i+b);
      LCDDrawPixel(i,y,color);   //�����ص�
    }
  }else{
      for(int i=x1;i<x0;i++){
      y=(int)(k*i+b);
      LCDDrawPixel(i,y,color);  //�����ص�
    }
  }
}
/***********************************************************
* ����: Draw_five
* ����: ������ǻ������
* ����: ������㣬���ߵ���ɫ
* ����: ��
* �޸�:                                 (4)
* ע��: ����ǵĻ���ʹ�õ���             *
                                        * *
                               (1) * * *   * * * (2)
                                     *       *
                                      *     *
                                     *   *  *
                                (3) * *    * *(5)
���������˳��Ϊ��1-->2-->3-->4-->5�����������ֻ��ı�����Ĵ���˳Ϊ��1-->4-->2-->5-->3��
***********************************************************/
void Draw_five(int x0, int y0,int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,int color){
  Draw_itaLine(x0,y0,x1,y1,color);
  Draw_itaLine(x1,y1,x2,y2,color);
  Draw_itaLine(x2,y2,x3,y3,color);
  Draw_itaLine(x3,y3,x4,y4,color);
  Draw_itaLine(x4,y4,x0,y0,color);  
}

/***********************************************************
* ����: Draw_itaLine_RGB
* ����: ��б��
* ����: б�ߵ������յ㣬������ɫ
* ����: ��
* �޸�:
* ע��: ������Ϊ����������ɫֵΪ������RGBģʽ�����ϰ����RGBģʽ
        ��������ñ���������eg. ��ɫ �������������ɫ���� #FF0000      ��������ֱ��ʹ��16��������    0xFF0000��
***********************************************************/
void Draw_itaLine_RGB(int x0,int y0,int x1,int y1,s32 color){
  float k=0,b=0;
  int y=0;
  k=(float)(y1-y0)/(x1-x0);
  b=y1-k*x1;
  if(x0<x1){
    for(int i=x0;i<x1;i++){
      y=(int)(k*i+b);
      LCDDrawPixel(i,y,toRGBShow(color));   //�����ص�
    }
  }else{
      for(int i=x1;i<x0;i++){
      y=(int)(k*i+b);
      LCDDrawPixel(i,y,toRGBShow(color));  //�����ص�
    }
  }
}
/***********************************************************
* ����: Draw_five_RGB
* ����: ������ǻ������
* ����: ������㣬���ߵ���ɫ
* ����: ��
* �޸�:                                 (4)
* ע��: ����ǵĻ���ʹ�õ���             *
                                        * *
                               (1) * * *   * * * (2)
                                     *       *
                                      *     *
                                     *   *  *
                                (3) * *    * *(5)
���������˳��Ϊ��1-->2-->3-->4-->5�����������ֻ��ı�����Ĵ���˳Ϊ��1-->4-->2-->5-->3��

��ɫֵΪ������RGBģʽ�����ϰ����RGBģʽ��������ñ���������eg. ��ɫ �������������ɫ���� #FF0000      ��������ֱ��ʹ��16��������    0xFF0000��
***********************************************************/
void Draw_five_RGB(int x0, int y0,int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,s32 color){
  Draw_itaLine_RGB(x0,y0,x1,y1,color);
  Draw_itaLine_RGB(x1,y1,x2,y2,color);
  Draw_itaLine_RGB(x2,y2,x3,y3,color);
  Draw_itaLine_RGB(x3,y3,x4,y4,color);
  Draw_itaLine_RGB(x4,y4,x0,y0,color);  
}
/***********************************************************
* ����: Draw_four_RGB
* ����: ���ı���
* ����: �ĸ����㣬���ߵ���ɫ
* ����: ��
* �޸�:                                 
* ע��:      (1)*  *   *  *  *  *(2)
                *               *
                *               *
             (4)*  *   *  *  *  *(3)

�������ݰ�  
            ������
           ��   ��
            ������
��ͼ����ʽ���ݵõ��ľ����ı��β����Ǵӣ�1����ʼ���Ǵӣ�2����ʼ

��ɫֵΪ������RGBģʽ�����ϰ����RGBģʽ��������ñ���������eg. ��ɫ �������������ɫ���� #FF0000      ��������ֱ��ʹ��16��������    0xFF0000��
***********************************************************/
void Draw_four_RGB(int x0, int y0,int x1,int y1,int x2,int y2,int x3,int y3,s32 color){
  Draw_five_RGB(x0,y0,x1,y1,x2,y2,x3,y3,x3,y3,color);
}
/***********************************************************
* ����: Draw_three_RGB
* ����: ��������
* ����: �������㣬���ߵ���ɫ
* ����: ��
* �޸�:                              
* ע��:         

��ɫֵΪ������RGBģʽ�����ϰ����RGBģʽ��������ñ���������eg. ��ɫ �������������ɫ���� #FF0000      ��������ֱ��ʹ��16��������    0xFF0000��
***********************************************************/
void Draw_three_RGB(int x0, int y0,int x1,int y1,int x2,int y2,s32 color){
  Draw_four_RGB(x0,y0,x1,y1,x2,y2,x2,y2,color);
}
/***********************************************************
* ����: ShowLCD
* ����: ��ʾʵ����Ϣ
* ����: SensorName������������  Result��ʵ�������������  level��ʵ���Ѷȵȼ�
* ����: ��
* �޸�:
* ע��: 
***********************************************************/
void ShowLCD(char* SensorName,float Result,float level){
//  LCDDrawFnt16(30, 40, "Experiment:", 0x0000, -1);
//  LCDDrawFnt16(30, 70, "level:", 0x0000, -1);
//  LCDDrawFnt16(30, 100, "Key Point:", 0x0000, -1);
//  LCDDrawFnt16(30, 130, "Result:", 0x0000, -1);

  switch((int)Result){
    case 0: 
          Setlevel(level);
          ShowResult_1(SensorName);
      break;
    case 1: 
          Setlevel(level);
          ShowResult_2(SensorName);
      break;
      
    case 2:
          Setlevel(level);
          ShowResult_3(SensorName);
      break;
    case 3:
          Setlevel(level);
          //ShowResult_0(SensorName);
      break;
  }

}
/***********************************************************
* ����: Setlevel
* ����: ���õȼ�
* ����:   level��ʵ���Ѷȵȼ�
* ����: ��
* �޸�:
* ע��: 
***********************************************************/

void Setlevel(float level){
//  if(level==ONE)
//     LCDDrawFnt16(130, 70, "��", 0x0000, -1);
//  else if(level==ONE_HALF)
//     LCDDrawFnt16(130, 70, "���", 0x0000, -1);
//  else if(level==TWO)
//     LCDDrawFnt16(130, 70, "���", 0x0000, -1);
//  else if(level==TWO_HALF)
//     LCDDrawFnt16(130, 70, "����", 0x0000, -1);
//  else if(level==THREE)
//     LCDDrawFnt16(130, 70, "����", 0x0000, -1);
//  else if(level==NONE)
//     LCDDrawFnt16(130, 70, "��", 0x0000, -1);
}
/***********************************************************
* ����: ShowResult_2
* ����: ��ʾʵ����
* ����: SensorName������������  
* ����: ��
* �޸�:
* ע��: 
***********************************************************/
void ShowResult_2(char* SensorName){
  
  if(!strcmp(SensorName,"RFID"))
  {
//    LCDDrawFnt16(130, 40, SensorName, 0x0000, -1);
//    LCDDrawFnt16(130, 100, "SPI Used", 0x0000, -1);
//    LCDDrawFnt16(130, 130, result1, 0x0000, -1);
//    LCDDrawFnt16(130, 160, result2, 0x0000, -1);
  }
  if(!strcmp(SensorName,"HumiTemp"))
  {
//    LCDDrawFnt16(130, 40, SensorName, 0x0000, -1);
//    LCDDrawFnt16(130, 100, "DH11 module", 0x0000, -1);
//    LCDDrawFnt16(130, 130, result1, 0x0000, -1);
//    LCDDrawFnt16(130, 160, result2, 0x0000, -1);
  }
}

/***********************************************************
* ����: ShowResult_3
* ����: ��ʾʵ����
* ����: SensorName������������  
* ����: ��
* �޸�:
* ע��: 
***********************************************************/
void ShowResult_3(char* SensorName){
  
  if(!strcmp(SensorName,"Acceleration"))
  {
//    LCDDrawFnt16(130, 40, SensorName, 0x0000, -1);
//    LCDDrawFnt16(130, 100, "IIC Used", 0x0000, -1);
//    LCDDrawFnt16(130, 130, result1, 0x0000, -1);
//    LCDDrawFnt16(130, 160, result2, 0x0000, -1);
//    LCDDrawFnt16(130, 190, result3, 0x0000, -1);
  }
}
/***********************************************************
* ����: ShowResult_1
* ����: ��ʾʵ����
* ����: SensorName������������  
* ����: ��
* �޸�:
* ע��: 
***********************************************************/
void ShowResult_1(char* SensorName){
//  if(!strcmp(SensorName,"Photoresistance"))
//  {
//    LCDDrawFnt16(130, 40, SensorName, 0x0000, -1);
//    LCDDrawFnt16(130, 100, "ADC Transformation", 0x0000, -1);
//    LCDDrawFnt16(130, 130, result1, 0x0000, -1);
//  }
//  else if(!strcmp(SensorName,"Rain"))
//  {
//    LCDDrawFnt16(130, 40, SensorName, 0x0000, -1);
//    LCDDrawFnt16(130, 100, "ADC Transformation", 0x0000, -1);
//    LCDDrawFnt16(130, 130, result1, 0x0000, -1);
//  }
//  else  if(!strcmp(SensorName,"Flame"))
//  {
//    LCDDrawFnt16(130, 40, SensorName, 0x0000, -1);
//    LCDDrawFnt16(130, 100, "GPIO Check", 0x0000, -1);
//    LCDDrawFnt16(130, 130, result1, 0x0000, -1);
//  }
//  else  if(!strcmp(SensorName,"Relay"))
//  {
//    LCDDrawFnt16(130, 40, SensorName, 0x0000, -1);
//    LCDDrawFnt16(130, 100, "GPIO Contrl", 0x0000, -1);
//    LCDDrawFnt16(130, 130, result1, 0x0000, -1);
//  }
//  else  if(!strcmp(SensorName,"Hall"))
//  {
//    LCDDrawFnt16(130, 40, SensorName, 0x0000, -1);
//    LCDDrawFnt16(130, 100, "GPIO Check", 0x0000, -1);
//    LCDDrawFnt16(130, 130, result1, 0x0000, -1);
//  }
//  else  if(!strcmp(SensorName,"Ultrasonic"))
//  {
//    LCDDrawFnt16(130, 40, SensorName, 0x0000, -1);
//    LCDDrawFnt16(130, 100, "GPIO Contrl", 0x0000, -1);
//    LCDDrawFnt16(130, 130, result1, 0x0000, -1);
//  }
//  else  if(!strcmp(SensorName,"Infrared"))
//  {
//    LCDDrawFnt16(130, 40, SensorName, 0x0000, -1);
//    LCDDrawFnt16(130, 100, "GPIO Check", 0x0000, -1);
//    LCDDrawFnt16(130, 130, result1, 0x0000, -1);
//  }
//  else  if(!strcmp(SensorName,"CombustibleGas"))
//  {
//    LCDDrawFnt16(130, 40, SensorName, 0x0000, -1);
//    LCDDrawFnt16(130, 100, "ADC Transformation", 0x0000, -1);
//    LCDDrawFnt16(130, 130, result1, 0x0000, -1);
//  }
//  else  if(!strcmp(SensorName,"AlcoholGas"))
//  {
//    LCDDrawFnt16(130, 40, SensorName, 0x0000, -1);
//    LCDDrawFnt16(130, 100, "ADC Transformation", 0x0000, -1);
//    LCDDrawFnt16(130, 130, result1, 0x0000, -1);
//  }
//  else  if(!strcmp(SensorName,"AirGas"))
//  {
//    LCDDrawFnt16(130, 40, SensorName, 0x0000, -1);
//    LCDDrawFnt16(130, 100, "ADC Transformation", 0x0000, -1);
//    LCDDrawFnt16(130, 130, result1, 0x0000, -1);
//  }
//  else  if(!strcmp(SensorName,"Acceleration"))
//  {
//    LCDDrawFnt16(130, 40, SensorName, 0x0000, -1);
//    LCDDrawFnt16(130, 100, "IIC", 0x0000, -1);
//    LCDDrawFnt16(130, 130, result1, 0x0000, -1);
//  }
}
///***********************************************************
//* ����: ShowResult_0
//* ����: ��ʾʵ����
//* ����: SensorName��ʵ������  
//* ����: ��
//* �޸�:
//* ע��: 
//***********************************************************/
void ShowResult_0(char* SensorName){}
// void ShowResult_0(char* SensorName)
// {
//  if(!strcmp(SensorName,"KEY")){
//    //LCDDrawFnt16(30, 40, "Experiment:", 0x0000, -1);
//    LCDDrawFnt16(130, 40, SensorName, 0x0000, -1);
//    LCDDrawFnt16(130, 100, "KEY Used", 0x0000, -1);
//    LCDDrawFnt16(130, 130, result1, 0x0000, -1);
//  }else  if(!strcmp(SensorName,"Timer"))
//  {
//    LCDDrawFnt16(130, 40, SensorName, 0x0000, -1);
//    LCDDrawFnt16(130, 100, "Timer", 0x0000, -1);
//    LCDDrawFnt16(130, 130, result1, 0x0000, -1);
//  }else  if(!strcmp(SensorName,"Exti"))
//  {
//    LCDDrawFnt16(130, 40, SensorName, 0x0000, -1);
//    LCDDrawFnt16(130, 100, "Exti", 0x0000, -1);
//    LCDDrawFnt16(130, 130, result1, 0x0000, -1);
//    LCDDrawFnt16(130, 160, result2, 0x0000, -1);
//  }else  if(!strcmp(SensorName,"Iwdg"))
//  {
//    LCDDrawFnt16(130, 40, SensorName, 0x0000, -1);
//    LCDDrawFnt16(130, 100, "Iwdg", 0x0000, -1);
//    LCDDrawFnt16(130, 130, result1, 0x0000, -1);
//  }else  if(!strcmp(SensorName,"Usart"))
//  {
//    LCDDrawFnt16(130, 40, SensorName, 0x0000, -1);
//    LCDDrawFnt16(130, 100, "Usart", 0x0000, -1);
//    LCDDrawFnt16(130, 130, result1, 0x0000, -1);
//  }else  if(!strcmp(SensorName,"ADC"))
//  {
//    LCDDrawFnt16(130, 40, SensorName, 0x0000, -1);
//    LCDDrawFnt16(130, 100, "ADC Transformation", 0x0000, -1);
//    LCDDrawFnt16(130, 130, result1, 0x0000, -1);
//  }else  if(!strcmp(SensorName,"Flash"))
//  {
//    LCDDrawFnt16(130, 40, SensorName, 0x0000, -1);
//    LCDDrawFnt16(130, 100, "Flash", 0x0000, -1);
//    LCDDrawFnt16(130, 130, result1, 0x0000, -1);
//  }else  if(!strcmp(SensorName,"LCD"))
//  {
//    LCDDrawFnt16(130, 40, SensorName, 0x0000, -1);
//    LCDDrawFnt16(130, 100, "LCD", 0x0000, -1);
//    LCDDrawFnt16(130, 130, result1, 0x0000, -1);
//  }
//}
/***********************************************************
* ����: SetRusult1
* ����: ������ʾ���
* ����: ��  
* ����: ��
* �޸�:
* ע��: 
***********************************************************/
void SetResult1(){

  if(flag2){
   sprintf(result1,"k4 press");
    //printf(result1);
   flag2=0;
  }
  else if(flag1){
    sprintf(result1,"K3 press");
    flag1=0;
    //printf(result1);
  }else{
    sprintf(result1,"No key press");
 }
 ShowResult_0("Exti");
}
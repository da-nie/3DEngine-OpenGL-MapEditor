#ifndef GDI_H
#define GDI_H
 
#include <math.h>
 
//*************************************************************************************************************************
//������ ������ � ����� ����������� ����� 
//*************************************************************************************************************************
//����������� �������
void ClearVideoBuffer(void);//�������� ����
void PutPixel(int x,int y,unsigned char r,unsigned char g,unsigned char b);//��������� �����
void DrawLine(int x1,int y1,int x2,int y2,unsigned char r,unsigned char g,unsigned char b);//���������� �����
void Circle(int xc,int yc,int radius,unsigned char R,unsigned char G,unsigned char B);//���������� ����������� ����������
//------------------------------------------------------------------------------
#endif

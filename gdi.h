#ifndef GDI_H
#define GDI_H
 
#include <math.h>
 
//*************************************************************************************************************************
//Модуль работы с полем отображения карты 
//*************************************************************************************************************************
//Графические функции
void ClearVideoBuffer(void);//очистить поле
void PutPixel(int x,int y,unsigned char r,unsigned char g,unsigned char b);//поставить точку
void DrawLine(int x1,int y1,int x2,int y2,unsigned char r,unsigned char g,unsigned char b);//нарисовать линию
void Circle(int xc,int yc,int radius,unsigned char R,unsigned char G,unsigned char B);//нарисовать закрашенную окружность
//------------------------------------------------------------------------------
#endif

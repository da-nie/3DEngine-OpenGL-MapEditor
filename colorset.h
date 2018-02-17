#ifndef COLORSET_H
#define COLORSET_H
 
#include <windows.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "resource.h"
 
//*************************************************************************************************************************
//����� ������ ��� ������ �����
//*************************************************************************************************************************
class COLORSET
{
 public:
  COLORREF CustColor[16];
  COLORREF clr;
  CHOOSECOLOR cc;
  void Create(long Style,HWND hWnd,HINSTANCE hInstance);
  int Activate(unsigned char *R,unsigned char *G,unsigned char *B);
  void SetCustColor(int number,unsigned char R,unsigned char G,unsigned char B);
};
#endif
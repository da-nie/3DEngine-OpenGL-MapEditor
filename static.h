#ifndef STATIC_H
#define STATIC_H

#include <windows.h>

//*************************************************************************************************************************
//����� ��� ������ �� ��������� ��������
//*************************************************************************************************************************
class STATIC
{
 public:
  HWND Handle;
  void Create(int x,int y,int cx,int cy,char *Text,long Style,HWND hWnd,HINSTANCE hInstance);
  void SetText(char *Text);
};
#endif
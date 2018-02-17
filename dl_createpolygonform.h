#ifndef DL_CREATEPOLYGONFORM_H
#define DL_CREATEPOLYGONFORM_H

#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "resource.h"

#include "common.h"
#include "dl_createsegmentform.h"

//------------------------------------------------------------------------------
LONG WINAPI CREATEPOLYGONFORM_dlgProc(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam);
//------------------------------------------------------------------------------
class CREATEPOLYGONFORM
{
 public:
  //-----------------------------------------------------------
  HWND hDlg;
  //-----------------------------------------------------------
  HWND hEdit_Radius;
  HWND hEdit_Vertex;
  HWND hEdit_Angle;
  HWND hCheckBox_Vector;
  //-----------------------------------------------------------
  int Angle;
  int Radius;
  int Vertex;
  int X_Pos;
  int Y_Pos;
  //-----------------------------------------------------------
  CREATEPOLYGONFORM(void);
  //-----------------------------------------------------------
  void InitDialog(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void Command(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  //-----------------------------------------------------------
  void Initialize(void);//инициализация структур
  void Activate(int x,int y);//запуск диалога
  //-----------------------------------------------------------
};
#endif
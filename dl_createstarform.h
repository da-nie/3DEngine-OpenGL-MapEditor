#ifndef DL_CREATESTARTFORM_H
#define DL_CREATESTARTFORM_H

#include <windows.h>
#include "common.h"
#include "dl_createsegmentform.h"

//------------------------------------------------------------------------------
LONG WINAPI CREATESTARFORM_dlgProc(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam);
//------------------------------------------------------------------------------
class CDialog_CreateStar
{
 public:
  //-----------------------------------------------------------
  HWND hDlg;
  //-----------------------------------------------------------
  HWND hEdit_RadiusUp;
  HWND hEdit_RadiusDown;
  HWND hEdit_Vertex;
  HWND hEdit_Angle;
  HWND hCheckBox_Vector;
  //-----------------------------------------------------------
  int Angle;
  int RadiusUp;
  int RadiusDown;
  int Vertex;
  int X_Pos;
  int Y_Pos;
  //-----------------------------------------------------------
  CDialog_CreateStar(void);
  //-----------------------------------------------------------
  void InitDialog(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void Command(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  //-----------------------------------------------------------
  void Initialize(void);//инициализация структур
  void Activate(int x,int y);//запуск диалога
  //-----------------------------------------------------------
};
#endif
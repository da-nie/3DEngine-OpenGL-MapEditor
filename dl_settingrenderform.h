#ifndef DL_SETTINGRENDERFORM_H
#define DL_SETTINGRENDERFORM_H

#include <windows.h>
#include "colorset.h"
#include "resource.h"
#include "common.h"

//------------------------------------------------------------------------------
LONG WINAPI SETTINGRENDERFORM_dlgProc(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam);
//------------------------------------------------------------------------------
class SETTINGRENDERFORM
{
 public:
  //-----------------------------------------------------------
  HWND hDlg;
  //-----------------------------------------------------------
  HWND hEdit_BlockSize;
  HWND hEdit_Constant;
  HWND hEdit_Linear;
  HWND hEdit_Quadric;
  HWND hEdit_FogDensity;
  HWND hCheckBox_FogEnable;
  COLORSET ColorSet;
  //-----------------------------------------------------------
  unsigned char A_R,A_G,A_B;
  unsigned char F_R,F_G,F_B;
  //-----------------------------------------------------------
  void InitDialog(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void Command(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void Paint(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  //-----------------------------------------------------------
  void Activate(void);//запуск диалога
  //-----------------------------------------------------------
};
#endif
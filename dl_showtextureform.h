#ifndef DL_SHOWTEXTUREFORM_H
#define DL_SHOWTEXTUREFORM_H

#include <windows.h>
#include "resource.h"
#include "common.h"

extern SKeyData sKeyData;//ключевая информация
extern HINSTANCE hProjectInstance;

//------------------------------------------------------------------------------
LONG WINAPI SHOWTEXTUREFORM_dlgProc(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam);
//------------------------------------------------------------------------------
class SHOWSTextureCWnd_Form
{
 public:
  //-----------------------------------------------------------
  HWND hDlg;
  //-----------------------------------------------------------
  HWND hStatic_Width;
  HWND hStatic_Height;
  HWND hScroll_Horizontal;
  HWND hScroll_Vertical;
  //-----------------------------------------------------------
  int TextureNo;
  int hPos;
  int vPos;
  int hPosMax;
  int vPosMax;
  //-----------------------------------------------------------
  void InitDialog(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void Command(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void Paint(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void HScroll(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void VScroll(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  //-----------------------------------------------------------
  void Activate(int texture,HWND hWnd);//запуск диалога
  //-----------------------------------------------------------
};

#endif
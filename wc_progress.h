#ifndef WC_CWnd_Progress_H
#define WC_CWnd_Progress_H

#include <windows.h>
#include "common.h"

//------------------------------------------------------------------------------
void CWnd_Progress_Register(void);
LONG WINAPI CWnd_Progress_wndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
//------------------------------------------------------------------------------
class CWnd_Progress
{
 public:
  //-----------------------------------------------------------
  HWND hWnd;
  //-----------------------------------------------------------
  float cWnd_Progress;
  //-----------------------------------------------------------
  //-----------------------------------------------------------
  void Create(HWND hWnds,WPARAM wParam,LPARAM lParam);
  void Paint(HWND hWnds,WPARAM wParam,LPARAM lParam);
  //-----------------------------------------------------------
  //-----------------------------------------------------------
};
#endif

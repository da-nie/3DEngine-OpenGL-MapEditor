#ifndef WC_PROGRESS_H
#define WC_PROGRESS_H

#include <windows.h>
#include "common.h"

//------------------------------------------------------------------------------
void PROGRESS_Register(void);
LONG WINAPI PROGRESS_wndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
//------------------------------------------------------------------------------
class PROGRESS
{
 public:
  //-----------------------------------------------------------
  HWND hWnd;
  //-----------------------------------------------------------
  float Progress;
  //-----------------------------------------------------------
  //-----------------------------------------------------------
  void Create(HWND hWnds,WPARAM wParam,LPARAM lParam);
  void Paint(HWND hWnds,WPARAM wParam,LPARAM lParam);
  //-----------------------------------------------------------
  //-----------------------------------------------------------
};
#endif

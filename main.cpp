#include <windows.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "resource.h"

#include <windows.h>
 
#include "common.h"
#include "wc_form.h"
#include "wc_menuform.h"
#include "wc_progress.h"

extern HINSTANCE hProjectInstance;
extern CWnd_Form cWnd_Form;
//------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevstance,LPSTR lpstrCmdLine,int nCmdShow)
{
 MSG msg;
 hProjectInstance=hInstance;
 FORM_Register();
 MENUFORM_Register();
 CWnd_Progress_Register();
 HMENU hMainMenu=LoadMenu(hProjectInstance,(LPSTR)IDM_MENU1);
 CreateWindow("cWnd_Form","Редактор карт V 1.0",WS_MINIMIZEBOX|WS_SYSMENU|WS_VISIBLE,0,0,800,560,0,hMainMenu,hProjectInstance,NULL);
 while(GetMessage(&msg,NULL,0,0))
 {
  TranslateMessage(&msg);
  DispatchMessage(&msg);
 }
 ClipCursor(NULL);
 ShowCursor(TRUE);
 return(msg.wParam);
}
 

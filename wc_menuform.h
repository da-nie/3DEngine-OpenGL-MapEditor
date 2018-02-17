#ifndef MENUFORM_H
#define MENUFORM_H


#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "static.h"
#include "common.h"

#define MENUFORM_MENU_CREATE_SSegment              2000
#define MENUFORM_MENU_CREATE_FRONTIER             2001
#define MENUFORM_MENU_CREATE_SECTOR               2002
#define MENUFORM_MENU_CREATE_SLighting             2003
#define MENUFORM_MENU_CREATE_STARTPOS             2004
#define MENUFORM_MENU_CREATE_FIGURE               2005
 
#define MENUFORM_MENU_DELETE_SSegment              2100
#define MENUFORM_MENU_DELETE_FRONTIER             2101
#define MENUFORM_MENU_DELETE_LINE                 2102
#define MENUFORM_MENU_DELETE_SECTOR               2103
#define MENUFORM_MENU_DELETE_SLighting             2104
 
#define MENUFORM_MENU_SECTOR_SIMPLYSECTOR         2200
#define MENUFORM_MENU_SECTOR_SIMPLYDOOR           2201
#define MENUFORM_MENU_SECTOR_DISPOSABLEDOOR       2202
#define MENUFORM_MENU_SECTOR_CLOSEDDOOR           2203
#define MENUFORM_MENU_SECTOR_AUTOCLOSEDDOOR       2204
#define MENUFORM_MENU_SECTOR_SIMPLYPLATCWnd_Form       2205
#define MENUFORM_MENU_SECTOR_INACTIVEPLATCWnd_Form     2206
#define MENUFORM_MENU_SECTOR_DISCONNECTEDPLATCWnd_Form 2207
#define MENUFORM_MENU_SECTOR_SIMPLYBRIDGE         2208
#define MENUFORM_MENU_SECTOR_SIMPLYTELEPORT       2209
 
#define MENUFORM_MENU_FIGURE_CORRECTPOLYGON       2300
#define MENUFORM_MENU_FIGURE_STAR                 2301
 
#define MENUFORM_MENU_MODIFYCATION_SSegment        2400
#define MENUFORM_MENU_MODIFYCATION_FRONTIER       2401
#define MENUFORM_MENU_MODIFYCATION_SECTOR         2402
#define MENUFORM_MENU_MODIFYCATION_SLighting       2403
//------------------------------------------------------------------------------
void MENUFORM_Register(void);
LONG WINAPI MENUFORM_wndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
//------------------------------------------------------------------------------
class CWnd_Menu
{
 public:
  //-----------------------------------------------------------
  HWND hWnd;
  //-----------------------------------------------------------
  CStatic Static_Text1;
  CStatic Static_Text2;
  CStatic Static_TextInfo[26];
  //-----------------------------------------------------------
  void Create(HWND hWnds,WPARAM wParam,LPARAM lParam);
  void Command(HWND hWnds,WPARAM wParam,LPARAM lParam);
  //-----------------------------------------------------------
  void UpDate(void);//обновление данных на панели
};

#endif

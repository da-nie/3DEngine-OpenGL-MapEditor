#ifndef MENUFORM_H
#define MENUFORM_H


#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "static.h"
#include "common.h"

#define MENUFORM_MENU_CREATE_SEGMENT              2000
#define MENUFORM_MENU_CREATE_FRONTIER             2001
#define MENUFORM_MENU_CREATE_SECTOR               2002
#define MENUFORM_MENU_CREATE_LIGHTING             2003
#define MENUFORM_MENU_CREATE_STARTPOS             2004
#define MENUFORM_MENU_CREATE_FIGURE               2005
 
#define MENUFORM_MENU_DELETE_SEGMENT              2100
#define MENUFORM_MENU_DELETE_FRONTIER             2101
#define MENUFORM_MENU_DELETE_LINE                 2102
#define MENUFORM_MENU_DELETE_SECTOR               2103
#define MENUFORM_MENU_DELETE_LIGHTING             2104
 
#define MENUFORM_MENU_SECTOR_SIMPLYSECTOR         2200
#define MENUFORM_MENU_SECTOR_SIMPLYDOOR           2201
#define MENUFORM_MENU_SECTOR_DISPOSABLEDOOR       2202
#define MENUFORM_MENU_SECTOR_CLOSEDDOOR           2203
#define MENUFORM_MENU_SECTOR_AUTOCLOSEDDOOR       2204
#define MENUFORM_MENU_SECTOR_SIMPLYPLATFORM       2205
#define MENUFORM_MENU_SECTOR_INACTIVEPLATFORM     2206
#define MENUFORM_MENU_SECTOR_DISCONNECTEDPLATFORM 2207
#define MENUFORM_MENU_SECTOR_SIMPLYBRIDGE         2208
#define MENUFORM_MENU_SECTOR_SIMPLYTELEPORT       2209
 
#define MENUFORM_MENU_FIGURE_CORRECTPOLYGON       2300
#define MENUFORM_MENU_FIGURE_STAR                 2301
 
#define MENUFORM_MENU_MODIFYCATION_SEGMENT        2400
#define MENUFORM_MENU_MODIFYCATION_FRONTIER       2401
#define MENUFORM_MENU_MODIFYCATION_SECTOR         2402
#define MENUFORM_MENU_MODIFYCATION_LIGHTING       2403
//------------------------------------------------------------------------------
void MENUFORM_Register(void);
LONG WINAPI MENUFORM_wndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
//------------------------------------------------------------------------------
class MENUFORM
{
 public:
  //-----------------------------------------------------------
  HWND hWnd;
  //-----------------------------------------------------------
  STATIC Static_Text1;
  STATIC Static_Text2;
  STATIC Static_TextInfo[26];
  //-----------------------------------------------------------
  void Create(HWND hWnds,WPARAM wParam,LPARAM lParam);
  void Command(HWND hWnds,WPARAM wParam,LPARAM lParam);
  //-----------------------------------------------------------
  void UpDate(void);//обновление данных на панели
};

#endif

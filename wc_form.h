#ifndef WC_FORM_H
#define WC_FORM_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "static.h"
#include "menu.h"
#include "button.h"
#include "fileprocess.h"
#include "common.h"
#include "gdi.h"
#include "wc_menuform.h"
#include "dl_createlightingform.h"
#include "dl_createsegmentform.h"
#include "dl_createsimplydoorform.h"
#include "dl_createsimplysectorform.h"
#include "dl_startposform.h"
#include "dl_createpolygonform.h"
#include "dl_createstarform.h"
#include "dl_settingrenderform.h"
#include "wc_progress.h"
#include "gdi.h"
#include "tga.h"
#include "render.h"


#define FORM_MENU_FILE_LOADMAP         1000
#define FORM_MENU_FILE_SAVEMAP         1001
#define FORM_MENU_FILE_CLEARMAP        1002
#define FORM_MENU_FILE_CREATESTAGE     1003
#define FORM_MENU_FILE_EXIT            1004
#define FORM_MENU_SETTING_VECTOR       1010
#define FORM_MENU_SETTING_SHOWSEGMENT  1011
#define FORM_MENU_SETTING_SHOWSECTOR   1012
#define FORM_MENU_SETTING_SHOWLIGHTING 1013
#define FORM_MENU_SETTING_RENDER       1014
 
#define FORM_BUTTON_RESET              1200
#define FORM_BUTTON_EXECUTE_DIALOG     1201
#define FORM_CHECKBOX_SHOWDIALOG       1202
//------------------------------------------------------------------------------
void FORM_Register(void);
LONG WINAPI FORM_wndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
//------------------------------------------------------------------------------
class FORM
{
 public:
  //-----------------------------------------------------------
  HWND hWnd;
  UINT OldTimer;
  //-----------------------------------------------------------
  HMENU hSettingMenu;
  //-----------------------------------------------------------
  STATIC Static_Form;
  STATIC Static_Text1;
  STATIC Static_Text2;
  STATIC Static_Text3;
  STATIC Static_Text4;
  BUTTON Button_Reset;
  BUTTON Button_ExecuteDialog;
  CHECKBOX CheckBox_ShowDialog;
  FILEPROCESSED FPRS;
  FILEPROCESSED FPRS_1;
  //-----------------------------------------------------------
  int xLeftMap;//левый угол
  int yTopMap;//верхний угол
  int MapMove;//1-режим движения карты;0-ничего
  int MouseX;//координаты мыши
  int MouseY;//координаты мыши
  int MouseXW;//координаты мыши в окне
  int MouseYW;//координаты мыши в окне
  int MouseXS;//координаты мыши на сетке
  int MouseYS;//координаты мыши на сетке
  int OldMouseX;//координаты фиксации мыши
  int OldMouseY;//координаты фиксации мыши
  //-----------------------------------------------------------
  void Create(HWND hWnds,WPARAM wParam,LPARAM lParam);
  void Destroy(HWND hWnds,WPARAM wParam,LPARAM lParam);
  void Paint(HWND hWnds,WPARAM wParam,LPARAM lParam);
  void RButtonDown(HWND hWnds,WPARAM wParam,LPARAM lParam);
  void RButtonUp(HWND hWnds,WPARAM wParam,LPARAM lParam);
  void MouseMove(HWND hWnds,WPARAM wParam,LPARAM lParam);
  void Timer(HWND hWnds,WPARAM wParam,LPARAM lParam);
  void LButtonUp(HWND hWnds,WPARAM wParam,LPARAM lParam);
  void Command(HWND hWnds,WPARAM wParam,LPARAM lParam);
  void KeyDown(HWND hWnds,WPARAM wParam,LPARAM lParam);
  //-----------------------------------------------------------
  //Функции меню File
  void SaveMap(char *FileName);
  void LoadMap(char *FileName);
  //-----------------------------------------------------------
  void Initialize(void);//инициализация редактора
  int PointPosition(float x,float y,float xw1,float yw1,float xw2,float yw2);//определяет положение точки относительно прямой
  int SectorGamber(void);//проверка сектора на выпуклость
  void GetSelectLine(int x,int y,int frontier);//устанавливает выбранную линию
  void GetSelectSector(int x,int y);//устанавливает выбранный сектор
  void GetSelectLighting(int x,int y);//устанавливает выбранный источник света
  void LoadTexture(char *FileName);//загружает набор текстур
  //-----------------------------------------------------------
};
#endif

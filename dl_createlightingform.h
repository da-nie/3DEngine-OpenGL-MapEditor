#ifndef DL_CREATELIGHTINGFORM_H
#define DL_CREATELIGHTINGFORM_H

#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "resource.h"

#include "colorset.h"
#include "common.h"
#include "formats.h"
#include "wc_menuform.h"
#include "gdi.h"

//------------------------------------------------------------------------------
struct LIGHTING
{
 int X;
 int Y;
 int Z;
 unsigned char R;
 unsigned char G;
 unsigned char B;
 int Mode;
 int TimeInterval;
 float Mode2_DarkTime;
 float Mode2_LightTime;
 float Mode2_MinimumLightLevel;
 float Mode3_MinimumLightLevel;
 float Mode3_CycleTime;
 float Mode4_OnTime;
 float Mode4_OffTime;
 float Mode4_MinimumLightLevel;
};
//------------------------------------------------------------------------------
LONG WINAPI CREATELIGHTINGFORM_dlgProc(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam);
//------------------------------------------------------------------------------
class CREATELIGHTINGFORM
{
 public:
  //-----------------------------------------------------------
  HWND hDlg;
  //-----------------------------------------------------------
  HWND hEdit_Height;
  HWND hEdit_Mode2_DarkTime;
  HWND hEdit_Mode2_LightTime;
  HWND hEdit_Mode2_MinimumLightLevel;
  HWND hEdit_Mode3_MinimumLightLevel;
  HWND hEdit_Mode3_CycleTime;
  HWND hEdit_Mode4_OnTime;
  HWND hEdit_Mode4_OffTime;
  HWND hEdit_Mode4_MinimumLightLevel;
  HWND hEdit_TimeInterval;
  HWND hRadioButton_Mode1;
  HWND hRadioButton_Mode2;
  HWND hRadioButton_Mode3;
  HWND hRadioButton_Mode4;
  COLORSET ColorSet;
  //-----------------------------------------------------------
  LIGHTING Lighting[1000];
  //-----------------------------------------------------------
  LIGHTING WorkingLighting;
  int SelectLighting;//источник света, с которым мы работаем
  int Flag;//0-создание источника света,1-его модификация
  //-----------------------------------------------------------
  CREATELIGHTINGFORM(void);
  //-----------------------------------------------------------
  void InitDialog(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void Command(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void Paint(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  //-----------------------------------------------------------
  void Initialize(void);//начальная инициализация
  void CreateNewLighting(int x,int y);//создание нового источника света
  void ModifycationLighting(int lighting);//модификация источника света
  void DeleteLighting(void);//удаление источника света
  void SetColor(void);//установка цвета источника
  void SaveLighting(FILE *File);//сохранение источников света
  void LoadLighting(FILE *File);//загрузка источников света
  void DrawAllLighting(int xLeftMap,int yTopMap);//нарисовать все источники света
  int GetLightingInScreen(int x,int y);//возвращает выбранный на экране источник света
  void SaveLightingFromRender(FILE *File,int lighting);//сохранение ламп для оцифровщика
  //-----------------------------------------------------------
};

#endif

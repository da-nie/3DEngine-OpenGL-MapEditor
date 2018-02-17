#ifndef DL_STARTPOSFORM_H
#define DL_STARTPOSFORM_H

#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include "common.h"
#include "resource.h"
#include "formats.h"
#include "gdi.h"

//------------------------------------------------------------------------------
LONG WINAPI STARTPOSFORM_dlgProc(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam);
//------------------------------------------------------------------------------
class STARTPOSFORM
{
 public:
  //-----------------------------------------------------------
  HWND hDlg;
  //-----------------------------------------------------------
  HWND hEdit_Angle;
  //-----------------------------------------------------------
  int Angle;
  int Start_X_Pos;
  int Start_Y_Pos;
  int Working_X_Pos;
  int Working_Y_Pos;
  //-----------------------------------------------------------
  STARTPOSFORM(void);
  //-----------------------------------------------------------
  void InitDialog(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void Command(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  //-----------------------------------------------------------
  void Initialize(void);//инициализация структур
  void Activate(int x,int y);//запуск диалога
  void SaveStartPosition(FILE *File);//сохранение стартовой позиции
  void LoadStartPosition(FILE *File);//загрузка стартовой позиции
  void DrawStartPos(int xLeftMap,int yTopMap);//нарисовать стартовую позицию
  void SaveStartPositionFromRender(FILE *File);//сохранение стартовой позиции при оцифровке
};

#endif

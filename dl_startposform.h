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
  void Initialize(void);//������������� ��������
  void Activate(int x,int y);//������ �������
  void SaveStartPosition(FILE *File);//���������� ��������� �������
  void LoadStartPosition(FILE *File);//�������� ��������� �������
  void DrawStartPos(int xLeftMap,int yTopMap);//���������� ��������� �������
  void SaveStartPositionFromRender(FILE *File);//���������� ��������� ������� ��� ���������
};

#endif

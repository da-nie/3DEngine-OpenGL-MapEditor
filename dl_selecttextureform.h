#ifndef DL_SELECTTEXTUREFORM_H
#define DL_SELECTTEXTUREFORM_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "resource.h"

#include "formats.h"
#include "dl_showtextureform.h"

//------------------------------------------------------------------------------
struct STexture
{
 int TextureNo;//����� ��������
 int FlipVertical;//1-�������� �����������
 int FlipHorizontal;//1-�������� �������������
 int Rotate;//1-��������� �� 90
 int OffsetX;//�������� ��������
 int OffsetY;
 int ScaleX;//������� ��������
 int ScaleY;
};
//------------------------------------------------------------------------------
LONG WINAPI SELECTTEXTUREFORM_dlgProc(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam);

//------------------------------------------------------------------------------
class CDialog_SelectTexture
{
 public:
  //-----------------------------------------------------------
  HWND hDlg;
  //-----------------------------------------------------------
  HWND hButton_Cancel;
  HWND hButton_Ok;
  HWND hScroll_Horizontal;
  HWND hScroll_Vertical;
  HWND hEdit_Offset_X;
  HWND hEdit_Offset_Y;
  HWND hEdit_Scale_X;
  HWND hEdit_Scale_Y;
  HWND hCheckBox_Flip_V;
  HWND hCheckBox_Flip_H;
  HWND hCheckBox_Rotate;
  //-----------------------------------------------------------
  STexture OldTexture;//������ ��������
  STexture WorkingTexture;//������� ��������
  int Mode;//0-���������� �����,1-����������� �������������� ��������� ��������
  int hPos;//�������������� ������� �������
  int vPos;//������������ ������� �������
  int hPosMax;//������������ �������������� ������� �������
  int vPosMax;//������������ ������������ ������� �������
  //-----------------------------------------------------------
  void InitDialog(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void Command(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void Paint(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void HScroll(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void VScroll(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void LButtonUp(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  //-----------------------------------------------------------
  void SaveTextureStruct(FILE *File,STexture Texture);//��������� ��������� ��������
  STexture LoadTextureStruct(FILE *File);//��������� ��������� ��������
  int CompareTextureStruct(STexture Texture1,STexture Texture2);//���������� ��� ��������� ��������
  void CreateTextureImage(STexture Texture,unsigned char *Image);//������ ����� �������� �� � ����������
  void CreateTextureCoord(STexture Texture,double *TX,double *TY);
  void InitializeTextureStruct(STexture *Texture);
  void CopyTextureStruct(STexture *T1,STexture T2);
  //-----------------------------------------------------------
  STexture Activate(HWND hWnd,STexture Texture,int mode);//���������� ��������� ��� ��������� ��������
  //-----------------------------------------------------------
};

#endif
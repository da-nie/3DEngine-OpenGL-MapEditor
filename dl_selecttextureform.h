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
struct TEXTURE
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
class SELECTTEXTUREFORM
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
  TEXTURE OldTexture;//������ ��������
  TEXTURE WorkingTexture;//������� ��������
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
  void SaveTextureStruct(FILE *File,TEXTURE Texture);//��������� ��������� ��������
  TEXTURE LoadTextureStruct(FILE *File);//��������� ��������� ��������
  int CompareTextureStruct(TEXTURE Texture1,TEXTURE Texture2);//���������� ��� ��������� ��������
  void CreateTextureImage(TEXTURE Texture,unsigned char *Image);//������ ����� �������� �� � ����������
  void CreateTextureCoord(TEXTURE Texture,double *TX,double *TY);
  void InitializeTextureStruct(TEXTURE *Texture);
  void CopyTextureStruct(TEXTURE *T1,TEXTURE T2);
  //-----------------------------------------------------------
  TEXTURE Activate(HWND hWnd,TEXTURE Texture,int mode);//���������� ��������� ��� ��������� ��������
  //-----------------------------------------------------------
};

#endif
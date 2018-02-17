#ifndef DL_SETSTextureFollow_H
#define DL_SETSTextureFollow_H

#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "resource.h"

#include "dl_selecttextureform.h"
#include "button.h"

//------------------------------------------------------------------------------
struct STextureFollow
{
 int MaximumTexture;
 STexture TextureList[100];
 int Mode;
 int ScrollLToR;//-1-обратное направление
 int ScrollUToD;//-1-обратное направление
 int SpeedLToR;
 int SpeedUToD;
};
//------------------------------------------------------------------------------
LONG WINAPI SETTEXTUREFOLLOWFORM_dlgProc(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam);
//------------------------------------------------------------------------------
class SETSTextureFollowCWnd_Form
{
 public:
  //-----------------------------------------------------------
  HWND hDlg;
  //-----------------------------------------------------------
  HWND hRadioButton_Mode1;
  HWND hRadioButton_Mode2;
  HWND hRadioButton_Disable;
  HWND hRadioButton_SLToR;
  HWND hRadioButton_SUToD;
  HWND hRadioButton_InvertSLToR;
  HWND hRadioButton_InvertSUToD;
  HWND hScrollBar_List;
  HWND hEdit_SpeedSLToR;
  HWND hEdit_SpeedSUToD;
  //-----------------------------------------------------------
  STextureFollow TextureFollow;
  STextureFollow OldTextureFollow;
  int hPos;//позиция бегунка
  //-----------------------------------------------------------
  void InitDialog(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void Command(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void HScroll(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void Paint(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  //-----------------------------------------------------------
  void SaveForRender(STextureFollow texturefollow,FILE *File);
  void Save(STextureFollow texturefollow,FILE *File);
  void Load(STextureFollow *texturefollow,FILE *File);
  void InitializeTextureFollow(STextureFollow *texturefollow);
  //-----------------------------------------------------------
  STextureFollow Activate(HWND hWnd,STextureFollow texturefollow);//запуск диалога
};

#endif

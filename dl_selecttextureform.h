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
 int TextureNo;//номер текстуры
 int FlipVertical;//1-отразить вертикально
 int FlipHorizontal;//1-отразить горизонтально
 int Rotate;//1-повернуть на 90
 int OffsetX;//смещение текстуры
 int OffsetY;
 int ScaleX;//масштаб текстуры
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
  TEXTURE OldTexture;//старая текстура
  TEXTURE WorkingTexture;//рабочая текстура
  int Mode;//0-нормальный режим,1-блокировать дополнительные настройки текстуры
  int hPos;//горизонтальная позиция бегунка
  int vPos;//вертикальная позиция безунка
  int hPosMax;//максимальная горизонтальная позиция бегунка
  int vPosMax;//максимальная вертикальная позиция бегунка
  //-----------------------------------------------------------
  void InitDialog(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void Command(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void Paint(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void HScroll(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void VScroll(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void LButtonUp(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  //-----------------------------------------------------------
  void SaveTextureStruct(FILE *File,TEXTURE Texture);//сохраняет структуру текстуры
  TEXTURE LoadTextureStruct(FILE *File);//загружает структуру текстуры
  int CompareTextureStruct(TEXTURE Texture1,TEXTURE Texture2);//сравнивает две структуры текстуры
  void CreateTextureImage(TEXTURE Texture,unsigned char *Image);//создаёт образ текстуры по её параметрам
  void CreateTextureCoord(TEXTURE Texture,double *TX,double *TY);
  void InitializeTextureStruct(TEXTURE *Texture);
  void CopyTextureStruct(TEXTURE *T1,TEXTURE T2);
  //-----------------------------------------------------------
  TEXTURE Activate(HWND hWnd,TEXTURE Texture,int mode);//возвращает структуру для выбранной текстуры
  //-----------------------------------------------------------
};

#endif
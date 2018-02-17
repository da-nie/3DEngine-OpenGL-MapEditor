#ifndef DL_CREATESIMPLYSECTORFORM_H
#define DL_CREATESIMPLYSECTORFORM_H

#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "resource.h"

#include "colorset.h"
#include "common.h"
#include "formats.h"
#include "dl_selecttextureform.h"
#include "dl_settexturefollowform.h"
#include "wc_menuform.h"
#include "gdi.h"
#include "surface.h"

//------------------------------------------------------------------------------
struct SIMPLY_SECTOR
{
 int UpLevel;//уровень потолка
 int DownLevel;//уровень пола
 TEXTURE UpTexture;//текстура потолка
 TEXTURE DownTexture;//текстура пола
 int Vertex;//число вершин, задающих сектор
 int X[100];//координаты этих вершин
 int Y[100];
 TEXTUREFOLLOW UpTextureFollow;//последовательность анимации текстуры потолка
 TEXTUREFOLLOW DownTextureFollow;//последовательность анимации текстуры пола
 unsigned char UpEmissionR;//эмиссия потолка
 unsigned char UpEmissionG;
 unsigned char UpEmissionB;
 unsigned char DownEmissionR;//эмиссия пола
 unsigned char DownEmissionG;
 unsigned char DownEmissionB;
};
//------------------------------------------------------------------------------
LONG WINAPI CREATESIMPLYSECTORFORM_dlgProc(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam);
//------------------------------------------------------------------------------
class CREATESIMPLYSECTORFORM
{
 public:
  //-----------------------------------------------------------
  HWND hDlg;
  //-----------------------------------------------------------
  HWND hEdit_UpLevel;
  HWND hEdit_DownLevel;
  COLORSET ColorSet;
  //-----------------------------------------------------------
  SIMPLY_SECTOR WorkingSector;
  int Flag;
  int SelectSector;
  SIMPLY_SECTOR Sector[5000];
  //-----------------------------------------------------------
  CREATESIMPLYSECTORFORM(void);
  //-----------------------------------------------------------
  void InitDialog(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void Paint(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void Command(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  //-----------------------------------------------------------
  void Initialize(void);//инициализация структур
  void CreateNewSector(void);//создание нового сектора
  void ModifycationSector(int sector);//модификация сектора
  void DeleteSector(void);//удаление выбранного сектора
  void SaveSector(FILE *File);//сохранение секторов
  void LoadSector(FILE *File);//загрузка секторов
  int GetSectorInScreen(int x,int y);//возвращает номер сектора по экранным координатам или -1
  int GetSectorInMap(float x,float y,int number);//возвращает номер сектора начиная с number по координатам на карте или -1
  void DrawAllSector(int xLeftMap,int yTopMap);//рисует все сектора
  void GenerateFloor(int n,SECTOR_PACKAGE *SCP);//заполняет параметрами пола
  void GenerateCeiling(int n,SECTOR_PACKAGE *SCP);//заполняет параметрами потолка
  int GetUpLevelFromSegment(int n);//возвращает верхний уровень обычного сегмента для рендеринга
  int GetDownLevelFromSegment(int n);//возвращает нижний уровень обычного сегмента для рендеринга
  int GetUpLevelFromFrontier(int n);//возвращает верхний уровень линии раздела для рендеринга
  int GetDownLevelFromFrontier(int n);//возвращает нижний уровень линии раздела для рендеринга
  int GetPosition(int n,float X1,float Y1,float X2,float Y2);//возвращает положение сектора относительно прямой(-1-справа,1-слева,0-не определено)
  void SaveSectorFromRender(FILE *File,int sector);//сохранение сектора для оцифровщика
  //-----------------------------------------------------------
};

#endif
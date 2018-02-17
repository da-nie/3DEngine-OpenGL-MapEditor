#ifndef DL_CREATESEGMENTFORM_H
#define DL_CREATESEGMENTFORM_H

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
#include "dl_createsimplydoorform.h"
#include "dl_createsimplysectorform.h"
#include "wc_menuform.h"
#include "gdi.h"

//------------------------------------------------------------------------------
struct SEGMENT
{
 int X1;//координаты сегмента
 int Y1;
 int X2;
 int Y2;
 TEXTURE UpTexture;//номер верхней текстуры
 TEXTURE DownTexture;//номер нижней текстуры( у сегмента они равны)
 unsigned char UpEmissionR;//эмиссия верхней части
 unsigned char UpEmissionG;
 unsigned char UpEmissionB;
 unsigned char DownEmissionR;//эмиссия нижней части
 unsigned char DownEmissionG;
 unsigned char DownEmissionB;
 int Frontier;//является ли сегмент линией раздела (0-нет)
 //--------------------
 TEXTUREFOLLOW UpTextureFollow;//последовательность анимации текстуры
 TEXTUREFOLLOW DownTextureFollow;//последовательность анимации текстуры
 //--------------------
 int SectorOne;//номер первого сектора к которому принадлежит линия
 int SectorOneType;//его класс
 int SectorTwo;//номер второго сектора к которому принадлежит линия
 int SectorTwoType;//его класс
 int Blend;//1-полупрозрачность (только для сегментов)
 int DoubleSegment;//1-сегмент лежит на границе раздела (только для сегментов)
};
//------------------------------------------------------------------------------
LONG WINAPI CREATESEGMENTFORM_dlgProc(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam);
//------------------------------------------------------------------------------
class CREATESEGMENTFORM
{
 public:
  //-----------------------------------------------------------
  HWND hDlg;
  //-----------------------------------------------------------
  HWND hCheckBox_Blend;
  COLORSET ColorSet;
  //-----------------------------------------------------------
  SEGMENT WorkingSegment;//работа идёт с этой структурой
  SEGMENT OldWorkingSegment;//здесь сохраняются старые параметры сегмента, на случай отмены действия
  int SelectSegment;//сегмент, с которым происходит работа
  int Flag;//0-создание сегмента,1-модификация старого
  SEGMENT Segment[20000];
  //-----------------------------------------------------------
  CREATESEGMENTFORM(void);
  //-----------------------------------------------------------
  void InitDialog(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void Paint(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void Command(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  //-----------------------------------------------------------
  void Initialize(void);//инициализация
  void ChangeParameters(void);//изменить текущие настройки
  void CreateNewSegment(int frontier);//создание нового сегмента
  void ModifycationSegment(int segment);//модификация сегмента
  void CreateSegment(int frontier);//создание сегмента без вызова диалога
  void DeleteSegment(void);//удаление сегмента
  void SaveSegment(FILE *File);//сохранение сегментов
  void LoadSegment(FILE *File);//загрузка сегментов
  void DrawAllSegment(int xLeftMap,int yTopMap);//нарисовать все сегменты
  int GetLineInScreen(int x,int y,int frontier);//возвращает номер выбранной по экранным координатам линии c нужным frontier
  float DistanceOfVector(float xc,float yc,float xa,float ya,float xb,float yb);//возвращает расстояние от точки до прямой
  int DefinitionSector(void);//заполняет структуры линий значениями секторов. возвращает 0-ошибок нет иначе ошибки
  void SaveSegmentFromRender(FILE *File,int no);//сохранение сегмента no для модуля оцифровки
  //-----------------------------------------------------------
};
#endif
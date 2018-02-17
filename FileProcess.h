#ifndef FILEPROCESS_H
#define FILEPROCESS_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//*************************************************************************************************************************
//Класс файлового диалога
//*************************************************************************************************************************
//------------------------------------------------------------------------------
class FILEPROCESSED
{
 public:
  OPENFILENAME OFN;
  char CustomFilter[1024];
  char FileName[1024];
  char FileTitle[1024];
  char InitialDir[1024];
  char DefExtension[1024];
  char Title[1024];
  void Create(HWND hWnd);
  int Open(void);
  int Save(void);
  int StartOpen(char *BarName,char *Filter);
  int StartSave(char *BarName,char *Filter);
  void SetFilter(char *filter);
  void SetTitle(char *title);
};
#endif
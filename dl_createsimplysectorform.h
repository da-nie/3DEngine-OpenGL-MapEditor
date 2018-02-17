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
struct SSimplySector
{
 int UpLevel;//������� �������
 int DownLevel;//������� ����
 STexture UpTexture;//�������� �������
 STexture DownTexture;//�������� ����
 int Vertex;//����� ������, �������� ������
 int X[100];//���������� ���� ������
 int Y[100];
 STextureFollow UpTextureFollow;//������������������ �������� �������� �������
 STextureFollow DownTextureFollow;//������������������ �������� �������� ����
 unsigned char UpEmissionR;//������� �������
 unsigned char UpEmissionG;
 unsigned char UpEmissionB;
 unsigned char DownEmissionR;//������� ����
 unsigned char DownEmissionG;
 unsigned char DownEmissionB;
};
//------------------------------------------------------------------------------
LONG WINAPI CREATESIMPLYSECTORFORM_dlgProc(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam);
//------------------------------------------------------------------------------
class CDialog_CreateSimplySector
{
 public:
  //-----------------------------------------------------------
  HWND hDlg;
  //-----------------------------------------------------------
  HWND hEdit_UpLevel;
  HWND hEdit_DownLevel;
  CColorSet ColorSet;
  //-----------------------------------------------------------
  SSimplySector WorkingSector;
  int Flag;
  int SelectSector;
  SSimplySector Sector[5000];
  //-----------------------------------------------------------
  CDialog_CreateSimplySector(void);
  //-----------------------------------------------------------
  void InitDialog(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void Paint(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void Command(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  //-----------------------------------------------------------
  void Initialize(void);//������������� ��������
  void CreateNewSector(void);//�������� ������ �������
  void ModifycationSector(int sector);//����������� �������
  void DeleteSector(void);//�������� ���������� �������
  void SaveSector(FILE *File);//���������� ��������
  void LoadSector(FILE *File);//�������� ��������
  int GetSectorInScreen(int x,int y);//���������� ����� ������� �� �������� ����������� ��� -1
  int GetSectorInMap(float x,float y,int number);//���������� ����� ������� ������� � number �� ����������� �� ����� ��� -1
  void DrawAllSector(int xLeftMap,int yTopMap);//������ ��� �������
  void GenerateFloor(int n,SSectorPackage *SCP);//��������� ����������� ����
  void GenerateCeiling(int n,SSectorPackage *SCP);//��������� ����������� �������
  int GetUpLevelFromSegment(int n);//���������� ������� ������� �������� �������� ��� ����������
  int GetDownLevelFromSegment(int n);//���������� ������ ������� �������� �������� ��� ����������
  int GetUpLevelFromFrontier(int n);//���������� ������� ������� ����� ������� ��� ����������
  int GetDownLevelFromFrontier(int n);//���������� ������ ������� ����� ������� ��� ����������
  int GetPosition(int n,float X1,float Y1,float X2,float Y2);//���������� ��������� ������� ������������ ������(-1-������,1-�����,0-�� ����������)
  void SaveSectorFromRender(FILE *File,int sector);//���������� ������� ��� �����������
  //-----------------------------------------------------------
};

#endif
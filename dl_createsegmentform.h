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
 int X1;//���������� ��������
 int Y1;
 int X2;
 int Y2;
 TEXTURE UpTexture;//����� ������� ��������
 TEXTURE DownTexture;//����� ������ ��������( � �������� ��� �����)
 unsigned char UpEmissionR;//������� ������� �����
 unsigned char UpEmissionG;
 unsigned char UpEmissionB;
 unsigned char DownEmissionR;//������� ������ �����
 unsigned char DownEmissionG;
 unsigned char DownEmissionB;
 int Frontier;//�������� �� ������� ������ ������� (0-���)
 //--------------------
 TEXTUREFOLLOW UpTextureFollow;//������������������ �������� ��������
 TEXTUREFOLLOW DownTextureFollow;//������������������ �������� ��������
 //--------------------
 int SectorOne;//����� ������� ������� � �������� ����������� �����
 int SectorOneType;//��� �����
 int SectorTwo;//����� ������� ������� � �������� ����������� �����
 int SectorTwoType;//��� �����
 int Blend;//1-���������������� (������ ��� ���������)
 int DoubleSegment;//1-������� ����� �� ������� ������� (������ ��� ���������)
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
  SEGMENT WorkingSegment;//������ ��� � ���� ����������
  SEGMENT OldWorkingSegment;//����� ����������� ������ ��������� ��������, �� ������ ������ ��������
  int SelectSegment;//�������, � ������� ���������� ������
  int Flag;//0-�������� ��������,1-����������� �������
  SEGMENT Segment[20000];
  //-----------------------------------------------------------
  CREATESEGMENTFORM(void);
  //-----------------------------------------------------------
  void InitDialog(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void Paint(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  void Command(HWND hDlgs,WPARAM wParam,LPARAM lParam);
  //-----------------------------------------------------------
  void Initialize(void);//�������������
  void ChangeParameters(void);//�������� ������� ���������
  void CreateNewSegment(int frontier);//�������� ������ ��������
  void ModifycationSegment(int segment);//����������� ��������
  void CreateSegment(int frontier);//�������� �������� ��� ������ �������
  void DeleteSegment(void);//�������� ��������
  void SaveSegment(FILE *File);//���������� ���������
  void LoadSegment(FILE *File);//�������� ���������
  void DrawAllSegment(int xLeftMap,int yTopMap);//���������� ��� ��������
  int GetLineInScreen(int x,int y,int frontier);//���������� ����� ��������� �� �������� ����������� ����� c ������ frontier
  float DistanceOfVector(float xc,float yc,float xa,float ya,float xb,float yb);//���������� ���������� �� ����� �� ������
  int DefinitionSector(void);//��������� ��������� ����� ���������� ��������. ���������� 0-������ ��� ����� ������
  void SaveSegmentFromRender(FILE *File,int no);//���������� �������� no ��� ������ ���������
  //-----------------------------------------------------------
};
#endif
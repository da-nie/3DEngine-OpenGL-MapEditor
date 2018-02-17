#ifndef LIGHTING_H
#define LIGHTING_H

#include <windows.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "resource.h"
#include "common.h"
#include "surface.h"
#include "polygon.h"
#include "shadow.h"
#include "dl_createlightingform.h"

class LIGHT
{
 public:
  //----------------------------------------------------------------------------
  SURFACE *Surface;
  int AllSurface;
  int CurrentSurface;
  int *SphereFromLight[8];//������ ��� ������� ��������� ����� � ����� ����� ��������� ������, ���������� �
  int LightingNumber[8];//������ ���������� �����
  int LightingAmount;//����� ���������� �����
  SPoint sPoint_Lighting[8];//���������� ���������� �����
  int SphereMaxSurfaceFromLight[8];//������� ��� ������� ��������� ����� ���������� ������
  //----------------------------------------------------------------------------
  LIGHT(SURFACE *SurfacePointer,int AllSurfaceNumber);
  ~LIGHT(void);
  void SetCurrentSurface(int sfc,int segment,int sector,int sectortype,CPolygon *cPolygon_Stage);
  void SetShadowSurface(int sfc,double xc,double yc,double zc,int lightingnumber);
};
#endif


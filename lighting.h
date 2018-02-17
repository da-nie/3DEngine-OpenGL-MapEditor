#ifndef SLighting_H
#define SLighting_H

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

class CLight
{
 public:
  //----------------------------------------------------------------------------
  SSurface *Surface;
  int AllSurface;
  int CurrentSurface;
  int *SphereFromLight[8];//список для каждого источника света и нашей грани возможных граней, затеняющих её
  int LightingNumber[8];//номера источников света
  int LightingAmount;//число источников света
  SPoint sPoint_Lighting[8];//координаты источников света
  int SphereMaxSurfaceFromLight[8];//сколько для данного источника света затеняющих граней
  //----------------------------------------------------------------------------
  CLight(SSurface *SurfacePointer,int AllSurfaceNumber);
  ~CLight(void);
  void SetCurrentSurface(int sfc,int segment,int sector,int sectortype,CPolygon *cPolygon_Stage);
  void SetShadowSurface(int sfc,double xc,double yc,double zc,int lightingnumber);
};
#endif


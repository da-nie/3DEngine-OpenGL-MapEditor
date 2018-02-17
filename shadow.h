#ifndef SHADOW_H
#define SHADOW_H

#include <math.h>
#include <windows.h>
#include "common.h"
#include "vector.h"
#include "polygon.h"

#define S_EPS 0.01
#define S_EPS1 0.0000001
#define S_EPS2 0.0001

int GetPointPositionInPlaneXZ(SPoint sPoint_A,SPoint sPoint_B,SPoint sPoint);
int GetPointPositionPlane(SPoint sPoint_A,SPoint sPoint_Plane,SVector sVector_Normal);
BOOL IsPointInPolygonXZ(SPoint sPoint,SPolygon sPolygon);
BOOL GetPieceIntersectionInPlaneXZ(SPoint A,SPoint B,SPoint C,SPoint D,SPoint *sPointReturn);
BOOL GetLineIntersectionPieceInPlaneXZ(SPoint A,SPoint B,SPoint C,SPoint D,SPoint *sPointReturn);
BOOL GetLineIntersectionPlane(SPoint sPoint_A,SPoint sPoint_B,SPoint sPoint_Plane,SVector sVector_Normal,int mode,SPoint* sPointReturn);
BOOL IsPointInPolygon(SPoint sPoint,SPolygon sPolygon);
BOOL GenerateShadow(SPolygon sPolygon_ShadowSource,SPolygon sPolygon_ShadowDestination,SPoint sPoint_Lighting,CPolygon *cPolygon_Fragment);

#endif
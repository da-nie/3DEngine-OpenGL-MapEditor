#ifndef POLYGON_H
#define POLYGON_H

#include "vector.h"
#include <windows.h>

struct SPoint
{
 double X;
 double Y;
 double Z;
};
struct SPolygon
{
 int PointAmount;
 SPoint *sPoint_Array;
 //данные, вычисляемые автоматически
 SVector sVector_Normal;//вектор нормали
 BOOL LightingEnable[8];
};
//---------------------------------------------------------------------------
struct SPolygonLinker
{
 int Identificator;//идентификатор полигона
 int Index;//индекс полигона в массиве
};

//---------------------------------------------------------------------------
class CPolygon
{
 //переменные класса
 public:
  SPolygon *sPolygon_Array;//массив полигонов
  int AmountOfPolygons;//всего полигонов
  SPolygonLinker *sPolygonLinker_Array;//массив структур, связывающих номер полигонов с его индексом в массиве
 public:
  //методы класса
 public:
  //-------------------------------------------------------------------------
  CPolygon(void); 
  //-------------------------------------------------------------------------
  ~CPolygon(void); 
  //-------------------------------------------------------------------------
  int CreateNewPolygon(SPolygon polygon);
  void DeletePolygon(int polygon_identificator);
  void ClearAllPolygon(void);
  int GetAmountOfPolygons(void);
  SPolygon GetPolygonForIdentificator(int polygon_identificator);
  SPolygon GetPolygonForIndex(int polygon_index);
  int GetPolygonIndex(int polygon_identificator);
  int GetPolygonIdentificator(int polygon_index);
  void GenerateNormal(int polygon_index);
  void SetPolygonNormalForIndex(int polygon_index,SVector sVector);
  void SetPolygonLightingEnableForIndex(int polygon_index,BOOL *lightingenable);
  //-------------------------------------------------------------------------
};

SVector CalculateNormal(SPoint sp1,SPoint sp2,SPoint sp3);
SVector CalculateNormalVector(SPolygon sPolygon);

#endif


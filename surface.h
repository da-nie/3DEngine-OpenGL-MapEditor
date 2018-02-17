#ifndef SURFACE_H
#define SURFACE_H

#include "dl_selecttextureform.h"
#include "vector.h"

struct SEGMENT_PACKAGE
{
 double X[4];
 double Y[4];
 double Z[4];
 TEXTURE Texture;
 SVector Normal;
 int Segment;
 int Location;
 double X_Left_Up;
 double Y_Left_Up;
 double Z_Left_Up;
 int BarrierType;
};
struct SECTOR_PACKAGE
{
 int Vertex;
 double X[100];
 double Y[100];
 double Z[100];
 TEXTURE Texture;
 int Sector;
 int SectorType;
 SVector Normal;
 int Location;
 int BarrierType;
 int Dz;
};
struct SURFACE
{
 int Vertex;
 double X[100];
 double Y[100];
 double Z[100];
 TEXTURE Texture;
 int Location;//0-просто поверхность, 1-верхняя,2-нижняя (это нужно для отделения текстур линий раздела)
 //у секторов бывают лишь 1 или 2-потолок и пол.
 int Segment;//номер сегмента к которому относится поверхность(если это стена)
 int SectorType;//тип сектора к которому относится поверхность(если это пол-потолок)
 int Sector;//номер сектора к которому относится поверхность(если это пол-потолок)
 int Dz;//смещение по высоте для поверхностей (только для полов-потолков)
 SVector Normal;
 SURFACE *Next;
 SURFACE *Previous;
 int BarrierType;//0-поверхность сплошная, 1-поверхность-стекло (только для сегментов), 2-поверхность не создаёт теней (для движущихся стен)
 //данные для обработки текстуры (только для сегментов)
 double X_Left_Up;
 double Y_Left_Up;
 double Z_Left_Up;
};
//------------------------------------------------------------------------------
void NewSurfaceSegment(SURFACE **Surface,SEGMENT_PACKAGE SP);
void NewSurfaceSector(SURFACE **Surface,SECTOR_PACKAGE SCP);
void DeleteAllSurface(SURFACE **Surface);

#endif
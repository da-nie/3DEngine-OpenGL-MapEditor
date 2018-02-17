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
 int Location;//0-������ �����������, 1-�������,2-������ (��� ����� ��� ��������� ������� ����� �������)
 //� �������� ������ ���� 1 ��� 2-������� � ���.
 int Segment;//����� �������� � �������� ��������� �����������(���� ��� �����)
 int SectorType;//��� ������� � �������� ��������� �����������(���� ��� ���-�������)
 int Sector;//����� ������� � �������� ��������� �����������(���� ��� ���-�������)
 int Dz;//�������� �� ������ ��� ������������ (������ ��� �����-��������)
 SVector Normal;
 SURFACE *Next;
 SURFACE *Previous;
 int BarrierType;//0-����������� ��������, 1-�����������-������ (������ ��� ���������), 2-����������� �� ������ ����� (��� ���������� ����)
 //������ ��� ��������� �������� (������ ��� ���������)
 double X_Left_Up;
 double Y_Left_Up;
 double Z_Left_Up;
};
//------------------------------------------------------------------------------
void NewSurfaceSegment(SURFACE **Surface,SEGMENT_PACKAGE SP);
void NewSurfaceSector(SURFACE **Surface,SECTOR_PACKAGE SCP);
void DeleteAllSurface(SURFACE **Surface);

#endif
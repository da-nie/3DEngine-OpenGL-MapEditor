#ifndef SSurface_H
#define SSurface_H

#include "dl_selecttextureform.h"
#include "vector.h"

struct SSegmentPackage
{
 double X[4];
 double Y[4];
 double Z[4];
 STexture Texture;
 SVector Normal;
 int Segment;
 int Location;
 double X_Left_Up;
 double Y_Left_Up;
 double Z_Left_Up;
 int BarrierType;
};
struct SSectorPackage
{
 int Vertex;
 double X[100];
 double Y[100];
 double Z[100];
 STexture Texture;
 int Sector;
 int SectorType;
 SVector Normal;
 int Location;
 int BarrierType;
 int Dz;
};
struct SSurface
{
 int Vertex;
 double X[100];
 double Y[100];
 double Z[100];
 STexture Texture;
 int Location;//0-������ �����������, 1-�������,2-������ (��� ����� ��� ��������� ������� ����� �������)
 //� �������� ������ ���� 1 ��� 2-������� � ���.
 int Segment;//����� �������� � �������� ��������� �����������(���� ��� �����)
 int SectorType;//��� ������� � �������� ��������� �����������(���� ��� ���-�������)
 int Sector;//����� ������� � �������� ��������� �����������(���� ��� ���-�������)
 int Dz;//�������� �� ������ ��� ������������ (������ ��� �����-��������)
 SVector Normal;
 SSurface *Next;
 SSurface *Previous;
 int BarrierType;//0-����������� ��������, 1-�����������-������ (������ ��� ���������), 2-����������� �� ������ ����� (��� ���������� ����)
 //������ ��� ��������� �������� (������ ��� ���������)
 double X_Left_Up;
 double Y_Left_Up;
 double Z_Left_Up;
};
//------------------------------------------------------------------------------
void NewSurfaceSegment(SSurface **Surface,SSegmentPackage SP);
void NewSurfaceSector(SSurface **Surface,SSectorPackage SCP);
void DeleteAllSurface(SSurface **Surface);

#endif
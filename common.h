#ifndef COMMON_H
#define COMMON_H
 
#include <windows.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "resource.h"
 
#define M_PI 3.141592654
#define EPS  0.00001
//------------------------------------------------------------------------------
struct SETUP//��������� ���������
{
 int ShowSegmentCreateDialog;//1-������ �������� �������� ������������,0-���
 int ShowVector;//1-����������� ����� ������������
 int ShowSegment;//1-�������� ������������
 int ShowSector;//1-������� ������������
 int ShowLighting;//1-��������� ����� ������������
 int BlockSize;//������ ����� ���������
 double Constant_Attenuation;//���������� ���������� �����
 double Linear_Attenuation;//�������� ���������� �����
 double Quadric_Attenuation;//������������ ���������� �����
 unsigned char R_Ambient;//���������� ������� ���������
 unsigned char G_Ambient;
 unsigned char B_Ambient;
  
 unsigned char R_Fog;//���� ������
 unsigned char G_Fog;
 unsigned char B_Fog;
 int Fog_Density;//������� ������
 int Fog_Enable;//1-����� �������
};
struct TEXTURE_MAP
{
 int Size;//������ �������� �� X � �� Y (�������� ������ ���������� � ������ ������� 2)
 unsigned char *R;//����� ��������
 unsigned char *G;
 unsigned char *B;
};
struct KEY_DATA//�������� ����������
{
 int PrimaryMode;//��������� ����� ������
 int SecondaryMode;//��������� ����� ������
 int MaximumNumberOfLine;//������� ����� �� ����� ����� (�����-������� ��� ����� �������)
 int MaximumNumberOfSimplySector;//������� ����� �� ����� ������� ��������
 int MaximumNumberOfSimplyDoor;//������� ����� �� ����� ������� ������
 int MaximumNumberOfDisposableDoor;//������� ����� �� ����� ����������� ������
 int MaximumNumberOfClosedDoor;//������� ����� �� ����� �������� ������
 int MaximumNumberOfAutoClosedDoor;//������� ����� �� ����� ������������� ������
 int MaximumNumberOfSimplyPlatform;//������� ����� �� ����� ������� ��������
 int MaximumNumberOfInactivePlatform;//������� ����� �� ����� ���������� ��������
 int MaximumNumberOfDisconnectPlatform;//������� ����� �� ����� ������������� ��������
 int MaximumNumberOfSimplyBridge;//������� ����� �� ����� ������� ��������
 int MaximumNumberOfSimplyTeleport;//������� ����� �� ����� ������� ��������������
 int MaximumNumberOfAllSector;//������� ����� �� ����� ���� ��������
 int MaximumNumberOfLighting;//������� ����� �� ����� ���������� �����
  
 int MaximumTexture;//������������ ����� ����������� �������
 TEXTURE_MAP *TextureMap;
  
 int X[1000];//���������� ��������� �����
 int Y[1000];
 int MaximumPset;//����� ����� � �������� �����
 int SelectLine;//����� ���������� ��������
 int SelectLighting;//����� ���������� ��������� �����
 int SelectSector;//����� ���������� �������
 int SelectSectorType;//��� ���������� �������
 HWND hWndMain;//���������� ������� �����(����� ��� � ����������� ��������� ������)
 HWND hWndMenu;//���������� ���� ����������(����� ��� ������������ ��� ������� ������)
 HWND hWndProgress;//���������� ���� ��������� ����������(����� ��� ��� ����������)
};
//------------------------------------------------------------------------------
//������ ������� ������ (Primary,Secondary)
//0,0-������
//1,0-�������� ���������
//1,1-�������� ����� �������
//2,0-�������� �������� �������
//2,1-�������� ������� �����
//2,2-�������� ����������� �����
//2,3-�������� �������� �����
//2,4-�������� ������������ �����
//2,5-�������� ������� ���������
//2,6-�������� ���������� ���������
//2,7-�������� ������������� ���������
//2,8-�������� �������� �������
//2,9-�������� �������� �������������
//3,0-�������� ��������� �����
//4,0-������� ���������� ��������� �������
//5,0-�������� ����������� ��������������
//5,1-�������� ������
//6,0-�������� ���������
//7,0-�������� ��������
//8,0-�������� ���������� �����
//9,0-����������� ���������
//10,0-����������� ��������
//11,0-����������� ���������� �����
//------------------------------------------------------------------------------
 
#endif
 
 

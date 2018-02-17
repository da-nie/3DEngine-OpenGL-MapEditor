#include "render.h"

extern CREATESEGMENTFORM CreateSegmentForm;
extern CREATESIMPLYDOORFORM CreateSimplyDoorForm;
extern CREATESIMPLYSECTORFORM CreateSimplySectorForm;
extern CREATELIGHTINGFORM CreateLightingForm;
extern SELECTTEXTUREFORM SelectTextureForm;
extern PROGRESS Progress;
extern STARTPOSFORM StartPosForm;
extern SETUP SetUp;//��������� ���������


//------------------------------------------------------------------------------
RENDER::RENDER(char *FileName)
{
 SEGMENT_PACKAGE SP;
 SECTOR_PACKAGE SCP;
 SURFACE *Surface=NULL;
 int n,m,u,v,k,l,r;
 //�������� �������� ���������� ���� �������
 if (CreateSegmentForm.DefinitionSector()==1) return;
 //�������� ����������� ����
 for(n=0;n<KeyData.MaximumNumberOfLine;n++)
 {
  int type=CreateSegmentForm.Segment[n].Frontier;
  if (type==0)//��� ������� �����
  {
   double up_level,down_level;
   int SectorOneType=CreateSegmentForm.Segment[n].SectorOneType;
   int SectorOne=CreateSegmentForm.Segment[n].SectorOne;
   int SectorTwoType=CreateSegmentForm.Segment[n].SectorTwoType;
   int SectorTwo=CreateSegmentForm.Segment[n].SectorTwo;
   if (CreateSegmentForm.Segment[n].DoubleSegment==0)//������� ����������� ������ �������
   {
    //������ � ���������
    if (SectorOneType==0)//������� ����������� �������� �������
    {
     up_level=CreateSimplySectorForm.GetUpLevelFromSegment(SectorOne);//����� �� � ��������� ������� ������� ��������
     down_level=CreateSimplySectorForm.GetDownLevelFromSegment(SectorOne);//����� �� � ��������� ������ ������� ��������
    }
    if (SectorOneType==1)//������� ����������� ������� �����
    {
     up_level=CreateSimplyDoorForm.GetUpLevelFromSegment(SectorOne);//����� �� � ��������� ������� ������� ��������
     down_level=CreateSimplyDoorForm.GetDownLevelFromSegment(SectorOne);//����� �� � ��������� ������ ������� ��������
    }
    //������ � ���������
   }
   else
   {
    double up_level1,down_level1;
    double up_level2,down_level2;
    //����� ����� ����� ������� � ����� ������ �������
    //������ � ���������
    if (SectorOneType==0)//������� ����������� �������� �������
    {
     up_level1=CreateSimplySectorForm.GetUpLevelFromSegment(SectorOne);//����� �� � ��������� ������� ������� ��������
     down_level1=CreateSimplySectorForm.GetDownLevelFromSegment(SectorOne);//����� �� � ��������� ������ ������� ��������
    }
    if (SectorTwoType==0)//������� ����������� �������� �������
    {
     up_level2=CreateSimplySectorForm.GetUpLevelFromSegment(SectorTwo);//����� �� � ��������� ������� ������� ��������
     down_level2=CreateSimplySectorForm.GetDownLevelFromSegment(SectorTwo);//����� �� � ��������� ������ ������� ��������
    }
    if (SectorOneType==1)//������� ����������� ������� �����
    {
     up_level1=CreateSimplyDoorForm.GetUpLevelFromSegment(SectorOne);//����� �� � ��������� ������� ������� ��������
     down_level1=CreateSimplyDoorForm.GetDownLevelFromSegment(SectorOne);//����� �� � ��������� ������ ������� ��������
    }
    if (SectorTwoType==1)//������� ����������� ������� �����
    {
     up_level2=CreateSimplyDoorForm.GetUpLevelFromSegment(SectorTwo);//����� �� � ��������� ������� ������� ��������
     down_level2=CreateSimplyDoorForm.GetDownLevelFromSegment(SectorTwo);//����� �� � ��������� ������ ������� ��������
    }
    //������ � ���������
    up_level=up_level1;
    down_level=down_level1;
    if (up_level2<up_level) up_level=up_level2;
    if (down_level2>down_level) down_level=down_level2;
    if (up_level<=down_level) continue;//�� ��� �� ����� ������
   }
   //������ �������� �� ������ ����� �������� �����������
   SP.Normal.X=-(CreateSegmentForm.Segment[n].Y2-CreateSegmentForm.Segment[n].Y1);
   SP.Normal.Y=(CreateSegmentForm.Segment[n].X2-CreateSegmentForm.Segment[n].X1);
   SP.Normal.Z=0;
   SP.Texture=CreateSegmentForm.Segment[n].UpTexture;
   //����������� ������� �� ����, �.�. ���� ���������� ������� ��������� �����������
   SP.X[0]=CreateSegmentForm.Segment[n].X2;
   SP.Y[0]=CreateSegmentForm.Segment[n].Y2;
   SP.Z[0]=down_level;
   SP.X[1]=CreateSegmentForm.Segment[n].X2;
   SP.Y[1]=CreateSegmentForm.Segment[n].Y2;
   SP.Z[1]=up_level;
   SP.X[2]=CreateSegmentForm.Segment[n].X1;
   SP.Y[2]=CreateSegmentForm.Segment[n].Y1;
   SP.Z[2]=up_level;
   SP.X[3]=CreateSegmentForm.Segment[n].X1;
   SP.Y[3]=CreateSegmentForm.Segment[n].Y1;
   SP.Z[3]=down_level;
   SP.Segment=n;
   SP.X_Left_Up=CreateSegmentForm.Segment[n].X1;
   SP.Y_Left_Up=CreateSegmentForm.Segment[n].Y1;
   SP.Z_Left_Up=up_level;
   SP.Location=0;
   SP.BarrierType=0;
   if (CreateSegmentForm.Segment[n].Blend==1) SP.BarrierType=1;
   NewSurfaceSegment(&Surface,SP);
  }
  else//���� � ��� ����� �������
  {
   double SectorOne_up_level,SectorOne_down_level;
   double SectorTwo_up_level,SectorTwo_down_level;
   int SectorOneType=CreateSegmentForm.Segment[n].SectorOneType;
   int SectorOne=CreateSegmentForm.Segment[n].SectorOne;
   int SectorTwoType=CreateSegmentForm.Segment[n].SectorTwoType;
   int SectorTwo=CreateSegmentForm.Segment[n].SectorTwo;
   if (SectorOneType*SectorTwoType!=0)//��� ��� ������� ������� ����� ��� 0, �� ����� �������� �� ��, ��� ���� �� �������� ����� �������
   {
    MessageBox(NULL,"�� ���� �� �������� ��� ����� ������� �� ������� ������ !","������ ��������� �����������",MB_OK);
    DeleteAllSurface(&Surface);//������ ��� ������ �����������
    return;
   }
   //������ � ���������
   if (SectorOneType==0)//������ ������ �������
   {
    SectorOne_up_level=CreateSimplySectorForm.GetUpLevelFromFrontier(SectorOne);//����� �� � ��������� ������� ������� ����� �������
    SectorOne_down_level=CreateSimplySectorForm.GetDownLevelFromFrontier(SectorOne);//����� �� � ��������� ������ ������� ����� �������
   }
   if (SectorTwoType==0)//������ ������ �������
   {
    SectorTwo_up_level=CreateSimplySectorForm.GetUpLevelFromFrontier(SectorTwo);//����� �� � ��������� ������� ������� ����� �������
    SectorTwo_down_level=CreateSimplySectorForm.GetDownLevelFromFrontier(SectorTwo);//����� �� � ��������� ������ ������� ����� �������
   }
   if (SectorOneType==1)//������ ������ ������� �����
   {
    SectorOne_up_level=CreateSimplyDoorForm.GetUpLevelFromFrontier(SectorOne);//����� �� � ��������� ������� ������� ����� �������
    SectorOne_down_level=CreateSimplyDoorForm.GetDownLevelFromFrontier(SectorOne);//����� �� � ��������� ������ ������� ����� �������
   }
   if (SectorTwoType==1)//������ ������ ������� �����
   {
    SectorTwo_up_level=CreateSimplyDoorForm.GetUpLevelFromFrontier(SectorTwo);//����� �� � ��������� ������� ������� ����� �������
    SectorTwo_down_level=CreateSimplyDoorForm.GetDownLevelFromFrontier(SectorTwo);//����� �� � ��������� ������ ������� ����� �������
   }
   //������ � ���������
   //������ �������� �� ������ ���� ����� ������� ��� �����������(����,�������,���� �������� �����)
   //������ ������� ����� �������
   if (SectorOne_up_level!=SectorTwo_up_level)//�������� ����� ����
   {
    if (SectorOne_up_level>SectorTwo_up_level)//������ ������ ���� �������
    {
     //������ � ���������
     int pos=0;
     if (SectorOneType==0) pos=CreateSimplySectorForm.GetPosition(SectorOne,(float)(CreateSegmentForm.Segment[n].X1),(float)(CreateSegmentForm.Segment[n].Y1),(float)(CreateSegmentForm.Segment[n].X2),(float)(CreateSegmentForm.Segment[n].Y2));
     if (SectorOneType==1) pos=CreateSimplyDoorForm.GetPosition(SectorOne,(float)(CreateSegmentForm.Segment[n].X1),(float)(CreateSegmentForm.Segment[n].Y1),(float)(CreateSegmentForm.Segment[n].X2),(float)(CreateSegmentForm.Segment[n].Y2));
     //������ � ���������
     if (pos==0)
     {
      MessageBox(NULL,"�� ���������� � ����� ������� ������ �� ����� �������","������",MB_OK);
      return;
     }
     if (pos<0)//������ ������(�.�. �� ���������, ����������� ����� ����� ��� ����� �����������)
     {
      SP.X[3]=CreateSegmentForm.Segment[n].X2;
      SP.Y[3]=CreateSegmentForm.Segment[n].Y2;
      SP.Z[3]=SectorTwo_up_level;
      SP.X[2]=CreateSegmentForm.Segment[n].X2;
      SP.Y[2]=CreateSegmentForm.Segment[n].Y2;
      SP.Z[2]=SectorOne_up_level;
      SP.X[1]=CreateSegmentForm.Segment[n].X1;
      SP.Y[1]=CreateSegmentForm.Segment[n].Y1;
      SP.Z[1]=SectorOne_up_level;
      SP.X[0]=CreateSegmentForm.Segment[n].X1;
      SP.Y[0]=CreateSegmentForm.Segment[n].Y1;
      SP.Z[0]=SectorTwo_up_level;
      SP.Normal.X=(SP.Y[2]-SP.Y[1]);
      SP.Normal.Y=-(SP.X[2]-SP.X[1]);
      SP.Normal.Z=0;
      SP.Texture=CreateSegmentForm.Segment[n].UpTexture;
      SP.Segment=n;
      SP.X_Left_Up=CreateSegmentForm.Segment[n].X1;
      SP.Y_Left_Up=CreateSegmentForm.Segment[n].Y1;
      SP.Z_Left_Up=SectorOne_up_level;
      SP.Location=1;
      SP.BarrierType=0;
      if (SectorOneType==1 || SectorTwoType==1) SP.BarrierType=2;//�.�. �����
      NewSurfaceSegment(&Surface,SP);
     }
     else//������ �����(�.�. ����� ������ ����������� �����)
     {
      SP.X[3]=CreateSegmentForm.Segment[n].X1;
      SP.Y[3]=CreateSegmentForm.Segment[n].Y1;
      SP.Z[3]=SectorTwo_up_level;
      SP.X[2]=CreateSegmentForm.Segment[n].X1;
      SP.Y[2]=CreateSegmentForm.Segment[n].Y1;
      SP.Z[2]=SectorOne_up_level;
      SP.X[1]=CreateSegmentForm.Segment[n].X2;
      SP.Y[1]=CreateSegmentForm.Segment[n].Y2;
      SP.Z[1]=SectorOne_up_level;
      SP.X[0]=CreateSegmentForm.Segment[n].X2;
      SP.Y[0]=CreateSegmentForm.Segment[n].Y2;
      SP.Z[0]=SectorTwo_up_level;
      SP.Normal.X=(SP.Y[2]-SP.Y[1]);
      SP.Normal.Y=-(SP.X[2]-SP.X[1]);
      SP.Normal.Z=0;
      SP.Texture=CreateSegmentForm.Segment[n].UpTexture;
      SP.Segment=n;
      SP.X_Left_Up=CreateSegmentForm.Segment[n].X1;
      SP.Y_Left_Up=CreateSegmentForm.Segment[n].Y1;
      SP.Z_Left_Up=SectorOne_up_level;
      SP.Location=1;
      SP.BarrierType=0;
      if (SectorOneType==1 || SectorTwoType==1) SP.BarrierType=2;//�.�. �����
      NewSurfaceSegment(&Surface,SP);
     }
    }
    else//������ ������ ���� �������
    {
     int pos=0;
     //������ � ���������
     if (SectorTwoType==0) pos=CreateSimplySectorForm.GetPosition(SectorTwo,(float)(CreateSegmentForm.Segment[n].X1),(float)(CreateSegmentForm.Segment[n].Y1),(float)(CreateSegmentForm.Segment[n].X2),(float)(CreateSegmentForm.Segment[n].Y2));
     if (SectorTwoType==1) pos=CreateSimplyDoorForm.GetPosition(SectorTwo,(float)(CreateSegmentForm.Segment[n].X1),(float)(CreateSegmentForm.Segment[n].Y1),(float)(CreateSegmentForm.Segment[n].X2),(float)(CreateSegmentForm.Segment[n].Y2));
     //������ � ���������
     if (pos==0)
     {
      MessageBox(NULL,"�� ���������� � ����� ������� ������ �� ����� �������","������",MB_OK);
      DeleteAllSurface(&Surface);//������ ��� ������ �����������
      return;
     }
     if (pos<0)//������ ������(�.�. �� ���������, ����������� ����� ����� ��� ����� �����������)
     {
      SP.X[3]=CreateSegmentForm.Segment[n].X2;
      SP.Y[3]=CreateSegmentForm.Segment[n].Y2;
      SP.Z[3]=SectorOne_up_level;
      SP.X[2]=CreateSegmentForm.Segment[n].X2;
      SP.Y[2]=CreateSegmentForm.Segment[n].Y2;
      SP.Z[2]=SectorTwo_up_level;
      SP.X[1]=CreateSegmentForm.Segment[n].X1;
      SP.Y[1]=CreateSegmentForm.Segment[n].Y1;
      SP.Z[1]=SectorTwo_up_level;
      SP.X[0]=CreateSegmentForm.Segment[n].X1;
      SP.Y[0]=CreateSegmentForm.Segment[n].Y1;
      SP.Z[0]=SectorOne_up_level;
      SP.Normal.X=(SP.Y[2]-SP.Y[1]);
      SP.Normal.Y=-(SP.X[2]-SP.X[1]);
      SP.Normal.Z=0;
      SP.Texture=CreateSegmentForm.Segment[n].UpTexture;
      SP.Segment=n;
      SP.X_Left_Up=CreateSegmentForm.Segment[n].X1;
      SP.Y_Left_Up=CreateSegmentForm.Segment[n].Y1;
      SP.Z_Left_Up=SectorTwo_up_level;
      SP.Location=1;
      SP.BarrierType=0;
      if (SectorOneType==1 || SectorTwoType==1) SP.BarrierType=2;//�.�. �����
      NewSurfaceSegment(&Surface,SP);
     }
     else//������ �����(�.�. ����� ������ ����������� �����)
     {
      SP.X[3]=CreateSegmentForm.Segment[n].X1;
      SP.Y[3]=CreateSegmentForm.Segment[n].Y1;
      SP.Z[3]=SectorOne_up_level;
      SP.X[2]=CreateSegmentForm.Segment[n].X1;
      SP.Y[2]=CreateSegmentForm.Segment[n].Y1;
      SP.Z[2]=SectorTwo_up_level;
      SP.X[1]=CreateSegmentForm.Segment[n].X2;
      SP.Y[1]=CreateSegmentForm.Segment[n].Y2;
      SP.Z[1]=SectorTwo_up_level;
      SP.X[0]=CreateSegmentForm.Segment[n].X2;
      SP.Y[0]=CreateSegmentForm.Segment[n].Y2;
      SP.Z[0]=SectorOne_up_level;
      SP.Normal.X=(SP.Y[2]-SP.Y[1]);
      SP.Normal.Y=-(SP.X[2]-SP.X[1]);
      SP.Normal.Z=0;
      SP.Texture=CreateSegmentForm.Segment[n].UpTexture;
      SP.Segment=n;
      SP.X_Left_Up=CreateSegmentForm.Segment[n].X1;
      SP.Y_Left_Up=CreateSegmentForm.Segment[n].Y1;
      SP.Z_Left_Up=SectorTwo_up_level;
      SP.Location=1;
      SP.BarrierType=0;
      if (SectorOneType==1 || SectorTwoType==1) SP.BarrierType=2;//�.�. �����
      NewSurfaceSegment(&Surface,SP);
     }
    }
   }
   //������ ������ ����� �������
   if (SectorOne_down_level!=SectorTwo_down_level)//�������� ����� ����
   {
    if (SectorOne_down_level>SectorTwo_down_level)//������ ������ ���� �������
    {
     int pos=0; 
     //������ � ���������
     if (SectorOneType==0) pos=CreateSimplySectorForm.GetPosition(SectorOne,(float)(CreateSegmentForm.Segment[n].X1),(float)(CreateSegmentForm.Segment[n].Y1),(float)(CreateSegmentForm.Segment[n].X2),(float)(CreateSegmentForm.Segment[n].Y2));
     if (SectorOneType==1) pos=CreateSimplyDoorForm.GetPosition(SectorOne,(float)(CreateSegmentForm.Segment[n].X1),(float)(CreateSegmentForm.Segment[n].Y1),(float)(CreateSegmentForm.Segment[n].X2),(float)(CreateSegmentForm.Segment[n].Y2));
     //������ � ���������
     if (pos==0)
     {
      MessageBox(NULL,"�� ���������� � ����� ������� ������ �� ����� �������","������",MB_OK);
      DeleteAllSurface(&Surface);//������ ��� ������ �����������
      return;
     }
     if (pos<0)//������ ������(�.�. �� ���������, ����������� ����� ����� ��� ����� �����������)
     {
      SP.X[3]=CreateSegmentForm.Segment[n].X1;
      SP.Y[3]=CreateSegmentForm.Segment[n].Y1;
      SP.Z[3]=SectorTwo_down_level;
      SP.X[2]=CreateSegmentForm.Segment[n].X1;
      SP.Y[2]=CreateSegmentForm.Segment[n].Y1;
      SP.Z[2]=SectorOne_down_level;
      SP.X[1]=CreateSegmentForm.Segment[n].X2;
      SP.Y[1]=CreateSegmentForm.Segment[n].Y2;
      SP.Z[1]=SectorOne_down_level;
      SP.X[0]=CreateSegmentForm.Segment[n].X2;
      SP.Y[0]=CreateSegmentForm.Segment[n].Y2;
      SP.Z[0]=SectorTwo_down_level;
      SP.Normal.X=(SP.Y[2]-SP.Y[1]);
      SP.Normal.Y=-(SP.X[2]-SP.X[1]);
      SP.Normal.Z=0;
      SP.Texture=CreateSegmentForm.Segment[n].DownTexture;
      SP.Segment=n;
      SP.X_Left_Up=CreateSegmentForm.Segment[n].X1;
      SP.Y_Left_Up=CreateSegmentForm.Segment[n].Y1;
      SP.Z_Left_Up=SectorOne_down_level;
      SP.Location=2;
      SP.BarrierType=0;
      if (SectorOneType==1 || SectorTwoType==1) SP.BarrierType=2;//�.�. �����
      NewSurfaceSegment(&Surface,SP);
     }
     else//������ �����(�.�. ����� ������ ����������� �����)
     {
      SP.X[3]=CreateSegmentForm.Segment[n].X2;
      SP.Y[3]=CreateSegmentForm.Segment[n].Y2;
      SP.Z[3]=SectorTwo_down_level;
      SP.X[2]=CreateSegmentForm.Segment[n].X2;
      SP.Y[2]=CreateSegmentForm.Segment[n].Y2;
      SP.Z[2]=SectorOne_down_level;
      SP.X[1]=CreateSegmentForm.Segment[n].X1;
      SP.Y[1]=CreateSegmentForm.Segment[n].Y1;
      SP.Z[1]=SectorOne_down_level;
      SP.X[0]=CreateSegmentForm.Segment[n].X1;
      SP.Y[0]=CreateSegmentForm.Segment[n].Y1;
      SP.Z[0]=SectorTwo_down_level;
      SP.Normal.X=(SP.Y[2]-SP.Y[1]);
      SP.Normal.Y=-(SP.X[2]-SP.X[1]);
      SP.Normal.Z=0;
      SP.Texture=CreateSegmentForm.Segment[n].DownTexture;
      SP.Segment=n;
      SP.X_Left_Up=CreateSegmentForm.Segment[n].X1;
      SP.Y_Left_Up=CreateSegmentForm.Segment[n].Y1;
      SP.Z_Left_Up=SectorOne_down_level;
      SP.Location=2;
      SP.BarrierType=0;
      if (SectorOneType==1 || SectorTwoType==1) SP.BarrierType=2;//�.�. �����
      NewSurfaceSegment(&Surface,SP);
     }
    }
    else//������ ������ ���� �������
    {
     int pos=0;
     //������ � ���������
     if (SectorTwoType==0) pos=CreateSimplySectorForm.GetPosition(SectorTwo,(float)(CreateSegmentForm.Segment[n].X1),(float)(CreateSegmentForm.Segment[n].Y1),(float)(CreateSegmentForm.Segment[n].X2),(float)(CreateSegmentForm.Segment[n].Y2));
     if (SectorTwoType==1) pos=CreateSimplyDoorForm.GetPosition(SectorTwo,(float)(CreateSegmentForm.Segment[n].X1),(float)(CreateSegmentForm.Segment[n].Y1),(float)(CreateSegmentForm.Segment[n].X2),(float)(CreateSegmentForm.Segment[n].Y2));
     //������ � ���������
     if (pos==0)
     {
      MessageBox(NULL,"�� ���������� � ����� ������� ������ �� ����� �������","������",MB_OK);
      DeleteAllSurface(&Surface);//������ ��� ������ �����������
      return;
     }
     if (pos<0)//������ ������(�.�. �� ���������, ����������� ����� ����� ��� ����� �����������)
     {
      SP.X[3]=CreateSegmentForm.Segment[n].X1;
      SP.Y[3]=CreateSegmentForm.Segment[n].Y1;
      SP.Z[3]=SectorOne_down_level;
      SP.X[2]=CreateSegmentForm.Segment[n].X1;
      SP.Y[2]=CreateSegmentForm.Segment[n].Y1;
      SP.Z[2]=SectorTwo_down_level;
      SP.X[1]=CreateSegmentForm.Segment[n].X2;
      SP.Y[1]=CreateSegmentForm.Segment[n].Y2;
      SP.Z[1]=SectorTwo_down_level;
      SP.X[0]=CreateSegmentForm.Segment[n].X2;
      SP.Y[0]=CreateSegmentForm.Segment[n].Y2;
      SP.Z[0]=SectorOne_down_level;
      SP.Normal.X=(SP.Y[2]-SP.Y[1]);
      SP.Normal.Y=-(SP.X[2]-SP.X[1]);
      SP.Normal.Z=0;
      SP.Texture=CreateSegmentForm.Segment[n].DownTexture;
      SP.Segment=n;
      SP.X_Left_Up=CreateSegmentForm.Segment[n].X1;
      SP.Y_Left_Up=CreateSegmentForm.Segment[n].Y1;
      SP.Z_Left_Up=SectorTwo_down_level;
      SP.Location=2;
      SP.BarrierType=0;
      if (SectorOneType==1 || SectorTwoType==1) SP.BarrierType=2;//�.�. �����
      NewSurfaceSegment(&Surface,SP);
     }
     else//������ �����(�.�. ����� ������ ����������� �����)
     {
      SP.X[3]=CreateSegmentForm.Segment[n].X2;
      SP.Y[3]=CreateSegmentForm.Segment[n].Y2;
      SP.Z[3]=SectorOne_down_level;
      SP.X[2]=CreateSegmentForm.Segment[n].X2;
      SP.Y[2]=CreateSegmentForm.Segment[n].Y2;
      SP.Z[2]=SectorTwo_down_level;
      SP.X[1]=CreateSegmentForm.Segment[n].X1;
      SP.Y[1]=CreateSegmentForm.Segment[n].Y1;
      SP.Z[1]=SectorTwo_down_level;
      SP.X[0]=CreateSegmentForm.Segment[n].X1;
      SP.Y[0]=CreateSegmentForm.Segment[n].Y1;
      SP.Z[0]=SectorOne_down_level;
      SP.Normal.X=(SP.Y[2]-SP.Y[1]);
      SP.Normal.Y=-(SP.X[2]-SP.X[1]);
      SP.Normal.Z=0;
      SP.Texture=CreateSegmentForm.Segment[n].DownTexture;
      SP.Segment=n;
      SP.X_Left_Up=CreateSegmentForm.Segment[n].X1;
      SP.Y_Left_Up=CreateSegmentForm.Segment[n].Y1;
      SP.Z_Left_Up=SectorTwo_down_level;
      SP.Location=2;
      SP.BarrierType=0;
      if (SectorOneType==1 || SectorTwoType==1) SP.BarrierType=2;//�.�. �����
      NewSurfaceSegment(&Surface,SP);
     }
    }
   }
  }
 }
 //������� ����������� ���� � �������
 //������ � ���������
 for(n=0;n<KeyData.MaximumNumberOfSimplySector;n++)
 {
  CreateSimplySectorForm.GenerateFloor(n,&SCP);
  NewSurfaceSector(&Surface,SCP);
  CreateSimplySectorForm.GenerateCeiling(n,&SCP);
  NewSurfaceSector(&Surface,SCP);
 }
 for(n=0;n<KeyData.MaximumNumberOfSimplyDoor;n++)
 {
  CreateSimplyDoorForm.GenerateFloor(n,&SCP);
  NewSurfaceSector(&Surface,SCP);
  CreateSimplyDoorForm.GenerateCeiling(n,&SCP);
  NewSurfaceSector(&Surface,SCP);
 }
 //������ � ���������
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------
 //��������� �������� �� ��������� ������� ��������� ��������,����������� ���
 //���������� ���������� ��������� ������
 if (Surface==NULL) return;
 int SurfaceAmount=0;
 SURFACE *CurrentSurface=Surface;
 while(1)
 {
  SurfaceAmount++;
  if (CurrentSurface->Previous==NULL) break;
  CurrentSurface=CurrentSurface->Previous;
 }
 SURFACE *RenderSurface=new SURFACE[SurfaceAmount+1];
 CPolygon cPolygon_Stage;
 cPolygon_Stage.ClearAllPolygon();
 //� ��������� �� � ����� ���������
 SurfaceAmount=0;
 CurrentSurface=Surface;
 while(1)
 {
  RenderSurface[SurfaceAmount]=*(CurrentSurface);
  for(v=0;v<100;v++)
  {
   RenderSurface[SurfaceAmount].X[v]=CurrentSurface->X[v];
   RenderSurface[SurfaceAmount].Y[v]=CurrentSurface->Y[v];
   RenderSurface[SurfaceAmount].Z[v]=CurrentSurface->Z[v];
  }
  SPolygon sPolygon_Temporary;
  sPolygon_Temporary.PointAmount=CurrentSurface->Vertex;
  sPolygon_Temporary.sPoint_Array=new SPoint[sPolygon_Temporary.PointAmount+1];
  for(v=0;v<sPolygon_Temporary.PointAmount;v++)
  {
   sPolygon_Temporary.sPoint_Array[CurrentSurface->Vertex-v-1].X=CurrentSurface->X[v];
   sPolygon_Temporary.sPoint_Array[CurrentSurface->Vertex-v-1].Y=CurrentSurface->Y[v];
   sPolygon_Temporary.sPoint_Array[CurrentSurface->Vertex-v-1].Z=CurrentSurface->Z[v];
  }
  cPolygon_Stage.CreateNewPolygon(sPolygon_Temporary);
  delete(sPolygon_Temporary.sPoint_Array);
  SurfaceAmount++;
  if (CurrentSurface->Previous==NULL) break;
  CurrentSurface=CurrentSurface->Previous;
 }
 DeleteAllSurface(&Surface);//������ ��� ������ �����������
 //������ � ��� ������������ ��� ����������� ��� ����������
 double MaximumElement=KeyData.MaximumNumberOfLine;//����� ��� ����������� ���������
 MaximumElement+=KeyData.MaximumNumberOfSimplySector;
 MaximumElement+=KeyData.MaximumNumberOfSimplyDoor;
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------
 FILE *File=fopen(FileName,"w+b");
 if (File==NULL)
 {
  MessageBox(NULL,"�� ���� �������� ����.","������ ������",MB_OK|MB_ICONSTOP);
  delete(RenderSurface);
  return;
 }
 //������ ���������
 SaveFloat(File,1.0);
 //�������� ��������� ����� �� �����
 fprintf(File,"LIGHTINGS STRUCTURE");
 SaveInt(File,KeyData.MaximumNumberOfLighting);
 for(n=0;n<KeyData.MaximumNumberOfLighting;n++) CreateLightingForm.SaveLightingFromRender(File,n);
 SaveFloat(File,(float)SetUp.Constant_Attenuation);
 SaveFloat(File,(float)SetUp.Linear_Attenuation);
 SaveFloat(File,(float)SetUp.Quadric_Attenuation);
 SaveChar(File,SetUp.R_Ambient);
 SaveChar(File,SetUp.G_Ambient);
 SaveChar(File,SetUp.B_Ambient);
 LIGHT Light(RenderSurface,SurfaceAmount);//�������� ������ ��� ������� ������������ � ������� ��� ��� �����������
 //-----------------------------------------------------------------------------
 //������� ���������� ��������� �� �����
 fprintf(File,"SEGMENTS STRUCTURE");
 SaveInt(File,KeyData.MaximumNumberOfLine);
 //������ �������� ��� ��������
 for(n=0;n<KeyData.MaximumNumberOfLine;n++)
 { 
  Progress.Progress=(float)((float)(n+1)/(float)(MaximumElement));
  InvalidateRect(KeyData.hWndProgress,NULL,FALSE);
  MSG msg;
  while (PeekMessage(&msg,NULL,0,0,PM_REMOVE))//��������� ��������� Windows
  {
   TranslateMessage(&msg);
   DispatchMessage(&msg);
  }
  CreateSegmentForm.SaveSegmentFromRender(File,n);//�������� ��������� ��������
  //�������� ��� � ��������, �� ������� ����� ����� �����������,� ������� �� ���������
  //����� ����� ������������ ��� ����
  int sfc=0;//����� ������������ ��� ������� ��������
  for(m=0;m<SurfaceAmount;m++)
  {
   if (RenderSurface[m].Segment==n) sfc++;
  }
  SaveInt(File,sfc);//�������� ��� �����
  for(m=0;m<SurfaceAmount;m++)
  {
   if (RenderSurface[m].Segment==n)//��� ����������� �������� ������ ��������
   {
    //�������� � ���������
    SaveInt(File,RenderSurface[m].Location);
    //�������� � �������
    SaveFloat(File,(float)(-RenderSurface[m].Normal.X));
    SaveFloat(File,(float)(RenderSurface[m].Normal.Z));
    SaveFloat(File,(float)(-RenderSurface[m].Normal.Y));
    //� ������ ��������
    CPolygon cPolygon_Fragment;
    cPolygon_Fragment.ClearAllPolygon();
    if (m>=cPolygon_Stage.AmountOfPolygons)
    {
     MessageBox(NULL,"Error","",MB_OK);
     continue;
    }
    //������ ���� ������ ���������, ����� ����� ����� �������� ��� �����������
    //��� ������� ��������� ����� � ������ ��� ��������� �����
    Light.SetCurrentSurface(m,n,-1,-1,&cPolygon_Stage);
    //�������� ����� � ������ ���������� �����
    SaveChar(File,Light.LightingAmount);
    for(l=0;l<Light.LightingAmount;l++) SaveInt(File,Light.LightingNumber[l]);
    //�������� �������������� ��������� �����������
    if (RenderSurface[m].Location==1 || RenderSurface[m].Location==0)
    {
     SaveChar(File,CreateSegmentForm.Segment[n].UpEmissionR);
     SaveChar(File,CreateSegmentForm.Segment[n].UpEmissionG);
     SaveChar(File,CreateSegmentForm.Segment[n].UpEmissionB);
    }
    if (RenderSurface[m].Location==2)
    {
     SaveChar(File,CreateSegmentForm.Segment[n].DownEmissionR);
     SaveChar(File,CreateSegmentForm.Segment[n].DownEmissionG);
     SaveChar(File,CreateSegmentForm.Segment[n].DownEmissionB);
    }
    //�� � ������ ��������
    SPolygon sPolygon_Basic=cPolygon_Stage.GetPolygonForIndex(m);
    cPolygon_Fragment.CreateNewPolygon(sPolygon_Basic);//�������� ������ ����
    BOOL LightingEnable[8];
    LightingEnable[0]=TRUE;//��������� ����� ��� ��������
    LightingEnable[1]=TRUE;
    LightingEnable[2]=TRUE;
    LightingEnable[3]=TRUE;
    LightingEnable[4]=TRUE;
    LightingEnable[5]=TRUE;
    LightingEnable[6]=TRUE;
    LightingEnable[7]=TRUE;
    cPolygon_Fragment.SetPolygonLightingEnableForIndex(0,LightingEnable);
    for(l=0;l<Light.LightingAmount;l++)//��������, ���������� �������
    {
     //���������, ���� �� ����� �������, ��� ��������� ��������� ��������
     for(k=0;k<cPolygon_Fragment.GetAmountOfPolygons();k++)//��� ������� ��������� ������� ���� � ������ ���-���������
     {
      for(r=0;r<Light.SphereMaxSurfaceFromLight[l];r++)//�������, ��������� ����
      {
       u=Light.SphereFromLight[l][r];
       if (u==m) continue;//���� �� ���� ���� �� �����������
       SPolygon sPolygon_ShadowSource=cPolygon_Stage.GetPolygonForIndex(u);
       CPolygon cPolygon_Temporary;
       BOOL EnableShadow=GenerateShadow(sPolygon_ShadowSource,cPolygon_Fragment.GetPolygonForIndex(k),Light.sPoint_Lighting[l],&cPolygon_Temporary);
       if (EnableShadow==TRUE && cPolygon_Temporary.GetAmountOfPolygons()==1)//���� �������� � ����
       {
        SPolygon sPolygon=cPolygon_Fragment.GetPolygonForIndex(k);
        sPolygon.LightingEnable[l]=FALSE;
        cPolygon_Fragment.SetPolygonLightingEnableForIndex(k,sPolygon.LightingEnable);
        cPolygon_Temporary.ClearAllPolygon();
        break;
       }
       cPolygon_Temporary.ClearAllPolygon();
      }
     }
     for(r=0;r<Light.SphereMaxSurfaceFromLight[l];r++)//�������, ��������� ����
     {
      u=Light.SphereFromLight[l][r];
      if (u==m) continue;//���� �� ���� ���� �� �����������
      SPolygon sPolygon_ShadowSource=cPolygon_Stage.GetPolygonForIndex(u);
      CPolygon cPolygon_NewFragment;
      cPolygon_NewFragment.ClearAllPolygon();
      for(k=0;k<cPolygon_Fragment.GetAmountOfPolygons();k++)//��� ������� ��������� ������� ���� � ������ ���-���������
      {
       SPolygon sPolygon_F=cPolygon_Fragment.GetPolygonForIndex(k);
       if (sPolygon_F.LightingEnable[l]==FALSE)
       {
        cPolygon_NewFragment.CreateNewPolygon(sPolygon_F);
        continue;
       }
       CPolygon cPolygon_Temporary;
       BOOL EnableShadow=GenerateShadow(sPolygon_ShadowSource,sPolygon_F,Light.sPoint_Lighting[l],&cPolygon_Temporary);
       //��������� ��������� �����
       for(v=0;v<cPolygon_Temporary.GetAmountOfPolygons();v++)
       {
        SPolygon sPolygon=cPolygon_Fragment.GetPolygonForIndex(k);
        cPolygon_Temporary.SetPolygonLightingEnableForIndex(v,sPolygon.LightingEnable);
        if (v==0 && EnableShadow==TRUE)//���� ���� ����
        {
         sPolygon.LightingEnable[l]=FALSE;
         cPolygon_Temporary.SetPolygonLightingEnableForIndex(v,sPolygon.LightingEnable);
        }
        sPolygon=cPolygon_Temporary.GetPolygonForIndex(v);
        cPolygon_NewFragment.CreateNewPolygon(sPolygon);
       }
       cPolygon_Temporary.ClearAllPolygon();
      }
      cPolygon_Fragment.ClearAllPolygon();
      for(k=0;k<cPolygon_NewFragment.GetAmountOfPolygons();k++)
      {
       SPolygon sPolygon=cPolygon_NewFragment.GetPolygonForIndex(k);
       cPolygon_Fragment.CreateNewPolygon(sPolygon);
      }
      cPolygon_NewFragment.ClearAllPolygon();
     }
    }
    //�������� ��� ��������� ���������
    SaveInt(File,cPolygon_Fragment.GetAmountOfPolygons());
    for(u=0;u<cPolygon_Fragment.GetAmountOfPolygons();u++)
    {
     SPolygon sPolygon=cPolygon_Fragment.GetPolygonForIndex(u);
     //�������� ���������� ���������� ����� ��� ������� ��������
     unsigned char enablelighting=0;
     int set=1;
     for(l=0;l<Light.LightingAmount;l++,set*=2)
     {
      if (sPolygon.LightingEnable[l]==TRUE) enablelighting|=set;
     }
     SaveChar(File,enablelighting);
     SaveInt(File,sPolygon.PointAmount);
     for(k=0;k<sPolygon.PointAmount;k++) 
     {
      SaveFloat(File,-(float)sPolygon.sPoint_Array[k].X);
      SaveFloat(File,(float)sPolygon.sPoint_Array[k].Z);
      SaveFloat(File,-(float)sPolygon.sPoint_Array[k].Y);
      //�������� ���������� ����������
      double dx=(RenderSurface[m].X_Left_Up-sPolygon.sPoint_Array[k].X);
      double dy=(RenderSurface[m].Y_Left_Up-sPolygon.sPoint_Array[k].Y);
      double tlen=sqrt(dx*dx+dy*dy);
      double tu=tlen/128.0;
      double tv=(RenderSurface[m].Z_Left_Up-sPolygon.sPoint_Array[k].Z)/128.0;
      SelectTextureForm.CreateTextureCoord(RenderSurface[m].Texture,&tu,&tv);
      SaveFloat(File,(float)(tu));
      SaveFloat(File,(float)(tv));
     }
    }
    cPolygon_Fragment.ClearAllPolygon();
   }
  }
 }
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------
 //������� ���������� ������� �������� �� �����
 fprintf(File,"SIMPLYSECTORS STRUCTURE");
 SaveInt(File,KeyData.MaximumNumberOfSimplySector);
 //������ �������� ��� �������
 for(n=0;n<KeyData.MaximumNumberOfSimplySector;n++)
 { 
  Progress.Progress=(float)((float)(1+n+KeyData.MaximumNumberOfLine)/(float)(MaximumElement));
  InvalidateRect(KeyData.hWndProgress,NULL,FALSE);
  MSG msg;
  while (PeekMessage(&msg,NULL,0,0,PM_REMOVE))//��������� ��������� Windows
  {
   TranslateMessage(&msg);
   DispatchMessage(&msg);
  }
  CreateSimplySectorForm.SaveSectorFromRender(File,n);//�������� ��������� �������
  //�������� ��� � ��������, �� ������� ����� ����� �����������,� ������� �� ���������
  //����� ������������ ��� ���� 2
  for(m=0;m<SurfaceAmount;m++)
  {
   if (RenderSurface[m].SectorType==0 && RenderSurface[m].Sector==n)//��� ���� �����������
   {
    //�������� � ���������
    SaveInt(File,RenderSurface[m].Location);
    //�������� � �������
    SaveFloat(File,(float)(-RenderSurface[m].Normal.X));
    SaveFloat(File,(float)(RenderSurface[m].Normal.Z));
    SaveFloat(File,(float)(-RenderSurface[m].Normal.Y));
    //� ������ ��������
    CPolygon cPolygon_Fragment;
    cPolygon_Fragment.ClearAllPolygon();
    if (m>=cPolygon_Stage.AmountOfPolygons)
    {
     MessageBox(NULL,"Error","",MB_OK);
     continue;
    }
    //������ ���� ������ ���������, ����� ����� ����� �������� ��� �����������
    //��� ������� ��������� ����� � ������ ��� ��������� �����
    Light.SetCurrentSurface(m,-1,RenderSurface[m].Sector,RenderSurface[m].SectorType,&cPolygon_Stage);
    //�������� ����� � ������ ���������� �����
    SaveChar(File,Light.LightingAmount);
    for(l=0;l<Light.LightingAmount;l++) SaveInt(File,Light.LightingNumber[l]);
    //�������� �������������� ��������� �����������
    if (RenderSurface[m].Location==1 || RenderSurface[m].Location==0)
    {
     SaveChar(File,CreateSimplySectorForm.Sector[n].UpEmissionR);
     SaveChar(File,CreateSimplySectorForm.Sector[n].UpEmissionG);
     SaveChar(File,CreateSimplySectorForm.Sector[n].UpEmissionB);
    }
    if (RenderSurface[m].Location==2)
    {
     SaveChar(File,CreateSimplySectorForm.Sector[n].DownEmissionR);
     SaveChar(File,CreateSimplySectorForm.Sector[n].DownEmissionG);
     SaveChar(File,CreateSimplySectorForm.Sector[n].DownEmissionB);
    }
    SPolygon sPolygon_Basic=cPolygon_Stage.GetPolygonForIndex(m);
    cPolygon_Fragment.CreateNewPolygon(sPolygon_Basic);//�������� ������ ����
    BOOL LightingEnable[8];
    LightingEnable[0]=TRUE;//��������� ����� ��� ��������
    LightingEnable[1]=TRUE;
    LightingEnable[2]=TRUE;
    LightingEnable[3]=TRUE;
    LightingEnable[4]=TRUE;
    LightingEnable[5]=TRUE;
    LightingEnable[6]=TRUE;
    LightingEnable[7]=TRUE;
    cPolygon_Fragment.SetPolygonLightingEnableForIndex(0,LightingEnable);
    for(l=0;l<Light.LightingAmount;l++)//��������, ���������� �������
    {
     //���������, ���� �� ����� �������, ��� ��������� ��������� ��������
     for(k=0;k<cPolygon_Fragment.GetAmountOfPolygons();k++)//��� ������� ��������� ������� ���� � ������ ���-���������
     {
      for(r=0;r<Light.SphereMaxSurfaceFromLight[l];r++)//�������, ��������� ����
      {
       u=Light.SphereFromLight[l][r];
       if (u==m) continue;//���� �� ���� ���� �� �����������
       SPolygon sPolygon_ShadowSource=cPolygon_Stage.GetPolygonForIndex(u);
       CPolygon cPolygon_Temporary;
       BOOL EnableShadow=GenerateShadow(sPolygon_ShadowSource,cPolygon_Fragment.GetPolygonForIndex(k),Light.sPoint_Lighting[l],&cPolygon_Temporary);
       if (EnableShadow==TRUE && cPolygon_Temporary.GetAmountOfPolygons()==1)//���� �������� � ����
       {
        SPolygon sPolygon=cPolygon_Fragment.GetPolygonForIndex(k);
        sPolygon.LightingEnable[l]=FALSE;
        cPolygon_Fragment.SetPolygonLightingEnableForIndex(k,sPolygon.LightingEnable);
        cPolygon_Temporary.ClearAllPolygon();
        break;
       }
       cPolygon_Temporary.ClearAllPolygon();
      }
     }
     for(r=0;r<Light.SphereMaxSurfaceFromLight[l];r++)//�������, ��������� ����
     {
      u=Light.SphereFromLight[l][r];
      if (u==m) continue;//���� �� ���� ���� �� �����������
      SPolygon sPolygon_ShadowSource=cPolygon_Stage.GetPolygonForIndex(u);
      CPolygon cPolygon_NewFragment;
      cPolygon_NewFragment.ClearAllPolygon();
      for(k=0;k<cPolygon_Fragment.GetAmountOfPolygons();k++)//��� ������� ��������� ������� ���� � ������ ���-���������
      {
       SPolygon sPolygon_F=cPolygon_Fragment.GetPolygonForIndex(k);
       if (sPolygon_F.LightingEnable[l]==FALSE)
       {
        cPolygon_NewFragment.CreateNewPolygon(sPolygon_F);
        continue;
       }
       CPolygon cPolygon_Temporary;
       BOOL EnableShadow=GenerateShadow(sPolygon_ShadowSource,sPolygon_F,Light.sPoint_Lighting[l],&cPolygon_Temporary);
       //��������� ��������� �����
       for(v=0;v<cPolygon_Temporary.GetAmountOfPolygons();v++)
       {
        SPolygon sPolygon=cPolygon_Fragment.GetPolygonForIndex(k);
        cPolygon_Temporary.SetPolygonLightingEnableForIndex(v,sPolygon.LightingEnable);
        if (v==0 && EnableShadow==TRUE)//���� ���� ����
        {
         sPolygon.LightingEnable[l]=FALSE;
         cPolygon_Temporary.SetPolygonLightingEnableForIndex(v,sPolygon.LightingEnable);
        }
        sPolygon=cPolygon_Temporary.GetPolygonForIndex(v);
        cPolygon_NewFragment.CreateNewPolygon(sPolygon);
       }
       cPolygon_Temporary.ClearAllPolygon();
      }
      cPolygon_Fragment.ClearAllPolygon();
      for(k=0;k<cPolygon_NewFragment.GetAmountOfPolygons();k++)
      {
       SPolygon sPolygon=cPolygon_NewFragment.GetPolygonForIndex(k);
       cPolygon_Fragment.CreateNewPolygon(sPolygon);
      }
      cPolygon_NewFragment.ClearAllPolygon();
     }
    }
    //�������� ��� ��������� ���������
    SaveInt(File,cPolygon_Fragment.GetAmountOfPolygons());
    for(u=0;u<cPolygon_Fragment.GetAmountOfPolygons();u++)
    {
     SPolygon sPolygon=cPolygon_Fragment.GetPolygonForIndex(u);
     //�������� ���������� ���������� ����� ��� ������� ��������
     unsigned char enablelighting=0;
     int set=1;
     for(l=0;l<Light.LightingAmount;l++,set*=2)
     {
      if (sPolygon.LightingEnable[l]==TRUE) enablelighting|=set;
     }
     SaveChar(File,enablelighting);
     SaveInt(File,sPolygon.PointAmount);
     for(k=0;k<sPolygon.PointAmount;k++) 
     {
      SaveFloat(File,-(float)sPolygon.sPoint_Array[k].X);
      SaveFloat(File,(float)sPolygon.sPoint_Array[k].Z);
      SaveFloat(File,-(float)sPolygon.sPoint_Array[k].Y);
      //�������� ���������� ����������
      double tu=(sPolygon.sPoint_Array[k].X)/128.0;
      double tv=(sPolygon.sPoint_Array[k].Y)/128.0;
      SelectTextureForm.CreateTextureCoord(RenderSurface[m].Texture,&tu,&tv);
      SaveFloat(File,(float)(tu));
      SaveFloat(File,(float)(tv));
     }
    }
    cPolygon_Fragment.ClearAllPolygon();
   }
  }
 }
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------
 //������� ���������� ������� ������ �� �����
 fprintf(File,"SIMPLYDOORS STRUCTURE");
 SaveInt(File,KeyData.MaximumNumberOfSimplyDoor);
 //������ �������� ��� �������
 for(n=0;n<KeyData.MaximumNumberOfSimplyDoor;n++)
 { 
  Progress.Progress=(float)((float)(1+n+KeyData.MaximumNumberOfLine+KeyData.MaximumNumberOfSimplySector)/(float)(MaximumElement));
  InvalidateRect(KeyData.hWndProgress,NULL,FALSE);
  MSG msg;
  while (PeekMessage(&msg,NULL,0,0,PM_REMOVE))//��������� ��������� Windows
  {
   TranslateMessage(&msg);
   DispatchMessage(&msg);
  }
  CreateSimplyDoorForm.SaveSectorFromRender(File,n);//�������� ��������� �������
  //�������� ��� � ��������, �� ������� ����� ����� �����������,� ������� �� ���������
  //����� ������������ ��� ���� 2
  for(m=0;m<SurfaceAmount;m++)
  {
   if (RenderSurface[m].SectorType==1 && RenderSurface[m].Sector==n)//��� ���� �����������
   {
    //�������� � ���������
    SaveInt(File,RenderSurface[m].Location);
    //�������� � �������
    SaveFloat(File,(float)(-RenderSurface[m].Normal.X));
    SaveFloat(File,(float)(RenderSurface[m].Normal.Z));
    SaveFloat(File,(float)(-RenderSurface[m].Normal.Y));
    //� ������ ��������
    CPolygon cPolygon_Fragment;
    cPolygon_Fragment.ClearAllPolygon();
    if (m>=cPolygon_Stage.AmountOfPolygons)
    {
     MessageBox(NULL,"Error","",MB_OK);
     continue;
    }
    //������ ���� ������ ���������, ����� ����� ����� �������� ��� �����������
    //��� ������� ��������� ����� � ������ ��� ��������� �����
    Light.SetCurrentSurface(m,-1,RenderSurface[m].Sector,RenderSurface[m].SectorType,&cPolygon_Stage);
    //�������� ����� � ������ ���������� �����
    SaveChar(File,Light.LightingAmount);
    for(l=0;l<Light.LightingAmount;l++) SaveInt(File,Light.LightingNumber[l]);
    //�������� �������������� ��������� �����������
    if (RenderSurface[m].Location==1)
    {
     SaveChar(File,CreateSimplyDoorForm.Sector[n].UpEmissionR);
     SaveChar(File,CreateSimplyDoorForm.Sector[n].UpEmissionG);
     SaveChar(File,CreateSimplyDoorForm.Sector[n].UpEmissionB);
    }
    if (RenderSurface[m].Location==2)
    {
     SaveChar(File,CreateSimplyDoorForm.Sector[n].DownEmissionR);
     SaveChar(File,CreateSimplyDoorForm.Sector[n].DownEmissionG);
     SaveChar(File,CreateSimplyDoorForm.Sector[n].DownEmissionB);
    }
    SPolygon sPolygon_Basic=cPolygon_Stage.GetPolygonForIndex(m);
    cPolygon_Fragment.CreateNewPolygon(sPolygon_Basic);//�������� ������ ����
    BOOL LightingEnable[8];
    LightingEnable[0]=TRUE;//��������� ����� ��� ��������
    LightingEnable[1]=TRUE;
    LightingEnable[2]=TRUE;
    LightingEnable[3]=TRUE;
    LightingEnable[4]=TRUE;
    LightingEnable[5]=TRUE;
    LightingEnable[6]=TRUE;
    LightingEnable[7]=TRUE;
    cPolygon_Fragment.SetPolygonLightingEnableForIndex(0,LightingEnable);
    for(l=0;l<Light.LightingAmount;l++)//��������, ���������� �������
    {
     //���������, ���� �� ����� �������, ��� ��������� ��������� ��������
     for(k=0;k<cPolygon_Fragment.GetAmountOfPolygons();k++)//��� ������� ��������� ������� ���� � ������ ���-���������
     {
      for(r=0;r<Light.SphereMaxSurfaceFromLight[l];r++)//�������, ��������� ����
      {
       u=Light.SphereFromLight[l][r];
       if (u==m) continue;//���� �� ���� ���� �� �����������
       SPolygon sPolygon_ShadowSource=cPolygon_Stage.GetPolygonForIndex(u);
       CPolygon cPolygon_Temporary;
       BOOL EnableShadow=GenerateShadow(sPolygon_ShadowSource,cPolygon_Fragment.GetPolygonForIndex(k),Light.sPoint_Lighting[l],&cPolygon_Temporary);
       if (EnableShadow==TRUE && cPolygon_Temporary.GetAmountOfPolygons()==1)//���� �������� � ����
       {
        SPolygon sPolygon=cPolygon_Fragment.GetPolygonForIndex(k);
        sPolygon.LightingEnable[l]=FALSE;
        cPolygon_Fragment.SetPolygonLightingEnableForIndex(k,sPolygon.LightingEnable);
        cPolygon_Temporary.ClearAllPolygon();
        break;
       }
       cPolygon_Temporary.ClearAllPolygon();
      }
     }
     for(r=0;r<Light.SphereMaxSurfaceFromLight[l];r++)//�������, ��������� ����
     {
      u=Light.SphereFromLight[l][r];
      if (u==m) continue;//���� �� ���� ���� �� �����������
      SPolygon sPolygon_ShadowSource=cPolygon_Stage.GetPolygonForIndex(u);
      CPolygon cPolygon_NewFragment;
      cPolygon_NewFragment.ClearAllPolygon();
      for(k=0;k<cPolygon_Fragment.GetAmountOfPolygons();k++)//��� ������� ��������� ������� ���� � ������ ���-���������
      {
       SPolygon sPolygon_F=cPolygon_Fragment.GetPolygonForIndex(k);
       if (sPolygon_F.LightingEnable[l]==FALSE)
       {
        cPolygon_NewFragment.CreateNewPolygon(sPolygon_F);
        continue;
       }
       CPolygon cPolygon_Temporary;
       BOOL EnableShadow=GenerateShadow(sPolygon_ShadowSource,sPolygon_F,Light.sPoint_Lighting[l],&cPolygon_Temporary);
       //��������� ��������� �����
       for(v=0;v<cPolygon_Temporary.GetAmountOfPolygons();v++)
       {
        SPolygon sPolygon=cPolygon_Fragment.GetPolygonForIndex(k);
        cPolygon_Temporary.SetPolygonLightingEnableForIndex(v,sPolygon.LightingEnable);
        if (v==0 && EnableShadow==TRUE)//���� ���� ����
        {
         sPolygon.LightingEnable[l]=FALSE;
         cPolygon_Temporary.SetPolygonLightingEnableForIndex(v,sPolygon.LightingEnable);
        }
        sPolygon=cPolygon_Temporary.GetPolygonForIndex(v);
        cPolygon_NewFragment.CreateNewPolygon(sPolygon);
       }
       cPolygon_Temporary.ClearAllPolygon();
      }
      cPolygon_Fragment.ClearAllPolygon();
      for(k=0;k<cPolygon_NewFragment.GetAmountOfPolygons();k++)
      {
       SPolygon sPolygon=cPolygon_NewFragment.GetPolygonForIndex(k);
       cPolygon_Fragment.CreateNewPolygon(sPolygon);
      }
      cPolygon_NewFragment.ClearAllPolygon();
     }
    }
    //�������� ��� ��������� ���������
    SaveInt(File,cPolygon_Fragment.GetAmountOfPolygons());
    for(u=0;u<cPolygon_Fragment.GetAmountOfPolygons();u++)
    {
     SPolygon sPolygon=cPolygon_Fragment.GetPolygonForIndex(u);
     //�������� ���������� ���������� ����� ��� ������� ��������
     unsigned char enablelighting=0;
     int set=1;
     for(l=0;l<Light.LightingAmount;l++,set*=2)
     {
      if (sPolygon.LightingEnable[l]==TRUE) enablelighting|=set;
     }
     SaveChar(File,enablelighting);
     SaveInt(File,sPolygon.PointAmount);
     for(k=0;k<sPolygon.PointAmount;k++) 
     {
      SaveFloat(File,-(float)sPolygon.sPoint_Array[k].X);
      SaveFloat(File,(float)sPolygon.sPoint_Array[k].Z+RenderSurface[m].Dz);
      SaveFloat(File,-(float)sPolygon.sPoint_Array[k].Y);
      //�������� ���������� ����������
      double tu=(sPolygon.sPoint_Array[k].X)/128.0;
      double tv=(sPolygon.sPoint_Array[k].Y)/128.0;
      SelectTextureForm.CreateTextureCoord(RenderSurface[m].Texture,&tu,&tv);
      SaveFloat(File,(float)(tu));
      SaveFloat(File,(float)(tv));
     }
    }
    cPolygon_Fragment.ClearAllPolygon();
   }
  }
 }
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------
 //�������� ��������� �������
 StartPosForm.SaveStartPositionFromRender(File);
 //�������� ��������� ���������� ���������
 fprintf(File,"GLOBAL FOG STRUCTURE");
 SaveFloat(File,(float)(((float)(SetUp.R_Fog)/255.0)));
 SaveFloat(File,(float)(((float)(SetUp.G_Fog)/255.0)));
 SaveFloat(File,(float)(((float)(SetUp.B_Fog)/255.0)));
 SaveFloat(File,(float)(((float)(SetUp.Fog_Density)/1000000000.0)));
 SaveChar(File,SetUp.Fog_Enable);
 fclose(File);
  
 cPolygon_Stage.ClearAllPolygon();
 delete(RenderSurface);
}
 

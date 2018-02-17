#include "shadow.h"

int GetPointPositionInPlaneXZ(SPoint sPoint_A,SPoint sPoint_B,SPoint sPoint)
{
 double p=sPoint.X*(sPoint_A.Z-sPoint_B.Z)-sPoint.Z*(sPoint_A.X-sPoint_B.X)+sPoint_A.X*sPoint_B.Z-sPoint_A.Z*sPoint_B.X;
 if (p<=-S_EPS2) return(-1);
 if (p>=S_EPS2) return(1);
 return(0);
}
int GetPointPositionPlane(SPoint sPoint_A,SPoint sPoint_Plane,SVector sVector_Normal)
{
 double p=sVector_Normal.X*(sPoint_A.X-sPoint_Plane.X)+sVector_Normal.Y*(sPoint_A.Y-sPoint_Plane.Y)+sVector_Normal.Z*(sPoint_A.Z-sPoint_Plane.Z);
 if (p<=-S_EPS2) return(-1);
 if (p>=S_EPS2) return(1);
 return(0);
}
BOOL IsPointInPolygonXZ(SPoint sPoint,SPolygon sPolygon)
{
 int OldPosition=0;
 for(int v=0;v<sPolygon.PointAmount;v++)
 {
  int v1=v;//текущая точка
  int v2=v+1;//следующая точка
  if (v2>=sPolygon.PointAmount) v2-=sPolygon.PointAmount;
  int Position=GetPointPositionInPlaneXZ(sPolygon.sPoint_Array[v1],sPolygon.sPoint_Array[v2],sPoint);
  if (Position==0) continue;
  if (OldPosition==0) OldPosition=Position;
  if (OldPosition!=Position) return(FALSE);
 }
 return(TRUE);
}
BOOL GetPieceIntersectionInPlaneXZ(SPoint A,SPoint B,SPoint C,SPoint D,SPoint *sPointReturn)
{
 double z=(B.X-A.X)*(D.Z-C.Z)-(B.Z-A.Z)*(D.X-C.X);
 if (fabs(z)<=S_EPS1) return(FALSE);
 double r=(A.Z-C.Z)*(D.X-C.X)-(A.X-C.X)*(D.Z-C.Z);
 double s=(A.Z-C.Z)*(B.X-A.X)-(A.X-C.X)*(B.Z-A.Z);
 //уменьшим погрешности вычислений
 if (z<0)
 {
  r=-r;
  s=-s;
  z=-z;
 }
 if (r<0 || r>z) return(FALSE);
 if (s<0 || s>z) return(FALSE);
 r/=z;
 s/=z;
 sPointReturn->X=(double)(A.X+r*(B.X-A.X));
 sPointReturn->Z=(double)(A.Z+r*(B.Z-A.Z));
 sPointReturn->Y=0;
 return(TRUE);
}
BOOL GetLineIntersectionPieceInPlaneXZ(SPoint A,SPoint B,SPoint C,SPoint D,SPoint *sPointReturn)
{
 double z=(B.X-A.X)*(D.Z-C.Z)-(B.Z-A.Z)*(D.X-C.X);
 if (fabs(z)<=S_EPS1) return(FALSE);
 double r=(A.Z-C.Z)*(D.X-C.X)-(A.X-C.X)*(D.Z-C.Z);
 double s=(A.Z-C.Z)*(B.X-A.X)-(A.X-C.X)*(B.Z-A.Z);
 //уменьшим погрешности вычислений
 if (z<0)
 {
  r=-r;
  s=-s;
  z=-z;
 }
 if (s<0 || s>z) return(FALSE);
 r/=z;
 s/=z;
 sPointReturn->X=(double)(A.X+r*(B.X-A.X));
 sPointReturn->Z=(double)(A.Z+r*(B.Z-A.Z));
 sPointReturn->Y=0;
 return(TRUE);
}
BOOL GetLineIntersectionPlane(SPoint sPoint_A,SPoint sPoint_B,SPoint sPoint_Plane,SVector sVector_Normal,int mode,SPoint* sPointReturn)
{
 double A=sVector_Normal.X;
 double B=sVector_Normal.Y;
 double C=sVector_Normal.Z;
 double lx=sPoint_B.X-sPoint_A.X;
 double ly=sPoint_B.Y-sPoint_A.Y;
 double lz=sPoint_B.Z-sPoint_A.Z;
 double E=(A*lx+B*ly+C*lz);
 if (fabs(E)<=S_EPS1) return(FALSE);//нет пересечения
 double D=-(sPoint_Plane.X*A+sPoint_Plane.Y*B+sPoint_Plane.Z*C);
 double t=-(D+A*sPoint_A.X+B*sPoint_A.Y+C*sPoint_A.Z);
 //уменьшим погрешности вычислений
 if (E<0)
 {
  t=-t;
  E=-E;
 }
 if (t<E+S_EPS1 && mode==0) return(FALSE);
 if ((t>E-S_EPS1 || t<-S_EPS1) && mode==2) return(FALSE);
 sPointReturn->X=sPoint_A.X+(t*lx)/E;
 sPointReturn->Y=sPoint_A.Y+(t*ly)/E;
 sPointReturn->Z=sPoint_A.Z+(t*lz)/E;
 return(TRUE);
}
BOOL IsPointInPolygon(SPoint sPoint,SPolygon sPolygon)
{
 for(int n=0;n<sPolygon.PointAmount;n++)
 {
  int i1,i2,i3;
  i1=n;
  i2=n+1;
  i3=n+2;
  if (i2>=sPolygon.PointAmount) i2-=sPolygon.PointAmount;
  if (i3>=sPolygon.PointAmount) i3-=sPolygon.PointAmount;
  double v1x=sPolygon.sPoint_Array[i1].X;
  double v1y=sPolygon.sPoint_Array[i1].Y;
  double v1z=sPolygon.sPoint_Array[i1].Z;
   
  double v2x=sPolygon.sPoint_Array[i2].X;
  double v2y=sPolygon.sPoint_Array[i2].Y;
  double v2z=sPolygon.sPoint_Array[i2].Z;
   
  double v3x=sPolygon.sPoint_Array[i3].X;
  double v3y=sPolygon.sPoint_Array[i3].Y;
  double v3z=sPolygon.sPoint_Array[i3].Z;
   
  SVector V1=CreateVector(v2x-v1x,v2y-v1y,v2z-v1z);
  SVector V2=CreateVector(v3x-v1x,v3y-v1y,v3z-v1z);
  SVector V3=CreateVector(sPoint.X-v1x,sPoint.Y-v1y,sPoint.Z-v1z);
   
  SVector V4=VectorProduct(V1,V2);
  SVector V5=VectorProduct(V1,V3);
  V4=NormalizeVector(V4);
  V5=NormalizeVector(V5);
  long double scalar=ScalarProduct(V4,V5);
  if (scalar<-S_EPS1) return(FALSE);
 }
 return(TRUE);
}
 
BOOL GenerateShadow(SPolygon sPolygon_ShadowSource,SPolygon sPolygon_ShadowDestination,SPoint sPoint_Lighting,CPolygon *cPolygon_Fragment)
{
 //sPolygon_ShadowSource-отбрасывает тень на sPolygon_ShadowDestination
 //sPoint_Lighting-положение источника света
 SPolygon sPolygon_Temporary;//резерный полигон
 SPoint sPoint_Temporary;//резервная точка
 SVector sVector_Temporary;//резервный вектор
 int n,m,u,v;
 cPolygon_Fragment->ClearAllPolygon();
 if (sPolygon_ShadowDestination.PointAmount<3) return(FALSE);
 if (sPolygon_ShadowSource.PointAmount<3)
 {
  cPolygon_Fragment->CreateNewPolygon(sPolygon_ShadowDestination);//добавим сам полигон
  return(FALSE);
 }
 //посмотрим, может ли вообще источник света освещать полигон 
 if (GetPointPositionPlane(sPoint_Lighting,sPolygon_ShadowDestination.sPoint_Array[0],sPolygon_ShadowDestination.sVector_Normal)!=1)//не может
 {
  cPolygon_Fragment->CreateNewPolygon(sPolygon_ShadowDestination);//добавим сам полигон
  return(TRUE);
 }
 //скорректируем полигон, отбрасывающий тень (он ведь может пересекать плоскость тени)
 SPolygon sPolygon_CorrectShadowSource;
 sPolygon_CorrectShadowSource.sPoint_Array=new SPoint [sPolygon_ShadowSource.PointAmount*2+1];
 sPolygon_CorrectShadowSource.PointAmount=0;
 for(u=0;u<sPolygon_ShadowSource.PointAmount;u++)
 {
  int u1=u;
  int u2=u+1;
  if (u2>=sPolygon_ShadowSource.PointAmount) u2-=sPolygon_ShadowSource.PointAmount;
  SPoint sPoint_A=sPolygon_ShadowSource.sPoint_Array[u1];
  SPoint sPoint_B=sPolygon_ShadowSource.sPoint_Array[u2];
  int PointAPosition=GetPointPositionPlane(sPoint_A,sPolygon_ShadowDestination.sPoint_Array[0],sPolygon_ShadowDestination.sVector_Normal);
  int PointBPosition=GetPointPositionPlane(sPoint_B,sPolygon_ShadowDestination.sPoint_Array[0],sPolygon_ShadowDestination.sVector_Normal);
  SPoint sPoint_Intersection;
  if (PointAPosition>=0)//точка A расположена правильно 
  {
   sPolygon_CorrectShadowSource.sPoint_Array[sPolygon_CorrectShadowSource.PointAmount]=sPoint_A;
   sPolygon_CorrectShadowSource.PointAmount++;
  }
  //проверим пересечение 
  if (PointAPosition*PointBPosition<0)//есть пересечение (точки по разные стороны от плоскости)
  {
   //найдём его
   if (GetLineIntersectionPlane(sPoint_A,sPoint_B,sPolygon_ShadowDestination.sPoint_Array[0],sPolygon_ShadowDestination.sVector_Normal,1,&sPoint_Intersection)==TRUE)
   {
    sPolygon_CorrectShadowSource.sPoint_Array[sPolygon_CorrectShadowSource.PointAmount]=sPoint_Intersection;
    sPolygon_CorrectShadowSource.PointAmount++;
   }
  }
 }
 if (sPolygon_CorrectShadowSource.PointAmount<3)//тени нет
 {
  delete(sPolygon_CorrectShadowSource.sPoint_Array);
  cPolygon_Fragment->CreateNewPolygon(sPolygon_ShadowDestination);//добавим сам полигон
  return(FALSE);
 }
 sPolygon_CorrectShadowSource.sVector_Normal=CalculateNormalVector(sPolygon_CorrectShadowSource);
  
 //проверим, не находятся ли полигон на который отбрасывается тень и источник 
 //с одной стороны от полигона, отбрасывающего тень (тогда тени нет)
 int lightpos=GetPointPositionPlane(sPoint_Lighting,sPolygon_CorrectShadowSource.sPoint_Array[0],sPolygon_CorrectShadowSource.sVector_Normal);
 BOOL ShadowOn=FALSE;
 for(n=0;n<sPolygon_ShadowDestination.PointAmount;n++)
 {
  int pos=GetPointPositionPlane(sPolygon_ShadowDestination.sPoint_Array[n],sPolygon_ShadowSource.sPoint_Array[0],sPolygon_ShadowSource.sVector_Normal);
  if (pos==0) continue;
  if (pos!=lightpos)//тень есть
  {
   ShadowOn=TRUE;
   break;
  }
 }
 if (ShadowOn==FALSE)
 {
  delete(sPolygon_CorrectShadowSource.sPoint_Array);
  cPolygon_Fragment->CreateNewPolygon(sPolygon_ShadowDestination);//добавим сам полигон
  return(FALSE);
 }
 CPolygon cPolygon_ShadowBorder;//набор полигонов, ограничивающий теневой объём
 cPolygon_ShadowBorder.CreateNewPolygon(sPolygon_CorrectShadowSource);//добавляем себя
 sPolygon_Temporary.PointAmount=4;
 sPolygon_Temporary.sPoint_Array=new SPoint[4];
 for(n=0;n<sPolygon_CorrectShadowSource.PointAmount;n++)//добавляем полигоны для каждой стороны
 {
  int i=n;
  int j=n+1;
  if (j>=sPolygon_CorrectShadowSource.PointAmount) j-=sPolygon_CorrectShadowSource.PointAmount;
  sVector_Temporary=CreateVector(sPolygon_CorrectShadowSource.sPoint_Array[i].X-sPoint_Lighting.X,sPolygon_CorrectShadowSource.sPoint_Array[i].Y-sPoint_Lighting.Y,sPolygon_CorrectShadowSource.sPoint_Array[i].Z-sPoint_Lighting.Z);
  sVector_Temporary=NormalizeVector(sVector_Temporary);
  sPolygon_Temporary.sPoint_Array[0].X=sPolygon_CorrectShadowSource.sPoint_Array[i].X+sVector_Temporary.X*10000.0;
  sPolygon_Temporary.sPoint_Array[0].Y=sPolygon_CorrectShadowSource.sPoint_Array[i].Y+sVector_Temporary.Y*10000.0;
  sPolygon_Temporary.sPoint_Array[0].Z=sPolygon_CorrectShadowSource.sPoint_Array[i].Z+sVector_Temporary.Z*10000.0;
  sPolygon_Temporary.sPoint_Array[1]=sPolygon_CorrectShadowSource.sPoint_Array[i];
  sPolygon_Temporary.sPoint_Array[2]=sPolygon_CorrectShadowSource.sPoint_Array[j];
  sVector_Temporary=CreateVector(sPolygon_CorrectShadowSource.sPoint_Array[j].X-sPoint_Lighting.X,sPolygon_CorrectShadowSource.sPoint_Array[j].Y-sPoint_Lighting.Y,sPolygon_CorrectShadowSource.sPoint_Array[j].Z-sPoint_Lighting.Z);
  sVector_Temporary=NormalizeVector(sVector_Temporary);
  sPolygon_Temporary.sPoint_Array[3].X=sPolygon_CorrectShadowSource.sPoint_Array[j].X+sVector_Temporary.X*10000.0;
  sPolygon_Temporary.sPoint_Array[3].Y=sPolygon_CorrectShadowSource.sPoint_Array[j].Y+sVector_Temporary.Y*10000.0;
  sPolygon_Temporary.sPoint_Array[3].Z=sPolygon_CorrectShadowSource.sPoint_Array[j].Z+sVector_Temporary.Z*10000.0;
  cPolygon_ShadowBorder.CreateNewPolygon(sPolygon_Temporary);//добавляем грань
 }
 delete(sPolygon_Temporary.sPoint_Array);
 SPoint sPoint_ShadowSourceCenter;
 sPoint_ShadowSourceCenter.X=0;
 sPoint_ShadowSourceCenter.Y=0;
 sPoint_ShadowSourceCenter.Z=0;
 for(n=0;n<sPolygon_CorrectShadowSource.PointAmount;n++)
 {
  sPoint_ShadowSourceCenter.X+=sPolygon_CorrectShadowSource.sPoint_Array[n].X;
  sPoint_ShadowSourceCenter.Y+=sPolygon_CorrectShadowSource.sPoint_Array[n].Y;
  sPoint_ShadowSourceCenter.Z+=sPolygon_CorrectShadowSource.sPoint_Array[n].Z;
 }
 sPoint_ShadowSourceCenter.X/=(double)sPolygon_CorrectShadowSource.PointAmount;
 sPoint_ShadowSourceCenter.Y/=(double)sPolygon_CorrectShadowSource.PointAmount;
 sPoint_ShadowSourceCenter.Z/=(double)sPolygon_CorrectShadowSource.PointAmount;
 //скорректируем нормали нашего набора (нормаль должна быть наружу)
 sVector_Temporary=CreateVector(sPoint_ShadowSourceCenter.X-sPoint_Lighting.X,sPoint_ShadowSourceCenter.Y-sPoint_Lighting.Y,sPoint_ShadowSourceCenter.Z-sPoint_Lighting.Z);
 sVector_Temporary=NormalizeVector(sVector_Temporary);
 //эта точка лежит внутри объёма
 sPoint_Temporary.X=sPoint_ShadowSourceCenter.X+sVector_Temporary.X*100.0;
 sPoint_Temporary.Y=sPoint_ShadowSourceCenter.Y+sVector_Temporary.Y*100.0;
 sPoint_Temporary.Z=sPoint_ShadowSourceCenter.Z+sVector_Temporary.Z*100.0;
 for(n=0;n<cPolygon_ShadowBorder.GetAmountOfPolygons();n++)
 {
  sPolygon_Temporary=cPolygon_ShadowBorder.GetPolygonForIndex(n);
  int pos=GetPointPositionPlane(sPoint_Temporary,sPolygon_Temporary.sPoint_Array[0],sPolygon_Temporary.sVector_Normal);
  if (pos>0)//изменим направление нормали
  {
   sPolygon_Temporary.sVector_Normal.X=-sPolygon_Temporary.sVector_Normal.X;
   sPolygon_Temporary.sVector_Normal.Y=-sPolygon_Temporary.sVector_Normal.Y;
   sPolygon_Temporary.sVector_Normal.Z=-sPolygon_Temporary.sVector_Normal.Z;
   cPolygon_ShadowBorder.SetPolygonNormalForIndex(n,sPolygon_Temporary.sVector_Normal);
  }
 }
 //теперь создаём точки тени
 SPolygon sPolygon_ShadowPoint;
 sPolygon_ShadowPoint.sPoint_Array=new SPoint[sPolygon_ShadowDestination.PointAmount*4+sPolygon_CorrectShadowSource.PointAmount*4+1];
 sPolygon_ShadowPoint.PointAmount=0; 
 //добавим все точки полигона, лежащие внутри объёма
 for(n=0;n<sPolygon_ShadowDestination.PointAmount;n++)
 {
  sPoint_Temporary=sPolygon_ShadowDestination.sPoint_Array[n];
  //проверим, лежит ли эта точка внутри объёма
  BOOL error=FALSE;
  for(m=0;m<cPolygon_ShadowBorder.GetAmountOfPolygons();m++)
  {
   sPolygon_Temporary=cPolygon_ShadowBorder.GetPolygonForIndex(m);
   int pos=GetPointPositionPlane(sPoint_Temporary,sPolygon_Temporary.sPoint_Array[0],sPolygon_Temporary.sVector_Normal);
   if (pos>0) 
   {
    error=TRUE;
    break;
   }
  }
  if (error==FALSE)//точка лежит внутри объёма
  {
   //посмотрим, может быть уже есть такая точка 
   BOOL enable=TRUE;
   for(v=0;v<sPolygon_ShadowPoint.PointAmount;v++)
   {
    SPoint sPoint_D=sPolygon_ShadowPoint.sPoint_Array[v];
    if ((fabs(sPoint_D.X-sPoint_Temporary.X))<=S_EPS && (fabs(sPoint_D.Z-sPoint_Temporary.Z))<=S_EPS && (fabs(sPoint_D.Y-sPoint_Temporary.Y))<=S_EPS) 
    { 
     enable=FALSE;
     break;
    }
   }
   if (enable==TRUE)
   {
    sPolygon_ShadowPoint.sPoint_Array[sPolygon_ShadowPoint.PointAmount]=sPoint_Temporary;
    sPolygon_ShadowPoint.PointAmount++;
   }
  }
 } 
 //добавим точки пересечения с теневым объёмом
 for(n=0;n<cPolygon_ShadowBorder.GetAmountOfPolygons();n++)
 {
  sPolygon_Temporary=cPolygon_ShadowBorder.GetPolygonForIndex(n);
  for(m=0;m<sPolygon_ShadowDestination.PointAmount;m++)
  {
   int i=m;
   int j=m+1;
   if (j>=sPolygon_ShadowDestination.PointAmount) j-=sPolygon_ShadowDestination.PointAmount;
   SPoint sPoint_A=sPolygon_ShadowDestination.sPoint_Array[i];
   SPoint sPoint_B=sPolygon_ShadowDestination.sPoint_Array[j];
   SPoint sPoint_Return;
   //есть пересечение с плоскостью
   if (GetLineIntersectionPlane(sPoint_A,sPoint_B,sPolygon_Temporary.sPoint_Array[0],sPolygon_Temporary.sVector_Normal,2,&sPoint_Return)==TRUE)
   {
    //убедимся, что точка пересечения попадает в грань теневого объёма
    if (IsPointInPolygon(sPoint_Return,sPolygon_Temporary)==TRUE)
    {
     //посмотрим, может быть уже есть такая точка 
     BOOL enable=TRUE;
     for(v=0;v<sPolygon_ShadowPoint.PointAmount;v++)
     {
      SPoint sPoint_D=sPolygon_ShadowPoint.sPoint_Array[v];
      if ((fabs(sPoint_D.X-sPoint_Return.X))<=S_EPS && (fabs(sPoint_D.Z-sPoint_Return.Z))<=S_EPS && (fabs(sPoint_D.Y-sPoint_Return.Y))<=S_EPS) 
      { 
       enable=FALSE;
       break;
      }
     }
     if (enable==TRUE)
     {
      sPolygon_ShadowPoint.sPoint_Array[sPolygon_ShadowPoint.PointAmount]=sPoint_Return;
      sPolygon_ShadowPoint.PointAmount++;
     }
    }
   }
  }
 }
 //переведём все созданные точки в двумерную систему координат
 //создадим орты новой системы координат, связанной с полигоном sPolygon_ShadowDestination
 SPoint sPoint_CenterOfCoordSystem=sPolygon_ShadowDestination.sPoint_Array[0];
 SVector sVector_OrtsX;
 SVector sVector_OrtsY;
 SVector sVector_OrtsZ;
 sVector_OrtsY=sPolygon_ShadowDestination.sVector_Normal;
 sVector_OrtsX.X=sPolygon_ShadowDestination.sPoint_Array[1].X-sPolygon_ShadowDestination.sPoint_Array[0].X;
 sVector_OrtsX.Y=sPolygon_ShadowDestination.sPoint_Array[1].Y-sPolygon_ShadowDestination.sPoint_Array[0].Y;
 sVector_OrtsX.Z=sPolygon_ShadowDestination.sPoint_Array[1].Z-sPolygon_ShadowDestination.sPoint_Array[0].Z;
 sVector_OrtsX=NormalizeVector(sVector_OrtsX);
 sVector_OrtsZ=VectorProduct(sVector_OrtsX,sVector_OrtsY);
 sVector_OrtsZ=NormalizeVector(sVector_OrtsZ);
 for(n=0;n<sPolygon_ShadowPoint.PointAmount;n++)
 {
  sPoint_Temporary=sPolygon_ShadowPoint.sPoint_Array[n];
  SVector sVector_Radius=CreateVector(sPoint_Temporary.X-sPoint_CenterOfCoordSystem.X,sPoint_Temporary.Y-sPoint_CenterOfCoordSystem.Y,sPoint_Temporary.Z-sPoint_CenterOfCoordSystem.Z);
  sPolygon_ShadowPoint.sPoint_Array[n].X=ScalarProduct(sVector_Radius,sVector_OrtsX);
  sPolygon_ShadowPoint.sPoint_Array[n].Z=ScalarProduct(sVector_Radius,sVector_OrtsZ);
  sPolygon_ShadowPoint.sPoint_Array[n].Y=0;//т.к. на нормаль проекция отсутствует всегда
 }
 //исходный полигон
 SPolygon sPolygon_ShadowDestinationProject;
 sPolygon_ShadowDestinationProject.sPoint_Array=new SPoint[sPolygon_ShadowDestination.PointAmount+1];
 sPolygon_ShadowDestinationProject.PointAmount=sPolygon_ShadowDestination.PointAmount;
 for(n=0;n<sPolygon_ShadowDestination.PointAmount;n++)
 {
  sPoint_Temporary=sPolygon_ShadowDestination.sPoint_Array[n];
  SVector sVector_Radius=CreateVector(sPoint_Temporary.X-sPoint_CenterOfCoordSystem.X,sPoint_Temporary.Y-sPoint_CenterOfCoordSystem.Y,sPoint_Temporary.Z-sPoint_CenterOfCoordSystem.Z);
  sPolygon_ShadowDestinationProject.sPoint_Array[n].X=ScalarProduct(sVector_Radius,sVector_OrtsX);
  sPolygon_ShadowDestinationProject.sPoint_Array[n].Z=ScalarProduct(sVector_Radius,sVector_OrtsZ);
  sPolygon_ShadowDestinationProject.sPoint_Array[n].Y=0;//т.к. на нормаль проекция отсутствует всегда
 } 
 //добавим все точки пересечения объёма с плоскостью полигона и попадающие внутрь полигона
 for(n=0;n<sPolygon_CorrectShadowSource.PointAmount;n++)
 {
  sPoint_Temporary=sPolygon_CorrectShadowSource.sPoint_Array[n];
  SPoint sPoint_Return;
  if (GetLineIntersectionPlane(sPoint_Lighting,sPoint_Temporary,sPolygon_ShadowDestination.sPoint_Array[0],sPolygon_ShadowDestination.sVector_Normal,0,&sPoint_Return)==TRUE)//есть точка пересечения
  {
   //переведём в новую систему координат
   SVector sVector_Radius=CreateVector(sPoint_Return.X-sPoint_CenterOfCoordSystem.X,sPoint_Return.Y-sPoint_CenterOfCoordSystem.Y,sPoint_Return.Z-sPoint_CenterOfCoordSystem.Z);
   sPoint_Temporary.X=ScalarProduct(sVector_Radius,sVector_OrtsX);
   sPoint_Temporary.Z=ScalarProduct(sVector_Radius,sVector_OrtsZ);
   sPoint_Temporary.Y=0;//т.к. на нормаль проекция отсутствует всегда
   if (IsPointInPolygonXZ(sPoint_Temporary,sPolygon_ShadowDestinationProject)==TRUE)//точка внутри полигона
   {
    //посмотрим, может быть уже есть такая точка 
    BOOL enable=TRUE;
    for(v=0;v<sPolygon_ShadowPoint.PointAmount;v++)
    {
     SPoint sPoint_D=sPolygon_ShadowPoint.sPoint_Array[v];
     if ((fabs(sPoint_D.X-sPoint_Temporary.X))<=S_EPS && (fabs(sPoint_D.Z-sPoint_Temporary.Z))<=S_EPS)  
     { 
      enable=FALSE;
      break;
     }
    }
    if (enable==TRUE)
    {
     sPolygon_ShadowPoint.sPoint_Array[sPolygon_ShadowPoint.PointAmount]=sPoint_Temporary;
     sPolygon_ShadowPoint.PointAmount++;
    }
   }
  }
 }
 if (sPolygon_ShadowPoint.PointAmount<3)//тени нет
 {
  cPolygon_Fragment->CreateNewPolygon(sPolygon_ShadowDestination);//добавим сам полигон
  delete(sPolygon_CorrectShadowSource.sPoint_Array);
  delete(sPolygon_ShadowPoint.sPoint_Array);
  delete(sPolygon_ShadowDestinationProject.sPoint_Array);
  return(FALSE);
 }
 //теперь сортируем точки
 SPolygon sPolygon_Shadow;//точки тени, отсечённой по полигону
 sPolygon_Shadow.sPoint_Array=new SPoint[sPolygon_ShadowPoint.PointAmount+1];
 sPolygon_Shadow.PointAmount=sPolygon_ShadowPoint.PointAmount;
 //найдём центральную точку тени
 SPoint sPoint_CenterShadow;
 sPoint_CenterShadow.X=0;
 sPoint_CenterShadow.Y=0;
 sPoint_CenterShadow.Z=0;
 for(n=0;n<sPolygon_ShadowPoint.PointAmount;n++)
 {
  sPoint_CenterShadow.X+=sPolygon_ShadowPoint.sPoint_Array[n].X;
  sPoint_CenterShadow.Z+=sPolygon_ShadowPoint.sPoint_Array[n].Z;
  sPolygon_Shadow.sPoint_Array[n]=sPolygon_ShadowPoint.sPoint_Array[n];
 }
 sPoint_CenterShadow.X/=(double)sPolygon_ShadowPoint.PointAmount;
 sPoint_CenterShadow.Z/=(double)sPolygon_ShadowPoint.PointAmount;
 //узнаем параметры точек
 double *Angle=new double[sPolygon_Shadow.PointAmount+1];
 double *Length=new double[sPolygon_Shadow.PointAmount+1];
 for(v=0;v<sPolygon_Shadow.PointAmount;v++)
 {
  SPoint sPoint=sPolygon_Shadow.sPoint_Array[v];
  double dx=sPoint.X-sPoint_CenterShadow.X;
  double dz=sPoint.Z-sPoint_CenterShadow.Z;
  Length[v]=sqrt(dx*dx+dz*dz);
  Angle[v]=0;
  if (dx!=0) Angle[v]=atan(dz/dx)*180.0/3.14159265358979323;
  else
  {
   if (dz<0) Angle[v]=270.0;
   if (dz>0) Angle[v]=90.0;
  }
  if (dx<0) Angle[v]+=180.0;
 }
 //теперь сортируем точки
 for(v=0;v<sPolygon_Shadow.PointAmount;v++)
 {
  for(u=0;u<sPolygon_Shadow.PointAmount-1;u++)
  {
   double angle1=Angle[u];
   double angle2=Angle[u+1];
   double length1=Length[u];
   double length2=Length[u+1];
   if (angle1>angle2)
   {
    SPoint sPoint_1=sPolygon_Shadow.sPoint_Array[u];
    SPoint sPoint_2=sPolygon_Shadow.sPoint_Array[u+1];
    sPolygon_Shadow.sPoint_Array[u]=sPoint_2;
    sPolygon_Shadow.sPoint_Array[u+1]=sPoint_1;
    Angle[u]=angle2;
    Angle[u+1]=angle1;
    Length[u]=length2;
    Length[u+1]=length1;
    continue;
   }
   if (angle1==angle2)
   {
    if (length1>length2)
    {
     SPoint sPoint_1=sPolygon_Shadow.sPoint_Array[u];
     SPoint sPoint_2=sPolygon_Shadow.sPoint_Array[u+1];
     sPolygon_Shadow.sPoint_Array[u]=sPoint_2;
     sPolygon_Shadow.sPoint_Array[u+1]=sPoint_1;
     Angle[u]=angle2;
     Angle[u+1]=angle1;
     Length[u]=length2;
     Length[u+1]=length1;
     continue;
    }
   }
  }
 }
 delete(Angle);
 delete(Length);
 delete(sPolygon_ShadowPoint.sPoint_Array);
 //теперь у нас есть тень
 //разобъём полигон на фрагменты
 cPolygon_Fragment->CreateNewPolygon(sPolygon_Shadow);//добавим саму тень в список
 SPolygon sPolygon_Fragment;
 sPolygon_Fragment.sPoint_Array=new SPoint[sPolygon_ShadowDestinationProject.PointAmount*4+2];
 for(v=0;v<sPolygon_Shadow.PointAmount;v++)
 {
  int v1=v;
  int v2=v+1;
  if (v2>=sPolygon_Shadow.PointAmount) v2-=sPolygon_Shadow.PointAmount;
  sPolygon_Fragment.PointAmount=0;
  SPoint sPoint_A=sPolygon_Shadow.sPoint_Array[v1];
  SPoint sPoint_B=sPolygon_Shadow.sPoint_Array[v2];
  int CenterShadowPosition=GetPointPositionInPlaneXZ(sPoint_A,sPoint_B,sPoint_CenterShadow);
  if (CenterShadowPosition==0)//тени нет
  {
   cPolygon_Fragment->ClearAllPolygon();//удалим всё что добавили
   cPolygon_Fragment->CreateNewPolygon(sPolygon_ShadowDestination);//добавим сам полигон
   delete(sPolygon_CorrectShadowSource.sPoint_Array);
   delete(sPolygon_ShadowDestinationProject.sPoint_Array);
   delete(sPolygon_Shadow.sPoint_Array);
   delete(sPolygon_Fragment.sPoint_Array);
   return(FALSE);
  }
  //создаём фрагмент
  //добавляем точки, лежащие снаружи 
  for(u=0;u<sPolygon_ShadowDestinationProject.PointAmount;u++)
  {
   SPoint sPoint_C=sPolygon_ShadowDestinationProject.sPoint_Array[u];
   int PointCPosition=GetPointPositionInPlaneXZ(sPoint_A,sPoint_B,sPoint_C);
   if (PointCPosition*CenterShadowPosition<=0)//по разные стороны
   {
    //посмотрим, может быть уже есть такая точка 
    BOOL enable=TRUE;
    for(n=0;n<sPolygon_Fragment.PointAmount;n++)
    {
     SPoint sPoint_D=sPolygon_Fragment.sPoint_Array[n];
     if ((fabs(sPoint_D.X-sPoint_C.X))<=S_EPS && (fabs(sPoint_D.Z-sPoint_C.Z))<=S_EPS)
     { 
      enable=FALSE;
      break;
     }
    }
    if (enable==TRUE)
    {
     sPolygon_Fragment.sPoint_Array[sPolygon_Fragment.PointAmount]=sPoint_C;
     sPolygon_Fragment.PointAmount++;
    }
   }
  }
  //добавляем точки пересечения
  for(u=0;u<sPolygon_ShadowDestinationProject.PointAmount;u++)
  {
   int u1=u;
   int u2=u+1;
   if (u2>=sPolygon_ShadowDestinationProject.PointAmount) u2-=sPolygon_ShadowDestinationProject.PointAmount;
   SPoint sPoint_C=sPolygon_ShadowDestinationProject.sPoint_Array[u1];
   SPoint sPoint_D=sPolygon_ShadowDestinationProject.sPoint_Array[u2];
   SPoint sPoint_Intersection;
   if (GetLineIntersectionPieceInPlaneXZ(sPoint_A,sPoint_B,sPoint_C,sPoint_D,&sPoint_Intersection)==TRUE)//есть пересечение
   {
    //посмотрим, может быть уже есть такая точка 
    BOOL enable=TRUE;
    for(n=0;n<sPolygon_Fragment.PointAmount;n++)
    {
     SPoint sPoint_E=sPolygon_Fragment.sPoint_Array[n];
     if ((fabs(sPoint_E.X-sPoint_Intersection.X))<=S_EPS && (fabs(sPoint_E.Z-sPoint_Intersection.Z))<=S_EPS)
     { 
      enable=FALSE;
      break;
     }
    }
    if (enable==TRUE)
    {
     sPolygon_Fragment.sPoint_Array[sPolygon_Fragment.PointAmount]=sPoint_Intersection;
     sPolygon_Fragment.PointAmount++;
    }
   }
  }
  if (sPolygon_Fragment.PointAmount==0) continue;//нет фрагмента
  //модифицируем наш полигон
  SPolygon sPolygon_NewBasic;
  sPolygon_NewBasic.sPoint_Array=new SPoint[sPolygon_ShadowDestinationProject.PointAmount*2+1];
  sPolygon_NewBasic.PointAmount=0;
  for(n=0;n<sPolygon_ShadowDestinationProject.PointAmount;n++)
  {
   int u1=n;
   int u2=n+1;
   if (u2>=sPolygon_ShadowDestinationProject.PointAmount) u2-=sPolygon_ShadowDestinationProject.PointAmount;
   SPoint sPoint_C=sPolygon_ShadowDestinationProject.sPoint_Array[u1];
   SPoint sPoint_D=sPolygon_ShadowDestinationProject.sPoint_Array[u2];
   int PointCPosition=GetPointPositionInPlaneXZ(sPoint_A,sPoint_B,sPoint_C);
   SPoint sPoint_Intersection;
   if (GetLineIntersectionPieceInPlaneXZ(sPoint_A,sPoint_B,sPoint_C,sPoint_D,&sPoint_Intersection)==TRUE)//есть пересечение
   {
    if (PointCPosition*CenterShadowPosition>=0)//точка C внутри
    {
     sPolygon_NewBasic.sPoint_Array[sPolygon_NewBasic.PointAmount]=sPoint_C;
     sPolygon_NewBasic.PointAmount++;
    }
    if (PointCPosition==0) continue;
    sPolygon_NewBasic.sPoint_Array[sPolygon_NewBasic.PointAmount]=sPoint_Intersection;
    sPolygon_NewBasic.PointAmount++;
   }
   else
   {
    if (PointCPosition*CenterShadowPosition>=0)//точка C внутри
    {
     sPolygon_NewBasic.sPoint_Array[sPolygon_NewBasic.PointAmount]=sPoint_C;
     sPolygon_NewBasic.PointAmount++;
    }
   }
  }
  delete(sPolygon_ShadowDestinationProject.sPoint_Array);
  sPolygon_ShadowDestinationProject=sPolygon_NewBasic;
   
  SPoint sPoint_CenterFragment;
  sPoint_CenterFragment.X=0;
  sPoint_CenterFragment.Y=0;
  sPoint_CenterFragment.Z=0;
  for(n=0;n<sPolygon_Fragment.PointAmount;n++)
  {
   sPoint_CenterFragment.X+=sPolygon_Fragment.sPoint_Array[n].X;
   sPoint_CenterFragment.Z+=sPolygon_Fragment.sPoint_Array[n].Z;
  }
  sPoint_CenterFragment.X/=(double)sPolygon_Fragment.PointAmount;
  sPoint_CenterFragment.Z/=(double)sPolygon_Fragment.PointAmount;
  //узнаем параметры точек
  Angle=new double[sPolygon_Fragment.PointAmount+1];
  Length=new double[sPolygon_Fragment.PointAmount+1];
  for(n=0;n<sPolygon_Fragment.PointAmount;n++)
  {
   SPoint sPoint=sPolygon_Fragment.sPoint_Array[n];
   double dx=sPoint.X-sPoint_CenterFragment.X;
   double dz=sPoint.Z-sPoint_CenterFragment.Z;
   Length[n]=sqrt(dx*dx+dz*dz);
   Angle[n]=0;
   if (dx!=0) Angle[n]=atan(dz/dx)*180.0/3.14159265358979323;
   else
   {
    if (dz<0) Angle[n]=270.0;
    if (dz>0) Angle[n]=90.0;
   }
   if (dx<0) Angle[n]+=180.0;
  }
  //теперь сортируем точки
  for(n=0;n<sPolygon_Fragment.PointAmount;n++)
  {
   for(m=0;m<sPolygon_Fragment.PointAmount-1;m++)
   {
    double angle1=Angle[m];
    double angle2=Angle[m+1];
    double length1=Length[m];
    double length2=Length[m+1];
    if (angle1>angle2)
    {
     SPoint sPoint_1=sPolygon_Fragment.sPoint_Array[m];
     SPoint sPoint_2=sPolygon_Fragment.sPoint_Array[m+1];
     sPolygon_Fragment.sPoint_Array[m]=sPoint_2;
     sPolygon_Fragment.sPoint_Array[m+1]=sPoint_1;
     Angle[m]=angle2;
     Angle[m+1]=angle1;
     Length[m]=length2;
     Length[m+1]=length1;
     continue;
    }
    if (angle1==angle2)
    {
     if (length1>length2)
     {
      SPoint sPoint_1=sPolygon_Fragment.sPoint_Array[m];
      SPoint sPoint_2=sPolygon_Fragment.sPoint_Array[m+1];
      sPolygon_Fragment.sPoint_Array[m]=sPoint_2;
      sPolygon_Fragment.sPoint_Array[m+1]=sPoint_1;
      Angle[m]=angle2;
      Angle[m+1]=angle1;
      Length[m]=length2;
      Length[m+1]=length1;
      continue;
     }
    }
   }
  }
  delete(Angle);
  delete(Length);
  cPolygon_Fragment->CreateNewPolygon(sPolygon_Fragment);//добавим фрагмент в список
 }
 delete(sPolygon_Fragment.sPoint_Array);
 //обратное преобразование для всех точек
 for(n=0;n<cPolygon_Fragment->GetAmountOfPolygons();n++)
 {
  SPolygon sPolygon=cPolygon_Fragment->GetPolygonForIndex(n);
  //здесь получены указатели, и модификация идёт внутри массива напрямую
  for(v=0;v<sPolygon.PointAmount;v++)
  {
   SPoint sPoint=sPolygon.sPoint_Array[v];
   sPolygon.sPoint_Array[v].X=sPoint_CenterOfCoordSystem.X+sVector_OrtsX.X*sPoint.X+sVector_OrtsY.X*sPoint.Y+sVector_OrtsZ.X*sPoint.Z;
   sPolygon.sPoint_Array[v].Y=sPoint_CenterOfCoordSystem.Y+sVector_OrtsX.Y*sPoint.X+sVector_OrtsY.Y*sPoint.Y+sVector_OrtsZ.Y*sPoint.Z;
   sPolygon.sPoint_Array[v].Z=sPoint_CenterOfCoordSystem.Z+sVector_OrtsX.Z*sPoint.X+sVector_OrtsY.Z*sPoint.Y+sVector_OrtsZ.Z*sPoint.Z;
  }
  cPolygon_Fragment->GenerateNormal(n);
  sPolygon=cPolygon_Fragment->GetPolygonForIndex(n);
  if (ScalarProduct(sPolygon_ShadowDestination.sVector_Normal,sPolygon.sVector_Normal)<0)//нужно поменять направление обхода вершин
  {
   for(v=0;v<sPolygon.PointAmount/2;v++)
   {
    SPoint sPoint1=sPolygon.sPoint_Array[sPolygon.PointAmount-v-1];
    SPoint sPoint2=sPolygon.sPoint_Array[v];
    sPolygon.sPoint_Array[sPolygon.PointAmount-v-1]=sPoint2;
    sPolygon.sPoint_Array[v]=sPoint1;
   }
  }
  cPolygon_Fragment->SetPolygonNormalForIndex(n,sPolygon_ShadowDestination.sVector_Normal);
 } 
 delete(sPolygon_ShadowDestinationProject.sPoint_Array);
 delete(sPolygon_Shadow.sPoint_Array);
 delete(sPolygon_CorrectShadowSource.sPoint_Array);
 return(TRUE);
}

#include "render.h"

extern CDialog_CreateSegment cDialog_CreateSegment;
extern CDialog_CreateSimplyDoor cDialog_CreateSimplyDoor;
extern CDialog_CreateSimplySector cDialog_CreateSimplySector;
extern CDialog_CreateLighting cDialog_CreateLighting;
extern CDialog_SelectTexture cDialog_SelectTexture;
extern CWnd_Progress cWnd_Progress;
extern CDialog_StartPos StartPoscWnd_Form;
extern SSettings sSettings;//настройки редактора


//------------------------------------------------------------------------------
CRender::CRender(char *FileName)
{
 SSegmentPackage SP;
 SSectorPackage SCP;
 SSurface *Surface=NULL;
 int n,m,u,v,k,l,r;
 //попросим сегменты определить свои сектора
 if (cDialog_CreateSegment.DefinitionSector()==1) return;
 //создадим поверхности стен
 for(n=0;n<sKeyData.MaximumNumberOfLine;n++)
 {
  int type=cDialog_CreateSegment.Segment[n].Frontier;
  if (type==0)//это обычная стена
  {
   double up_level,down_level;
   int SectorOneType=cDialog_CreateSegment.Segment[n].SectorOneType;
   int SectorOne=cDialog_CreateSegment.Segment[n].SectorOne;
   int SectorTwoType=cDialog_CreateSegment.Segment[n].SectorTwoType;
   int SectorTwo=cDialog_CreateSegment.Segment[n].SectorTwo;
   if (cDialog_CreateSegment.Segment[n].DoubleSegment==0)//сегмент принадлежит одному сектору
   {
    //работа с секторами
    if (SectorOneType==0)//сегмент принадлежит обычному сектору
    {
     up_level=cDialog_CreateSimplySector.GetUpLevelFromSegment(SectorOne);//пусть он и возвратит верхний уровень сегмента
     down_level=cDialog_CreateSimplySector.GetDownLevelFromSegment(SectorOne);//пусть он и возвратит нижний уровень сегмента
    }
    if (SectorOneType==1)//сегмент принадлежит обычной двери
    {
     up_level=cDialog_CreateSimplyDoor.GetUpLevelFromSegment(SectorOne);//пусть он и возвратит верхний уровень сегмента
     down_level=cDialog_CreateSimplyDoor.GetDownLevelFromSegment(SectorOne);//пусть он и возвратит нижний уровень сегмента
    }
    //работа с секторами
   }
   else
   {
    double up_level1,down_level1;
    double up_level2,down_level2;
    //нужно найти самый высокий и самый низкий уровень
    //работа с секторами
    if (SectorOneType==0)//сегмент принадлежит обычному сектору
    {
     up_level1=cDialog_CreateSimplySector.GetUpLevelFromSegment(SectorOne);//пусть он и возвратит верхний уровень сегмента
     down_level1=cDialog_CreateSimplySector.GetDownLevelFromSegment(SectorOne);//пусть он и возвратит нижний уровень сегмента
    }
    if (SectorTwoType==0)//сегмент принадлежит обычному сектору
    {
     up_level2=cDialog_CreateSimplySector.GetUpLevelFromSegment(SectorTwo);//пусть он и возвратит верхний уровень сегмента
     down_level2=cDialog_CreateSimplySector.GetDownLevelFromSegment(SectorTwo);//пусть он и возвратит нижний уровень сегмента
    }
    if (SectorOneType==1)//сегмент принадлежит обычной двери
    {
     up_level1=cDialog_CreateSimplyDoor.GetUpLevelFromSegment(SectorOne);//пусть он и возвратит верхний уровень сегмента
     down_level1=cDialog_CreateSimplyDoor.GetDownLevelFromSegment(SectorOne);//пусть он и возвратит нижний уровень сегмента
    }
    if (SectorTwoType==1)//сегмент принадлежит обычной двери
    {
     up_level2=cDialog_CreateSimplyDoor.GetUpLevelFromSegment(SectorTwo);//пусть он и возвратит верхний уровень сегмента
     down_level2=cDialog_CreateSimplyDoor.GetDownLevelFromSegment(SectorTwo);//пусть он и возвратит нижний уровень сегмента
    }
    //работа с секторами
    up_level=up_level1;
    down_level=down_level1;
    if (up_level2<up_level) up_level=up_level2;
    if (down_level2>down_level) down_level=down_level2;
    if (up_level<=down_level) continue;//ну это уж явная ошибка
   }
   //терерь создадим на основе этого сегмента поверхность
   SP.Normal.X=-(cDialog_CreateSegment.Segment[n].Y2-cDialog_CreateSegment.Segment[n].Y1);
   SP.Normal.Y=(cDialog_CreateSegment.Segment[n].X2-cDialog_CreateSegment.Segment[n].X1);
   SP.Normal.Z=0;
   SP.Texture=cDialog_CreateSegment.Segment[n].UpTexture;
   //нормировать нормали не надо, т.к. этим занимается функция установки поверхности
   SP.X[0]=cDialog_CreateSegment.Segment[n].X2;
   SP.Y[0]=cDialog_CreateSegment.Segment[n].Y2;
   SP.Z[0]=down_level;
   SP.X[1]=cDialog_CreateSegment.Segment[n].X2;
   SP.Y[1]=cDialog_CreateSegment.Segment[n].Y2;
   SP.Z[1]=up_level;
   SP.X[2]=cDialog_CreateSegment.Segment[n].X1;
   SP.Y[2]=cDialog_CreateSegment.Segment[n].Y1;
   SP.Z[2]=up_level;
   SP.X[3]=cDialog_CreateSegment.Segment[n].X1;
   SP.Y[3]=cDialog_CreateSegment.Segment[n].Y1;
   SP.Z[3]=down_level;
   SP.Segment=n;
   SP.X_Left_Up=cDialog_CreateSegment.Segment[n].X1;
   SP.Y_Left_Up=cDialog_CreateSegment.Segment[n].Y1;
   SP.Z_Left_Up=up_level;
   SP.Location=0;
   SP.BarrierType=0;
   if (cDialog_CreateSegment.Segment[n].Blend==1) SP.BarrierType=1;
   NewSurfaceSegment(&Surface,SP);
  }
  else//если у нас линия раздела
  {
   double SectorOne_up_level,SectorOne_down_level;
   double SectorTwo_up_level,SectorTwo_down_level;
   int SectorOneType=cDialog_CreateSegment.Segment[n].SectorOneType;
   int SectorOne=cDialog_CreateSegment.Segment[n].SectorOne;
   int SectorTwoType=cDialog_CreateSegment.Segment[n].SectorTwoType;
   int SectorTwo=cDialog_CreateSegment.Segment[n].SectorTwo;
   if (SectorOneType*SectorTwoType!=0)//так как простые сектора имеют тип 0, то здесь проверка на то, что один из секторов точно простой
   {
    MessageBox(NULL,"Ни один из секторов при линии раздела не простой сектор !","Ошибка генерации поверхности",MB_OK);
    DeleteAllSurface(&Surface);//удалим все старые поверхности
    return;
   }
   //работа с секторами
   if (SectorOneType==0)//первый сектор обычный
   {
    SectorOne_up_level=cDialog_CreateSimplySector.GetUpLevelFromFrontier(SectorOne);//пусть он и возвратит верхний уровень линии раздела
    SectorOne_down_level=cDialog_CreateSimplySector.GetDownLevelFromFrontier(SectorOne);//пусть он и возвратит нижний уровень линии раздела
   }
   if (SectorTwoType==0)//второй сектор обычный
   {
    SectorTwo_up_level=cDialog_CreateSimplySector.GetUpLevelFromFrontier(SectorTwo);//пусть он и возвратит верхний уровень линии раздела
    SectorTwo_down_level=cDialog_CreateSimplySector.GetDownLevelFromFrontier(SectorTwo);//пусть он и возвратит нижний уровень линии раздела
   }
   if (SectorOneType==1)//первый сектор обычная дверь
   {
    SectorOne_up_level=cDialog_CreateSimplyDoor.GetUpLevelFromFrontier(SectorOne);//пусть он и возвратит верхний уровень линии раздела
    SectorOne_down_level=cDialog_CreateSimplyDoor.GetDownLevelFromFrontier(SectorOne);//пусть он и возвратит нижний уровень линии раздела
   }
   if (SectorTwoType==1)//второй сектор обычная дверь
   {
    SectorTwo_up_level=cDialog_CreateSimplyDoor.GetUpLevelFromFrontier(SectorTwo);//пусть он и возвратит верхний уровень линии раздела
    SectorTwo_down_level=cDialog_CreateSimplyDoor.GetDownLevelFromFrontier(SectorTwo);//пусть он и возвратит нижний уровень линии раздела
   }
   //работа с секторами
   //теперь создадим на основе этой линии раздела две поверхности(если,конечно,есть разность высот)
   //создаём верхнюю линию раздела
   if (SectorOne_up_level!=SectorTwo_up_level)//разность высот есть
   {
    if (SectorOne_up_level>SectorTwo_up_level)//первый сектор выше второго
    {
     //работа с секторами
     int pos=0;
     if (SectorOneType==0) pos=cDialog_CreateSimplySector.GetPosition(SectorOne,(float)(cDialog_CreateSegment.Segment[n].X1),(float)(cDialog_CreateSegment.Segment[n].Y1),(float)(cDialog_CreateSegment.Segment[n].X2),(float)(cDialog_CreateSegment.Segment[n].Y2));
     if (SectorOneType==1) pos=cDialog_CreateSimplyDoor.GetPosition(SectorOne,(float)(cDialog_CreateSegment.Segment[n].X1),(float)(cDialog_CreateSegment.Segment[n].Y1),(float)(cDialog_CreateSegment.Segment[n].X2),(float)(cDialog_CreateSegment.Segment[n].Y2));
     //работа с секторами
     if (pos==0)
     {
      MessageBox(NULL,"Не определить с какой стороны сектор от линии раздела","Ошибка",MB_OK);
      return;
     }
     if (pos<0)//сектор справа(т.е. всё нормально, поверхность будет видна при таком направлении)
     {
      SP.X[3]=cDialog_CreateSegment.Segment[n].X2;
      SP.Y[3]=cDialog_CreateSegment.Segment[n].Y2;
      SP.Z[3]=SectorTwo_up_level;
      SP.X[2]=cDialog_CreateSegment.Segment[n].X2;
      SP.Y[2]=cDialog_CreateSegment.Segment[n].Y2;
      SP.Z[2]=SectorOne_up_level;
      SP.X[1]=cDialog_CreateSegment.Segment[n].X1;
      SP.Y[1]=cDialog_CreateSegment.Segment[n].Y1;
      SP.Z[1]=SectorOne_up_level;
      SP.X[0]=cDialog_CreateSegment.Segment[n].X1;
      SP.Y[0]=cDialog_CreateSegment.Segment[n].Y1;
      SP.Z[0]=SectorTwo_up_level;
      SP.Normal.X=(SP.Y[2]-SP.Y[1]);
      SP.Normal.Y=-(SP.X[2]-SP.X[1]);
      SP.Normal.Z=0;
      SP.Texture=cDialog_CreateSegment.Segment[n].UpTexture;
      SP.Segment=n;
      SP.X_Left_Up=cDialog_CreateSegment.Segment[n].X1;
      SP.Y_Left_Up=cDialog_CreateSegment.Segment[n].Y1;
      SP.Z_Left_Up=SectorOne_up_level;
      SP.Location=1;
      SP.BarrierType=0;
      if (SectorOneType==1 || SectorTwoType==1) SP.BarrierType=2;//т.к. двери
      NewSurfaceSegment(&Surface,SP);
     }
     else//сектор слева(т.е. нужно менять направление линии)
     {
      SP.X[3]=cDialog_CreateSegment.Segment[n].X1;
      SP.Y[3]=cDialog_CreateSegment.Segment[n].Y1;
      SP.Z[3]=SectorTwo_up_level;
      SP.X[2]=cDialog_CreateSegment.Segment[n].X1;
      SP.Y[2]=cDialog_CreateSegment.Segment[n].Y1;
      SP.Z[2]=SectorOne_up_level;
      SP.X[1]=cDialog_CreateSegment.Segment[n].X2;
      SP.Y[1]=cDialog_CreateSegment.Segment[n].Y2;
      SP.Z[1]=SectorOne_up_level;
      SP.X[0]=cDialog_CreateSegment.Segment[n].X2;
      SP.Y[0]=cDialog_CreateSegment.Segment[n].Y2;
      SP.Z[0]=SectorTwo_up_level;
      SP.Normal.X=(SP.Y[2]-SP.Y[1]);
      SP.Normal.Y=-(SP.X[2]-SP.X[1]);
      SP.Normal.Z=0;
      SP.Texture=cDialog_CreateSegment.Segment[n].UpTexture;
      SP.Segment=n;
      SP.X_Left_Up=cDialog_CreateSegment.Segment[n].X1;
      SP.Y_Left_Up=cDialog_CreateSegment.Segment[n].Y1;
      SP.Z_Left_Up=SectorOne_up_level;
      SP.Location=1;
      SP.BarrierType=0;
      if (SectorOneType==1 || SectorTwoType==1) SP.BarrierType=2;//т.к. двери
      NewSurfaceSegment(&Surface,SP);
     }
    }
    else//второй сектор выше первого
    {
     int pos=0;
     //работа с секторами
     if (SectorTwoType==0) pos=cDialog_CreateSimplySector.GetPosition(SectorTwo,(float)(cDialog_CreateSegment.Segment[n].X1),(float)(cDialog_CreateSegment.Segment[n].Y1),(float)(cDialog_CreateSegment.Segment[n].X2),(float)(cDialog_CreateSegment.Segment[n].Y2));
     if (SectorTwoType==1) pos=cDialog_CreateSimplyDoor.GetPosition(SectorTwo,(float)(cDialog_CreateSegment.Segment[n].X1),(float)(cDialog_CreateSegment.Segment[n].Y1),(float)(cDialog_CreateSegment.Segment[n].X2),(float)(cDialog_CreateSegment.Segment[n].Y2));
     //работа с секторами
     if (pos==0)
     {
      MessageBox(NULL,"Не определить с какой стороны сектор от линии раздела","Ошибка",MB_OK);
      DeleteAllSurface(&Surface);//удалим все старые поверхности
      return;
     }
     if (pos<0)//сектор справа(т.е. всё нормально, поверхность будет видна при таком направлении)
     {
      SP.X[3]=cDialog_CreateSegment.Segment[n].X2;
      SP.Y[3]=cDialog_CreateSegment.Segment[n].Y2;
      SP.Z[3]=SectorOne_up_level;
      SP.X[2]=cDialog_CreateSegment.Segment[n].X2;
      SP.Y[2]=cDialog_CreateSegment.Segment[n].Y2;
      SP.Z[2]=SectorTwo_up_level;
      SP.X[1]=cDialog_CreateSegment.Segment[n].X1;
      SP.Y[1]=cDialog_CreateSegment.Segment[n].Y1;
      SP.Z[1]=SectorTwo_up_level;
      SP.X[0]=cDialog_CreateSegment.Segment[n].X1;
      SP.Y[0]=cDialog_CreateSegment.Segment[n].Y1;
      SP.Z[0]=SectorOne_up_level;
      SP.Normal.X=(SP.Y[2]-SP.Y[1]);
      SP.Normal.Y=-(SP.X[2]-SP.X[1]);
      SP.Normal.Z=0;
      SP.Texture=cDialog_CreateSegment.Segment[n].UpTexture;
      SP.Segment=n;
      SP.X_Left_Up=cDialog_CreateSegment.Segment[n].X1;
      SP.Y_Left_Up=cDialog_CreateSegment.Segment[n].Y1;
      SP.Z_Left_Up=SectorTwo_up_level;
      SP.Location=1;
      SP.BarrierType=0;
      if (SectorOneType==1 || SectorTwoType==1) SP.BarrierType=2;//т.к. двери
      NewSurfaceSegment(&Surface,SP);
     }
     else//сектор слева(т.е. нужно менять направление линии)
     {
      SP.X[3]=cDialog_CreateSegment.Segment[n].X1;
      SP.Y[3]=cDialog_CreateSegment.Segment[n].Y1;
      SP.Z[3]=SectorOne_up_level;
      SP.X[2]=cDialog_CreateSegment.Segment[n].X1;
      SP.Y[2]=cDialog_CreateSegment.Segment[n].Y1;
      SP.Z[2]=SectorTwo_up_level;
      SP.X[1]=cDialog_CreateSegment.Segment[n].X2;
      SP.Y[1]=cDialog_CreateSegment.Segment[n].Y2;
      SP.Z[1]=SectorTwo_up_level;
      SP.X[0]=cDialog_CreateSegment.Segment[n].X2;
      SP.Y[0]=cDialog_CreateSegment.Segment[n].Y2;
      SP.Z[0]=SectorOne_up_level;
      SP.Normal.X=(SP.Y[2]-SP.Y[1]);
      SP.Normal.Y=-(SP.X[2]-SP.X[1]);
      SP.Normal.Z=0;
      SP.Texture=cDialog_CreateSegment.Segment[n].UpTexture;
      SP.Segment=n;
      SP.X_Left_Up=cDialog_CreateSegment.Segment[n].X1;
      SP.Y_Left_Up=cDialog_CreateSegment.Segment[n].Y1;
      SP.Z_Left_Up=SectorTwo_up_level;
      SP.Location=1;
      SP.BarrierType=0;
      if (SectorOneType==1 || SectorTwoType==1) SP.BarrierType=2;//т.к. двери
      NewSurfaceSegment(&Surface,SP);
     }
    }
   }
   //создаём нижнюю линию раздела
   if (SectorOne_down_level!=SectorTwo_down_level)//разность высот есть
   {
    if (SectorOne_down_level>SectorTwo_down_level)//первый сектор выше второго
    {
     int pos=0; 
     //работа с секторами
     if (SectorOneType==0) pos=cDialog_CreateSimplySector.GetPosition(SectorOne,(float)(cDialog_CreateSegment.Segment[n].X1),(float)(cDialog_CreateSegment.Segment[n].Y1),(float)(cDialog_CreateSegment.Segment[n].X2),(float)(cDialog_CreateSegment.Segment[n].Y2));
     if (SectorOneType==1) pos=cDialog_CreateSimplyDoor.GetPosition(SectorOne,(float)(cDialog_CreateSegment.Segment[n].X1),(float)(cDialog_CreateSegment.Segment[n].Y1),(float)(cDialog_CreateSegment.Segment[n].X2),(float)(cDialog_CreateSegment.Segment[n].Y2));
     //работа с секторами
     if (pos==0)
     {
      MessageBox(NULL,"Не определить с какой стороны сектор от линии раздела","Ошибка",MB_OK);
      DeleteAllSurface(&Surface);//удалим все старые поверхности
      return;
     }
     if (pos<0)//сектор справа(т.е. всё нормально, поверхность будет видна при таком направлении)
     {
      SP.X[3]=cDialog_CreateSegment.Segment[n].X1;
      SP.Y[3]=cDialog_CreateSegment.Segment[n].Y1;
      SP.Z[3]=SectorTwo_down_level;
      SP.X[2]=cDialog_CreateSegment.Segment[n].X1;
      SP.Y[2]=cDialog_CreateSegment.Segment[n].Y1;
      SP.Z[2]=SectorOne_down_level;
      SP.X[1]=cDialog_CreateSegment.Segment[n].X2;
      SP.Y[1]=cDialog_CreateSegment.Segment[n].Y2;
      SP.Z[1]=SectorOne_down_level;
      SP.X[0]=cDialog_CreateSegment.Segment[n].X2;
      SP.Y[0]=cDialog_CreateSegment.Segment[n].Y2;
      SP.Z[0]=SectorTwo_down_level;
      SP.Normal.X=(SP.Y[2]-SP.Y[1]);
      SP.Normal.Y=-(SP.X[2]-SP.X[1]);
      SP.Normal.Z=0;
      SP.Texture=cDialog_CreateSegment.Segment[n].DownTexture;
      SP.Segment=n;
      SP.X_Left_Up=cDialog_CreateSegment.Segment[n].X1;
      SP.Y_Left_Up=cDialog_CreateSegment.Segment[n].Y1;
      SP.Z_Left_Up=SectorOne_down_level;
      SP.Location=2;
      SP.BarrierType=0;
      if (SectorOneType==1 || SectorTwoType==1) SP.BarrierType=2;//т.к. двери
      NewSurfaceSegment(&Surface,SP);
     }
     else//сектор слева(т.е. нужно менять направление линии)
     {
      SP.X[3]=cDialog_CreateSegment.Segment[n].X2;
      SP.Y[3]=cDialog_CreateSegment.Segment[n].Y2;
      SP.Z[3]=SectorTwo_down_level;
      SP.X[2]=cDialog_CreateSegment.Segment[n].X2;
      SP.Y[2]=cDialog_CreateSegment.Segment[n].Y2;
      SP.Z[2]=SectorOne_down_level;
      SP.X[1]=cDialog_CreateSegment.Segment[n].X1;
      SP.Y[1]=cDialog_CreateSegment.Segment[n].Y1;
      SP.Z[1]=SectorOne_down_level;
      SP.X[0]=cDialog_CreateSegment.Segment[n].X1;
      SP.Y[0]=cDialog_CreateSegment.Segment[n].Y1;
      SP.Z[0]=SectorTwo_down_level;
      SP.Normal.X=(SP.Y[2]-SP.Y[1]);
      SP.Normal.Y=-(SP.X[2]-SP.X[1]);
      SP.Normal.Z=0;
      SP.Texture=cDialog_CreateSegment.Segment[n].DownTexture;
      SP.Segment=n;
      SP.X_Left_Up=cDialog_CreateSegment.Segment[n].X1;
      SP.Y_Left_Up=cDialog_CreateSegment.Segment[n].Y1;
      SP.Z_Left_Up=SectorOne_down_level;
      SP.Location=2;
      SP.BarrierType=0;
      if (SectorOneType==1 || SectorTwoType==1) SP.BarrierType=2;//т.к. двери
      NewSurfaceSegment(&Surface,SP);
     }
    }
    else//первый сектор ниже второго
    {
     int pos=0;
     //работа с секторами
     if (SectorTwoType==0) pos=cDialog_CreateSimplySector.GetPosition(SectorTwo,(float)(cDialog_CreateSegment.Segment[n].X1),(float)(cDialog_CreateSegment.Segment[n].Y1),(float)(cDialog_CreateSegment.Segment[n].X2),(float)(cDialog_CreateSegment.Segment[n].Y2));
     if (SectorTwoType==1) pos=cDialog_CreateSimplyDoor.GetPosition(SectorTwo,(float)(cDialog_CreateSegment.Segment[n].X1),(float)(cDialog_CreateSegment.Segment[n].Y1),(float)(cDialog_CreateSegment.Segment[n].X2),(float)(cDialog_CreateSegment.Segment[n].Y2));
     //работа с секторами
     if (pos==0)
     {
      MessageBox(NULL,"Не определить с какой стороны сектор от линии раздела","Ошибка",MB_OK);
      DeleteAllSurface(&Surface);//удалим все старые поверхности
      return;
     }
     if (pos<0)//сектор справа(т.е. всё нормально, поверхность будет видна при таком направлении)
     {
      SP.X[3]=cDialog_CreateSegment.Segment[n].X1;
      SP.Y[3]=cDialog_CreateSegment.Segment[n].Y1;
      SP.Z[3]=SectorOne_down_level;
      SP.X[2]=cDialog_CreateSegment.Segment[n].X1;
      SP.Y[2]=cDialog_CreateSegment.Segment[n].Y1;
      SP.Z[2]=SectorTwo_down_level;
      SP.X[1]=cDialog_CreateSegment.Segment[n].X2;
      SP.Y[1]=cDialog_CreateSegment.Segment[n].Y2;
      SP.Z[1]=SectorTwo_down_level;
      SP.X[0]=cDialog_CreateSegment.Segment[n].X2;
      SP.Y[0]=cDialog_CreateSegment.Segment[n].Y2;
      SP.Z[0]=SectorOne_down_level;
      SP.Normal.X=(SP.Y[2]-SP.Y[1]);
      SP.Normal.Y=-(SP.X[2]-SP.X[1]);
      SP.Normal.Z=0;
      SP.Texture=cDialog_CreateSegment.Segment[n].DownTexture;
      SP.Segment=n;
      SP.X_Left_Up=cDialog_CreateSegment.Segment[n].X1;
      SP.Y_Left_Up=cDialog_CreateSegment.Segment[n].Y1;
      SP.Z_Left_Up=SectorTwo_down_level;
      SP.Location=2;
      SP.BarrierType=0;
      if (SectorOneType==1 || SectorTwoType==1) SP.BarrierType=2;//т.к. двери
      NewSurfaceSegment(&Surface,SP);
     }
     else//сектор слева(т.е. нужно менять направление линии)
     {
      SP.X[3]=cDialog_CreateSegment.Segment[n].X2;
      SP.Y[3]=cDialog_CreateSegment.Segment[n].Y2;
      SP.Z[3]=SectorOne_down_level;
      SP.X[2]=cDialog_CreateSegment.Segment[n].X2;
      SP.Y[2]=cDialog_CreateSegment.Segment[n].Y2;
      SP.Z[2]=SectorTwo_down_level;
      SP.X[1]=cDialog_CreateSegment.Segment[n].X1;
      SP.Y[1]=cDialog_CreateSegment.Segment[n].Y1;
      SP.Z[1]=SectorTwo_down_level;
      SP.X[0]=cDialog_CreateSegment.Segment[n].X1;
      SP.Y[0]=cDialog_CreateSegment.Segment[n].Y1;
      SP.Z[0]=SectorOne_down_level;
      SP.Normal.X=(SP.Y[2]-SP.Y[1]);
      SP.Normal.Y=-(SP.X[2]-SP.X[1]);
      SP.Normal.Z=0;
      SP.Texture=cDialog_CreateSegment.Segment[n].DownTexture;
      SP.Segment=n;
      SP.X_Left_Up=cDialog_CreateSegment.Segment[n].X1;
      SP.Y_Left_Up=cDialog_CreateSegment.Segment[n].Y1;
      SP.Z_Left_Up=SectorTwo_down_level;
      SP.Location=2;
      SP.BarrierType=0;
      if (SectorOneType==1 || SectorTwoType==1) SP.BarrierType=2;//т.к. двери
      NewSurfaceSegment(&Surface,SP);
     }
    }
   }
  }
 }
 //добавим поверхности пола и потолка
 //работа с секторами
 for(n=0;n<sKeyData.MaximumNumberOfSimplySector;n++)
 {
  cDialog_CreateSimplySector.GenerateFloor(n,&SCP);
  NewSurfaceSector(&Surface,SCP);
  cDialog_CreateSimplySector.GenerateCeiling(n,&SCP);
  NewSurfaceSector(&Surface,SCP);
 }
 for(n=0;n<sKeyData.MaximumNumberOfSimplyDoor;n++)
 {
  cDialog_CreateSimplyDoor.GenerateFloor(n,&SCP);
  NewSurfaceSector(&Surface,SCP);
  cDialog_CreateSimplyDoor.GenerateCeiling(n,&SCP);
  NewSurfaceSector(&Surface,SCP);
 }
 //работа с секторами
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------
 //поскольку работать со связанным списком несколько неудобно,преобразуем его
 //подсчитаем количество элементов списка
 if (Surface==NULL) return;
 int SurfaceAmount=0;
 SSurface *CurrentSurface=Surface;
 while(1)
 {
  SurfaceAmount++;
  if (CurrentSurface->Previous==NULL) break;
  CurrentSurface=CurrentSurface->Previous;
 }
 SSurface *RenderSurface=new SSurface[SurfaceAmount+1];
 CPolygon cPolygon_Stage;
 cPolygon_Stage.ClearAllPolygon();
 //и перепишем их в новую структуру
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
 DeleteAllSurface(&Surface);//удалим все старые поверхности
 //теперь у нас сформированы все поверхности для рендеринга
 double MaximumElement=sKeyData.MaximumNumberOfLine;//нужно для определения прогресса
 MaximumElement+=sKeyData.MaximumNumberOfSimplySector;
 MaximumElement+=sKeyData.MaximumNumberOfSimplyDoor;
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------
 FILE *File=fopen(FileName,"w+b");
 if (File==NULL)
 {
  MessageBox(NULL,"Не могу записать файл.","Ошибка записи",MB_OK|MB_ICONSTOP);
  delete(RenderSurface);
  return;
 }
 //версия программы
 SaveFloat(File,1.0);
 //сохраним источники света на карте
 fprintf(File,"SLightingS STRUCTURE");
 SaveInt(File,sKeyData.MaximumNumberOfLighting);
 for(n=0;n<sKeyData.MaximumNumberOfLighting;n++) cDialog_CreateLighting.SaveLightingFromRender(File,n);
 SaveFloat(File,(float)sSettings.Constant_Attenuation);
 SaveFloat(File,(float)sSettings.Linear_Attenuation);
 SaveFloat(File,(float)sSettings.Quadric_Attenuation);
 SaveChar(File,sSettings.R_Ambient);
 SaveChar(File,sSettings.G_Ambient);
 SaveChar(File,sSettings.B_Ambient);
 CLight Light(RenderSurface,SurfaceAmount);//создадим объект для расчёта освещённости и сообщим ему все поверхности
 //-----------------------------------------------------------------------------
 //сообщим количество сегментов на карте
 fprintf(File,"SSegmentS STRUCTURE");
 SaveInt(File,sKeyData.MaximumNumberOfLine);
 //теперь сохраним эти сегменты
 for(n=0;n<sKeyData.MaximumNumberOfLine;n++)
 { 
  cWnd_Progress.cWnd_Progress=(float)((float)(n+1)/(float)(MaximumElement));
  InvalidateRect(sKeyData.hWndcWnd_Progress,NULL,FALSE);
  MSG msg;
  while (PeekMessage(&msg,NULL,0,0,PM_REMOVE))//обработка сообщений Windows
  {
   TranslateMessage(&msg);
   DispatchMessage(&msg);
  }
  cDialog_CreateSegment.SaveSegmentFromRender(File,n);//сохраним параметры сегмента
  //разобъём его и сохраним, но сначала нужно найти поверхность,к которой он относится
  //найдём число поверхностей для него
  int sfc=0;//всего поверхностей для данного сегмента
  for(m=0;m<SurfaceAmount;m++)
  {
   if (RenderSurface[m].Segment==n) sfc++;
  }
  SaveInt(File,sfc);//сохраним это число
  for(m=0;m<SurfaceAmount;m++)
  {
   if (RenderSurface[m].Segment==n)//это поверхность является частью сегмента
   {
    //сохраним её положение
    SaveInt(File,RenderSurface[m].Location);
    //сохраним её нормаль
    SaveFloat(File,(float)(-RenderSurface[m].Normal.X));
    SaveFloat(File,(float)(RenderSurface[m].Normal.Z));
    SaveFloat(File,(float)(-RenderSurface[m].Normal.Y));
    //и создаём полигоны
    CPolygon cPolygon_Fragment;
    cPolygon_Fragment.ClearAllPolygon();
    if (m>=cPolygon_Stage.AmountOfPolygons)
    {
     MessageBox(NULL,"Error","",MB_OK);
     continue;
    }
    //теперь этот объект определил, какие грани могут затенять эту поверхность
    //для каждого источника света и выбрал эти источники света
    Light.SetCurrentSurface(m,n,-1,-1,&cPolygon_Stage);
    //сохраним число и номера источников света
    SaveChar(File,Light.LightingAmount);
    for(l=0;l<Light.LightingAmount;l++) SaveInt(File,Light.LightingNumber[l]);
    //сохраним дополнительные параметры поверхности
    if (RenderSurface[m].Location==1 || RenderSurface[m].Location==0)
    {
     SaveChar(File,cDialog_CreateSegment.Segment[n].UpEmissionR);
     SaveChar(File,cDialog_CreateSegment.Segment[n].UpEmissionG);
     SaveChar(File,cDialog_CreateSegment.Segment[n].UpEmissionB);
    }
    if (RenderSurface[m].Location==2)
    {
     SaveChar(File,cDialog_CreateSegment.Segment[n].DownEmissionR);
     SaveChar(File,cDialog_CreateSegment.Segment[n].DownEmissionG);
     SaveChar(File,cDialog_CreateSegment.Segment[n].DownEmissionB);
    }
    //ну а теперь начинаем
    SPolygon sPolygon_Basic=cPolygon_Stage.GetPolygonForIndex(m);
    cPolygon_Fragment.CreateNewPolygon(sPolygon_Basic);//добавили самого себя
    BOOL LightingEnable[8];
    LightingEnable[0]=TRUE;//источники света все включены
    LightingEnable[1]=TRUE;
    LightingEnable[2]=TRUE;
    LightingEnable[3]=TRUE;
    LightingEnable[4]=TRUE;
    LightingEnable[5]=TRUE;
    LightingEnable[6]=TRUE;
    LightingEnable[7]=TRUE;
    cPolygon_Fragment.SetPolygonLightingEnableForIndex(0,LightingEnable);
    for(l=0;l<Light.LightingAmount;l++)//источник, освещающий полигон
    {
     //посмотрим, есть ли такой полигон, что полностью закрывает фрагмент
     for(k=0;k<cPolygon_Fragment.GetAmountOfPolygons();k++)//для каждого фрагмента считаем тень и создаём суб-фрагменты
     {
      for(r=0;r<Light.SphereMaxSurfaceFromLight[l];r++)//полигон, создающий тень
      {
       u=Light.SphereFromLight[l][r];
       if (u==m) continue;//сами на себя тень не отбрасываем
       SPolygon sPolygon_ShadowSource=cPolygon_Stage.GetPolygonForIndex(u);
       CPolygon cPolygon_Temporary;
       BOOL EnableShadow=GenerateShadow(sPolygon_ShadowSource,cPolygon_Fragment.GetPolygonForIndex(k),Light.sPoint_Lighting[l],&cPolygon_Temporary);
       if (EnableShadow==TRUE && cPolygon_Temporary.GetAmountOfPolygons()==1)//весь фрагмент в тени
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
     for(r=0;r<Light.SphereMaxSurfaceFromLight[l];r++)//полигон, создающий тень
     {
      u=Light.SphereFromLight[l][r];
      if (u==m) continue;//сами на себя тень не отбрасываем
      SPolygon sPolygon_ShadowSource=cPolygon_Stage.GetPolygonForIndex(u);
      CPolygon cPolygon_NewFragment;
      cPolygon_NewFragment.ClearAllPolygon();
      for(k=0;k<cPolygon_Fragment.GetAmountOfPolygons();k++)//для каждого фрагмента считаем тень и создаём суб-фрагменты
      {
       SPolygon sPolygon_F=cPolygon_Fragment.GetPolygonForIndex(k);
       if (sPolygon_F.LightingEnable[l]==FALSE)
       {
        cPolygon_NewFragment.CreateNewPolygon(sPolygon_F);
        continue;
       }
       CPolygon cPolygon_Temporary;
       BOOL EnableShadow=GenerateShadow(sPolygon_ShadowSource,sPolygon_F,Light.sPoint_Lighting[l],&cPolygon_Temporary);
       //подключим источники света
       for(v=0;v<cPolygon_Temporary.GetAmountOfPolygons();v++)
       {
        SPolygon sPolygon=cPolygon_Fragment.GetPolygonForIndex(k);
        cPolygon_Temporary.SetPolygonLightingEnableForIndex(v,sPolygon.LightingEnable);
        if (v==0 && EnableShadow==TRUE)//если тень была
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
    //сохраним все созданные фрагменты
    SaveInt(File,cPolygon_Fragment.GetAmountOfPolygons());
    for(u=0;u<cPolygon_Fragment.GetAmountOfPolygons();u++)
    {
     SPolygon sPolygon=cPolygon_Fragment.GetPolygonForIndex(u);
     //сохраним состояниия источников света для данного полигона
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
      //сохраним текстурные координаты
      double dx=(RenderSurface[m].X_Left_Up-sPolygon.sPoint_Array[k].X);
      double dy=(RenderSurface[m].Y_Left_Up-sPolygon.sPoint_Array[k].Y);
      double tlen=sqrt(dx*dx+dy*dy);
      double tu=tlen/128.0;
      double tv=(RenderSurface[m].Z_Left_Up-sPolygon.sPoint_Array[k].Z)/128.0;
      cDialog_SelectTexture.CreateTextureCoord(RenderSurface[m].Texture,&tu,&tv);
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
 //сообщим количество простых секторов на карте
 fprintf(File,"SIMPLYSECTORS STRUCTURE");
 SaveInt(File,sKeyData.MaximumNumberOfSimplySector);
 //теперь сохраним эти сектора
 for(n=0;n<sKeyData.MaximumNumberOfSimplySector;n++)
 { 
  cWnd_Progress.cWnd_Progress=(float)((float)(1+n+sKeyData.MaximumNumberOfLine)/(float)(MaximumElement));
  InvalidateRect(sKeyData.hWndcWnd_Progress,NULL,FALSE);
  MSG msg;
  while (PeekMessage(&msg,NULL,0,0,PM_REMOVE))//обработка сообщений Windows
  {
   TranslateMessage(&msg);
   DispatchMessage(&msg);
  }
  cDialog_CreateSimplySector.SaveSectorFromRender(File,n);//сохраним параметры сектора
  //разобъём его и сохраним, но сначала нужно найти поверхность,к которой он относится
  //число поверхностей для него 2
  for(m=0;m<SurfaceAmount;m++)
  {
   if (RenderSurface[m].SectorType==0 && RenderSurface[m].Sector==n)//это наша поверхность
   {
    //сохраним её положение
    SaveInt(File,RenderSurface[m].Location);
    //сохраним её нормаль
    SaveFloat(File,(float)(-RenderSurface[m].Normal.X));
    SaveFloat(File,(float)(RenderSurface[m].Normal.Z));
    SaveFloat(File,(float)(-RenderSurface[m].Normal.Y));
    //и создаём полигоны
    CPolygon cPolygon_Fragment;
    cPolygon_Fragment.ClearAllPolygon();
    if (m>=cPolygon_Stage.AmountOfPolygons)
    {
     MessageBox(NULL,"Error","",MB_OK);
     continue;
    }
    //теперь этот объект определил, какие грани могут затенять эту поверхность
    //для каждого источника света и выбрал эти источники света
    Light.SetCurrentSurface(m,-1,RenderSurface[m].Sector,RenderSurface[m].SectorType,&cPolygon_Stage);
    //сохраним число и номера источников света
    SaveChar(File,Light.LightingAmount);
    for(l=0;l<Light.LightingAmount;l++) SaveInt(File,Light.LightingNumber[l]);
    //сохраним дополнительные параметры поверхности
    if (RenderSurface[m].Location==1 || RenderSurface[m].Location==0)
    {
     SaveChar(File,cDialog_CreateSimplySector.Sector[n].UpEmissionR);
     SaveChar(File,cDialog_CreateSimplySector.Sector[n].UpEmissionG);
     SaveChar(File,cDialog_CreateSimplySector.Sector[n].UpEmissionB);
    }
    if (RenderSurface[m].Location==2)
    {
     SaveChar(File,cDialog_CreateSimplySector.Sector[n].DownEmissionR);
     SaveChar(File,cDialog_CreateSimplySector.Sector[n].DownEmissionG);
     SaveChar(File,cDialog_CreateSimplySector.Sector[n].DownEmissionB);
    }
    SPolygon sPolygon_Basic=cPolygon_Stage.GetPolygonForIndex(m);
    cPolygon_Fragment.CreateNewPolygon(sPolygon_Basic);//добавили самого себя
    BOOL LightingEnable[8];
    LightingEnable[0]=TRUE;//источники света все включены
    LightingEnable[1]=TRUE;
    LightingEnable[2]=TRUE;
    LightingEnable[3]=TRUE;
    LightingEnable[4]=TRUE;
    LightingEnable[5]=TRUE;
    LightingEnable[6]=TRUE;
    LightingEnable[7]=TRUE;
    cPolygon_Fragment.SetPolygonLightingEnableForIndex(0,LightingEnable);
    for(l=0;l<Light.LightingAmount;l++)//источник, освещающий полигон
    {
     //посмотрим, есть ли такой полигон, что полностью закрывает фрагмент
     for(k=0;k<cPolygon_Fragment.GetAmountOfPolygons();k++)//для каждого фрагмента считаем тень и создаём суб-фрагменты
     {
      for(r=0;r<Light.SphereMaxSurfaceFromLight[l];r++)//полигон, создающий тень
      {
       u=Light.SphereFromLight[l][r];
       if (u==m) continue;//сами на себя тень не отбрасываем
       SPolygon sPolygon_ShadowSource=cPolygon_Stage.GetPolygonForIndex(u);
       CPolygon cPolygon_Temporary;
       BOOL EnableShadow=GenerateShadow(sPolygon_ShadowSource,cPolygon_Fragment.GetPolygonForIndex(k),Light.sPoint_Lighting[l],&cPolygon_Temporary);
       if (EnableShadow==TRUE && cPolygon_Temporary.GetAmountOfPolygons()==1)//весь фрагмент в тени
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
     for(r=0;r<Light.SphereMaxSurfaceFromLight[l];r++)//полигон, создающий тень
     {
      u=Light.SphereFromLight[l][r];
      if (u==m) continue;//сами на себя тень не отбрасываем
      SPolygon sPolygon_ShadowSource=cPolygon_Stage.GetPolygonForIndex(u);
      CPolygon cPolygon_NewFragment;
      cPolygon_NewFragment.ClearAllPolygon();
      for(k=0;k<cPolygon_Fragment.GetAmountOfPolygons();k++)//для каждого фрагмента считаем тень и создаём суб-фрагменты
      {
       SPolygon sPolygon_F=cPolygon_Fragment.GetPolygonForIndex(k);
       if (sPolygon_F.LightingEnable[l]==FALSE)
       {
        cPolygon_NewFragment.CreateNewPolygon(sPolygon_F);
        continue;
       }
       CPolygon cPolygon_Temporary;
       BOOL EnableShadow=GenerateShadow(sPolygon_ShadowSource,sPolygon_F,Light.sPoint_Lighting[l],&cPolygon_Temporary);
       //подключим источники света
       for(v=0;v<cPolygon_Temporary.GetAmountOfPolygons();v++)
       {
        SPolygon sPolygon=cPolygon_Fragment.GetPolygonForIndex(k);
        cPolygon_Temporary.SetPolygonLightingEnableForIndex(v,sPolygon.LightingEnable);
        if (v==0 && EnableShadow==TRUE)//если тень была
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
    //сохраним все созданные фрагменты
    SaveInt(File,cPolygon_Fragment.GetAmountOfPolygons());
    for(u=0;u<cPolygon_Fragment.GetAmountOfPolygons();u++)
    {
     SPolygon sPolygon=cPolygon_Fragment.GetPolygonForIndex(u);
     //сохраним состояниия источников света для данного полигона
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
      //сохраним текстурные координаты
      double tu=(sPolygon.sPoint_Array[k].X)/128.0;
      double tv=(sPolygon.sPoint_Array[k].Y)/128.0;
      cDialog_SelectTexture.CreateTextureCoord(RenderSurface[m].Texture,&tu,&tv);
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
 //сообщим количество простых дверей на карте
 fprintf(File,"SIMPLYDOORS STRUCTURE");
 SaveInt(File,sKeyData.MaximumNumberOfSimplyDoor);
 //теперь сохраним эти сектора
 for(n=0;n<sKeyData.MaximumNumberOfSimplyDoor;n++)
 { 
  cWnd_Progress.cWnd_Progress=(float)((float)(1+n+sKeyData.MaximumNumberOfLine+sKeyData.MaximumNumberOfSimplySector)/(float)(MaximumElement));
  InvalidateRect(sKeyData.hWndcWnd_Progress,NULL,FALSE);
  MSG msg;
  while (PeekMessage(&msg,NULL,0,0,PM_REMOVE))//обработка сообщений Windows
  {
   TranslateMessage(&msg);
   DispatchMessage(&msg);
  }
  cDialog_CreateSimplyDoor.SaveSectorFromRender(File,n);//сохраним параметры сектора
  //разобъём его и сохраним, но сначала нужно найти поверхность,к которой он относится
  //число поверхностей для него 2
  for(m=0;m<SurfaceAmount;m++)
  {
   if (RenderSurface[m].SectorType==1 && RenderSurface[m].Sector==n)//это наша поверхность
   {
    //сохраним её положение
    SaveInt(File,RenderSurface[m].Location);
    //сохраним её нормаль
    SaveFloat(File,(float)(-RenderSurface[m].Normal.X));
    SaveFloat(File,(float)(RenderSurface[m].Normal.Z));
    SaveFloat(File,(float)(-RenderSurface[m].Normal.Y));
    //и создаём полигоны
    CPolygon cPolygon_Fragment;
    cPolygon_Fragment.ClearAllPolygon();
    if (m>=cPolygon_Stage.AmountOfPolygons)
    {
     MessageBox(NULL,"Error","",MB_OK);
     continue;
    }
    //теперь этот объект определил, какие грани могут затенять эту поверхность
    //для каждого источника света и выбрал эти источники света
    Light.SetCurrentSurface(m,-1,RenderSurface[m].Sector,RenderSurface[m].SectorType,&cPolygon_Stage);
    //сохраним число и номера источников света
    SaveChar(File,Light.LightingAmount);
    for(l=0;l<Light.LightingAmount;l++) SaveInt(File,Light.LightingNumber[l]);
    //сохраним дополнительные параметры поверхности
    if (RenderSurface[m].Location==1)
    {
     SaveChar(File,cDialog_CreateSimplyDoor.Sector[n].UpEmissionR);
     SaveChar(File,cDialog_CreateSimplyDoor.Sector[n].UpEmissionG);
     SaveChar(File,cDialog_CreateSimplyDoor.Sector[n].UpEmissionB);
    }
    if (RenderSurface[m].Location==2)
    {
     SaveChar(File,cDialog_CreateSimplyDoor.Sector[n].DownEmissionR);
     SaveChar(File,cDialog_CreateSimplyDoor.Sector[n].DownEmissionG);
     SaveChar(File,cDialog_CreateSimplyDoor.Sector[n].DownEmissionB);
    }
    SPolygon sPolygon_Basic=cPolygon_Stage.GetPolygonForIndex(m);
    cPolygon_Fragment.CreateNewPolygon(sPolygon_Basic);//добавили самого себя
    BOOL LightingEnable[8];
    LightingEnable[0]=TRUE;//источники света все включены
    LightingEnable[1]=TRUE;
    LightingEnable[2]=TRUE;
    LightingEnable[3]=TRUE;
    LightingEnable[4]=TRUE;
    LightingEnable[5]=TRUE;
    LightingEnable[6]=TRUE;
    LightingEnable[7]=TRUE;
    cPolygon_Fragment.SetPolygonLightingEnableForIndex(0,LightingEnable);
    for(l=0;l<Light.LightingAmount;l++)//источник, освещающий полигон
    {
     //посмотрим, есть ли такой полигон, что полностью закрывает фрагмент
     for(k=0;k<cPolygon_Fragment.GetAmountOfPolygons();k++)//для каждого фрагмента считаем тень и создаём суб-фрагменты
     {
      for(r=0;r<Light.SphereMaxSurfaceFromLight[l];r++)//полигон, создающий тень
      {
       u=Light.SphereFromLight[l][r];
       if (u==m) continue;//сами на себя тень не отбрасываем
       SPolygon sPolygon_ShadowSource=cPolygon_Stage.GetPolygonForIndex(u);
       CPolygon cPolygon_Temporary;
       BOOL EnableShadow=GenerateShadow(sPolygon_ShadowSource,cPolygon_Fragment.GetPolygonForIndex(k),Light.sPoint_Lighting[l],&cPolygon_Temporary);
       if (EnableShadow==TRUE && cPolygon_Temporary.GetAmountOfPolygons()==1)//весь фрагмент в тени
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
     for(r=0;r<Light.SphereMaxSurfaceFromLight[l];r++)//полигон, создающий тень
     {
      u=Light.SphereFromLight[l][r];
      if (u==m) continue;//сами на себя тень не отбрасываем
      SPolygon sPolygon_ShadowSource=cPolygon_Stage.GetPolygonForIndex(u);
      CPolygon cPolygon_NewFragment;
      cPolygon_NewFragment.ClearAllPolygon();
      for(k=0;k<cPolygon_Fragment.GetAmountOfPolygons();k++)//для каждого фрагмента считаем тень и создаём суб-фрагменты
      {
       SPolygon sPolygon_F=cPolygon_Fragment.GetPolygonForIndex(k);
       if (sPolygon_F.LightingEnable[l]==FALSE)
       {
        cPolygon_NewFragment.CreateNewPolygon(sPolygon_F);
        continue;
       }
       CPolygon cPolygon_Temporary;
       BOOL EnableShadow=GenerateShadow(sPolygon_ShadowSource,sPolygon_F,Light.sPoint_Lighting[l],&cPolygon_Temporary);
       //подключим источники света
       for(v=0;v<cPolygon_Temporary.GetAmountOfPolygons();v++)
       {
        SPolygon sPolygon=cPolygon_Fragment.GetPolygonForIndex(k);
        cPolygon_Temporary.SetPolygonLightingEnableForIndex(v,sPolygon.LightingEnable);
        if (v==0 && EnableShadow==TRUE)//если тень была
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
    //сохраним все созданные фрагменты
    SaveInt(File,cPolygon_Fragment.GetAmountOfPolygons());
    for(u=0;u<cPolygon_Fragment.GetAmountOfPolygons();u++)
    {
     SPolygon sPolygon=cPolygon_Fragment.GetPolygonForIndex(u);
     //сохраним состояниия источников света для данного полигона
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
      //сохраним текстурные координаты
      double tu=(sPolygon.sPoint_Array[k].X)/128.0;
      double tv=(sPolygon.sPoint_Array[k].Y)/128.0;
      cDialog_SelectTexture.CreateTextureCoord(RenderSurface[m].Texture,&tu,&tv);
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
 //сохраним стартовую позицию
 StartPoscWnd_Form.SaveStartPositionFromRender(File);
 //сохраним некоторые глобальные параметры
 fprintf(File,"GLOBAL FOG STRUCTURE");
 SaveFloat(File,(float)(((float)(sSettings.R_Fog)/255.0)));
 SaveFloat(File,(float)(((float)(sSettings.G_Fog)/255.0)));
 SaveFloat(File,(float)(((float)(sSettings.B_Fog)/255.0)));
 SaveFloat(File,(float)(((float)(sSettings.Fog_Density)/1000000000.0)));
 SaveChar(File,sSettings.Fog_Enable);
 fclose(File);
  
 cPolygon_Stage.ClearAllPolygon();
 delete(RenderSurface);
}
 

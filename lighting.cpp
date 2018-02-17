#include "lighting.h"

extern CREATELIGHTINGFORM CreateLightingForm;
extern SETUP SetUp;//настройки редактора

//------------------------------------------------------------------------------
LIGHT::LIGHT(SURFACE *SurfacePointer,int AllSurfaceNumber)
{
 Surface=SurfacePointer;
 AllSurface=AllSurfaceNumber;
 //сразу же выделим память под массив данных сферы затенения
 for(int n=0;n<8;n++) SphereFromLight[n]=new int[AllSurface+1];
}
LIGHT::~LIGHT(void)
{
 for(int n=0;n<8;n++) delete(SphereFromLight[n]);
}
//------------------------------------------------------------------------------
void LIGHT::SetCurrentSurface(int sfc,int segment,int sector,int sectortype,CPolygon *cPolygon_Stage)
{
 int n,m,k,l,u;
 CurrentSurface=sfc;
 //найдём центральную точку этой поверхности
 double xc=0;
 double yc=0;
 double zc=0;
 for(n=0;n<Surface[sfc].Vertex;n++)
 {
  xc+=Surface[sfc].X[n];
  yc+=Surface[sfc].Y[n];
  zc+=Surface[sfc].Z[n];
 }
 if (Surface[sfc].Vertex>0)
 {
  xc/=Surface[sfc].Vertex;
  yc/=Surface[sfc].Vertex;
  zc/=Surface[sfc].Vertex;
 }
 //определим источники света, максимальным образом влияющие на эту поверхность
 double C_A=SetUp.Constant_Attenuation;
 double L_A=SetUp.Linear_Attenuation;
 double Q_A=SetUp.Quadric_Attenuation;
  
  
 int *light_array=new int[KeyData.MaximumNumberOfLighting+1];
 float *light_maxforce=new float[KeyData.MaximumNumberOfLighting+1];
 int EnabledLightingAmount=0;
 for(n=0;n<KeyData.MaximumNumberOfLighting;n++)
 {
  SPoint sPoint_Light;
  sPoint_Light.X=CreateLightingForm.Lighting[n].X*16.0;
  sPoint_Light.Y=CreateLightingForm.Lighting[n].Y*16.0;
  sPoint_Light.Z=CreateLightingForm.Lighting[n].Z;
  BOOL LightEnable=TRUE;
  //посмотрим, может быть этот источник вообще не освещает поверхность
  //нет ли такого полигона, который сразу закрывает поверхность ? (это ускорит рендеринг)
  //создадим список кандидатов на затенение
  LightingNumber[0]=n;
  sPoint_Lighting[0].X=sPoint_Light.X;
  sPoint_Lighting[0].Y=sPoint_Light.Y;
  sPoint_Lighting[0].Z=sPoint_Light.Z;
  SetShadowSurface(CurrentSurface,xc,yc,zc,0);
  for(u=0;u<SphereMaxSurfaceFromLight[0];u++)//полигон, создающий тень
  {
   m=SphereFromLight[0][u];
   if (CurrentSurface==m) continue;//сами на себя тень не отбрасываем
   if (Surface[m].BarrierType==1 || Surface[m].BarrierType==2) continue;//стеклянные грани и двери тоже не создают тени
   //   if (Surface[m].Segment==segment || (Surface[m].Sector==sector && Surface[m].SectorType==sectortype)) continue;
   SPolygon sPolygon_ShadowSource=cPolygon_Stage->GetPolygonForIndex(m);
   CPolygon cPolygon_Temporary;
   BOOL EnableShadow=GenerateShadow(sPolygon_ShadowSource,cPolygon_Stage->GetPolygonForIndex(CurrentSurface),sPoint_Light,&cPolygon_Temporary);
   if (EnableShadow==TRUE && cPolygon_Temporary.GetAmountOfPolygons()==1)//весь фрагмент в тени
   {
    LightEnable=FALSE;
    cPolygon_Temporary.ClearAllPolygon();
    break;
   }
   cPolygon_Temporary.ClearAllPolygon();
  }
  if (LightEnable==FALSE) continue;//не подходит нам
  CPolygon cPolygon_Fragment;
  cPolygon_Fragment.CreateNewPolygon(cPolygon_Stage->GetPolygonForIndex(CurrentSurface));
  while(1)
  {
   int shadowon=FALSE;
   for(u=0;u<SphereMaxSurfaceFromLight[0];u++)//полигон, создающий тень
   {  
    m=SphereFromLight[0][u];
    if (CurrentSurface==m) continue;//сами на себя тень не отбрасываем
    if (Surface[m].BarrierType==1 || Surface[m].BarrierType==2) continue;//стеклянные грани и двери тоже не создают тени
    //  if (Surface[m].Segment==segment) continue;
    CPolygon cPolygon_NewFragment; 
    for(k=0;k<cPolygon_Fragment.GetAmountOfPolygons();k++)//для каждого фрагмента считаем тень и создаём суб-фрагменты
    {
     SPolygon sPolygon_ShadowSource=cPolygon_Stage->GetPolygonForIndex(m);
     CPolygon cPolygon_Temporary;
     BOOL EnableShadow=GenerateShadow(sPolygon_ShadowSource,cPolygon_Fragment.GetPolygonForIndex(k),sPoint_Light,&cPolygon_Temporary);
     if (EnableShadow==FALSE) 
     { 
      for(l=0;l<cPolygon_Temporary.GetAmountOfPolygons();l++)
      {
       SPolygon sPolygon=cPolygon_Temporary.GetPolygonForIndex(l);
       cPolygon_NewFragment.CreateNewPolygon(sPolygon);
      }
     }
     else
     {
      shadowon=TRUE;
      for(l=1;l<cPolygon_Temporary.GetAmountOfPolygons();l++)
      {
       SPolygon sPolygon=cPolygon_Temporary.GetPolygonForIndex(l);
       cPolygon_NewFragment.CreateNewPolygon(sPolygon);
      }
     }
     cPolygon_Temporary.ClearAllPolygon();
    }
    if (cPolygon_NewFragment.GetAmountOfPolygons()==0)
    { 
     LightEnable=FALSE;
     cPolygon_Fragment.ClearAllPolygon();
     cPolygon_NewFragment.ClearAllPolygon();
     break;
    }
    cPolygon_Fragment.ClearAllPolygon();
    for(k=0;k<cPolygon_NewFragment.GetAmountOfPolygons();k++)
    {
     SPolygon sPolygon=cPolygon_NewFragment.GetPolygonForIndex(k);
     cPolygon_Fragment.CreateNewPolygon(sPolygon);
    }
    cPolygon_NewFragment.ClearAllPolygon();
   }
   if (LightEnable==FALSE) break;
   if (shadowon==FALSE)
   {
    LightEnable=TRUE;
    break;
   }
  }
  cPolygon_Fragment.ClearAllPolygon();
  if (LightEnable==FALSE) continue;//не подходит нам
  //раз освещает - участвует в конкурсе
  light_array[EnabledLightingAmount]=n;
  for(m=0;m<Surface[CurrentSurface].Vertex;m++)
  {
   double x=Surface[CurrentSurface].X[m];
   double y=Surface[CurrentSurface].Y[m];
   double z=Surface[CurrentSurface].Z[m];
   double lx=CreateLightingForm.Lighting[n].X*16.0-x;
   double ly=CreateLightingForm.Lighting[n].Y*16.0-y;
   double lz=CreateLightingForm.Lighting[n].Z-z;
   double dist=sqrt(lx*lx+ly*ly+lz*lz);//дистанция между источником и точкой поверхности
   if (dist!=0)
   {
    lx=lx/dist;
    ly=ly/dist;
    lz=lz/dist;
   }
   double nx=Surface[CurrentSurface].Normal.X;
   double ny=Surface[CurrentSurface].Normal.Y;
   double nz=Surface[CurrentSurface].Normal.Z;
   double normalproduct=lx*nx+ly*ny+lz*nz;
   if (normalproduct<=0 && Surface[CurrentSurface].BarrierType!=1 && Surface[CurrentSurface].BarrierType!=2)//это задняя грань, следовательно, не освещаем её этим источником
   {
    light_maxforce[EnabledLightingAmount]=0;//сила излучения данного источника для данной грани 0
    break;
   }
   normalproduct=fabs(normalproduct);
   double d=normalproduct/(C_A+L_A*dist+Q_A*dist*dist);
   float rf=(float)(d*CreateLightingForm.Lighting[n].R);
   float gf=(float)(d*CreateLightingForm.Lighting[n].G);
   float bf=(float)(d*CreateLightingForm.Lighting[n].B);
   float light_force=rf+gf+bf;
   if (light_maxforce[EnabledLightingAmount]<light_force) light_maxforce[EnabledLightingAmount]=light_force;
  }
  EnabledLightingAmount++;
 }
 //сортируем источники по силе воздействия на поверхность
 for(n=0;n<EnabledLightingAmount;n++)
 for(m=0;m<EnabledLightingAmount-1;m++)
 {
  if (light_maxforce[m]<light_maxforce[m+1])
  {
   int light=light_array[m+1];
   light_array[m+1]=light_array[m];
   light_array[m]=light;
   float force=light_maxforce[m+1];
   light_maxforce[m+1]=light_maxforce[m];
   light_maxforce[m]=force;
  }
 }
 LightingAmount=0;
 int limit=8;
 if (limit>EnabledLightingAmount) limit=EnabledLightingAmount;
 for(n=0;n<limit;n++)
 { 
  if ((light_maxforce[n]/765.0)<0.02) break;
  int lighting=light_array[n];
  LightingNumber[LightingAmount]=lighting;
  sPoint_Lighting[LightingAmount].X=CreateLightingForm.Lighting[lighting].X*16.0;
  sPoint_Lighting[LightingAmount].Y=CreateLightingForm.Lighting[lighting].Y*16.0;
  sPoint_Lighting[LightingAmount].Z=CreateLightingForm.Lighting[lighting].Z;
  LightingAmount++;
 }
 delete(light_array);
 delete(light_maxforce);
  
 //создадим набор плоскостей для определения попавших в область затенения поверхностей
 int Vertex=Surface[CurrentSurface].Vertex;
 int Planes=Vertex+1;
 double *tx1=new double[Planes+1];
 double *ty1=new double[Planes+1];
 double *tz1=new double[Planes+1];
 double *tx2=new double[Planes+1];
 double *ty2=new double[Planes+1];
 double *tz2=new double[Planes+1];
 double *tx3=new double[Planes+1];
 double *ty3=new double[Planes+1];
 double *tz3=new double[Planes+1];
 int *tpos=new int[Planes+1];//положение точки центра полигона относительно плоскостей
 SVector *tNormal=new SVector[Planes+1];//нормали к плоскостям
  
 //начинаем определение возможных поверхностей затенения
 for(n=0;n<LightingAmount;n++)
 {
  double lx=sPoint_Lighting[n].X;
  double ly=sPoint_Lighting[n].Y;
  double lz=sPoint_Lighting[n].Z;
  for(m=0;m<Vertex;m++)
  {
   int i1=m;
   int i2=m+1;
   if (i2>=Vertex) i2-=Vertex;
   tx1[m]=lx;
   ty1[m]=ly;
   tz1[m]=lz;
   tx2[m]=Surface[CurrentSurface].X[i1];
   ty2[m]=Surface[CurrentSurface].Y[i1];
   tz2[m]=Surface[CurrentSurface].Z[i1];
   tx3[m]=Surface[CurrentSurface].X[i2];
   ty3[m]=Surface[CurrentSurface].Y[i2];
   tz3[m]=Surface[CurrentSurface].Z[i2];
   SVector V1=CreateVector(tx2[m]-tx1[m],ty2[m]-ty1[m],tz2[m]-tz1[m]);
   SVector V2=CreateVector(tx3[m]-tx2[m],ty3[m]-ty2[m],tz3[m]-tz2[m]);
   tNormal[m]=NormalizeVector(VectorProduct(V1,V2));
   //считаем положение центральной точки полигона
   double A=tNormal[m].X;
   double B=tNormal[m].Y;
   double C=tNormal[m].Z;
   double D=-A*tx1[m]-B*ty1[m]-C*tz1[m];
   double pos=A*xc+B*yc+C*zc+D;
   if (pos>EPS) tpos[m]=1;
   if (pos<-EPS) tpos[m]=-1;
   if (pos>=-EPS && pos<=EPS) tpos[m]=0;
  }
  //добавим сюда и саму поверхность 
  tx1[Vertex]=Surface[CurrentSurface].X[0];
  ty1[Vertex]=Surface[CurrentSurface].Y[0];
  tz1[Vertex]=Surface[CurrentSurface].Z[0];
  tx2[Vertex]=Surface[CurrentSurface].X[1];
  ty2[Vertex]=Surface[CurrentSurface].Y[1];
  tz2[Vertex]=Surface[CurrentSurface].Z[1];
  tx3[Vertex]=Surface[CurrentSurface].X[2];
  ty3[Vertex]=Surface[CurrentSurface].Y[2];
  tz3[Vertex]=Surface[CurrentSurface].Z[2];
  SVector V1=CreateVector(tx2[Vertex]-tx1[Vertex],ty2[Vertex]-ty1[Vertex],tz2[Vertex]-tz1[Vertex]);
  SVector V2=CreateVector(tx3[Vertex]-tx2[Vertex],ty3[Vertex]-ty2[Vertex],tz3[Vertex]-tz2[Vertex]);
  tNormal[Vertex]=NormalizeVector(VectorProduct(V1,V2));
  //считаем положение точки источника света
  double A=tNormal[Vertex].X;
  double B=tNormal[Vertex].Y;
  double C=tNormal[Vertex].Z;
  double D=-A*tx1[Vertex]-B*ty1[Vertex]-C*tz1[Vertex];
  double pos=A*lx+B*ly+C*lz+D;
  if (pos>EPS) tpos[Vertex]=1;
  if (pos<-EPS) tpos[Vertex]=-1;
  if (pos>=-EPS && pos<=EPS) tpos[Vertex]=0;
  //проверяем возможность затенения
  int s=0;  
  for(m=0;m<AllSurface;m++)
  {
   if (m==CurrentSurface) continue;//сами себя затенять мы ещё не научились
   if (Surface[m].BarrierType==1 || Surface[m].BarrierType==2) continue;//стеклянные грани и двери тоже не создают тени
   int shadow=1;//тень есть
   //посмотрим не находятся ли все точки с противоположной эталону стороны
   //для какой-либо стороны пирамиды
   for(l=0;l<Planes;l++)
   {
    double A=tNormal[l].X;
    double B=tNormal[l].Y;
    double C=tNormal[l].Z;
    double D=-A*tx1[l]-B*ty1[l]-C*tz1[l];
    int ok=1;
    for(k=0;k<Surface[m].Vertex;k++)
    {
     double x=Surface[m].X[k];
     double y=Surface[m].Y[k];
     double z=Surface[m].Z[k];
     double pos=A*x+B*y+C*z+D;
     if (pos>EPS) pos=1;
     if (pos<-EPS) pos=-1;
     if (pos>=-EPS && pos<=EPS) pos=0;
     if (tpos[l]*pos>=0)//точка лежит так же как и эталон
     {
      ok=0;
      break;
     }
    }
    if (ok==1) //нашлась такая сторона
    {
     shadow=0;//тени нет
     break;
    }
   }
   if (shadow==1)
   {
    SphereFromLight[n][s]=m;
    s++;
   }
  }
  SphereMaxSurfaceFromLight[n]=s;
 } 
 delete(tx1);
 delete(ty1);
 delete(tz1);
 delete(tx2);
 delete(ty2);
 delete(tz2);
 delete(tx3);
 delete(ty3);
 delete(tz3);
 delete(tpos);
 delete(tNormal);
}
void LIGHT::SetShadowSurface(int sfc,double xc,double yc,double zc,int lightingnumber)
{
 int m,k,l;
 //создадим набор плоскостей для определения попавших в область затенения поверхностей
 int Vertex=Surface[CurrentSurface].Vertex;
 int Planes=Vertex+1;
 double *tx1=new double[Planes+1];
 double *ty1=new double[Planes+1];
 double *tz1=new double[Planes+1];
 double *tx2=new double[Planes+1];
 double *ty2=new double[Planes+1];
 double *tz2=new double[Planes+1];
 double *tx3=new double[Planes+1];
 double *ty3=new double[Planes+1];
 double *tz3=new double[Planes+1];
 int *tpos=new int[Planes+1];//положение точки центра полигона относительно плоскостей
 SVector *tNormal=new SVector[Planes+1];//нормали к плоскостям
 //начинаем определение возможных поверхностей затенения
 double lx=sPoint_Lighting[lightingnumber].X;
 double ly=sPoint_Lighting[lightingnumber].Y;
 double lz=sPoint_Lighting[lightingnumber].Z;
 for(m=0;m<Vertex;m++)
 {
  int i1=m;
  int i2=m+1;
  if (i2>=Vertex) i2-=Vertex;
  tx1[m]=lx;
  ty1[m]=ly;
  tz1[m]=lz;
  tx2[m]=Surface[sfc].X[i1];
  ty2[m]=Surface[sfc].Y[i1];
  tz2[m]=Surface[sfc].Z[i1];
  tx3[m]=Surface[sfc].X[i2];
  ty3[m]=Surface[sfc].Y[i2];
  tz3[m]=Surface[sfc].Z[i2];
  SVector V1=CreateVector(tx2[m]-tx1[m],ty2[m]-ty1[m],tz2[m]-tz1[m]);
  SVector V2=CreateVector(tx3[m]-tx2[m],ty3[m]-ty2[m],tz3[m]-tz2[m]);
  tNormal[m]=NormalizeVector(VectorProduct(V1,V2));
  //считаем положение центральной точки полигона
  double A=tNormal[m].X;
  double B=tNormal[m].Y;
  double C=tNormal[m].Z;
  double D=-A*tx1[m]-B*ty1[m]-C*tz1[m];
  double pos=A*xc+B*yc+C*zc+D;
  if (pos>EPS) tpos[m]=1;
  if (pos<-EPS) tpos[m]=-1;
  if (pos>=-EPS && pos<=EPS) tpos[m]=0;
 }
 //добавим сюда и саму поверхность 
 tx1[Vertex]=Surface[sfc].X[0];
 ty1[Vertex]=Surface[sfc].Y[0];
 tz1[Vertex]=Surface[sfc].Z[0];
 tx2[Vertex]=Surface[sfc].X[1];
 ty2[Vertex]=Surface[sfc].Y[1];
 tz2[Vertex]=Surface[sfc].Z[1];
 tx3[Vertex]=Surface[sfc].X[2];
 ty3[Vertex]=Surface[sfc].Y[2];
 tz3[Vertex]=Surface[sfc].Z[2];
 SVector V1=CreateVector(tx2[Vertex]-tx1[Vertex],ty2[Vertex]-ty1[Vertex],tz2[Vertex]-tz1[Vertex]);
 SVector V2=CreateVector(tx3[Vertex]-tx2[Vertex],ty3[Vertex]-ty2[Vertex],tz3[Vertex]-tz2[Vertex]);
 tNormal[Vertex]=NormalizeVector(VectorProduct(V1,V2));
 //считаем положение точки источника света
 double A=tNormal[Vertex].X;
 double B=tNormal[Vertex].Y;
 double C=tNormal[Vertex].Z;
 double D=-A*tx1[Vertex]-B*ty1[Vertex]-C*tz1[Vertex];
 double pos=A*lx+B*ly+C*lz+D;
 if (pos>EPS) tpos[Vertex]=1;
 if (pos<-EPS) tpos[Vertex]=-1;
 if (pos>=-EPS && pos<=EPS) tpos[Vertex]=0;
 //проверяем возможность затенения
 int s=0;  
 for(m=0;m<AllSurface;m++)
 {
  if (m==sfc) continue;//сами себя затенять мы ещё не научились
  if (Surface[m].BarrierType==1 || Surface[m].BarrierType==2) continue;//стекляные стены и двери 
  int shadow=1;//тень есть
  //посмотрим не находятся ли все точки с противоположной эталону стороны
  //для какой-либо стороны пирамиды
  for(l=0;l<Planes;l++)
  {
   double A=tNormal[l].X;
   double B=tNormal[l].Y;
   double C=tNormal[l].Z;
   double D=-A*tx1[l]-B*ty1[l]-C*tz1[l];
   int ok=1;
   for(k=0;k<Surface[m].Vertex;k++)
   {
    double x=Surface[m].X[k];
    double y=Surface[m].Y[k];
    double z=Surface[m].Z[k];
    double pos=A*x+B*y+C*z+D;
    if (pos>EPS) pos=1;
    if (pos<-EPS) pos=-1;
    if (pos>=-EPS && pos<=EPS) pos=0;
    if (tpos[l]*pos>=0)//точка лежит так же как и эталон
    {
     ok=0;
     break;
    }
   }
   if (ok==1) //нашлась такая сторона
   {
    shadow=0;//тени нет
    break;
   }
  }
  if (shadow==1)
  {
   SphereFromLight[lightingnumber][s]=m;
   s++;
  }
 }
 SphereMaxSurfaceFromLight[lightingnumber]=s;
 delete(tx1);
 delete(ty1);
 delete(tz1);
 delete(tx2);
 delete(ty2);
 delete(tz2);
 delete(tx3);
 delete(ty3);
 delete(tz3);
 delete(tpos);
 delete(tNormal);
}

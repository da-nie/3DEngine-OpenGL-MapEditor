#include "polygon.h"

//---------------------------------------------------------------------------
SVector CalculateNormal(SPoint sp1,SPoint sp2,SPoint sp3)
{
 SVector sv1=CreateVector(sp3.X-sp1.X,sp3.Y-sp1.Y,sp3.Z-sp1.Z);
 SVector sv2=CreateVector(sp2.X-sp1.X,sp2.Y-sp1.Y,sp2.Z-sp1.Z);
 SVector Normal=NormalizeVector(VectorProduct(sv1,sv2));
 return(Normal);
}
SVector CalculateNormalVector(SPolygon sPolygon)
{
 SVector sVector;
 sVector.X=0;
 sVector.Y=0;
 sVector.Z=0;
 if (sPolygon.PointAmount<3) return(sVector);
 SPoint sPoint[3];
 sPoint[0]=sPolygon.sPoint_Array[0];
 sPoint[1]=sPolygon.sPoint_Array[2];
 sPoint[2]=sPolygon.sPoint_Array[1];
 sVector=CalculateNormal(sPoint[0],sPoint[1],sPoint[2]);
 return(sVector);
}
//---------------------------------------------------------------------------
CPolygon::CPolygon(void)
{
 sPolygon_Array=NULL;
 AmountOfPolygons=0;
 sPolygonLinker_Array=NULL;
}
//---------------------------------------------------------------------------
CPolygon::~CPolygon(void)
{
 ClearAllPolygon();
}
//---------------------------------------------------------------------------
int CPolygon::CreateNewPolygon(SPolygon polygon)
{
 if (polygon.PointAmount<3) return(-1);//полигон с такими параметрами невозможен
 int n,m;
 //создадим массивы побольше
 SPolygon *TArray=new SPolygon[AmountOfPolygons+1];
 SPolygonLinker *TLArray=new SPolygonLinker[AmountOfPolygons+1];
 if (sPolygon_Array!=NULL)
 {
  memcpy(TArray,sPolygon_Array,sizeof(SPolygon)*AmountOfPolygons);
  delete(sPolygon_Array);
 }
 if (sPolygonLinker_Array!=NULL)
 {
  memcpy(TLArray,sPolygonLinker_Array,sizeof(SPolygonLinker)*AmountOfPolygons);
  delete(sPolygonLinker_Array);
 }
 sPolygon_Array=TArray;
 sPolygonLinker_Array=TLArray;
 //заполним массивы данными
 sPolygon_Array[AmountOfPolygons]=polygon;
 sPolygon_Array[AmountOfPolygons].sPoint_Array=new SPoint[polygon.PointAmount+1];
 memcpy(sPolygon_Array[AmountOfPolygons].sPoint_Array,polygon.sPoint_Array,polygon.PointAmount*sizeof(SPoint));
 //вычислим некоторые нужные параметры
 //нормаль
 GenerateNormal(AmountOfPolygons);
 sPolygonLinker_Array[AmountOfPolygons].Index=AmountOfPolygons;
 //найдём свободный идентификатор
 int identificator=AmountOfPolygons;
 for(n=0;n<AmountOfPolygons;n++)
 {
  int is_search=0;
  for(m=0;m<AmountOfPolygons;m++)
  {
   int i=sPolygonLinker_Array[m].Identificator;
   if (i==n)
   {
    is_search=1;
    break;
   }
  }
  if (is_search==0)//такого идентификатора ещё нет
  {
   identificator=n;
   break;
  }
 }
 sPolygonLinker_Array[AmountOfPolygons].Identificator=identificator;
 AmountOfPolygons++;
 return(identificator);
}
void CPolygon::DeletePolygon(int polygon_identificator)
{
 int n;
 //проверим особый случай
 if (AmountOfPolygons==0) return;//нечего удалять
 //ищем такой идентификатор
 int index=-1;
 int link_element=-1;
 for(n=0;n<AmountOfPolygons;n++)
 {
  int i=sPolygonLinker_Array[n].Identificator;
  if (i==polygon_identificator)
  {
   index=sPolygonLinker_Array[n].Index;
   link_element=n;
   break;
  }
 }
 if (index==-1) return;//идентификатор не найден
 //проверим ещё один особый случай
 if (AmountOfPolygons==1)//у нас один элемент
 {
  delete(sPolygon_Array[0].sPoint_Array);
  delete(sPolygon_Array);
  delete(sPolygonLinker_Array);
  AmountOfPolygons=0;
  sPolygon_Array=NULL;
  sPolygonLinker_Array=NULL;
  return;
 }
 //удалим данные найденного полигона
 delete(sPolygon_Array[index].sPoint_Array);
 //создадим массивы поменьше
 SPolygon *TArray=new SPolygon[AmountOfPolygons-1];
 SPolygonLinker *TLArray=new SPolygonLinker[AmountOfPolygons-1];
 //копируем данные (и изменяем индексы у связки)
 for(n=0;n<index;n++) TArray[n]=sPolygon_Array[n];
 for(n=index+1;n<AmountOfPolygons;n++) TArray[n-1]=sPolygon_Array[n];
 delete(sPolygon_Array);
  
 for(n=0;n<link_element;n++)
 {
  int i=sPolygonLinker_Array[n].Index;
  if (i>=index) i--;
  sPolygonLinker_Array[n].Index=i;
  TLArray[n]=sPolygonLinker_Array[n];
 }
 for(n=link_element+1;n<AmountOfPolygons;n++)
 {
  int i=sPolygonLinker_Array[n].Index;
  if (i>=index) i--;
  sPolygonLinker_Array[n].Index=i;
  TLArray[n-1]=sPolygonLinker_Array[n];
 }
 delete(sPolygonLinker_Array);
 sPolygon_Array=TArray;
 sPolygonLinker_Array=TLArray;
 AmountOfPolygons--;
}
void CPolygon::ClearAllPolygon(void)
{
 for(int n=0;n<AmountOfPolygons;n++) delete(sPolygon_Array[n].sPoint_Array);
 if (sPolygon_Array!=NULL) delete(sPolygon_Array);
 if (sPolygonLinker_Array!=NULL) delete(sPolygonLinker_Array);
 sPolygon_Array=NULL;
 sPolygonLinker_Array=NULL;
 AmountOfPolygons=0;
}
int CPolygon::GetAmountOfPolygons(void)
{
 return(AmountOfPolygons);
}
SPolygon CPolygon::GetPolygonForIdentificator(int polygon_identificator)
{
 //ищем такой идентификатор
 int index=0;
 for(int n=0;n<AmountOfPolygons;n++)
 {
  int i=sPolygonLinker_Array[n].Identificator;
  if (i==polygon_identificator)
  {
   index=sPolygonLinker_Array[n].Index;
   break;
  }
 }
 return(sPolygon_Array[index]);
}
SPolygon CPolygon::GetPolygonForIndex(int polygon_index)
{
 return(sPolygon_Array[polygon_index]);
}
int CPolygon::GetPolygonIndex(int polygon_identificator)
{
 //ищем такой идентификатор
 int index=-1;
 for(int n=0;n<AmountOfPolygons;n++)
 {
  int i=sPolygonLinker_Array[n].Identificator;
  if (i==polygon_identificator)
  {
   index=sPolygonLinker_Array[n].Index;
   break;
  }
 }
 return(index);
}
int CPolygon::GetPolygonIdentificator(int polygon_index)
{
 //ищем индекс
 int identificator=-1;
 for(int n=0;n<AmountOfPolygons;n++)
 {
  int i=sPolygonLinker_Array[n].Index;
  if (i==polygon_index)
  {
   identificator=sPolygonLinker_Array[n].Identificator;
   break;
  }
 }
 return(identificator);
}
void CPolygon::GenerateNormal(int polygon_index)
{
 sPolygon_Array[polygon_index].sVector_Normal=CalculateNormalVector(sPolygon_Array[polygon_index]);
}
void CPolygon::SetPolygonNormalForIndex(int polygon_index,SVector sVector)
{
 sPolygon_Array[polygon_index].sVector_Normal=sVector;
}
void CPolygon::SetPolygonLightingEnableForIndex(int polygon_index,BOOL *lightingenable)
{
 for(int n=0;n<8;n++) sPolygon_Array[polygon_index].LightingEnable[n]=lightingenable[n];
}

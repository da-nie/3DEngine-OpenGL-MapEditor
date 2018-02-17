#include "dl_createsimplydoorform.h"

extern CDialog_SelectTexture cDialog_SelectTexture;
extern SETSTextureFollowCWnd_Form cDialog_SetTextureFollow;
extern CWnd_Menu cWnd_Menu;
extern SSettings sSettings;//настройки редактора

CDialog_CreateSimplyDoor cDialog_CreateSimplyDoor;
//------------------------------------------------------------------------------
CDialog_CreateSimplyDoor::CDialog_CreateSimplyDoor(void)
{
 cDialog_CreateSimplyDoor.Initialize();
}
LONG WINAPI CREATESIMPLYDOORFORM_dlgProc(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam)
{
 switch(msg)
 {
  case WM_INITDIALOG:
  {
   cDialog_CreateSimplyDoor.InitDialog(hDlg,wParam,lParam);
   return(TRUE);
  }
  case WM_PAINT:
  {
   cDialog_CreateSimplyDoor.Paint(hDlg,wParam,lParam);
   return(TRUE);
  }
  case WM_COMMAND:
  {
   cDialog_CreateSimplyDoor.Command(hDlg,wParam,lParam);
   return(TRUE);
  }
 }
 return(FALSE);
}
//------------------------------------------------------------------------------
void CDialog_CreateSimplyDoor::InitDialog(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 hDlg=hDlgs;
 hEdit_UpLevel=GetDlgItem(hDlg,CREATESIMPLYDOORFORM_EDIT_UPLEVEL);
 hEdit_DownLevel=GetDlgItem(hDlg,CREATESIMPLYDOORFORM_EDIT_DOWNLEVEL);
 char string[255];
 itoa(WorkingSector.UpLevel,string,10);
 SetWindowText(hEdit_UpLevel,string);
 itoa(WorkingSector.DownLevel,string,10);
 SetWindowText(hEdit_DownLevel,string);
 ColorSet.Create(CC_ANYCOLOR|CC_FULLOPEN,hDlg,hProjectInstance);
}
void CDialog_CreateSimplyDoor::Paint(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 RECT Rect;
 BITMAPINFOHEADER bmih;
 bmih.biSize=sizeof(BITMAPINFOHEADER);
 bmih.biWidth=128;
 bmih.biHeight=128;
 bmih.biPlanes=1;
 bmih.biBitCount=24;
 bmih.biCompression=BI_RGB;
 bmih.biSizeImage=0;
 bmih.biXPelsPerMeter=300;
 bmih.biYPelsPerMeter=300;
 bmih.biClrUsed=0;
 bmih.biClrImportant=0;
 RGBQUAD rgbq;
 rgbq.rgbBlue=1;
 rgbq.rgbGreen=0;
 rgbq.rgbRed=0;
 rgbq.rgbReserved=0;
 BITMAPINFO info;
 info.bmiHeader=bmih;
 info.bmiColors[0]=rgbq;
 PAINTSTRUCT ps;
 HDC hdc;
 hdc=BeginPaint(hDlg,&ps);
 unsigned char TextureMap[128*128*3];
 cDialog_SelectTexture.CreateTextureImage(WorkingSector.DownTexture,TextureMap);
 Rect.left=8;
 Rect.right=Rect.left+64;
 Rect.top=16;
 Rect.bottom=Rect.top+64;
 MapDialogRect(hDlg,&Rect);
 StretchDIBits(hdc,Rect.left,Rect.top,Rect.right-Rect.left,Rect.bottom-Rect.top,0,0,128,128,TextureMap,&info,DIB_RGB_COLORS,SRCCOPY);
 cDialog_SelectTexture.CreateTextureImage(WorkingSector.UpTexture,TextureMap);
 Rect.left=144;
 Rect.right=Rect.left+64;
 Rect.top=16;
 Rect.bottom=Rect.top+64;
 MapDialogRect(hDlg,&Rect);
 StretchDIBits(hdc,Rect.left,Rect.top,Rect.right-Rect.left,Rect.bottom-Rect.top,0,0,128,128,TextureMap,&info,DIB_RGB_COLORS,SRCCOPY);
 //рисуем пол€ эмиссии
 Rect.left=76;
 Rect.right=Rect.left+56;
 Rect.top=60;
 Rect.bottom=Rect.top+20;
 MapDialogRect(hDlg,&Rect);
 HPEN hOldPen,hPen;
 HBRUSH hOldBrush,hBrush;
 hPen=CreatePen(PS_SOLID,1,RGB(0,0,0));
 hBrush=CreateSolidBrush(RGB(WorkingSector.DownEmissionR,WorkingSector.DownEmissionG,WorkingSector.DownEmissionB));
 hOldBrush=(HBRUSH)SelectObject(hdc,hBrush);
 hOldPen=(HPEN)SelectObject(hdc,hPen);
 Rectangle(hdc,Rect.left,Rect.top,Rect.right,Rect.bottom);
 SelectObject(hdc,hOldBrush);
 SelectObject(hdc,hOldPen);
 DeleteObject(hBrush);
 DeleteObject(hPen);
 Rect.left=212;
 Rect.right=Rect.left+56;
 Rect.top=60;
 Rect.bottom=Rect.top+20;
 MapDialogRect(hDlg,&Rect);
 hPen=CreatePen(PS_SOLID,1,RGB(0,0,0));
 hBrush=CreateSolidBrush(RGB(WorkingSector.UpEmissionR,WorkingSector.UpEmissionG,WorkingSector.UpEmissionB));
 hOldBrush=(HBRUSH)SelectObject(hdc,hBrush);
 hOldPen=(HPEN)SelectObject(hdc,hPen);
 Rectangle(hdc,Rect.left,Rect.top,Rect.right,Rect.bottom);
 SelectObject(hdc,hOldBrush);
 SelectObject(hdc,hOldPen);
 DeleteObject(hBrush);
 DeleteObject(hPen);
 EndPaint(hDlg,&ps);
}
void CDialog_CreateSimplyDoor::Command(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 int id=LOWORD(wParam);
 if (id==CREATESIMPLYDOORFORM_BUTTON_CHANGETEXTUREDOWN)
 {
  WorkingSector.DownTexture=cDialog_SelectTexture.Activate(hDlg,WorkingSector.DownTexture,0);
  InvalidateRect(hDlg,NULL,FALSE);
 }
 if (id==CREATESIMPLYDOORFORM_BUTTON_CHANGETEXTUREUP)
 {
  WorkingSector.UpTexture=cDialog_SelectTexture.Activate(hDlg,WorkingSector.UpTexture,0);
  InvalidateRect(hDlg,NULL,FALSE);
 }
 if (id==CREATESIMPLYDOORFORM_BUTTON_ANIMATEUP)
 {
  WorkingSector.UpTextureFollow.TextureList[0]=WorkingSector.UpTexture;
  WorkingSector.UpTextureFollow=cDialog_SetTextureFollow.Activate(hDlg,WorkingSector.UpTextureFollow);
 }
 if (id==CREATESIMPLYDOORFORM_BUTTON_ANIMATEDOWN)
 {
  WorkingSector.DownTextureFollow.TextureList[0]=WorkingSector.DownTexture;
  WorkingSector.DownTextureFollow=cDialog_SetTextureFollow.Activate(hDlg,WorkingSector.DownTextureFollow);
 }
 if (id==CREATESIMPLYDOORFORM_BUTTON_EMISSIONDOWN)
 {
  unsigned char r,g,b;
  if (ColorSet.Activate(&r,&g,&b))
  {
   WorkingSector.DownEmissionR=r;
   WorkingSector.DownEmissionG=g;
   WorkingSector.DownEmissionB=b;
   InvalidateRect(hDlg,NULL,FALSE);
  }
 }
 if (id==CREATESIMPLYDOORFORM_BUTTON_EMISSIONUP)
 {
  unsigned char r,g,b;
  if (ColorSet.Activate(&r,&g,&b))
  {
   WorkingSector.UpEmissionR=r;
   WorkingSector.UpEmissionG=g;
   WorkingSector.UpEmissionB=b;
   InvalidateRect(hDlg,NULL,FALSE);
  }
 }
 if (id==CREATESIMPLYDOORFORM_BUTTON_CANCEL)
 {
  sKeyData.MaximumPset=0;
  cWnd_Menu.UpDate();
  InvalidateRect(sKeyData.hWndMain,NULL,FALSE);
  EndDialog(hDlg,TRUE);
 }
 if (id==CREATESIMPLYDOORFORM_BUTTON_CREATE)
 {
  WorkingSector.DownTextureFollow.TextureList[0]=WorkingSector.DownTexture;
  WorkingSector.UpTextureFollow.TextureList[0]=WorkingSector.UpTexture;
  char string[255];
  GetWindowText(hEdit_UpLevel,string,255);
  WorkingSector.UpLevel=atoi(string);
  GetWindowText(hEdit_DownLevel,string,255);
  WorkingSector.DownLevel=atoi(string);
  Sector[SelectSector]=WorkingSector;
  if (Flag==0)
  {
   Sector[SelectSector].Vertex=sKeyData.MaximumPset-1;
   for(int n=0;n<sKeyData.MaximumPset-1;n++)
   {
    Sector[SelectSector].X[n]=sKeyData.X[n];
    Sector[SelectSector].Y[n]=sKeyData.Y[n];
   }
   sKeyData.MaximumNumberOfSimplyDoor++;
  }
  sKeyData.MaximumPset=0;
  cWnd_Menu.UpDate();
  InvalidateRect(sKeyData.hWndMain,NULL,FALSE);
  EndDialog(hDlg,TRUE);
 }
}
//------------------------------------------------------------------------------
void CDialog_CreateSimplyDoor::Initialize(void)
{
 WorkingSector.UpLevel=0;
 WorkingSector.DownLevel=0;
 WorkingSector.UpEmissionR=0;
 WorkingSector.UpEmissionG=0;
 WorkingSector.UpEmissionB=0;
 WorkingSector.DownEmissionR=0;
 WorkingSector.DownEmissionG=0;
 WorkingSector.DownEmissionB=0;
 WorkingSector.Vertex=0;
 cDialog_SelectTexture.InitializeTextureStruct(&WorkingSector.UpTexture);
 cDialog_SelectTexture.InitializeTextureStruct(&WorkingSector.DownTexture);
 cDialog_SetTextureFollow.InitializeTextureFollow(&WorkingSector.UpTextureFollow);
 cDialog_SetTextureFollow.InitializeTextureFollow(&WorkingSector.DownTextureFollow);
}
void CDialog_CreateSimplyDoor::CreateNewSector(void)
{
 Flag=0;
 SelectSector=sKeyData.MaximumNumberOfSimplyDoor;
 EnableWindow(sKeyData.hWndMenu,FALSE);
 DialogBox(hProjectInstance,(LPSTR)17,sKeyData.hWndMain,(DLGPROC)CREATESIMPLYDOORFORM_dlgProc);
 EnableWindow(sKeyData.hWndMenu,TRUE);
}
void CDialog_CreateSimplyDoor::ModifycationSector(int sector)
{
 if (sector<0) return;
 SelectSector=sector;
 WorkingSector=Sector[sector];
 Flag=1;//флаг модификации включЄн
 EnableWindow(sKeyData.hWndMenu,FALSE);
 DialogBox(hProjectInstance,(LPSTR)18,sKeyData.hWndMain,(DLGPROC)CREATESIMPLYDOORFORM_dlgProc);
 EnableWindow(sKeyData.hWndMenu,TRUE);
}
void CDialog_CreateSimplyDoor::DeleteSector(void)
{
 if (sKeyData.SelectSector==-1) return;
 for(int n=sKeyData.SelectSector+1;n<sKeyData.MaximumNumberOfSimplyDoor;n++) Sector[n-1]=Sector[n];
 sKeyData.SelectSector=-1;
 sKeyData.SelectSectorType=-1;
 sKeyData.MaximumNumberOfSimplyDoor--;
}
void CDialog_CreateSimplyDoor::SaveSector(FILE *File)
{
 fprintf(File,"SIMPLY DOOR STRUCTURE\n");
 fprintf(File,"MAXIMUM %i\n",sKeyData.MaximumNumberOfSimplyDoor);
 for(int n=0;n<sKeyData.MaximumNumberOfSimplyDoor;n++)
 {
  fprintf(File,"%i ",Sector[n].UpLevel);
  fprintf(File,"%i ",Sector[n].DownLevel);
  cDialog_SelectTexture.SaveTextureStruct(File,Sector[n].UpTexture);
  cDialog_SelectTexture.SaveTextureStruct(File,Sector[n].DownTexture);
  fprintf(File,"     %i \n",Sector[n].Vertex);
  for(int m=0;m<Sector[n].Vertex;m++)
  {
   fprintf(File,"     %i ",Sector[n].X[m]);
   fprintf(File,"%i \n",Sector[n].Y[m]);
  }
  //сохран€ем анимацию текстур
  cDialog_SetTextureFollow.Save(Sector[n].UpTextureFollow,File);
  cDialog_SetTextureFollow.Save(Sector[n].DownTextureFollow,File);
  //сохран€ем эмиссию
  fprintf(File,"%i ",(int)Sector[n].UpEmissionR);
  fprintf(File,"%i ",(int)Sector[n].UpEmissionG);
  fprintf(File,"%i \n",(int)Sector[n].UpEmissionB);
  fprintf(File,"%i ",(int)Sector[n].DownEmissionR);
  fprintf(File,"%i ",(int)Sector[n].DownEmissionG);
  fprintf(File,"%i \n",(int)Sector[n].DownEmissionB);
 }
 //сохран€ем текущие настройки
 fprintf(File,"%i ",WorkingSector.UpLevel);
 fprintf(File,"%i ",WorkingSector.DownLevel);
 cDialog_SelectTexture.SaveTextureStruct(File,WorkingSector.UpTexture);
 cDialog_SelectTexture.SaveTextureStruct(File,WorkingSector.DownTexture);
 //сохран€ем анимацию текстур
 cDialog_SetTextureFollow.Save(WorkingSector.UpTextureFollow,File);
 cDialog_SetTextureFollow.Save(WorkingSector.DownTextureFollow,File);
 //сохран€ем эмиссию
 fprintf(File,"%i ",(int)WorkingSector.UpEmissionR);
 fprintf(File,"%i ",(int)WorkingSector.UpEmissionG);
 fprintf(File,"%i \n",(int)WorkingSector.UpEmissionB);
 fprintf(File,"%i ",(int)WorkingSector.DownEmissionR);
 fprintf(File,"%i ",(int)WorkingSector.DownEmissionG);
 fprintf(File,"%i \n",(int)WorkingSector.DownEmissionB);
}
void CDialog_CreateSimplyDoor::LoadSector(FILE *File)
{
 if (GetReadPos(File,"SIMPLY DOOR STRUCTURE")==0) return;
 GetReadPos(File,"MAXIMUM");
 sKeyData.MaximumNumberOfSimplyDoor=(int)ReadNumber(File);
 for(int n=0;n<sKeyData.MaximumNumberOfSimplyDoor;n++)
 {
  Sector[n].UpLevel=(int)ReadNumber(File);
  Sector[n].DownLevel=(int)ReadNumber(File);
  Sector[n].UpTexture=cDialog_SelectTexture.LoadTextureStruct(File);
  Sector[n].DownTexture=cDialog_SelectTexture.LoadTextureStruct(File);
  Sector[n].Vertex=(int)ReadNumber(File);
  for(int m=0;m<Sector[n].Vertex;m++)
  {
   Sector[n].X[m]=(int)ReadNumber(File);
   Sector[n].Y[m]=(int)ReadNumber(File);
  }
  //загружаем анимацию текстур
  cDialog_SetTextureFollow.Load(&Sector[n].UpTextureFollow,File);
  cDialog_SetTextureFollow.Load(&Sector[n].DownTextureFollow,File);
  //загружаем эмиссию
  Sector[n].UpEmissionR=(unsigned char)ReadNumber(File);
  Sector[n].UpEmissionG=(unsigned char)ReadNumber(File);
  Sector[n].UpEmissionB=(unsigned char)ReadNumber(File);
  Sector[n].DownEmissionR=(unsigned char)ReadNumber(File);
  Sector[n].DownEmissionG=(unsigned char)ReadNumber(File);
  Sector[n].DownEmissionB=(unsigned char)ReadNumber(File);
 }
 WorkingSector.UpLevel=(int)ReadNumber(File);
 WorkingSector.DownLevel=(int)ReadNumber(File);
 WorkingSector.UpTexture=cDialog_SelectTexture.LoadTextureStruct(File);
 WorkingSector.DownTexture=cDialog_SelectTexture.LoadTextureStruct(File);
 //загружаем анимацию текстур
 cDialog_SetTextureFollow.Load(&WorkingSector.UpTextureFollow,File);
 cDialog_SetTextureFollow.Load(&WorkingSector.DownTextureFollow,File);
 //загружаем эмиссию
 WorkingSector.UpEmissionR=(unsigned char)ReadNumber(File);
 WorkingSector.UpEmissionG=(unsigned char)ReadNumber(File);
 WorkingSector.UpEmissionB=(unsigned char)ReadNumber(File);
 WorkingSector.DownEmissionR=(unsigned char)ReadNumber(File);
 WorkingSector.DownEmissionG=(unsigned char)ReadNumber(File);
 WorkingSector.DownEmissionB=(unsigned char)ReadNumber(File);
}
int CDialog_CreateSimplyDoor::GetSectorInScreen(int x,int y)
{
 int sector=-1;
 for(int n=0;n<sKeyData.MaximumNumberOfSimplyDoor;n++)
 {
  int pos=0;
  for(int m=0;m<Sector[n].Vertex;m++)
  {
   int i1=m;
   int i2=m+1;
   if (i2>=Sector[n].Vertex) i2-=Sector[n].Vertex;
   float xw1=(float)(Sector[n].X[i1]*10.0);
   float yw1=(float)(Sector[n].Y[i1]*10.0);
   float xw2=(float)(Sector[n].X[i2]*10.0);
   float yw2=(float)(Sector[n].Y[i2]*10.0);
   float res=x*(yw1-yw2)-y*(xw1-xw2)+xw1*yw2-xw2*yw1;
   if (res<=-EPS) res=-1;
   if (res>=EPS) res=1;
   if (res>-EPS && res<EPS) res=0;
   if (res==0) continue;
   if (pos==0) pos=(int)(res);
   if (pos!=(int)(res))
   {
    pos=-2;
    break;
   }
  }
  if (pos!=-2) sector=n;
 }
 return(sector);
}
int CDialog_CreateSimplyDoor::GetSectorInMap(float x,float y,int number)
{
 for(int n=number;n<sKeyData.MaximumNumberOfSimplyDoor;n++)
 {
  int pos=0;
  for(int m=0;m<Sector[n].Vertex;m++)
  {
   int i1=m;
   int i2=m+1;
   if (i2>=Sector[n].Vertex) i2-=Sector[n].Vertex;
   float xw1=(float)(Sector[n].X[i1]);
   float yw1=(float)(Sector[n].Y[i1]);
   float xw2=(float)(Sector[n].X[i2]);
   float yw2=(float)(Sector[n].Y[i2]);
   float res=x*(yw1-yw2)-y*(xw1-xw2)+xw1*yw2-xw2*yw1;
   if (res<=-EPS) res=-1;
   if (res>=EPS) res=1;
   if (res>-EPS && res<EPS) res=0;
   if (res==0) continue;
   if (pos==0) pos=(int)(res);
   if (pos!=res)
   {
    pos=-2;
    break;
   }
  }
  if (pos!=-2) return(n);
 }
 return(-1);
}
void CDialog_CreateSimplyDoor::DrawAllSector(int xLeftMap,int yTopMap)
{
 for(int n=0;n<sKeyData.MaximumNumberOfSimplyDoor;n++)
 {
  int minx=1000000,maxx=0,miny=1000000,maxy=0;
  for(int m=0;m<Sector[n].Vertex;m++)
  {
   int i1=m;
   int i2=m+1;
   if (i2>=Sector[n].Vertex) i2-=Sector[n].Vertex;
   //если выбран простой сектор и это его пор€дковый номер
   if (sKeyData.SelectSector==n && sKeyData.SelectSectorType==1 && (sKeyData.PrimaryMode==7 || sKeyData.PrimaryMode==10)) DrawLine((Sector[n].X[i1]-xLeftMap)*10,(Sector[n].Y[i1]-yTopMap)*10,(Sector[n].X[i2]-xLeftMap)*10,(Sector[n].Y[i2]-yTopMap)*10,255,255,64);
   else DrawLine((Sector[n].X[i1]-xLeftMap)*10,(Sector[n].Y[i1]-yTopMap)*10,(Sector[n].X[i2]-xLeftMap)*10,(Sector[n].Y[i2]-yTopMap)*10,255,0,255);
   if (Sector[n].Y[i1]>maxy) maxy=Sector[n].Y[i1];
   if (Sector[n].Y[i1]<miny) miny=Sector[n].Y[i1];
   if (Sector[n].X[i1]>maxx) maxx=Sector[n].X[i1];
   if (Sector[n].X[i1]<minx) minx=Sector[n].X[i1];
   if (Sector[n].Y[i2]>maxy) maxy=Sector[n].Y[i2];
   if (Sector[n].Y[i2]<miny) miny=Sector[n].Y[i2];
   if (Sector[n].X[i2]>maxx) maxx=Sector[n].X[i2];
   if (Sector[n].X[i2]<minx) minx=Sector[n].X[i2];
  }
  //закрасим сектор
  maxx=(maxx-xLeftMap)*10;
  maxy=(maxy-yTopMap)*10;
  minx=(minx-xLeftMap)*10;
  miny=(miny-yTopMap)*10;
  if (maxx<0) continue;
  if (maxy<0) continue;
  if (minx>500) continue;
  if (miny>500) continue;
  if (minx<0) minx=5;
  if (miny<0) miny=5;
  if (maxx>500) maxx=500;
  if (maxy>500) maxy=500;
  int r=0,g=255,b=0;
  if (sKeyData.SelectSector==n && sKeyData.SelectSectorType==1 && (sKeyData.PrimaryMode==7 || sKeyData.PrimaryMode==10))
  {
   r=255;
   g=0;
   b=255;
  }
  for(int x=minx;x<=maxx;x+=5)
  for(int y=miny;y<=maxy;y+=5)
  {
   //проверим принадлежность точки сектору
   int pos=0;
   for(int m=0;m<Sector[n].Vertex;m++)
   {
    int i1=m;
    int i2=m+1;
    if (i2>=Sector[n].Vertex) i2-=Sector[n].Vertex;
    float xw1=(float)((Sector[n].X[i1]-xLeftMap)*10.0);
    float yw1=(float)((Sector[n].Y[i1]-yTopMap)*10.0);
    float xw2=(float)((Sector[n].X[i2]-xLeftMap)*10.0);
    float yw2=(float)((Sector[n].Y[i2]-yTopMap)*10.0);
    float res=x*(yw1-yw2)-y*(xw1-xw2)+xw1*yw2-xw2*yw1;
    if (res<=-EPS) res=-1;
    if (res>=EPS) res=1;
    if (res>-EPS && res<EPS) res=0;
    if (res==0) continue;
    if (pos==0) pos=(int)(res);
    if (pos!=(int)(res))
    {
     pos=-2;
     break;
    }
   }
   if (pos!=-2) PutPixel(x,y,r,g,b);
  }
 }
}
void CDialog_CreateSimplyDoor::GenerateFloor(int n,SSectorPackage *SCP)
{
 //считаем направление нормали, чтобы узнать, как задавать направление обхода сектора
 double vx1=Sector[n].X[1]-Sector[n].X[0];
 double vy1=Sector[n].Y[1]-Sector[n].Y[0];
 double vx2=Sector[n].X[2]-Sector[n].X[1];
 double vy2=Sector[n].Y[2]-Sector[n].Y[1];
 double nz=vx1*vy2-vy1*vx2;
 SCP->Vertex=Sector[n].Vertex;
 SCP->Texture=Sector[n].DownTexture;
 for(int m=0;m<Sector[n].Vertex;m++)
 {
  int i=m;
  if (nz>0) i=Sector[n].Vertex-1-m;
  SCP->X[i]=Sector[n].X[m];
  SCP->Y[i]=Sector[n].Y[m];
  SCP->Z[i]=Sector[n].DownLevel;
 }
 SCP->Sector=n;
 SCP->SectorType=1;
 SCP->Normal.X=0;
 SCP->Normal.Y=0;
 SCP->Normal.Z=1;
 SCP->BarrierType=0;
 SCP->Location=2;
 SCP->Dz=Sector[n].UpLevel-Sector[n].DownLevel;
}
void CDialog_CreateSimplyDoor::GenerateCeiling(int n,SSectorPackage *SCP)
{
 //считаем направление нормали, чтобы узнать, как задавать направление обхода сектора
 double vx1=Sector[n].X[1]-Sector[n].X[0];
 double vy1=Sector[n].Y[1]-Sector[n].Y[0];
 double vx2=Sector[n].X[2]-Sector[n].X[1];
 double vy2=Sector[n].Y[2]-Sector[n].Y[1];
 double nz=vx1*vy2-vy1*vx2;
 SCP->Vertex=Sector[n].Vertex;
 SCP->Texture=Sector[n].UpTexture;
 for(int m=0;m<Sector[n].Vertex;m++)
 {
  int i=Sector[n].Vertex-1-m;
  if (nz>0) i=m;
  SCP->X[i]=Sector[n].X[m];
  SCP->Y[i]=Sector[n].Y[m];
  SCP->Z[i]=Sector[n].UpLevel;
 }
 SCP->Sector=n;
 SCP->SectorType=1;
 SCP->Normal.X=0;
 SCP->Normal.Y=0;
 SCP->Normal.Z=-1;
 SCP->BarrierType=0;
 SCP->Location=1;
 SCP->Dz=0;
}
int CDialog_CreateSimplyDoor::GetUpLevelFromSegment(int n)
{
 return(Sector[n].UpLevel);
}
int CDialog_CreateSimplyDoor::GetDownLevelFromSegment(int n)
{
 return(Sector[n].DownLevel);
}
int CDialog_CreateSimplyDoor::GetUpLevelFromFrontier(int n)
{
 return(Sector[n].UpLevel);
}
int CDialog_CreateSimplyDoor::GetDownLevelFromFrontier(int n)
{
 return(Sector[n].UpLevel);
}
int CDialog_CreateSimplyDoor::GetPosition(int n,float X1,float Y1,float X2,float Y2)
{
 int Left=0;
 int Right=0;
 for(int s=0;s<Sector[n].Vertex;s++)
 {
  float x=(float)(Sector[n].X[s]);
  float y=(float)(Sector[n].Y[s]);
  float p=x*(Y1-Y2)-y*(X1-X2)+X1*Y2-X2*Y1;
  if (p<-EPS) Right++;
  if (p>EPS) Left++;
 }
 if (Right>Left) return(-1);
 if (Left>Right) return(1);
 return(0);
}
void CDialog_CreateSimplyDoor::SaveSectorFromRender(FILE *File,int sector)
{
 SaveInt(File,Sector[sector].UpLevel);
 SaveInt(File,Sector[sector].DownLevel);
 SaveInt(File,Sector[sector].UpTexture.TextureNo);
 SaveInt(File,Sector[sector].DownTexture.TextureNo);
 SaveInt(File,Sector[sector].Vertex);
 for(int m=0;m<Sector[sector].Vertex;m++)
 {
  SaveFloat(File,(float)(Sector[sector].X[m]*16.0));
  SaveFloat(File,(float)(Sector[sector].Y[m]*16.0));
 }
 //сохран€ем анимацию текстур
 cDialog_SetTextureFollow.SaveForRender(Sector[sector].UpTextureFollow,File);
 cDialog_SetTextureFollow.SaveForRender(Sector[sector].DownTextureFollow,File);
}
 

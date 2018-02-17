#include "dl_createsegmentform.h"

extern CDialog_CreateSimplyDoor cDialog_CreateSimplyDoor;
extern CDialog_CreateSimplySector cDialog_CreateSimplySector;
extern CDialog_SelectTexture cDialog_SelectTexture;
extern SETSTextureFollowCWnd_Form cDialog_SetTextureFollow;
extern CWnd_Menu cWnd_Menu;
extern SSettings sSettings;//настройки редактора

CDialog_CreateSegment cDialog_CreateSegment;
//------------------------------------------------------------------------------
CDialog_CreateSegment::CDialog_CreateSegment(void)
{
 cDialog_CreateSegment.Initialize();
}
//------------------------------------------------------------------------------
LONG WINAPI CREATESEGMENTFORM_dlgProc(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam)
{
 switch(msg)
 {
  case WM_INITDIALOG:
  {
   cDialog_CreateSegment.InitDialog(hDlg,wParam,lParam);
   return(TRUE);
  }
  case WM_PAINT:
  {
   cDialog_CreateSegment.Paint(hDlg,wParam,lParam);
   return(TRUE);
  }
  case WM_COMMAND:
  {
   cDialog_CreateSegment.Command(hDlg,wParam,lParam);
   return(TRUE);
  }
 }
 return(FALSE);
}
//------------------------------------------------------------------------------
void CDialog_CreateSegment::InitDialog(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 hDlg=hDlgs;
 ColorSet.Create(CC_ANYCOLOR|CC_FULLOPEN,hDlg,hProjectInstance);
 if (WorkingSegment.Frontier==0 || Flag==2)
 {
  hCheckBox_Blend=GetDlgItem(hDlg,CREATESEGMENTFORM_CHECKBOX_BLEND);
  SendMessage(hCheckBox_Blend,BM_SETCHECK,0,0);
  if (WorkingSegment.Blend!=0) SendMessage(hCheckBox_Blend,BM_SETCHECK,1,0);
 }
}
void CDialog_CreateSegment::Paint(HWND hWnds,WPARAM wParam,LPARAM lParam)
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
 cDialog_SelectTexture.CreateTextureImage(WorkingSegment.UpTexture,TextureMap);
 Rect.left=4;
 Rect.right=Rect.left+64;
 Rect.top=4;
 Rect.bottom=Rect.top+64;
 MapDialogRect(hDlg,&Rect);
 StretchDIBits(hdc,Rect.left,Rect.top,Rect.right-Rect.left,Rect.bottom-Rect.top,0,0,128,128,TextureMap,&info,DIB_RGB_COLORS,SRCCOPY);
 if (WorkingSegment.Frontier==1 || Flag==2)
 {
  cDialog_SelectTexture.CreateTextureImage(WorkingSegment.DownTexture,TextureMap);
  Rect.left=84;
  Rect.right=Rect.left+64;
  Rect.top=4;
  Rect.bottom=Rect.top+64;
  MapDialogRect(hDlg,&Rect);
  StretchDIBits(hdc,Rect.left,Rect.top,Rect.right-Rect.left,Rect.bottom-Rect.top,0,0,128,128,TextureMap,&info,DIB_RGB_COLORS,SRCCOPY);
 }
 //рисуем поля эмиссии
 Rect.left=4;
 Rect.right=Rect.left+64;
 Rect.top=132;
 Rect.bottom=Rect.top+12;
 MapDialogRect(hDlg,&Rect);
 HPEN hOldPen,hPen;
 HBRUSH hOldBrush,hBrush;
 hPen=CreatePen(PS_SOLID,1,RGB(0,0,0));
 hBrush=CreateSolidBrush(RGB(WorkingSegment.UpEmissionR,WorkingSegment.UpEmissionG,WorkingSegment.UpEmissionB));
 hOldBrush=(HBRUSH)SelectObject(hdc,hBrush);
 hOldPen=(HPEN)SelectObject(hdc,hPen);
 Rectangle(hdc,Rect.left,Rect.top,Rect.right,Rect.bottom);
 SelectObject(hdc,hOldBrush);
 SelectObject(hdc,hOldPen);
 DeleteObject(hBrush);
 DeleteObject(hPen);
 Rect.left=84;
 Rect.right=Rect.left+64;
 Rect.top=132;
 Rect.bottom=Rect.top+12;
 MapDialogRect(hDlg,&Rect);
 hPen=CreatePen(PS_SOLID,1,RGB(0,0,0));
 hBrush=CreateSolidBrush(RGB(WorkingSegment.DownEmissionR,WorkingSegment.DownEmissionG,WorkingSegment.DownEmissionB));
 hOldBrush=(HBRUSH)SelectObject(hdc,hBrush);
 hOldPen=(HPEN)SelectObject(hdc,hPen);
 Rectangle(hdc,Rect.left,Rect.top,Rect.right,Rect.bottom);
 SelectObject(hdc,hOldBrush);
 SelectObject(hdc,hOldPen);
 DeleteObject(hBrush);
 DeleteObject(hPen);
 EndPaint(hDlg,&ps);
}
void CDialog_CreateSegment::Command(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 int id=LOWORD(wParam);
 if (id==CREATESEGMENTFORM_BUTTON_CHANGETEXTUREUP)
 {
  WorkingSegment.UpTexture=cDialog_SelectTexture.Activate(hDlg,WorkingSegment.UpTexture,0);
  InvalidateRect(hDlg,NULL,FALSE);
 }
 if (id==CREATESEGMENTFORM_BUTTON_CHANGETEXTUREDOWN)
 {
  WorkingSegment.DownTexture=cDialog_SelectTexture.Activate(hDlg,WorkingSegment.DownTexture,0);
  InvalidateRect(hDlg,NULL,FALSE);
 }
 if (id==CREATESEGMENTFORM_BUTTON_ANIMATEUP)
 {
  WorkingSegment.UpTextureFollow.TextureList[0]=WorkingSegment.UpTexture;
  WorkingSegment.UpTextureFollow=cDialog_SetTextureFollow.Activate(hDlg,WorkingSegment.UpTextureFollow);
 }
 if (id==CREATESEGMENTFORM_BUTTON_ANIMATEDOWN)
 {
  WorkingSegment.DownTextureFollow.TextureList[0]=WorkingSegment.DownTexture;
  WorkingSegment.DownTextureFollow=cDialog_SetTextureFollow.Activate(hDlg,WorkingSegment.DownTextureFollow);
 }
  
 if (id==CREATESEGMENTFORM_BUTTON_EMISSIONUP)
 {
  unsigned char r,g,b;
  if (ColorSet.Activate(&r,&g,&b))
  {
   WorkingSegment.UpEmissionR=r;
   WorkingSegment.UpEmissionG=g;
   WorkingSegment.UpEmissionB=b;
   InvalidateRect(hDlg,NULL,FALSE);
  }
 }
 if (id==CREATESEGMENTFORM_BUTTON_EMISSIONDOWN)
 {
  unsigned char r,g,b;
  if (ColorSet.Activate(&r,&g,&b))
  {
   WorkingSegment.DownEmissionR=r;
   WorkingSegment.DownEmissionG=g;
   WorkingSegment.DownEmissionB=b;
   InvalidateRect(hDlg,NULL,FALSE);
  }
 }
 if (id==CREATESEGMENTFORM_BUTTON_CANCEL)
 {
  WorkingSegment=OldWorkingSegment;
  if (Flag==2)
  {
   InvalidateRect(sKeyData.hWndMain,NULL,FALSE);
   EndDialog(hDlg,TRUE);
   return;
  }
  sKeyData.MaximumPset=0;
  cWnd_Menu.UpDate();
  InvalidateRect(sKeyData.hWndMain,NULL,FALSE);
  EndDialog(hDlg,TRUE);
 }
 if (id==CREATESEGMENTFORM_BUTTON_CREATE)
 {
  if (WorkingSegment.Frontier==0 || Flag==2)
  {
   WorkingSegment.Blend=SendMessage(hCheckBox_Blend,BM_GETCHECK,0,0);
  }
  else WorkingSegment.Blend=0;
  WorkingSegment.UpTextureFollow.TextureList[0]=WorkingSegment.UpTexture;
  WorkingSegment.DownTextureFollow.TextureList[0]=WorkingSegment.DownTexture;
  if (Flag==2)
  {
   InvalidateRect(sKeyData.hWndMain,NULL,FALSE);
   EndDialog(hDlg,TRUE);
   return;
  }
  Segment[SelectSegment]=WorkingSegment;
  if (Flag==0)//если мы создаём новый сегмент
  {
   sKeyData.MaximumNumberOfLine++;
  }
  sKeyData.MaximumPset=0;
  cWnd_Menu.UpDate();
  InvalidateRect(sKeyData.hWndMain,NULL,FALSE);
  EndDialog(hDlg,TRUE);
 }
}
//------------------------------------------------------------------------------
void CDialog_CreateSegment::Initialize(void)
{
 WorkingSegment.Frontier=0;
 WorkingSegment.UpEmissionR=0;
 WorkingSegment.UpEmissionG=0;
 WorkingSegment.UpEmissionB=0;
 WorkingSegment.DownEmissionR=0;
 WorkingSegment.DownEmissionG=0;
 WorkingSegment.DownEmissionB=0;
 WorkingSegment.Blend=0;
 cDialog_SelectTexture.InitializeTextureStruct(&WorkingSegment.UpTexture);
 cDialog_SelectTexture.InitializeTextureStruct(&WorkingSegment.DownTexture);
 cDialog_SetTextureFollow.InitializeTextureFollow(&WorkingSegment.UpTextureFollow);
 cDialog_SetTextureFollow.InitializeTextureFollow(&WorkingSegment.DownTextureFollow);
}
void CDialog_CreateSegment::ChangeParameters(void)
{
 OldWorkingSegment=WorkingSegment;
 Flag=2;//изменение настроек
 EnableWindow(sKeyData.hWndMenu,FALSE);
 DialogBox(hProjectInstance,(LPSTR)12,sKeyData.hWndMain,(DLGPROC)CREATESEGMENTFORM_dlgProc);
 EnableWindow(sKeyData.hWndMenu,TRUE);
}
void CDialog_CreateSegment::CreateNewSegment(int frontier)
{
 OldWorkingSegment=WorkingSegment;
 Flag=0;//создаётся новый сегмент
 SelectSegment=sKeyData.MaximumNumberOfLine;
 WorkingSegment.Frontier=frontier;
 WorkingSegment.X1=sKeyData.X[0];
 WorkingSegment.Y1=sKeyData.Y[0];
 WorkingSegment.X2=sKeyData.X[1];
 WorkingSegment.Y2=sKeyData.Y[1];
 EnableWindow(sKeyData.hWndMenu,FALSE);
 if (frontier==1) DialogBox(hProjectInstance,(LPSTR)2,sKeyData.hWndMain,(DLGPROC)CREATESEGMENTFORM_dlgProc);
 else DialogBox(hProjectInstance,(LPSTR)3,sKeyData.hWndMain,(DLGPROC)CREATESEGMENTFORM_dlgProc);
 EnableWindow(sKeyData.hWndMenu,TRUE);
}
void CDialog_CreateSegment::ModifycationSegment(int segment)
{
 OldWorkingSegment=WorkingSegment;
 if (segment<0) return;
 Flag=1;//модификация сегмента
 SelectSegment=segment;
 WorkingSegment=Segment[segment];
 EnableWindow(sKeyData.hWndMenu,FALSE);
 if (WorkingSegment.Frontier==1) DialogBox(hProjectInstance,(LPSTR)4,sKeyData.hWndMain,(DLGPROC)CREATESEGMENTFORM_dlgProc);
 else DialogBox(hProjectInstance,(LPSTR)5,sKeyData.hWndMain,(DLGPROC)CREATESEGMENTFORM_dlgProc);
 EnableWindow(sKeyData.hWndMenu,TRUE);
}
void CDialog_CreateSegment::CreateSegment(int frontier)
{
 WorkingSegment.Frontier=frontier;
 WorkingSegment.X1=sKeyData.X[0];
 WorkingSegment.Y1=sKeyData.Y[0];
 WorkingSegment.X2=sKeyData.X[1];
 WorkingSegment.Y2=sKeyData.Y[1];
 Segment[sKeyData.MaximumNumberOfLine]=WorkingSegment;
 sKeyData.MaximumNumberOfLine++;
 sKeyData.MaximumPset=0;
 cWnd_Menu.UpDate();
}
void CDialog_CreateSegment::DeleteSegment(void)
{
 if (sKeyData.SelectLine==-1) return;
 for(int n=sKeyData.SelectLine+1;n<sKeyData.MaximumNumberOfLine;n++) Segment[n-1]=Segment[n];
 sKeyData.SelectLine=-1;
 sKeyData.MaximumNumberOfLine--;
}
void CDialog_CreateSegment::SaveSegment(FILE *File)
{
 char string[255];
 itoa(sKeyData.MaximumNumberOfLine,string,10);
 fprintf(File,"SSegment STRUCTURE\n");
 fprintf(File,"MAXIMUM %s \n",string);
 for(int n=0;n<sKeyData.MaximumNumberOfLine;n++)
 {
  fprintf(File,"%i ",Segment[n].X1);
  fprintf(File,"%i ",Segment[n].Y1);
  fprintf(File,"%i ",Segment[n].X2);
  fprintf(File,"%i ",Segment[n].Y2);
  cDialog_SelectTexture.SaveTextureStruct(File,Segment[n].UpTexture);
  cDialog_SelectTexture.SaveTextureStruct(File,Segment[n].DownTexture);
  fprintf(File,"%i ",Segment[n].Blend);
  fprintf(File,"%i \n",Segment[n].Frontier);
  //сохраняем анимацию текстуры
  cDialog_SetTextureFollow.Save(Segment[n].UpTextureFollow,File);
  cDialog_SetTextureFollow.Save(Segment[n].DownTextureFollow,File);
  //сохраняем эмиссию
  fprintf(File,"%i ",(int)Segment[n].UpEmissionR);
  fprintf(File,"%i ",(int)Segment[n].UpEmissionG);
  fprintf(File,"%i \n",(int)Segment[n].UpEmissionB);
  fprintf(File,"%i ",(int)Segment[n].DownEmissionR);
  fprintf(File,"%i ",(int)Segment[n].DownEmissionG);
  fprintf(File,"%i \n",(int)Segment[n].DownEmissionB);
 }
 //сохраняем текущие настройки
 fprintf(File,"%i ",WorkingSegment.X1);
 fprintf(File,"%i ",WorkingSegment.Y1);
 fprintf(File,"%i ",WorkingSegment.X2);
 fprintf(File,"%i ",WorkingSegment.Y2);
 cDialog_SelectTexture.SaveTextureStruct(File,WorkingSegment.UpTexture);
 cDialog_SelectTexture.SaveTextureStruct(File,WorkingSegment.DownTexture);
 fprintf(File,"%i ",WorkingSegment.Blend);
 fprintf(File,"%i ",WorkingSegment.Frontier);
 //сохраняем анимацию текстуры
 cDialog_SetTextureFollow.Save(WorkingSegment.UpTextureFollow,File);
 cDialog_SetTextureFollow.Save(WorkingSegment.DownTextureFollow,File);
 //сохраняем эмиссию
 fprintf(File,"%i ",(int)WorkingSegment.UpEmissionR);
 fprintf(File,"%i ",(int)WorkingSegment.UpEmissionG);
 fprintf(File,"%i \n",(int)WorkingSegment.UpEmissionB);
 fprintf(File,"%i ",(int)WorkingSegment.DownEmissionR);
 fprintf(File,"%i ",(int)WorkingSegment.DownEmissionG);
 fprintf(File,"%i \n",(int)WorkingSegment.DownEmissionB);
}
void CDialog_CreateSegment::LoadSegment(FILE *File)
{
 if (GetReadPos(File,"SSegment STRUCTURE")==0) return;
 GetReadPos(File,"MAXIMUM");
 sKeyData.MaximumNumberOfLine=(int)ReadNumber(File);
 for(int n=0;n<sKeyData.MaximumNumberOfLine;n++)
 {
  Segment[n].X1=(int)ReadNumber(File);
  Segment[n].Y1=(int)ReadNumber(File);
  Segment[n].X2=(int)ReadNumber(File);
  Segment[n].Y2=(int)ReadNumber(File);
  Segment[n].UpTexture=cDialog_SelectTexture.LoadTextureStruct(File);
  Segment[n].DownTexture=cDialog_SelectTexture.LoadTextureStruct(File);
  Segment[n].Blend=(int)ReadNumber(File);
  Segment[n].Frontier=(int)ReadNumber(File);
  //загружаем анимацию текстуры
  cDialog_SetTextureFollow.Load(&Segment[n].UpTextureFollow,File);
  cDialog_SetTextureFollow.Load(&Segment[n].DownTextureFollow,File);
  //загружаем эмиссию
  Segment[n].UpEmissionR=(unsigned char)ReadNumber(File);
  Segment[n].UpEmissionG=(unsigned char)ReadNumber(File);
  Segment[n].UpEmissionB=(unsigned char)ReadNumber(File);
  Segment[n].DownEmissionR=(unsigned char)ReadNumber(File);
  Segment[n].DownEmissionG=(unsigned char)ReadNumber(File);
  Segment[n].DownEmissionB=(unsigned char)ReadNumber(File);
 }
 WorkingSegment.X1=(int)ReadNumber(File);
 WorkingSegment.Y1=(int)ReadNumber(File);
 WorkingSegment.X2=(int)ReadNumber(File);
 WorkingSegment.Y2=(int)ReadNumber(File);
 WorkingSegment.UpTexture=cDialog_SelectTexture.LoadTextureStruct(File);
 WorkingSegment.DownTexture=cDialog_SelectTexture.LoadTextureStruct(File);
 WorkingSegment.Blend=(int)ReadNumber(File);
 WorkingSegment.Frontier=(int)ReadNumber(File);
 //загружаем анимацию текстуры
 cDialog_SetTextureFollow.Load(&WorkingSegment.UpTextureFollow,File);
 cDialog_SetTextureFollow.Load(&WorkingSegment.DownTextureFollow,File);
 //загружаем эмиссию
 WorkingSegment.UpEmissionR=(unsigned char)ReadNumber(File);
 WorkingSegment.UpEmissionG=(unsigned char)ReadNumber(File);
 WorkingSegment.UpEmissionB=(unsigned char)ReadNumber(File);
 WorkingSegment.DownEmissionR=(unsigned char)ReadNumber(File);
 WorkingSegment.DownEmissionG=(unsigned char)ReadNumber(File);
 WorkingSegment.DownEmissionB=(unsigned char)ReadNumber(File);
}
void CDialog_CreateSegment::DrawAllSegment(int xLeftMap,int yTopMap)
{
 for(int n=0;n<sKeyData.MaximumNumberOfLine;n++)
 {
  if (n==sKeyData.SelectLine)//если сегмент выделен
  {
   DrawLine((Segment[n].X1-xLeftMap)*10,(Segment[n].Y1-yTopMap)*10,(Segment[n].X2-xLeftMap)*10,(Segment[n].Y2-yTopMap)*10,255,255,64);
   if (sSettings.ShowVector==1)
   {
    float x1=(float)((Segment[n].X1-xLeftMap)*10+((Segment[n].Y2-yTopMap)*10-(Segment[n].Y1-yTopMap)*10)/2);
    float y1=(float)((Segment[n].Y1-yTopMap)*10-((Segment[n].X2-xLeftMap)*10-(Segment[n].X1-xLeftMap)*10)/2);
    float x2=(float)((Segment[n].X1-xLeftMap)*10-((Segment[n].Y2-yTopMap)*10-(Segment[n].Y1-yTopMap)*10)/2);
    float y2=(float)((Segment[n].Y1-yTopMap)*10+((Segment[n].X2-xLeftMap)*10-(Segment[n].X1-xLeftMap)*10)/2);
    float vx=x1-(Segment[n].X2-xLeftMap)*10;
    float vy=y1-(Segment[n].Y2-yTopMap)*10;
    float ux=x2-(Segment[n].X2-xLeftMap)*10;
    float uy=y2-(Segment[n].Y2-yTopMap)*10;
    float l=(float)(sqrt(vx*vx+vy*vy));
    if (l==0) continue;
    x1=(Segment[n].X2-xLeftMap)*10+vx/l*10;
    y1=(Segment[n].Y2-yTopMap)*10+vy/l*10;
    x2=(Segment[n].X2-xLeftMap)*10+ux/l*10;
    y2=(Segment[n].Y2-yTopMap)*10+uy/l*10;
    if (Segment[n].Frontier==0)
    {
     DrawLine((Segment[n].X2-xLeftMap)*10,(Segment[n].Y2-yTopMap)*10,(int)(x1),(int)(y1),255,255,64);
     DrawLine((Segment[n].X2-xLeftMap)*10,(Segment[n].Y2-yTopMap)*10,(int)(x2),(int)(y2),255,255,64);
    }
   }
   continue;
  }
  if (Segment[n].Frontier==0) DrawLine((Segment[n].X1-xLeftMap)*10,(Segment[n].Y1-yTopMap)*10,(Segment[n].X2-xLeftMap)*10,(Segment[n].Y2-yTopMap)*10,255,0,0);
  if (Segment[n].Frontier==1) DrawLine((Segment[n].X1-xLeftMap)*10,(Segment[n].Y1-yTopMap)*10,(Segment[n].X2-xLeftMap)*10,(Segment[n].Y2-yTopMap)*10,0,127,255);
  if (sSettings.ShowVector==1)
  {
   float x1=(float)((Segment[n].X1-xLeftMap)*10+((Segment[n].Y2-yTopMap)*10-(Segment[n].Y1-yTopMap)*10)/2);
   float y1=(float)((Segment[n].Y1-yTopMap)*10-((Segment[n].X2-xLeftMap)*10-(Segment[n].X1-xLeftMap)*10)/2);
   float x2=(float)((Segment[n].X1-xLeftMap)*10-((Segment[n].Y2-yTopMap)*10-(Segment[n].Y1-yTopMap)*10)/2);
   float y2=(float)((Segment[n].Y1-yTopMap)*10+((Segment[n].X2-xLeftMap)*10-(Segment[n].X1-xLeftMap)*10)/2);
   float vx=x1-(Segment[n].X2-xLeftMap)*10;
   float vy=y1-(Segment[n].Y2-yTopMap)*10;
   float ux=x2-(Segment[n].X2-xLeftMap)*10;
   float uy=y2-(Segment[n].Y2-yTopMap)*10;
   float l=(float)(sqrt(vx*vx+vy*vy));
   if (l==0) continue;
   x1=(Segment[n].X2-xLeftMap)*10+vx/l*10;
   y1=(Segment[n].Y2-yTopMap)*10+vy/l*10;
   x2=(Segment[n].X2-xLeftMap)*10+ux/l*10;
   y2=(Segment[n].Y2-yTopMap)*10+uy/l*10;
   if (Segment[n].Frontier==0)
   {
    DrawLine((Segment[n].X2-xLeftMap)*10,(Segment[n].Y2-yTopMap)*10,(int)(x1),(int)(y1),255,0,0);
    DrawLine((Segment[n].X2-xLeftMap)*10,(Segment[n].Y2-yTopMap)*10,(int)(x2),(int)(y2),255,0,0);
   }
   if (Segment[n].Frontier==1)
   {
    DrawLine((Segment[n].X2-xLeftMap)*10,(Segment[n].Y2-yTopMap)*10,(int)(x1),(int)(y1),0,127,255);
    DrawLine((Segment[n].X2-xLeftMap)*10,(Segment[n].Y2-yTopMap)*10,(int)(x2),(int)(y2),0,127,255);
   }
  }
 }
}
float CDialog_CreateSegment::DistanceOfVector(float xc,float yc,float xa,float ya,float xb,float yb)
{
 float xp,yp;
 float k;
 if (xa!=xb)
 {
  k=(yb-ya)/(xb-xa);
  xp=(xc+(yc+k*xa-ya)*k)/(k*k+1);
  yp=k*(xp-xa)+ya;
 }
 else
 {
  k=(xb-xa)/(yb-ya);
  yp=(yc+(xc+k*ya-xa)*k)/(k*k+1);
  xp=k*(yp-ya)+xa;
 }
 if (xa>xb)
 {
  float r=xa;
  xa=xb;
  xb=r;
 }
 if (ya>yb)
 {
  float r=ya;
  ya=yb;
  yb=r;
 }
 if (xp<xa || xp>xb || yp<ya || yp>yb) return(-1);
 float l=(float)(sqrt((xc-xp)*(xc-xp)+(yc-yp)*(yc-yp)));
 return(l);
}
int CDialog_CreateSegment::GetLineInScreen(int x,int y,int frontier)
{
 int selected=-1;
 float minlen=1000000000.0;
 for(int n=0;n<sKeyData.MaximumNumberOfLine;n++)
 {
  if (frontier==0 && Segment[n].Frontier!=0) continue;//нужны сегменты
  if (frontier==1 && Segment[n].Frontier==0) continue;//нужны линии раздела
  float x1=(float)(Segment[n].X1*10.0);
  float y1=(float)(Segment[n].Y1*10.0);
  float x2=(float)(Segment[n].X2*10.0);
  float y2=(float)(Segment[n].Y2*10.0);
  float dist=DistanceOfVector((float)(x),(float)(y),x1,y1,x2,y2);
  if (dist<0) continue;
  if (dist<=minlen)
  {
   minlen=dist;
   selected=n;
  }
 }
 return(selected);
}
int CDialog_CreateSegment::DefinitionSector(void)
{
 int SectorOne[1000];
 int SectorOneType[1000];
 int SectorTwo[1000];
 int SectorTwoType[1000];
 for(int n=0;n<sKeyData.MaximumNumberOfLine;n++)
 {
  int PointerOne=0;
  //ищем сектора для первой точки линии
  //работа с секторами
  //ищем среди простых секторов
  int number=0;
  while(1)
  {
   number=cDialog_CreateSimplySector.GetSectorInMap((float)(Segment[n].X1),(float)(Segment[n].Y1),number);
   if (number==-1) break;
   SectorOne[PointerOne]=number;
   SectorOneType[PointerOne]=0;
   PointerOne++;
   number++;
  }
  //ищем среди простых дверей
  number=0;
  while(1)
  {
   number=cDialog_CreateSimplyDoor.GetSectorInMap((float)(Segment[n].X1),(float)(Segment[n].Y1),number);
   if (number==-1) break;
   SectorOne[PointerOne]=number;
   SectorOneType[PointerOne]=1;
   PointerOne++;
   number++;
  }
  //работа с секторами
  //ищем сектора для второй точки линии
  //работа с секторами
  //ищем среди простых секторов
  int PointerTwo=0;
  number=0;
  while(1)
  {
   number=cDialog_CreateSimplySector.GetSectorInMap((float)(Segment[n].X2),(float)(Segment[n].Y2),number);
   if (number==-1) break;
   SectorTwo[PointerTwo]=number;
   SectorTwoType[PointerTwo]=0;
   PointerTwo++;
   number++;
  }
  //ищем среди простых дверей
  number=0;
  while(1)
  {
   number=cDialog_CreateSimplyDoor.GetSectorInMap((float)(Segment[n].X2),(float)(Segment[n].Y2),number);
   if (number==-1) break;
   SectorTwo[PointerTwo]=number;
   SectorTwoType[PointerTwo]=1;
   PointerTwo++;
   number++;
  }
  //работа с секторами
  //выделяем одинаковые
  int Sector[1000];
  int SectorType[1000];
  int Pointer=0;
  for(int h=0;h<PointerOne;h++)
  {
   if (SectorOne[h]<0) continue;
   for(int l=0;l<PointerTwo;l++)
   {
    if (SectorTwo[l]<0) continue;
    if (SectorOne[h]==SectorTwo[l] && SectorOneType[h]==SectorTwoType[l])
    {
     Sector[Pointer]=SectorOne[h];
     SectorType[Pointer]=SectorOneType[h];
     SectorOne[h]=-1;
     SectorTwo[l]=-1;
     Pointer++;
    }
   }
  }
  //теперь проверим на ошибки
  if (Pointer==0)
  {
   MessageBox(NULL,"Линия не принадлежит ни одному сектору !","Ошибка",MB_OK);
   return(1);
  }
  if (Segment[n].Frontier==0 && Pointer>2)
  {
   MessageBox(NULL,"Сегмент принадлежит нескольким секторам (больше 2-х)!","Ошибка",MB_OK);
   return(1);
  }
  if (Segment[n].Frontier==1 && Pointer>2)
  {
   MessageBox(NULL,"Линия раздела принадлежит более чем двум секторам !","Ошибка",MB_OK);
   return(1);
  }
  if (Segment[n].Frontier==1 && Pointer==1)
  {
   MessageBox(NULL,"Линия раздела принадлежит одному сектору !","Ошибка",MB_OK);
   return(1);
  }
  //раз ошибок нет то заносим данные в структуру
  if (Segment[n].Frontier==0 && Pointer==1)
  {
   Segment[n].SectorOne=Sector[0];
   Segment[n].SectorOneType=SectorType[0];
   Segment[n].SectorTwo=Sector[0];
   Segment[n].SectorTwoType=SectorType[0];
   Segment[n].DoubleSegment=0;
  }
  else
  {
   Segment[n].SectorOne=Sector[0];
   Segment[n].SectorOneType=SectorType[0];
   Segment[n].SectorTwo=Sector[1];
   Segment[n].SectorTwoType=SectorType[1];
   Segment[n].DoubleSegment=1;
  }
  if (Segment[n].Frontier==1)
  {
   Segment[n].SectorOne=Sector[0];
   Segment[n].SectorOneType=SectorType[0];
   Segment[n].SectorTwo=Sector[1];
   Segment[n].SectorTwoType=SectorType[1];
  }
 }
 return(0); 
}
void CDialog_CreateSegment::SaveSegmentFromRender(FILE *File,int no)
{
 SaveFloat(File,(float)(Segment[no].X1*16.0));
 SaveFloat(File,(float)(Segment[no].Y1*16.0));
 SaveFloat(File,(float)(Segment[no].X2*16.0));
 SaveFloat(File,(float)(Segment[no].Y2*16.0));
 SaveInt(File,Segment[no].UpTexture.TextureNo);
 SaveInt(File,Segment[no].DownTexture.TextureNo);
 SaveChar(File,Segment[no].Blend);
 SaveChar(File,Segment[no].Frontier);
 SaveInt(File,Segment[no].SectorOne);
 SaveShort(File,Segment[no].SectorOneType);
 SaveInt(File,Segment[no].SectorTwo);
 SaveShort(File,Segment[no].SectorTwoType);
 //сохраняем анимацию текстуры
 cDialog_SetTextureFollow.SaveForRender(Segment[no].UpTextureFollow,File);
 cDialog_SetTextureFollow.SaveForRender(Segment[no].DownTextureFollow,File);
}
 

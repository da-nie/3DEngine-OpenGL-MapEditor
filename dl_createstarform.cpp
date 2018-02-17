#include "dl_createstarform.h"

extern SKeyData sKeyData;//ключевая информация
extern CDialog_CreateSegment cDialog_CreateSegment;

CDialog_CreateStar cDialog_CreateStar;
//------------------------------------------------------------------------------
CDialog_CreateStar::CDialog_CreateStar(void)
{
 cDialog_CreateStar.Initialize();
}
 
LONG WINAPI CREATESTARFORM_dlgProc(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam)
{
 switch(msg)
 {
  case WM_INITDIALOG:
  {
   cDialog_CreateStar.InitDialog(hDlg,wParam,lParam);
   return(TRUE);
  }
  case WM_COMMAND:
  {
   cDialog_CreateStar.Command(hDlg,wParam,lParam);
   return(TRUE);
  }
 }
 return(FALSE);
}
//------------------------------------------------------------------------------
void CDialog_CreateStar::InitDialog(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 hDlg=hDlgs;
 hEdit_RadiusUp=GetDlgItem(hDlg,CREATESTARFORM_EDIT_RADIUSUP);
 hEdit_RadiusDown=GetDlgItem(hDlg,CREATESTARFORM_EDIT_RADIUSDOWN);
 hEdit_Vertex=GetDlgItem(hDlg,CREATESTARFORM_EDIT_VERTEX);
 hEdit_Angle=GetDlgItem(hDlg,CREATESTARFORM_EDIT_ANGLE);
 hCheckBox_Vector=GetDlgItem(hDlg,CREATESTARFORM_CHECKBOX_VECTOR);
 SendMessage(hCheckBox_Vector,BM_SETCHECK,1,0);
 char string[255];
 itoa(RadiusUp,string,10);
 SetWindowText(hEdit_RadiusUp,string);
 itoa(RadiusDown,string,10);
 SetWindowText(hEdit_RadiusDown,string);
 itoa(Vertex,string,10);
 SetWindowText(hEdit_Vertex,string);
 itoa(Angle,string,10);
 SetWindowText(hEdit_Angle,string);
}
void CDialog_CreateStar::Command(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 int id=LOWORD(wParam);
 if (id==CREATESTARFORM_BUTTON_CANCEL)
 {
  InvalidateRect(sKeyData.hWndMain,NULL,FALSE);
  EndDialog(hDlg,TRUE);
 }
 if (id==CREATESTARFORM_BUTTON_CREATE)
 {
  char string[255];
  GetWindowText(hEdit_RadiusUp,string,255);
  RadiusUp=atoi(string);
  GetWindowText(hEdit_RadiusDown,string,255);
  RadiusDown=atoi(string);
  GetWindowText(hEdit_Vertex,string,255);
  Vertex=atoi(string);
  GetWindowText(hEdit_Angle,string,255);
  Angle=atoi(string);
  Angle=Angle%360;
  float da=0;
  if (Vertex>0) da=(float)(360.0/(float)Vertex);
  for(int n=0;n<Vertex;n++)
  {
   float x1=(float)(RadiusUp*cos(M_PI/180.0*(n*da+Angle))+X_Pos);
   float y1=(float)(RadiusUp*sin(M_PI/180.0*(n*da+Angle))+Y_Pos);
   float x2=(float)(RadiusDown*cos(M_PI/180.0*(n*da+Angle+da/2.0))+X_Pos);
   float y2=(float)(RadiusDown*sin(M_PI/180.0*(n*da+Angle+da/2.0))+Y_Pos);
   float x1_1=(float)(RadiusUp*cos(M_PI/180.0*(n*da+Angle+da))+X_Pos);
   float y1_1=(float)(RadiusUp*sin(M_PI/180.0*(n*da+Angle+da))+Y_Pos);
   if (x2<0 || y2<0) continue;
   if (x2>100000 || y2>100000) continue;
   if (x1>=0 && x1<=100000 && y1>=0 && y1<=100000)
   {
    sKeyData.MaximumPset=2;
    sKeyData.X[0]=(int)(x1);
    sKeyData.Y[0]=(int)(y1);
    sKeyData.X[1]=(int)(x2);
    sKeyData.Y[1]=(int)(y2);
    if (SendMessage(hCheckBox_Vector,BM_GETCHECK,0,0)==0)
    {
     sKeyData.X[0]=(int)(x2);
     sKeyData.Y[0]=(int)(y2);
     sKeyData.X[1]=(int)(x1);
     sKeyData.Y[1]=(int)(y1);
    }
    cDialog_CreateSegment.CreateSegment(0);
   }
   if (x1_1>=0 && x1_1<=100000 && y1_1>=0 && y1_1<=100000)
   {
    sKeyData.MaximumPset=2;
    sKeyData.X[0]=(int)(x2);
    sKeyData.Y[0]=(int)(y2);
    sKeyData.X[1]=(int)(x1_1);
    sKeyData.Y[1]=(int)(y1_1);
    if (SendMessage(hCheckBox_Vector,BM_GETCHECK,0,0)==0)
    {
     sKeyData.X[0]=(int)(x1_1);
     sKeyData.Y[0]=(int)(y1_1);
     sKeyData.X[1]=(int)(x2);
     sKeyData.Y[1]=(int)(y2);
    }
    cDialog_CreateSegment.CreateSegment(0);
   }
  }
  InvalidateRect(sKeyData.hWndMain,NULL,FALSE);
  EndDialog(hDlg,TRUE);
 }
}
//------------------------------------------------------------------------------
void CDialog_CreateStar::Initialize(void)
{
 Angle=0;
 RadiusUp=0;
 RadiusDown=0;
 Vertex=0;
}
void CDialog_CreateStar::Activate(int x,int y)
{
 X_Pos=x;
 Y_Pos=y;
 EnableWindow(sKeyData.hWndMenu,FALSE);
 DialogBox(hProjectInstance,(LPSTR)8,sKeyData.hWndMain,(DLGPROC)CREATESTARFORM_dlgProc);
 EnableWindow(sKeyData.hWndMenu,TRUE);
}
 

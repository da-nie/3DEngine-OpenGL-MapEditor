#include "dl_createpolygonform.h"

extern SKeyData sKeyData;//ключевая информация
extern HINSTANCE hProjectInstance;
extern CDialog_CreateSegment cDialog_CreateSegment;

CDialog_CreatePolygon cDialog_CreatePolygon;
//------------------------------------------------------------------------------
CDialog_CreatePolygon::CDialog_CreatePolygon(void)
{
 cDialog_CreatePolygon.Initialize();
}
LONG WINAPI CREATEPOLYGONFORM_dlgProc(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam)
{
 switch(msg)
 {
  case WM_INITDIALOG:
  {
   cDialog_CreatePolygon.InitDialog(hDlg,wParam,lParam);
   return(TRUE);
  }
  case WM_COMMAND:
  {
   cDialog_CreatePolygon.Command(hDlg,wParam,lParam);
   return(TRUE);
  }
 }
 return(FALSE);
}
//------------------------------------------------------------------------------
void CDialog_CreatePolygon::InitDialog(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 hDlg=hDlgs;
 hEdit_Radius=GetDlgItem(hDlg,CREATEPOLYGONFORM_EDIT_RADIUS);
 hEdit_Vertex=GetDlgItem(hDlg,CREATEPOLYGONFORM_EDIT_VERTEX);
 hEdit_Angle=GetDlgItem(hDlg,CREATEPOLYGONFORM_EDIT_ANGLE);
 hCheckBox_Vector=GetDlgItem(hDlg,CREATEPOLYGONFORM_CHECKBOX_VECTOR);
 SendMessage(hCheckBox_Vector,BM_SETCHECK,1,0);
 char string[255];
 itoa(Radius,string,10);
 SetWindowText(hEdit_Radius,string);
 itoa(Vertex,string,10);
 SetWindowText(hEdit_Vertex,string);
 itoa(Angle,string,10);
 SetWindowText(hEdit_Angle,string);
}
void CDialog_CreatePolygon::Command(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 int id=LOWORD(wParam);
 if (id==CREATEPOLYGONFORM_BUTTON_CANCEL)
 {
  InvalidateRect(sKeyData.hWndMain,NULL,FALSE);
  EndDialog(hDlg,TRUE);
 }
 if (id==CREATEPOLYGONFORM_BUTTON_CREATE)
 {
  char string[255];
  GetWindowText(hEdit_Radius,string,255);
  Radius=atoi(string);
  GetWindowText(hEdit_Vertex,string,255);
  Vertex=atoi(string);
  GetWindowText(hEdit_Angle,string,255);
  Angle=atoi(string);
  Angle=Angle%360;
  float da=0;
  if (Vertex>0) da=(float)(360.0/(float)Vertex);
  for(int n=0;n<Vertex;n++)
  {
   float x1=(float)(X_Pos+(float)Radius*cos(M_PI/180.0*(Angle+da*n)));
   float y1=(float)(Y_Pos+(float)Radius*sin(M_PI/180.0*(Angle+da*n)));
   float x2=(float)(X_Pos+(float)Radius*cos(M_PI/180.0*(Angle+da*(n+1))));
   float y2=(float)(Y_Pos+(float)Radius*sin(M_PI/180.0*(Angle+da*(n+1))));
   if (x1<0 || x2<0 || y1<0 || y2<0) continue;
   if (x1>100000 || x2>100000 || y1>100000 || y2>100000) continue;
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
  InvalidateRect(sKeyData.hWndMain,NULL,FALSE);
  EndDialog(hDlg,TRUE);
 }
}
//------------------------------------------------------------------------------
void CDialog_CreatePolygon::Initialize(void)
{
 Angle=0;
 Radius=0;
 Vertex=0;
}
void CDialog_CreatePolygon::Activate(int x,int y)
{
 X_Pos=x;
 Y_Pos=y;
 EnableWindow(sKeyData.hWndMenu,FALSE);
 DialogBox(hProjectInstance,(LPSTR)7,sKeyData.hWndMain,(DLGPROC)CREATEPOLYGONFORM_dlgProc);
 EnableWindow(sKeyData.hWndMenu,TRUE);
}
 

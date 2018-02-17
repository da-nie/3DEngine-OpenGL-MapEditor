#include "dl_createpolygonform.h"

extern KEY_DATA KeyData;//ключевая информация
extern HINSTANCE hProjectInstance;
extern CREATESEGMENTFORM CreateSegmentForm;

CREATEPOLYGONFORM CreatePolygonForm;
//------------------------------------------------------------------------------
CREATEPOLYGONFORM::CREATEPOLYGONFORM(void)
{
 CreatePolygonForm.Initialize();
}
LONG WINAPI CREATEPOLYGONFORM_dlgProc(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam)
{
 switch(msg)
 {
  case WM_INITDIALOG:
  {
   CreatePolygonForm.InitDialog(hDlg,wParam,lParam);
   return(TRUE);
  }
  case WM_COMMAND:
  {
   CreatePolygonForm.Command(hDlg,wParam,lParam);
   return(TRUE);
  }
 }
 return(FALSE);
}
//------------------------------------------------------------------------------
void CREATEPOLYGONFORM::InitDialog(HWND hDlgs,WPARAM wParam,LPARAM lParam)
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
void CREATEPOLYGONFORM::Command(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 int id=LOWORD(wParam);
 if (id==CREATEPOLYGONFORM_BUTTON_CANCEL)
 {
  InvalidateRect(KeyData.hWndMain,NULL,FALSE);
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
   KeyData.MaximumPset=2;
   KeyData.X[0]=(int)(x1);
   KeyData.Y[0]=(int)(y1);
   KeyData.X[1]=(int)(x2);
   KeyData.Y[1]=(int)(y2);
   if (SendMessage(hCheckBox_Vector,BM_GETCHECK,0,0)==0)
   {
    KeyData.X[0]=(int)(x2);
    KeyData.Y[0]=(int)(y2);
    KeyData.X[1]=(int)(x1);
    KeyData.Y[1]=(int)(y1);
   }
   CreateSegmentForm.CreateSegment(0);
  }
  InvalidateRect(KeyData.hWndMain,NULL,FALSE);
  EndDialog(hDlg,TRUE);
 }
}
//------------------------------------------------------------------------------
void CREATEPOLYGONFORM::Initialize(void)
{
 Angle=0;
 Radius=0;
 Vertex=0;
}
void CREATEPOLYGONFORM::Activate(int x,int y)
{
 X_Pos=x;
 Y_Pos=y;
 EnableWindow(KeyData.hWndMenu,FALSE);
 DialogBox(hProjectInstance,(LPSTR)7,KeyData.hWndMain,(DLGPROC)CREATEPOLYGONFORM_dlgProc);
 EnableWindow(KeyData.hWndMenu,TRUE);
}
 

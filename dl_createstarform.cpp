#include "dl_createstarform.h"

extern KEY_DATA KeyData;//ключевая информация
extern CREATESEGMENTFORM CreateSegmentForm;

CREATESTARFORM CreateStarForm;
//------------------------------------------------------------------------------
CREATESTARFORM::CREATESTARFORM(void)
{
 CreateStarForm.Initialize();
}
 
LONG WINAPI CREATESTARFORM_dlgProc(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam)
{
 switch(msg)
 {
  case WM_INITDIALOG:
  {
   CreateStarForm.InitDialog(hDlg,wParam,lParam);
   return(TRUE);
  }
  case WM_COMMAND:
  {
   CreateStarForm.Command(hDlg,wParam,lParam);
   return(TRUE);
  }
 }
 return(FALSE);
}
//------------------------------------------------------------------------------
void CREATESTARFORM::InitDialog(HWND hDlgs,WPARAM wParam,LPARAM lParam)
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
void CREATESTARFORM::Command(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 int id=LOWORD(wParam);
 if (id==CREATESTARFORM_BUTTON_CANCEL)
 {
  InvalidateRect(KeyData.hWndMain,NULL,FALSE);
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
   if (x1_1>=0 && x1_1<=100000 && y1_1>=0 && y1_1<=100000)
   {
    KeyData.MaximumPset=2;
    KeyData.X[0]=(int)(x2);
    KeyData.Y[0]=(int)(y2);
    KeyData.X[1]=(int)(x1_1);
    KeyData.Y[1]=(int)(y1_1);
    if (SendMessage(hCheckBox_Vector,BM_GETCHECK,0,0)==0)
    {
     KeyData.X[0]=(int)(x1_1);
     KeyData.Y[0]=(int)(y1_1);
     KeyData.X[1]=(int)(x2);
     KeyData.Y[1]=(int)(y2);
    }
    CreateSegmentForm.CreateSegment(0);
   }
  }
  InvalidateRect(KeyData.hWndMain,NULL,FALSE);
  EndDialog(hDlg,TRUE);
 }
}
//------------------------------------------------------------------------------
void CREATESTARFORM::Initialize(void)
{
 Angle=0;
 RadiusUp=0;
 RadiusDown=0;
 Vertex=0;
}
void CREATESTARFORM::Activate(int x,int y)
{
 X_Pos=x;
 Y_Pos=y;
 EnableWindow(KeyData.hWndMenu,FALSE);
 DialogBox(hProjectInstance,(LPSTR)8,KeyData.hWndMain,(DLGPROC)CREATESTARFORM_dlgProc);
 EnableWindow(KeyData.hWndMenu,TRUE);
}
 

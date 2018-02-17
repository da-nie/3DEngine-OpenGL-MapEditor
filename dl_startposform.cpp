#include "dl_startposform.h"

extern SKeyData sKeyData;//ключевая информация
extern HINSTANCE hProjectInstance;

CDialog_StartPos StartPoscWnd_Form;
//------------------------------------------------------------------------------
CDialog_StartPos::CDialog_StartPos(void)
{
 StartPoscWnd_Form.Initialize();
}
LONG WINAPI STARTPOSFORM_dlgProc(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam)
{
 switch(msg)
 {
  case WM_INITDIALOG:
  {
   StartPoscWnd_Form.InitDialog(hDlg,wParam,lParam);
   return(TRUE);
  }
  case WM_COMMAND:
  {
   StartPoscWnd_Form.Command(hDlg,wParam,lParam);
   return(TRUE);
  }
 }
 return(FALSE);
}
//------------------------------------------------------------------------------
void CDialog_StartPos::InitDialog(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 hDlg=hDlgs;
 hEdit_Angle=GetDlgItem(hDlg,STARTPOSFORM_EDIT_ANGLE);
 char string[255];
 itoa(Angle,string,10);
 SetWindowText(hEdit_Angle,string);
}
void CDialog_StartPos::Command(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 int id=LOWORD(wParam);
 if (id==STARTPOSFORM_BUTTON_CANCEL)
 {
  InvalidateRect(sKeyData.hWndMain,NULL,FALSE);
  EndDialog(hDlg,TRUE);
 }
 if (id==STARTPOSFORM_BUTTON_CREATE)
 {
  char string[255];
  GetWindowText(hEdit_Angle,string,255);
  Angle=atoi(string);
  Angle=Angle%360;
  Start_X_Pos=Working_X_Pos;
  Start_Y_Pos=Working_Y_Pos;
  InvalidateRect(sKeyData.hWndMain,NULL,FALSE);
  EndDialog(hDlg,TRUE);
 }
}
//------------------------------------------------------------------------------
void CDialog_StartPos::Initialize(void)
{
 Angle=0;
 Start_X_Pos=8;
 Start_Y_Pos=8;
}
void CDialog_StartPos::Activate(int x,int y)
{
 Working_X_Pos=x;
 Working_Y_Pos=y;
 EnableWindow(sKeyData.hWndMenu,FALSE);
 DialogBox(hProjectInstance,(LPSTR)6,sKeyData.hWndMain,(DLGPROC)STARTPOSFORM_dlgProc);
 EnableWindow(sKeyData.hWndMenu,TRUE);
}
void CDialog_StartPos::SaveStartPosition(FILE *File)
{
 fprintf(File,"START POSITION STRUCTURE\n");
 fprintf(File,"%i ",Start_X_Pos);
 fprintf(File,"%i ",Start_Y_Pos);
 fprintf(File,"%i \n",Angle);
}
void CDialog_StartPos::LoadStartPosition(FILE *File)
{
 if (GetReadPos(File,"START POSITION STRUCTURE")==0) return;
 Start_X_Pos=(int)ReadNumber(File);
 Start_Y_Pos=(int)ReadNumber(File);
 Angle=(int)ReadNumber(File);
}
void CDialog_StartPos::DrawStartPos(int xLeftMap,int yTopMap)
{
 Circle((Start_X_Pos-xLeftMap)*10,(Start_Y_Pos-yTopMap)*10,8,255,0,0);
 Circle((Start_X_Pos-xLeftMap)*10,(Start_Y_Pos-yTopMap)*10,6,255,255,0);
 Circle((Start_X_Pos-xLeftMap)*10,(Start_Y_Pos-yTopMap)*10,3,255,0,255);
 int dy=(int)(8.0*cos(M_PI/180.0*Angle));
 int dx=(int)(-8.0*sin(M_PI/180.0*Angle));
 DrawLine((Start_X_Pos-xLeftMap)*10,(Start_Y_Pos-yTopMap)*10,(Start_X_Pos-xLeftMap)*10+dx,(Start_Y_Pos-yTopMap)*10+dy,0,0,255);
}
void CDialog_StartPos::SaveStartPositionFromRender(FILE *File)
{
 fprintf(File,"START POSITION");
 SaveFloat(File,(float)(Start_X_Pos*16.0));
 SaveFloat(File,(float)(Start_Y_Pos*16.0));
 SaveFloat(File,(float)(Angle));
}
 

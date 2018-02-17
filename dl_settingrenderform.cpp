#include "dl_settingrenderform.h"

extern SSettings sSettings;//настройки редактора
extern SKeyData sKeyData;//ключевая информация
extern HINSTANCE hProjectInstance;


CDialog_SettingsRender cDialog_SettingsRender;
//------------------------------------------------------------------------------
LONG WINAPI SETTINGRENDERFORM_dlgProc(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam)
{
 switch(msg)
 {
  case WM_INITDIALOG:
  {
   cDialog_SettingsRender.InitDialog(hDlg,wParam,lParam);
   return(TRUE);
  }
  case WM_COMMAND:
  {
   cDialog_SettingsRender.Command(hDlg,wParam,lParam);
   return(TRUE);
  }
  case WM_PAINT:
  {
   cDialog_SettingsRender.Paint(hDlg,wParam,lParam);
   return(TRUE);
  }
 }
 return(FALSE);
}
//------------------------------------------------------------------------------
void CDialog_SettingsRender::InitDialog(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 hDlg=hDlgs;
 hEdit_BlockSize=GetDlgItem(hDlg,SETTINGRENDERFORM_EDIT_BLOCKSIZE);
 hEdit_Constant=GetDlgItem(hDlg,SETTINGRENDERFORM_EDIT_CONSTANT);
 hEdit_Linear=GetDlgItem(hDlg,SETTINGRENDERFORM_EDIT_LINEAR);
 hEdit_Quadric=GetDlgItem(hDlg,SETTINGRENDERFORM_EDIT_QUADRIC);
 hEdit_FogDensity=GetDlgItem(hDlg,SETTINGRENDERFORM_EDIT_FOGDENSITY);
 hCheckBox_FogEnable=GetDlgItem(hDlg,SETTINGRENDERFORM_CHECKBOX_FOGENABLE);
 char string[255];
 itoa(sSettings.BlockSize,string,10);
 SetWindowText(hEdit_BlockSize,string);
 sprintf(string,"%g",sSettings.Constant_Attenuation);
 SetWindowText(hEdit_Constant,string);
 sprintf(string,"%g",sSettings.Linear_Attenuation);
 SetWindowText(hEdit_Linear,string);
 sprintf(string,"%g",sSettings.Quadric_Attenuation);
 SetWindowText(hEdit_Quadric,string);
 itoa(sSettings.Fog_Density,string,10);
 SetWindowText(hEdit_FogDensity,string);
 ColorSet.Create(CC_ANYCOLOR|CC_FULLOPEN,hDlg,hProjectInstance);
 A_R=sSettings.R_Ambient;
 A_G=sSettings.G_Ambient;
 A_B=sSettings.B_Ambient;
  
 F_R=sSettings.R_Fog;
 F_G=sSettings.G_Fog;
 F_B=sSettings.B_Fog;
  
 if (sSettings.Fog_Enable==0) SendMessage(hCheckBox_FogEnable,BM_SETCHECK,0,0);
 else SendMessage(hCheckBox_FogEnable,BM_SETCHECK,1,0);
}
void CDialog_SettingsRender::Command(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 int id=LOWORD(wParam);
 if (id==SETTINGRENDERFORM_BUTTON_CREATE)
 {
  char string[255];
  GetWindowText(hEdit_BlockSize,string,255);
  sSettings.BlockSize=atoi(string);
  GetWindowText(hEdit_Constant,string,255);
  sSettings.Constant_Attenuation=atof(string);
  GetWindowText(hEdit_Linear,string,255);
  sSettings.Linear_Attenuation=atof(string);
  GetWindowText(hEdit_Quadric,string,255);
  sSettings.Quadric_Attenuation=atof(string);
  GetWindowText(hEdit_FogDensity,string,255);
  sSettings.Fog_Density=atoi(string);
  if (SendMessage(hCheckBox_FogEnable,BM_GETCHECK,0,0)==1) sSettings.Fog_Enable=1;
  else sSettings.Fog_Enable=0;
  sSettings.R_Ambient=A_R;
  sSettings.G_Ambient=A_G;
  sSettings.B_Ambient=A_B;
  sSettings.R_Fog=F_R;
  sSettings.G_Fog=F_G;
  sSettings.B_Fog=F_B;
  EndDialog(hDlg,TRUE);
 }
 if (id==SETTINGRENDERFORM_BUTTON_CANCEL)
 {
  EndDialog(hDlg,TRUE);
 }
 if (id==SETTINGRENDERFORM_BUTTON_RESTORE)
 {
  char string[255];
  itoa(64,string,10);
  SetWindowText(hEdit_BlockSize,string);
  itoa(0,string,10);
  SetWindowText(hEdit_Constant,string);
  itoa(1000000,string,10);
  SetWindowText(hEdit_Linear,string);
  itoa(100000,string,10);
  SetWindowText(hEdit_Quadric,string);
  itoa(2500000,string,10);
  SetWindowText(hEdit_FogDensity,string);
  SendMessage(hCheckBox_FogEnable,BM_SETCHECK,0,0);
  A_R=32;
  A_G=32;
  A_B=32;
  F_R=255;
  F_G=255;
  F_B=255;
  InvalidateRect(hDlg,NULL,FALSE);
 }
 if (id==SETTINGRENDERFORM_BUTTON_SETCOLOR)
 {
  ColorSet.Activate(&A_R,&A_G,&A_B);
  InvalidateRect(hDlg,NULL,FALSE);
 }
 if (id==SETTINGRENDERFORM_BUTTON_SETFOGCOLOR)
 {
  ColorSet.Activate(&F_R,&F_G,&F_B);
  InvalidateRect(hDlg,NULL,FALSE);
 }
}
void CDialog_SettingsRender::Paint(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 int x,y;
 unsigned char ColorMap[40*40*3];
 for(x=0;x<40;x++)
 for(y=0;y<40;y++)
 {
  int offset=(x+y*40)*3;
  ColorMap[offset]=A_B;
  ColorMap[offset+1]=A_G;
  ColorMap[offset+2]=A_R;
 }
 BITMAPINFOHEADER bmih;
 bmih.biSize=sizeof(BITMAPINFOHEADER);
 bmih.biWidth=40;
 bmih.biHeight=40;
 bmih.biPlanes=1;
 bmih.biBitCount=24;
 bmih.biCompression=BI_RGB;
 bmih.biSizeImage=0;
 bmih.biXPelsPerMeter=300;
 bmih.biYPelsPerMeter=300;
 bmih.biClrUsed=0;
 bmih.biClrImportant=0;
 RGBQUAD rgbq;
 BITMAPINFO info;
 rgbq.rgbBlue=1;
 rgbq.rgbGreen=0;
 rgbq.rgbRed=0;
 rgbq.rgbReserved=0;
 info.bmiHeader=bmih;
 info.bmiColors[0]=rgbq;
 PAINTSTRUCT ps;
 HDC hdc;
 hdc=BeginPaint(hDlg,&ps);
 RECT Rect;
 Rect.left=4;
 Rect.right=Rect.left+20;
 Rect.top=80;
 Rect.bottom=Rect.top+20;
 MapDialogRect(hDlg,&Rect);
 StretchDIBits(hdc,Rect.left,Rect.top,Rect.right-Rect.left,Rect.bottom-Rect.top,0,0,40,40,ColorMap,&info,DIB_RGB_COLORS,SRCCOPY);
 for(x=0;x<40;x++)
 for(y=0;y<40;y++)
 {
  int offset=(x+y*40)*3;
  ColorMap[offset]=F_B;
  ColorMap[offset+1]=F_G;
  ColorMap[offset+2]=F_R;
 }
 Rect.left=128;
 Rect.right=Rect.left+20;
 Rect.top=80;
 Rect.bottom=Rect.top+20;
 MapDialogRect(hDlg,&Rect);
 StretchDIBits(hdc,Rect.left,Rect.top,Rect.right-Rect.left,Rect.bottom-Rect.top,0,0,40,40,ColorMap,&info,DIB_RGB_COLORS,SRCCOPY);
 EndPaint(hDlg,&ps);
}
//------------------------------------------------------------------------------
void CDialog_SettingsRender::Activate(void)
{
 EnableWindow(sKeyData.hWndMenu,FALSE);
 DialogBox(hProjectInstance,(LPSTR)9,sKeyData.hWndMain,(DLGPROC)SETTINGRENDERFORM_dlgProc);
 EnableWindow(sKeyData.hWndMenu,TRUE);
}
 

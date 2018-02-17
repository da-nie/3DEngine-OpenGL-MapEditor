#include "dl_createlightingform.h"

extern KEY_DATA KeyData;//ключевая информация
extern HINSTANCE hProjectInstance;
extern MENUFORM MenuForm;

CREATELIGHTINGFORM CreateLightingForm;

//------------------------------------------------------------------------------
CREATELIGHTINGFORM::CREATELIGHTINGFORM(void)
{
 CreateLightingForm.Initialize();
}
LONG WINAPI CREATELIGHTINGFORM_dlgProc(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam)
{
 switch(msg)
 {
  case WM_INITDIALOG:
  {
   CreateLightingForm.InitDialog(hDlg,wParam,lParam);
   return(TRUE);
  }
  case WM_COMMAND:
  {
   CreateLightingForm.Command(hDlg,wParam,lParam);
   return(TRUE);
  }
  case WM_PAINT:
  {
   CreateLightingForm.Paint(hDlg,wParam,lParam);
   return(TRUE);
  }
 }
 return(FALSE);
}
//------------------------------------------------------------------------------
void CREATELIGHTINGFORM::InitDialog(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 hDlg=hDlgs;
 hEdit_Height=GetDlgItem(hDlg,CREATELIGHTINGFORM_EDIT_HEIGHT);
 hRadioButton_Mode1=GetDlgItem(hDlg,CREATELIGHTINGFORM_RADIO_MODE1);
 hRadioButton_Mode2=GetDlgItem(hDlg,CREATELIGHTINGFORM_RADIO_MODE2);
 hRadioButton_Mode3=GetDlgItem(hDlg,CREATELIGHTINGFORM_RADIO_MODE3);
 hRadioButton_Mode4=GetDlgItem(hDlg,CREATELIGHTINGFORM_RADIO_MODE4);
 hEdit_Mode2_DarkTime=GetDlgItem(hDlg,CREATELIGHTINGFORM_EDIT_MODE2_DARK_TIME);
 hEdit_Mode2_LightTime=GetDlgItem(hDlg,CREATELIGHTINGFORM_EDIT_MODE2_LIGHT_TIME);
 hEdit_Mode2_MinimumLightLevel=GetDlgItem(hDlg,CREATELIGHTINGFORM_EDIT_MODE2_MINIMUM_LIGHT_LEVEL);
 hEdit_Mode3_MinimumLightLevel=GetDlgItem(hDlg,CREATELIGHTINGFORM_EDIT_MODE3_MINIMUM_LIGHT_LEVEL);
 hEdit_Mode3_CycleTime=GetDlgItem(hDlg,CREATELIGHTINGFORM_EDIT_MODE3_CYCLE_TIME);
 hEdit_Mode4_OnTime=GetDlgItem(hDlg,CREATELIGHTINGFORM_EDIT_MODE4_ON_TIME);
 hEdit_Mode4_OffTime=GetDlgItem(hDlg,CREATELIGHTINGFORM_EDIT_MODE4_OFF_TIME);
 hEdit_Mode4_MinimumLightLevel=GetDlgItem(hDlg,CREATELIGHTINGFORM_EDIT_MODE4_MINIMUM_LIGHT_LEVEL);
 hEdit_TimeInterval=GetDlgItem(hDlg,CREATELIGHTINGFORM_EDIT_TIME_INTERVAL);
  
 char string[255];
 sprintf(string,"%i",WorkingLighting.Z);
 SetWindowText(hEdit_Height,string);
 sprintf(string,"%g",WorkingLighting.Mode2_DarkTime);
 SetWindowText(hEdit_Mode2_DarkTime,string);
 sprintf(string,"%g",WorkingLighting.Mode2_LightTime);
 SetWindowText(hEdit_Mode2_LightTime,string);
 sprintf(string,"%g",WorkingLighting.Mode2_MinimumLightLevel);
 SetWindowText(hEdit_Mode2_MinimumLightLevel,string);
 sprintf(string,"%g",WorkingLighting.Mode3_CycleTime);
 SetWindowText(hEdit_Mode3_CycleTime,string);
 sprintf(string,"%g",WorkingLighting.Mode3_MinimumLightLevel);
 SetWindowText(hEdit_Mode3_MinimumLightLevel,string);
 sprintf(string,"%g",WorkingLighting.Mode4_MinimumLightLevel);
 SetWindowText(hEdit_Mode4_MinimumLightLevel,string);
 sprintf(string,"%g",WorkingLighting.Mode4_OffTime);
 SetWindowText(hEdit_Mode4_OffTime,string);
 sprintf(string,"%g",WorkingLighting.Mode4_OnTime);
 SetWindowText(hEdit_Mode4_OnTime,string);
 sprintf(string,"%i",WorkingLighting.TimeInterval);
 SetWindowText(hEdit_TimeInterval,string);
  
 SendMessage(hRadioButton_Mode1,BM_SETCHECK,0,0) ;
 SendMessage(hRadioButton_Mode2,BM_SETCHECK,0,0) ;
 SendMessage(hRadioButton_Mode3,BM_SETCHECK,0,0) ;
 SendMessage(hRadioButton_Mode4,BM_SETCHECK,0,0) ;
 if (WorkingLighting.Mode==1) SendMessage(hRadioButton_Mode1,BM_SETCHECK,1,0) ;
 if (WorkingLighting.Mode==2) SendMessage(hRadioButton_Mode2,BM_SETCHECK,1,0) ;
 if (WorkingLighting.Mode==3) SendMessage(hRadioButton_Mode3,BM_SETCHECK,1,0) ;
 if (WorkingLighting.Mode==4) SendMessage(hRadioButton_Mode4,BM_SETCHECK,1,0) ; 
 ColorSet.Create(CC_ANYCOLOR|CC_FULLOPEN,hDlg,hProjectInstance);
}
void CREATELIGHTINGFORM::Command(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 int id=LOWORD(wParam);
 if (id==CREATELIGHTINGFORM_BUTTON_CANCEL)
 {
  InvalidateRect(KeyData.hWndMain,NULL,FALSE);
  EndDialog(hDlg,TRUE);
 }
 if (id==CREATELIGHTINGFORM_BUTTON_CREATE)
 {
  char string[255];
  GetWindowText(hEdit_Height,string,255);
  WorkingLighting.Z=atoi(string);
   
  GetWindowText(hEdit_Mode2_LightTime,string,255);
  WorkingLighting.Mode2_LightTime=(float)atof(string); 
  GetWindowText(hEdit_Mode2_DarkTime,string,255);
  WorkingLighting.Mode2_DarkTime=(float)atof(string);
  GetWindowText(hEdit_Mode2_MinimumLightLevel,string,255);
  WorkingLighting.Mode2_MinimumLightLevel=(float)atof(string);
  GetWindowText(hEdit_Mode3_CycleTime,string,255);
  WorkingLighting.Mode3_CycleTime=(float)atof(string);
  GetWindowText(hEdit_Mode3_MinimumLightLevel,string,255);
  WorkingLighting.Mode3_MinimumLightLevel=(float)atof(string);
  GetWindowText(hEdit_Mode4_MinimumLightLevel,string,255);
  WorkingLighting.Mode4_MinimumLightLevel=(float)atof(string);
  GetWindowText(hEdit_Mode4_OnTime,string,255);
  WorkingLighting.Mode4_OnTime=(float)atof(string);
  GetWindowText(hEdit_Mode4_OffTime,string,255);
  WorkingLighting.Mode4_OffTime=(float)atof(string);
  GetWindowText(hEdit_TimeInterval,string,255);
  WorkingLighting.TimeInterval=atoi(string);
   
  if (SendMessage(hRadioButton_Mode1,BM_GETCHECK,0,0)==1) WorkingLighting.Mode=1;
  if (SendMessage(hRadioButton_Mode2,BM_GETCHECK,0,0)==1) WorkingLighting.Mode=2;
  if (SendMessage(hRadioButton_Mode3,BM_GETCHECK,0,0)==1) WorkingLighting.Mode=3;
  if (SendMessage(hRadioButton_Mode4,BM_GETCHECK,0,0)==1) WorkingLighting.Mode=4;
  Lighting[SelectLighting]=WorkingLighting;
  if (Flag==0)//если мы создаём новый источник света
  {
   KeyData.MaximumNumberOfLighting++;
   MenuForm.UpDate();
  }
  InvalidateRect(KeyData.hWndMain,NULL,FALSE);
  EndDialog(hDlg,TRUE);
 }
 if (id==CREATELIGHTINGFORM_BUTTON_SETCOLOR) SetColor();
}
void CREATELIGHTINGFORM::Paint(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 PAINTSTRUCT ps;
 HDC hdc;
 hdc=BeginPaint(hDlg,&ps);
 RECT Rect;
 Rect.left=152;
 Rect.right=Rect.left+20;
 Rect.top=20;
 Rect.bottom=Rect.top+20;
 MapDialogRect(hDlg,&Rect);
 HPEN hOldPen,hPen;
 HBRUSH hOldBrush,hBrush;
 hPen=CreatePen(PS_SOLID,1,RGB(0,0,0));
 hBrush=CreateSolidBrush(RGB(WorkingLighting.R,WorkingLighting.G,WorkingLighting.B));
 hOldBrush=(HBRUSH)SelectObject(hdc,hBrush);
 hOldPen=(HPEN)SelectObject(hdc,hPen);
 Rectangle(hdc,Rect.left,Rect.top,Rect.right,Rect.bottom);
 SelectObject(hdc,hOldBrush);
 SelectObject(hdc,hOldPen);
 DeleteObject(hBrush);
 DeleteObject(hPen);
 EndPaint(hDlg,&ps);
}
//------------------------------------------------------------------------------
void CREATELIGHTINGFORM::Initialize(void)
{
 WorkingLighting.Z=0;
 WorkingLighting.X=0;
 WorkingLighting.Y=0;
 WorkingLighting.R=255;
 WorkingLighting.G=255;
 WorkingLighting.B=255;
 WorkingLighting.Mode=1;
  
 WorkingLighting.Mode2_DarkTime=0;
 WorkingLighting.Mode2_LightTime=0;
 WorkingLighting.Mode2_MinimumLightLevel=0;
 WorkingLighting.Mode3_CycleTime=0;
 WorkingLighting.Mode3_MinimumLightLevel=0;
 WorkingLighting.Mode4_MinimumLightLevel=0;
 WorkingLighting.Mode4_OffTime=0;
 WorkingLighting.Mode4_OnTime=0;
 WorkingLighting.TimeInterval=0;
}
void CREATELIGHTINGFORM::CreateNewLighting(int x,int y)
{
 Flag=0;
 WorkingLighting.X=x;
 WorkingLighting.Y=y;
 SelectLighting=KeyData.MaximumNumberOfLighting;
 EnableWindow(KeyData.hWndMenu,FALSE);
 DialogBox(hProjectInstance,(LPSTR)10,KeyData.hWndMain,(DLGPROC)CREATELIGHTINGFORM_dlgProc);
 EnableWindow(KeyData.hWndMenu,TRUE);
}
void CREATELIGHTINGFORM::ModifycationLighting(int lighting)
{
 if (lighting==-1) return;
 Flag=1;
 WorkingLighting=Lighting[lighting];
 SelectLighting=lighting;
 EnableWindow(KeyData.hWndMenu,FALSE);
 DialogBox(hProjectInstance,(LPSTR)11,KeyData.hWndMain,(DLGPROC)CREATELIGHTINGFORM_dlgProc);
 EnableWindow(KeyData.hWndMenu,TRUE);
}
void CREATELIGHTINGFORM::DeleteLighting(void)
{
 if (KeyData.SelectLighting==-1) return;
 for(int n=KeyData.SelectLighting+1;n<KeyData.MaximumNumberOfLighting;n++) Lighting[n-1]=Lighting[n];
 KeyData.MaximumNumberOfLighting--;
 KeyData.SelectLighting=-1;
}
void CREATELIGHTINGFORM::SetColor(void)
{
 unsigned char r,g,b;
 if (ColorSet.Activate(&r,&g,&b))
 {
  WorkingLighting.R=(unsigned char)r;
  WorkingLighting.G=(unsigned char)g;
  WorkingLighting.B=(unsigned char)b;
  InvalidateRect(hDlg,NULL,FALSE);
 }
}
void CREATELIGHTINGFORM::SaveLighting(FILE *File)
{
 char string[255];
 itoa(KeyData.MaximumNumberOfLighting,string,10);
 fprintf(File,"LIGHTING STRUCTURE\n");
 fprintf(File,"MAXIMUM %s\n",string);
 for(int n=0;n<KeyData.MaximumNumberOfLighting;n++)
 {
  fprintf(File,"%i ",Lighting[n].X);
  fprintf(File,"%i ",Lighting[n].Y);
  fprintf(File,"%i ",Lighting[n].Z);
  fprintf(File,"%i ",Lighting[n].R);
  fprintf(File,"%i ",Lighting[n].G);
  fprintf(File,"%i ",Lighting[n].B);
  fprintf(File,"%i ",Lighting[n].Mode);
  fprintf(File,"%i ",Lighting[n].TimeInterval);
  fprintf(File,"%f ",Lighting[n].Mode2_DarkTime);
  fprintf(File,"%f ",Lighting[n].Mode2_LightTime);
  fprintf(File,"%f ",Lighting[n].Mode2_MinimumLightLevel);
  fprintf(File,"%f ",Lighting[n].Mode3_CycleTime);
  fprintf(File,"%f ",Lighting[n].Mode3_MinimumLightLevel);
  fprintf(File,"%f ",Lighting[n].Mode4_MinimumLightLevel);
  fprintf(File,"%f ",Lighting[n].Mode4_OffTime);
  fprintf(File,"%f \n",Lighting[n].Mode4_OnTime);
 }
 //сохраняем текущие настройки
 fprintf(File,"%i ",WorkingLighting.X);
 fprintf(File,"%i ",WorkingLighting.Y);
 fprintf(File,"%i ",WorkingLighting.Z);
 fprintf(File,"%i ",WorkingLighting.R);
 fprintf(File,"%i ",WorkingLighting.G);
 fprintf(File,"%i ",WorkingLighting.B);
 fprintf(File,"%i ",WorkingLighting.Mode);
 fprintf(File,"%i ",WorkingLighting.TimeInterval);
 fprintf(File,"%f ",WorkingLighting.Mode2_DarkTime);
 fprintf(File,"%f ",WorkingLighting.Mode2_LightTime);
 fprintf(File,"%f ",WorkingLighting.Mode2_MinimumLightLevel);
 fprintf(File,"%f ",WorkingLighting.Mode3_CycleTime);
 fprintf(File,"%f ",WorkingLighting.Mode3_MinimumLightLevel);
 fprintf(File,"%f ",WorkingLighting.Mode4_MinimumLightLevel);
 fprintf(File,"%f ",WorkingLighting.Mode4_OffTime);
 fprintf(File,"%f \n",WorkingLighting.Mode4_OnTime);
}
void CREATELIGHTINGFORM::LoadLighting(FILE *File)
{
 if (GetReadPos(File,"LIGHTING STRUCTURE")==0) return;
 GetReadPos(File,"MAXIMUM");
 KeyData.MaximumNumberOfLighting=(int)ReadNumber(File);
 for(int n=0;n<KeyData.MaximumNumberOfLighting;n++)
 {
  Lighting[n].X=(int)ReadNumber(File);
  Lighting[n].Y=(int)ReadNumber(File);
  Lighting[n].Z=(int)ReadNumber(File);
  Lighting[n].R=(int)ReadNumber(File);
  Lighting[n].G=(int)ReadNumber(File);
  Lighting[n].B=(int)ReadNumber(File);
   
  Lighting[n].Mode=(int)ReadNumber(File);
  Lighting[n].TimeInterval=(int)ReadNumber(File); 
  Lighting[n].Mode2_DarkTime=ReadNumber(File);
  Lighting[n].Mode2_LightTime=ReadNumber(File);
  Lighting[n].Mode2_MinimumLightLevel=ReadNumber(File);
  Lighting[n].Mode3_CycleTime=ReadNumber(File);
  Lighting[n].Mode3_MinimumLightLevel=ReadNumber(File);
  Lighting[n].Mode4_MinimumLightLevel=ReadNumber(File);
  Lighting[n].Mode4_OffTime=ReadNumber(File);
  Lighting[n].Mode4_OnTime=ReadNumber(File);
 }
 WorkingLighting.X=(int)ReadNumber(File);
 WorkingLighting.Y=(int)ReadNumber(File);
 WorkingLighting.Z=(int)ReadNumber(File);
 WorkingLighting.R=(int)ReadNumber(File);
 WorkingLighting.G=(int)ReadNumber(File);
 WorkingLighting.B=(int)ReadNumber(File);
 WorkingLighting.Mode=(int)ReadNumber(File);
 WorkingLighting.TimeInterval=(int)ReadNumber(File);
 WorkingLighting.Mode2_DarkTime=ReadNumber(File);
 WorkingLighting.Mode2_LightTime=ReadNumber(File);
 WorkingLighting.Mode2_MinimumLightLevel=ReadNumber(File);
 WorkingLighting.Mode3_CycleTime=ReadNumber(File);
 WorkingLighting.Mode3_MinimumLightLevel=ReadNumber(File);
 WorkingLighting.Mode4_MinimumLightLevel=ReadNumber(File);
 WorkingLighting.Mode4_OffTime=ReadNumber(File);
 WorkingLighting.Mode4_OnTime=ReadNumber(File);
}
void CREATELIGHTINGFORM::DrawAllLighting(int xLeftMap,int yTopMap)
{
 for(int n=0;n<KeyData.MaximumNumberOfLighting;n++)
 {
  Circle((Lighting[n].X-xLeftMap)*10,(Lighting[n].Y-yTopMap)*10,8,Lighting[n].R,Lighting[n].G,Lighting[n].B);
  if (KeyData.SelectLighting==n) Circle((Lighting[n].X-xLeftMap)*10,(Lighting[n].Y-yTopMap)*10,5,255-Lighting[n].R,255-Lighting[n].G,255-Lighting[n].B);//выделенный источник света
 }
}
int CREATELIGHTINGFORM::GetLightingInScreen(int x,int y)
{
 int selected=-1;
 float minlen=1000000000.0;
 for(int n=0;n<KeyData.MaximumNumberOfLighting;n++)
 {
  float xl=(float)(Lighting[n].X*10.0);
  float yl=(float)(Lighting[n].Y*10.0);
  float dist=(float)(sqrt((xl-x)*(xl-x)+(yl-y)*(yl-y)));
  if (dist<0) continue;
  if (dist<=minlen)
  {
   minlen=dist;
   selected=n;
  }
 }
 return(selected); 
}
void CREATELIGHTINGFORM::SaveLightingFromRender(FILE *File,int lighting)
{
 SaveFloat(File,(float)(-Lighting[lighting].X*16.0));
 SaveFloat(File,(float)(Lighting[lighting].Z));
 SaveFloat(File,(float)(-Lighting[lighting].Y*16.0));
 SaveChar(File,Lighting[lighting].R);
 SaveChar(File,Lighting[lighting].G);
 SaveChar(File,Lighting[lighting].B);
 SaveInt(File,Lighting[lighting].Mode);
 SaveInt(File,Lighting[lighting].TimeInterval);
 SaveFloat(File,Lighting[lighting].Mode2_DarkTime);
 SaveFloat(File,Lighting[lighting].Mode2_LightTime);
 SaveFloat(File,Lighting[lighting].Mode2_MinimumLightLevel);
 SaveFloat(File,Lighting[lighting].Mode3_MinimumLightLevel);
 SaveFloat(File,Lighting[lighting].Mode3_CycleTime);
 SaveFloat(File,Lighting[lighting].Mode4_OnTime);
 SaveFloat(File,Lighting[lighting].Mode4_OffTime);
 SaveFloat(File,Lighting[lighting].Mode4_MinimumLightLevel);
}

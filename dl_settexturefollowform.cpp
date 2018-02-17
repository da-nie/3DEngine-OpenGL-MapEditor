#include "dl_settexturefollowform.h"

extern CDialog_SelectTexture cDialog_SelectTexture;

SETSTextureFollowCWnd_Form cDialog_SetTextureFollow;
//------------------------------------------------------------------------------
LONG WINAPI SETTEXTUREFOLLOWFORM_dlgProc(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam)
{
 switch(msg)
 {
  case WM_INITDIALOG:
  {
   cDialog_SetTextureFollow.InitDialog(hDlg,wParam,lParam);
   return(TRUE);
  }
  case WM_COMMAND:
  {
   cDialog_SetTextureFollow.Command(hDlg,wParam,lParam);
   return(TRUE);
  }
  case WM_HSCROLL:
  {
   cDialog_SetTextureFollow.HScroll(hDlg,wParam,lParam);
   return(TRUE);
  }
  case WM_PAINT:
  {
   cDialog_SetTextureFollow.Paint(hDlg,wParam,lParam);
   return(TRUE);
  }
 }
 return(FALSE);
}
//------------------------------------------------------------------------------
void SETSTextureFollowCWnd_Form::InitDialog(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 hDlg=hDlgs;
 hRadioButton_Mode1=GetDlgItem(hDlg,SETTEXTUREFOLLOWFORM_RADIOBUTTON_MODE1);
 hRadioButton_Mode2=GetDlgItem(hDlg,SETTEXTUREFOLLOWFORM_RADIOBUTTON_MODE2);
 hRadioButton_Disable=GetDlgItem(hDlg,SETTEXTUREFOLLOWFORM_RADIOBUTTON_DISABLE);
 hScrollBar_List=GetDlgItem(hDlg,SETTEXTUREFOLLOWFORM_SCROLLBAR_LIST);
  
 hRadioButton_SLToR=GetDlgItem(hDlg,SETTEXTUREFOLLOWFORM_RADIOBUTTON_SLTOR);
 hRadioButton_SUToD=GetDlgItem(hDlg,SETTEXTUREFOLLOWFORM_RADIOBUTTON_SUTOD);
 hRadioButton_InvertSLToR=GetDlgItem(hDlg,SETTEXTUREFOLLOWFORM_RADIOBUTTON_INVERTSLTOR);
 hRadioButton_InvertSUToD=GetDlgItem(hDlg,SETTEXTUREFOLLOWFORM_RADIOBUTTON_INVERTSUTOD);
 hEdit_SpeedSLToR=GetDlgItem(hDlg,SETTEXTUREFOLLOWFORM_EDIT_SPEEDSLTOR);
 hEdit_SpeedSUToD=GetDlgItem(hDlg,SETTEXTUREFOLLOWFORM_EDIT_SPEEDSUTOD);
  
 SendMessage(hRadioButton_Mode1,BM_SETCHECK,0,0);
 SendMessage(hRadioButton_Mode2,BM_SETCHECK,0,0);
 SendMessage(hRadioButton_Disable,BM_SETCHECK,0,0);
 SendMessage(hRadioButton_SLToR,BM_SETCHECK,0,0);
 SendMessage(hRadioButton_SUToD,BM_SETCHECK,0,0);
 SendMessage(hRadioButton_InvertSLToR,BM_SETCHECK,0,0);
 SendMessage(hRadioButton_InvertSUToD,BM_SETCHECK,0,0);
 SendMessage(hEdit_SpeedSLToR,EM_LIMITTEXT,(WPARAM)255,0);
 SendMessage(hEdit_SpeedSUToD,EM_LIMITTEXT,(WPARAM)255,0);
 char string[255];
 itoa(TextureFollow.SpeedLToR,string,10);
 SetWindowText(hEdit_SpeedSLToR,string);
 itoa(TextureFollow.SpeedUToD,string,10);
 SetWindowText(hEdit_SpeedSUToD,string);
 if (TextureFollow.ScrollLToR!=0)
 {
  SendMessage(hRadioButton_SLToR,BM_SETCHECK,1,0);
  if (TextureFollow.ScrollLToR==-1) SendMessage(hRadioButton_InvertSLToR,BM_SETCHECK,1,0);
 }
 else
 {
  EnableWindow(hRadioButton_InvertSLToR,FALSE);
  EnableWindow(hEdit_SpeedSLToR,FALSE);
 }
 if (TextureFollow.ScrollUToD!=0)
 {
  SendMessage(hRadioButton_SUToD,BM_SETCHECK,1,0);
  if (TextureFollow.ScrollUToD==-1) SendMessage(hRadioButton_InvertSUToD,BM_SETCHECK,1,0);
 }
 else
 {
  EnableWindow(hRadioButton_InvertSUToD,FALSE);
  EnableWindow(hEdit_SpeedSUToD,FALSE);
 }
 if (TextureFollow.Mode==0) SendMessage(hRadioButton_Disable,BM_SETCHECK,1,0);
 if (TextureFollow.Mode==1) SendMessage(hRadioButton_Mode1,BM_SETCHECK,1,0);
 if (TextureFollow.Mode==2) SendMessage(hRadioButton_Mode2,BM_SETCHECK,1,0);
 SetScrollRange(hScrollBar_List,SB_CTL,0,TextureFollow.MaximumTexture-1,TRUE);
 hPos=TextureFollow.MaximumTexture-3;
 if (hPos<0) hPos=0;
 SetScrollPos(hScrollBar_List,SB_CTL,hPos,TRUE);
}
void SETSTextureFollowCWnd_Form::Command(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 int id=LOWORD(wParam);
 if (id==SETTEXTUREFOLLOWFORM_BUTTON_CANCEL)
 {
  TextureFollow=OldTextureFollow;
  InvalidateRect(sKeyData.hWndMain,NULL,FALSE);
  EndDialog(hDlg,TRUE);
 }
 if (id==SETTEXTUREFOLLOWFORM_BUTTON_CREATE)
 {
  if (SendMessage(hRadioButton_Mode1,BM_GETCHECK,0,0)==1) TextureFollow.Mode=1;
  if (SendMessage(hRadioButton_Mode2,BM_GETCHECK,0,0)==1) TextureFollow.Mode=2;
  if (SendMessage(hRadioButton_Disable,BM_GETCHECK,0,0)==1) TextureFollow.Mode=0;
   
  if (SendMessage(hRadioButton_SLToR,BM_GETCHECK,0,0)==1) TextureFollow.ScrollLToR=1;
  else TextureFollow.ScrollLToR=0;
  if (SendMessage(hRadioButton_SUToD,BM_GETCHECK,0,0)==1) TextureFollow.ScrollUToD=1;
  else TextureFollow.ScrollUToD=0;
  if (SendMessage(hRadioButton_InvertSLToR,BM_GETCHECK,0,0)==1) TextureFollow.ScrollLToR=-TextureFollow.ScrollLToR;
  if (SendMessage(hRadioButton_InvertSUToD,BM_GETCHECK,0,0)==1) TextureFollow.ScrollUToD=-TextureFollow.ScrollUToD;
  char string[255];
  GetWindowText(hEdit_SpeedSLToR,string,255);
  TextureFollow.SpeedLToR=atoi(string);
  GetWindowText(hEdit_SpeedSUToD,string,255);
  TextureFollow.SpeedUToD=atoi(string);
  InvalidateRect(sKeyData.hWndMain,NULL,FALSE);
  EndDialog(hDlg,TRUE);
 }
 if (id==SETTEXTUREFOLLOWFORM_BUTTON_CLEAR)
 {
  TextureFollow.MaximumTexture=1;
  SetScrollRange(hScrollBar_List,SB_CTL,0,TextureFollow.MaximumTexture-1,TRUE);
  hPos=TextureFollow.MaximumTexture-1;
  SetScrollPos(hScrollBar_List,SB_CTL,hPos,TRUE);
  InvalidateRect(hDlg,NULL,FALSE);
 }
 if (id==SETTEXTUREFOLLOWFORM_BUTTON_DELETE)
 {
  if (TextureFollow.MaximumTexture<=1) return;
  TextureFollow.MaximumTexture--;
  SetScrollRange(hScrollBar_List,SB_CTL,0,TextureFollow.MaximumTexture-1,TRUE);
  hPos=TextureFollow.MaximumTexture-3;
  if (hPos<0) hPos=0;
  SetScrollPos(hScrollBar_List,SB_CTL,hPos,TRUE);
  InvalidateRect(hDlg,NULL,FALSE);
 }
 if (id==SETTEXTUREFOLLOWFORM_BUTTON_ADD)
 {
  if (TextureFollow.MaximumTexture>=100) return;
  STexture texture=cDialog_SelectTexture.Activate(hDlg,TextureFollow.TextureList[TextureFollow.MaximumTexture-1],1);
  if (cDialog_SelectTexture.CompareTextureStruct(texture,TextureFollow.TextureList[TextureFollow.MaximumTexture-1])==1) return;
  TextureFollow.TextureList[TextureFollow.MaximumTexture]=texture;
  TextureFollow.MaximumTexture++;
  SetScrollRange(hScrollBar_List,SB_CTL,0,TextureFollow.MaximumTexture-1,TRUE);
  hPos=TextureFollow.MaximumTexture-3;
  if (hPos<0) hPos=0;
  SetScrollPos(hScrollBar_List,SB_CTL,hPos,TRUE);
  InvalidateRect(hDlg,NULL,FALSE);
 }
 if (id==SETTEXTUREFOLLOWFORM_BUTTON_REPEAT)
 {
  if (TextureFollow.MaximumTexture>=100) return;
  TextureFollow.TextureList[TextureFollow.MaximumTexture]=TextureFollow.TextureList[TextureFollow.MaximumTexture-1];
  TextureFollow.MaximumTexture++;
  SetScrollRange(hScrollBar_List,SB_CTL,0,TextureFollow.MaximumTexture-1,TRUE);
  hPos=TextureFollow.MaximumTexture-3;
  if (hPos<0) hPos=0;
  SetScrollPos(hScrollBar_List,SB_CTL,hPos,TRUE);
  InvalidateRect(hDlg,NULL,FALSE);
 }
 if (id==SETTEXTUREFOLLOWFORM_RADIOBUTTON_SLTOR)
 {
  if (TextureFollow.ScrollLToR==0)
  {
   TextureFollow.ScrollLToR=1;
   SendMessage(hRadioButton_SLToR,BM_SETCHECK,1,0);
   EnableWindow(hRadioButton_InvertSLToR,TRUE);
   EnableWindow(hEdit_SpeedSLToR,TRUE);
  }
  else
  {
   TextureFollow.ScrollLToR=0;
   SendMessage(hRadioButton_SLToR,BM_SETCHECK,0,0);
   EnableWindow(hRadioButton_InvertSLToR,FALSE);
   EnableWindow(hEdit_SpeedSLToR,FALSE);
  }
 }
 if (id==SETTEXTUREFOLLOWFORM_RADIOBUTTON_SUTOD)
 {
  if (TextureFollow.ScrollUToD==0)
  {
   TextureFollow.ScrollUToD=1;
   SendMessage(hRadioButton_SUToD,BM_SETCHECK,1,0);
   EnableWindow(hRadioButton_InvertSUToD,TRUE);
   EnableWindow(hEdit_SpeedSUToD,TRUE);
  }
  else
  {
   TextureFollow.ScrollUToD=0;
   SendMessage(hRadioButton_SUToD,BM_SETCHECK,0,0);
   EnableWindow(hRadioButton_InvertSUToD,FALSE);
   EnableWindow(hEdit_SpeedSUToD,FALSE);
  }
 }
}
void SETSTextureFollowCWnd_Form::HScroll(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 int move=0;
 int msg=LOWORD(wParam);
 if (msg==SB_THUMBPOSITION || msg==SB_THUMBTRACK)
 {
  hPos=HIWORD(wParam);
  move=1;
 }
 if (msg==SB_LINELEFT)
 {
  hPos--;
  move=1;
 }
 if (msg==SB_LINERIGHT)
 {
  hPos++;
  move=1;
 }
 if (msg==SB_PAGELEFT)
 {
  hPos-=5;
  move=1;
 }
 if (msg==SB_PAGERIGHT)
 {
  hPos+=5;
  move=1;
 }
 if (move==1)
 {
  if (hPos<0) hPos=0;
  if (hPos>=TextureFollow.MaximumTexture) hPos=TextureFollow.MaximumTexture-1;
  SetScrollPos(hScrollBar_List,SB_CTL,hPos,TRUE);
  InvalidateRect(hDlg,NULL,FALSE);
 }
}
void SETSTextureFollowCWnd_Form::Paint(HWND hDlgs,WPARAM wParam,LPARAM lParam)
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
 for(int x=0;x<4;x++)
 {
  unsigned char TextureMap[128*128*3];
  STexture number;
  if (hPos+x<TextureFollow.MaximumTexture) number=TextureFollow.TextureList[hPos+x];
  if (hPos+x<TextureFollow.MaximumTexture) cDialog_SelectTexture.CreateTextureImage(number,TextureMap);
  else
  {
   for(int tx=0;tx<128;tx++)
   {
    for(int ty=0;ty<128;ty++)
    {
     int offset=(tx+(127-ty)*128)*3;
     TextureMap[offset]=0;
     TextureMap[offset+1]=0;
     TextureMap[offset+2]=0;
    }
   }
  }
  Rect.left=8+x*64;
  Rect.right=Rect.left+64;
  Rect.top=8;
  Rect.bottom=Rect.top+64;
  MapDialogRect(hDlg,&Rect);
  StretchDIBits(hdc,Rect.left,Rect.top,Rect.right-Rect.left,Rect.bottom-Rect.top,0,0,128,128,TextureMap,&info,DIB_RGB_COLORS,SRCCOPY);
 }
 EndPaint(hDlg,&ps);
}
//------------------------------------------------------------------------------
void SETSTextureFollowCWnd_Form::SaveForRender(STextureFollow texturefollow,FILE *File)
{
 SaveInt(File,texturefollow.Mode);
 SaveInt(File,texturefollow.MaximumTexture);
 for(int m=0;m<texturefollow.MaximumTexture;m++)
 SaveInt(File,texturefollow.TextureList[m].TextureNo);
 SaveInt(File,texturefollow.ScrollLToR);
 SaveInt(File,texturefollow.SpeedLToR);
 SaveInt(File,texturefollow.ScrollUToD);
 SaveInt(File,texturefollow.SpeedUToD);
}
void SETSTextureFollowCWnd_Form::Save(STextureFollow texturefollow,FILE *File)
{
 fprintf(File,"%i ",texturefollow.Mode);
 fprintf(File,"%i \n",texturefollow.MaximumTexture);
 for(int m=0;m<texturefollow.MaximumTexture;m++)
 cDialog_SelectTexture.SaveTextureStruct(File,texturefollow.TextureList[m]);
 fprintf(File,"\n%i ",texturefollow.ScrollLToR);
 fprintf(File,"%i ",texturefollow.SpeedLToR);
 fprintf(File,"%i ",texturefollow.ScrollUToD);
 fprintf(File,"%i \n",texturefollow.SpeedUToD);
}
void SETSTextureFollowCWnd_Form::Load(STextureFollow *texturefollow,FILE *File)
{
 texturefollow->Mode=(int)ReadNumber(File);
 texturefollow->MaximumTexture=(int)ReadNumber(File);
 for(int m=0;m<texturefollow->MaximumTexture;m++)
 texturefollow->TextureList[m]=cDialog_SelectTexture.LoadTextureStruct(File);
 texturefollow->ScrollLToR=(int)ReadNumber(File);
 texturefollow->SpeedLToR=(int)ReadNumber(File);
 texturefollow->ScrollUToD=(int)ReadNumber(File);
 texturefollow->SpeedUToD=(int)ReadNumber(File);
}
void SETSTextureFollowCWnd_Form::InitializeTextureFollow(STextureFollow *texturefollow)
{
 texturefollow->MaximumTexture=1;
 texturefollow->Mode=0;
 texturefollow->MaximumTexture=1;
 texturefollow->Mode=0;
 texturefollow->ScrollLToR=0;
 texturefollow->ScrollUToD=0;
 texturefollow->SpeedLToR=0;
 texturefollow->SpeedUToD=0;
}
//------------------------------------------------------------------------------
STextureFollow SETSTextureFollowCWnd_Form::Activate(HWND hWnd,STextureFollow texturefollow)
{
 OldTextureFollow=texturefollow;
 TextureFollow=texturefollow;
 for(int n=1;n<TextureFollow.MaximumTexture;n++)
 cDialog_SelectTexture.CopyTextureStruct(&TextureFollow.TextureList[n],TextureFollow.TextureList[0]);
 DialogBox(hProjectInstance,(LPSTR)13,hWnd,(DLGPROC)SETTEXTUREFOLLOWFORM_dlgProc);
 return(TextureFollow);
}
 

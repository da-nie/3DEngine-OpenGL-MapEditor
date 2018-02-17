#include "dl_showtextureform.h"

//------------------------------------------------------------------------------
SHOWTEXTUREFORM ShowTextureForm;

//------------------------------------------------------------------------------
LONG WINAPI SHOWTEXTUREFORM_dlgProc(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam)
{
 switch(msg)
 {
  case WM_INITDIALOG:
  {
   ShowTextureForm.InitDialog(hDlg,wParam,lParam);
   return(TRUE);
  }
  case WM_COMMAND:
  {
   ShowTextureForm.Command(hDlg,wParam,lParam);
   return(TRUE);
  }
  case WM_PAINT:
  {
   ShowTextureForm.Paint(hDlg,wParam,lParam);
   return(TRUE);
  }
  case WM_HSCROLL:
  {
   ShowTextureForm.HScroll(hDlg,wParam,lParam);
   return(TRUE);
  }
  case WM_VSCROLL:
  {
   ShowTextureForm.VScroll(hDlg,wParam,lParam);
   return(TRUE);
  }
 }
 return(FALSE);
}
//------------------------------------------------------------------------------
void SHOWTEXTUREFORM::InitDialog(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 hDlg=hDlgs;
 hScroll_Vertical=GetDlgItem(hDlg,SHOWTEXTUREFORM_SCROLL_VERTICAL);
 hScroll_Horizontal=GetDlgItem(hDlg,SHOWTEXTUREFORM_SCROLL_HORIZONTAL);
 hStatic_Height=GetDlgItem(hDlg,SHOWTEXTUREFORM_STATIC_HEIGHT);
 hStatic_Width=GetDlgItem(hDlg,SHOWTEXTUREFORM_STATIC_WIDTH);
 char string[256];
 itoa(KeyData.TextureMap[TextureNo].Size,string,10);
 SetWindowText(hStatic_Height,string);
 SetWindowText(hStatic_Width,string);
  
 hPosMax=KeyData.TextureMap[TextureNo].Size-256;
 vPosMax=hPosMax;
 hPos=0;
 vPos=0;
 if (hPosMax>0)
 {
  SetScrollRange(hScroll_Horizontal,SB_CTL,0,hPosMax,TRUE);
  SetScrollRange(hScroll_Vertical,SB_CTL,0,vPosMax,TRUE);
  SetScrollPos(hScroll_Horizontal,SB_CTL,hPos,TRUE);
  SetScrollPos(hScroll_Vertical,SB_CTL,vPos,TRUE);
 }
 else
 {
  EnableWindow(hScroll_Horizontal,FALSE);
  EnableWindow(hScroll_Vertical,FALSE);
 }
}
void SHOWTEXTUREFORM::Command(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 int id=LOWORD(wParam);
 if (id==SHOWTEXTUREFORM_BUTTON_EXIT)
 {
  InvalidateRect(KeyData.hWndMain,NULL,FALSE);
  EndDialog(hDlg,TRUE);
 }
}
void SHOWTEXTUREFORM::Paint(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 RECT Rect;
 PAINTSTRUCT ps;
 HDC hdc;
 hdc=BeginPaint(hDlg,&ps);
 unsigned char TextureMap[256*256*3];
 int tms=KeyData.TextureMap[TextureNo].Size;
 for(int tx=0;tx<256;tx++)
 for(int ty=0;ty<256;ty++)
 {
  int offset=(tx+(256-ty-1)*256)*3;
  unsigned char R=0;
  unsigned char G=0;
  unsigned char B=0;
  if (tx+hPos<tms && ty+vPos<tms)
  {
   int offset1=(tx+hPos)*tms+(ty+vPos);
   R=KeyData.TextureMap[TextureNo].R[offset1];
   G=KeyData.TextureMap[TextureNo].G[offset1];
   B=KeyData.TextureMap[TextureNo].B[offset1];
  }
  TextureMap[offset]=B;
  TextureMap[offset+1]=G;
  TextureMap[offset+2]=R;
 }
 Rect.left=12;
 Rect.right=Rect.left+128;
 Rect.top=12;
 Rect.bottom=Rect.top+128;
 MapDialogRect(hDlg,&Rect);
 BITMAPINFOHEADER bmih;
 bmih.biSize=sizeof(BITMAPINFOHEADER);
 bmih.biWidth=256;
 bmih.biHeight=256;
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
 StretchDIBits(hdc,Rect.left,Rect.top,Rect.right-Rect.left,Rect.bottom-Rect.top,0,0,256,256,TextureMap,&info,DIB_RGB_COLORS,SRCCOPY);
 EndPaint(hDlg,&ps);
}
void SHOWTEXTUREFORM::HScroll(HWND hDlgs,WPARAM wParam,LPARAM lParam)
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
  hPos-=128;
  move=1;
 }
 if (msg==SB_PAGERIGHT)
 {
  hPos+=128;
  move=1;
 }
 if (move==1)
 {
  if (hPos<0) hPos=0;
  if (hPos>=hPosMax) hPos=hPosMax;
  SetScrollPos(hScroll_Horizontal,SB_CTL,hPos,TRUE);
  InvalidateRect(hDlg,NULL,FALSE);
 }
}
void SHOWTEXTUREFORM::VScroll(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 int move=0;
 int msg=LOWORD(wParam);
 if (msg==SB_THUMBPOSITION || msg==SB_THUMBTRACK)
 {
  vPos=HIWORD(wParam);
  move=1;
 }
 if (msg==SB_LINELEFT)
 {
  vPos--;
  move=1;
 }
 if (msg==SB_LINERIGHT)
 {
  vPos++;
  move=1;
 }
 if (msg==SB_PAGELEFT)
 {
  vPos-=128;
  move=1;
 }
 if (msg==SB_PAGERIGHT)
 {
  vPos+=128;
  move=1;
 }
 if (move==1)
 {
  if (vPos<0) vPos=0;
  if (vPos>=vPosMax) vPos=vPosMax;
  SetScrollPos(hScroll_Vertical,SB_CTL,vPos,TRUE);
  InvalidateRect(hDlg,NULL,FALSE);
 }
}
//------------------------------------------------------------------------------
void SHOWTEXTUREFORM::Activate(int texture,HWND hWnd)
{
 TextureNo=texture;
 EnableWindow(KeyData.hWndMenu,FALSE);
 DialogBox(hProjectInstance,(LPSTR)14,hWnd,(DLGPROC)SHOWTEXTUREFORM_dlgProc);
 EnableWindow(KeyData.hWndMenu,TRUE);
}
 

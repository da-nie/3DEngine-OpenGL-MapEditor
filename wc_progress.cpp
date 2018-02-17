#include "wc_progress.h"

extern HINSTANCE hProjectInstance;

CWnd_Progress cWnd_Progress;

//------------------------------------------------------------------------------
void CWnd_Progress_Register(void)
{
 WNDCLASS wc;
 wc.style=CS_HREDRAW|CS_VREDRAW;
 wc.cbClsExtra=0;
 wc.cbWndExtra=0;
 wc.hInstance=hProjectInstance;
 wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
 wc.hCursor=LoadCursor(NULL,IDC_ARROW);
 wc.hbrBackground=(HBRUSH)(COLOR_WINDOW);
 wc.lpszMenuName=NULL;
 wc.lpszClassName="cWnd_Progress";
 wc.lpfnWndProc=(WNDPROC)CWnd_Progress_wndProc;
 RegisterClass(&wc);
}
LONG WINAPI CWnd_Progress_wndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
 switch(msg)
 {
  case WM_CREATE:
  {
   cWnd_Progress.Create(hWnd,wParam,lParam);
   return(0);
  }
  case WM_DESTROY:
  {
   return(0);
  }
  case WM_PAINT:
  {
   cWnd_Progress.Paint(hWnd,wParam,lParam);
   return(0);
  }
 }
 return(DefWindowProc(hWnd,msg,wParam,lParam));
}
//------------------------------------------------------------------------------
void CWnd_Progress::Create(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 hWnd=hWnds;
}
void CWnd_Progress::Paint(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 RECT Rect;
 GetClientRect(hWnd,&Rect);
 PAINTSTRUCT ps;
 HDC hdc=BeginPaint(hWnd,&ps);
 float r=0;
 float dr=(float)(255.0/((float)(Rect.right-Rect.left-10.0)));
 int xo=(int)(cWnd_Progress*((float)(Rect.right-Rect.left-10))+5);
 for(int x=Rect.left+5;x<=Rect.right-5;x++,r+=dr)
 {
  if (x<=xo)
  {
   float b=255;
   float db=(float)(255.0/((float)(Rect.bottom-Rect.top-40)));
   for(int y=Rect.top+20;y<=Rect.bottom-20;y++,b-=db) SetPixel(hdc,x,y,RGB(r,32,b));
  }
  else
  {
   for(int y=Rect.top+20;y<=Rect.bottom-20;y++) SetPixel(hdc,x,y,RGB(128,128,128));
  }
 }
 EndPaint(hWnd,&ps);
}

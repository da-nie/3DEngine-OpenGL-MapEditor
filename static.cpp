#include "static.h"

void STATIC::Create(int x,int y,int cx,int cy,char *Text,long Style,HWND hWnd,HINSTANCE hInstance)
{
 Handle=CreateWindow("static",Text,WS_VISIBLE|Style|WS_CHILD,
 x,y,cx,cy,hWnd,(HMENU)0,hInstance,NULL);
}
void STATIC::SetText(char *Text)
{
 SetWindowText(Handle,Text);
}

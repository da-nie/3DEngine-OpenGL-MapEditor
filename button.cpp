#include "button.h"
 
//------------------------------------------------------------------------------
void BUTTON::Create(int x,int y,int cx,int cy,char *Name,int iD,long Style,HWND hWnd,HINSTANCE hInstance)
{
 Handle=CreateWindow("button",Name,WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON|Style,
 x,y,cx,cy,hWnd,(HMENU)iD,hInstance,NULL);
}
void BUTTON::SetStateOn(void)
{
 SendMessage(Handle,BM_SETSTATE,TRUE,0l);
}
void BUTTON::SetStateOff(void)
{
 SendMessage(Handle,BM_SETSTATE,FALSE,0l);
}
int BUTTON::GetState(void)
{
 int state=SendMessage(Handle,BM_GETCHECK,0,0l);
 if (state==0) return(OFF);
 return(ON);
}
void BUTTON::Disable(void)
{
 EnableWindow(Handle,FALSE);
}
void BUTTON::Enable(void)
{
 EnableWindow(Handle,TRUE);
}
//------------------------------------------------------------------------------
void RADIOBUTTON::Create(int x,int y,int cx,int cy,char *Name,int iD,long Style,HWND hWnd,HINSTANCE hInstance)
{
 Handle=CreateWindow("button",Name,WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON|Style,
 x,y,cx,cy,hWnd,(HMENU)iD,hInstance,NULL);
}
void RADIOBUTTON::SetStateOn(void)
{
 SendMessage(Handle,BM_SETCHECK,1,0l);
}
void RADIOBUTTON::SetStateOff(void)
{
 SendMessage(Handle,BM_SETCHECK,0,0l);
}
void RADIOBUTTON::SetStateDisable(void)
{
 SendMessage(Handle,BM_SETCHECK,2,0l);
}
int RADIOBUTTON::GetState(void)
{
 int state=SendMessage(Handle,BM_GETCHECK,0,0l);
 if (state==0) return(OFF);
 if (state==1) return(ON);
 return(DISABLE);
}
void RADIOBUTTON::Disable(void)
{
 EnableWindow(Handle,FALSE);
}
void RADIOBUTTON::Enable(void)
{
 EnableWindow(Handle,TRUE);
}
//------------------------------------------------------------------------------
void CHECKBOX::Create(int x,int y,int cx,int cy,char *Name,int iD,long Style,HWND hWnd,HINSTANCE hInstance)
{
 Handle=CreateWindow("button",Name,WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX|Style,
 x,y,cx,cy,hWnd,(HMENU)iD,hInstance,NULL);
}
void CHECKBOX::SetStateOn(void)
{
 SendMessage(Handle,BM_SETCHECK,1,0l);
}
void CHECKBOX::SetStateOff(void)
{
 SendMessage(Handle,BM_SETCHECK,0,0l);
}
void CHECKBOX::SetStateDisable(void)
{
 SendMessage(Handle,BM_SETCHECK,2,0l);
}
int CHECKBOX::GetState(void)
{
 int state=SendMessage(Handle,BM_GETCHECK,0,0l);
 if (state==0) return(OFF);
 if (state==1) return(ON);
 return(DISABLE);
}
void CHECKBOX::Disable(void)
{
 EnableWindow(Handle,FALSE);
}
void CHECKBOX::Enable(void)
{
 EnableWindow(Handle,TRUE);
}
//------------------------------------------------------------------------------
void CHECKBOX3STATE::Create(int x,int y,int cx,int cy,char *Name,int iD,long Style,HWND hWnd,HINSTANCE hInstance)
{
 Handle=CreateWindow("button",Name,WS_CHILD|WS_VISIBLE|BS_AUTO3STATE|Style,
 x,y,cx,cy,hWnd,(HMENU)iD,hInstance,NULL);
}
void CHECKBOX3STATE::SetStateOn(void)
{
 SendMessage(Handle,BM_SETCHECK,1,0l);
}
void CHECKBOX3STATE::SetStateOff(void)
{
 SendMessage(Handle,BM_SETCHECK,0,0l);
}
void CHECKBOX3STATE::SetStateDisable(void)
{
 SendMessage(Handle,BM_SETCHECK,2,0l);
}
int CHECKBOX3STATE::GetState(void)
{
 int state=SendMessage(Handle,BM_GETCHECK,0,0l);
 if (state==0) return(OFF);
 if (state==1) return(ON);
 return(DISABLE);
}
void CHECKBOX3STATE::Disable(void)
{
 EnableWindow(Handle,FALSE);
}
void CHECKBOX3STATE::Enable(void)
{
 EnableWindow(Handle,TRUE);
}
 

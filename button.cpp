#include "button.h"
 
//------------------------------------------------------------------------------
void CButton::Create(int x,int y,int cx,int cy,char *Name,int iD,long Style,HWND hWnd,HINSTANCE hInstance)
{
 Handle=CreateWindow("button",Name,WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON|Style,
 x,y,cx,cy,hWnd,(HMENU)iD,hInstance,NULL);
}
void CButton::SetStateOn(void)
{
 SendMessage(Handle,BM_SETSTATE,TRUE,0l);
}
void CButton::SetStateOff(void)
{
 SendMessage(Handle,BM_SETSTATE,FALSE,0l);
}
int CButton::GetState(void)
{
 int state=SendMessage(Handle,BM_GETCHECK,0,0l);
 if (state==0) return(OFF);
 return(ON);
}
void CButton::Disable(void)
{
 EnableWindow(Handle,FALSE);
}
void CButton::Enable(void)
{
 EnableWindow(Handle,TRUE);
}
//------------------------------------------------------------------------------
void RADIOCButton::Create(int x,int y,int cx,int cy,char *Name,int iD,long Style,HWND hWnd,HINSTANCE hInstance)
{
 Handle=CreateWindow("button",Name,WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON|Style,
 x,y,cx,cy,hWnd,(HMENU)iD,hInstance,NULL);
}
void RADIOCButton::SetStateOn(void)
{
 SendMessage(Handle,BM_SETCHECK,1,0l);
}
void RADIOCButton::SetStateOff(void)
{
 SendMessage(Handle,BM_SETCHECK,0,0l);
}
void RADIOCButton::SetStateDisable(void)
{
 SendMessage(Handle,BM_SETCHECK,2,0l);
}
int RADIOCButton::GetState(void)
{
 int state=SendMessage(Handle,BM_GETCHECK,0,0l);
 if (state==0) return(OFF);
 if (state==1) return(ON);
 return(DISABLE);
}
void RADIOCButton::Disable(void)
{
 EnableWindow(Handle,FALSE);
}
void RADIOCButton::Enable(void)
{
 EnableWindow(Handle,TRUE);
}
//------------------------------------------------------------------------------
void CCheckBox::Create(int x,int y,int cx,int cy,char *Name,int iD,long Style,HWND hWnd,HINSTANCE hInstance)
{
 Handle=CreateWindow("button",Name,WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX|Style,
 x,y,cx,cy,hWnd,(HMENU)iD,hInstance,NULL);
}
void CCheckBox::SetStateOn(void)
{
 SendMessage(Handle,BM_SETCHECK,1,0l);
}
void CCheckBox::SetStateOff(void)
{
 SendMessage(Handle,BM_SETCHECK,0,0l);
}
void CCheckBox::SetStateDisable(void)
{
 SendMessage(Handle,BM_SETCHECK,2,0l);
}
int CCheckBox::GetState(void)
{
 int state=SendMessage(Handle,BM_GETCHECK,0,0l);
 if (state==0) return(OFF);
 if (state==1) return(ON);
 return(DISABLE);
}
void CCheckBox::Disable(void)
{
 EnableWindow(Handle,FALSE);
}
void CCheckBox::Enable(void)
{
 EnableWindow(Handle,TRUE);
}
//------------------------------------------------------------------------------
void CCheckBox3STATE::Create(int x,int y,int cx,int cy,char *Name,int iD,long Style,HWND hWnd,HINSTANCE hInstance)
{
 Handle=CreateWindow("button",Name,WS_CHILD|WS_VISIBLE|BS_AUTO3STATE|Style,
 x,y,cx,cy,hWnd,(HMENU)iD,hInstance,NULL);
}
void CCheckBox3STATE::SetStateOn(void)
{
 SendMessage(Handle,BM_SETCHECK,1,0l);
}
void CCheckBox3STATE::SetStateOff(void)
{
 SendMessage(Handle,BM_SETCHECK,0,0l);
}
void CCheckBox3STATE::SetStateDisable(void)
{
 SendMessage(Handle,BM_SETCHECK,2,0l);
}
int CCheckBox3STATE::GetState(void)
{
 int state=SendMessage(Handle,BM_GETCHECK,0,0l);
 if (state==0) return(OFF);
 if (state==1) return(ON);
 return(DISABLE);
}
void CCheckBox3STATE::Disable(void)
{
 EnableWindow(Handle,FALSE);
}
void CCheckBox3STATE::Enable(void)
{
 EnableWindow(Handle,TRUE);
}
 

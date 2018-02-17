#include "colorset.h"
 
void CColorSet::Create(long Style,HWND hWnd,HINSTANCE hInstance)
{
 cc.lStructSize=sizeof(CHOOSECOLOR);
 cc.hwndOwner=hWnd;
 cc.hInstance=(HWND)hInstance;
 cc.rgbResult=clr;
 cc.lpCustColors=CustColor;
 cc.Flags=Style;
 for(int n=0;n<16;n++) SetCustColor(n,255,255,255);
}
int CColorSet::Activate(unsigned char *R,unsigned char *G,unsigned char *B)
{
 if(ChooseColor(&cc))
 {
  unsigned char r=(unsigned char)(cc.rgbResult&255);
  unsigned char g=(unsigned char)((cc.rgbResult&65280)>>8);
  unsigned char b=(unsigned char)((cc.rgbResult&16711680)>>16);
  *R=r;
  *G=g;
  *B=b;
  return(1);
 }
 return(0);
}
void CColorSet::SetCustColor(int number,unsigned char R,unsigned char G,unsigned char B)
{
 if (number>=16 || number<0) return;
 CustColor[number]=RGB(R,G,B);
}

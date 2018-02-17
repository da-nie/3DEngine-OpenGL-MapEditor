#include "dl_selecttextureform.h"

extern SHOWSTextureCWnd_Form ShowTexturecWnd_Form;

CDialog_SelectTexture cDialog_SelectTexture;

//------------------------------------------------------------------------------
LONG WINAPI SELECTTEXTUREFORM_dlgProc(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam)
{
 switch(msg)
 {
  case WM_INITDIALOG:
  {
   cDialog_SelectTexture.InitDialog(hDlg,wParam,lParam);
   return(TRUE);
  }
  case WM_COMMAND:
  {
   cDialog_SelectTexture.Command(hDlg,wParam,lParam);
   return(TRUE);
  }
  case WM_PAINT:
  {
   cDialog_SelectTexture.Paint(hDlg,wParam,lParam);
   return(TRUE);
  }
  case WM_HSCROLL:
  {
   cDialog_SelectTexture.HScroll(hDlg,wParam,lParam);
   return(TRUE);
  }
  case WM_VSCROLL:
  {
   cDialog_SelectTexture.VScroll(hDlg,wParam,lParam);
   return(TRUE);
  }
  case WM_LBUTTONUP:
  {
   cDialog_SelectTexture.LButtonUp(hDlg,wParam,lParam);
   return(TRUE);
  }
 }
 return(FALSE);
}
//------------------------------------------------------------------------------
void CDialog_SelectTexture::InitDialog(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 hDlg=hDlgs;
 hButton_Ok=GetDlgItem(hDlg,SELECTTEXTUREFORM_BUTTON_OK);
 hButton_Cancel=GetDlgItem(hDlg,SELECTTEXTUREFORM_BUTTON_CANCEL);
 hScroll_Horizontal=GetDlgItem(hDlg,SELECTTEXTUREFORM_SCROLL_HORIZONTAL);
 hScroll_Vertical=GetDlgItem(hDlg,SELECTTEXTUREFORM_SCROLL_VERTICAL);
 hEdit_Offset_X=GetDlgItem(hDlg,SELECTTEXTUREFORM_EDIT_OFFSET_X);
 hEdit_Offset_Y=GetDlgItem(hDlg,SELECTTEXTUREFORM_EDIT_OFFSET_Y);
 hEdit_Scale_X=GetDlgItem(hDlg,SELECTTEXTUREFORM_EDIT_SCALE_X);
 hEdit_Scale_Y=GetDlgItem(hDlg,SELECTTEXTUREFORM_EDIT_SCALE_Y);
 hCheckBox_Flip_V=GetDlgItem(hDlg,SELECTTEXTUREFORM_CHECKBOX_FLIP_V);
 hCheckBox_Flip_H=GetDlgItem(hDlg,SELECTTEXTUREFORM_CHECKBOX_FLIP_H);
 hCheckBox_Rotate=GetDlgItem(hDlg,SELECTTEXTUREFORM_CHECKBOX_ROTATE);
  
 SetScrollRange(hScroll_Horizontal,SB_CTL,0,hPosMax-1,TRUE);
 SetScrollRange(hScroll_Vertical,SB_CTL,0,vPosMax-1,TRUE);
 SetScrollPos(hScroll_Horizontal,SB_CTL,hPos,TRUE);
 SetScrollPos(hScroll_Vertical,SB_CTL,vPos,TRUE);
  
 char string[255];
 itoa(WorkingTexture.OffsetX,string,10);
 SetWindowText(hEdit_Offset_X,string);
 itoa(WorkingTexture.OffsetY,string,10);
 SetWindowText(hEdit_Offset_Y,string);
  
 itoa(WorkingTexture.ScaleX,string,10);
 SetWindowText(hEdit_Scale_X,string);
 itoa(WorkingTexture.ScaleY,string,10);
 SetWindowText(hEdit_Scale_Y,string);
  
 if (WorkingTexture.FlipVertical==1) SendMessage(hCheckBox_Flip_V,BM_SETCHECK,1,0);
 else SendMessage(hCheckBox_Flip_V,BM_SETCHECK,0,0);
 if (WorkingTexture.FlipHorizontal==1) SendMessage(hCheckBox_Flip_H,BM_SETCHECK,1,0);
 else SendMessage(hCheckBox_Flip_H,BM_SETCHECK,0,0);
 if (WorkingTexture.Rotate==1) SendMessage(hCheckBox_Rotate,BM_SETCHECK,1,0);
 else SendMessage(hCheckBox_Rotate,BM_SETCHECK,0,0);
 if (Mode==1)
 {
  EnableWindow(hEdit_Offset_X,FALSE);
  EnableWindow(hEdit_Offset_Y,FALSE);
  EnableWindow(hEdit_Scale_X,FALSE);
  EnableWindow(hEdit_Scale_Y,FALSE);
  EnableWindow(hCheckBox_Flip_V,FALSE);
  EnableWindow(hCheckBox_Flip_H,FALSE);
  EnableWindow(hCheckBox_Rotate,FALSE);
 }
}
void CDialog_SelectTexture::Command(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 int id=LOWORD(wParam);
 int ia=HIWORD(wParam);
 if (id==SELECTTEXTUREFORM_BUTTON_CANCEL)
 {
  WorkingTexture=OldTexture;
  EndDialog(hDlg,TRUE);
 }
 if (id==SELECTTEXTUREFORM_BUTTON_OK)
 {
  char string[256];
  GetWindowText(hEdit_Scale_X,string,256);
  WorkingTexture.ScaleX=atoi(string);
  if (WorkingTexture.ScaleX==0) WorkingTexture.ScaleX=100;
  GetWindowText(hEdit_Scale_Y,string,256);
  WorkingTexture.ScaleY=atoi(string);
  if (WorkingTexture.ScaleY==0) WorkingTexture.ScaleY=100;
  EndDialog(hDlg,TRUE);
 }
 if (id==SELECTTEXTUREFORM_BUTTON_SHOWIMAGE) ShowTexturecWnd_Form.Activate(WorkingTexture.TextureNo,hDlg);
 if (id==SELECTTEXTUREFORM_CHECKBOX_FLIP_V)
 {
  WorkingTexture.FlipVertical=SendMessage(hCheckBox_Flip_V,BM_GETCHECK,0,0);
  InvalidateRect(hDlg,NULL,FALSE);
 }
 if (id==SELECTTEXTUREFORM_CHECKBOX_FLIP_H)
 {
  WorkingTexture.FlipHorizontal=SendMessage(hCheckBox_Flip_H,BM_GETCHECK,0,0);
  InvalidateRect(hDlg,NULL,FALSE);
 }
 if (id==SELECTTEXTUREFORM_CHECKBOX_ROTATE)
 {
  WorkingTexture.Rotate=SendMessage(hCheckBox_Rotate,BM_GETCHECK,0,0);
  InvalidateRect(hDlg,NULL,FALSE);
 }
 if (id==SELECTTEXTUREFORM_EDIT_OFFSET_X)
 {
  if (ia==EN_CHANGE)
  {
   char string[256];
   GetWindowText(hEdit_Offset_X,string,256);
   WorkingTexture.OffsetX=atoi(string);
   if (WorkingTexture.OffsetX>=sKeyData.TextureMap[WorkingTexture.TextureNo].Size)
   {
    WorkingTexture.OffsetX=sKeyData.TextureMap[WorkingTexture.TextureNo].Size-1;
    itoa(WorkingTexture.OffsetX,string,10);
    SetWindowText(hEdit_Offset_X,string);
   }
   InvalidateRect(hDlg,NULL,FALSE);
  }
 }
 if (id==SELECTTEXTUREFORM_EDIT_OFFSET_Y)
 {
  if (ia==EN_CHANGE)
  {
   char string[256];
   GetWindowText(hEdit_Offset_Y,string,256);
   WorkingTexture.OffsetY=atoi(string);
   if (WorkingTexture.OffsetY>=sKeyData.TextureMap[WorkingTexture.TextureNo].Size)
   {
    WorkingTexture.OffsetY=sKeyData.TextureMap[WorkingTexture.TextureNo].Size-1;
    itoa(WorkingTexture.OffsetY,string,10);
    SetWindowText(hEdit_Offset_Y,string);
   }
   InvalidateRect(hDlg,NULL,FALSE);
  }
 }
}
void CDialog_SelectTexture::Paint(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 RECT Rect;
 PAINTSTRUCT ps;
 HDC hdc;
 hdc=BeginPaint(hDlg,&ps);
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
 unsigned char TextureMap[128*128*3];
 for(int x=0;x<5;x++)
 for(int y=0;y<3;y++)
 {
  int number=hPos+x+(vPos+y)*50;
  int tms=128;
  if (number<sKeyData.MaximumTexture) tms=sKeyData.TextureMap[number].Size;
  float kx=(float)((float)tms/128.0);
  float ky=(float)((float)tms/128.0);
  float tmx=0,tmy=0;
  for(int tx=0;tx<128;tx++,tmx=tmx+kx)
  {
   tmy=0;
   for(int ty=0;ty<128;ty++,tmy=tmy+ky)
   {
    int offset=(tx+(127-ty)*128)*3;
    int offset1=((int)(tmx))*tms+(int)(tmy);
    unsigned char R=0;
    unsigned char G=0;
    unsigned char B=0;
    if (number<sKeyData.MaximumTexture)
    {
     R=sKeyData.TextureMap[number].R[offset1];
     G=sKeyData.TextureMap[number].G[offset1];
     B=sKeyData.TextureMap[number].B[offset1];
    }
    if (WorkingTexture.TextureNo==number)
    {
     if (tx<8 || tx>=120 || ty<8 || ty>=120)
     {
      R=G^255;
      G=B^255;
      B=R^255;
     }
    }
    TextureMap[offset]=B;
    TextureMap[offset+1]=G;
    TextureMap[offset+2]=R;
   }
  }
  Rect.left=4+x*64;
  Rect.right=Rect.left+64;
  Rect.top=4+y*64;
  Rect.bottom=Rect.top+64;
  MapDialogRect(hDlg,&Rect);
  StretchDIBits(hdc,Rect.left,Rect.top,Rect.right-Rect.left,Rect.bottom-Rect.top,0,0,128,128,TextureMap,&info,DIB_RGB_COLORS,SRCCOPY);
 }
 CreateTextureImage(WorkingTexture,TextureMap);
 Rect.left=340;
 Rect.right=Rect.left+64;
 Rect.top=8;
 Rect.bottom=Rect.top+64;
 MapDialogRect(hDlg,&Rect);
 StretchDIBits(hdc,Rect.left,Rect.top,Rect.right-Rect.left,Rect.bottom-Rect.top,0,0,128,128,TextureMap,&info,DIB_RGB_COLORS,SRCCOPY);
 EndPaint(hDlg,&ps);
}
void CDialog_SelectTexture::HScroll(HWND hDlgs,WPARAM wParam,LPARAM lParam)
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
  if (hPos>=hPosMax-1) hPos=hPosMax-1;
  if (hPos<0) hPos=0;
  SetScrollPos(hScroll_Horizontal,SB_CTL,hPos,TRUE);
  InvalidateRect(hDlg,NULL,FALSE);
 }
}
void CDialog_SelectTexture::VScroll(HWND hDlgs,WPARAM wParam,LPARAM lParam)
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
  vPos-=3;
  move=1;
 }
 if (msg==SB_PAGERIGHT)
 {
  vPos+=3;
  move=1;
 }
 if (move==1)
 {
  if (vPos>vPosMax-1) vPos=vPosMax-1;
  if (vPos<0) vPos=0;
  SetScrollPos(hScroll_Vertical,SB_CTL,vPos,TRUE);
  InvalidateRect(hDlg,NULL,FALSE);
 }
}
void CDialog_SelectTexture::LButtonUp(HWND hDlgs,WPARAM wParam,LPARAM lParam)
{
 DWORD xyPos=GetMessagePos();
 POINT Point;
 Point.x=LOWORD(xyPos);
 Point.y=HIWORD(xyPos);
 ScreenToClient(hDlg,&Point);
 RECT Rect;
 Rect.left=4;
 Rect.right=Rect.left+64;
 Rect.top=4;
 Rect.bottom=Rect.top+64;
 MapDialogRect(hDlg,&Rect);
 int MouseX=Point.x-Rect.left;
 int MouseY=Point.y-Rect.top;
 if (MouseX>=0 && MouseY>=0 && MouseX<=(Rect.right-Rect.left)*5 && MouseY<=(Rect.bottom-Rect.top)*3)
 {
  int x=MouseX/(Rect.right-Rect.left);
  int y=MouseY/(Rect.bottom-Rect.top);
  int st=x+hPos+(y+vPos)*50;
  if (st<sKeyData.MaximumTexture)
  {
   WorkingTexture.TextureNo=st;
   InvalidateRect(hDlg,NULL,FALSE);
  }
 }
}
//------------------------------------------------------------------------------
void CDialog_SelectTexture::SaveTextureStruct(FILE *File,STexture Texture)
{
 fprintf(File,"%i ",Texture.TextureNo);
 fprintf(File,"%i ",Texture.OffsetX);
 fprintf(File,"%i ",Texture.OffsetY);
 fprintf(File,"%i ",Texture.ScaleX);
 fprintf(File,"%i ",Texture.ScaleY);
 fprintf(File,"%i ",Texture.FlipVertical);
 fprintf(File,"%i ",Texture.FlipHorizontal);
 fprintf(File,"%i ",Texture.Rotate);
}
STexture CDialog_SelectTexture::LoadTextureStruct(FILE *File)
{
 STexture Texture;
 Texture.TextureNo=(int)ReadNumber(File);
 Texture.OffsetX=(int)ReadNumber(File);
 Texture.OffsetY=(int)ReadNumber(File);
 Texture.ScaleX=(int)ReadNumber(File);
 Texture.ScaleY=(int)ReadNumber(File);
 Texture.FlipVertical=(int)ReadNumber(File);
 Texture.FlipHorizontal=(int)ReadNumber(File);
 Texture.Rotate=(int)ReadNumber(File);
 return(Texture);
}
int CDialog_SelectTexture::CompareTextureStruct(STexture Texture1,STexture Texture2)
{
 if (Texture1.TextureNo!=Texture2.TextureNo) return(0);
 return(1);
}
void CDialog_SelectTexture::CreateTextureImage(STexture Texture,unsigned char *Image)
{
 int tms=sKeyData.TextureMap[Texture.TextureNo].Size;
 float kx=(float)((float)tms/128.0);
 float ky=(float)((float)tms/128.0);
 float tmx=0,tmy=0;
 for(int x=0;x<128;x++,tmx+=kx)
 {
  tmy=0;
  for(int y=0;y<128;y++,tmy+=ky)
  {
   int offset=(x+(128-y-1)*128)*3;
   int tx=((int)(tmx+Texture.OffsetX))%tms;
   int ty=((int)(tmy+Texture.OffsetY))%tms;
   if (Texture.FlipVertical==1) tx=tms-tx-1;
   if (Texture.FlipHorizontal==1) ty=tms-ty-1;
   if (Texture.Rotate==1)
   {
    int reserv=tx;
    tx=ty;
    ty=reserv;
   }
   int offset1=tx*tms+ty;
   Image[offset+2]=sKeyData.TextureMap[Texture.TextureNo].R[offset1];
   Image[offset+1]=sKeyData.TextureMap[Texture.TextureNo].G[offset1];
   Image[offset]=sKeyData.TextureMap[Texture.TextureNo].B[offset1];
  }
 }
}
void CDialog_SelectTexture::CreateTextureCoord(STexture Texture,double *TX,double *TY)
{
 int tms=sKeyData.TextureMap[Texture.TextureNo].Size;
 int x=(int)((*(TX))*tms);
 int y=(int)((*(TY))*tms);
 x=x+(int)(Texture.OffsetX*((double)(Texture.ScaleX))/128.0);
 y=y+(int)(Texture.OffsetY*((double)(Texture.ScaleY))/128.0);
 if (Texture.FlipVertical==1) x=-x;
 if (Texture.FlipHorizontal==1) y=-y;
 if (Texture.Rotate==1)
 {
  int reserv=x;
  x=y;
  y=reserv;
  *(TX)=128.0*(double)(x)/((double)tms*(double)Texture.ScaleY);
  *(TY)=128.0*(double)(y)/((double)tms*(double)Texture.ScaleX);
 }
 else
 {
  *(TX)=128.0*(double)(x)/((double)tms*(double)Texture.ScaleX);
  *(TY)=128.0*(double)(y)/((double)tms*(double)Texture.ScaleY);
 }
}
void CDialog_SelectTexture::InitializeTextureStruct(STexture *Texture)
{
 Texture->ScaleX=128;
 Texture->ScaleY=128;
 Texture->OffsetX=0;
 Texture->OffsetY=0;
 Texture->FlipVertical=0;
 Texture->FlipHorizontal=0;
 Texture->TextureNo=0;
 Texture->Rotate=0;
}
void CDialog_SelectTexture::CopyTextureStruct(STexture *T1,STexture T2)
{
 T1->OffsetX=T2.OffsetX;
 T1->OffsetY=T2.OffsetY;
 T1->FlipVertical=T2.FlipVertical;
 T1->FlipHorizontal=T2.FlipHorizontal;
 T1->Rotate=T2.Rotate;
}
//------------------------------------------------------------------------------
STexture CDialog_SelectTexture::Activate(HWND hWnd,STexture Texture,int mode)
{
 Mode=mode;
 OldTexture=Texture;
 WorkingTexture=Texture;
 vPosMax=sKeyData.MaximumTexture/50-1;
 if (vPosMax<0) vPosMax=0;
 hPosMax=50-5;
 vPos=Texture.TextureNo/50;
 hPos=Texture.TextureNo-vPos*50;
 if (vPos>=vPosMax-1) vPos=vPosMax-1;
 if (vPos<0) vPos=0;
 if (hPos>=hPosMax-1) hPos=hPosMax-1;
 if (hPos<0) hPos=0;
 DialogBox(hProjectInstance,(LPSTR)1,hWnd,(DLGPROC)SELECTTEXTUREFORM_dlgProc);
 return(WorkingTexture);
}
 

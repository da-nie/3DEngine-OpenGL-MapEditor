#include "wc_menuform.h"

extern SKeyData sKeyData;//ключевая информация
extern HINSTANCE hProjectInstance;

CWnd_Menu cWnd_Menu;

//------------------------------------------------------------------------------
void MENUFORM_Register(void)
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
 wc.lpszClassName="cWnd_Menu";
 wc.lpfnWndProc=(WNDPROC)MENUFORM_wndProc;
 RegisterClass(&wc);
}
LONG WINAPI MENUFORM_wndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
 switch(msg)
 {
  case WM_CREATE:
  {
   cWnd_Menu.Create(hWnd,wParam,lParam);
   return(0);
  }
  case WM_DESTROY:
  {
   return(0);
  }
  case WM_COMMAND:
  {
   cWnd_Menu.Command(hWnd,wParam,lParam);
   return(0);
  }
 }
 return(DefWindowProc(hWnd,msg,wParam,lParam));
}
//------------------------------------------------------------------------------
void CWnd_Menu::Create(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 hWnd=hWnds;
 sKeyData.hWndMenu=hWnd;
 Static_Text1.Create(8,8,300,20,"Режим работы редактора карт",0,hWnd,hProjectInstance);
 Static_Text2.Create(8,28,300,20,"-",0,hWnd,hProjectInstance);
 Static_TextInfo[0].Create(8,58,300,170,"Всего секторов:",0,hWnd,hProjectInstance);
 Static_TextInfo[1].Create(188,58,300,50,"0",0,hWnd,hProjectInstance);
 Static_TextInfo[2].Create(8,78,300,170,"Всего сегментов:",0,hWnd,hProjectInstance);
 Static_TextInfo[3].Create(188,78,300,50,"0",0,hWnd,hProjectInstance);
 Static_TextInfo[4].Create(8,98,300,170,"Всего источников света:",0,hWnd,hProjectInstance);
 Static_TextInfo[5].Create(188,98,300,50,"0",0,hWnd,hProjectInstance);
  
 Static_TextInfo[6].Create(8,128,300,170,"Обычных секторов:",0,hWnd,hProjectInstance);
 Static_TextInfo[7].Create(188,128,300,50,"0",0,hWnd,hProjectInstance);
 Static_TextInfo[8].Create(8,148,300,170,"Обычных дверей:",0,hWnd,hProjectInstance);
 Static_TextInfo[9].Create(188,148,300,50,"0",0,hWnd,hProjectInstance);
 Static_TextInfo[10].Create(8,168,300,170,"Одноразовых дверей:",0,hWnd,hProjectInstance);
 Static_TextInfo[11].Create(188,168,300,50,"0",0,hWnd,hProjectInstance);
 Static_TextInfo[12].Create(8,188,300,170,"Запертых дверей:",0,hWnd,hProjectInstance);
 Static_TextInfo[13].Create(188,188,300,50,"0",0,hWnd,hProjectInstance);
 Static_TextInfo[14].Create(8,208,300,170,"Запирающихся дверей:",0,hWnd,hProjectInstance);
 Static_TextInfo[15].Create(188,208,300,50,"0",0,hWnd,hProjectInstance);
 Static_TextInfo[16].Create(8,228,300,170,"Обычных платформ:",0,hWnd,hProjectInstance);
 Static_TextInfo[17].Create(188,228,300,50,"0",0,hWnd,hProjectInstance);
 Static_TextInfo[18].Create(8,248,300,170,"Неактивных платформ:",0,hWnd,hProjectInstance);
 Static_TextInfo[19].Create(188,248,300,50,"0",0,hWnd,hProjectInstance);
 Static_TextInfo[20].Create(8,268,300,170,"Отключ. платформ:",0,hWnd,hProjectInstance);
 Static_TextInfo[21].Create(188,268,300,50,"0",0,hWnd,hProjectInstance);
 Static_TextInfo[22].Create(8,288,300,170,"Обычных мостиков:",0,hWnd,hProjectInstance);
 Static_TextInfo[23].Create(188,288,300,50,"0",0,hWnd,hProjectInstance);
 Static_TextInfo[24].Create(8,308,300,170,"Обычных телепортаторов:",0,hWnd,hProjectInstance);
 Static_TextInfo[25].Create(188,308,300,50,"0",0,hWnd,hProjectInstance);
}
void CWnd_Menu::Command(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 int id=LOWORD(wParam);
 sKeyData.MaximumPset=0;//всего точек в рисуемом блоке
 InvalidateRect(sKeyData.hWndMain,NULL,FALSE);
 sKeyData.SelectLine=-1;
 sKeyData.SelectLighting=-1;
 if (id==MENUFORM_MENU_CREATE_SSegment)
 {
  sKeyData.PrimaryMode=1;
  sKeyData.SecondaryMode=0;
  Static_Text2.SetText("Создание сегментов");
 }
 if (id==MENUFORM_MENU_CREATE_FRONTIER)
 {
  sKeyData.PrimaryMode=1;
  sKeyData.SecondaryMode=1;
  Static_Text2.SetText("Создание линий раздела");
 }
 if (id==MENUFORM_MENU_CREATE_SLighting)
 {
  sKeyData.PrimaryMode=3;
  sKeyData.SecondaryMode=0;
  Static_Text2.SetText("Создание источников света");
 }
 if (id==MENUFORM_MENU_CREATE_STARTPOS)
 {
  sKeyData.PrimaryMode=4;
  sKeyData.SecondaryMode=0;
  Static_Text2.SetText("Задание стартовой позиции");
 }
 if (id==MENUFORM_MENU_DELETE_SSegment)
 {
  sKeyData.PrimaryMode=6;
  sKeyData.SecondaryMode=0;
  Static_Text2.SetText("Удаление сегментов");
 }
 if (id==MENUFORM_MENU_DELETE_FRONTIER)
 {
  sKeyData.PrimaryMode=6;
  sKeyData.SecondaryMode=1;
  Static_Text2.SetText("Удаление линий раздела");
 }
 if (id==MENUFORM_MENU_DELETE_LINE)
 {
  sKeyData.PrimaryMode=6;
  sKeyData.SecondaryMode=2;
  Static_Text2.SetText("Удаление любых линий");
 }
 if (id==MENUFORM_MENU_DELETE_SECTOR)
 {
  sKeyData.PrimaryMode=7;
  sKeyData.SecondaryMode=0;
  Static_Text2.SetText("Удаление секторов");
 }
 if (id==MENUFORM_MENU_DELETE_SLighting)
 {
  sKeyData.PrimaryMode=8;
  sKeyData.SecondaryMode=0;
  Static_Text2.SetText("Удаление источников света");
 }
 if (id==MENUFORM_MENU_MODIFYCATION_SSegment)
 {
  sKeyData.PrimaryMode=9;
  sKeyData.SecondaryMode=0;
  Static_Text2.SetText("Модификация сегментов");
 }
 if (id==MENUFORM_MENU_MODIFYCATION_FRONTIER)
 {
  sKeyData.PrimaryMode=9;
  sKeyData.SecondaryMode=1;
  Static_Text2.SetText("Модификация линии раздела");
 }
 if (id==MENUFORM_MENU_MODIFYCATION_SECTOR)
 {
  sKeyData.PrimaryMode=10;
  sKeyData.SecondaryMode=0;
  Static_Text2.SetText("Модификация секторов");
 }
 if (id==MENUFORM_MENU_MODIFYCATION_SLighting)
 {
  sKeyData.PrimaryMode=11;
  sKeyData.SecondaryMode=0;
  Static_Text2.SetText("Модификация источников света");
 }
 if (id==MENUFORM_MENU_FIGURE_CORRECTPOLYGON)
 {
  sKeyData.PrimaryMode=5;
  sKeyData.SecondaryMode=0;
  Static_Text2.SetText("Создание многоугольника");
 }
 if (id==MENUFORM_MENU_FIGURE_STAR)
 {
  sKeyData.PrimaryMode=5;
  sKeyData.SecondaryMode=1;
  Static_Text2.SetText("Создание звезды");
 }
 if (id==MENUFORM_MENU_SECTOR_SIMPLYSECTOR)
 {
  sKeyData.PrimaryMode=2;
  sKeyData.SecondaryMode=0;
  Static_Text2.SetText("Создание обычного сектора");
 }
 if (id==MENUFORM_MENU_SECTOR_SIMPLYDOOR)
 {
  sKeyData.PrimaryMode=2;
  sKeyData.SecondaryMode=1;
  Static_Text2.SetText("Создание обычной двери");
 }
 if (id==MENUFORM_MENU_SECTOR_DISPOSABLEDOOR)
 {
  sKeyData.PrimaryMode=2;
  sKeyData.SecondaryMode=2;
  Static_Text2.SetText("Создание одноразовой двери");
 }
 if (id==MENUFORM_MENU_SECTOR_CLOSEDDOOR)
 {
  sKeyData.PrimaryMode=2;
  sKeyData.SecondaryMode=3;
  Static_Text2.SetText("Создание запертой двери");
 }
 if (id==MENUFORM_MENU_SECTOR_AUTOCLOSEDDOOR)
 {
  sKeyData.PrimaryMode=2;
  sKeyData.SecondaryMode=4;
  Static_Text2.SetText("Создание закрывающейся двери");
 }
 if (id==MENUFORM_MENU_SECTOR_SIMPLYPLATCWnd_Form)
 {
  sKeyData.PrimaryMode=2;
  sKeyData.SecondaryMode=5;
  Static_Text2.SetText("Создание обычной платформы");
 }
 if (id==MENUFORM_MENU_SECTOR_INACTIVEPLATCWnd_Form)
 {
  sKeyData.PrimaryMode=2;
  sKeyData.SecondaryMode=6;
  Static_Text2.SetText("Создание неактивной платформы");
 }
 if (id==MENUFORM_MENU_SECTOR_DISCONNECTEDPLATCWnd_Form)
 {
  sKeyData.PrimaryMode=2;
  sKeyData.SecondaryMode=7;
  Static_Text2.SetText("Созд. отключающейся платформы");
 }
 if (id==MENUFORM_MENU_SECTOR_SIMPLYBRIDGE)
 {
  sKeyData.PrimaryMode=2;
  sKeyData.SecondaryMode=8;
  Static_Text2.SetText("Создание обычного мостика");
 }
 if (id==MENUFORM_MENU_SECTOR_SIMPLYTELEPORT)
 {
  sKeyData.PrimaryMode=2;
  sKeyData.SecondaryMode=9;
  Static_Text2.SetText("Создание обычного телепортатора");
 }
}
//------------------------------------------------------------------------------
void CWnd_Menu::UpDate(void)
{
 sKeyData.MaximumNumberOfAllSector=0;
 sKeyData.MaximumNumberOfAllSector+=sKeyData.MaximumNumberOfSimplySector;
 sKeyData.MaximumNumberOfAllSector+=sKeyData.MaximumNumberOfSimplyDoor;
 sKeyData.MaximumNumberOfAllSector+=sKeyData.MaximumNumberOfDisposableDoor;
 sKeyData.MaximumNumberOfAllSector+=sKeyData.MaximumNumberOfClosedDoor;
 sKeyData.MaximumNumberOfAllSector+=sKeyData.MaximumNumberOfAutoClosedDoor;
 sKeyData.MaximumNumberOfAllSector+=sKeyData.MaximumNumberOfSimplyPlatform;
 sKeyData.MaximumNumberOfAllSector+=sKeyData.MaximumNumberOfInactivePlatform;
 sKeyData.MaximumNumberOfAllSector+=sKeyData.MaximumNumberOfDisconnectPlatform;
 sKeyData.MaximumNumberOfAllSector+=sKeyData.MaximumNumberOfSimplyBridge;
 sKeyData.MaximumNumberOfAllSector+=sKeyData.MaximumNumberOfSimplyTeleport;
 char string[255];
 itoa(sKeyData.MaximumNumberOfAllSector,string,10);
 Static_TextInfo[1].SetText(string);
 itoa(sKeyData.MaximumNumberOfLine,string,10);
 Static_TextInfo[3].SetText(string);
 itoa(sKeyData.MaximumNumberOfLighting,string,10);
 Static_TextInfo[5].SetText(string);
 itoa(sKeyData.MaximumNumberOfSimplySector,string,10);
 Static_TextInfo[7].SetText(string);
 itoa(sKeyData.MaximumNumberOfSimplyDoor,string,10);
 Static_TextInfo[9].SetText(string);
 itoa(sKeyData.MaximumNumberOfDisposableDoor,string,10);
 Static_TextInfo[11].SetText(string);
 itoa(sKeyData.MaximumNumberOfClosedDoor,string,10);
 Static_TextInfo[13].SetText(string);
 itoa(sKeyData.MaximumNumberOfAutoClosedDoor,string,10);
 Static_TextInfo[15].SetText(string);
 itoa(sKeyData.MaximumNumberOfSimplyPlatform,string,10);
 Static_TextInfo[17].SetText(string);
 itoa(sKeyData.MaximumNumberOfInactivePlatform,string,10);
 Static_TextInfo[19].SetText(string);
 itoa(sKeyData.MaximumNumberOfDisconnectPlatform,string,10);
 Static_TextInfo[21].SetText(string);
 itoa(sKeyData.MaximumNumberOfSimplyBridge,string,10);
 Static_TextInfo[23].SetText(string);
 itoa(sKeyData.MaximumNumberOfSimplyTeleport,string,10);
 Static_TextInfo[25].SetText(string);
}
 


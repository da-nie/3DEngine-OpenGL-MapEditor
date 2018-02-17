#include "wc_menuform.h"

extern KEY_DATA KeyData;//ключевая информация
extern HINSTANCE hProjectInstance;

MENUFORM MenuForm;

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
 wc.lpszClassName="MenuForm";
 wc.lpfnWndProc=(WNDPROC)MENUFORM_wndProc;
 RegisterClass(&wc);
}
LONG WINAPI MENUFORM_wndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
 switch(msg)
 {
  case WM_CREATE:
  {
   MenuForm.Create(hWnd,wParam,lParam);
   return(0);
  }
  case WM_DESTROY:
  {
   return(0);
  }
  case WM_COMMAND:
  {
   MenuForm.Command(hWnd,wParam,lParam);
   return(0);
  }
 }
 return(DefWindowProc(hWnd,msg,wParam,lParam));
}
//------------------------------------------------------------------------------
void MENUFORM::Create(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 hWnd=hWnds;
 KeyData.hWndMenu=hWnd;
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
void MENUFORM::Command(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 int id=LOWORD(wParam);
 KeyData.MaximumPset=0;//всего точек в рисуемом блоке
 InvalidateRect(KeyData.hWndMain,NULL,FALSE);
 KeyData.SelectLine=-1;
 KeyData.SelectLighting=-1;
 if (id==MENUFORM_MENU_CREATE_SEGMENT)
 {
  KeyData.PrimaryMode=1;
  KeyData.SecondaryMode=0;
  Static_Text2.SetText("Создание сегментов");
 }
 if (id==MENUFORM_MENU_CREATE_FRONTIER)
 {
  KeyData.PrimaryMode=1;
  KeyData.SecondaryMode=1;
  Static_Text2.SetText("Создание линий раздела");
 }
 if (id==MENUFORM_MENU_CREATE_LIGHTING)
 {
  KeyData.PrimaryMode=3;
  KeyData.SecondaryMode=0;
  Static_Text2.SetText("Создание источников света");
 }
 if (id==MENUFORM_MENU_CREATE_STARTPOS)
 {
  KeyData.PrimaryMode=4;
  KeyData.SecondaryMode=0;
  Static_Text2.SetText("Задание стартовой позиции");
 }
 if (id==MENUFORM_MENU_DELETE_SEGMENT)
 {
  KeyData.PrimaryMode=6;
  KeyData.SecondaryMode=0;
  Static_Text2.SetText("Удаление сегментов");
 }
 if (id==MENUFORM_MENU_DELETE_FRONTIER)
 {
  KeyData.PrimaryMode=6;
  KeyData.SecondaryMode=1;
  Static_Text2.SetText("Удаление линий раздела");
 }
 if (id==MENUFORM_MENU_DELETE_LINE)
 {
  KeyData.PrimaryMode=6;
  KeyData.SecondaryMode=2;
  Static_Text2.SetText("Удаление любых линий");
 }
 if (id==MENUFORM_MENU_DELETE_SECTOR)
 {
  KeyData.PrimaryMode=7;
  KeyData.SecondaryMode=0;
  Static_Text2.SetText("Удаление секторов");
 }
 if (id==MENUFORM_MENU_DELETE_LIGHTING)
 {
  KeyData.PrimaryMode=8;
  KeyData.SecondaryMode=0;
  Static_Text2.SetText("Удаление источников света");
 }
 if (id==MENUFORM_MENU_MODIFYCATION_SEGMENT)
 {
  KeyData.PrimaryMode=9;
  KeyData.SecondaryMode=0;
  Static_Text2.SetText("Модификация сегментов");
 }
 if (id==MENUFORM_MENU_MODIFYCATION_FRONTIER)
 {
  KeyData.PrimaryMode=9;
  KeyData.SecondaryMode=1;
  Static_Text2.SetText("Модификация линии раздела");
 }
 if (id==MENUFORM_MENU_MODIFYCATION_SECTOR)
 {
  KeyData.PrimaryMode=10;
  KeyData.SecondaryMode=0;
  Static_Text2.SetText("Модификация секторов");
 }
 if (id==MENUFORM_MENU_MODIFYCATION_LIGHTING)
 {
  KeyData.PrimaryMode=11;
  KeyData.SecondaryMode=0;
  Static_Text2.SetText("Модификация источников света");
 }
 if (id==MENUFORM_MENU_FIGURE_CORRECTPOLYGON)
 {
  KeyData.PrimaryMode=5;
  KeyData.SecondaryMode=0;
  Static_Text2.SetText("Создание многоугольника");
 }
 if (id==MENUFORM_MENU_FIGURE_STAR)
 {
  KeyData.PrimaryMode=5;
  KeyData.SecondaryMode=1;
  Static_Text2.SetText("Создание звезды");
 }
 if (id==MENUFORM_MENU_SECTOR_SIMPLYSECTOR)
 {
  KeyData.PrimaryMode=2;
  KeyData.SecondaryMode=0;
  Static_Text2.SetText("Создание обычного сектора");
 }
 if (id==MENUFORM_MENU_SECTOR_SIMPLYDOOR)
 {
  KeyData.PrimaryMode=2;
  KeyData.SecondaryMode=1;
  Static_Text2.SetText("Создание обычной двери");
 }
 if (id==MENUFORM_MENU_SECTOR_DISPOSABLEDOOR)
 {
  KeyData.PrimaryMode=2;
  KeyData.SecondaryMode=2;
  Static_Text2.SetText("Создание одноразовой двери");
 }
 if (id==MENUFORM_MENU_SECTOR_CLOSEDDOOR)
 {
  KeyData.PrimaryMode=2;
  KeyData.SecondaryMode=3;
  Static_Text2.SetText("Создание запертой двери");
 }
 if (id==MENUFORM_MENU_SECTOR_AUTOCLOSEDDOOR)
 {
  KeyData.PrimaryMode=2;
  KeyData.SecondaryMode=4;
  Static_Text2.SetText("Создание закрывающейся двери");
 }
 if (id==MENUFORM_MENU_SECTOR_SIMPLYPLATFORM)
 {
  KeyData.PrimaryMode=2;
  KeyData.SecondaryMode=5;
  Static_Text2.SetText("Создание обычной платформы");
 }
 if (id==MENUFORM_MENU_SECTOR_INACTIVEPLATFORM)
 {
  KeyData.PrimaryMode=2;
  KeyData.SecondaryMode=6;
  Static_Text2.SetText("Создание неактивной платформы");
 }
 if (id==MENUFORM_MENU_SECTOR_DISCONNECTEDPLATFORM)
 {
  KeyData.PrimaryMode=2;
  KeyData.SecondaryMode=7;
  Static_Text2.SetText("Созд. отключающейся платформы");
 }
 if (id==MENUFORM_MENU_SECTOR_SIMPLYBRIDGE)
 {
  KeyData.PrimaryMode=2;
  KeyData.SecondaryMode=8;
  Static_Text2.SetText("Создание обычного мостика");
 }
 if (id==MENUFORM_MENU_SECTOR_SIMPLYTELEPORT)
 {
  KeyData.PrimaryMode=2;
  KeyData.SecondaryMode=9;
  Static_Text2.SetText("Создание обычного телепортатора");
 }
}
//------------------------------------------------------------------------------
void MENUFORM::UpDate(void)
{
 KeyData.MaximumNumberOfAllSector=0;
 KeyData.MaximumNumberOfAllSector+=KeyData.MaximumNumberOfSimplySector;
 KeyData.MaximumNumberOfAllSector+=KeyData.MaximumNumberOfSimplyDoor;
 KeyData.MaximumNumberOfAllSector+=KeyData.MaximumNumberOfDisposableDoor;
 KeyData.MaximumNumberOfAllSector+=KeyData.MaximumNumberOfClosedDoor;
 KeyData.MaximumNumberOfAllSector+=KeyData.MaximumNumberOfAutoClosedDoor;
 KeyData.MaximumNumberOfAllSector+=KeyData.MaximumNumberOfSimplyPlatform;
 KeyData.MaximumNumberOfAllSector+=KeyData.MaximumNumberOfInactivePlatform;
 KeyData.MaximumNumberOfAllSector+=KeyData.MaximumNumberOfDisconnectPlatform;
 KeyData.MaximumNumberOfAllSector+=KeyData.MaximumNumberOfSimplyBridge;
 KeyData.MaximumNumberOfAllSector+=KeyData.MaximumNumberOfSimplyTeleport;
 char string[255];
 itoa(KeyData.MaximumNumberOfAllSector,string,10);
 Static_TextInfo[1].SetText(string);
 itoa(KeyData.MaximumNumberOfLine,string,10);
 Static_TextInfo[3].SetText(string);
 itoa(KeyData.MaximumNumberOfLighting,string,10);
 Static_TextInfo[5].SetText(string);
 itoa(KeyData.MaximumNumberOfSimplySector,string,10);
 Static_TextInfo[7].SetText(string);
 itoa(KeyData.MaximumNumberOfSimplyDoor,string,10);
 Static_TextInfo[9].SetText(string);
 itoa(KeyData.MaximumNumberOfDisposableDoor,string,10);
 Static_TextInfo[11].SetText(string);
 itoa(KeyData.MaximumNumberOfClosedDoor,string,10);
 Static_TextInfo[13].SetText(string);
 itoa(KeyData.MaximumNumberOfAutoClosedDoor,string,10);
 Static_TextInfo[15].SetText(string);
 itoa(KeyData.MaximumNumberOfSimplyPlatform,string,10);
 Static_TextInfo[17].SetText(string);
 itoa(KeyData.MaximumNumberOfInactivePlatform,string,10);
 Static_TextInfo[19].SetText(string);
 itoa(KeyData.MaximumNumberOfDisconnectPlatform,string,10);
 Static_TextInfo[21].SetText(string);
 itoa(KeyData.MaximumNumberOfSimplyBridge,string,10);
 Static_TextInfo[23].SetText(string);
 itoa(KeyData.MaximumNumberOfSimplyTeleport,string,10);
 Static_TextInfo[25].SetText(string);
}
 


#include "wc_form.h"

 
extern SETUP SetUp;//настройки редактора
extern KEY_DATA KeyData;//ключевая информация
extern HINSTANCE hProjectInstance;

extern CREATELIGHTINGFORM CreateLightingForm;
extern CREATESIMPLYSECTORFORM CreateSimplySectorForm;
extern CREATESIMPLYDOORFORM CreateSimplyDoorForm;
extern CREATESEGMENTFORM CreateSegmentForm;
extern STARTPOSFORM StartPosForm;
extern CREATEPOLYGONFORM CreatePolygonForm;
extern CREATESTARFORM CreateStarForm;
extern MENUFORM MenuForm;
extern PROGRESS Progress;
extern SETTINGRENDERFORM SettingRenderForm;

extern unsigned char VideoBuffer[500*500*3];//поле для рисования

FORM Form;
//------------------------------------------------------------------------------
void FORM_Register(void)
{
 WNDCLASS wc;
 wc.style=CS_HREDRAW|CS_VREDRAW;
 wc.cbClsExtra=0;
 wc.cbWndExtra=0;
 wc.hInstance=hProjectInstance;
 wc.hIcon=LoadIcon(hProjectInstance,(LPSTR)1);
 wc.hCursor=LoadCursor(NULL,IDC_ARROW);
 wc.hbrBackground=(HBRUSH)(COLOR_WINDOW-1);
 wc.lpszMenuName=NULL;
 wc.lpszClassName="Form";
 wc.lpfnWndProc=(WNDPROC)FORM_wndProc;
 RegisterClass(&wc);
}
LONG WINAPI FORM_wndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
 switch(msg)
 {
  case WM_CREATE:
  {
   Form.Create(hWnd,wParam,lParam);
   return(0);
  }
  case WM_DESTROY:
  {
   Form.Destroy(hWnd,wParam,lParam);
   PostQuitMessage(0);
   return(0);
  }
  case WM_PAINT:
  {
   Form.Paint(hWnd,wParam,lParam);
   return(0);
  }
  case WM_RBUTTONDOWN:
  {
   Form.RButtonDown(hWnd,wParam,lParam);
   return(0);
  }
  case WM_RBUTTONUP:
  {
   Form.RButtonUp(hWnd,wParam,lParam);
   return(0);
  }
  case WM_MOUSEMOVE:
  {
   Form.MouseMove(hWnd,wParam,lParam);
   return(0);
  }
  case WM_TIMER:
  {
   Form.Timer(hWnd,wParam,lParam);
   return(0);
  }
  case WM_LBUTTONUP:
  {
   Form.LButtonUp(hWnd,wParam,lParam);
   return(0);
  }
  case WM_COMMAND:
  {
   Form.Command(hWnd,wParam,lParam);
   return(0);
  }
  case WM_KEYDOWN:
  {
   Form.KeyDown(hWnd,wParam,lParam);
   return(0);
  }
 }
 return(DefWindowProc(hWnd,msg,wParam,lParam));
}
//------------------------------------------------------------------------------
void FORM::Create(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 hWnd=hWnds;
 KeyData.hWndMain=hWnd;
 Initialize();//инициализируем редактор
 LoadTexture("texture.pak");//загружаем текстуры
 HMENU hMainMenu=GetMenu(hWnd);
 hSettingMenu=GetSubMenu(hMainMenu,1);
 FPRS.Create(hWnd);
 FPRS_1.Create(hWnd);
 Static_Form.Create(510,4,280,32,"",WS_BORDER,hWnd,hProjectInstance);
 Static_Text1.Create(520,8,20,24,"X:",0,hWnd,hProjectInstance);
 Static_Text2.Create(540,8,100,24,"0",0,hWnd,hProjectInstance);
 Static_Text3.Create(660,8,20,24,"Y:",0,hWnd,hProjectInstance);
 Static_Text4.Create(680,8,100,24,"0",0,hWnd,hProjectInstance);
 Button_ExecuteDialog.Create(520,460,270,24,"Изменить параметры линий",FORM_BUTTON_EXECUTE_DIALOG,0,hWnd,hProjectInstance);
 Button_Reset.Create(520,490,270,24,"Сбросить точки",FORM_BUTTON_RESET,0,hWnd,hProjectInstance);
 Button_Reset.Disable();
 CheckBox_ShowDialog.Create(520,430,270,25,"Вызывать диалог настройки линий",FORM_CHECKBOX_SHOWDIALOG,WS_BORDER,hWnd,hProjectInstance);
 CheckBox_ShowDialog.SetStateOn();
 OldTimer=SetTimer(hWnd,1,1,NULL);
 //создаём панель управления
 HMENU hControlMenu=LoadMenu(hProjectInstance,(LPSTR)IDM_MENU2);
 CreateWindow("MenuForm","Панель управления",WS_VISIBLE|WS_CAPTION|WS_POPUP,525,80,260,390,hWnd,hControlMenu,hProjectInstance,NULL);
}
void FORM::Destroy(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 KillTimer(hWnd,OldTimer);
 if (KeyData.MaximumTexture>0)
 {
  for(int n=0;n<KeyData.MaximumTexture;n++)
  {
   delete(KeyData.TextureMap[n].R);
   delete(KeyData.TextureMap[n].G);
   delete(KeyData.TextureMap[n].B);
  }
  delete(KeyData.TextureMap);
 }
}
void FORM::Paint(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 BITMAPINFOHEADER bmih;
 bmih.biSize=sizeof(BITMAPINFOHEADER);
 bmih.biWidth=500;
 bmih.biHeight=500;
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
 ClearVideoBuffer();
 //выводим линии сетки
 for(int x=0;x<50;x++)
 {
  if ((x+xLeftMap)%8==0) DrawLine(x*10,0,x*10,500,255,255,255);
  else DrawLine(x*10,0,x*10,500,127,127,127);
 }
 for(int y=0;y<50;y++)
 {
  if ((y+yTopMap)%8==0) DrawLine(0,y*10,500,y*10,255,255,255);
  else DrawLine(0,y*10,500,y*10,127,127,127);
 }
 //рисуем все имеющиеся источники света
 if (SetUp.ShowLighting==1) CreateLightingForm.DrawAllLighting(xLeftMap,yTopMap);
 //рисуем все имеющиеся сектора:
 if (SetUp.ShowSector==1)
 {
  //работа с секторами
  //обычные сектора
  CreateSimplySectorForm.DrawAllSector(xLeftMap,yTopMap);
  //обычные двери
  CreateSimplyDoorForm.DrawAllSector(xLeftMap,yTopMap);
  //работа с секторами
 }
 //рисуем все имеющиеся сегменты
 if (SetUp.ShowSegment==1) CreateSegmentForm.DrawAllSegment(xLeftMap,yTopMap);
 //рисуем стартовую позицию
 StartPosForm.DrawStartPos(xLeftMap,yTopMap);
 //рисуем текущий создающийся объект (если он есть)
 for(int n=0;n<KeyData.MaximumPset-1;n++)
 {
  DrawLine((KeyData.X[n]-xLeftMap)*10,(KeyData.Y[n]-yTopMap)*10,(KeyData.X[n+1]-xLeftMap)*10,(KeyData.Y[n+1]-yTopMap)*10,64,255,255);
 }
 if (KeyData.MaximumPset>0) Button_Reset.Enable();//если есть точки, то кнопка активна, иначе - нет
 else Button_Reset.Disable();
 //выводим на экран то что нарисовали
 PAINTSTRUCT ps;
 HDC hdc;
 hdc=BeginPaint(hWnd,&ps);
 StretchDIBits(hdc,8,8,500,500,0,0,500,500,VideoBuffer,&info,DIB_RGB_COLORS,SRCCOPY);
 EndPaint(hWnd,&ps);
}
void FORM::RButtonDown(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 if (!(MouseXW>=0 && MouseXW<500 && MouseYW>=0 && MouseYW<500)) return;
 MapMove=1;
 OldMouseX=MouseX;
 OldMouseY=MouseY;
 ShowCursor(FALSE);
 RECT c_rect;
 RECT w_rect;
 RECT a_rect;
 GetClientRect(hWnd,&c_rect);
 GetWindowRect(hWnd,&w_rect);
 a_rect=c_rect;
 AdjustWindowRectEx(&a_rect,WS_MINIMIZEBOX|WS_SYSMENU,TRUE,0);
 c_rect.left=w_rect.left+2*(c_rect.left-a_rect.left)+10;
 c_rect.top=w_rect.top+2*(c_rect.top-a_rect.top)+10;
 c_rect.right=c_rect.left+500;
 c_rect.bottom=c_rect.top+500;
 ClipCursor(&c_rect);
}
void FORM::RButtonUp(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 if (MapMove==1)
 {
  ClipCursor(NULL);
  ShowCursor(TRUE);
  MapMove=0;
 }
}
void FORM::MouseMove(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 DWORD xyPos=GetMessagePos();
 POINT Point;
 Point.x=LOWORD(xyPos);
 Point.y=HIWORD(xyPos);
 MouseX=Point.x;
 MouseY=Point.y;
 ScreenToClient(hWnd,&Point);
 MouseXW=Point.x-8;
 MouseYW=Point.y-8;
 Static_Text2.SetText("-");
 Static_Text4.SetText("-");
 if (MouseXW>=0 && MouseXW<=499 && MouseYW>=0 && MouseYW<=499)
 {
  float x=(float)(MouseXW/10.0);
  float y=(float)(MouseYW/10.0);
  float minlen=1000;
  for(float xn=(float)((int)(x)-2);xn<=(float)((int)(x)+2);xn++)
  for(float yn=(float)((int)(y)-2);yn<=(float)((int)(y)+2);yn++)
  {
   if (xn<0 || yn<0) continue;
   float len=(float)(sqrt((xn-x)*(xn-x)+(yn-y)*(yn-y)));
   if (len<=minlen)
   {
    minlen=len;
    MouseXS=(int)(xn+xLeftMap);
    MouseYS=(int)(yn+yTopMap);
   }
  }
  if (MapMove==0)
  {
   char string[255];
   itoa(MouseXS,string,10);
   Static_Text2.SetText(string);
   itoa(MouseYS,string,10);
   Static_Text4.SetText(string);
  }
 }
 if (KeyData.MaximumPset>0 && MapMove==0)
 {
  KeyData.X[KeyData.MaximumPset-1]=MouseXS;
  KeyData.Y[KeyData.MaximumPset-1]=MouseYS;
  InvalidateRect(hWnd,NULL,FALSE);
 }
}
void FORM::Timer(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 if (MapMove==1)
 {
  int dx=(MouseX-OldMouseX)/20;
  int dy=(MouseY-OldMouseY)/20;
  xLeftMap+=dx;
  yTopMap+=dy;
  if (xLeftMap<0) xLeftMap=0;
  if (yTopMap<0) yTopMap=0;
  if (xLeftMap>1000000) xLeftMap=1000000;
  if (yTopMap>1000000) yTopMap=1000000;
  SetCursorPos(OldMouseX,OldMouseY);
  if (dx!=0 || dy!=0) InvalidateRect(hWnd,NULL,FALSE);
 }
}
void FORM::LButtonUp(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 //-----------------------------------------------------------------------------
 //РАБОТА С СЕГМЕНТАМИ
 //-----------------------------------------------------------------------------
 if (KeyData.PrimaryMode==1)//создаётся сегмент или линия раздела
 {
  if (KeyData.MaximumPset==0)//если мы ставим первую точку линии
  {
   KeyData.X[0]=MouseXS;
   KeyData.Y[0]=MouseYS;
   KeyData.X[1]=MouseXS;
   KeyData.Y[1]=MouseYS;
   KeyData.MaximumPset=2;
  }
  else// если мы дорисовали линию, её нужно сохранить
  {
   if (KeyData.X[0]==KeyData.X[1] && KeyData.Y[0]==KeyData.Y[1])
   {
    MessageBox(hWnd,"Сегмент имеет нулевую длину и создан не будет.","Предупреждение",MB_OK);
    return;
   }
   if (SetUp.ShowSegmentCreateDialog==1)
   {
    if (KeyData.SecondaryMode==0) CreateSegmentForm.CreateNewSegment(0);
    if (KeyData.SecondaryMode==1) CreateSegmentForm.CreateNewSegment(1);
   }
   else
   {
    if (KeyData.SecondaryMode==0) CreateSegmentForm.CreateSegment(0);
    if (KeyData.SecondaryMode==1) CreateSegmentForm.CreateSegment(1);
   }
  }
 }
 //удаление сегментов
 if (KeyData.PrimaryMode==6)
 {
  if (KeyData.SecondaryMode==0) GetSelectLine(MouseXW,MouseYW,0);
  if (KeyData.SecondaryMode==1) GetSelectLine(MouseXW,MouseYW,1);
  if (KeyData.SecondaryMode==2) GetSelectLine(MouseXW,MouseYW,2);
 }
 //модификация сегмента
 if (KeyData.PrimaryMode==9)
 {
  if (KeyData.SecondaryMode==0) GetSelectLine(MouseXW,MouseYW,0);
  if (KeyData.SecondaryMode==1) GetSelectLine(MouseXW,MouseYW,1);
 }
 //-----------------------------------------------------------------------------
 //РАБОТА СО СТАНДАРТНЫМИ ФИГУРАМИ
 //-----------------------------------------------------------------------------
 if (KeyData.PrimaryMode==5 && KeyData.SecondaryMode==0)//создание правильного многоугольника
 {
  CreatePolygonForm.Activate(MouseXS,MouseYS);
 }
 if (KeyData.PrimaryMode==5 && KeyData.SecondaryMode==1)//создание звезды
 {
  CreateStarForm.Activate(MouseXS,MouseYS);
 }
 //-----------------------------------------------------------------------------
 //РАБОТА С ИСТОЧНИКАМИ СВЕТА
 //-----------------------------------------------------------------------------
 if (KeyData.PrimaryMode==3)//создание источника света
 {
  CreateLightingForm.CreateNewLighting(MouseXS,MouseYS);
 }
 if (KeyData.PrimaryMode==8)//удаление источника света
 {
  GetSelectLighting(MouseXW,MouseYW);
 }
 if (KeyData.PrimaryMode==11)//модификация источника света
 {
  GetSelectLighting(MouseXW,MouseYW);
 }
 //-----------------------------------------------------------------------------
 //РАБОТА С СТАРТОВОЙ ПОЗИЦИЕЙ
 //-----------------------------------------------------------------------------
 if (KeyData.PrimaryMode==4)
 {
  StartPosForm.Activate(MouseXS,MouseYS);
 }
 //-----------------------------------------------------------------------------
 //РАБОТА С СЕКТОРАМИ
 //-----------------------------------------------------------------------------
 if (KeyData.PrimaryMode==2)//создаётся сектор
 {
  if (KeyData.MaximumPset==0)//если мы ставим первую точку сектора
  {
   KeyData.X[0]=MouseXS;
   KeyData.Y[0]=MouseYS;
   KeyData.X[1]=MouseXS;
   KeyData.Y[1]=MouseYS;
   KeyData.MaximumPset=2;
  }
  else// если мы ставим не первую точку сектора
  {
   if (KeyData.X[0]==MouseXS && KeyData.Y[0]==MouseYS)//мы замкнули контур, значит сектор готов
   {
    //проверим сектор на выпуклость
    if (SectorGamber()==0)//сектор не выпуклый
    {
     MessageBox(hWnd,"Сектор не является выпуклым многоугольником !","Ошибка",MB_OK);
     KeyData.MaximumPset=0;
    }
    else//сектор выпуклый, можно его добавить в набор
    {
     //работа с секторами
     if (KeyData.SecondaryMode==0) CreateSimplySectorForm.CreateNewSector();
     if (KeyData.SecondaryMode==1) CreateSimplyDoorForm.CreateNewSector();
     //работа с секторами
    }
   }
   else//иначе просто добавляем точку
   {
    if (KeyData.X[KeyData.MaximumPset-2]==MouseXS && KeyData.Y[KeyData.MaximumPset-2]==MouseYS)
    {
     MessageBox(hWnd,"Линия имеет нулевую длину и не будет занесена в список.","Предупреждение",MB_OK);
     return;
    }
    KeyData.X[KeyData.MaximumPset-1]=MouseXS;
    KeyData.Y[KeyData.MaximumPset-1]=MouseYS;
    KeyData.X[KeyData.MaximumPset]=MouseXS;
    KeyData.Y[KeyData.MaximumPset]=MouseYS;
    KeyData.MaximumPset++;
   }
  }
 }
 //удаление секторов
 if (KeyData.PrimaryMode==7)
 {
  GetSelectSector(MouseXW,MouseYW);
 }
 //модификация секторов
 if (KeyData.PrimaryMode==10)
 {
  GetSelectSector(MouseXW,MouseYW);
 }
 InvalidateRect(hWnd,NULL,FALSE);
}
void FORM::Command(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 int id=LOWORD(wParam);
 if (id==FORM_BUTTON_RESET)
 {
  KeyData.MaximumPset=0;
  InvalidateRect(hWnd,NULL,FALSE);
 }
 if (id==FORM_BUTTON_EXECUTE_DIALOG)
 {
  EnableWindow(KeyData.hWndMenu,FALSE);
  CreateSegmentForm.ChangeParameters();
  EnableWindow(KeyData.hWndMenu,TRUE);
 }
 if (id==FORM_MENU_FILE_EXIT)
 {
  int res=MessageBox(hWnd,"Вы хотите выйти ?","Подтверждение действия",MB_YESNO|MB_ICONWARNING|MB_DEFBUTTON2);
  if (res==IDYES) DestroyWindow(hWnd);
 }
 if (id==FORM_CHECKBOX_SHOWDIALOG)
 {
  if (SetUp.ShowSegmentCreateDialog==0)
  {
   CheckBox_ShowDialog.SetStateOn();
   SetUp.ShowSegmentCreateDialog=1;
  }
  else
  {
   CheckBox_ShowDialog.SetStateOff();
   SetUp.ShowSegmentCreateDialog=0;
  }
 }
 //------------------------------------------------------------------------------
 //Обработка меню File
 //------------------------------------------------------------------------------
 if (id==FORM_MENU_FILE_SAVEMAP)//сохранение карты
 {
  if (FPRS.StartSave("Сохранение карты","*.map\0*.map\0*.*\0*.*\0")) SaveMap(FPRS.FileName);
 }
 if (id==FORM_MENU_FILE_LOADMAP)//загрузка карты
 {
  if (FPRS.StartOpen("Загрузка карты","*.map\0*.map\0*.*\0*.*\0")) LoadMap(FPRS.FileName);
 }
 if (id==FORM_MENU_FILE_CLEARMAP)//очистка поля
 {
  int res=MessageBox(hWnd,"Очистить поле ?","Подтверждение действия",MB_YESNO|MB_DEFBUTTON2|MB_ICONWARNING);
  if (res==IDYES)
  {
   Initialize();
   CreateLightingForm.Initialize();
   CreatePolygonForm.Initialize();
   StartPosForm.Initialize();
   CreateSegmentForm.Initialize();
   //работа с секторами
   CreateSimplySectorForm.Initialize();
   CreateSimplyDoorForm.Initialize();
   //работа с секторами
   MenuForm.UpDate();
   InvalidateRect(hWnd,NULL,FALSE);
  }
 }
 if (id==FORM_MENU_FILE_CREATESTAGE)//создание сцены
 {
  if (FPRS_1.StartSave("Создание сцены","*.stg\0*.stg\0"))
  {
   EnableWindow(KeyData.hWndMain,FALSE);
   EnableWindow(KeyData.hWndMenu,FALSE);
   Progress.Progress=0;
   KeyData.hWndProgress=CreateWindow("Progress","Прогресс рендеринга",WS_VISIBLE|WS_OVERLAPPED,CW_USEDEFAULT,CW_USEDEFAULT,320,80,hWnd,0,hProjectInstance,NULL);
   RENDER Render(FPRS_1.FileName);//запустим рендер
   DestroyWindow(KeyData.hWndProgress);
   EnableWindow(KeyData.hWndMain,TRUE);
   EnableWindow(KeyData.hWndMenu,TRUE);
   SetActiveWindow(KeyData.hWndMain);
  }
 }
 //------------------------------------------------------------------------------
 //Обработка меню Setting
 //------------------------------------------------------------------------------
 if (id==FORM_MENU_SETTING_VECTOR)
 {
  if (SetUp.ShowVector==0)
  {
   SetUp.ShowVector=1;
   SetMenuItem(hSettingMenu,FORM_MENU_SETTING_VECTOR,MFS_CHECKED,FALSE);
  }
  else
  {
   SetUp.ShowVector=0;
   SetMenuItem(hSettingMenu,FORM_MENU_SETTING_VECTOR,MFS_UNCHECKED,FALSE);
  }
  InvalidateRect(hWnd,NULL,FALSE);
 }
 if (id==FORM_MENU_SETTING_SHOWSEGMENT)
 {
  if (SetUp.ShowSegment==0)
  {
   SetUp.ShowSegment=1;
   SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWSEGMENT,MFS_CHECKED,FALSE);
  }
  else
  {
   SetUp.ShowSegment=0;
   SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWSEGMENT,MFS_UNCHECKED,FALSE);
  }
  InvalidateRect(hWnd,NULL,FALSE);
 }
 if (id==FORM_MENU_SETTING_SHOWSECTOR)
 {
  if (SetUp.ShowSector==0)
  {
   SetUp.ShowSector=1;
   SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWSECTOR,MFS_CHECKED,FALSE);
  }
  else
  {
   SetUp.ShowSector=0;
   SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWSECTOR,MFS_UNCHECKED,FALSE);
  }
  InvalidateRect(hWnd,NULL,FALSE);
 }
 if (id==FORM_MENU_SETTING_SHOWLIGHTING)
 {
  if (SetUp.ShowLighting==0)
  {
   SetUp.ShowLighting=1;
   SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWLIGHTING,MFS_CHECKED,FALSE);
  }
  else
  {
   SetUp.ShowLighting=0;
   SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWLIGHTING,MFS_UNCHECKED,FALSE);
  }
  InvalidateRect(hWnd,NULL,FALSE);
 }
 if (id==FORM_MENU_SETTING_RENDER) SettingRenderForm.Activate();
}
void FORM::KeyDown(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 int key=wParam;
 if (key==VK_DELETE)//удаление объектов
 {
  if (KeyData.PrimaryMode==6) CreateSegmentForm.DeleteSegment();//удаление сегментов
  if (KeyData.PrimaryMode==7)//удаление секторов
  {
   //работа с секторами
   if (KeyData.SelectSectorType==0) CreateSimplySectorForm.DeleteSector();//если выбран простой сектор
   if (KeyData.SelectSectorType==1) CreateSimplyDoorForm.DeleteSector();//если выбрана простая дверь
   //работа с секторами
  }
  if (KeyData.PrimaryMode==8) CreateLightingForm.DeleteLighting();//удаление источников света
  MenuForm.UpDate();
  InvalidateRect(hWnd,NULL,FALSE);
 }
 if (key==VK_RETURN)//модификация объекта
 {
  if (KeyData.PrimaryMode==9) CreateSegmentForm.ModifycationSegment(KeyData.SelectLine);//модификация сегмента или линии раздела
  if (KeyData.PrimaryMode==10)//модификация секторов
  {
   //работа с секторами
   if (KeyData.SelectSectorType==0) CreateSimplySectorForm.ModifycationSector(KeyData.SelectSector);//если выбран простой сектор
   if (KeyData.SelectSectorType==1) CreateSimplyDoorForm.ModifycationSector(KeyData.SelectSector);//если выбрана простая дверь
   //работа с секторами
  }
  if (KeyData.PrimaryMode==11) CreateLightingForm.ModifycationLighting(KeyData.SelectLighting);//модификация источников света
 }
}
//------------------------------------------------------------------------------
void FORM::SaveMap(char *FileName)
{
 FILE *File=fopen(FileName,"w+b");
 if (File==NULL)
 {
  MessageBox(hWnd,"Не могу записать файл.","Ошибка записи",MB_OK|MB_ICONSTOP);
  return;
 }
 fprintf(File,"----------------------------------------\n");
 fprintf(File,"Map Editor Version 1.0                  \n");
 fprintf(File,"----------------------------------------\n");
 fprintf(File,"\n");
 fprintf(File,"----------------------------------------\n");
 fprintf(File,"Сегменты                                \n");
 fprintf(File,"----------------------------------------\n");
 CreateSegmentForm.SaveSegment(File);
 fprintf(File,"----------------------------------------\n");
 fprintf(File,"Источники света                         \n");
 fprintf(File,"----------------------------------------\n");
 CreateLightingForm.SaveLighting(File);
 //работа с секторами
 fprintf(File,"----------------------------------------\n");
 fprintf(File,"Простые сектора                         \n");
 fprintf(File,"----------------------------------------\n");
 CreateSimplySectorForm.SaveSector(File);
 fprintf(File,"----------------------------------------\n");
 fprintf(File,"Простые двери                           \n");
 fprintf(File,"----------------------------------------\n");
 CreateSimplyDoorForm.SaveSector(File);
 //работа с секторами
 fprintf(File,"----------------------------------------\n");
 fprintf(File,"Стартовая позиция                       \n");
 fprintf(File,"----------------------------------------\n");
 StartPosForm.SaveStartPosition(File);
 fprintf(File,"----------------------------------------\n");
 fprintf(File,"Текущие настройки редактора             \n");
 fprintf(File,"----------------------------------------\n");
 fprintf(File,"EDITOR SETTING\n");
 fprintf(File,"%i ",xLeftMap);
 fprintf(File,"%i ",yTopMap);
 fprintf(File,"%i ",SetUp.ShowSegmentCreateDialog);
 fprintf(File,"%i ",SetUp.ShowVector);
 fprintf(File,"%i ",SetUp.ShowSegment);
 fprintf(File,"%i ",SetUp.ShowSector);
 fprintf(File,"%i ",SetUp.ShowLighting);
 fprintf(File,"%i ",SetUp.BlockSize);
 fprintf(File,"%f ",SetUp.Constant_Attenuation);
 fprintf(File,"%f ",SetUp.Linear_Attenuation);
 fprintf(File,"%f ",SetUp.Quadric_Attenuation);
 fprintf(File,"%i ",SetUp.R_Ambient);
 fprintf(File,"%i ",SetUp.G_Ambient);
 fprintf(File,"%i ",SetUp.B_Ambient);
 fprintf(File,"%i ",SetUp.R_Fog);
 fprintf(File,"%i ",SetUp.G_Fog);
 fprintf(File,"%i ",SetUp.B_Fog);
 fprintf(File,"%i ",SetUp.Fog_Density);
 fprintf(File,"%i ",SetUp.Fog_Enable);
 fclose(File);
}
void FORM::LoadMap(char *FileName)
{
 FILE *File=fopen(FileName,"r+b");
 if (File==NULL)
 {
  MessageBox(hWnd,"Не могу открыть файл.","Ошибка чтения",MB_OK|MB_ICONSTOP);
  return;
 }
 Initialize();
 CreateLightingForm.Initialize();
 CreatePolygonForm.Initialize();
 StartPosForm.Initialize();
 CreateSegmentForm.Initialize();
 CreateSimplySectorForm.Initialize();
 CreateSegmentForm.LoadSegment(File);
 fclose(File);
 File=fopen(FileName,"r+b");
 CreateLightingForm.LoadLighting(File);
 fclose(File);
 //работа с секторами
 File=fopen(FileName,"r+b");
 CreateSimplySectorForm.LoadSector(File);
 fclose(File);
 File=fopen(FileName,"r+b");
 CreateSimplyDoorForm.LoadSector(File);
 fclose(File);
 //работа с секторами
 File=fopen(FileName,"r+b");
 StartPosForm.LoadStartPosition(File);
 fclose(File);
 File=fopen(FileName,"r+b");
 if (GetReadPos(File,"EDITOR SETTING"))
 {
  xLeftMap=(int)ReadNumber(File);
  yTopMap=(int)ReadNumber(File);
  SetUp.ShowSegmentCreateDialog=(int)ReadNumber(File);
  if (SetUp.ShowSegmentCreateDialog==0) CheckBox_ShowDialog.SetStateOff();
  else CheckBox_ShowDialog.SetStateOn();
  SetUp.ShowVector=(int)ReadNumber(File);
  if (SetUp.ShowVector==1) SetMenuItem(hSettingMenu,FORM_MENU_SETTING_VECTOR,MFS_CHECKED,FALSE);
  else SetMenuItem(hSettingMenu,FORM_MENU_SETTING_VECTOR,MFS_UNCHECKED,FALSE);
  SetUp.ShowSegment=(int)ReadNumber(File);
  if (SetUp.ShowSegment==1) SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWSEGMENT,MFS_CHECKED,FALSE);
  else SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWSEGMENT,MFS_UNCHECKED,FALSE);
  SetUp.ShowSector=(int)ReadNumber(File);
  if (SetUp.ShowSector==1) SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWSECTOR,MFS_CHECKED,FALSE);
  else SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWSECTOR,MFS_UNCHECKED,FALSE);
  SetUp.ShowLighting=(int)ReadNumber(File);
  if (SetUp.ShowLighting==1) SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWLIGHTING,MFS_CHECKED,FALSE);
  else SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWLIGHTING,MFS_UNCHECKED,FALSE);
  SetUp.BlockSize=(int)ReadNumber(File);
  SetUp.Constant_Attenuation=ReadNumber(File);
  SetUp.Linear_Attenuation=ReadNumber(File);
  SetUp.Quadric_Attenuation=ReadNumber(File);
  SetUp.R_Ambient=(int)ReadNumber(File);
  SetUp.G_Ambient=(int)ReadNumber(File);
  SetUp.B_Ambient=(int)ReadNumber(File);
  SetUp.R_Fog=(int)ReadNumber(File);
  SetUp.G_Fog=(int)ReadNumber(File);
  SetUp.B_Fog=(int)ReadNumber(File);
  SetUp.Fog_Density=(int)ReadNumber(File);
  SetUp.Fog_Enable=(int)ReadNumber(File);
 }
 fclose(File);
 MenuForm.UpDate();
 MenuForm.Static_Text2.SetText("-");
 InvalidateRect(hWnd,NULL,FALSE);
}
//------------------------------------------------------------------------------
void FORM::Initialize(void)
{
 xLeftMap=0;//коордитата левого угла карты
 yTopMap=0;//координата верхнего угла карты
 MapMove=0;//режим прокрутки карты
  
 KeyData.PrimaryMode=0;//первичный режим работы
 KeyData.SecondaryMode=0;//вторичный режим работы
 KeyData.MaximumNumberOfLine=0;//сколько всего на карте линий (линия-сегмент или линия раздела)
 KeyData.MaximumNumberOfSimplySector=0;//сколько всего на карте обычных секторов
 KeyData.MaximumNumberOfSimplyDoor=0;//сколько всего на карте обычных дверей
 KeyData.MaximumNumberOfDisposableDoor=0;//сколько всего на карте одноразовых дверей
 KeyData.MaximumNumberOfClosedDoor=0;//сколько всего на карте запертых дверей
 KeyData.MaximumNumberOfAutoClosedDoor=0;//сколько всего на карте закрывающихся дверей
 KeyData.MaximumNumberOfSimplyPlatform=0;//сколько всего на карте обычных платформ
 KeyData.MaximumNumberOfInactivePlatform=0;//сколько всего на карте неактивных платформ
 KeyData.MaximumNumberOfDisconnectPlatform=0;//сколько всего на карте отключающихся платформ
 KeyData.MaximumNumberOfSimplyBridge=0;//сколько всего на карте обычных мостиков
 KeyData.MaximumNumberOfSimplyTeleport=0;//сколько всего на карте обычных телепортаторов
 KeyData.MaximumNumberOfAllSector=0;//сколько всего на карте всех секторов
 KeyData.MaximumNumberOfLighting=0;//сколько всего на карте источников света
  
 KeyData.MaximumPset=0;//всего точек в рисуемом блоке
 KeyData.SelectLine=-1;//ни один сегмент не выбран
 KeyData.SelectSector=-1;//ни один сектор не выбран
 KeyData.SelectSectorType=-1;//ни одного типа
 KeyData.SelectLighting=-1;//ни один источник света не выбран
 SetUp.ShowSegmentCreateDialog=1;//диалог вызывается
 CheckBox_ShowDialog.SetStateOn();
 SetUp.ShowVector=0;//направление не показывается
 SetUp.ShowSegment=1;//сегменты показываются
 SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWSEGMENT,MFS_CHECKED,FALSE);
 SetUp.ShowSector=1;//сектора показываются
 SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWSECTOR,MFS_CHECKED,FALSE);
 SetUp.ShowLighting=1;//источники света показываются
 SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWLIGHTING,MFS_CHECKED,FALSE);
  
  
 SetUp.BlockSize=64;//размер блока разбиения
 SetUp.Constant_Attenuation=1;//постоянное ослабление света
 SetUp.Linear_Attenuation=0.0001;//линейное ослабление света
 SetUp.Quadric_Attenuation=0.00001;//квадратичное ослабление света
 SetUp.R_Ambient=32;//глобальное фоновое освещение
 SetUp.G_Ambient=32;
 SetUp.B_Ambient=32;
 SetUp.R_Fog=255;//настройки тумана
 SetUp.G_Fog=255;
 SetUp.B_Fog=255;
 SetUp.Fog_Density=2500000;
 SetUp.Fog_Enable=0;
}
int FORM::PointPosition(float x,float y,float xw1,float yw1,float xw2,float yw2)
{
 float p=x*(yw1-yw2)-y*(xw1-xw2)+xw1*yw2-xw2*yw1;
 if (p<=-EPS) p=-1;
 if (p>=EPS) p=1;
 if (p>-EPS && p<EPS) p=0;
 return((int)(p));
}
int FORM::SectorGamber(void)
{
 for(int n=0;n<=KeyData.MaximumPset-1;n++)
 {
  int p1=n;
  int p2=n+1;
  if (p2>=KeyData.MaximumPset-1) p2=0;
  float x1=(float)(KeyData.X[p1]);//выбрали сторону многоугольника
  float y1=(float)(KeyData.Y[p1]);
  float x2=(float)(KeyData.X[p2]);
  float y2=(float)(KeyData.Y[p2]);
  int pos=0;
  for(int m=0;m<KeyData.MaximumPset-1;m++)
  {
   if (m==n) continue;
   float x=(float)(KeyData.X[m]);//выбрали точку многоугольника
   float y=(float)(KeyData.Y[m]);
   int res=PointPosition(x,y,x1,y1,x2,y2);
   if (res==0) continue;
   if (pos==0) pos=res;
   if (pos*res<0) return(0);//не выпуклый
  }
 }
 return(1);//выпуклый
}
void FORM::GetSelectLine(int x,int y,int frontier)
{
 if (!(x>=0 && x<=499 && y>=0 && y<=499)) return;
 KeyData.SelectLine=CreateSegmentForm.GetLineInScreen((int)(x+xLeftMap*10.0),(int)(y+yTopMap*10.0),frontier);
}
void FORM::GetSelectSector(int x,int y)
{
 if (!(x>=0 && x<=499 && y>=0 && y<=499)) return;
 //работа с секторами
 //проверим среди обычных секторов
 KeyData.SelectSector=CreateSimplySectorForm.GetSectorInScreen((int)(x+xLeftMap*10.0),(int)(y+yTopMap*10.0));
 if (KeyData.SelectSector!=-1)
 {
  KeyData.SelectSectorType=0;
  return;
 }
 //проверим среди обычных дверей
 KeyData.SelectSector=CreateSimplyDoorForm.GetSectorInScreen((int)(x+xLeftMap*10.0),(int)(y+yTopMap*10.0));
 if (KeyData.SelectSector!=-1) 
 {
  KeyData.SelectSectorType=1;
  return;
 }
 //работа с секторами
}
void FORM::GetSelectLighting(int x,int y)
{
 if (!(x>=0 && x<=499 && y>=0 && y<=499)) return;
 KeyData.SelectLighting=CreateLightingForm.GetLightingInScreen((int)(x+xLeftMap*10.0),(int)(y+yTopMap*10.0));
}
void FORM::LoadTexture(char *FileName)
{
 int n;
 unsigned char R[256];
 unsigned char G[256];
 unsigned char B[256];
 FILE *file=fopen(FileName,"r+b");
 if (file!=NULL)
 {
  KeyData.MaximumTexture=(unsigned short)LoadShort(file);
  if (KeyData.MaximumTexture<=0)
  {
   KeyData.MaximumTexture=0;
   fclose(file);
   return;
  }
  //теперь пропустим таблицу смещений текстур (здесь она не нужна)
  for(n=0;n<KeyData.MaximumTexture;n++) LoadInt(file);
  //и загрузим сами текстуры
  KeyData.TextureMap=new TEXTURE_MAP[KeyData.MaximumTexture];
  for (n=0;n<KeyData.MaximumTexture;n++)
  {
   int ColorMode=LoadChar(file);
   if (ColorMode==1)//256 цветов
   {
    for(int m=0;m<256;m++)
    {
     R[m]=(unsigned char)LoadChar(file);
     G[m]=(unsigned char)LoadChar(file);
     B[m]=(unsigned char)LoadChar(file);
    }
    KeyData.TextureMap[n].Size=(unsigned short)LoadShort(file);
    KeyData.TextureMap[n].R=new unsigned char[KeyData.TextureMap[n].Size*KeyData.TextureMap[n].Size];
    KeyData.TextureMap[n].G=new unsigned char[KeyData.TextureMap[n].Size*KeyData.TextureMap[n].Size];
    KeyData.TextureMap[n].B=new unsigned char[KeyData.TextureMap[n].Size*KeyData.TextureMap[n].Size];
    for(int x=0;x<KeyData.TextureMap[n].Size;x++)
    for(int y=0;y<KeyData.TextureMap[n].Size;y++)
    {
     int byte=(unsigned char)LoadChar(file);
     int offset=x*KeyData.TextureMap[n].Size+y;
     KeyData.TextureMap[n].R[offset]=R[byte];
     KeyData.TextureMap[n].G[offset]=G[byte];
     KeyData.TextureMap[n].B[offset]=B[byte];
    }
   }
   if (ColorMode==2)//RGB цвета
   {
    KeyData.TextureMap[n].Size=(unsigned short)LoadShort(file);
    KeyData.TextureMap[n].R=new unsigned char[KeyData.TextureMap[n].Size*KeyData.TextureMap[n].Size];
    KeyData.TextureMap[n].G=new unsigned char[KeyData.TextureMap[n].Size*KeyData.TextureMap[n].Size];
    KeyData.TextureMap[n].B=new unsigned char[KeyData.TextureMap[n].Size*KeyData.TextureMap[n].Size];
    for(int x=0;x<KeyData.TextureMap[n].Size;x++)
    for(int y=0;y<KeyData.TextureMap[n].Size;y++)
    {
     unsigned char r=(unsigned char)LoadChar(file);
     unsigned char g=(unsigned char)LoadChar(file);
     unsigned char b=(unsigned char)LoadChar(file);
     int offset=x*KeyData.TextureMap[n].Size+y;
     KeyData.TextureMap[n].R[offset]=r;
     KeyData.TextureMap[n].G[offset]=g;
     KeyData.TextureMap[n].B[offset]=b;
    }
   }
  }
  fclose(file);
 }
 else KeyData.MaximumTexture=0;
}
 

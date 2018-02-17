#include "wc_form.h"

 
extern SSettings sSettings;//настройки редактора
extern SKeyData sKeyData;//ключевая информация
extern HINSTANCE hProjectInstance;

extern CDialog_CreateLighting cDialog_CreateLighting;
extern CDialog_CreateSimplySector cDialog_CreateSimplySector;
extern CDialog_CreateSimplyDoor cDialog_CreateSimplyDoor;
extern CDialog_CreateSegment cDialog_CreateSegment;
extern CDialog_StartPos StartPoscWnd_Form;
extern CDialog_CreatePolygon cDialog_CreatePolygon;
extern CDialog_CreateStar cDialog_CreateStar;
extern CWnd_Menu cWnd_Menu;
extern CWnd_Progress cWnd_Progress;
extern CDialog_SettingsRender cDialog_SettingsRender;

extern unsigned char VideoBuffer[500*500*3];//поле для рисования

CWnd_Form cWnd_Form;
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
 wc.lpszClassName="cWnd_Form";
 wc.lpfnWndProc=(WNDPROC)FORM_wndProc;
 RegisterClass(&wc);
}
LONG WINAPI FORM_wndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
 switch(msg)
 {
  case WM_CREATE:
  {
   cWnd_Form.Create(hWnd,wParam,lParam);
   return(0);
  }
  case WM_DESTROY:
  {
   cWnd_Form.Destroy(hWnd,wParam,lParam);
   PostQuitMessage(0);
   return(0);
  }
  case WM_PAINT:
  {
   cWnd_Form.Paint(hWnd,wParam,lParam);
   return(0);
  }
  case WM_RBUTTONDOWN:
  {
   cWnd_Form.RButtonDown(hWnd,wParam,lParam);
   return(0);
  }
  case WM_RBUTTONUP:
  {
   cWnd_Form.RButtonUp(hWnd,wParam,lParam);
   return(0);
  }
  case WM_MOUSEMOVE:
  {
   cWnd_Form.MouseMove(hWnd,wParam,lParam);
   return(0);
  }
  case WM_TIMER:
  {
   cWnd_Form.Timer(hWnd,wParam,lParam);
   return(0);
  }
  case WM_LBUTTONUP:
  {
   cWnd_Form.LButtonUp(hWnd,wParam,lParam);
   return(0);
  }
  case WM_COMMAND:
  {
   cWnd_Form.Command(hWnd,wParam,lParam);
   return(0);
  }
  case WM_KEYDOWN:
  {
   cWnd_Form.KeyDown(hWnd,wParam,lParam);
   return(0);
  }
 }
 return(DefWindowProc(hWnd,msg,wParam,lParam));
}
//------------------------------------------------------------------------------
void CWnd_Form::Create(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 hWnd=hWnds;
 sKeyData.hWndMain=hWnd;
 Initialize();//инициализируем редактор
 LoadTexture("texture.pak");//загружаем текстуры
 HMENU hMainMenu=GetMenu(hWnd);
 hSettingMenu=GetSubMenu(hMainMenu,1);
 FPRS.Create(hWnd);
 FPRS_1.Create(hWnd);
 Static_cWnd_Form.Create(510,4,280,32,"",WS_BORDER,hWnd,hProjectInstance);
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
 CreateWindow("cWnd_Menu","Панель управления",WS_VISIBLE|WS_CAPTION|WS_POPUP,525,80,260,390,hWnd,hControlMenu,hProjectInstance,NULL);
}
void CWnd_Form::Destroy(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 KillTimer(hWnd,OldTimer);
 if (sKeyData.MaximumTexture>0)
 {
  for(int n=0;n<sKeyData.MaximumTexture;n++)
  {
   delete(sKeyData.TextureMap[n].R);
   delete(sKeyData.TextureMap[n].G);
   delete(sKeyData.TextureMap[n].B);
  }
  delete(sKeyData.TextureMap);
 }
}
void CWnd_Form::Paint(HWND hWnds,WPARAM wParam,LPARAM lParam)
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
 if (sSettings.ShowLighting==1) cDialog_CreateLighting.DrawAllLighting(xLeftMap,yTopMap);
 //рисуем все имеющиеся сектора:
 if (sSettings.ShowSector==1)
 {
  //работа с секторами
  //обычные сектора
  cDialog_CreateSimplySector.DrawAllSector(xLeftMap,yTopMap);
  //обычные двери
  cDialog_CreateSimplyDoor.DrawAllSector(xLeftMap,yTopMap);
  //работа с секторами
 }
 //рисуем все имеющиеся сегменты
 if (sSettings.ShowSegment==1) cDialog_CreateSegment.DrawAllSegment(xLeftMap,yTopMap);
 //рисуем стартовую позицию
 StartPoscWnd_Form.DrawStartPos(xLeftMap,yTopMap);
 //рисуем текущий создающийся объект (если он есть)
 for(int n=0;n<sKeyData.MaximumPset-1;n++)
 {
  DrawLine((sKeyData.X[n]-xLeftMap)*10,(sKeyData.Y[n]-yTopMap)*10,(sKeyData.X[n+1]-xLeftMap)*10,(sKeyData.Y[n+1]-yTopMap)*10,64,255,255);
 }
 if (sKeyData.MaximumPset>0) Button_Reset.Enable();//если есть точки, то кнопка активна, иначе - нет
 else Button_Reset.Disable();
 //выводим на экран то что нарисовали
 PAINTSTRUCT ps;
 HDC hdc;
 hdc=BeginPaint(hWnd,&ps);
 StretchDIBits(hdc,8,8,500,500,0,0,500,500,VideoBuffer,&info,DIB_RGB_COLORS,SRCCOPY);
 EndPaint(hWnd,&ps);
}
void CWnd_Form::RButtonDown(HWND hWnds,WPARAM wParam,LPARAM lParam)
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
void CWnd_Form::RButtonUp(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 if (MapMove==1)
 {
  ClipCursor(NULL);
  ShowCursor(TRUE);
  MapMove=0;
 }
}
void CWnd_Form::MouseMove(HWND hWnds,WPARAM wParam,LPARAM lParam)
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
 if (sKeyData.MaximumPset>0 && MapMove==0)
 {
  sKeyData.X[sKeyData.MaximumPset-1]=MouseXS;
  sKeyData.Y[sKeyData.MaximumPset-1]=MouseYS;
  InvalidateRect(hWnd,NULL,FALSE);
 }
}
void CWnd_Form::Timer(HWND hWnds,WPARAM wParam,LPARAM lParam)
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
void CWnd_Form::LButtonUp(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 //-----------------------------------------------------------------------------
 //РАБОТА С СЕГМЕНТАМИ
 //-----------------------------------------------------------------------------
 if (sKeyData.PrimaryMode==1)//создаётся сегмент или линия раздела
 {
  if (sKeyData.MaximumPset==0)//если мы ставим первую точку линии
  {
   sKeyData.X[0]=MouseXS;
   sKeyData.Y[0]=MouseYS;
   sKeyData.X[1]=MouseXS;
   sKeyData.Y[1]=MouseYS;
   sKeyData.MaximumPset=2;
  }
  else// если мы дорисовали линию, её нужно сохранить
  {
   if (sKeyData.X[0]==sKeyData.X[1] && sKeyData.Y[0]==sKeyData.Y[1])
   {
    MessageBox(hWnd,"Сегмент имеет нулевую длину и создан не будет.","Предупреждение",MB_OK);
    return;
   }
   if (sSettings.ShowSegmentCreateDialog==1)
   {
    if (sKeyData.SecondaryMode==0) cDialog_CreateSegment.CreateNewSegment(0);
    if (sKeyData.SecondaryMode==1) cDialog_CreateSegment.CreateNewSegment(1);
   }
   else
   {
    if (sKeyData.SecondaryMode==0) cDialog_CreateSegment.CreateSegment(0);
    if (sKeyData.SecondaryMode==1) cDialog_CreateSegment.CreateSegment(1);
   }
  }
 }
 //удаление сегментов
 if (sKeyData.PrimaryMode==6)
 {
  if (sKeyData.SecondaryMode==0) GetSelectLine(MouseXW,MouseYW,0);
  if (sKeyData.SecondaryMode==1) GetSelectLine(MouseXW,MouseYW,1);
  if (sKeyData.SecondaryMode==2) GetSelectLine(MouseXW,MouseYW,2);
 }
 //модификация сегмента
 if (sKeyData.PrimaryMode==9)
 {
  if (sKeyData.SecondaryMode==0) GetSelectLine(MouseXW,MouseYW,0);
  if (sKeyData.SecondaryMode==1) GetSelectLine(MouseXW,MouseYW,1);
 }
 //-----------------------------------------------------------------------------
 //РАБОТА СО СТАНДАРТНЫМИ ФИГУРАМИ
 //-----------------------------------------------------------------------------
 if (sKeyData.PrimaryMode==5 && sKeyData.SecondaryMode==0)//создание правильного многоугольника
 {
  cDialog_CreatePolygon.Activate(MouseXS,MouseYS);
 }
 if (sKeyData.PrimaryMode==5 && sKeyData.SecondaryMode==1)//создание звезды
 {
  cDialog_CreateStar.Activate(MouseXS,MouseYS);
 }
 //-----------------------------------------------------------------------------
 //РАБОТА С ИСТОЧНИКАМИ СВЕТА
 //-----------------------------------------------------------------------------
 if (sKeyData.PrimaryMode==3)//создание источника света
 {
  cDialog_CreateLighting.CreateNewLighting(MouseXS,MouseYS);
 }
 if (sKeyData.PrimaryMode==8)//удаление источника света
 {
  GetSelectLighting(MouseXW,MouseYW);
 }
 if (sKeyData.PrimaryMode==11)//модификация источника света
 {
  GetSelectLighting(MouseXW,MouseYW);
 }
 //-----------------------------------------------------------------------------
 //РАБОТА С СТАРТОВОЙ ПОЗИЦИЕЙ
 //-----------------------------------------------------------------------------
 if (sKeyData.PrimaryMode==4)
 {
  StartPoscWnd_Form.Activate(MouseXS,MouseYS);
 }
 //-----------------------------------------------------------------------------
 //РАБОТА С СЕКТОРАМИ
 //-----------------------------------------------------------------------------
 if (sKeyData.PrimaryMode==2)//создаётся сектор
 {
  if (sKeyData.MaximumPset==0)//если мы ставим первую точку сектора
  {
   sKeyData.X[0]=MouseXS;
   sKeyData.Y[0]=MouseYS;
   sKeyData.X[1]=MouseXS;
   sKeyData.Y[1]=MouseYS;
   sKeyData.MaximumPset=2;
  }
  else// если мы ставим не первую точку сектора
  {
   if (sKeyData.X[0]==MouseXS && sKeyData.Y[0]==MouseYS)//мы замкнули контур, значит сектор готов
   {
    //проверим сектор на выпуклость
    if (SectorGamber()==0)//сектор не выпуклый
    {
     MessageBox(hWnd,"Сектор не является выпуклым многоугольником !","Ошибка",MB_OK);
     sKeyData.MaximumPset=0;
    }
    else//сектор выпуклый, можно его добавить в набор
    {
     //работа с секторами
     if (sKeyData.SecondaryMode==0) cDialog_CreateSimplySector.CreateNewSector();
     if (sKeyData.SecondaryMode==1) cDialog_CreateSimplyDoor.CreateNewSector();
     //работа с секторами
    }
   }
   else//иначе просто добавляем точку
   {
    if (sKeyData.X[sKeyData.MaximumPset-2]==MouseXS && sKeyData.Y[sKeyData.MaximumPset-2]==MouseYS)
    {
     MessageBox(hWnd,"Линия имеет нулевую длину и не будет занесена в список.","Предупреждение",MB_OK);
     return;
    }
    sKeyData.X[sKeyData.MaximumPset-1]=MouseXS;
    sKeyData.Y[sKeyData.MaximumPset-1]=MouseYS;
    sKeyData.X[sKeyData.MaximumPset]=MouseXS;
    sKeyData.Y[sKeyData.MaximumPset]=MouseYS;
    sKeyData.MaximumPset++;
   }
  }
 }
 //удаление секторов
 if (sKeyData.PrimaryMode==7)
 {
  GetSelectSector(MouseXW,MouseYW);
 }
 //модификация секторов
 if (sKeyData.PrimaryMode==10)
 {
  GetSelectSector(MouseXW,MouseYW);
 }
 InvalidateRect(hWnd,NULL,FALSE);
}
void CWnd_Form::Command(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 int id=LOWORD(wParam);
 if (id==FORM_BUTTON_RESET)
 {
  sKeyData.MaximumPset=0;
  InvalidateRect(hWnd,NULL,FALSE);
 }
 if (id==FORM_BUTTON_EXECUTE_DIALOG)
 {
  EnableWindow(sKeyData.hWndMenu,FALSE);
  cDialog_CreateSegment.ChangeParameters();
  EnableWindow(sKeyData.hWndMenu,TRUE);
 }
 if (id==FORM_MENU_FILE_EXIT)
 {
  int res=MessageBox(hWnd,"Вы хотите выйти ?","Подтверждение действия",MB_YESNO|MB_ICONWARNING|MB_DEFBUTTON2);
  if (res==IDYES) DestroyWindow(hWnd);
 }
 if (id==FORM_CHECKBOX_SHOWDIALOG)
 {
  if (sSettings.ShowSegmentCreateDialog==0)
  {
   CheckBox_ShowDialog.SetStateOn();
   sSettings.ShowSegmentCreateDialog=1;
  }
  else
  {
   CheckBox_ShowDialog.SetStateOff();
   sSettings.ShowSegmentCreateDialog=0;
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
   cDialog_CreateLighting.Initialize();
   cDialog_CreatePolygon.Initialize();
   StartPoscWnd_Form.Initialize();
   cDialog_CreateSegment.Initialize();
   //работа с секторами
   cDialog_CreateSimplySector.Initialize();
   cDialog_CreateSimplyDoor.Initialize();
   //работа с секторами
   cWnd_Menu.UpDate();
   InvalidateRect(hWnd,NULL,FALSE);
  }
 }
 if (id==FORM_MENU_FILE_CREATESTAGE)//создание сцены
 {
  if (FPRS_1.StartSave("Создание сцены","*.stg\0*.stg\0"))
  {
   EnableWindow(sKeyData.hWndMain,FALSE);
   EnableWindow(sKeyData.hWndMenu,FALSE);
   cWnd_Progress.cWnd_Progress=0;
   sKeyData.hWndcWnd_Progress=CreateWindow("cWnd_Progress","Прогресс рендеринга",WS_VISIBLE|WS_OVERLAPPED,CW_USEDEFAULT,CW_USEDEFAULT,320,80,hWnd,0,hProjectInstance,NULL);
   CRender Render(FPRS_1.FileName);//запустим рендер
   DestroyWindow(sKeyData.hWndcWnd_Progress);
   EnableWindow(sKeyData.hWndMain,TRUE);
   EnableWindow(sKeyData.hWndMenu,TRUE);
   SetActiveWindow(sKeyData.hWndMain);
  }
 }
 //------------------------------------------------------------------------------
 //Обработка меню Setting
 //------------------------------------------------------------------------------
 if (id==FORM_MENU_SETTING_VECTOR)
 {
  if (sSettings.ShowVector==0)
  {
   sSettings.ShowVector=1;
   SetMenuItem(hSettingMenu,FORM_MENU_SETTING_VECTOR,MFS_CHECKED,FALSE);
  }
  else
  {
   sSettings.ShowVector=0;
   SetMenuItem(hSettingMenu,FORM_MENU_SETTING_VECTOR,MFS_UNCHECKED,FALSE);
  }
  InvalidateRect(hWnd,NULL,FALSE);
 }
 if (id==FORM_MENU_SETTING_SHOWSSegment)
 {
  if (sSettings.ShowSegment==0)
  {
   sSettings.ShowSegment=1;
   SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWSSegment,MFS_CHECKED,FALSE);
  }
  else
  {
   sSettings.ShowSegment=0;
   SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWSSegment,MFS_UNCHECKED,FALSE);
  }
  InvalidateRect(hWnd,NULL,FALSE);
 }
 if (id==FORM_MENU_SETTING_SHOWSECTOR)
 {
  if (sSettings.ShowSector==0)
  {
   sSettings.ShowSector=1;
   SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWSECTOR,MFS_CHECKED,FALSE);
  }
  else
  {
   sSettings.ShowSector=0;
   SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWSECTOR,MFS_UNCHECKED,FALSE);
  }
  InvalidateRect(hWnd,NULL,FALSE);
 }
 if (id==FORM_MENU_SETTING_SHOWSLighting)
 {
  if (sSettings.ShowLighting==0)
  {
   sSettings.ShowLighting=1;
   SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWSLighting,MFS_CHECKED,FALSE);
  }
  else
  {
   sSettings.ShowLighting=0;
   SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWSLighting,MFS_UNCHECKED,FALSE);
  }
  InvalidateRect(hWnd,NULL,FALSE);
 }
 if (id==FORM_MENU_SETTING_CRender) cDialog_SettingsRender.Activate();
}
void CWnd_Form::KeyDown(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 int key=wParam;
 if (key==VK_DELETE)//удаление объектов
 {
  if (sKeyData.PrimaryMode==6) cDialog_CreateSegment.DeleteSegment();//удаление сегментов
  if (sKeyData.PrimaryMode==7)//удаление секторов
  {
   //работа с секторами
   if (sKeyData.SelectSectorType==0) cDialog_CreateSimplySector.DeleteSector();//если выбран простой сектор
   if (sKeyData.SelectSectorType==1) cDialog_CreateSimplyDoor.DeleteSector();//если выбрана простая дверь
   //работа с секторами
  }
  if (sKeyData.PrimaryMode==8) cDialog_CreateLighting.DeleteLighting();//удаление источников света
  cWnd_Menu.UpDate();
  InvalidateRect(hWnd,NULL,FALSE);
 }
 if (key==VK_RETURN)//модификация объекта
 {
  if (sKeyData.PrimaryMode==9) cDialog_CreateSegment.ModifycationSegment(sKeyData.SelectLine);//модификация сегмента или линии раздела
  if (sKeyData.PrimaryMode==10)//модификация секторов
  {
   //работа с секторами
   if (sKeyData.SelectSectorType==0) cDialog_CreateSimplySector.ModifycationSector(sKeyData.SelectSector);//если выбран простой сектор
   if (sKeyData.SelectSectorType==1) cDialog_CreateSimplyDoor.ModifycationSector(sKeyData.SelectSector);//если выбрана простая дверь
   //работа с секторами
  }
  if (sKeyData.PrimaryMode==11) cDialog_CreateLighting.ModifycationLighting(sKeyData.SelectLighting);//модификация источников света
 }
}
//------------------------------------------------------------------------------
void CWnd_Form::SaveMap(char *FileName)
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
 cDialog_CreateSegment.SaveSegment(File);
 fprintf(File,"----------------------------------------\n");
 fprintf(File,"Источники света                         \n");
 fprintf(File,"----------------------------------------\n");
 cDialog_CreateLighting.SaveLighting(File);
 //работа с секторами
 fprintf(File,"----------------------------------------\n");
 fprintf(File,"Простые сектора                         \n");
 fprintf(File,"----------------------------------------\n");
 cDialog_CreateSimplySector.SaveSector(File);
 fprintf(File,"----------------------------------------\n");
 fprintf(File,"Простые двери                           \n");
 fprintf(File,"----------------------------------------\n");
 cDialog_CreateSimplyDoor.SaveSector(File);
 //работа с секторами
 fprintf(File,"----------------------------------------\n");
 fprintf(File,"Стартовая позиция                       \n");
 fprintf(File,"----------------------------------------\n");
 StartPoscWnd_Form.SaveStartPosition(File);
 fprintf(File,"----------------------------------------\n");
 fprintf(File,"Текущие настройки редактора             \n");
 fprintf(File,"----------------------------------------\n");
 fprintf(File,"EDITOR SETTING\n");
 fprintf(File,"%i ",xLeftMap);
 fprintf(File,"%i ",yTopMap);
 fprintf(File,"%i ",sSettings.ShowSegmentCreateDialog);
 fprintf(File,"%i ",sSettings.ShowVector);
 fprintf(File,"%i ",sSettings.ShowSegment);
 fprintf(File,"%i ",sSettings.ShowSector);
 fprintf(File,"%i ",sSettings.ShowLighting);
 fprintf(File,"%i ",sSettings.BlockSize);
 fprintf(File,"%f ",sSettings.Constant_Attenuation);
 fprintf(File,"%f ",sSettings.Linear_Attenuation);
 fprintf(File,"%f ",sSettings.Quadric_Attenuation);
 fprintf(File,"%i ",sSettings.R_Ambient);
 fprintf(File,"%i ",sSettings.G_Ambient);
 fprintf(File,"%i ",sSettings.B_Ambient);
 fprintf(File,"%i ",sSettings.R_Fog);
 fprintf(File,"%i ",sSettings.G_Fog);
 fprintf(File,"%i ",sSettings.B_Fog);
 fprintf(File,"%i ",sSettings.Fog_Density);
 fprintf(File,"%i ",sSettings.Fog_Enable);
 fclose(File);
}
void CWnd_Form::LoadMap(char *FileName)
{
 FILE *File=fopen(FileName,"r+b");
 if (File==NULL)
 {
  MessageBox(hWnd,"Не могу открыть файл.","Ошибка чтения",MB_OK|MB_ICONSTOP);
  return;
 }
 Initialize();
 cDialog_CreateLighting.Initialize();
 cDialog_CreatePolygon.Initialize();
 StartPoscWnd_Form.Initialize();
 cDialog_CreateSegment.Initialize();
 cDialog_CreateSimplySector.Initialize();
 cDialog_CreateSegment.LoadSegment(File);
 fclose(File);
 File=fopen(FileName,"r+b");
 cDialog_CreateLighting.LoadLighting(File);
 fclose(File);
 //работа с секторами
 File=fopen(FileName,"r+b");
 cDialog_CreateSimplySector.LoadSector(File);
 fclose(File);
 File=fopen(FileName,"r+b");
 cDialog_CreateSimplyDoor.LoadSector(File);
 fclose(File);
 //работа с секторами
 File=fopen(FileName,"r+b");
 StartPoscWnd_Form.LoadStartPosition(File);
 fclose(File);
 File=fopen(FileName,"r+b");
 if (GetReadPos(File,"EDITOR SETTING"))
 {
  xLeftMap=(int)ReadNumber(File);
  yTopMap=(int)ReadNumber(File);
  sSettings.ShowSegmentCreateDialog=(int)ReadNumber(File);
  if (sSettings.ShowSegmentCreateDialog==0) CheckBox_ShowDialog.SetStateOff();
  else CheckBox_ShowDialog.SetStateOn();
  sSettings.ShowVector=(int)ReadNumber(File);
  if (sSettings.ShowVector==1) SetMenuItem(hSettingMenu,FORM_MENU_SETTING_VECTOR,MFS_CHECKED,FALSE);
  else SetMenuItem(hSettingMenu,FORM_MENU_SETTING_VECTOR,MFS_UNCHECKED,FALSE);
  sSettings.ShowSegment=(int)ReadNumber(File);
  if (sSettings.ShowSegment==1) SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWSSegment,MFS_CHECKED,FALSE);
  else SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWSSegment,MFS_UNCHECKED,FALSE);
  sSettings.ShowSector=(int)ReadNumber(File);
  if (sSettings.ShowSector==1) SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWSECTOR,MFS_CHECKED,FALSE);
  else SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWSECTOR,MFS_UNCHECKED,FALSE);
  sSettings.ShowLighting=(int)ReadNumber(File);
  if (sSettings.ShowLighting==1) SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWSLighting,MFS_CHECKED,FALSE);
  else SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWSLighting,MFS_UNCHECKED,FALSE);
  sSettings.BlockSize=(int)ReadNumber(File);
  sSettings.Constant_Attenuation=ReadNumber(File);
  sSettings.Linear_Attenuation=ReadNumber(File);
  sSettings.Quadric_Attenuation=ReadNumber(File);
  sSettings.R_Ambient=(int)ReadNumber(File);
  sSettings.G_Ambient=(int)ReadNumber(File);
  sSettings.B_Ambient=(int)ReadNumber(File);
  sSettings.R_Fog=(int)ReadNumber(File);
  sSettings.G_Fog=(int)ReadNumber(File);
  sSettings.B_Fog=(int)ReadNumber(File);
  sSettings.Fog_Density=(int)ReadNumber(File);
  sSettings.Fog_Enable=(int)ReadNumber(File);
 }
 fclose(File);
 cWnd_Menu.UpDate();
 cWnd_Menu.Static_Text2.SetText("-");
 InvalidateRect(hWnd,NULL,FALSE);
}
//------------------------------------------------------------------------------
void CWnd_Form::Initialize(void)
{
 xLeftMap=0;//коордитата левого угла карты
 yTopMap=0;//координата верхнего угла карты
 MapMove=0;//режим прокрутки карты
  
 sKeyData.PrimaryMode=0;//первичный режим работы
 sKeyData.SecondaryMode=0;//вторичный режим работы
 sKeyData.MaximumNumberOfLine=0;//сколько всего на карте линий (линия-сегмент или линия раздела)
 sKeyData.MaximumNumberOfSimplySector=0;//сколько всего на карте обычных секторов
 sKeyData.MaximumNumberOfSimplyDoor=0;//сколько всего на карте обычных дверей
 sKeyData.MaximumNumberOfDisposableDoor=0;//сколько всего на карте одноразовых дверей
 sKeyData.MaximumNumberOfClosedDoor=0;//сколько всего на карте запертых дверей
 sKeyData.MaximumNumberOfAutoClosedDoor=0;//сколько всего на карте закрывающихся дверей
 sKeyData.MaximumNumberOfSimplyPlatform=0;//сколько всего на карте обычных платформ
 sKeyData.MaximumNumberOfInactivePlatform=0;//сколько всего на карте неактивных платформ
 sKeyData.MaximumNumberOfDisconnectPlatform=0;//сколько всего на карте отключающихся платформ
 sKeyData.MaximumNumberOfSimplyBridge=0;//сколько всего на карте обычных мостиков
 sKeyData.MaximumNumberOfSimplyTeleport=0;//сколько всего на карте обычных телепортаторов
 sKeyData.MaximumNumberOfAllSector=0;//сколько всего на карте всех секторов
 sKeyData.MaximumNumberOfLighting=0;//сколько всего на карте источников света
  
 sKeyData.MaximumPset=0;//всего точек в рисуемом блоке
 sKeyData.SelectLine=-1;//ни один сегмент не выбран
 sKeyData.SelectSector=-1;//ни один сектор не выбран
 sKeyData.SelectSectorType=-1;//ни одного типа
 sKeyData.SelectLighting=-1;//ни один источник света не выбран
 sSettings.ShowSegmentCreateDialog=1;//диалог вызывается
 CheckBox_ShowDialog.SetStateOn();
 sSettings.ShowVector=0;//направление не показывается
 sSettings.ShowSegment=1;//сегменты показываются
 SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWSSegment,MFS_CHECKED,FALSE);
 sSettings.ShowSector=1;//сектора показываются
 SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWSECTOR,MFS_CHECKED,FALSE);
 sSettings.ShowLighting=1;//источники света показываются
 SetMenuItem(hSettingMenu,FORM_MENU_SETTING_SHOWSLighting,MFS_CHECKED,FALSE);
  
  
 sSettings.BlockSize=64;//размер блока разбиения
 sSettings.Constant_Attenuation=1;//постоянное ослабление света
 sSettings.Linear_Attenuation=0.0001;//линейное ослабление света
 sSettings.Quadric_Attenuation=0.00001;//квадратичное ослабление света
 sSettings.R_Ambient=32;//глобальное фоновое освещение
 sSettings.G_Ambient=32;
 sSettings.B_Ambient=32;
 sSettings.R_Fog=255;//настройки тумана
 sSettings.G_Fog=255;
 sSettings.B_Fog=255;
 sSettings.Fog_Density=2500000;
 sSettings.Fog_Enable=0;
}
int CWnd_Form::PointPosition(float x,float y,float xw1,float yw1,float xw2,float yw2)
{
 float p=x*(yw1-yw2)-y*(xw1-xw2)+xw1*yw2-xw2*yw1;
 if (p<=-EPS) p=-1;
 if (p>=EPS) p=1;
 if (p>-EPS && p<EPS) p=0;
 return((int)(p));
}
int CWnd_Form::SectorGamber(void)
{
 for(int n=0;n<=sKeyData.MaximumPset-1;n++)
 {
  int p1=n;
  int p2=n+1;
  if (p2>=sKeyData.MaximumPset-1) p2=0;
  float x1=(float)(sKeyData.X[p1]);//выбрали сторону многоугольника
  float y1=(float)(sKeyData.Y[p1]);
  float x2=(float)(sKeyData.X[p2]);
  float y2=(float)(sKeyData.Y[p2]);
  int pos=0;
  for(int m=0;m<sKeyData.MaximumPset-1;m++)
  {
   if (m==n) continue;
   float x=(float)(sKeyData.X[m]);//выбрали точку многоугольника
   float y=(float)(sKeyData.Y[m]);
   int res=PointPosition(x,y,x1,y1,x2,y2);
   if (res==0) continue;
   if (pos==0) pos=res;
   if (pos*res<0) return(0);//не выпуклый
  }
 }
 return(1);//выпуклый
}
void CWnd_Form::GetSelectLine(int x,int y,int frontier)
{
 if (!(x>=0 && x<=499 && y>=0 && y<=499)) return;
 sKeyData.SelectLine=cDialog_CreateSegment.GetLineInScreen((int)(x+xLeftMap*10.0),(int)(y+yTopMap*10.0),frontier);
}
void CWnd_Form::GetSelectSector(int x,int y)
{
 if (!(x>=0 && x<=499 && y>=0 && y<=499)) return;
 //работа с секторами
 //проверим среди обычных секторов
 sKeyData.SelectSector=cDialog_CreateSimplySector.GetSectorInScreen((int)(x+xLeftMap*10.0),(int)(y+yTopMap*10.0));
 if (sKeyData.SelectSector!=-1)
 {
  sKeyData.SelectSectorType=0;
  return;
 }
 //проверим среди обычных дверей
 sKeyData.SelectSector=cDialog_CreateSimplyDoor.GetSectorInScreen((int)(x+xLeftMap*10.0),(int)(y+yTopMap*10.0));
 if (sKeyData.SelectSector!=-1) 
 {
  sKeyData.SelectSectorType=1;
  return;
 }
 //работа с секторами
}
void CWnd_Form::GetSelectLighting(int x,int y)
{
 if (!(x>=0 && x<=499 && y>=0 && y<=499)) return;
 sKeyData.SelectLighting=cDialog_CreateLighting.GetLightingInScreen((int)(x+xLeftMap*10.0),(int)(y+yTopMap*10.0));
}
void CWnd_Form::LoadTexture(char *FileName)
{
 int n;
 unsigned char R[256];
 unsigned char G[256];
 unsigned char B[256];
 FILE *file=fopen(FileName,"r+b");
 if (file!=NULL)
 {
  sKeyData.MaximumTexture=(unsigned short)LoadShort(file);
  if (sKeyData.MaximumTexture<=0)
  {
   sKeyData.MaximumTexture=0;
   fclose(file);
   return;
  }
  //теперь пропустим таблицу смещений текстур (здесь она не нужна)
  for(n=0;n<sKeyData.MaximumTexture;n++) LoadInt(file);
  //и загрузим сами текстуры
  sKeyData.TextureMap=new STextureMap[sKeyData.MaximumTexture];
  for (n=0;n<sKeyData.MaximumTexture;n++)
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
    sKeyData.TextureMap[n].Size=(unsigned short)LoadShort(file);
    sKeyData.TextureMap[n].R=new unsigned char[sKeyData.TextureMap[n].Size*sKeyData.TextureMap[n].Size];
    sKeyData.TextureMap[n].G=new unsigned char[sKeyData.TextureMap[n].Size*sKeyData.TextureMap[n].Size];
    sKeyData.TextureMap[n].B=new unsigned char[sKeyData.TextureMap[n].Size*sKeyData.TextureMap[n].Size];
    for(int x=0;x<sKeyData.TextureMap[n].Size;x++)
    for(int y=0;y<sKeyData.TextureMap[n].Size;y++)
    {
     int byte=(unsigned char)LoadChar(file);
     int offset=x*sKeyData.TextureMap[n].Size+y;
     sKeyData.TextureMap[n].R[offset]=R[byte];
     sKeyData.TextureMap[n].G[offset]=G[byte];
     sKeyData.TextureMap[n].B[offset]=B[byte];
    }
   }
   if (ColorMode==2)//RGB цвета
   {
    sKeyData.TextureMap[n].Size=(unsigned short)LoadShort(file);
    sKeyData.TextureMap[n].R=new unsigned char[sKeyData.TextureMap[n].Size*sKeyData.TextureMap[n].Size];
    sKeyData.TextureMap[n].G=new unsigned char[sKeyData.TextureMap[n].Size*sKeyData.TextureMap[n].Size];
    sKeyData.TextureMap[n].B=new unsigned char[sKeyData.TextureMap[n].Size*sKeyData.TextureMap[n].Size];
    for(int x=0;x<sKeyData.TextureMap[n].Size;x++)
    for(int y=0;y<sKeyData.TextureMap[n].Size;y++)
    {
     unsigned char r=(unsigned char)LoadChar(file);
     unsigned char g=(unsigned char)LoadChar(file);
     unsigned char b=(unsigned char)LoadChar(file);
     int offset=x*sKeyData.TextureMap[n].Size+y;
     sKeyData.TextureMap[n].R[offset]=r;
     sKeyData.TextureMap[n].G[offset]=g;
     sKeyData.TextureMap[n].B[offset]=b;
    }
   }
   /*
   //для сохранения текстур в tga-файлах
   unsigned char *image=new unsigned char[sKeyData.TextureMap[n].Size*sKeyData.TextureMap[n].Size*4];
   for(int x=0;x<sKeyData.TextureMap[n].Size;x++)
   {
    for(int y=0;y<sKeyData.TextureMap[n].Size;y++)
	{
     int offset=x*sKeyData.TextureMap[n].Size+y;
     image[(x+y*sKeyData.TextureMap[n].Size)*3]=sKeyData.TextureMap[n].B[offset];
     image[(x+y*sKeyData.TextureMap[n].Size)*3+1]=sKeyData.TextureMap[n].G[offset];
     image[(x+y*sKeyData.TextureMap[n].Size)*3+2]=sKeyData.TextureMap[n].R[offset];
	}
   }
   char filename[255];
   sprintf(filename,"texture\\%i.tga",n+1);
   SaveTGA(filename,sKeyData.TextureMap[n].Size,sKeyData.TextureMap[n].Size,image);
   delete[](image);*/
  }
  fclose(file);
 }
 else sKeyData.MaximumTexture=0;
}
 

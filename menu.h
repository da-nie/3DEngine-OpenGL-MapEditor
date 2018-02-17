#ifndef MENU_H
#define MENU_H

#include <windows.h>

//*************************************************************************************************************************
//Функции для работы с меню
//*************************************************************************************************************************
BOOL CreateMenuItem(HMENU hMenu,char *str,UINT uIns,UINT uCom,HMENU hSubMenu,BOOL flag,UINT fType);
BOOL SetMenuItem(HMENU hMenu,UINT uIns,UINT fState,BOOL flag);

#endif
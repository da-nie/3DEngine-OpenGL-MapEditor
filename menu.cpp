#include "menu.h"

//*************************************************************************************************************************
//Функции для работы с меню
//*************************************************************************************************************************
BOOL CreateMenuItem(HMENU hMenu,char *str,UINT uIns,UINT uCom,HMENU hSubMenu,BOOL flag,UINT fType)
{
 MENUITEMINFO mii;
 mii.cbSize=sizeof(MENUITEMINFO);
 mii.fMask=MIIM_STATE|MIIM_TYPE|MIIM_SUBMENU|MIIM_ID;
 mii.fType=fType;
 mii.fState=MFS_ENABLED;
 mii.dwTypeData=str;
 mii.cch=sizeof(str);
 mii.wID=uCom;
 mii.hSubMenu=hSubMenu;
 return(InsertMenuItem(hMenu,uIns,flag,&mii));
}
BOOL SetMenuItem(HMENU hMenu,UINT uIns,UINT fState,BOOL flag)
{
 MENUITEMINFO mii;
 mii.cbSize=sizeof(MENUITEMINFO);
 mii.fMask=MIIM_STATE|MIIM_ID;
 mii.fState=fState;
 mii.wID=uIns;
 return(SetMenuItemInfo(hMenu,uIns,flag,&mii));
}

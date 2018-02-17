#include "fileprocess.h"

void CFileProcessed::Create(HWND hWnd)
{
 strcpy(CustomFilter,"");
 strcpy(FileName,"");
 strcpy(FileTitle,"");
 GetCurrentDirectory(1024,InitialDir);
 strcpy(DefExtension,"");
 strcpy(Title,"");
 OFN.hwndOwner=hWnd;
 OFN.lStructSize=sizeof(OPENFILENAME);
 OFN.lpstrFilter=NULL;
 OFN.lpstrCustomFilter=CustomFilter;
 OFN.nMaxCustFilter=1024;
 OFN.nFilterIndex=1;
 OFN.lpstrFile=FileName;
 OFN.nMaxFile=1024;
 OFN.lpstrFileTitle=FileTitle;
 OFN.nMaxFileTitle=1024;
 OFN.lpstrInitialDir=InitialDir;
 OFN.lpstrTitle=Title;
 OFN.nFileOffset=0;
 OFN.nFileExtension=0;
 OFN.lpstrDefExt=DefExtension;
 OFN.Flags=OFN_EXPLORER|OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST|OFN_OVERWRITEPROMPT;
 OFN.lpfnHook=(LPOFNHOOKPROC)NULL;
 OFN.lpTemplateName=NULL;
 OFN.lCustData=0;
}
int CFileProcessed::Open(void)
{
 int result=GetOpenFileName(&OFN);
 GetCurrentDirectory(1024,InitialDir);
 OFN.lpstrInitialDir=InitialDir;
 return(result);
}
int CFileProcessed::Save(void)
{
 int result=GetSaveFileName(&OFN);
 GetCurrentDirectory(1024,InitialDir);
 OFN.lpstrInitialDir=InitialDir;
 return(result);
}
void CFileProcessed::SetFilter(char *filter)
{
 OFN.lpstrFilter=filter;
}
int CFileProcessed::StartOpen(char *BarName,char *Filter)
{
 strcpy(Title,BarName);
 SetFilter(Filter);
 return(Open());
}
int CFileProcessed::StartSave(char *BarName,char *Filter)
{
 strcpy(Title,BarName);
 SetFilter(Filter);
 return(Save());
}
void CFileProcessed::SetTitle(char *title)
{
 strcpy(Title,title);
}

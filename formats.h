#ifndef CWnd_FormATS_H
#define CWnd_FormATS_H
 
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
 
void SaveInt(FILE *file,int arg);
int LoadInt(FILE *file);
void SaveShort(FILE *file,short arg);
short LoadShort(FILE *file);
void SaveChar(FILE *file,char arg);
char LoadChar(FILE *file);
void SaveFloat(FILE *file,float arg);
float LoadFloat(FILE *file);
int GetReadPos(FILE *File,char *SearchString);
float ReadNumber(FILE *File);
 
#endif

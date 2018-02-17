#include "formats.h"
 
//============================================================================
void SaveInt(FILE *file,int arg)
{
 fwrite(&arg,1,sizeof(int),file);
}
int LoadInt(FILE *file)
{
 int arg;
 fread(&arg,1,sizeof(int),file);
 return(arg);
}
//============================================================================
void SaveShort(FILE *file,short arg)
{
 fwrite(&arg,1,sizeof(short),file);
}
short LoadShort(FILE *file)
{
 short arg;
 fread(&arg,1,sizeof(short),file);
 return(arg);
}
//============================================================================
void SaveChar(FILE *file,char arg)
{
 fwrite(&arg,1,sizeof(char),file);
}
char LoadChar(FILE *file)
{
 char arg;
 fread(&arg,1,sizeof(char),file);
 return(arg);
}
//============================================================================
void SaveFloat(FILE *file,float arg)
{
 fwrite(&arg,1,sizeof(float),file);
}
float LoadFloat(FILE *file)
{
 float arg;
 fread(&arg,1,sizeof(float),file);
 return(arg);
}
//============================================================================
int GetReadPos(FILE *File,char *SearchString)
{
 unsigned char byte;
 unsigned int pos=0;
 while(1)
 {
  if (fread(&byte,1,1,File)==0) break;
  if (byte==SearchString[pos]) pos++;
  else pos=0;
  if (pos==strlen(SearchString)) return(1);
 }
 return(0);
}
float ReadNumber(FILE *File)
{
 int len=0;
 char byte;
 char string[4096];
 while(1)
 {
  if (fread(&byte,1,1,File)==0) break;
  if (len==0)
  {
   if ((byte<'0' || byte>'9') && byte!='-' && byte!='+' && byte!='.' && byte!='e' && byte!='E') continue;
   string[len]=byte;
   len++;
  }
  else
  {
   if ((byte<'0' || byte>'9') && byte!='-' && byte!='+' && byte!='.' && byte!='e' && byte!='E') break;
   string[len]=byte;
   len++;
  }
 }
 string[len]=0;
 if (len==0) return(0);
 return((float)atof(string));
}

#ifndef BUTTON_H
#define BUTTON_H
 
#include <windows.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "resource.h"
 
//*************************************************************************************************************************
//Класс для кнопки 
//*************************************************************************************************************************
#define ON      1000
#define OFF     1001
#define DISABLE 1002
//------------------------------------------------------------------------------
class CButton//класс кнопки
{
 public:
  HWND Handle;//дескриптор кнопки
  void Create(int x,int y,int cx,int cy,char *Name,int iD,long Style,HWND hWnd,HINSTANCE hInstance);
  void SetStateOn(void);
  void SetStateOff(void);
  int GetState(void);
  void Enable(void);
  void Disable(void);
};
//------------------------------------------------------------------------------
class RADIOCButton
{
 public:
  HWND Handle;
  void Create(int x,int y,int cx,int cy,char *Name,int iD,long Style,HWND hWnd,HINSTANCE hInstance);
  void SetStateOn(void);
  void SetStateOff(void);
  void SetStateDisable(void);
  int GetState(void);
  void Enable(void);
  void Disable(void);
};
//------------------------------------------------------------------------------
class CCheckBox
{
 public:
  HWND Handle;
  void Create(int x,int y,int cx,int cy,char *Name,int iD,long Style,HWND hWnd,HINSTANCE hInstance);
  void SetStateOn(void);
  void SetStateOff(void);
  void SetStateDisable(void);
  int GetState(void);
  void Enable(void);
  void Disable(void);
};
//------------------------------------------------------------------------------
class CCheckBox3STATE
{
 public:
  HWND Handle;
  void Create(int x,int y,int cx,int cy,char *Name,int iD,long Style,HWND hWnd,HINSTANCE hInstance);
  void SetStateOn(void);
  void SetStateOff(void);
  void SetStateDisable(void);
  int GetState(void);
  void Enable(void);
  void Disable(void);
};
 
#endif

#ifndef COMMON_H
#define COMMON_H
 
#include <windows.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "resource.h"
 
#define M_PI 3.141592654
#define EPS  0.00001
//------------------------------------------------------------------------------
struct SETUP//настройки редактора
{
 int ShowSegmentCreateDialog;//1-диалог создания сегмента показывается,0-нет
 int ShowVector;//1-направление линии показывается
 int ShowSegment;//1-сегменты показываются
 int ShowSector;//1-сектора показываются
 int ShowLighting;//1-источники света показываются
 int BlockSize;//размер блока разбиения
 double Constant_Attenuation;//постоянное ослабление света
 double Linear_Attenuation;//линейное ослабление света
 double Quadric_Attenuation;//квадратичное ослабление света
 unsigned char R_Ambient;//глобальное фоновое освещение
 unsigned char G_Ambient;
 unsigned char B_Ambient;
  
 unsigned char R_Fog;//цвет тумана
 unsigned char G_Fog;
 unsigned char B_Fog;
 int Fog_Density;//густота тумана
 int Fog_Enable;//1-туман включён
};
struct TEXTURE_MAP
{
 int Size;//размер текстуры по X и по Y (текстура всегда квадратная и кратна степени 2)
 unsigned char *R;//цвета текстуры
 unsigned char *G;
 unsigned char *B;
};
struct KEY_DATA//ключевая информация
{
 int PrimaryMode;//первичный режим работы
 int SecondaryMode;//вторичный режим работы
 int MaximumNumberOfLine;//сколько всего на карте линий (линия-сегмент или линия раздела)
 int MaximumNumberOfSimplySector;//сколько всего на карте обычных секторов
 int MaximumNumberOfSimplyDoor;//сколько всего на карте обычных дверей
 int MaximumNumberOfDisposableDoor;//сколько всего на карте одноразовых дверей
 int MaximumNumberOfClosedDoor;//сколько всего на карте запертых дверей
 int MaximumNumberOfAutoClosedDoor;//сколько всего на карте закрывающихся дверей
 int MaximumNumberOfSimplyPlatform;//сколько всего на карте обычных платформ
 int MaximumNumberOfInactivePlatform;//сколько всего на карте неактивных платформ
 int MaximumNumberOfDisconnectPlatform;//сколько всего на карте отключающихся платформ
 int MaximumNumberOfSimplyBridge;//сколько всего на карте обычных мостиков
 int MaximumNumberOfSimplyTeleport;//сколько всего на карте обычных телепортаторов
 int MaximumNumberOfAllSector;//сколько всего на карте всех секторов
 int MaximumNumberOfLighting;//сколько всего на карте источников света
  
 int MaximumTexture;//максимальное число загруженных текстур
 TEXTURE_MAP *TextureMap;
  
 int X[1000];//координаты рисуемого блока
 int Y[1000];
 int MaximumPset;//всего точек в рисуемом блоке
 int SelectLine;//номер выбранного сегмента
 int SelectLighting;//номер выбранного источника света
 int SelectSector;//номер выбранного сектора
 int SelectSectorType;//тип выбранного сектора
 HWND hWndMain;//дескриптор главной формы(нужен для её перерисовки дочерними окнами)
 HWND hWndMenu;//дескриптор окна управления(нужен для блокирования его другими окнами)
 HWND hWndProgress;//дескриптор окна прогресса рендеринга(нужен для его обновления)
};
//------------------------------------------------------------------------------
//Список режимов работы (Primary,Secondary)
//0,0-ничего
//1,0-создание сегментов
//1,1-создание линий раздела
//2,0-создание обычного сектора
//2,1-создание обычной двери
//2,2-создание одноразовой двери
//2,3-создание запертой двери
//2,4-создание запирающейся двери
//2,5-создание простой платформы
//2,6-создание неактивной платформы
//2,7-создание отключающейся платформы
//2,8-создание простого мостика
//2,9-создание простого телепортатора
//3,0-создание источника света
//4,0-задание параметров стартовой позиции
//5,0-создание правильного многоугольника
//5,1-создание звезды
//6,0-удаление сегментов
//7,0-удаление секторов
//8,0-удаление источников света
//9,0-модификация сегментов
//10,0-модификация секторов
//11,0-модификация источников света
//------------------------------------------------------------------------------
 
#endif
 
 

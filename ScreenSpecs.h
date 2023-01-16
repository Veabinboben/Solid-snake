#pragma once
//
// VALUES ASSIGNED IN MAIN EXEC.CPP
//
extern HANDLE console ; // хэндл консоли
extern COORD cord ; // размер поля вывода (вроде нигде не используется :) )

extern double aspect; // соотношение сторон
extern bool ison; //идет ли игра

//разрешение
extern int horiz; 
extern int vert;

// размер поля
extern int gamefieldsize;

//массив всех "пиклселей" экрана
extern CHAR_INFO* display;
//массив всех "пиклселей" поля
extern wchar_t* gamefield;

void GameKill();

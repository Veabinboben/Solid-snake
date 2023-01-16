#pragma once
//
// VALUES ASSIGNED IN MAIN EXEC.CPP
//
extern HANDLE console ;
extern COORD cord ;

extern double aspect;
extern bool ison;

extern int horiz;
extern int vert;

extern int gamefieldsize;

extern CHAR_INFO* display;

extern wchar_t* gamefield;

void GameKill();

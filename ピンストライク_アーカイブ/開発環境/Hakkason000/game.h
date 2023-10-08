//**************************************************
//
//ゲーム画面
//Author::Takano Minto
//
//**************************************************
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//==================================================
//プロトタイプ宣言
//==================================================
void InitGame();
void UninitGame();
void UpdateGame();
void DrawGame();
void SetEnablePause(bool bPause);
int GetSoundNumber();

#endif // !_GAME_H_



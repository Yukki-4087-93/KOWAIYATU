//**************************************************
//
//サウンド
//Author::Takano Minto
//
//**************************************************
#ifndef _SOUND_H_
#define _SOUND_H_

//==================================================
// インクルードファイル
//==================================================
#include "xaudio2.h"

//==================================================
// サウンドファイル
//==================================================
typedef enum
{
	SOUND_LABEL_GAME1 = 0,				// BGM0
	SOUND_LABEL_GAME2,				// BGM1
	SOUND_LABEL_GAME3,				// BGM2
	SOUND_LAVEL_Ex,
	SOUND_LAVEL_Ex2,
	Sound_LAVEL_ATitle,
	Sound_LAVEL_ATitle2,
	SOUND_LABEL_SHOT,				// SE0
	SOUND_LABEL_HIT,				// SE1
	SOUND_LABEL_START,				// SE2
	SOUND_LABEL_LAUGH_GHOST,		// SE3
	SOUND_LABEL_LAUGH_YOSHIKO,		// SE4
	SOUND_LAVEL_LAUGH_YOSHIKO2,
	SOUND_LAVEL_HIMEI,
	SOUND_LAVEL_ARIGATO,
	SOUND_LAVEL_SEEYOU,
	SOUND_LAVEL_WARAIGOE,
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//==================================================
// プロトタイプ宣言
//==================================================
void InitSound();
void UninitSound();
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopAll();
void SetVolume(SOUND_LABEL lavel,float vol);
void SetPitch(SOUND_LABEL lavel, float pih);

#endif

//**************************************************
//
//インプット
//Author::Takano Minto
//
//**************************************************
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//==================================================
//キーの種類
//==================================================
typedef enum
{
	JOYKEY_UP = 0,			//十字キー上
	JOYKEY_DOWN,			//十字キー下
	JOYKEY_LEFT,			//十字キー左
	JOYKEY_RIGHT,			//十字キー右
	JOYKEY_STRTE,			//スタ-ト
	JOYKEY_BACK,			//バック
	JOYKEY_LPUSH,			//Lトリガー
	JOYKEY_RPUSH,			//Rトリガー
	JOYKEY_L1,				//L1ボタン
	JOYKEY_R1,				//R1ボタン
	JOYKEY_L2,				//L2ボタン
	JOYKEY_R2,				//R2ボタン
	JOYKEY_A,				//Aボタン
	JOYKEY_B,				//Bボタン
	JOYKEY_X,				//Xボタン
	JOYKEY_Y,				//Yボタン
	MAX_KEY
}JOYkey;

//==================================================
//プロトタイプ宣言
//==================================================
HRESULT Initkeyboard(HINSTANCE hInstance, HWND hWnd);
void Uninitkeyboard();
void Updatekeyboard();
bool GetkeyboardPress(int nkey);
bool GetkeyboardTrigger(int nkey);
HRESULT InitJoypad();
void UninitJoypad();
void UpdateJoypad();
bool GetJoypadPress(JOYkey key);
bool GetJoypadTrigger(JOYkey key);

#endif // !_INPUT_H_


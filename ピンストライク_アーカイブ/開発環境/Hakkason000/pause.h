//**************************************************
//
//ポーズ
//Author::Takano Minto
//
//**************************************************
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

//==================================================
//ポーズメニューの構造体
//==================================================
typedef enum
{
	POUSE_MENU_COUNTINUE = 0,
	POUSE_MENU_RETRY,
	POUSE_MENU_QUIT,
	POUSE_MENU_MAX
}PAUSE_MENU;

//==================================================
//ポーズの構造体の定義
//==================================================
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXCOLOR col;							//イロハ
}PAUSE;

//==================================================
//プロトタイプ宣言
//==================================================
void InitPause();
void UninitPause();
void UpdatePause();
void DrawPause();

#endif // !_PAUSE_H_


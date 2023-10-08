//==========================================================
//
//プレイヤーの描画処理[player.h]
//Author:チームK2MT
//
//==========================================================

#ifndef _PLAYER_H_ //このマクロ定義がされていなかったら
#define _PLAYER_H_ //2重インクルード防止のマクロ定義

//include
#include "main.h"

//マクロ定義
#define MAX_PLAYER		(2)		//プレイヤーの最大数
#define NUM_PLAYER		(2)		//プレイヤーの種類(左右反転用で使用)
#define PLAYER_WIDTH	(200.0f)	//プレイヤーの幅
#define PLAYER_HEIGHT	(200.0f)	//プレイヤーの高さ


//構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotOld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 moveOld;
	D3DXCOLOR col;
	float fLength;							//対角線の長さ
	float fAngle;							//対角線の角度
	bool bUse;
}Player;

//プロトタイプ宣言
void InitPlayer(void);		//プレイヤーの初期化処理
void UninitPlayer(void);	//プレイヤーの終了処理
void UpdatePlayer(void);	//プレイヤーの更新処理
void DrawPlayer(void);		//プレイヤーの描画処理
void SetPlayerLeft(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//プレイヤーの設定処理
#endif
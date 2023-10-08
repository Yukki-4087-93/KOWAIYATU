//==========================================================
//
//スコアの描画処理[score.h]
//Author:チームK2MT
//
//==========================================================

#ifndef _SCORE_H_ //このマクロ定義がされていなかったら
#define _SCORE_H_ //2重インクルード防止のマクロ定義

//include
#include "main.h"

//スコアの構造体の定義
typedef struct
{
	D3DXVECTOR3 pos; //スコアの位置
	bool bUse;        //スコアを使用しているかどうか
}Score;

//プロトタイプ宣言
void InitScore(void); //スコアの初期化処理
void UninitScore(void); //スコアの終了処理
void UpdateScore(void); //スコアの更新処理
void DrawScore(void);   //スコアの描画処理
void SetScorePos(D3DXVECTOR3 pos); //スコアの設定処理
void AddScore(int nValue);	//スコアの加算処理
int GetScore(void);		//スコアの取得

//マクロ定義
#define SCORE_WIDTH	(50)   //スコアの1桁の幅
#define SCORE_HEIGHT	(50)   //スコアの1桁の高さ
#define MAX_SCORE	(8) //スコアの最大桁数


#endif
//**************************************************
//
//ランキング処理
//Author:チームK2MT
//
//**************************************************
#ifndef _RANKINGSCORE_H_
#define _RANKINGSCORE_H_

//include
#include "main.h"

//==================================================
//マクロ定義
//==================================================
#define MAX_RANK	(8)	//最大ランク数
#define MAX_DIGIT	(8)	//最大桁数
#define MAX_RANKWIDTH	(30.0f)	//ランキング1桁分の幅
#define MAX_RANKHEIGHT	(30.0f)	//ランキング1桁分の高さ

//==================================================
//ランキングの構造体
//==================================================
typedef struct
{
	D3DXVECTOR3 pos;				//位置
	D3DXCOLOR col;					//カラー
	int nScore;						//スコア
	int nScorePos;					//テクスチャの位置
	bool bRight;					//新しくランクインしたら光らせる用
}RankScore;

//プロトタイプ宣言
void InitRanking();		//ランキングの初期化処理
void UninitRanking();	//ランキングの終了処理
void UpdateRanking();	//ランキングの更新処理
void DrawRanking();		//ランキングの描画処理
void ResetRanking();	//ランキングのリセット処理
void SetRanking(int nScore);	//ランキングの設定処理


#endif
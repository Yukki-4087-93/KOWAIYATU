//**************************************************
//
//ピンボール
//Author::Takano Minto
//
//**************************************************
#ifndef _PINBALL_H_
#define _PINBALL_H_

#include "main.h"

//==================================================
//ピンボールの構造体の定義
//==================================================
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
}PINBALL;

//==================================================
//プロトタイプ宣言
//==================================================
void InitPinball();				//初期化
void UninitPinball();			//終了
void UpdatePinball();			//更新
void DrawPinball();				//描画
void HitPinball();				//当たり判定
void DestPinBall();				//ピンボールの消える位置の設定
bool PinCollision(D3DXVECTOR3 pos1, float fRadius1, D3DXVECTOR3 pos2, float fRadius2);
void SetPinBall(D3DXVECTOR3 pos);

#endif // !_PINBALL_H_


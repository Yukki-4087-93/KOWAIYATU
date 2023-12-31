//**************************************************
//
//障害物
//Author::Takano Minto
//
//**************************************************
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

//==================================================
//インクルードファイル
//==================================================
#include "main.h"

//==================================================
//構造体
//==================================================
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//角度
	D3DXVECTOR3 siz;		//サイズ
	D3DXCOLOR col;			//色
}OBSTACLE;

//==================================================
//プロトタイプ宣言
//==================================================
void InitObstacle();
void UninitObstacle();
void UpdateObstacle();
void DrawObstacle();

#endif // !_OBSTACLE_H_


//**************************************************
//
//背景画面
//Author::Takano Minto
//
//**************************************************

//==================================================
//インクルードファイル
//==================================================
#include"pinball.h"
#include "input.h"
#include "enemy.h"

//==================================================
//定数定義
//==================================================
const float Gravity = 0.3f;
const float WD_PINBALL = 20.0f;
const float HI_PINBALL = 20.0f;

//==================================================
//プロトタイプ宣言
//==================================================
void MoveUp();

//==================================================
//グローバル変数
//==================================================
PINBALL g_pinball;								// ピンボールのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePinball = NULL;			// テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPinball = NULL;	// 頂点バッファへのポインタ
bool g_bMoveDown;	//落下するかしないか
int g_nCountDown;	//落下するまでのカウンター

//==================================================
//初期化
//==================================================
void InitPinball()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//デバイスのポインタ

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPinball, NULL);

	{// 構造体の初期化
		g_pinball.pos = D3DXVECTOR3(0.0f,0.0f,0.0f);		// 位置の初期化
		g_pinball.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 過去の位置の初期化
		g_pinball.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 角度の初期化
		g_pinball.rotOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 過去の角度の初期化
		g_pinball.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期化
		g_pinball.moveOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 過去の移動量の初期化
		g_pinball.col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);		// 色の初期化
		g_pinball.bUse = false;
	}

	g_bMoveDown = true;
	g_nCountDown = 0;

	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//bullet000.png", &g_pTexturePinball);

	VERTEX_2D* pVtx;			//頂点情報へのポインタ

	//頂点バッファをコック＆ロックし、頂点情報へのポインタを取得
	g_pVtxBuffPinball->Lock(0, 0, (void**)&pVtx, 0);

	//対角線の長さを算出する
	g_pinball.fLength = sqrtf(WD_PINBALL * WD_PINBALL + HI_PINBALL * HI_PINBALL);

	//対角線の角度を算出する
	g_pinball.fAngle = atan2f(HI_PINBALL, WD_PINBALL);

	//頂点座標の設定
	pVtx[0].pos.x = g_pinball.pos.x - WD_PINBALL / 2;
	pVtx[0].pos.y = g_pinball.pos.y - HI_PINBALL;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_pinball.pos.x + WD_PINBALL / 2;
	pVtx[1].pos.y = g_pinball.pos.y - HI_PINBALL;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_pinball.pos.x - WD_PINBALL / 2;
	pVtx[2].pos.y = g_pinball.pos.y;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_pinball.pos.x + WD_PINBALL / 2;
	pVtx[3].pos.y = g_pinball.pos.y;
	pVtx[3].pos.z = 0.0f;

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テキスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPinball->Unlock();
}

//==================================================
//終了
//==================================================
void UninitPinball()
{
	//テクスチャの破棄
	if (g_pTexturePinball != NULL)
	{
		g_pTexturePinball->Release();
		g_pTexturePinball = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPinball != NULL)
	{
		g_pVtxBuffPinball->Release();
		g_pVtxBuffPinball = NULL;
	}
}

//==================================================
//更新
//==================================================
void UpdatePinball()
{
	if (g_pinball.bUse)
	{
		HitPinball();	//ヒット処理

		MoveUp();		//移動量の設定

		DestPinBall();	//ボールの位置変更
	}
}

//==================================================
//描画
//==================================================
void DrawPinball()
{
	if (g_pinball.bUse)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスのポインタを取得

		//頂点フォーマット
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePinball);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffPinball, 0, sizeof(VERTEX_2D));

		//ポリゴンの描画
		pDevice->DrawPrimitive
		(D3DPT_TRIANGLESTRIP,
			0,
			2);
	}
}

//==================================================
//当たり判定
//==================================================
void SetPinBall(D3DXVECTOR3 pos)
{
	if (!g_pinball.bUse)
	{
		InitPinball();
		g_pinball.pos = pos;
		g_pinball.bUse = true;
	}
}

//==================================================
//当たり判定
//==================================================
void HitPinball()
{
	Enemy* pEnemy = GetEnemy();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{//エネミーが使用されている
			if (g_pinball.pos.x >= pEnemy->pos.x - ENEMY_SIZE - WD_PINBALL &&
				g_pinball.pos.x <= pEnemy->pos.x + ENEMY_SIZE + WD_PINBALL &&
				g_pinball.pos.y >= pEnemy->pos.y - ENEMY_SIZE - WD_PINBALL &&
				g_pinball.pos.y <= pEnemy->pos.y + ENEMY_SIZE + WD_PINBALL)
			{//プレイヤーの中心にエネミーと弾のサイズ（各半分）を＋ーした範囲に弾が当たった時
			 //エネミーのヒット処理
				HitEnemy(nCntEnemy, 1);

				g_pinball.bUse = false;			//使用されていない状態にする
			}
		}
	}
}

//==================================================
//死亡処理
//==================================================
void DestPinBall()
{
	if (g_pinball.pos.y <= 0.0f)
	{
		g_pinball.move.y = 0.0f;

		g_pinball.bUse = false;
	}
}

//==================================================
//下に行く処理
//==================================================
void MoveUp()
{
	VERTEX_2D* pVtx;			//頂点情報へのポインタ

	//頂点バッファをコック＆ロックし、頂点情報へのポインタを取得
	g_pVtxBuffPinball->Lock(0, 0, (void**)&pVtx, 0);

	// 重力
	g_pinball.move.y -= Gravity;

	// 前回の位置を保存
	g_pinball.posOld = g_pinball.pos;

	g_pinball.moveOld = g_pinball.move;

	if (g_bMoveDown)
	{
		// 位置を更新
		g_pinball.pos.x += g_pinball.move.x;
		g_pinball.pos.y += g_pinball.move.y;
	}

	////移動量を更新
	//g_pinball.move.x += (0.0f - g_pinball.move.x) * PLAYER_INERTIA;

	//頂点座標の設定
	pVtx[0].pos.x = g_pinball.pos.x - WD_PINBALL / 2;
	pVtx[0].pos.y = g_pinball.pos.y - HI_PINBALL;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_pinball.pos.x + WD_PINBALL / 2;
	pVtx[1].pos.y = g_pinball.pos.y - HI_PINBALL;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_pinball.pos.x - WD_PINBALL / 2;
	pVtx[2].pos.y = g_pinball.pos.y;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_pinball.pos.x + WD_PINBALL / 2;
	pVtx[3].pos.y = g_pinball.pos.y;
	pVtx[3].pos.z = 0.0f;

	//頂点バッファをアンロックする
	g_pVtxBuffPinball->Unlock();
}

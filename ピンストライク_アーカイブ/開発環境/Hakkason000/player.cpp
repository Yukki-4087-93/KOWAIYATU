//==========================================================
//
//プレイヤーの描画処理[player.cpp]
//Author:チームK2MT
//
//==========================================================

//include
#include "main.h"
#include "player.h"
#include "input.h"
#include "pinball.h"
#include "sound.h"
#include "game.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL; //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL; //頂点バッファへのポインタ
Player g_Player;					//プレイヤーの情報
float g_fLengthPlayer = 0.0f;					 //プレイヤーの対角線の長さ
float g_fAnglePlayer = 0.0f;					//プレイヤーの角度

//=======================================================================
//プレイヤーの初期化処理
//=======================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;  //デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "Data\\TEXTURE\\player.png", &g_pTexturePlayer);


		g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置の初期化
		g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期化
		g_Player.bUse = false;

	//対角線の長さを算出する
	g_fLengthPlayer = sqrtf(PLAYER_WIDTH * PLAYER_WIDTH + PLAYER_HEIGHT * PLAYER_HEIGHT) / 2.0f;

	//対角線の角度を算出する
	g_fAnglePlayer = atan2f(PLAYER_WIDTH, PLAYER_HEIGHT);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPlayer, NULL);

	VERTEX_2D* pVtx;  //頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);


	//頂点座標の設定
	pVtx[0].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (-D3DX_PI * 0.75f)) * g_fLengthPlayer;
	pVtx[0].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (-D3DX_PI * 0.75f)) * g_fLengthPlayer;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI * 0.75f)) * g_fLengthPlayer;
	pVtx[1].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI * 0.75f)) * g_fLengthPlayer;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (-D3DX_PI * 0.25f)) * g_fLengthPlayer;
	pVtx[2].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (-D3DX_PI * 0.25f)) * g_fLengthPlayer;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI * 0.25f)) * g_fLengthPlayer;
	pVtx[3].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI * 0.25f)) * g_fLengthPlayer;
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


		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);


	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();

}

//=======================================================================
//プレイヤーの終了処理
//=======================================================================
void UninitPlayer(void)
{
	//テクスチャの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//=======================================================================
//プレイヤーの更新処理
//=======================================================================
void UpdatePlayer(void)
{
	if (GetkeyboardTrigger(DIK_SPACE))
	{
		if (GetSoundNumber() % 2 == 1)
		{
			PlaySound(SOUND_LABEL_SHOT);
		}
		SetPinBall(g_Player.pos);
	}

}

//=======================================================================
//プレイヤーの描画処理
//=======================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePlayer);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2);
}

//=======================================================================
//プレイヤーの設定処理
//=======================================================================
void SetPlayerLeft(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	VERTEX_2D* pVtx;  //頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);


	if(g_Player.bUse == false)
	{
		g_Player.pos = pos;
		g_Player.rot = rot;
		g_Player.bUse = true;


		//頂点座標の設定
		pVtx[0].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (-D3DX_PI * 0.75f)) * g_fLengthPlayer;
		pVtx[0].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (-D3DX_PI * 0.75f)) * g_fLengthPlayer;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI * 0.75f)) * g_fLengthPlayer;
		pVtx[1].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI * 0.75f)) * g_fLengthPlayer;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (-D3DX_PI * 0.25f)) * g_fLengthPlayer;
		pVtx[2].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (-D3DX_PI * 0.25f)) * g_fLengthPlayer;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI * 0.25f)) * g_fLengthPlayer;
		pVtx[3].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI * 0.25f)) * g_fLengthPlayer;
		pVtx[3].pos.z = 0.0f;

	}

	//頂点バッファのアンロック
	g_pVtxBuffPlayer->Unlock();
}


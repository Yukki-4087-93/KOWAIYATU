//**************************************************
//
//リザルト画面
//Author::Takano Minto
//
//**************************************************
#include"result.h"
#include"input.h"
#include"sound.h"
#include"fade.h"
#include"ranking.h"
#include "game.h"

//==================================================
// グローバル変数
//==================================================
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;					//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;			//頂点バッファへのポインタ

//==================================================
// リザルト画面の初期化処理
//==================================================
void InitResult()
{
	LPDIRECT3DDEVICE9 pDevice;						//デバイスのポインタ

													//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult, NULL);

	D3DXCreateTextureFromFile(pDevice,
		"Data//TEXTURE//reseut0099.png",
		&g_pTextureResult);

	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをコック＆ロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT, 0.0f);

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
	g_pVtxBuffResult->Unlock();

	if (GetSoundNumber() % 2 == 0)
	{
		
	}
	else
	{
		//サウンドの再生
		PlaySound(SOUND_LABEL_GAME3);
	}
}

//==================================================
// リザルト画面の終了処理
//==================================================
void UninitResult()
{
	//サウンドの停止
	//StopSound();

	//テクスチャの破棄
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//==================================================
// リザルト画面の更新処理
//==================================================
void UpdateResult()
{
	FADE pFade = GetFade();
	if (pFade == FADE_NONE)
	{
		//決定キー(ENTER)が押されたかどうか
		if (GetkeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true)
		{//モードの設定
			SetFade(MODE_RANKING);
		}
	}
}

//==================================================
// リザルト画面の描画処理
//==================================================
void DrawResult()
{
	LPDIRECT3DDEVICE9 pDevice;						//デバイスのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResult);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//ポリゴンの描画
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,
		0,
		2);
}
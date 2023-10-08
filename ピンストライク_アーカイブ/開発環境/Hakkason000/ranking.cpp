//**************************************************
//
//ランキング画面
//Author::Takano Minto
//
//**************************************************

//include
#include "main.h"
#include"ranking.h"
#include"input.h"
#include"sound.h"
#include"fade.h"
#include "score.h"

//==================================================
//グローバル変数
//==================================================
LPDIRECT3DTEXTURE9 g_pTextureRankingBG = NULL;					//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingBG = NULL;				//頂点バッファへのポインタ


//==================================================
//ランキング画面の初期化処理
//==================================================
void InitRankingBG()
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
		&g_pVtxBuffRankingBG, NULL);

	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//rankingBG.jpg", &g_pTextureRankingBG);

	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankingBG->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
	g_pVtxBuffRankingBG->Unlock();

	////サウンドの再生
	//PlaySound(SOUND_LABEL_GAME3);
}

//==================================================
//ランキング画面の終了処理
//==================================================
void UninitRankingBG()
{
	//テクスチャの破棄
	if (g_pTextureRankingBG != NULL)
	{
		g_pTextureRankingBG->Release();
		g_pTextureRankingBG = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRankingBG != NULL)
	{
		g_pVtxBuffRankingBG->Release();
		g_pVtxBuffRankingBG = NULL;
	}
}

//==================================================
//ランキング画面の更新処理
//==================================================
void UpdateRankingBG()
{
	FADE pFade = GetFade();
	if (pFade == FADE_NONE)
	{
		//決定キー(ENTER)が押されたかどうか
		if (GetkeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true)
		{
			SetFade(MODE_TITLE);
		}
	}
}

//==================================================
//ランキング画面の描画処理
//==================================================
void DrawRankingBG()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRankingBG);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRankingBG, 0, sizeof(VERTEX_2D));

	//ポリゴンの描画
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,
		0,
		2);
}


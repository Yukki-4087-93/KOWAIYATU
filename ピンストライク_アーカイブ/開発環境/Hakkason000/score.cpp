//==========================================================
//
//スコアの描画処理[score.cpp]
//Author:チームK2MT
//
//==========================================================

//include
#include "score.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;       //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL; //頂点バッファへのポインタ
D3DXVECTOR3 g_posScore; //スコアの位置
Score g_aScore[MAX_SCORE];                   //スコアの情報
int g_nScore[MAX_SCORE];
int g_nScoreRank;
int g_KeepNum = 0;	//情報を保存する用
int g_MathScore = 0;	//現在のスコア
int g_nCountup = 0;	//スコアの位を上げるために必要な関数
float g_animLeft = 0;	//テクスチャの動かす座標(テクスチャの左側)
float g_animRight = 0;	//テクスチャの動かす座標(テクスチャの右側)


//=======================================================================
//スコアの初期化処理
//=======================================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScore; //数をカウントする

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number000.png", &g_pTextureScore);

	//スコアの情報の初期化
	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		g_aScore[nCntScore].pos = D3DXVECTOR3(300.0f, 300.0f, 0.0f); //スコアの位置の初期化
		g_aScore[nCntScore].bUse = false;                       //使用していない状態
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffScore, NULL);

	//頂点情報のポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(350.0f, 300.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(300.0f, 350.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(350.0f, 350.0f, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		//頂点データのポインタを4つ分進める
		pVtx += 4;
	}

	SetScorePos(D3DXVECTOR3(300.0f, 120.0f, 0.0f));
	SetScorePos(D3DXVECTOR3(260.0f, 120.0f, 0.0f));
	SetScorePos(D3DXVECTOR3(220.0f, 120.0f, 0.0f));
	SetScorePos(D3DXVECTOR3(180.0f, 120.0f, 0.0f));
	SetScorePos(D3DXVECTOR3(140.0f, 120.0f, 0.0f));
	SetScorePos(D3DXVECTOR3(100.0f, 120.0f, 0.0f));
	SetScorePos(D3DXVECTOR3(60.0f, 120.0f, 0.0f));
	SetScorePos(D3DXVECTOR3(20.0f, 120.0f, 0.0f));

	g_MathScore = 0;	//現在のスコア

   //頂点バッファのアンロック
	g_pVtxBuffScore->Unlock();

}

//=======================================================================
//スコアの終了処理
//=======================================================================
void UninitScore(void)
{
	//テクスチャの破棄
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//=======================================================================
//スコアの更新処理
//=======================================================================
void UpdateScore(void)
{
	int nCntScore;
	VERTEX_2D* pVtx;  //頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);


	g_KeepNum = g_MathScore;
	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		g_nScore[nCntScore] = g_KeepNum % 10;
		g_KeepNum /= 10;

		switch (g_nScore[nCntScore])
		{
		case 0:
			g_animLeft = 0.0f;
			g_animRight = 0.0f;
			break;
		case 1:
			g_animLeft = 0.1f;
			g_animRight = 0.1f;
			break;
		case 2:
			g_animLeft = 0.2f;
			g_animRight = 0.2f;
			break;
		case 3:
			g_animLeft = 0.3f;
			g_animRight = 0.3f;
			break;
		case 4:
			g_animLeft = 0.4f;
			g_animRight = 0.4f;
			break;
		case 5:
			g_animLeft = 0.5f;
			g_animRight = 0.5f;
			break;
		case 6:
			g_animLeft = 0.6f;
			g_animRight = 0.6f;
			break;
		case 7:
			g_animLeft = 0.7f;
			g_animRight = 0.7f;
			break;
		case 8:
			g_animLeft = 0.8f;
			g_animRight = 0.8f;
			break;
		case 9:
			g_animLeft = 0.9f;
			g_animRight = 0.9f;
			break;
		}

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(g_animLeft, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_animRight + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_animLeft, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_animRight + 0.1f, 1.0f);

		pVtx += 4;
	}


	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();

}

//=======================================================================
//スコアの描画処理
//=======================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScore;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureScore);

	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		if (g_aScore[nCntScore].bUse == true)
		{//スコアが使用されている
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
		}
	}
}

//=======================================================================
//スコアの設定処理
//=======================================================================
void SetScorePos(D3DXVECTOR3 pos)
{
	int nCntScore; //数をカウントする変数
	int aPosTexU[MAX_SCORE];	//各桁の数字を格納
	int nScore = 0;
	g_nScore[0] = nScore;
	VERTEX_2D* pVtx;  //頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		aPosTexU[nCntScore] = g_nScore[nCntScore];
	}

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		if (g_aScore[nCntScore].bUse == false)
		{//スコアが使用されていない
			g_aScore[nCntScore].pos = pos;
			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x - 25.0f, g_aScore[nCntScore].pos.y - 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x + 25.0f, g_aScore[nCntScore].pos.y - 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x - 25.0f, g_aScore[nCntScore].pos.y + 25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x + 25.0f, g_aScore[nCntScore].pos.y + 25.0f, 0.0f);



			g_aScore[nCntScore].bUse = true;
			break;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();

}
//=======================================================================
//スコアの加算処理
//=======================================================================
void AddScore(int nValue)
{

	if (g_MathScore < 0)
	{
		g_MathScore = 0;
	}
	else
	{
		//スコアを増やす
		g_MathScore += nValue;

	}
}

//=======================================================================
//スコアの取得
//=======================================================================
int GetScore(void)
{
	return g_MathScore;
}

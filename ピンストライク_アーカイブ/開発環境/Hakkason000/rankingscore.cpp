//**************************************************
//
//ランキング処理
//Author:チームK2MT
//
//**************************************************

//include
#include "main.h"
#include "rankingscore.h"
#include "input.h"
#include "score.h"
#include "fade.h"
#include "sound.h"
#include <stdio.h>
#include <string.h>

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureRanking = NULL;					//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;				//頂点バッファへのポインタ
RankScore g_aRankScore[MAX_RANK][MAX_DIGIT];					//ランキングスコア情報([ランク数][桁数])
int g_nTimerRanking;											//点灯させる時間

//==================================================
//ランキングの初期化処理
//==================================================
void InitRanking()
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntRank = 0; //数をカウントする(順位)
	int nDataRank = 0;	//数をカウントする(桁数)


	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number000.png", &g_pTextureRanking);


	//ランキングの情報の初期化
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (nDataRank = 0; nDataRank < MAX_DIGIT; nDataRank++)
		{
			g_aRankScore[nCntRank][nDataRank].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //スコアの位置の初期化
			g_aRankScore[nCntRank][nDataRank].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 300.0f - 80.0f * nDataRank, 80.0f + 70 * nCntRank, 0.0f);
			g_aRankScore[nCntRank][nDataRank].nScore = 0;                       //使用していない状態
			g_aRankScore[nCntRank][nDataRank].nScorePos = 0;					//テクスチャの位置
			g_aRankScore[nCntRank][nDataRank].bRight = false;					//点灯させるかどうか
		}
	}

	g_nTimerRanking = 0;	//点灯させる時間

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK * MAX_DIGIT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffRanking, NULL);

	//頂点情報のポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);


	for (nCntRank = 0; nCntRank < MAX_RANK * MAX_DIGIT; nCntRank++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		pVtx += 4;
	}

	SetRanking(GetScore());
	//頂点バッファのアンロック
	g_pVtxBuffRanking->Unlock();
}

//=======================================================================
//ランキングの終了処理
//=======================================================================
void UninitRanking()
{
	//サウンドの停止
	StopAll();

	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}


	//頂点バッファの破棄
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}

}


//=======================================================================
//ランキングの更新処理
//=======================================================================
void UpdateRanking()
{
	g_nTimerRanking++;	//ランキングを点灯させる時間の更新
	if (GetkeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true)
	{
		SetFade(MODE_TITLE);
	}


	//頂点情報のポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	int nCntRank = 0;
	int nCntDigit = 0;	//桁数

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++)
		{
			pVtx[0].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntDigit].pos.x - MAX_RANKWIDTH, g_aRankScore[nCntRank][nCntDigit].pos.y - MAX_RANKHEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntDigit].pos.x + MAX_RANKWIDTH, g_aRankScore[nCntRank][nCntDigit].pos.y - MAX_RANKHEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntDigit].pos.x - MAX_RANKWIDTH, g_aRankScore[nCntRank][nCntDigit].pos.y + MAX_RANKHEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntDigit].pos.x + MAX_RANKWIDTH, g_aRankScore[nCntRank][nCntDigit].pos.y + MAX_RANKHEIGHT, 0.0f);


			if (g_aRankScore[nCntRank][nCntDigit].bRight == true)
			{
				if (g_nTimerRanking % 2 == 0)
				{//赤くする
					//頂点カラーの設定
					pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				}
				else
				{//元に戻す
					//頂点カラーの設定
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				}
			}
			pVtx += 4;

		}

	}


	//頂点バッファのアンロック
	g_pVtxBuffRanking->Unlock();


}

//=======================================================================
//ランキングの描画処理
//=======================================================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntRank = 0;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));


	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntRank = 0; nCntRank < MAX_RANK * MAX_DIGIT; nCntRank++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureRanking);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntRank * 4, 2);

	}


}

//==================================================
//ランキング画面のリセット処理
//==================================================
void ResetRanking()
{
	int nCntRank; //数をカウントする(順位)
	int nCntDigit;	//数をカウントする(桁数)

	//ランキングの情報の初期化
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++)
		{
			g_aRankScore[nCntRank][nCntDigit].nScore = 0;                       //使用していない状態
		}
	}
}

//=======================================================================
//ランキングのセット処理
//=======================================================================
void SetRanking(int nScore)
{
	//頂点情報のポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	FILE* pFile;

	int nCnt = 0;
	int nCntRank = 0;
	int nCntDigit = 0;	//桁数

	int nCntData = 0;	//要素1の情報
	int nAddRank = 0;	//今回のスコア
	int nCopyData = 0;	//データの受け皿
	int nData[MAX_RANK];	//すでにランクインしてるスコア	
	int nDataRank[MAX_RANK];	//データを保存する用
	int nDataSave[MAX_RANK];	//ランクインしたスコアの保存(並べ替えた後)


	pFile = fopen("Data\\ranking\\ranking.txt", "r");

	if (pFile != NULL)
	{
		for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{
			fscanf(pFile, "%d", &nData[nCntRank]);	//スコアをファイルから読み込む

			nDataRank[nCntRank] = nData[nCntRank];	//保存する

			nDataSave[nCntRank] = 0;	//初期化
		}

		nAddRank = nScore;	//今回のスコアを代入する
	}
	fclose(pFile);

	if (nAddRank >= nData[MAX_RANK - 1])
	{//もし5位より現在のスコアが高かったら
		nData[MAX_RANK - 1] = nAddRank;//5位に現在のスコアを代入
	}

	for (nCntData = 0; nCntData <= MAX_RANK - 1; nCntData++)//要素1と要素2を比較する
	{
		for (nCntRank = nCntData + 1; nCntRank < MAX_RANK; nCntRank++)
		{
			if (nData[nCntData] < nData[nCntRank])
			{
				nCopyData = nData[nCntData];	//受け皿に要素1を代入
				nData[nCntData] = nData[nCntRank];	//要素1に要素2を代入
				nData[nCntRank] = nCopyData;		//数値を入れ替える
			}
		}
	}

	pFile = fopen("Data\\ranking\\ranking.txt", "w");
	if (pFile != NULL)
	{
		for (nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			fprintf(pFile, "%d\n", nData[nCnt]);	//並べ替えたものを改めて保存する
		}
	}

	fclose(pFile);

	for (nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		nDataSave[nCnt] = nData[nCnt];	//スコアの代入
	}

	for (nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		for (nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++)
		{
			g_aRankScore[nCnt][nCntDigit].nScorePos = nData[nCnt] % 10;
			nData[nCnt] = nData[nCnt] / 10;
		}
	}


	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++)
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_aRankScore[nCntRank][nCntDigit].nScorePos), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_aRankScore[nCntRank][nCntDigit].nScorePos), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_aRankScore[nCntRank][nCntDigit].nScorePos), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_aRankScore[nCntRank][nCntDigit].nScorePos), 1.0f);

			if (nDataSave[nCntRank] == nScore)
			{
				g_aRankScore[nCntRank][nCntDigit].bRight = true;
			}

			pVtx += 4;
		}

	}

	//頂点バッファのアンロック
	g_pVtxBuffRanking->Unlock();

}
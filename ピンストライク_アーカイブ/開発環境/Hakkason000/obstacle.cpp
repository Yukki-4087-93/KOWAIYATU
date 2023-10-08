//**************************************************
//
//障害物
//Author::Takano Minto
//
//**************************************************

//==================================================
//インクルードファイル
//==================================================
#include"obstacle.h"

//==================================================
//定数定義
//==================================================
const float Gravity = 0.088f;
const float WD_OBSTACLE = 25.0f;
const float HI_OBSTACLE = 25.0f;
const int MAX_OBSTACLE = 50;

//==================================================
//グローバル変数
//==================================================
OBSTACLE g_Obj[MAX_OBSTACLE];								// 障害物のポインタ
//LPDIRECT3DTEXTURE9 g_pTextureObstacle = NULL;			// テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffObstacle = NULL;	// 頂点バッファへのポインタ

//==================================================
//初期化
//==================================================
void InitObstacle()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//デバイスのポインタ

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffObstacle, NULL);

	for (int i = 0; i < MAX_OBSTACLE; i++)
	{// 構造体の初期化
		g_Obj[i].pos = D3DXVECTOR3(640.0f, 110.0f, 0.0f);		// 位置の初期化
		g_Obj[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 角度の初期化
		g_Obj[i].siz = D3DXVECTOR3(25.0f, 25.0f, 0.0f);		// 角度の初期化
		g_Obj[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// 色の初期化
	}

	//D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//bullet000.png", &g_pTextureObstacle);

	VERTEX_2D* pVtx;			//頂点情報へのポインタ

	//頂点バッファをコック＆ロックし、頂点情報へのポインタを取得
	g_pVtxBuffObstacle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_OBSTACLE; nCntBlock++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_Obj[nCntBlock].pos.x - WD_OBSTACLE, g_Obj[nCntBlock].pos.y - HI_OBSTACLE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Obj[nCntBlock].pos.x + WD_OBSTACLE, g_Obj[nCntBlock].pos.y - HI_OBSTACLE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Obj[nCntBlock].pos.x - WD_OBSTACLE, g_Obj[nCntBlock].pos.y + HI_OBSTACLE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Obj[nCntBlock].pos.x + WD_OBSTACLE, g_Obj[nCntBlock].pos.y + HI_OBSTACLE, 0.0f);

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

		pVtx += 4;				//デデデータが4個分進む
	}

	//頂点バッファをアンロックする
	g_pVtxBuffObstacle->Unlock();

}

//==================================================
//終了
//==================================================
void UninitObstacle()
{
	////テクスチャの破棄
	//if (g_pTextureObstacle != NULL)
	//{
	//	g_pTextureObstacle->Release();
	//	g_pTextureObstacle = NULL;
	//}

	//頂点バッファの破棄
	if (g_pVtxBuffObstacle != NULL)
	{
		g_pVtxBuffObstacle->Release();
		g_pVtxBuffObstacle = NULL;
	}
}

//==================================================
//更新
//==================================================
void UpdateObstacle()
{
	//HitObstacle();	//ヒット処理

	//DownCounter();	//位置を変更するかどうか

	//MoveDown();		//移動量の設定

	//DestObstacle();	//ボールの位置変更
}

//==================================================
//描画
//==================================================
void DrawObstacle()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスのポインタを取得

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffObstacle, 0, sizeof(VERTEX_2D));

	//ポリゴンの描画
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//==================================================
//当たり判定
//==================================================
void HitObstacle()
{
	
}

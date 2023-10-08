//**************************************************
//
//タイトル画面
//Author::Takano Minto
//
//**************************************************
#include"title.h"
#include"input.h"
#include"sound.h"
#include"fade.h"
#include <time.h>

//==================================================
//グローバル変数
//==================================================
void StartBGM();

//==================================================
//グローバル変数
//==================================================
LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL;					//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				//頂点バッファへのポインタ
int g_SetBgm;
int g_Change = 0;

//==================================================
//タイトル画面の初期化処理
//==================================================
void InitTitle()
{
	g_SetBgm = 0;

	LPDIRECT3DDEVICE9 pDevice;						//デバイスのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle, NULL);

	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//Taitoru_102.png", &g_pTextureTitle);

	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffTitle->Unlock();

	srand((unsigned int)time(nullptr));				//ランダムの初期化

	StartBGM();
}

//==================================================
//タイトル画面の終了処理
//==================================================
void UninitTitle()
{
	////サウンドの停止
	//StopSound(SOUND_LABEL_GAME1);

	//テクスチャの破棄
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//==================================================
//タイトル画面の更新処理
//==================================================
void UpdateTitle()
{
	FADE pFade = GetFade();
	if (pFade == FADE_NONE)
	{
		//決定キー(ENTER)が押されたかどうか
		if (GetkeyboardTrigger(DIK_RETURN) ||
			GetJoypadTrigger(JOYKEY_A))
		{
			SetFade(MODE_TUTORIAL);
		}
	}
}

//==================================================
//タイトル画面の描画処理
//==================================================
void DrawTitle()
{
	LPDIRECT3DDEVICE9 pDevice;						//デバイスのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitle);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//ポリゴンの描画
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

void StartBGM()
{
	g_Change++;

	if (g_Change % 2 == 0)
	{
		g_SetBgm = rand() % 3;

		switch (g_SetBgm)
		{
		case 0:

			//サウンドの再生
			PlaySound(SOUND_LABEL_GAME1);

			break;

		case 1:

			//サウンドの再生
			PlaySound(Sound_LAVEL_ATitle);

			break;

		case 2:

			//サウンドの再生
			PlaySound(Sound_LAVEL_ATitle2);

			break;

		default:
			break;
		}
	}
	else
	{
		//サウンドの再生
		PlaySound(SOUND_LABEL_GAME1);
	}
}

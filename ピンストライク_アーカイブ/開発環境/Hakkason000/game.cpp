//**************************************************
//
//ゲーム画面
//Author::Takano Minto
//
//**************************************************
#include "input.h"
#include "sound.h"
#include "time.h"
#include "bg.h"
#include "bg2.h"
#include "fade.h"
#include "pause.h"
#include "timer.h"
#include "pinball.h"
#include "score.h"
#include "player.h"
#include "enemy.h"
#include "game.h"
#include <time.h>

//==================================================
//プロトタイプ宣言
//==================================================
void SetSpanEnemy();
void SetSound();
void UninitSoundNumber();

//==================================================
//グローバル変数
//==================================================
bool g_bPause = false;
int g_nCntTime = 0;			//タイマーのカウントダウンをするタイミング用の変数
int g_SpawnCounter;
int g_REARSpawn;
int g_NumYoshiko;
int g_ChangeSound = 0;
int g_RandamSound;

//==================================================
//初期化
//==================================================
void InitGame()
{
	InitEnemy();
	InitBG();					//背景の初期化
	InitBG2();
	InitScore();				//スコアの初期化処理
	InitPause();				//ポーズの初期化
	InitTimer();				//タイマーの初期化処理
	InitPinball();
	InitPlayer();				//プレイヤーの初期化処理

	g_bPause = false;
	g_nCntTime = 0;	//タイマーカウントの初期化
	g_SpawnCounter = 0;
	g_REARSpawn = 0;
	g_NumYoshiko = 1;
	g_RandamSound = 0;

	//SetEnemy(D3DXVECTOR3(200.0f,400.0f,0.0f),0,0);
	SetPlayerLeft(D3DXVECTOR3(640.0f, SCREEN_HEIGHT - 20.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.5f));

	srand((unsigned int)time(nullptr));				//ランダムの初期化

	SetSound();
}

//==================================================
//終了
//==================================================
void UninitGame()
{
	UninitSoundNumber();
	UninitEnemy();
	UninitBG();				//終了処理(背景)
	UninitBG2();
	UninitPinball();
	UninitPause();
	UninitTimer();			//タイマーの終了処理

	UninitScore();			//スコアの終了処理

	UninitPlayer();			//プレイヤーの終了処理
}

//==================================================
//更新
//==================================================
void UpdateGame()
{
#ifdef _DEBUG
	if (GetkeyboardTrigger(DIK_F1))
	{//Pキーとその他もろもろが押された
		SetFade(MODE_RESULT);
	}
#endif // _DEBUG

	if (GetkeyboardTrigger(DIK_P) || 
		GetJoypadTrigger(JOYKEY_STRTE) ||
		GetJoypadTrigger(JOYKEY_BACK))
	{//Pキーとその他もろもろが押された
		g_bPause = g_bPause ? false : true;
	}

	if (!g_bPause)
	{
		g_nCntTime++;
		if (g_nCntTime % 60 == 0)
		{
			SubTimer(1);
		}
		UpdatePinball();
		UpdateEnemy();
		SetSpanEnemy();
		UpdateScore();
		UpdateBG();					//BackGroundの更新処理
		UpdateBG2();
		UpdateTimer();				//タイマーの更新処理
		UpdatePlayer();				//プレイヤーの更新処理
	}
	else
	{
		UpdatePause();
	}
}

//==================================================
//描画
//==================================================
void DrawGame()
{
	DrawBG();					//背景の描画処理
	DrawEnemy();
	DrawBG2(); 
	DrawTimer();				//タイマーの描画処理
	DrawPinball();
	DrawScore();
	DrawPlayer();				//プレイヤーの描画処理
	if (g_bPause == true)
	{//ポーズなう
		DrawPause();
	}
}

//==================================================
//ポーズの設定
//==================================================
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}

//==================================================
//ポーズの設定
//==================================================
void SetSpanEnemy()
{
	g_SpawnCounter++;		//出現カウンターを加算

	if (g_SpawnCounter % 100 == 0)
	{//ちょうど割り切れたとき
		SetEnemy(D3DXVECTOR3(200.0f, 500.0f, 0.0f),	// 位置設定
			D3DXVECTOR3(20.0f, 20.0f, 0.0f),		// サイズ設定
			D3DXVECTOR3(1.0f, 0.0f, 0.0f),			// 移動設定
			0,		// 種類の設定										
			0);		// テクスチャ設定
		g_REARSpawn++;		//ヨシコ出現カウンターを加算
	}
	
	if (g_SpawnCounter % 240 == 0)
	{//ちょうど割り切れたとき
		SetEnemy(D3DXVECTOR3(200.0f, 400.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f), 2, 1);
	}
	
	if (g_REARSpawn >= 10 * g_NumYoshiko)
	{//ヨシコカウンターがたまり切ったら
		PlaySound(SOUND_LABEL_LAUGH_GHOST);
		SetVolume(SOUND_LABEL_LAUGH_GHOST,2.0f);
		SetEnemy(D3DXVECTOR3(200.0f, 50.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(3.0f, 0.0f, 0.0f),1, 2);
		g_REARSpawn = 0;		//カウンターを初期化
		g_NumYoshiko++;
	}
}

//==================================================
//サウンドの設定
//==================================================
void SetSound()
{
	g_ChangeSound++;

	if (g_ChangeSound % 2 == 0)
	{
		g_RandamSound = rand() % 2;

		switch (g_RandamSound)
		{
		case 0:

			PlaySound(SOUND_LAVEL_Ex);
			SetVolume(SOUND_LABEL_GAME2, 0.5f);

			break;

		case 1:

			PlaySound(SOUND_LAVEL_Ex2);
			SetVolume(SOUND_LABEL_GAME2, 0.5f);

			break;

		default:
			break;
		}

		
	}
	else
	{
		PlaySound(SOUND_LABEL_GAME2);
		SetVolume(SOUND_LABEL_GAME2, 0.5f);
	}

	if (g_ChangeSound >= 10)
	{
		g_ChangeSound = 0;
	}
}

void UninitSoundNumber()
{
	if (g_ChangeSound % 2 == 0)
	{

	}
	else
	{
		StopAll();
	}
}

//==================================================
//サウンド番号取得
//==================================================
int GetSoundNumber()
{
	return g_ChangeSound;
}


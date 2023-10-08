//**************************************************
//
//メイン
//Author::Takano Minto
//
//**************************************************
#ifndef _MAIN_H_			//このマクロ定義がなされなっかたら
#define _MAIN_H_			//二重インクルード防止のマクロ定義

//==================================================
// インクルードファイル
//==================================================
#include <Windows.h>
#include "d3dx9.h"
#define  DIRECTINPUT_VERSION	(0X0800)		//ビルド時の警告対応用マクロ
#include "dinput.h"
#include "xaudio2.h"
#include "xinput.h"

//==================================================
//ライブラリのリンク
//==================================================
#pragma comment(lib,"d3d9.lib")			//描画処理に必須
#pragma comment(lib,"d3dx9.lib")		//d3d9.libの拡張ライブラリ
#pragma comment(lib,"dxguid.lib")		//DirectXコンポーネント使用に必須
#pragma comment(lib,"winmm.lib")		//システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")		//入力処理に必須
#pragma comment(lib,"xinput.lib")

//==================================================
//マクロ定義
//==================================================
#define SCREEN_WIDTH		(1280)		//ウィンドウの幅
#define SCREEN_HEIGHT		(720)		//ウィンドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//頂点座標と頂点カラー																	//円周率ｗ

//==================================================
//頂点座標[2D]の構造体定義
//==================================================
typedef struct
{
	D3DXVECTOR3 pos;		//頂点座標
	float rhw;				//座標交換用係数(1.0fで固定)
	D3DCOLOR col;			//頂点カラー
	D3DXVECTOR2 tex;		//テクスチャの座標
}VERTEX_2D;

//==================================================
//画面(モード)の種類
//==================================================
typedef enum 
{
	MODE_TITLE = 0,				//ゲームタイトル
	MODE_TUTORIAL,				//チュートリアル
	MODE_GAME,					//ゲーム画面
	MODE_RESULT,				//リザルト画面
	MODE_RANKING,				//ランキング画面
	MODE_MAX
}MODE;

//==================================================
//プロトタイプ宣言
//==================================================
LPDIRECT3DDEVICE9 GetDevice();
void SetMode(MODE mode);
MODE GetMode();

#endif // !_MAIN_H_


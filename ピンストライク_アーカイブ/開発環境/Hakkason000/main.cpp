//**************************************************
//
//メイン
//Author::Takano Minto
//
//**************************************************

//==================================================
// インクルードファイル
//==================================================
#include"main.h"
#include"input.h"
#include"title.h"
#include"game.h"
#include"tutorial.h"
#include"sound.h"
#include"result.h"
#include"fade.h"
#include"ranking.h"
#include "rankingscore.h"

//==================================================
//マクロ定義
//==================================================
#define CLASS_NAME			"Hakkason"			//ウィンドウクラスの名前
#define WINDOW_NAME			"ピンストライク"		//ウィンドウの名前

//==================================================
//プロトタイプ宣言
//==================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT InIt(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit();
void Update();
void Draw();
void DrawFPS();

//==================================================
//グローバル変数
//==================================================
LPDIRECT3D9 g_pD3D = NULL;							//Direct3Dオブジェクトのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;				//Direct3Dデバイスのポインタ
LPD3DXFONT g_pFont = NULL;
int g_nCountFPS = 0;
MODE g_mode = MODE_TITLE;							//現在のモード

//==================================================
//メイン関数
//==================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),						//WINDCLASSEXのメモリサイズ
		CS_CLASSDC,								//ウィンドウスタイル
		WindowProc,							    //ウィンドウプローシャ
		0,										//0にする
		0,										//０にする
		hInstance,								//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),			//タスクバーアイコン
		LoadCursor(NULL,IDC_ARROW),				//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),				//クライアント領域の背景
		NULL,									//メニューバー
		CLASS_NAME,								//ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)			//ファイルアイコン
	};

	HWND hWnd;									//ウィンドウハンドル
	MSG msg;									//メッセージを収納する十八番

	//画面構造体
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウ生成
	hWnd = CreateWindowEx(0,						//拡張ウィンドスタイル
		CLASS_NAME,									//ウィンドクラスのスタイル
		WINDOW_NAME,								//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,						//ウィンドスタイル			
		CW_USEDEFAULT,								//ウィンドウの左上ｘ座標
		CW_USEDEFAULT,								//ウィンドウの左上ｙ座標
		(rect.right - rect.left),					//ウィンドウの幅
		(rect.bottom - rect.top),					//ウィンドウの高さ
		NULL,										//親ウィンドウのハンドル
		NULL,										//メニューハンドルor子ウィンドウＩＤ
		hInstance,									//インスタンスハンドル
		NULL);										//ウィンドウの作成データ

	DWORD dwFrameCount;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;			//現在時刻
	DWORD dwExecLastTime;			//最後に処理した時刻

	//初期化処理
	if (FAILED(InIt(hInstance, hWnd, TRUE)))
	{//初期化が失敗した場合
		return -1;
	}

	//分解能を設定
	timeBeginPeriod(1);

	dwCurrentTime = 0;							//初期化
	dwExecLastTime = timeGetTime();				//現在時刻を取得
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();;

	//ウィンドの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windowsの処理
			if (msg.message == WM_QUIT)
			{//MW_QUITメッセージを受け取ったらメッセージループをぬける
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);

				DispatchMessage(&msg);
			}
		}
		else
		{//DirctXの処理
			dwCurrentTime = timeGetTime();				//現在時刻を取得
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
				//FPSを計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				//FPSの計測時刻を保存
				dwFPSLastTime = dwCurrentTime;

				//フレームカウントをクリア
				dwFrameCount = 0;
			}
			if (dwCurrentTime - dwExecLastTime >=(1000/60))
			{
				dwExecLastTime = dwCurrentTime;			//処理開始の時刻と現在時刻を取得
				//更新処理
				Update();
				//描画処理
				Draw();
				//フレームカウントを加算
				dwFrameCount++;
			}
		}
	}
	//終了処理
	Uninit();

	//分解能を戻す
	timeEndPeriod(1);

	//ウィンドクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//==================================================
//ウィンドウプロージャ
//==================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;  
	switch (uMsg)
	{
	case WM_DESTROY:		//ウィンドウ破棄メッセージ

		//WM_QUITメッセージで送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:				//ESCキーが押された
			//ウィンドウを破棄する
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_TOPMOST);

			if (nID == IDYES)
			{
				//ウィンドウを破壊する
				DestroyWindow(hWnd);
			}
			break;
		}
		break;

	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//==================================================
//初期化処理
//==================================================
HRESULT InIt(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;					//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;			//プレゼンテーションパラメーター

	//Dirct3dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//デバイスのプレゼンテーションのパラメーターの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));														//パラメーターのゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;													//ゲーム画面サイズ（横）
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;													//ゲーム画面サイズ（高さ）
	d3dpp.BackBufferFormat = d3ddm.Format;													//バックバッファの数
	d3dpp.BackBufferCount = 1;																//ダブルバッファの切り替え
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;												//ダブルバッファの切り替え
	d3dpp.EnableAutoDepthStencil = TRUE;													//デプスバッファとステンシルバッファの生成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;												//デプスバッファとして、16bitを使う
	d3dpp.Windowed = bWindow;																//ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;								//インターバル

	//Direct3Dデバイスの生成(描画処理＝ハード、頂点＝CPU)
	if (FAILED(g_pD3D->CreateDevice
		(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))

	{
		//Direct3Dデバイスの生成(描画処理＝ハード、頂点＝CPU)
		if (FAILED(g_pD3D->CreateDevice
			(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))

		{//Direct3Dデバイスの生成(描画処理＝CPU、頂点＝CPU)
			if (FAILED(g_pD3D->CreateDevice
				(D3DADAPTER_DEFAULT,
					D3DDEVTYPE_REF,
					hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&d3dpp,
					&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}

	}
	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);

	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);

	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);


	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);

	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//デバック表示用のフォトンストリームを生成
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE,
		SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFont);

	//キーボードの初期化処理
	if (FAILED(Initkeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//ゲームパットの初期化
	InitJoypad();
	
	//サウンドの初期化処理
	InitSound();

	//モードの設定
	InitFade(g_mode);

	return S_OK;
}

//==================================================
//終了処理
//==================================================
void Uninit()
{
	//フェードの終了処理
	UninitFade();

	//タイトル画面の終了処理
	UninitTitle();

	//ゲーム画面の終了処理
	UninitGame();

	//チュートリアルの終了処理
	UninitTutorial();

	//リザルト画面の終了処理
	UninitResult();

	//キーボードの終了処理
	Uninitkeyboard();

	//ジョイパッドの終了処理
	UninitJoypad();

	//ランキングの終了処理
	UninitRanking();

	//サウンドの終了処理
	UninitSound();

	//デバック用フォトンの破棄
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	//Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//==================================================
//更新処理
//==================================================
void Update()
{
	Updatekeyboard();				//keyboardの更新処理

	UpdateJoypad();					//Joypadの更新処理

	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();				//titlescreenの更新処理
		break;

	case MODE_TUTORIAL:
		UpdateTutorial();
		break;

	case MODE_GAME:
		UpdateGame();				//gamescreenの更新処理
		break;

	case MODE_RESULT:
		UpdateResult();				//resultscreenの更新処理
		break;

	case MODE_RANKING:
		UpdateRanking();			//resultscreenの更新処理
		break;
	}

	//フェードの更新処理
	UpdateFade();
}

//==================================================
//描画処理
//==================================================
void Draw()
{
	//画面クリア（バックバッファ＆Zバッファのクリア）
	g_pD3DDevice->Clear(
		0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合

		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;

		case MODE_TUTORIAL:
			DrawTutorial();
			break;

		case MODE_GAME:
			DrawGame();
			break;

		case MODE_RESULT:
			DrawResult();
			break;

		case MODE_RANKING:
			DrawRanking();
			break;
		}

		//フェードの描画処理
		DrawFade();
		#ifdef _DEBUG
			//FPSの表示
			DrawFPS();
		#endif


		//描画終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//==================================================
//FPSの設定
//==================================================
void DrawFPS()
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	char aStr[256];

	//文字列に代入
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==================================================
//モードの設定
//==================================================
void SetMode(MODE mode)
{
	//現在のモードの終了処理
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;

	case MODE_TUTORIAL:
		UninitTutorial();
		break;

	case MODE_GAME:
		UninitGame();
		break;

	case MODE_RESULT:
		UninitResult();
		break;

	case MODE_RANKING:
		UninitRanking();
		break;
	}

	//新しいモードの設定
	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;

	case MODE_TUTORIAL:
		InitTutorial();
		break;

	case MODE_GAME:
		InitGame();
		break;

	case MODE_RESULT:
		InitResult();
		break;

	case MODE_RANKING:
		InitRanking();
		break;
	}
	g_mode = mode;
}

//==================================================
//デバイスの取得
//==================================================
LPDIRECT3DDEVICE9 GetDevice()
{
	return g_pD3DDevice;
}

//==================================================
//モードの取得
//==================================================
MODE GetMode()
{
	return g_mode;
}
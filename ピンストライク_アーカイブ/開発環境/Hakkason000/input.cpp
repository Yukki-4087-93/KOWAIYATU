//**************************************************
//
//キーボード、ゲームパッド入力処理
//Author::Takano Minto
//
//**************************************************
#include"input.h"

//==================================================
//マクロ定義
//==================================================
#define NUM_KEY_MAX			(256)						//キーの最大数

//==================================================
//グローバル変数
//==================================================
LPDIRECTINPUT8 g_pInput = NULL;							//ダイレクトインプットオブジェクトのポインタ
LPDIRECTINPUTDEVICE8 g_pDevkeyboard = NULL;				//入力デバイス（キーボード）のポインタ
BYTE g_akeyState[NUM_KEY_MAX];							//キーボードのプレス情報
BYTE g_akeyStateTrigger[NUM_KEY_MAX];					//キーボードのトリガー情報
XINPUT_STATE g_JoykeyState;								//ゲームパッドのプレス情報
XINPUT_STATE g_JoykeyStateTrigger;						//ゲームパッドのトリガー情報

//==================================================
//キーボードの初期化
//==================================================
HRESULT Initkeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//Directinputの生成
	if (FAILED(DirectInput8Create(hInstance,DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)& g_pInput,NULL)))
	{
		return E_FAIL;
	}

	//入力デバイスの生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard,&g_pDevkeyboard,NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(g_pDevkeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードの設定
	if (FAILED(g_pDevkeyboard->SetCooperativeLevel(hWnd,(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードのアクセス権を獲得
	g_pDevkeyboard->Acquire();

	return S_OK;
}

//==================================================
//ゲームパッドの初期化
//==================================================
HRESULT InitJoypad()
{
	//メモリのクリア
	memset(&g_JoykeyState, 0, sizeof(XINPUT_STATE));

	//Xinputのステートの設定（有効活用）
	XInputEnable(true);

	return S_OK;
}

//==================================================
//キーボードの終了
//==================================================
void Uninitkeyboard()
{
	//入力デバイスの破棄
	if (g_pDevkeyboard != NULL)
	{
		g_pDevkeyboard->Unacquire();
		g_pDevkeyboard->Release();
		g_pDevkeyboard = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//==================================================
//ゲームパッドの終了
//==================================================
void UninitJoypad()
{
	//Xinputのステートの設定
	XInputEnable(false);
}

//==================================================
//キーボードの更新
//==================================================
void Updatekeyboard()
{
	BYTE akeystate[NUM_KEY_MAX];				//キーボードの入力情報
	int nCntkey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevkeyboard->GetDeviceState(sizeof(akeystate), &akeystate[0])))
	{
		for (nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
		{
			g_akeyStateTrigger[nCntkey] = (g_akeyState[nCntkey] & akeystate[nCntkey]) ^ akeystate[nCntkey];			//トリガー処理						//キーボードのトリガー情報を取得
			g_akeyState[nCntkey] = akeystate[nCntkey];																//プレス処理																					//キーボードのプレス情報を取得
		}
	}
	else
	{
		g_pDevkeyboard->Acquire();					//キーボードのアクセス権を獲得
	}
}

//==================================================
//ゲームパッド更新
//==================================================
void UpdateJoypad()
{
	XINPUT_STATE joykeystate;

	//ショイパットの状態を取得
	if (XInputGetState(0,&joykeystate) == ERROR_SUCCESS)
	{
		g_JoykeyStateTrigger.Gamepad.wButtons = (g_JoykeyState.Gamepad.wButtons & joykeystate.Gamepad.wButtons) ^ joykeystate.Gamepad.wButtons;			//トリガー処理	
		g_JoykeyState = joykeystate;
	}
}

//==================================================
//キーボードの情報を取得(押込)
//==================================================
bool GetkeyboardPress(int nkey)
{
	return(g_akeyState[nkey] & 0x80) ? true : false;
}

//==================================================
//キーボードの情報を取得
//==================================================
bool GetkeyboardTrigger(int nkey)
{
	return(g_akeyStateTrigger[nkey] & 0x80) ? true : false;
}

//==================================================
//ゲームパッドの情報を取得(押込)
//==================================================
bool GetJoypadPress(JOYkey key)
{
	return (g_JoykeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//==================================================
//ゲームパッドの情報を取得
//==================================================
bool GetJoypadTrigger(JOYkey key)
{
	return (g_JoykeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

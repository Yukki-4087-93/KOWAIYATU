//**************************************************
//
//�Q�[�����
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
//�v���g�^�C�v�錾
//==================================================
void SetSpanEnemy();
void SetSound();
void UninitSoundNumber();

//==================================================
//�O���[�o���ϐ�
//==================================================
bool g_bPause = false;
int g_nCntTime = 0;			//�^�C�}�[�̃J�E���g�_�E��������^�C�~���O�p�̕ϐ�
int g_SpawnCounter;
int g_REARSpawn;
int g_NumYoshiko;
int g_ChangeSound = 0;
int g_RandamSound;

//==================================================
//������
//==================================================
void InitGame()
{
	InitEnemy();
	InitBG();					//�w�i�̏�����
	InitBG2();
	InitScore();				//�X�R�A�̏���������
	InitPause();				//�|�[�Y�̏�����
	InitTimer();				//�^�C�}�[�̏���������
	InitPinball();
	InitPlayer();				//�v���C���[�̏���������

	g_bPause = false;
	g_nCntTime = 0;	//�^�C�}�[�J�E���g�̏�����
	g_SpawnCounter = 0;
	g_REARSpawn = 0;
	g_NumYoshiko = 1;
	g_RandamSound = 0;

	//SetEnemy(D3DXVECTOR3(200.0f,400.0f,0.0f),0,0);
	SetPlayerLeft(D3DXVECTOR3(640.0f, SCREEN_HEIGHT - 20.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.5f));

	srand((unsigned int)time(nullptr));				//�����_���̏�����

	SetSound();
}

//==================================================
//�I��
//==================================================
void UninitGame()
{
	UninitSoundNumber();
	UninitEnemy();
	UninitBG();				//�I������(�w�i)
	UninitBG2();
	UninitPinball();
	UninitPause();
	UninitTimer();			//�^�C�}�[�̏I������

	UninitScore();			//�X�R�A�̏I������

	UninitPlayer();			//�v���C���[�̏I������
}

//==================================================
//�X�V
//==================================================
void UpdateGame()
{
#ifdef _DEBUG
	if (GetkeyboardTrigger(DIK_F1))
	{//P�L�[�Ƃ��̑�������낪�����ꂽ
		SetFade(MODE_RESULT);
	}
#endif // _DEBUG

	if (GetkeyboardTrigger(DIK_P) || 
		GetJoypadTrigger(JOYKEY_STRTE) ||
		GetJoypadTrigger(JOYKEY_BACK))
	{//P�L�[�Ƃ��̑�������낪�����ꂽ
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
		UpdateBG();					//BackGround�̍X�V����
		UpdateBG2();
		UpdateTimer();				//�^�C�}�[�̍X�V����
		UpdatePlayer();				//�v���C���[�̍X�V����
	}
	else
	{
		UpdatePause();
	}
}

//==================================================
//�`��
//==================================================
void DrawGame()
{
	DrawBG();					//�w�i�̕`�揈��
	DrawEnemy();
	DrawBG2(); 
	DrawTimer();				//�^�C�}�[�̕`�揈��
	DrawPinball();
	DrawScore();
	DrawPlayer();				//�v���C���[�̕`�揈��
	if (g_bPause == true)
	{//�|�[�Y�Ȃ�
		DrawPause();
	}
}

//==================================================
//�|�[�Y�̐ݒ�
//==================================================
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}

//==================================================
//�|�[�Y�̐ݒ�
//==================================================
void SetSpanEnemy()
{
	g_SpawnCounter++;		//�o���J�E���^�[�����Z

	if (g_SpawnCounter % 100 == 0)
	{//���傤�Ǌ���؂ꂽ�Ƃ�
		SetEnemy(D3DXVECTOR3(200.0f, 500.0f, 0.0f),	// �ʒu�ݒ�
			D3DXVECTOR3(20.0f, 20.0f, 0.0f),		// �T�C�Y�ݒ�
			D3DXVECTOR3(1.0f, 0.0f, 0.0f),			// �ړ��ݒ�
			0,		// ��ނ̐ݒ�										
			0);		// �e�N�X�`���ݒ�
		g_REARSpawn++;		//���V�R�o���J�E���^�[�����Z
	}
	
	if (g_SpawnCounter % 240 == 0)
	{//���傤�Ǌ���؂ꂽ�Ƃ�
		SetEnemy(D3DXVECTOR3(200.0f, 400.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f), 2, 1);
	}
	
	if (g_REARSpawn >= 10 * g_NumYoshiko)
	{//���V�R�J�E���^�[�����܂�؂�����
		PlaySound(SOUND_LABEL_LAUGH_GHOST);
		SetVolume(SOUND_LABEL_LAUGH_GHOST,2.0f);
		SetEnemy(D3DXVECTOR3(200.0f, 50.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(3.0f, 0.0f, 0.0f),1, 2);
		g_REARSpawn = 0;		//�J�E���^�[��������
		g_NumYoshiko++;
	}
}

//==================================================
//�T�E���h�̐ݒ�
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
//�T�E���h�ԍ��擾
//==================================================
int GetSoundNumber()
{
	return g_ChangeSound;
}


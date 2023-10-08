//**************************************************
//
//�^�C�g�����
//Author::Takano Minto
//
//**************************************************
#include"title.h"
#include"input.h"
#include"sound.h"
#include"fade.h"
#include <time.h>

//==================================================
//�O���[�o���ϐ�
//==================================================
void StartBGM();

//==================================================
//�O���[�o���ϐ�
//==================================================
LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL;					//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				//���_�o�b�t�@�ւ̃|�C���^
int g_SetBgm;
int g_Change = 0;

//==================================================
//�^�C�g����ʂ̏���������
//==================================================
void InitTitle()
{
	g_SetBgm = 0;

	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle, NULL);

	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//Taitoru_102.png", &g_pTextureTitle);

	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�L�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	srand((unsigned int)time(nullptr));				//�����_���̏�����

	StartBGM();
}

//==================================================
//�^�C�g����ʂ̏I������
//==================================================
void UninitTitle()
{
	////�T�E���h�̒�~
	//StopSound(SOUND_LABEL_GAME1);

	//�e�N�X�`���̔j��
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//==================================================
//�^�C�g����ʂ̍X�V����
//==================================================
void UpdateTitle()
{
	FADE pFade = GetFade();
	if (pFade == FADE_NONE)
	{
		//����L�[(ENTER)�������ꂽ���ǂ���
		if (GetkeyboardTrigger(DIK_RETURN) ||
			GetJoypadTrigger(JOYKEY_A))
		{
			SetFade(MODE_TUTORIAL);
		}
	}
}

//==================================================
//�^�C�g����ʂ̕`�揈��
//==================================================
void DrawTitle()
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitle);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//�|���S���̕`��
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

			//�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_GAME1);

			break;

		case 1:

			//�T�E���h�̍Đ�
			PlaySound(Sound_LAVEL_ATitle);

			break;

		case 2:

			//�T�E���h�̍Đ�
			PlaySound(Sound_LAVEL_ATitle2);

			break;

		default:
			break;
		}
	}
	else
	{
		//�T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_GAME1);
	}
}

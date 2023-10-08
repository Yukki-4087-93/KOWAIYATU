//**************************************************
//
//�����L���O���
//Author::Takano Minto
//
//**************************************************

//include
#include "main.h"
#include"ranking.h"
#include"input.h"
#include"sound.h"
#include"fade.h"
#include "score.h"

//==================================================
//�O���[�o���ϐ�
//==================================================
LPDIRECT3DTEXTURE9 g_pTextureRankingBG = NULL;					//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingBG = NULL;				//���_�o�b�t�@�ւ̃|�C���^


//==================================================
//�����L���O��ʂ̏���������
//==================================================
void InitRankingBG()
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingBG, NULL);

	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//rankingBG.jpg", &g_pTextureRankingBG);

	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRankingBG->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffRankingBG->Unlock();

	////�T�E���h�̍Đ�
	//PlaySound(SOUND_LABEL_GAME3);
}

//==================================================
//�����L���O��ʂ̏I������
//==================================================
void UninitRankingBG()
{
	//�e�N�X�`���̔j��
	if (g_pTextureRankingBG != NULL)
	{
		g_pTextureRankingBG->Release();
		g_pTextureRankingBG = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRankingBG != NULL)
	{
		g_pVtxBuffRankingBG->Release();
		g_pVtxBuffRankingBG = NULL;
	}
}

//==================================================
//�����L���O��ʂ̍X�V����
//==================================================
void UpdateRankingBG()
{
	FADE pFade = GetFade();
	if (pFade == FADE_NONE)
	{
		//����L�[(ENTER)�������ꂽ���ǂ���
		if (GetkeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true)
		{
			SetFade(MODE_TITLE);
		}
	}
}

//==================================================
//�����L���O��ʂ̕`�揈��
//==================================================
void DrawRankingBG()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRankingBG);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankingBG, 0, sizeof(VERTEX_2D));

	//�|���S���̕`��
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,
		0,
		2);
}


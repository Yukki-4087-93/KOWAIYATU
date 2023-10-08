//==========================================================
//
//�^�C�}�[����[timer.cpp]
//Author:�`�[��K2MT
//
//==========================================================

//include 
#include "main.h"
#include "timer.h"
#include "fade.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTimer = NULL;       //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL; //���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posTimer; //�^�C�}�[�̈ʒu
Timer g_aTimer[MAX_TIMER];                   //�^�C�}�[�̏��
int g_MathTimer = 0;	//���݂̃^�C�}�[
int g_KeepNumTimer = 0;	//����ۑ�����p
int g_nTimer[MAX_TIMER] = {};
float g_animTimerLeft = 0;	//�e�N�X�`���̓��������W(�e�N�X�`���̍���)
float g_animTimerRight = 0;	//�e�N�X�`���̓��������W(�e�N�X�`���̉E��)


//=======================================================================
//�^�C�}�[�̏���������
//=======================================================================
void InitTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntTimer; //�����J�E���g����

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "Data\\TEXTURE\\Number000.png", &g_pTextureTimer);

	//�^�C�}�[�̏��̏�����
	for (nCntTimer = 0; nCntTimer < MAX_TIMER; nCntTimer++)
	{
		g_aTimer[nCntTimer].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�X�R�A�̈ʒu�̏�����
		g_aTimer[nCntTimer].bUse = false;                       //�g�p���Ă��Ȃ����
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIMER, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTimer, NULL);

	//���_���̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);


	for (nCntTimer = 0; nCntTimer < MAX_TIMER; nCntTimer++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(350.0f, 300.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(300.0f, 350.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(350.0f, 350.0f, 0.0f);

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

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		//���_�f�[�^�̃|�C���^��4���i�߂�
		pVtx += 4;
	}

	SetTimerPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 50.0f, 0.0f));
	SetTimerPos(D3DXVECTOR3(SCREEN_WIDTH / 2 - 50.0f, 50.0f, 0.0f));
	SetTimerPos(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100.0f, 50.0f, 0.0f));

	g_MathTimer = MAX_TIME;	//���݂̃^�C�}�[

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTimer->Unlock();

}

//=======================================================================
//�^�C�}�[�̏I������
//=======================================================================
void UninitTimer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureTimer != NULL)
	{
		g_pTextureTimer->Release();
		g_pTextureTimer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}

}

//=======================================================================
//�^�C�}�[�̍X�V����
//=======================================================================
void UpdateTimer(void)
{
	int nCntTimer;
	VERTEX_2D* pVtx;  //���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	g_KeepNumTimer = g_MathTimer;
	for (nCntTimer = 0; nCntTimer < MAX_TIMER; nCntTimer++)
	{
		g_nTimer[nCntTimer] = g_KeepNumTimer % 10;
		g_KeepNumTimer /= 10;

		switch (g_nTimer[nCntTimer])
		{
		case 0:
			g_animTimerLeft = 0.0f;
			g_animTimerRight = 0.0f;
			break;
		case 1:
			g_animTimerLeft = 0.1f;
			g_animTimerRight = 0.1f;
			break;
		case 2:
			g_animTimerLeft = 0.2f;
			g_animTimerRight = 0.2f;
			break;
		case 3:
			g_animTimerLeft = 0.3f;
			g_animTimerRight = 0.3f;
			break;
		case 4:
			g_animTimerLeft = 0.4f;
			g_animTimerRight = 0.4f;
			break;
		case 5:
			g_animTimerLeft = 0.5f;
			g_animTimerRight = 0.5f;
			break;
		case 6:
			g_animTimerLeft = 0.6f;
			g_animTimerRight = 0.6f;
			break;
		case 7:
			g_animTimerLeft = 0.7f;
			g_animTimerRight = 0.7f;
			break;
		case 8:
			g_animTimerLeft = 0.8f;
			g_animTimerRight = 0.8f;
			break;
		case 9:
			g_animTimerLeft = 0.9f;
			g_animTimerRight = 0.9f;
			break;
		}

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(g_animTimerLeft, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_animTimerRight + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_animTimerLeft, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_animTimerRight + 0.1f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTimer->Unlock();

}

//=======================================================================
//�^�C�}�[�̕`�揈��
//=======================================================================
void DrawTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntTimer;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTimer);

	for (nCntTimer = 0; nCntTimer < MAX_TIMER; nCntTimer++)
	{
		if (g_aTimer[nCntTimer].bUse == true)
		{//�X�R�A���g�p����Ă���
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTimer * 4, 2);
		}
	}

}

//=======================================================================
//�^�C�}�[�̐ݒ菈��
//=======================================================================
void SetTimerPos(D3DXVECTOR3 pos)
{
	int nCntTimer; //�����J�E���g����ϐ�
	int aPosTimerTexU[MAX_TIMER];	//�e���̐������i�[
	int nTimer = 0;
	g_nTimer[0] = nTimer;
	VERTEX_2D* pVtx;  //���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTimer = 0; nCntTimer < MAX_TIMER; nCntTimer++)
	{
		aPosTimerTexU[nCntTimer] = g_nTimer[nCntTimer];
	}


	for (nCntTimer = 0; nCntTimer < MAX_TIMER; nCntTimer++)
	{
		if (g_aTimer[nCntTimer].bUse == false)
		{//�X�R�A���g�p����Ă��Ȃ�
			g_aTimer[nCntTimer].pos = pos;
			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aTimer[nCntTimer].pos.x - 25.0f, g_aTimer[nCntTimer].pos.y - 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aTimer[nCntTimer].pos.x + 25.0f, g_aTimer[nCntTimer].pos.y - 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aTimer[nCntTimer].pos.x - 25.0f, g_aTimer[nCntTimer].pos.y + 25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aTimer[nCntTimer].pos.x + 25.0f, g_aTimer[nCntTimer].pos.y + 25.0f, 0.0f);



			g_aTimer[nCntTimer].bUse = true;
			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTimer->Unlock();

}

//=======================================================================
//�^�C�}�[�̌��Z����
//=======================================================================
void SubTimer(int nValue)
{
	//�^�C�}�[�����炷
	g_MathTimer -= nValue;

	if (g_MathTimer <= 0)
	{
		SetFade(MODE_RESULT);
	}
}

//=======================================================================
//�^�C�}�[��0�ɂȂ������ǂ����𒲂ׂ鏈��
//=======================================================================
bool CheckTime(void)
{
	if (g_MathTimer <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

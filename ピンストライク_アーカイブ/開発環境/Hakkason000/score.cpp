//==========================================================
//
//�X�R�A�̕`�揈��[score.cpp]
//Author:�`�[��K2MT
//
//==========================================================

//include
#include "score.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;       //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL; //���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posScore; //�X�R�A�̈ʒu
Score g_aScore[MAX_SCORE];                   //�X�R�A�̏��
int g_nScore[MAX_SCORE];
int g_nScoreRank;
int g_KeepNum = 0;	//����ۑ�����p
int g_MathScore = 0;	//���݂̃X�R�A
int g_nCountup = 0;	//�X�R�A�̈ʂ��グ�邽�߂ɕK�v�Ȋ֐�
float g_animLeft = 0;	//�e�N�X�`���̓��������W(�e�N�X�`���̍���)
float g_animRight = 0;	//�e�N�X�`���̓��������W(�e�N�X�`���̉E��)


//=======================================================================
//�X�R�A�̏���������
//=======================================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScore; //�����J�E���g����

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number000.png", &g_pTextureScore);

	//�X�R�A�̏��̏�����
	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		g_aScore[nCntScore].pos = D3DXVECTOR3(300.0f, 300.0f, 0.0f); //�X�R�A�̈ʒu�̏�����
		g_aScore[nCntScore].bUse = false;                       //�g�p���Ă��Ȃ����
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffScore, NULL);

	//���_���̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
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

	SetScorePos(D3DXVECTOR3(300.0f, 120.0f, 0.0f));
	SetScorePos(D3DXVECTOR3(260.0f, 120.0f, 0.0f));
	SetScorePos(D3DXVECTOR3(220.0f, 120.0f, 0.0f));
	SetScorePos(D3DXVECTOR3(180.0f, 120.0f, 0.0f));
	SetScorePos(D3DXVECTOR3(140.0f, 120.0f, 0.0f));
	SetScorePos(D3DXVECTOR3(100.0f, 120.0f, 0.0f));
	SetScorePos(D3DXVECTOR3(60.0f, 120.0f, 0.0f));
	SetScorePos(D3DXVECTOR3(20.0f, 120.0f, 0.0f));

	g_MathScore = 0;	//���݂̃X�R�A

   //���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffScore->Unlock();

}

//=======================================================================
//�X�R�A�̏I������
//=======================================================================
void UninitScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//=======================================================================
//�X�R�A�̍X�V����
//=======================================================================
void UpdateScore(void)
{
	int nCntScore;
	VERTEX_2D* pVtx;  //���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);


	g_KeepNum = g_MathScore;
	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		g_nScore[nCntScore] = g_KeepNum % 10;
		g_KeepNum /= 10;

		switch (g_nScore[nCntScore])
		{
		case 0:
			g_animLeft = 0.0f;
			g_animRight = 0.0f;
			break;
		case 1:
			g_animLeft = 0.1f;
			g_animRight = 0.1f;
			break;
		case 2:
			g_animLeft = 0.2f;
			g_animRight = 0.2f;
			break;
		case 3:
			g_animLeft = 0.3f;
			g_animRight = 0.3f;
			break;
		case 4:
			g_animLeft = 0.4f;
			g_animRight = 0.4f;
			break;
		case 5:
			g_animLeft = 0.5f;
			g_animRight = 0.5f;
			break;
		case 6:
			g_animLeft = 0.6f;
			g_animRight = 0.6f;
			break;
		case 7:
			g_animLeft = 0.7f;
			g_animRight = 0.7f;
			break;
		case 8:
			g_animLeft = 0.8f;
			g_animRight = 0.8f;
			break;
		case 9:
			g_animLeft = 0.9f;
			g_animRight = 0.9f;
			break;
		}

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(g_animLeft, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_animRight + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_animLeft, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_animRight + 0.1f, 1.0f);

		pVtx += 4;
	}


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();

}

//=======================================================================
//�X�R�A�̕`�揈��
//=======================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScore;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		if (g_aScore[nCntScore].bUse == true)
		{//�X�R�A���g�p����Ă���
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
		}
	}
}

//=======================================================================
//�X�R�A�̐ݒ菈��
//=======================================================================
void SetScorePos(D3DXVECTOR3 pos)
{
	int nCntScore; //�����J�E���g����ϐ�
	int aPosTexU[MAX_SCORE];	//�e���̐������i�[
	int nScore = 0;
	g_nScore[0] = nScore;
	VERTEX_2D* pVtx;  //���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		aPosTexU[nCntScore] = g_nScore[nCntScore];
	}

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		if (g_aScore[nCntScore].bUse == false)
		{//�X�R�A���g�p����Ă��Ȃ�
			g_aScore[nCntScore].pos = pos;
			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x - 25.0f, g_aScore[nCntScore].pos.y - 25.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x + 25.0f, g_aScore[nCntScore].pos.y - 25.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x - 25.0f, g_aScore[nCntScore].pos.y + 25.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x + 25.0f, g_aScore[nCntScore].pos.y + 25.0f, 0.0f);



			g_aScore[nCntScore].bUse = true;
			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();

}
//=======================================================================
//�X�R�A�̉��Z����
//=======================================================================
void AddScore(int nValue)
{

	if (g_MathScore < 0)
	{
		g_MathScore = 0;
	}
	else
	{
		//�X�R�A�𑝂₷
		g_MathScore += nValue;

	}
}

//=======================================================================
//�X�R�A�̎擾
//=======================================================================
int GetScore(void)
{
	return g_MathScore;
}

//**************************************************
//
//�����L���O����
//Author:�`�[��K2MT
//
//**************************************************

//include
#include "main.h"
#include "rankingscore.h"
#include "input.h"
#include "score.h"
#include "fade.h"
#include "sound.h"
#include <stdio.h>
#include <string.h>

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureRanking = NULL;					//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;				//���_�o�b�t�@�ւ̃|�C���^
RankScore g_aRankScore[MAX_RANK][MAX_DIGIT];					//�����L���O�X�R�A���([�����N��][����])
int g_nTimerRanking;											//�_�������鎞��

//==================================================
//�����L���O�̏���������
//==================================================
void InitRanking()
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntRank = 0; //�����J�E���g����(����)
	int nDataRank = 0;	//�����J�E���g����(����)


	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number000.png", &g_pTextureRanking);


	//�����L���O�̏��̏�����
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (nDataRank = 0; nDataRank < MAX_DIGIT; nDataRank++)
		{
			g_aRankScore[nCntRank][nDataRank].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�X�R�A�̈ʒu�̏�����
			g_aRankScore[nCntRank][nDataRank].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 300.0f - 80.0f * nDataRank, 80.0f + 70 * nCntRank, 0.0f);
			g_aRankScore[nCntRank][nDataRank].nScore = 0;                       //�g�p���Ă��Ȃ����
			g_aRankScore[nCntRank][nDataRank].nScorePos = 0;					//�e�N�X�`���̈ʒu
			g_aRankScore[nCntRank][nDataRank].bRight = false;					//�_�������邩�ǂ���
		}
	}

	g_nTimerRanking = 0;	//�_�������鎞��

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK * MAX_DIGIT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffRanking, NULL);

	//���_���̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);


	for (nCntRank = 0; nCntRank < MAX_RANK * MAX_DIGIT; nCntRank++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		pVtx += 4;
	}

	SetRanking(GetScore());
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffRanking->Unlock();
}

//=======================================================================
//�����L���O�̏I������
//=======================================================================
void UninitRanking()
{
	//�T�E���h�̒�~
	StopAll();

	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}


	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}

}


//=======================================================================
//�����L���O�̍X�V����
//=======================================================================
void UpdateRanking()
{
	g_nTimerRanking++;	//�����L���O��_�������鎞�Ԃ̍X�V
	if (GetkeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true)
	{
		SetFade(MODE_TITLE);
	}


	//���_���̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	int nCntRank = 0;
	int nCntDigit = 0;	//����

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++)
		{
			pVtx[0].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntDigit].pos.x - MAX_RANKWIDTH, g_aRankScore[nCntRank][nCntDigit].pos.y - MAX_RANKHEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntDigit].pos.x + MAX_RANKWIDTH, g_aRankScore[nCntRank][nCntDigit].pos.y - MAX_RANKHEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntDigit].pos.x - MAX_RANKWIDTH, g_aRankScore[nCntRank][nCntDigit].pos.y + MAX_RANKHEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntDigit].pos.x + MAX_RANKWIDTH, g_aRankScore[nCntRank][nCntDigit].pos.y + MAX_RANKHEIGHT, 0.0f);


			if (g_aRankScore[nCntRank][nCntDigit].bRight == true)
			{
				if (g_nTimerRanking % 2 == 0)
				{//�Ԃ�����
					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				}
				else
				{//���ɖ߂�
					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				}
			}
			pVtx += 4;

		}

	}


	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffRanking->Unlock();


}

//=======================================================================
//�����L���O�̕`�揈��
//=======================================================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntRank = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));


	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntRank = 0; nCntRank < MAX_RANK * MAX_DIGIT; nCntRank++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRanking);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntRank * 4, 2);

	}


}

//==================================================
//�����L���O��ʂ̃��Z�b�g����
//==================================================
void ResetRanking()
{
	int nCntRank; //�����J�E���g����(����)
	int nCntDigit;	//�����J�E���g����(����)

	//�����L���O�̏��̏�����
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++)
		{
			g_aRankScore[nCntRank][nCntDigit].nScore = 0;                       //�g�p���Ă��Ȃ����
		}
	}
}

//=======================================================================
//�����L���O�̃Z�b�g����
//=======================================================================
void SetRanking(int nScore)
{
	//���_���̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	FILE* pFile;

	int nCnt = 0;
	int nCntRank = 0;
	int nCntDigit = 0;	//����

	int nCntData = 0;	//�v�f1�̏��
	int nAddRank = 0;	//����̃X�R�A
	int nCopyData = 0;	//�f�[�^�̎󂯎M
	int nData[MAX_RANK];	//���łɃ����N�C�����Ă�X�R�A	
	int nDataRank[MAX_RANK];	//�f�[�^��ۑ�����p
	int nDataSave[MAX_RANK];	//�����N�C�������X�R�A�̕ۑ�(���בւ�����)


	pFile = fopen("Data\\ranking\\ranking.txt", "r");

	if (pFile != NULL)
	{
		for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{
			fscanf(pFile, "%d", &nData[nCntRank]);	//�X�R�A���t�@�C������ǂݍ���

			nDataRank[nCntRank] = nData[nCntRank];	//�ۑ�����

			nDataSave[nCntRank] = 0;	//������
		}

		nAddRank = nScore;	//����̃X�R�A��������
	}
	fclose(pFile);

	if (nAddRank >= nData[MAX_RANK - 1])
	{//����5�ʂ�茻�݂̃X�R�A������������
		nData[MAX_RANK - 1] = nAddRank;//5�ʂɌ��݂̃X�R�A����
	}

	for (nCntData = 0; nCntData <= MAX_RANK - 1; nCntData++)//�v�f1�Ɨv�f2���r����
	{
		for (nCntRank = nCntData + 1; nCntRank < MAX_RANK; nCntRank++)
		{
			if (nData[nCntData] < nData[nCntRank])
			{
				nCopyData = nData[nCntData];	//�󂯎M�ɗv�f1����
				nData[nCntData] = nData[nCntRank];	//�v�f1�ɗv�f2����
				nData[nCntRank] = nCopyData;		//���l�����ւ���
			}
		}
	}

	pFile = fopen("Data\\ranking\\ranking.txt", "w");
	if (pFile != NULL)
	{
		for (nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			fprintf(pFile, "%d\n", nData[nCnt]);	//���בւ������̂����߂ĕۑ�����
		}
	}

	fclose(pFile);

	for (nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		nDataSave[nCnt] = nData[nCnt];	//�X�R�A�̑��
	}

	for (nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		for (nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++)
		{
			g_aRankScore[nCnt][nCntDigit].nScorePos = nData[nCnt] % 10;
			nData[nCnt] = nData[nCnt] / 10;
		}
	}


	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++)
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_aRankScore[nCntRank][nCntDigit].nScorePos), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_aRankScore[nCntRank][nCntDigit].nScorePos), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_aRankScore[nCntRank][nCntDigit].nScorePos), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_aRankScore[nCntRank][nCntDigit].nScorePos), 1.0f);

			if (nDataSave[nCntRank] == nScore)
			{
				g_aRankScore[nCntRank][nCntDigit].bRight = true;
			}

			pVtx += 4;
		}

	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffRanking->Unlock();

}
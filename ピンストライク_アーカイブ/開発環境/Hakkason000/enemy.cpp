//------------------------------------------------------
//
//�G�l�~�[
//Author;takano
//
//------------------------------------------------------
//#include"explosion.h"
#include"enemy.h"
#include"score.h"
#include"fade.h"
#include"time.h"
#include "sound.h"
#include "game.h"
#include <time.h>

void PlaySE(int Num);

//---------------
//�O���[�o���ϐ�
//---------------
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = { NULL, NULL, NULL };					//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;													//���_�o�b�t�@�̃|�C���^
Enemy g_aEnemy[MAX_ENEMY];																		//�G�l�~�[�̏��
int g_SetSE;

//---------------------
//�G�l�~�[�̏���������
//---------------------
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;			//�f�o�C�X�̃|�C���^

	int nCntEnemy;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY, 
		FVF_VERTEX_2D, 
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy, NULL);

	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̓ǂݍ��ݏ���
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//enemy_000.png", &g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//enemy_001.png", &g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//enemy_002.png", &g_apTextureEnemy[2]);

	//�G�l�~�[�̂̏�����
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���S�̈ʒu
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].nPattern = 0;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = 0;
		g_aEnemy[nCntEnemy].bUse = false;								//�g�p���ĂȂ���Ԃɂ���
	}

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_MAXSIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_MAXSIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_MAXSIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_MAXSIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_MAXSIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_MAXSIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_MAXSIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_MAXSIZE, 0.0f);

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

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();

	g_SetSE = 0;

	srand((unsigned int)time(nullptr));				//�����_���̏�����
}

//---------------------
//�G�l�~�[�̃I���^����
//---------------------
void UninitEnemy(void)
{
	int nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//-------------------
//�G�l�~�[�̍X�V����
//-------------------
void UpdateEnemy(void)
{
	int nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			g_aEnemy[nCntEnemy].pos += g_aEnemy[nCntEnemy].move;

			VERTEX_2D* pVtx;

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += nCntEnemy * 4;						//�f�[�^�ɍ��킹�����l���i��

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].size.x, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].size.x, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].size.x, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].size.x, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].size.y, 0.0f);


			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:


				break;

			case ENEMYSTATE_DAMAGE:

				g_aEnemy[nCntEnemy].nCounterState--;

				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{//�G�l�~�[�̗̑͂�0�ȏ�̂Ƃ�
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;					//�G�l�~�[��ʏ��Ԃɂ���

					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				}
				break;
			}

			if (g_aEnemy[nCntEnemy].pos.x >= SCREEN_WIDTH - 200.0f)
			{
				g_aEnemy[nCntEnemy].bUse = false;
			}


			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffEnemy->Unlock();
		}
	}
}

//-------------------
//�G�l�~�[�̕`�揈��
//-------------------
void DrawEnemy(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	int nCntEnemy;

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//�e�򂪎g�p����Ă���
		 //�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);
		 //�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntEnemy * 4,						//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);									//�|���S����
		}
	}
}

//----------------
//�G�l�~�[�Z�b�g
//----------------
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, int nType, int nPattern)
{
	int nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{//�e���g���Ă��Ȃ�
			g_aEnemy[nCntEnemy].pos = pos;				//�v���C���[�̒��S�ƃ}�e���A���̒��S�𓯂��ɂ���
			g_aEnemy[nCntEnemy].size = size;
			g_aEnemy[nCntEnemy].move = move;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].nPattern = nPattern;

			VERTEX_2D *pVtx;

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += nCntEnemy * 4;						//�f�f�f�[�^�ɍ��킹�����l���i��

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_MAXSIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_MAXSIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_MAXSIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_MAXSIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_MAXSIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_MAXSIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_MAXSIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_MAXSIZE, 0.0f);

			if (nPattern == 0)
			{
				g_aEnemy[nCntEnemy].nLife = 1;
			}
			else if (nPattern == 1)
			{
				g_aEnemy[nCntEnemy].nLife = 1;
			}
			else if (nPattern == 2)
			{
				g_aEnemy[nCntEnemy].nLife = 1;
			}
			
			g_aEnemy[nCntEnemy].bUse = true;			//�g�p���Ă����Ԃɂ���

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffEnemy->Unlock();
			break;
		}
	}
}

//---------------------
//�G�l�~�[�̃q�b�g����
//---------------------
void HitEnemy(int nCntEnemy, int nDamage)
{
	PlaySE(nCntEnemy);
	g_aEnemy[nCntEnemy].nLife -= nDamage;

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{//�G�l�~�[�̗̑͂��Ȃ��Ȃ����Ƃ�
		//SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

		switch (g_aEnemy[nCntEnemy].nPattern)
		{
		case 0:

			AddScore(100);

			break;

		case 1:

			AddScore(500);

			break;

		case 2:

			AddScore(1000);

			break;

		default:
			break;
		}
		g_aEnemy[nCntEnemy].bUse = false;			//�g�p����Ă��Ȃ���Ԃɂ���
	}
	else
	{
		VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nCntEnemy * 4;						//�f�[�^�ɍ��킹�����l���i��

		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCounterState = 5;				//�_���[�W��Ԃ�ۂ���
		
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffEnemy->Unlock();
	}
}

//---------------
//�f�o�C�X�̎擾
//---------------
Enemy* GetEnemy(void)
{
	return &g_aEnemy[0];
}

void PlaySE(int Num)
{
	if (GetSoundNumber() % 2 == 0 &&
		g_aEnemy[Num].nPattern != 2)
	{
		g_SetSE = rand() % 2;

		switch (g_SetSE)
		{
		case 0:

			PlaySound(SOUND_LAVEL_ARIGATO);

			break;

		case 1:

			PlaySound(SOUND_LAVEL_SEEYOU);

			break;

		default:
			break;
		}
	}
	else if (GetSoundNumber() % 2 == 0 &&
		g_aEnemy[Num].nPattern == 2)
	{
		PlaySound(SOUND_LAVEL_WARAIGOE);
	}
	else
	{
		PlaySound(SOUND_LABEL_HIT);
	}
}

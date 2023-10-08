//**************************************************
//
//�w�i���
//Author::Takano Minto
//
//**************************************************

//==================================================
//�C���N���[�h�t�@�C��
//==================================================
#include"pinball.h"
#include "input.h"
#include "enemy.h"

//==================================================
//�萔��`
//==================================================
const float Gravity = 0.3f;
const float WD_PINBALL = 20.0f;
const float HI_PINBALL = 20.0f;

//==================================================
//�v���g�^�C�v�錾
//==================================================
void MoveUp();

//==================================================
//�O���[�o���ϐ�
//==================================================
PINBALL g_pinball;								// �s���{�[���̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePinball = NULL;			// �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPinball = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
bool g_bMoveDown;	//�������邩���Ȃ���
int g_nCountDown;	//��������܂ł̃J�E���^�[

//==================================================
//������
//==================================================
void InitPinball()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�̃|�C���^

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPinball, NULL);

	{// �\���̂̏�����
		g_pinball.pos = D3DXVECTOR3(0.0f,0.0f,0.0f);		// �ʒu�̏�����
		g_pinball.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ߋ��̈ʒu�̏�����
		g_pinball.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �p�x�̏�����
		g_pinball.rotOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ߋ��̊p�x�̏�����
		g_pinball.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏�����
		g_pinball.moveOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ߋ��̈ړ��ʂ̏�����
		g_pinball.col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);		// �F�̏�����
		g_pinball.bUse = false;
	}

	g_bMoveDown = true;
	g_nCountDown = 0;

	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//bullet000.png", &g_pTexturePinball);

	VERTEX_2D* pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@���R�b�N�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPinball->Lock(0, 0, (void**)&pVtx, 0);

	//�Ίp���̒������Z�o����
	g_pinball.fLength = sqrtf(WD_PINBALL * WD_PINBALL + HI_PINBALL * HI_PINBALL);

	//�Ίp���̊p�x���Z�o����
	g_pinball.fAngle = atan2f(HI_PINBALL, WD_PINBALL);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_pinball.pos.x - WD_PINBALL / 2;
	pVtx[0].pos.y = g_pinball.pos.y - HI_PINBALL;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_pinball.pos.x + WD_PINBALL / 2;
	pVtx[1].pos.y = g_pinball.pos.y - HI_PINBALL;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_pinball.pos.x - WD_PINBALL / 2;
	pVtx[2].pos.y = g_pinball.pos.y;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_pinball.pos.x + WD_PINBALL / 2;
	pVtx[3].pos.y = g_pinball.pos.y;
	pVtx[3].pos.z = 0.0f;

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
	g_pVtxBuffPinball->Unlock();
}

//==================================================
//�I��
//==================================================
void UninitPinball()
{
	//�e�N�X�`���̔j��
	if (g_pTexturePinball != NULL)
	{
		g_pTexturePinball->Release();
		g_pTexturePinball = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPinball != NULL)
	{
		g_pVtxBuffPinball->Release();
		g_pVtxBuffPinball = NULL;
	}
}

//==================================================
//�X�V
//==================================================
void UpdatePinball()
{
	if (g_pinball.bUse)
	{
		HitPinball();	//�q�b�g����

		MoveUp();		//�ړ��ʂ̐ݒ�

		DestPinBall();	//�{�[���̈ʒu�ύX
	}
}

//==================================================
//�`��
//==================================================
void DrawPinball()
{
	if (g_pinball.bUse)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̃|�C���^���擾

		//���_�t�H�[�}�b�g
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePinball);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffPinball, 0, sizeof(VERTEX_2D));

		//�|���S���̕`��
		pDevice->DrawPrimitive
		(D3DPT_TRIANGLESTRIP,
			0,
			2);
	}
}

//==================================================
//�����蔻��
//==================================================
void SetPinBall(D3DXVECTOR3 pos)
{
	if (!g_pinball.bUse)
	{
		InitPinball();
		g_pinball.pos = pos;
		g_pinball.bUse = true;
	}
}

//==================================================
//�����蔻��
//==================================================
void HitPinball()
{
	Enemy* pEnemy = GetEnemy();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{//�G�l�~�[���g�p����Ă���
			if (g_pinball.pos.x >= pEnemy->pos.x - ENEMY_SIZE - WD_PINBALL &&
				g_pinball.pos.x <= pEnemy->pos.x + ENEMY_SIZE + WD_PINBALL &&
				g_pinball.pos.y >= pEnemy->pos.y - ENEMY_SIZE - WD_PINBALL &&
				g_pinball.pos.y <= pEnemy->pos.y + ENEMY_SIZE + WD_PINBALL)
			{//�v���C���[�̒��S�ɃG�l�~�[�ƒe�̃T�C�Y�i�e�����j���{�[�����͈͂ɒe������������
			 //�G�l�~�[�̃q�b�g����
				HitEnemy(nCntEnemy, 1);

				g_pinball.bUse = false;			//�g�p����Ă��Ȃ���Ԃɂ���
			}
		}
	}
}

//==================================================
//���S����
//==================================================
void DestPinBall()
{
	if (g_pinball.pos.y <= 0.0f)
	{
		g_pinball.move.y = 0.0f;

		g_pinball.bUse = false;
	}
}

//==================================================
//���ɍs������
//==================================================
void MoveUp()
{
	VERTEX_2D* pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@���R�b�N�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPinball->Lock(0, 0, (void**)&pVtx, 0);

	// �d��
	g_pinball.move.y -= Gravity;

	// �O��̈ʒu��ۑ�
	g_pinball.posOld = g_pinball.pos;

	g_pinball.moveOld = g_pinball.move;

	if (g_bMoveDown)
	{
		// �ʒu���X�V
		g_pinball.pos.x += g_pinball.move.x;
		g_pinball.pos.y += g_pinball.move.y;
	}

	////�ړ��ʂ��X�V
	//g_pinball.move.x += (0.0f - g_pinball.move.x) * PLAYER_INERTIA;

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_pinball.pos.x - WD_PINBALL / 2;
	pVtx[0].pos.y = g_pinball.pos.y - HI_PINBALL;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_pinball.pos.x + WD_PINBALL / 2;
	pVtx[1].pos.y = g_pinball.pos.y - HI_PINBALL;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_pinball.pos.x - WD_PINBALL / 2;
	pVtx[2].pos.y = g_pinball.pos.y;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_pinball.pos.x + WD_PINBALL / 2;
	pVtx[3].pos.y = g_pinball.pos.y;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPinball->Unlock();
}

//==========================================================
//
//�v���C���[�̕`�揈��[player.cpp]
//Author:�`�[��K2MT
//
//==========================================================

//include
#include "main.h"
#include "player.h"
#include "input.h"
#include "pinball.h"
#include "sound.h"
#include "game.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL; //���_�o�b�t�@�ւ̃|�C���^
Player g_Player;					//�v���C���[�̏��
float g_fLengthPlayer = 0.0f;					 //�v���C���[�̑Ίp���̒���
float g_fAnglePlayer = 0.0f;					//�v���C���[�̊p�x

//=======================================================================
//�v���C���[�̏���������
//=======================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;  //�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "Data\\TEXTURE\\player.png", &g_pTexturePlayer);


		g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏�����
		g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏�����
		g_Player.bUse = false;

	//�Ίp���̒������Z�o����
	g_fLengthPlayer = sqrtf(PLAYER_WIDTH * PLAYER_WIDTH + PLAYER_HEIGHT * PLAYER_HEIGHT) / 2.0f;

	//�Ίp���̊p�x���Z�o����
	g_fAnglePlayer = atan2f(PLAYER_WIDTH, PLAYER_HEIGHT);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPlayer, NULL);

	VERTEX_2D* pVtx;  //���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);


	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (-D3DX_PI * 0.75f)) * g_fLengthPlayer;
	pVtx[0].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (-D3DX_PI * 0.75f)) * g_fLengthPlayer;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI * 0.75f)) * g_fLengthPlayer;
	pVtx[1].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI * 0.75f)) * g_fLengthPlayer;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (-D3DX_PI * 0.25f)) * g_fLengthPlayer;
	pVtx[2].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (-D3DX_PI * 0.25f)) * g_fLengthPlayer;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI * 0.25f)) * g_fLengthPlayer;
	pVtx[3].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI * 0.25f)) * g_fLengthPlayer;
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


		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();

}

//=======================================================================
//�v���C���[�̏I������
//=======================================================================
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//=======================================================================
//�v���C���[�̍X�V����
//=======================================================================
void UpdatePlayer(void)
{
	if (GetkeyboardTrigger(DIK_SPACE))
	{
		if (GetSoundNumber() % 2 == 1)
		{
			PlaySound(SOUND_LABEL_SHOT);
		}
		SetPinBall(g_Player.pos);
	}

}

//=======================================================================
//�v���C���[�̕`�揈��
//=======================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2);
}

//=======================================================================
//�v���C���[�̐ݒ菈��
//=======================================================================
void SetPlayerLeft(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	VERTEX_2D* pVtx;  //���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);


	if(g_Player.bUse == false)
	{
		g_Player.pos = pos;
		g_Player.rot = rot;
		g_Player.bUse = true;


		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (-D3DX_PI * 0.75f)) * g_fLengthPlayer;
		pVtx[0].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (-D3DX_PI * 0.75f)) * g_fLengthPlayer;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI * 0.75f)) * g_fLengthPlayer;
		pVtx[1].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI * 0.75f)) * g_fLengthPlayer;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (-D3DX_PI * 0.25f)) * g_fLengthPlayer;
		pVtx[2].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (-D3DX_PI * 0.25f)) * g_fLengthPlayer;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI * 0.25f)) * g_fLengthPlayer;
		pVtx[3].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI * 0.25f)) * g_fLengthPlayer;
		pVtx[3].pos.z = 0.0f;

	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffPlayer->Unlock();
}


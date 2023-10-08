//==========================================================
//
//�v���C���[�̕`�揈��[player.h]
//Author:�`�[��K2MT
//
//==========================================================

#ifndef _PLAYER_H_ //���̃}�N����`������Ă��Ȃ�������
#define _PLAYER_H_ //2�d�C���N���[�h�h�~�̃}�N����`

//include
#include "main.h"

//�}�N����`
#define MAX_PLAYER		(2)		//�v���C���[�̍ő吔
#define NUM_PLAYER		(2)		//�v���C���[�̎��(���E���]�p�Ŏg�p)
#define PLAYER_WIDTH	(200.0f)	//�v���C���[�̕�
#define PLAYER_HEIGHT	(200.0f)	//�v���C���[�̍���


//�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotOld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 moveOld;
	D3DXCOLOR col;
	float fLength;							//�Ίp���̒���
	float fAngle;							//�Ίp���̊p�x
	bool bUse;
}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);		//�v���C���[�̏���������
void UninitPlayer(void);	//�v���C���[�̏I������
void UpdatePlayer(void);	//�v���C���[�̍X�V����
void DrawPlayer(void);		//�v���C���[�̕`�揈��
void SetPlayerLeft(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//�v���C���[�̐ݒ菈��
#endif
//==========================================================
//
//�X�R�A�̕`�揈��[score.h]
//Author:�`�[��K2MT
//
//==========================================================

#ifndef _SCORE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _SCORE_H_ //2�d�C���N���[�h�h�~�̃}�N����`

//include
#include "main.h"

//�X�R�A�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos; //�X�R�A�̈ʒu
	bool bUse;        //�X�R�A���g�p���Ă��邩�ǂ���
}Score;

//�v���g�^�C�v�錾
void InitScore(void); //�X�R�A�̏���������
void UninitScore(void); //�X�R�A�̏I������
void UpdateScore(void); //�X�R�A�̍X�V����
void DrawScore(void);   //�X�R�A�̕`�揈��
void SetScorePos(D3DXVECTOR3 pos); //�X�R�A�̐ݒ菈��
void AddScore(int nValue);	//�X�R�A�̉��Z����
int GetScore(void);		//�X�R�A�̎擾

//�}�N����`
#define SCORE_WIDTH	(50)   //�X�R�A��1���̕�
#define SCORE_HEIGHT	(50)   //�X�R�A��1���̍���
#define MAX_SCORE	(8) //�X�R�A�̍ő包��


#endif
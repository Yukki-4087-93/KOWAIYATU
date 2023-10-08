//**************************************************
//
//�����L���O����
//Author:�`�[��K2MT
//
//**************************************************
#ifndef _RANKINGSCORE_H_
#define _RANKINGSCORE_H_

//include
#include "main.h"

//==================================================
//�}�N����`
//==================================================
#define MAX_RANK	(8)	//�ő僉���N��
#define MAX_DIGIT	(8)	//�ő包��
#define MAX_RANKWIDTH	(30.0f)	//�����L���O1�����̕�
#define MAX_RANKHEIGHT	(30.0f)	//�����L���O1�����̍���

//==================================================
//�����L���O�̍\����
//==================================================
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXCOLOR col;					//�J���[
	int nScore;						//�X�R�A
	int nScorePos;					//�e�N�X�`���̈ʒu
	bool bRight;					//�V���������N�C����������点��p
}RankScore;

//�v���g�^�C�v�錾
void InitRanking();		//�����L���O�̏���������
void UninitRanking();	//�����L���O�̏I������
void UpdateRanking();	//�����L���O�̍X�V����
void DrawRanking();		//�����L���O�̕`�揈��
void ResetRanking();	//�����L���O�̃��Z�b�g����
void SetRanking(int nScore);	//�����L���O�̐ݒ菈��


#endif
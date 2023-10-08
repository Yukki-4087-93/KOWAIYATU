//==========================================================
//
//�^�C�}�[����[timer.h]
//Author:�`�[��K2MT
//
//==========================================================

#ifndef _TIMER_H_
#define _TIMER_H_

//include
#include "main.h"

//�}�N����`
#define MAX_TIMER	(3)	//�^�C�}�[�̍ő包��
#define MAX_TIME	(90)	//�Q�[���̍ő厞��

//�^�C�}�[�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos; //�^�C�}�[�̈ʒu
	bool bUse;        //�^�C�}�[���g�p���Ă��邩�ǂ���
}Timer;

//�v���g�^�C�v�錾
void InitTimer(void);	//�^�C�}�[�̏���������
void UninitTimer(void);	//�^�C�}�[�̏I������
void UpdateTimer(void);	//�^�C�}�[�̍X�V����
void DrawTimer(void);	//�^�C�}�[�̕`�揈��
void SetTimerPos(D3DXVECTOR3 pos); //�^�C�}�[�̐ݒ菈��
void SubTimer(int nValue);	//�^�C�}�[�̌��Z����
bool CheckTime(void);	//�^�C�}�[��0�ɂȂ������ǂ���

#endif
//**************************************************
//
//�s���{�[��
//Author::Takano Minto
//
//**************************************************
#ifndef _PINBALL_H_
#define _PINBALL_H_

#include "main.h"

//==================================================
//�s���{�[���̍\���̂̒�`
//==================================================
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
}PINBALL;

//==================================================
//�v���g�^�C�v�錾
//==================================================
void InitPinball();				//������
void UninitPinball();			//�I��
void UpdatePinball();			//�X�V
void DrawPinball();				//�`��
void HitPinball();				//�����蔻��
void DestPinBall();				//�s���{�[���̏�����ʒu�̐ݒ�
bool PinCollision(D3DXVECTOR3 pos1, float fRadius1, D3DXVECTOR3 pos2, float fRadius2);
void SetPinBall(D3DXVECTOR3 pos);

#endif // !_PINBALL_H_


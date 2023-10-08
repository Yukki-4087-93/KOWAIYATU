//**************************************************
//
//�|�[�Y
//Author::Takano Minto
//
//**************************************************
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

//==================================================
//�|�[�Y���j���[�̍\����
//==================================================
typedef enum
{
	POUSE_MENU_COUNTINUE = 0,
	POUSE_MENU_RETRY,
	POUSE_MENU_QUIT,
	POUSE_MENU_MAX
}PAUSE_MENU;

//==================================================
//�|�[�Y�̍\���̂̒�`
//==================================================
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXCOLOR col;							//�C���n
}PAUSE;

//==================================================
//�v���g�^�C�v�錾
//==================================================
void InitPause();
void UninitPause();
void UpdatePause();
void DrawPause();

#endif // !_PAUSE_H_


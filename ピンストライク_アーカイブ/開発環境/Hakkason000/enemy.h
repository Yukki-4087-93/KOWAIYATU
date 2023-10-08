//------------------------------------------------------
//
//�G�l�~�[
//Author;takano
//
//------------------------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include"main.h"

//-----------------------
//�}�N����`
//-----------------------
#define	MAX_ENEMY			(1280)						//�G�l�~�[�ő吔
#define NUM_ENEMY			(3)							//�G�l�~�[�̎��
#define ENEMY_SIZE			(10)						//�G�l�~�[�̃T�C�Y�̔���
#define ENEMY_MAXSIZE		(20)						//�G�l�~�[�̃T�C�Y

//-----------------------
//�G�l�~�[�̏��
//-----------------------
typedef enum
{
	ENEMYSTATE_NORMAL = 0,				//�ʏ���
	ENEMYSTATE_DAMAGE,					//�_���[�W���
	ENEMYSTATE_MAX
}ENEMYSTATE;

//-----------------------
//�G�l�~�[�̍\���̂̒�`
//-----------------------
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 move;						//�ړ�
	D3DXVECTOR3 size;						//�T�C�Y
	int nType;								//���
	int nPattern;							//�s���p�^�[��
	ENEMYSTATE state;						//���
	int nCounterState;						//��ԊǗ��J�E���^�[
	int nLife;								//�̗�
	bool bUse;								//�G�l�~�[���g�p�����ۂ�
	
}Enemy;

//-----------------------
//�v���g�^�C�v�錾
//-----------------------
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move,int nType,int nPattern);
void HitEnemy(int nCntEnemy, int nDamage);
Enemy* GetEnemy(void);

#endif // !_ENEMY_H_
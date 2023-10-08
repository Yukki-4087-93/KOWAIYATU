//**************************************************
//
//��Q��
//Author::Takano Minto
//
//**************************************************

//==================================================
//�C���N���[�h�t�@�C��
//==================================================
#include"obstacle.h"

//==================================================
//�萔��`
//==================================================
const float Gravity = 0.088f;
const float WD_OBSTACLE = 25.0f;
const float HI_OBSTACLE = 25.0f;
const int MAX_OBSTACLE = 50;

//==================================================
//�O���[�o���ϐ�
//==================================================
OBSTACLE g_Obj[MAX_OBSTACLE];								// ��Q���̃|�C���^
//LPDIRECT3DTEXTURE9 g_pTextureObstacle = NULL;			// �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffObstacle = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

//==================================================
//������
//==================================================
void InitObstacle()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�̃|�C���^

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffObstacle, NULL);

	for (int i = 0; i < MAX_OBSTACLE; i++)
	{// �\���̂̏�����
		g_Obj[i].pos = D3DXVECTOR3(640.0f, 110.0f, 0.0f);		// �ʒu�̏�����
		g_Obj[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �p�x�̏�����
		g_Obj[i].siz = D3DXVECTOR3(25.0f, 25.0f, 0.0f);		// �p�x�̏�����
		g_Obj[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �F�̏�����
	}

	//D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//bullet000.png", &g_pTextureObstacle);

	VERTEX_2D* pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@���R�b�N�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffObstacle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_OBSTACLE; nCntBlock++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_Obj[nCntBlock].pos.x - WD_OBSTACLE, g_Obj[nCntBlock].pos.y - HI_OBSTACLE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Obj[nCntBlock].pos.x + WD_OBSTACLE, g_Obj[nCntBlock].pos.y - HI_OBSTACLE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Obj[nCntBlock].pos.x - WD_OBSTACLE, g_Obj[nCntBlock].pos.y + HI_OBSTACLE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Obj[nCntBlock].pos.x + WD_OBSTACLE, g_Obj[nCntBlock].pos.y + HI_OBSTACLE, 0.0f);

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

		pVtx += 4;				//�f�f�f�[�^��4���i��
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffObstacle->Unlock();

}

//==================================================
//�I��
//==================================================
void UninitObstacle()
{
	////�e�N�X�`���̔j��
	//if (g_pTextureObstacle != NULL)
	//{
	//	g_pTextureObstacle->Release();
	//	g_pTextureObstacle = NULL;
	//}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffObstacle != NULL)
	{
		g_pVtxBuffObstacle->Release();
		g_pVtxBuffObstacle = NULL;
	}
}

//==================================================
//�X�V
//==================================================
void UpdateObstacle()
{
	//HitObstacle();	//�q�b�g����

	//DownCounter();	//�ʒu��ύX���邩�ǂ���

	//MoveDown();		//�ړ��ʂ̐ݒ�

	//DestObstacle();	//�{�[���̈ʒu�ύX
}

//==================================================
//�`��
//==================================================
void DrawObstacle()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̃|�C���^���擾

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffObstacle, 0, sizeof(VERTEX_2D));

	//�|���S���̕`��
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//==================================================
//�����蔻��
//==================================================
void HitObstacle()
{
	
}

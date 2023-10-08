//**************************************************
//
//�w�i���
//Author::Takano Minto
//
//**************************************************
#include"bg2.h"

//==================================================
//�O���[�o���ϐ�
//==================================================
LPDIRECT3DTEXTURE9 g_pTextureBG2 = NULL;					//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG2 = NULL;			//���_�o�b�t�@�ւ̃|�C���^

//==================================================
//������
//==================================================
void InitBG2()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�̃|�C���^

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG2, NULL);

	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//000.png", &g_pTextureBG2);

	VERTEX_2D* pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@���R�b�N�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBG2->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
	g_pVtxBuffBG2->Unlock();

}

//==================================================
//�I��
//==================================================
void UninitBG2()
{
	//�e�N�X�`���̔j��
	if (g_pTextureBG2 != NULL)
	{
		g_pTextureBG2->Release();
		g_pTextureBG2 = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBG2 != NULL)
	{
		g_pVtxBuffBG2->Release();
		g_pVtxBuffBG2 = NULL;
	}
}

//==================================================
//�X�V
//==================================================
void UpdateBG2()
{

}

//==================================================
//�`��
//==================================================
void DrawBG2()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̃|�C���^���擾

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBG2);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBG2, 0, sizeof(VERTEX_2D));

	//�|���S���̕`��
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,
		0,
		2);
}
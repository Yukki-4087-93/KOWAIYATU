//**************************************************
//
//�T�E���h
//Author::Takano Minto
//
//**************************************************

//==================================================
// �C���N���[�h�t�@�C��
//==================================================
#include "sound.h"
#include <assert.h>

//==================================================
// �p�����[�^�\���̒�`
//==================================================
typedef struct
{
	char *pFilename;	// �t�@�C����
	int nCntLoop;		// ���[�v�J�E���g
} SOUNDPARAM;

//==================================================
// �v���g�^�C�v�錾
//==================================================
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

//==================================================
// �O���[�o���ϐ�
//==================================================
IXAudio2 *g_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
IXAudio2MasteringVoice *g_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
BYTE *g_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
DWORD g_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

// �e���f�ނ̃p�����[�^
SOUNDPARAM g_aParam[SOUND_LABEL_MAX] =
{
	{"Data/BGM/op.wav", -1},					// BGM0
	{"Data/BGM/game.wav", -1},					// BGM1
	{"Data/BGM/ranking.wav", -1},					// BGM2
	{ "Data/BGM/nennen.wav", -1 },					// BGM2
	{"Data/BGM/karasugyaku.wav", -1},					// BGM2
	{"Data/BGM/tooryanse.wav", -1},					// BGM2
	{"Data/BGM/sanbika_tal��is.wav", -1},					// BGM2
	{"Data/SE/000.wav", 0},					// SE0
	{"Data/SE/001.wav", 0},					// SE1
	{"Data/SE/002.wav", 0},					// SE2sanbika_tal��is
	{"Data/SE/003.wav", 0},					// SE3karasugyaku
	{"Data/SE/004.wav", 0},					// SE4tooryanse
	{"Data/SE/mouiikai1.wav", 0},					// SE4
	{"Data/SE/himei_kyaa_reverb.wav", 0},					// SE4
	{"Data/SE/arigato.wav", 0},			// SE4
	{"Data/SE/sayonara.wav", 0}	,				// SE4
	{"Data/SE/waraiufufu.wav", 0}					// SE4
};

//==================================================
// ����������
//==================================================
void InitSound()
{
	HRESULT hr;

	// COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&g_pXAudio2, 0);
	if(FAILED(hr))
	{
		// COM���C�u�����̏I������
		CoUninitialize();

		assert(false);	// XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s
	}
	
	// �}�X�^�[�{�C�X�̐���
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);
	if(FAILED(hr))
	{
		if(g_pXAudio2)
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			g_pXAudio2->Release();
			g_pXAudio2 = NULL;
		}

		// COM���C�u�����̏I������
		CoUninitialize();

		assert(false);	// �}�X�^�[�{�C�X�̐����Ɏ��s
	}

	// �T�E���h�f�[�^�̏�����
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		HANDLE hFile = NULL;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// �o�b�t�@�̃N���A
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// �T�E���h�f�[�^�t�@�C���̐���
		hFile = CreateFile(g_aParam[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if(hFile == INVALID_HANDLE_VALUE)
		{
			assert(false);	// �T�E���h�f�[�^�t�@�C���̐����Ɏ��s���Ă܂��B
		}

		if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// �t�@�C���|�C���^��擪�Ɉړ�
			assert(false);	// �T�E���h�f�[�^�t�@�C���̐����Ɏ��s���Ă܂��B
		}
	
		// WAVE�t�@�C���̃`�F�b�N
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			assert(false);	// �T�C�Y���傫���̂œǂݍ��߂Ă��܂���B
		}
		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if(FAILED(hr))
		{
			assert(false);	// WAVE�t�@�C���̃`�F�b�N�����Ɏ��s
		}
		if(dwFiletype != 'EVAW')
		{
			assert(false);	// WAVE����Ȃ��t�@�C���ǂݍ���ł܂��B
		}
	
		// �t�H�[�}�b�g�`�F�b�N
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			assert(false);	// �Ή����Ă��Ȃ��t�@�C���ǂݍ���ł܂��B
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if(FAILED(hr))
		{
			assert(false);	// �t�H�[�}�b�g�̓ǂݍ��݂Ɏ��s���܂����B
		}

		// �I�[�f�B�I�f�[�^�ǂݍ���
		hr = CheckChunk(hFile, 'atad', &g_aSizeAudio[nCntSound], &dwChunkPosition);
		if(FAILED(hr))
		{
			assert(false);	// �f�[�^���ǂݍ��߂Ă܂���B
		}
		
		// �I�[�f�B�I�f�[�^�̓��I�m��
		g_apDataAudio[nCntSound] = (BYTE*)malloc(g_aSizeAudio[nCntSound]);

		hr = ReadChunkData(hFile, g_apDataAudio[nCntSound], g_aSizeAudio[nCntSound], dwChunkPosition);
		if(FAILED(hr))
		{
			assert(false);	// �f�[�^���ǂݍ��݂Ɏ��s���Ă��܂��B
		}
	
		// �\�[�X�{�C�X�̐���
		hr = g_pXAudio2->CreateSourceVoice(&g_apSourceVoice[nCntSound], &(wfx.Format));
		if(FAILED(hr))
		{
			assert(false);	// �\�[�X�{�C�X�̐����Ɏ��s���Ă��܂��B
		}

		// �o�b�t�@�̒l�ݒ�
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = g_aSizeAudio[nCntSound];
		buffer.pAudioData = g_apDataAudio[nCntSound];
		buffer.Flags      = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount  = g_aParam[nCntSound].nCntLoop;

		// �I�[�f�B�I�o�b�t�@�̓o�^
		g_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);

		// �t�@�C�����N���[�Y
		CloseHandle(hFile);
	}
}

//==================================================
// �I������
//==================================================
void UninitSound()
{
	// �ꎞ��~
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound])
		{
			// �ꎞ��~
			g_apSourceVoice[nCntSound]->Stop(0);
	
			// �\�[�X�{�C�X�̔j��
			g_apSourceVoice[nCntSound]->DestroyVoice();
			g_apSourceVoice[nCntSound] = NULL;
	
			// �I�[�f�B�I�f�[�^�̊J��
			free(g_apDataAudio[nCntSound]);
			g_apDataAudio[nCntSound] = NULL;
		}
	}
	
	// �}�X�^�[�{�C�X�̔j��
	g_pMasteringVoice->DestroyVoice();
	g_pMasteringVoice = NULL;
	
	if(g_pXAudio2)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		g_pXAudio2->Release();
		g_pXAudio2 = NULL;
	}
	
	// COM���C�u�����̏I������
	CoUninitialize();
}

//==================================================
// �Z�O�����g�Đ�(�Đ����Ȃ��~)
//==================================================
HRESULT PlaySound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_aSizeAudio[label];
	buffer.pAudioData = g_apDataAudio[label];
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount  = g_aParam[label].nCntLoop;

	// ��Ԏ擾
	g_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_apSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_apSourceVoice[label]->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	g_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// �Đ�
	g_apSourceVoice[label]->Start(0);

	return S_OK;
}

//==================================================
// �Z�O�����g��~(���x���w��)
//==================================================
void StopSound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	g_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_apSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_apSourceVoice[label]->FlushSourceBuffers();
	}
}

//==================================================
// �Z�O�����g��~(�S��)
//==================================================
void StopAll()
{
	// �ꎞ��~
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound])
		{
			// �ꎞ��~
			g_apSourceVoice[nCntSound]->Stop(0);

			// �I�[�f�B�I�o�b�t�@�̍폜
			g_apSourceVoice[nCntSound]->FlushSourceBuffers();
		}
	}
}

//==================================================
// ���ʐݒ�
// �T�v : ������g���Ή��ʂ̕ύX���ł��܂��B
// �������A�g�p�������x���͏��������Ă܂��傤�B
//==================================================
void SetVolume(SOUND_LABEL lavel, float vol)
{
	// �Ή��������x���̉��ʂ�ݒ肷��
	g_apSourceVoice[lavel]->SetVolume(vol);
}

//==================================================
// �����ݒ�
// �T�v : ������g���Α��x�̕ύX���ł��܂��B
// �������A�g�p�������x���͏��������Ă܂��傤�B
//==================================================
void SetPitch(SOUND_LABEL lavel, float pih)
{
	// �Ή��������x���̉�����ݒ肷��
	g_apSourceVoice[lavel]->SetFrequencyRatio(pih);
}

//==================================================
// �`�����N�̃`�F�b�N
//==================================================
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;
	
	if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if(dwChunkType == format)
		{
			*pChunkSize         = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if(dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}
	
	return S_OK;
}

//==================================================
// �`�����N�f�[�^�̓ǂݍ���
//==================================================
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}


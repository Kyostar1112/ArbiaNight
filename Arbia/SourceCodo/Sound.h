#ifndef _C_SOUND_H_
#define _C_SOUND_H_

#include <Windows.h>

//ײ����.
#pragma comment( lib, "winmm.lib" )



//�������ޯ̧.
const int STR_BUFF_MAX = 256;


	//-----  -----//


//============================================================
//	����޸׽.
//		midi, mp3, wav�`��̧�ق̍Đ��E��~�����s��.
//============================================================
class clsSound
{
public:
	clsSound();
	~clsSound();

	//�T�E���h�\����.
	struct SOUND_DATA
	{
		char sAlias[STR_BUFF_MAX];	//�G�C���A�X��.
		char sPath[STR_BUFF_MAX];	//�t�@�C���p�X (�uBGM�vor�uSE�v����ł悢 ).
		int  iMaxVolume;			//�ő剹��.
	};


	//����̧�ق��J��.
	bool Open( LPCTSTR sFName, const char *sAlias, HWND hWnd );

	//����̧�ق����.
	bool Close();

	//�Đ��֐�.
	bool Play( bool bNotify = false );

	//��~�֐�.
	bool Stop();

//	//�ꎞ��~.
//	bool Pause();
//	//�ꎞ��~�̉���.
//	bool Resume();


	//�����߂��֐�(�Đ��ʒu������).
	bool SeekToStart();

	//�����߂��čĐ�.
	void SeekPlay( bool bNotify = false ){
		SeekToStart();
		Play( bNotify );
	}

	//��Ԏ擾�֐�.
	bool GetStatus( char *sStatus );

	//���̒�~���m�F����֐�.
	bool IsStopped();

	//���̍Đ������m�F����֐�.
	bool IsPlaying();


	//���ʂ�ݒ肷��.
	bool SetVolume( int iVolume );
	//�ő剹�ʂ�ݒ肷��.
	void SetMaxVolume( int iVolume = 1000 ){
		m_iMaxVol = iVolume;
	}

	//���̉��̍ő剹�ʂƍő剹��(1000)�̊�����Ԃ�.
	void GetMaxVolRate( int& iVol ){
		float fRate = (float)m_iMaxVol / 1000.0f;
		iVol = (int)( (float)iVol * fRate );
	}



private:
	//�����ݒ�.
	void	SetInitParam( const char *sAlias, HWND hWnd );

	HWND	m_hWnd;					//����޳�����.
	char	m_sAlias[STR_BUFF_MAX];	//��ر�.


	int		m_iMaxVol;//�ő剹��.

};

#endif//#define _C_SOUND_H_
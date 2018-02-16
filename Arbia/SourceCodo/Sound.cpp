#include "Sound.h"
#include <stdio.h>



//�ݽ�׸�.
clsSound::clsSound()
{
	ZeroMemory( this, sizeof( clsSound ) );
}

//�޽�׸�.
clsSound::~clsSound()
{
}


//����̧�ق��J��.
bool clsSound::Open( LPCTSTR sFName, const char *sAlias, HWND hWnd )
{
	//�����ݒ�.
	SetInitParam( sAlias, hWnd );

	//�����.
	char command[STR_BUFF_MAX] = "open Data\\Sound\\";//�ʓ|���߽����������ȗ�.

	strcat_s( command, sizeof( command ), sFName );		//̧�ٖ�������.
	strcat_s( command, sizeof( command ), " type mpegvideo alias " );//�u type mpegvideo �v: ���������邱�ƂŁAwav��mp3�Ɠ����悤�ɊJ��(������)�̂ŁA���ʂ̕ω����󂯕t����悤�ɂȂ�.
	strcat_s( command, sizeof( command ), m_sAlias );	//��ر������� : ��ر�(Ư�Ȱт̂悤�Ȃ���).

	if( mciSendString( command, NULL, 0, m_hWnd ) == 0 ){
		return true;
	}
	return false;
}

//����̧�ق����.
bool clsSound::Close()
{
	//�����.
	char command[STR_BUFF_MAX] = "close ";
	strcat_s( command, sizeof( command ), m_sAlias );	//��ر�������.
													//��ر�(Ư�Ȱт̂悤�Ȃ���).
	if( mciSendString( command, NULL, 0, m_hWnd ) == 0 ){
		return true;
	}
	return false;
}

//�Đ��֐�.
bool clsSound::Play( bool bNotify )
{
	//�����.
	char command[STR_BUFF_MAX] = "play ";
	strcat_s( command, sizeof( command ), m_sAlias );	//��ر�������.

	//	ٰ�߂���ꍇү���ނ𑗂�.
	if( bNotify ){
		strcat_s( command, sizeof( command ), " notify" );
		//notify: �������I�������Ƃ���hWnd��MM_MCINOTIFYү���ނ��߽Ă���.
	}

	if( mciSendString( command, NULL, 0, m_hWnd ) == 0 ){
		return true;
	}
	return false;
}

//��~�֐�.
bool clsSound::Stop()
{
	//�����.
	char command[STR_BUFF_MAX] = "stop ";
	strcat_s( command, sizeof( command ), m_sAlias );	//��ر�������.
													//��ر�(Ư�Ȱт̂悤�Ȃ���).
	if( mciSendString( command, NULL, 0, m_hWnd ) == 0 ){
		SeekToStart();
		return true;
	}
	return false;
}

////�ꎞ��~.
//bool clsSound::Pause()
//{
//	//�����.
//	char command[STR_BUFF_MAX] = "pause ";
//	strcat_s( command, sizeof( command ), m_sAlias );	//��ر�������.
//													//��ر�(Ư�Ȱт̂悤�Ȃ���).
//	if( mciSendString( command, NULL, 0, m_hWnd ) == 0 ){
//		SeekToStart();
//		return true;
//	}
//	return false;
//}
//
////�ꎞ��~�̉���.
//bool clsSound::Resume()
//{
//	//�����.
//	char command[STR_BUFF_MAX] = "resume ";
//	strcat_s( command, sizeof( command ), m_sAlias );	//��ر�������.
//													//��ر�(Ư�Ȱт̂悤�Ȃ���).
//	if( mciSendString( command, NULL, 0, m_hWnd ) == 0 ){
//		SeekToStart();
//		return true;
//	}
//	return false;
//}



//�����߂��֐�(�Đ��ʒu������).
bool clsSound::SeekToStart()
{
	//�����.
	char command[STR_BUFF_MAX] = "seek ";

	strcat_s( command, sizeof( command ), m_sAlias );	//��ر�������.
	strcat_s( command, sizeof( command ), " to start" );

	if( mciSendString( command, NULL, 0, m_hWnd ) == 0 ){
		return true;
	}
	return false;
}


//��Ԏ擾�֐�.
//	sStatus �̔z���256�ȉ��ɂ��邱��.
//���������A��Ԃ��擾����ꍇ�́A�Đ����Ɂunotify�v��ݒ肵�A.
//	����޳����ق�ү���ނ𑗂��Ă����K�v������.
bool clsSound::GetStatus( char *sStatus )
{
	//�����.
	char command[STR_BUFF_MAX] = "status ";
	strcat_s( command, sizeof( command ), m_sAlias );	//��ر�������.
	strcat_s( command, sizeof( command ), " mode" );

	if( mciSendString( command, sStatus, ( STR_BUFF_MAX - 1 ), m_hWnd ) == 0 ){
		return true;
	}
	return false;
}


//���̒�~���m�F����֐�.
bool clsSound::IsStopped()
{
	char sStatus[STR_BUFF_MAX] = "";

	//��Ԏ擾.
	if( GetStatus( sStatus ) ){
		//�������r.
		if( strcmp( sStatus, "stopped" ) == 0 ){
			return true;
		}
	}
	return false;
}

//���̍Đ������m�F����֐�.
bool clsSound::IsPlaying()
{
	char sStatus[STR_BUFF_MAX] = "";

	//��Ԏ擾.
	if( GetStatus( sStatus ) ){
		//�������r.
		if( strcmp( sStatus, "playing" ) == 0 ){
			return true;
		}
	}
	return false;
}

//============================================================
//	���ʂ�ݒ肷��.
//============================================================
bool clsSound::SetVolume( int ivolume )
{
	//���l�̊ۂ�.
	if( ivolume > 1000 )	{ ivolume = 1000; }
	else if( ivolume < 0 )	{ ivolume = 0	; }
	
	//���ʂ𕶎���ɕϊ�.
	char sVolume[STR_BUFF_MAX] = "";
	sprintf_s( sVolume, sizeof( sVolume ), "%d", ivolume );

	//�����.
	char command[STR_BUFF_MAX] = "setaudio ";

	strcat_s( command, sizeof( command ), m_sAlias );	//��ر�������.
	strcat_s( command, sizeof( command ), " volume to " );
	strcat_s( command, sizeof( command ), sVolume );//���ʂ�����.

	if( mciSendString( command, NULL, 0, m_hWnd ) == 0 ){
		return true;
	}
	return false;
}



//*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
//*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*


//============================================================
//�����ݒ�.
//============================================================
void clsSound::SetInitParam( const char *sAlias, HWND hWnd )
{
	//����޳����ٳ���޳����ق�n��.
	m_hWnd = hWnd;

	//��ر�.
	strcpy_s( m_sAlias, sizeof( m_sAlias ), sAlias );
}

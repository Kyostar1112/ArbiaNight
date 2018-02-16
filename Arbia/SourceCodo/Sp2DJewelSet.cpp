#include "Sp2DJewelSet.h"

#define sFILE_PATH_JEWEL "Data\\Image\\Jewel.png"

//��.
//�オ��.
#define ALIAS_NAME_UP "UiResultJewelUp"
#define  FILE_PATH_UP "SE\\600Result\\010JewelUp.wav"
const int     iVOL_UP = 1000;

//����(���n?).
#define ALIAS_NAME_SHINE "UiResultJewelShine"
#define  FILE_PATH_SHINE "SE\\600Result\\020JewelShine.wav"
const int     iVOL_SHINE = 1000;

//MulDisp�p.
const float fMUL_DISP_JEWEL = 1.0f;

//�傫��.
const float fSCALE_MAX = 1.0f;
const float fCHANGE_SCALE = fSCALE_MAX / 12.0f;


clsJewerSet::clsJewerSet()
{
	m_smpModel = nullptr;
	m_bEnd = false;
	m_bDown = false;
	m_bGet = false;
	m_vMove = { 0.0f, 0.0f, 0.0f };
	m_fAcc = 0.0f;

		m_pSe = NULL;
}

clsJewerSet::~clsJewerSet()
{
//	for( int i=0; i<enS_MAX; i++ ){
		m_pSe->Stop();
		m_pSe->Close();
		delete m_pSe;
		m_pSe = NULL;
//	}

	m_smpModel.reset();
}


void clsJewerSet::Create( HWND hWnd,
	ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11,
	int iNo )
{
	m_smpModel = make_unique<clsJewel>();
	m_smpModel->Create( pDevice11, pContext11, sFILE_PATH_JEWEL );
	m_smpModel->MulDisp( fMUL_DISP_JEWEL );

	SetSe( hWnd, iNo );
}


void clsJewerSet::Move(){
	m_smpModel->AddPos( m_vMove );

	m_vMove.y += m_fAcc;
	if( m_vMove.y > 0.0f ) m_bDown = true;

	AddScale( fCHANGE_SCALE );
}



void clsJewerSet::AddScale( float fScale )
{
	m_fScale += fScale;

	if		( m_fScale < 0.0f )			m_fScale = 0.0f;
	else if ( m_fScale > fSCALE_MAX )	m_fScale = fSCALE_MAX;

	m_smpModel->m_fScale = m_fScale;
}

void clsJewerSet::ReSet()
{
	m_bEnd = false;
	m_bDown = false;
	m_bGet = false;
	Stop();
	SetScale( 0.0f );
}




void clsJewerSet::SetSe( HWND hWnd, int iNo )
{
#if 0
	//�T�E���h�\����.
	clsSound::SOUND_DATA tmpSData[enS_MAX] =
	{
		{ ALIAS_NAME_UP,	FILE_PATH_UP,	iVOL_UP	},
//		{ ALIAS_NAME_SHINE,	FILE_PATH_SHINE,iVOL_SHINE },
	};

	//�T�E���h�N���X�쐬.
	for( int i=0; i<enS_MAX; i++ ){
		m_pSe[i] = new clsSound;
		//���O.
		char cAliasName[STR_BUFF_MAX] = "";
		strcat_s( cAliasName, sizeof( cAliasName ), tmpSData[i].sAlias );
		//�ԍ�.
		char cNumber[] = "  ";
		_itoa_s( iNo, cNumber, 10 );
		//���O�Ɣԍ�����.
		strcat_s( cAliasName, sizeof( cAliasName ), cNumber );
		//�쐬.
		m_pSe[i]->Open( tmpSData[i].sPath, cAliasName, hWnd );
		//�����ʏ�����.
		m_pSe[i]->SetVolume( tmpSData[i].iMaxVolume );
		//�ő剹�ʐݒ�.
		m_pSe[i]->SetMaxVolume( tmpSData[i].iMaxVolume );
	}
#else
	m_pSe = new clsSound;
	//���O.
	char cAliasName[STR_BUFF_MAX] = "";
	strcat_s( cAliasName, sizeof( cAliasName ), ALIAS_NAME_UP );
	//�ԍ�.
	char cNumber[] = "  ";
	_itoa_s( iNo, cNumber, 10 );
	//���O�Ɣԍ�����.
	strcat_s( cAliasName, sizeof( cAliasName ), cNumber );
	//�쐬.
	m_pSe->Open( FILE_PATH_UP, cAliasName, hWnd );
	//�����ʏ�����.
	m_pSe->SetVolume( iVOL_UP );
	//�ő剹�ʐݒ�.
	m_pSe->SetMaxVolume( iVOL_UP );
#endif
	//----- SE �I�� -----//
}
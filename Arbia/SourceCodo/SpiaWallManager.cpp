#include "Resource.h"
#include "SpiaWallManager.h"

//��.
//�U��.
#define ALIAS_NAME_VIB "SpiaWallVib"
#define FILE_PATH_VIB "SE\\300Trap\\100SpiaVib.wav"
const int iVOL_VIB = 1000;

//�オ��.
#define ALIAS_NAME_UP "SpiaWallTop"
#define FILE_PATH_UP "SE\\300Trap\\111SpiaTopwall.wav"					
const int iVOL_UP = 1000;

//������.
#define ALIAS_NAME_DOWN "SpiaWallDown"
#define FILE_PATH_DOWN "SE\\300Trap\\130SpiaClose.wav"					
const int iVOL_DOWN = 1000;


//�ғ��^�C�~���O.
const int iTIME_MUTUAL_FIRST_UP = 0;	//���������J�n.
const int iTIME_MUTUAL_FIRST_DOWN = 150;	//�������݊J�n.
const int iTIME_MUTUAL_SECOND_UP = 120;	//���������J�n.
const int iTIME_MUTUAL_SECOND_DOWN = iTIME_MUTUAL_SECOND_UP + ( iTIME_MUTUAL_FIRST_DOWN - iTIME_MUTUAL_FIRST_UP );//�������݊J�n.
const int iTIME_MUTUAL_LOOP = iTIME_MUTUAL_SECOND_DOWN;		//���[�v.	





//�ǂ̐�.
const char cWALL_MAX = 2;
//���̐�(�Б�).
const int iSPIA_MAX = 6;

//���̂��������Ȃ�т��炵��.
const float fFLOOR_X_OFFSET = 0.125f;
//���̂��������Ȃ�т��炵��.
const float fFLOOR_Y_OFFSET = 1.0f;
const float fFLOOR_Y_OFFSET_FIRST = 0.5f;


//�X�e�[�W��.
const float fSTAGE_WIDHT = 10.0f;
//��������̋���.
const float fWALL_SIDE_OFFSET = fSTAGE_WIDHT / 2.0f;
////�ǔ���̈ړ���.
const float fWALL_OFFSET = -0.25f;


//�ǂ̍���.
const float fWALL_HEIGHT = (float)iSPIA_MAX * fFLOOR_Y_OFFSET - fFLOOR_Y_OFFSET_FIRST;



clsSpiaWallMgr::clsSpiaWallMgr()
{
}

clsSpiaWallMgr::~clsSpiaWallMgr()
{
	Release();
}



void clsSpiaWallMgr::CreateSpia( HWND hWnd, int iNo, int iMoveMode )
{
	m_enMoveMode = (enMode)iMoveMode;

	//----- ���f�� -----//
	//��.
	m_iSpiaMax = iSPIA_MAX;
	//��.
	m_ppSpiaL = new clsSpiaWall*[m_iSpiaMax];
	for( int i=0; i<m_iSpiaMax; i++ ){
		m_ppSpiaL[i] = new clsSpiaWall;
		m_ppSpiaL[i]->Create( false, i );
		m_ppSpiaL[i]->AttachModel( 
			clsResource::GetInstance()->GetStaticModels( 
				clsResource::enST_MODEL_SPIA_OF_WALL ) );
		m_ppSpiaL[i]->SetRotationZ( -(float)M_PI_2 );
	}
	//�E.
	m_ppSpiaR = new clsSpiaWall*[m_iSpiaMax];
	for( int i=0; i<m_iSpiaMax; i++ ){
		m_ppSpiaR[i] = new clsSpiaWall;
		m_ppSpiaR[i]->Create( true, i );
		m_ppSpiaR[i]->AttachModel( 
			clsResource::GetInstance()->GetStaticModels( 
				clsResource::enST_MODEL_SPIA_OF_WALL ) );
		m_ppSpiaR[i]->SetRotationZ( (float)M_PI_2 );
	}


	//����.
	for( char i=0; i<cWALL_MAX; i++ ){
		m_pSpiaWall[i] = new clsCharaStatic;
		m_pSpiaWall[i]->AttachModel(
			clsResource::GetInstance()->GetStaticModels( 
				clsResource::enST_MODEL_SPIA_WALL ) );
	}
	//----- SE -----//
	//�T�E���h�\����.
	clsSound::SOUND_DATA tmpSData[clsSpiaWall::enSOUND_MAX] =
	{
		{ ALIAS_NAME_VIB,	FILE_PATH_VIB,	iVOL_VIB	},
		{ ALIAS_NAME_UP,	FILE_PATH_UP,	iVOL_UP		},
		{ ALIAS_NAME_DOWN,	FILE_PATH_DOWN,	iVOL_DOWN	},
	};

	//�T�E���h�N���X�쐬.
	m_ppSe = new clsSound*[clsSpiaWall::enSOUND_MAX];
	for( int i=0; i<clsSpiaWall::enSOUND_MAX; i++ ){
		m_ppSe[i] = new clsSound;
		//�����ʏ�����.
		m_ppSe[i]->SetVolume( 0 );
		//���O.
		char cAliasName[STR_BUFF_MAX] = "";
		strcat_s( cAliasName, sizeof( cAliasName ), tmpSData[i].sAlias );
		//�ԍ�.
		char cNumber[] = "  ";
		_itoa_s( iNo, cNumber, 10 );
		//���O�Ɣԍ�����.
		strcat_s( cAliasName, sizeof( cAliasName ), cNumber );
		//�쐬.
		m_ppSe[i]->Open( tmpSData[i].sPath, cAliasName, hWnd );
		//�ő剹�ʐݒ�.
		m_ppSe[i]->SetMaxVolume( tmpSData[i].iMaxVolume );
	}
	//----- SE �I�� -----//



	//----- ���f�� �I�� -----//
	Init();
}


void clsSpiaWallMgr::Init()
{
	m_iTimer = 0;
	//��.
	for( int i=0; i<m_iSpiaMax; i++ ){
		float fOffset = fFLOOR_X_OFFSET;
		if( i % 2 != 0 ){
			//�o�Ă���.
			fOffset *= -1.0f;
		}

		//����.
		m_ppSpiaL[i]->SetPosition( 
		D3DXVECTOR3( 
			GetPositionX() - fWALL_SIDE_OFFSET + fOffset, 
			GetPositionY() + (float)i * fFLOOR_Y_OFFSET + fFLOOR_Y_OFFSET_FIRST,
			GetPositionZ() ) );
		m_ppSpiaL[i]->Init( m_ppSpiaL[i]->GetPosition(), false );

		//�E��.
//		fOffset *= -1.0f;
		m_ppSpiaR[i]->SetPosition( 
		D3DXVECTOR3( 
			GetPositionX() + fWALL_SIDE_OFFSET + fOffset,
			GetPositionY() + (float)i * fFLOOR_Y_OFFSET + fFLOOR_Y_OFFSET_FIRST,
			GetPositionZ() ) );
		m_ppSpiaR[i]->Init( m_ppSpiaR[i]->GetPosition(), true );
	}
}


void clsSpiaWallMgr::Release()
{
	//��.
	if( m_ppSe != NULL ){
		for( int i=0; i<clsSpiaWall::enSOUND_MAX; i++ ){
			m_ppSe[i]->Stop();
			m_ppSe[i]->Close();
			delete m_ppSe[i];
			m_ppSe[i] = NULL;
		}
		delete[] m_ppSe;
		m_ppSe = NULL;
	}
	//�I�u�W�F�N�g.
	if( m_pSpiaWall != NULL ){
		for( char i=0; i<cWALL_MAX; i++ ){
			m_pSpiaWall[i]->DetatchModel();
			delete m_pSpiaWall[i];
			m_pSpiaWall[i] = NULL;
		}
	}

	if( m_ppSpiaL != NULL ){
		for( int i=0; i<m_iSpiaMax; i++ ){
			m_ppSpiaL[i]->DetatchModel();
			delete m_ppSpiaL[i];
			m_ppSpiaL[i] = NULL;
		}
		delete[] m_ppSpiaL;
		m_ppSpiaL = NULL;
	}
	if( m_ppSpiaR != NULL ){
		for( int i=0; i<m_iSpiaMax; i++ ){
			m_ppSpiaR[i]->DetatchModel();
			delete m_ppSpiaR[i];
			m_ppSpiaR[i] = NULL;
		}
		delete[] m_ppSpiaR;
		m_ppSpiaR = NULL;
		m_iSpiaMax = 0;
	}
}


void clsSpiaWallMgr::Move( float fEarZ )
{
	m_fEarZ = fEarZ;
	//�����̃Z�b�g.
	switch( m_enMoveMode )
	{
	case enMODE_MUTUAL_L:
		m_iTimer ++;
		MoveMutualL();
		break;
	case enMODE_MUTUAL_R:
		m_iTimer ++;
		MoveMutualR();
		break;
	case enMODE_CLOSE_L:
		MoveCloseL();
		break;
	case enMODE_CLOSE_R:
		MoveCloseR();
		break;
//	default:
//		m_enMoveMode = enMODE_MUTUAL_L;
		break;
	}



	//����.
	//��яo�����ʉ��p.
	bool bSpiaUpSound = false;
	for( int i=0; i<m_iSpiaMax; i++ ){
		bSpiaUpSound = m_ppSpiaL[i]->Move();
	}
	//��яo����.
	if( bSpiaUpSound ){
		PlaySe( clsSpiaWall::enSOUND_UP );
	}

	for( int i=0; i<m_iSpiaMax; i++ ){
		bSpiaUpSound = m_ppSpiaR[i]->Move();
	}
	//��яo����.
	if( bSpiaUpSound ){
		PlaySe( clsSpiaWall::enSOUND_UP );
	}


	//���Ǎ��W.
	m_pSpiaWall[0]->SetPosition( m_ppSpiaL[0]->GetPosition() );
	m_pSpiaWall[0]->AddPositionX( -fSTAGE_WIDHT - fWALL_OFFSET );
	m_pSpiaWall[0]->AddPositionY( fWALL_HEIGHT );
	m_pSpiaWall[1]->SetPosition( m_ppSpiaR[0]->GetPosition() );
	m_pSpiaWall[1]->AddPositionX( fWALL_OFFSET );
	m_pSpiaWall[1]->AddPositionY( fWALL_HEIGHT );
}

//����(������).
void clsSpiaWallMgr::MoveMutualL()
{
	//�ŏ���яo��.
	if( m_iTimer == iTIME_MUTUAL_FIRST_UP ){
		GoRight();
	}
	//�ŏ��̂��������.
	if( m_iTimer == iTIME_MUTUAL_FIRST_DOWN ){
		GoDown( 0 );
	}
	//���̂��яo��.
	if( m_iTimer == iTIME_MUTUAL_SECOND_UP ){
		GoLeft();
	}
	//���̂��������.
	if( m_iTimer == iTIME_MUTUAL_SECOND_DOWN ){
		GoDown( 1 );
	}
	//�^�C�}�[���[�v.
	if( m_iTimer == iTIME_MUTUAL_LOOP ){
		m_iTimer = -1;
	}
}
//����(�E����).
void clsSpiaWallMgr::MoveMutualR()
{
	//�ŏ���яo��.
	if( m_iTimer == iTIME_MUTUAL_FIRST_UP ){
		GoLeft();
	}
	//�ŏ��̂��������.
	if( m_iTimer == iTIME_MUTUAL_FIRST_DOWN ){
		GoDown( 1 );
	}
	//���̂��яo��.
	if( m_iTimer == iTIME_MUTUAL_SECOND_UP ){
		GoRight();
	}
	//���̂��������.
	if( m_iTimer == iTIME_MUTUAL_SECOND_DOWN ){
		GoDown( 0 );
	}
	//�^�C�}�[���[�v.
	if( m_iTimer == iTIME_MUTUAL_LOOP ){
		m_iTimer = -1;
	}
}
//����(������).
void clsSpiaWallMgr::MoveCloseL()
{

}
//����(�E����).
void clsSpiaWallMgr::MoveCloseR()
{

}





void clsSpiaWallMgr::SetPosition( D3DXVECTOR3 vPos )
{
	m_vPos = vPos;

	//�q���̍��W.
	for( int i=0; i<m_iSpiaMax; i++ ){
		float fOffset = fFLOOR_X_OFFSET;
		if( i % 2 != 0 ){
			//�o�Ă���.
			fOffset *= -1.0f;
		}

		m_ppSpiaL[i]->SetPosition( 
			D3DXVECTOR3( 
				GetPositionX() - fWALL_SIDE_OFFSET + fOffset, 
				GetPositionY() + (float)i * fFLOOR_Y_OFFSET + fFLOOR_Y_OFFSET_FIRST,
				GetPositionZ() ) );

		m_ppSpiaR[i]->SetPosition( 
			D3DXVECTOR3( 
				GetPositionX() + fWALL_SIDE_OFFSET + fOffset,
				GetPositionY() + (float)i * fFLOOR_Y_OFFSET + fFLOOR_Y_OFFSET_FIRST,
				GetPositionZ() ) );
	}



	//���Ǎ��W.
	m_pSpiaWall[0]->SetPosition( GetPosition() );
	m_pSpiaWall[0]->AddPositionX( 0.0f );
	m_pSpiaWall[0]->AddPositionY( fWALL_HEIGHT );
	m_pSpiaWall[1]->SetPosition( GetPosition() );
	m_pSpiaWall[1]->AddPositionX( fSTAGE_WIDHT );
	m_pSpiaWall[1]->AddPositionY( fWALL_HEIGHT );
}



void clsSpiaWallMgr::Render( D3DXMATRIX &mView, D3DXMATRIX &mProj,
				 D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye )
{
	for( int i=0; i<m_iSpiaMax; i++ ){
		m_ppSpiaL[i]->Render( mView, mProj, vLight, vEye );
		m_ppSpiaR[i]->Render( mView, mProj, vLight, vEye );
	}


	//��.
//	m_pSpiaWall[0]->Render( mView, mProj, vLight, vEye );
//	m_pSpiaWall[1]->Render( mView, mProj, vLight, vEye );
}

//���̂����蔻����Ԃ�.
COL_STATE* clsSpiaWallMgr::GetPointerSpiaCol( bool bRight, int i )
{
	if( bRight ){
		return m_ppSpiaR[i]->GetPointerCol();
	}
	else{
		return m_ppSpiaL[i]->GetPointerCol();
	}
	return NULL;
}


//���b�v.
void clsSpiaWallMgr::GoRight()
{
	PlaySe( clsSpiaWall::enSOUND_VIB );
	for( int i=0; i<m_iSpiaMax; i++ ){
		m_ppSpiaL[i]->GoRight();
	}
}
void clsSpiaWallMgr::GoLeft()
{
	PlaySe( clsSpiaWall::enSOUND_VIB );
	for( int i=0; i<m_iSpiaMax; i++ ){
		m_ppSpiaR[i]->GoLeft();
	}
}
//0:��, 1:�E, 2:����, ����ȊO:����.
void clsSpiaWallMgr::GoDown( int iRight )
{
	PlaySe( clsSpiaWall::enSOUND_DOWN );

	if( iRight == 0 ){
		for( int i=0; i<m_iSpiaMax; i++ ){
			m_ppSpiaL[i]->GoDown();
		}
	}
	else if( iRight == 1 ){
		for( int i=0; i<m_iSpiaMax; i++ ){
			m_ppSpiaR[i]->GoDown();
		}
	}
	else if( iRight == 2 ){
		for( int i=0; i<m_iSpiaMax; i++ ){
			m_ppSpiaL[i]->GoDown();
			m_ppSpiaR[i]->GoDown();
		}
	}
}

//============================================================
//	���ʉ�.
//============================================================
void clsSpiaWallMgr::PlaySe( clsSpiaWall::enSound enSe )
{
	//�Đ����鋗���Ȃ�.
	int vol = ChangeVolumeDistance( m_fEarZ, m_vPos.z );
	if( vol ){
		m_ppSe[enSe]->GetMaxVolRate( vol );
		m_ppSe[enSe]->SeekToStart();
		m_ppSe[enSe]->SetVolume( vol );
		m_ppSe[enSe]->Play();
	}
	//�Đ����Ȃ������Ȃ�.
	else{
		m_ppSe[enSe]->SetVolume( 0 );
	}
}

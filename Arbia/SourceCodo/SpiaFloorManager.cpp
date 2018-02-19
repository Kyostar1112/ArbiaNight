#include "Resource.h"
#include "SpiaFloorManager.h"


//��.
//�U��.
#define ALIAS_NAME_VIB "SpiaFloorVib"
#define FILE_PATH_VIB "SE\\300Trap\\100SpiaVib.wav"
const int iVOL_VIB = 1000;

//�オ��.
#define ALIAS_NAME_UP "SpiaFloorTop"
#define FILE_PATH_UP "SE\\300Trap\\110SpiaTop.wav"					
const int iVOL_UP = 1000;

//������.
#define ALIAS_NAME_DOWN "SpiaFloorDown"
#define FILE_PATH_DOWN "SE\\300Trap\\130SpiaClose.wav"					
const int iVOL_DOWN = 1000;



//�X�e�[�W����.
const float fSTAGE_WIDHT = 10.0f;
//�ǂ����̐�[����ǂꂾ�����炷��.
const float fWALL_OFFSET_Y = 0.4375f;

const int iFLOOR_MAX = 20;	//�����̐�.
const float fFLOOR_W_OFFSET = 0.5f;		//���Ƒ��̉��̊Ԋu.
const float fFLOOR_H_OFFSET = 0.0625f;		//��Ԗڂ�������ǂꂾ���グ�邩.
const float fFLOOR_H_OFFSET_SECOND = 0.25f;	//�����Ԗڂ�������ǂꂾ���グ�邩.


clsSpiaFlorMgr::clsSpiaFlorMgr()
{
	m_iSpiaMax = 0;

	m_ppSpia = nullptr;
	m_pSpiaWall = nullptr;

	m_ppSe = nullptr;
}

clsSpiaFlorMgr::~clsSpiaFlorMgr()
{
	Release();
}

void clsSpiaFlorMgr::Release()
{
	//��.
	if( m_ppSe != nullptr ){
		for( int i=0; i<clsSpiaFloor::enSOUND_MAX; i++ ){
			m_ppSe[i]->Stop();
			m_ppSe[i]->Close();
			delete m_ppSe[i];
			m_ppSe[i] = nullptr;
		}
		delete[] m_ppSe;
		m_ppSe = nullptr;
	}
	//�I�u�W�F�N�g.
	if( m_ppSpia != nullptr ){
		for( int i=0; i<m_iSpiaMax; i++ ){
			m_ppSpia[i]->DetatchModel();
			delete m_ppSpia[i];
			m_ppSpia[i] = nullptr;
		}
		delete[] m_ppSpia;
		m_ppSpia = nullptr;
		m_iSpiaMax = 0;
	}
	if( m_pSpiaWall != nullptr ){
		delete m_pSpiaWall;
		m_pSpiaWall = nullptr;
	}
}


void clsSpiaFlorMgr::CreateSpia( HWND hWnd, int iNo )
{
	if( m_ppSpia != nullptr || m_iSpiaMax ) return;
	if( m_pSpiaWall != nullptr ) return;
	if( m_ppSe != nullptr ) return;

	//----- ���f�� -----//
	//��.
	m_iSpiaMax = iFLOOR_MAX;
	m_ppSpia = new clsSpiaFloor*[m_iSpiaMax];
	for( int i=0; i<m_iSpiaMax; i++ ){
		m_ppSpia[i] = new clsSpiaFloor;

		m_ppSpia[i]->AttachModel( 
			clsResource::GetInstance()->GetStaticModels( 
				clsResource::enST_MODEL_SPIA ) );
	}

	//����.
	if( m_pSpiaWall != nullptr ) return;
	m_pSpiaWall = new clsCharaStatic;
	m_pSpiaWall->AttachModel(
		clsResource::GetInstance()->GetStaticModels( 
			clsResource::enST_MODEL_SPIA_WALL ) );
	//----- ���f�� �I�� -----//


	if( m_ppSe != nullptr ) return;
	//----- SE -----//
	//�T�E���h�\����.
	clsSound::SOUND_DATA tmpSData[clsSpiaFloor::enSOUND_MAX] =
	{
		{ ALIAS_NAME_VIB,	FILE_PATH_VIB,	iVOL_VIB	},
		{ ALIAS_NAME_UP,	FILE_PATH_UP,	iVOL_UP		},
		{ ALIAS_NAME_DOWN,	FILE_PATH_DOWN,	iVOL_DOWN	},
	};

	//�T�E���h�N���X�쐬.
	m_ppSe = new clsSound*[clsSpiaFloor::enSOUND_MAX];
	for( int i=0; i<clsSpiaFloor::enSOUND_MAX; i++ ){
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


	Init();
}

void clsSpiaFlorMgr::Init()
{
	if( m_ppSpia == nullptr ) return;

	//��.
	for( int i=0; i<m_iSpiaMax; i++ ){
		float fOffset = fFLOOR_H_OFFSET;
		bool bFlg = false;
		if( i % 2 != 0 ){
			//�������.
			fOffset = fFLOOR_H_OFFSET_SECOND;
			bFlg = true;
		}

		m_ppSpia[i]->SetPosition( 
		D3DXVECTOR3( 
			GetPositionX() - fSTAGE_WIDHT/2.0f + (float)i * fFLOOR_W_OFFSET + fFLOOR_W_OFFSET / 2.0f,
			GetPositionY() + fOffset, 
			GetPositionZ() ) );
		m_ppSpia[i]->Init( bFlg );
	}

	if( m_pSpiaWall == nullptr ) return;
	//���Ǎ��W.
	m_pSpiaWall->SetPosition( GetPosition() );
	m_pSpiaWall->AddPositionY( fWALL_OFFSET_Y );
	m_pSpiaWall->AddPositionX( -fSTAGE_WIDHT / 2.0f );
}


void clsSpiaFlorMgr::Update( float fEarZ )
{
	if( m_ppSpia == nullptr || m_ppSe == nullptr || m_pSpiaWall == nullptr ) return;

	//�ǂ̉���炷���̃t���O.
	clsSpiaFloor::enSound enSoundFlg;

	//����.
	for( int i=0; i<m_iSpiaMax; i++ ){
		//�����ɍ��킹�ăt���O���X�V.
		enSoundFlg = m_ppSpia[i]->Update();
	}

	//���ʉ��Đ��iMAX��SpiaFloor���̏������g���Ă���̂ł���ȏ�ł͖炳�Ȃ��j.
	if( enSoundFlg < clsSpiaFloor::enSOUND_MAX ){
		//��яo�����炬�����������~�߂�.
		if( enSoundFlg == clsSpiaFloor::enSOUND_UP ){
			m_ppSe[clsSpiaFloor::enSOUND_VIB]->Stop();
		}
		//�Đ�.
		PlaySe( enSoundFlg, fEarZ );
	}

	//���Ǎ��W.
	m_pSpiaWall->SetPositionY( m_ppSpia[0]->GetPositionY() );
	//�オ���Ă鎞��.�h����₷��
	//�������Ă��鎞�͎h����ɂ���.
	if( m_ppSpia[0]->GetMode() == clsSpiaFloor::enSFM_UNDER ||
		m_ppSpia[0]->GetMode() == clsSpiaFloor::enSFM_DOWN ){
		m_pSpiaWall->AddPositionY( fWALL_OFFSET_Y );
	}
	
}



void clsSpiaFlorMgr::Render( D3DXMATRIX &mView, D3DXMATRIX &mProj,
				 D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye )
{
	if( m_ppSpia == nullptr ) return;

	for( int i=0; i<m_iSpiaMax; i++ ){
		m_ppSpia[i]->Render( mView, mProj, vLight, vEye );
	}

//	//��.
//	m_pSpiaWall->Render( mView, mProj, vLight, vEye );

}

void clsSpiaFlorMgr::SetPosition( D3DXVECTOR3 vPos )
{
	if( m_ppSpia == nullptr || m_pSpiaWall == nullptr ) return;

	m_vPos = vPos;

	//�q���̍��W.
	for( int i=0; i<m_iSpiaMax; i++ ){
		m_ppSpia[i]->SetPosition( 
			D3DXVECTOR3( 
				GetPositionX() - fSTAGE_WIDHT/2.0f + (float)i * fFLOOR_W_OFFSET,
				GetPositionY(), 
				GetPositionZ() ) );
	}

	//���Ǎ��W.
	m_pSpiaWall->SetPosition( GetPosition() );
	m_pSpiaWall->AddPositionY( fWALL_OFFSET_Y );
	m_pSpiaWall->AddPositionX( -fSTAGE_WIDHT / 2.0f );
}

//���̂����蔻����Ԃ�.
COL_STATE* clsSpiaFlorMgr::GetPointerSpiaCol( int i )
{
	if( m_ppSpia == nullptr ) return nullptr;
	return m_ppSpia[i]->GetPointerCol();
}

//���̍ő吔.
int clsSpiaFlorMgr::GetSpiaMax()
{
	return m_iSpiaMax;
}

clsCharaStatic*	clsSpiaFlorMgr::GetWallPointer()
{
	return m_pSpiaWall;
}


//============================================================
//	���ʉ�.
//============================================================
void clsSpiaFlorMgr::PlaySe( clsSpiaFloor::enSound enSe, float fEarZ )
{
	if( m_ppSe == nullptr ) return;

	//�Đ����鋗���Ȃ�.
	int vol = ChangeVolumeDistance( fEarZ, m_vPos.z );
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


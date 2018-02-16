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





const float STAGE_WIDHT = 10.0f;
const float WALL_OFFSET_Y = 0.4375f;

const int iFLOOR_MAX = 20;	//�����̐�.
const float fFLOOR_W_OFFSET = 0.5f;
const float fFLOOR_H_OFFSET = 0.0625f;
const float fFLOOR_H_OFFSET_SECOND = 0.25f;


clsSpiaFlorMgr::clsSpiaFlorMgr()
{
}

clsSpiaFlorMgr::~clsSpiaFlorMgr()
{
	Release();
}

void clsSpiaFlorMgr::CreateSpia( HWND hWnd, int iNo )
{
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
	m_pSpiaWall = new clsCharaStatic;
	m_pSpiaWall->AttachModel(
		clsResource::GetInstance()->GetStaticModels( 
			clsResource::enST_MODEL_SPIA_WALL ) );
	//----- ���f�� �I�� -----//


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
			GetPositionX() - STAGE_WIDHT/2.0f + (float)i * fFLOOR_W_OFFSET + fFLOOR_W_OFFSET / 2.0f,
			GetPositionY() + fOffset, 
			GetPositionZ() ) );
		m_ppSpia[i]->Init( bFlg );
	}

	//���Ǎ��W.
	m_pSpiaWall->SetPosition( GetPosition() );
	m_pSpiaWall->AddPositionY( WALL_OFFSET_Y );
	m_pSpiaWall->AddPositionX( -STAGE_WIDHT / 2.0f );
}

void clsSpiaFlorMgr::Release()
{
	//��.
	if( m_ppSe != NULL ){
		for( int i=0; i<clsSpiaFloor::enSOUND_MAX; i++ ){
			m_ppSe[i]->Stop();
			m_ppSe[i]->Close();
			delete m_ppSe[i];
			m_ppSe[i] = NULL;
		}
		delete[] m_ppSe;
		m_ppSe = NULL;
	}
	//�I�u�W�F�N�g.
	if( m_ppSpia != NULL ){
		for( int i=0; i<m_iSpiaMax; i++ ){
			m_ppSpia[i]->DetatchModel();
			delete m_ppSpia[i];
			m_ppSpia[i] = NULL;
		}
		delete[] m_ppSpia;
		m_ppSpia = NULL;
		m_iSpiaMax = 0;
	}
	if( m_pSpiaWall != NULL ){
		delete m_pSpiaWall;
		m_pSpiaWall = NULL;
	}
}

void clsSpiaFlorMgr::Move( float fEarZ )
{
	//�ǂ̉���炷���̃t���O.
	clsSpiaFloor::enSound enSoundFlg;

	//����.
	for( int i=0; i<m_iSpiaMax; i++ ){
		//�����ɍ��킹�ăt���O���X�V.
		enSoundFlg = m_ppSpia[i]->Move();
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
		m_pSpiaWall->AddPositionY( WALL_OFFSET_Y );
	}
	
}



void clsSpiaFlorMgr::Render( D3DXMATRIX &mView, D3DXMATRIX &mProj,
				 D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye )
{
	for( int i=0; i<m_iSpiaMax; i++ ){
		m_ppSpia[i]->Render( mView, mProj, vLight, vEye );
	}

//	//��.
//	m_pSpiaWall->Render( mView, mProj, vLight, vEye );

}

void clsSpiaFlorMgr::SetPosition( D3DXVECTOR3 vPos )
{
	m_vPos = vPos;

	//�q���̍��W.
	for( int i=0; i<m_iSpiaMax; i++ ){
		m_ppSpia[i]->SetPosition( 
			D3DXVECTOR3( 
				GetPositionX() - STAGE_WIDHT/2.0f + (float)i * fFLOOR_W_OFFSET,
				GetPositionY(), 
				GetPositionZ() ) );
	}

	//���Ǎ��W.
	m_pSpiaWall->SetPosition( GetPosition() );
	m_pSpiaWall->AddPositionY( WALL_OFFSET_Y );
	m_pSpiaWall->AddPositionX( -STAGE_WIDHT / 2.0f );
}

//���̂����蔻����Ԃ�.
COL_STATE* clsSpiaFlorMgr::GetPointerSpiaCol( int i )
{
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


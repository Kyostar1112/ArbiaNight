#include "Resource.h"
#include "GoalManager.h"

const float fMODEL_SCALE = 1.0f;
const double fANIM_SPD = 0.01;


//�󔠂��J���鉹.
#define ALIAS_NAME_OPEN "GoalBreak"
#define  FILE_PATH_OPEN "SE\\300Trap\\400TrBox.wav"
const int	  iVOL_OPEN = 1000;

////�`�F�[������.
//#define ALIAS_NAME_KEY "GoalKeyBreak"
//#define  FILE_PATH_KEY "SE\\300Trap\\900GateBreak.wav"					
//const int	  iVOL_KEY = 1000;


//----- �R��ꔻ��p -----//.
const float fCOL_RANGE = 1.5f;
const float fCOL_HEIGHT = 1.0f;


//�󔠂��ǂꂾ�����ɂ��邩.
const float fTREASURE_Z = 22.0f;


//�G�t�F�N�g.
const D3DXVECTOR3 vEFF_SCALE = { 0.5f, 0.5f, 0.5f };



clsGoalMgr::clsGoalMgr()
{
	m_pEffect = nullptr;

}

clsGoalMgr::~clsGoalMgr()
{
	Release();
}

void clsGoalMgr::Create( HWND hWnd, ID3D11Device* pDevice, ID3D11DeviceContext* pContext )
{
	//��.
	m_pFloor = new clsCharaStatic;
	m_pFloor->AttachModel(
		clsResource::GetInstance()->GetStaticModels(
			clsResource::enST_MODEL_GOOL ) );

	//�󔠂�����.
	m_pTrBoxCol = new clsCharaStatic;
	m_pTrBoxCol->AttachModel(
		clsResource::GetInstance()->GetStaticModels(
			clsResource::enST_MODEL_TR_BOX_COL ) );

	//��.
	m_pTreasurer = new clsCharaSkin;

	CD3DXSKINMESH_INIT si;//skin_Init.
	si.hWnd = hWnd;
	si.pDevice = pDevice;
	si.pDeviceContext = pContext;

	m_pTreasurer->m_pModel = new clsD3DXSKINMESH;
	m_pTreasurer->m_pModel->Init( &si );

	m_pTreasurer->AttachModel(
		clsResource::GetInstance()->GetSkinModels(
			clsResource::enSK_MODEL_TR_BOX ) );

	m_pTreasurer->SetScale( fMODEL_SCALE );
	m_pTreasurer->SetAnimSpeed( fANIM_SPD );


	//�R��ꔻ��p.
	ColState.fRange = fCOL_RANGE;
	ColState.fHeight = fCOL_HEIGHT;

	//----- SE -----//
	//�T�E���h�\����.
	clsSound::SOUND_DATA tmpSData[] =
	{
		{ ALIAS_NAME_OPEN,	FILE_PATH_OPEN,	iVOL_OPEN	},
	};
	m_iSeMax = sizeof( tmpSData ) / sizeof( tmpSData[0] );

	//�T�E���h�N���X�쐬.
	m_ppSe = new clsSound*[m_iSeMax];
	for( int i=0; i<m_iSeMax; i++ ){
		m_ppSe[i] = new clsSound;
		//�����ʏ�����.
		m_ppSe[i]->SetVolume( 0 );
		//���O.
		char cAliasName[STR_BUFF_MAX] = "";
		strcat_s( cAliasName, sizeof( cAliasName ), tmpSData[i].sAlias );
		//�쐬.
		m_ppSe[i]->Open( tmpSData[i].sPath, cAliasName, hWnd );
		//�ő剹�ʐݒ�.
		m_ppSe[i]->SetMaxVolume( tmpSData[i].iMaxVolume );
	}
	//----- SE �I�� -----//

	//�G�t�F�N�g.
	if( m_pEffect == nullptr ){
		m_pEffect = clsEffects::GetInstance();
	}

	Init();
}
void clsGoalMgr::Init()
{
	m_bOpen = false;
	SetColPos( m_vPos );
	m_dAnimTimer = 0.0;
	ChangeAnimMode( enANIM_IDLE );

	//�G�t�F�N�g�~�߂�.
	m_pEffect->Stop( m_ehOpen );
	m_pEffect->Stop( m_ehLoop );
}


void clsGoalMgr::Release()
{
	m_pEffect = nullptr;


	if( m_ppSe != NULL ){
		for( int i=0; i<m_iSeMax; i++ ){
			m_ppSe[i]->Close();
			delete m_ppSe[i];
			m_ppSe[i] = NULL;
		}
		delete[] m_ppSe;
		m_ppSe = NULL;
	}

	if( m_pTreasurer != NULL ){
		delete m_pTreasurer;
		m_pTreasurer = NULL;
	}

	if( m_pTrBoxCol!= NULL ){
		delete m_pTrBoxCol;
		m_pTrBoxCol = NULL;
	}


	if( m_pFloor!= NULL ){
		delete m_pFloor;
		m_pFloor = NULL;
	}
}

//�`��.
void clsGoalMgr::Render( D3DXMATRIX &mView, D3DXMATRIX &mProj,
	D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye )
{
	//��.
	m_pFloor->Render( mView, mProj, vLight, vEye );
	//��.
	m_pTreasurer->Render( mView, mProj, vLight, vEye );

//	m_pTrBoxCol->Render( mView, mProj, vLight, vEye );
}


void clsGoalMgr::SetPosition( D3DXVECTOR3 vPos )
{
	m_vPos = vPos;

	//�q��.
	m_pFloor->SetPosition( m_vPos );
	m_pTreasurer->SetPosition( m_vPos );
	m_pTreasurer->AddPositionZ( fTREASURE_Z );

	m_pTrBoxCol->SetPosition( m_pTreasurer->GetPosition() );

	SetColPos( m_vPos );

	Init();
}


void clsGoalMgr::Move( float fEarZ )
{
//	m_fEarZ = fEarZ;
	Animation();

	//�G�t�F�N�g.
	if( m_bOpen ){
		//�J���G�t�F�N�g���I����Ă�.
		if( !m_pEffect->PlayCheck( m_ehOpen ) ){
			m_ehLoop = m_pEffect->Play( clsEffects::enEfcType_TRB_LOOP, m_pTreasurer->GetPosition() );
			m_pEffect->SetScale( m_ehLoop, vEFF_SCALE );
		}
	}
}





//============================================================
//	�R��ꂽ�Ƃ�.
//============================================================
void clsGoalMgr::BoxBreak()
{
	m_bOpen = true;

	PlaySe( enSOUND_OPEN );

	ChangeAnimMode( enANIM_OPEN );

	//�Đ�.
	if( !m_pEffect->PlayCheck( m_ehOpen ) ){
		m_ehOpen = m_pEffect->Play( clsEffects::enEfcType_TRB_OPEN, m_pTreasurer->GetPosition() );
		m_pEffect->SetScale( m_ehOpen, vEFF_SCALE );
	}
	if( !m_pEffect->PlayCheck( m_ehLoop ) ){
		m_ehLoop = m_pEffect->Play( clsEffects::enEfcType_TRB_LOOP, m_pTreasurer->GetPosition() );
		m_pEffect->SetScale( m_ehLoop, vEFF_SCALE );
	}

}


//============================================================
//	���ʉ��Đ�.
//============================================================
void clsGoalMgr::PlaySe( enSound enSe )
{
#if 0
	//�Đ����鋗���Ȃ�.
	int vol = ChangeVolumeDistance( m_fEarZ, m_vPos.z );
vol = 1;
	if( vol ){
		m_ppSe[enSe]->GetMaxVolRate( vol );
		m_ppSe[enSe]->SeekToStart();
		m_ppSe[enSe]->SetVolume( vol );
m_ppSe[enSe]->SetVolume( iVOL );
		m_ppSe[enSe]->Play();
	}
	//�Đ����Ȃ������Ȃ�.
	else{
		m_ppSe[enSe]->SetVolume( 0 );
	}
#else
	m_ppSe[enSe]->SeekToStart();
	m_ppSe[enSe]->SetVolume( iVOL_OPEN );
	m_ppSe[enSe]->Play();
#endif
}


//==================================================
//	�����蔻��p.
//==================================================
void clsGoalMgr::SetColPos( D3DXVECTOR3 vPos )
{
	ColState.vPos = vPos;
	ColState.vPos.z += fTREASURE_Z;
}

//============================================================
//	���̃A�j��.
//============================================================
void clsGoalMgr::Animation()
{
	//���[�v���Ȃ��A�j��.
	if( m_enAnimNo == enANIM_OPEN ){
		m_dAnimTimer += m_pTreasurer->m_pModel->GetAnimSpeed();
		
		const double dRATE = 5.0;//���{��΂�?.

		//���݂̃A�j���[�V�������I������.
		if( m_pTreasurer->m_pModel->GetAnimPeriod( m_enAnimNo ) - ( dANIM_ONE_FRAME_OVER_SOLUTION * dRATE ) <= m_dAnimTimer ){
			//�����Ȃ��Ȃ�.
			ChangeAnimMode( enANIM_DEAD );
		}
	}
}

//============================================================
//	�A�j���[�V�������[�h��ύX.
//============================================================
void clsGoalMgr::ChangeAnimMode( enAnimation anim )
{
	m_enAnimNo = anim;
	m_pTreasurer->ChangeAnimSet( m_enAnimNo );//�A�j���Z�b�g.
	m_dAnimTimer = 0.0;
}

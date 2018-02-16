#include "Resource.h"
#include "DoorManager.h"


const float fMODEL_SCALE = 1.0f;
const double fANIM_SPD = 0.01;


//----- �� -----//.
const char sALIAS_NAME[] = "DoorBreak";
const char sFILE_PATH[] = "SE\\300Trap\\900GateBreak.wav";
const int iVOL = 1000;


//----- �R��ꔻ��p -----//.
const float fCOL_RANGE = 1.5f;
const float fCOL_HEIGHT = 3.0f;

//----- �ǂ̒��� -----//.
const float fSTAGE_WIDTH = 10.0f;
const float fSTAGE_WIDTH_HARF = fSTAGE_WIDTH / 2.0f;
const float fWALL_HEIGHT = 6.0f;
const float fWALL_Z = -0.75f;

const D3DXVECTOR3 vWALL_OFFSET = { -fSTAGE_WIDTH_HARF, fWALL_HEIGHT, fWALL_Z };

//�������ǂꂾ����O�ɂ��邩Z.
const float fRE_SPAWN_POS_Z = 1.5f;

//----- ���� ------//
//���ߋ��E��Z.
const float fALPHA_BORDER_Z = 0.5f;

//���ߑ��x.
const float fALPHA_SPD = 1.0f / 16.0f;
//���߂�߂����x.
const float fALPHA_SPD_BACK = 1.0f / 32.0f;

//��Ԕ������Ă�.
const float fALPHA_LIMIT = 0.375f;
//��ԔZ�����Ă�.
const float fALPHA_LIMIT_MAX = 2.0f;



//�G�t�F�N�g.
const float fEFFECT_Z_OFFSET = 12.0f;//���̒��n�ʒu.
const float fEFFECT_SCALE = 0.5f;
const D3DXVECTOR3 vEFFECT_SCALE = { fEFFECT_SCALE, fEFFECT_SCALE, fEFFECT_SCALE };
const float fEFFECT_SPD = 1.0f;
const int iEFFECT_PLAY_RAG = 20;//�R���Ă��甭������܂ł̃��O.


clsDoorMgr::clsDoorMgr()
{
	m_pEffect = nullptr;
}

clsDoorMgr::~clsDoorMgr()
{
	Release();
}



void clsDoorMgr::Create( HWND hWnd, ID3D11Device* pDevice, ID3D11DeviceContext* pContext, int iNo )
{
	//��.
	m_pGate = new clsCharaStatic;
	m_pGate->AttachModel(
		clsResource::GetInstance()->GetStaticModels(
			clsResource::enST_MODEL_MON ) );

	//��.
	m_pDoor = new clsCharaSkin;

	CD3DXSKINMESH_INIT si;//skin_Init.
	si.hWnd = hWnd;
	si.pDevice = pDevice;
	si.pDeviceContext = pContext;

	m_pDoor->m_pModel = new clsD3DXSKINMESH;
	m_pDoor->m_pModel->Init( &si );

	m_pDoor->AttachModel(
		clsResource::GetInstance()->GetSkinModels(
			clsResource::enSK_MODEL_DOOR ) );

	m_pDoor->SetScale( fMODEL_SCALE );
	m_pDoor->SetAnimSpeed( fANIM_SPD );

	//�ǔ���.
	m_pColWall = new clsCharaStatic;
	m_pColWall->AttachModel(
		clsResource::GetInstance()->GetStaticModels(
			clsResource::enST_MODEL_SPIA_WALL ) );



	//�R��ꔻ��p.
	ColState.fRange = fCOL_RANGE;
	ColState.fHeight = fCOL_HEIGHT;

	//���ʉ�.
	m_pSe = new clsSound;
	m_pSe->SetVolume( 0 );
	//���O.
	char cAliasName[STR_BUFF_MAX] = "";
	strcat_s( cAliasName, sizeof( cAliasName ), sALIAS_NAME );
	//�ԍ�.
	char cNumber[] = "  ";
	_itoa_s( iNo, cNumber, 10 );
	//���O�Ɣԍ�����.
	strcat_s( cAliasName, sizeof( cAliasName ), cNumber );
	//�쐬.
	m_pSe->Open( sFILE_PATH, cAliasName, hWnd );
	//�ő剹�ʐݒ�.
	m_pSe->SetMaxVolume( iVOL );


	m_pEffect = clsEffects::GetInstance();
	PlayEff();
	m_pEffect->Stop( m_ehDust );

	Init();
}
void clsDoorMgr::Init()
{
	ReStart();
	m_bBreak = false;
	SetColPos( m_vPos );
	m_dAnimTimer = 0.0;
	ChangeAnimMode( enANIM_IDLE );

}
//�������̏�����.
void clsDoorMgr::ReStart()
{
	m_fAlpha = fALPHA_LIMIT_MAX;
	m_bAlpha = false;
	m_bAlphaChange = false;

	m_iEffTimer = 0;
	m_bEffTimer = false;
}


void clsDoorMgr::Release()
{
	m_pEffect = nullptr;

	if( m_pSe != NULL ){
		delete m_pSe;
		m_pSe = NULL;
	}

	if( m_pColWall!= NULL ){
		delete m_pColWall;
		m_pColWall = NULL;
	}

	if( m_pDoor != NULL ){
		delete m_pDoor;
		m_pDoor = NULL;
	}

	if( m_pGate != NULL ){
		delete m_pGate;
		m_pGate = NULL;
	}
}

//�`��.
void clsDoorMgr::Render( D3DXMATRIX &mView, D3DXMATRIX &mProj,
	D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye )
{
	//.
//	m_pColWall->Render( mView, mProj, vLight, vEye );
	//��.
	m_pDoor->Render( mView, mProj, vLight, vEye );
	//��.
	m_pGate->Render( mView, mProj, vLight, vEye,
		D3DXVECTOR4( 1.0f, 1.0f, 1.0f, m_fAlpha ), m_bAlpha );

}


void clsDoorMgr::SetPosition( D3DXVECTOR3 vPos )
{
	m_vPos = vPos;

	//�q��.
	m_pGate->SetPosition( m_vPos );
	m_pDoor->SetPosition( m_vPos );

	m_pColWall->SetPosition( m_vPos );
	m_pColWall->AddPosition( vWALL_OFFSET );

	Init();
}


void clsDoorMgr::Move( float fEarZ )
{
	m_fEarZ = fEarZ;
	Animation();
	SetAlpha();


	//�G�t�F�N�g�Đ�.
	if( m_bEffTimer ){
		m_iEffTimer ++;
		if( m_iEffTimer >= iEFFECT_PLAY_RAG ){
			m_iEffTimer = 0;
			m_bEffTimer = false;
			PlayEff();
		}
	}


}



//============================================================
//	���ߒl�̐ݒ�.
//============================================================
void clsDoorMgr::SetAlphaFlg( float fPlayerZ )
{
	//���ߒ�.
	if( m_bAlphaChange ){
		//���߃t���OON.
		m_bAlpha = true;
		//�v���C���[�����ɂ���Ȃ�.
		if( fPlayerZ > m_vPos.z + fALPHA_BORDER_Z ){
			return;
		}
		//���̉��J�n.
		m_bAlphaChange = false;
	}
	//���ߒ��ł͂Ȃ�.
	else{
		//�v���C���[����O�ɂ���Ȃ�.
		if( fPlayerZ < m_vPos.z + fALPHA_BORDER_Z ){
			return;
		}
		//���ߊJ�n.
		m_bAlphaChange = true;
	}
}

//============================================================
//	���ߒl�̐ݒ�.
//============================================================
void clsDoorMgr::SetAlpha()
{
	//���ߒ�.
	if( m_bAlphaChange ){
		m_fAlpha -= fALPHA_SPD;
		if( m_fAlpha < fALPHA_LIMIT ){
			m_fAlpha = fALPHA_LIMIT;
		}
	}
	//���̉���.
	else{
		m_fAlpha += fALPHA_SPD_BACK;
		if( m_fAlpha > fALPHA_LIMIT_MAX ){
			m_fAlpha = fALPHA_LIMIT_MAX;
			m_bAlpha = false;
		}
	}
}


//============================================================
//	�R��ꂽ�Ƃ�.
//============================================================
D3DXVECTOR3 clsDoorMgr::DoorBreak()
{
	m_bBreak = true;

	PlaySe();

	D3DXVECTOR3 vReSpawnPos = m_vPos;
	vReSpawnPos.z -= fRE_SPAWN_POS_Z;

	ChangeAnimMode( enANIM_BREAK );


	m_bEffTimer = true;

	return vReSpawnPos;
}

//==================================================
//	�����蔻��p.
//==================================================
void clsDoorMgr::SetColPos( D3DXVECTOR3 vPos )
{
	ColState.vPos = vPos;
}


//==================================================
//	���ʉ��Đ�.
//==================================================
void clsDoorMgr::PlaySe(/* enSound enSe*/ )
{
	m_pSe->SeekToStart();
	m_pSe->SetVolume( iVOL );
	m_pSe->Play();
}

//============================================================
//	�h�A�̃A�j��.
//============================================================
void clsDoorMgr::Animation()
{
	//���[�v���Ȃ��A�j��.
	if( m_enAnimNo == enANIM_BREAK ){
		m_dAnimTimer += m_pDoor->m_pModel->GetAnimSpeed();
		
		const double dRATE = 5.0;//���{��΂�?.

		//���݂̃A�j���[�V�������I������.
		if( m_pDoor->m_pModel->GetAnimPeriod( m_enAnimNo ) - ( dANIM_ONE_FRAME_OVER_SOLUTION * dRATE ) <= m_dAnimTimer ){
			//�����Ȃ��Ȃ�.
			ChangeAnimMode( enANIM_DEAD );
		}
	}
}

//============================================================
//	�A�j���[�V�������[�h��ύX.
//============================================================
void clsDoorMgr::ChangeAnimMode( enAnimation anim ){
	m_enAnimNo = anim;
	m_pDoor->ChangeAnimSet( m_enAnimNo );//�A�j���Z�b�g.
	m_dAnimTimer = 0.0;
}


//�G�t�F�N�g�Đ�.
void clsDoorMgr::PlayEff()
{
	if( !m_pEffect->PlayCheck( m_ehDust ) ){
			D3DXVECTOR3 vEffPos = m_vPos;
			vEffPos.z += fEFFECT_Z_OFFSET;

		m_ehDust = m_pEffect->Play( clsEffects::enEfcType_DOOR_DUST, vEffPos );
		m_pEffect->SetSpd( m_ehDust, fEFFECT_SPD );
		m_pEffect->SetScale( m_ehDust, vEFFECT_SCALE );
	}
}

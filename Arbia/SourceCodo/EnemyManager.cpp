#include "Resource.h"
#include "EnemyManager.h"

const float fMODEL_SCALE = 1.0f / 20.0f;//�������p.

const float fWALK_RANGE_MAX = 6.0f / 2.0f;//��������(���S����̋���).
const float fWALK_RANGE_MIN = 0.5f / 2.0f;//��������(���S����̋���).

const float fTWINS_OFFSET = 4.0f / 2.0f;//���ԓ�l�̒�������̋���(��{����Ɠ�l�̋���).


const int iDOR_DEAD_TIME = 24;//�h�A���S����.

clsEnemyMgr::clsEnemyMgr()
{
	m_ppEnemy = nullptr;
}

clsEnemyMgr::~clsEnemyMgr()
{
	Release();
}






//==================================================
//	.
//==================================================
void clsEnemyMgr::Release()
{
	if( m_ppEnemy != nullptr ){
		for( int i=0; i<m_iEnemyMax; i++ ){
			m_ppEnemy[i]->DetatchModel();
			delete m_ppEnemy[i];
			m_ppEnemy[i] = nullptr;
		}
		delete[] m_ppEnemy;
		m_ppEnemy = nullptr;
		m_iEnemyMax = 0;
	}
}



//==================================================
//	���ٓǍ�.
//==================================================
void clsEnemyMgr::CreateEnemy( HWND hWnd, ID3D11Device* pDevice, ID3D11DeviceContext* pContext,
		 int mode, int iMgrID )
{
	if( m_ppEnemy != nullptr ) return;

	m_enMode = enEMM_1X;
	if( mode < enEMM_MAX ){
		m_enMode = (enENEMY_MGR_MODE)mode;
	}

	//�G�̐��m��.
	if( enEMM_1X <= m_enMode && m_enMode <= enEMM_1SQ_R ){
		m_iEnemyMax = 1;
	}
	else if( enEMM_2X <= m_enMode && m_enMode <= enEMM_2SQ_R ){
		m_iEnemyMax = 2;
	}
	else if( m_enMode == enEMM_DOOR ){
		m_iEnemyMax = 1;
	}
	else{
		m_iEnemyMax = 0;
	}


	m_ppEnemy = new clsEnemy*[m_iEnemyMax];
	for( int j=0; j<m_iEnemyMax; j++ ){
		m_ppEnemy[j] = new clsEnemy;
		m_ppEnemy[j]->Create( hWnd, pDevice, pContext, iMgrID, j );
		m_ppEnemy[j]->Init( GetPositionZ() );

		CD3DXSKINMESH_INIT si;//skin_Init.
		si.hWnd = hWnd;
		si.pDevice = pDevice;
		si.pDeviceContext = pContext;

		m_ppEnemy[j]->m_pModel = new clsD3DXSKINMESH;
		m_ppEnemy[j]->m_pModel->Init( &si );

		m_ppEnemy[j]->AttachModel(
			clsResource::GetInstance()->GetSkinModels(
				clsResource::enSK_MODEL_ENEMY ) );

		m_ppEnemy[j]->SetScale( fMODEL_SCALE );
//		m_ppEnemy[j]->SetAnimSpeed( 0.01 );
	}

	Init( true );
}


//==================================================
//	.
//==================================================
void clsEnemyMgr::Init( bool bFirst )
{
	if( m_ppEnemy == nullptr ) return;

	//�X�e�[�W�̊J�n�łȂ��Ȃ� �h�A�Ŏ��񂾓z�� ���������Ȃ�.
	if( !bFirst && m_bDoor ){
		return;
	}

	for( int i=0; i<m_iEnemyMax; i++ ){
		m_ppEnemy[i]->Init( GetPositionZ() );
	}

	//�G�̈ʒu��������.
	SetPosition( GetPosition() );

	m_bDoor = false;
	m_iDoorTimer = 0;
}


//==================================================
//	.
//==================================================
void clsEnemyMgr::SetPosition( D3DXVECTOR3 vPos )
{
	if( m_ppEnemy == nullptr ) return;

	m_vPos = vPos;

	//�G�̍��W.
	for( int i=0; i<m_iEnemyMax; i++ ){
		m_ppEnemy[i]->SetPosition( GetPosition() );
		//�ړ��̊p���.
		SetTurnPos( m_enMode, i );
	}
}


//==================================================
//	�ړ��̊p���.
//==================================================
void clsEnemyMgr::SetTurnPos( enENEMY_MGR_MODE mode, int i )
{
	if( m_ppEnemy == nullptr ) return;

	float x, z;
	x = z = 1.0f;
	float fSecondX, fSecondZ;
	fSecondX = fSecondZ = 0.0f;

	bool bReverse = false;

	//X.                   
	if( mode == enEMM_1X	||
		mode == enEMM_1SQ_L ||
		mode == enEMM_2X_RE	||
		mode == enEMM_2SQ_L  )
	{
		x = fWALK_RANGE_MAX;
	}
	else if( 
		mode == enEMM_1SQ_R ||
		mode == enEMM_2SQ_R )
	{
		//�t��](R).
		x = -fWALK_RANGE_MAX;
		bReverse = true;
	}
	else if( mode == enEMM_2X ){
		if( i == 0 )x = fWALK_RANGE_MAX;
		else		x = -fWALK_RANGE_MAX;
	}
	else if( mode == enEMM_1Z ){
		x = fWALK_RANGE_MIN;
	}
	else if( 
		mode == enEMM_2Z ||
		mode == enEMM_2Z_RE )
	{
		x = fWALK_RANGE_MIN;
		if( i == 0 )fSecondX = +fTWINS_OFFSET;
		else		fSecondX = -fTWINS_OFFSET;
	}


	//Z.                   
	if( mode == enEMM_1Z	||
		mode == enEMM_1SQ_L	||
		mode == enEMM_2Z_RE	||
		mode == enEMM_2SQ_L )
	{
		z = fWALK_RANGE_MAX;
	}
	else if( 
		mode == enEMM_1SQ_R ||
		mode == enEMM_2SQ_R )
	{
		//�t��](R).
		z = -fWALK_RANGE_MAX;
		bReverse = true;
	}
	else if( mode == enEMM_2Z ){
		if( i == 0 )z = fWALK_RANGE_MAX;
		else		z = -fWALK_RANGE_MAX;
	}
	else if( mode == enEMM_1X ){
		z = fWALK_RANGE_MIN;
	}
	else if( 
		mode == enEMM_2X	||
		mode == enEMM_2X_RE )
	{
		z = fWALK_RANGE_MIN;
		if( i == 0 )fSecondZ = +fTWINS_OFFSET;
		else		fSecondZ = -fTWINS_OFFSET;
	}


	//��l�ڂ͑Ίp��ڎw��.
	bool bSecond = false;
	if( i != 0 ){
		bSecond = true;
	}


//	//�h�A�Ŏ���.
//	if( mode == enEMM_DOOR ){
//	
//	}

	//���.
	m_ppEnemy[i]->SetTurnPos( x, z,fSecondX, fSecondZ, bReverse, bSecond );

}








//==================================================
//	.
//==================================================
COL_STATE* clsEnemyMgr::GetPointerEnemyCol( int i )
{
	if( m_ppEnemy == nullptr ) return nullptr;
	return m_ppEnemy[i]->GetPointerCol();
}

//==================================================
//	.
//==================================================
COL_STATE* clsEnemyMgr::GetPointerEnemySubCol( int i )
{
	if( m_ppEnemy == nullptr ) return nullptr;
	return &m_ppEnemy[i]->m_colSub;
}



//==================================================
//	.
//==================================================
void clsEnemyMgr::Render( D3DXMATRIX &mView, D3DXMATRIX &mProj,
				D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye )
{
	if( m_ppEnemy == nullptr ) return;
	for( int i=0; i<m_iEnemyMax; i++ ){
		m_ppEnemy[i]->Render( mView, mProj, vLight, vEye );
	}
}


//==================================================
//	.
//==================================================
void clsEnemyMgr::Update( float fEarZ )
{
	if( m_ppEnemy == nullptr ) return;

	for( int i=0; i<m_iEnemyMax; i++ ){
		m_ppEnemy[i]->Update( fEarZ );
	}

	//�h�A�Ŏ��ʐl.
	if( m_bDoor ){
		//����.
		if( m_iDoorTimer <= iDOR_DEAD_TIME ){
			//��񂾂�.
			if( m_iDoorTimer == iDOR_DEAD_TIME ){
				//�O�̂��ߑS����.
				for( int i=0; i<m_iEnemyMax; i++ ){
					m_ppEnemy[i]->Dead();
				}
			}
			m_iDoorTimer ++;
		}
	}
	//����ȏ����������Ă���̂̓I�[�o�[���C�h�h�~�ƃt���O���₷�̂�������������.
}










//==================================================
//	���N��.
//==================================================
int clsEnemyMgr::GetWalkRangeMax()
{
	return (int)( fWALK_RANGE_MAX * 2.0f );//�萔�͒��S����̋����Ȃ̂őS�����o�����߂ɓ�{����.
}

#include "Resource.h"
#include "EndEnemyMgr.h"

const int iANIM_NO = 2;

const double fANIM_SPD = 0.025;


const float MODEL_SCALE = 1.0f / 20.0f;//‰Šú‰»—p.

//ƒuƒŒ( —”‚Ì• ).
const int iRAND_X_MIN =-8;
const int iRAND_X_MAX = 6;
const int iRAND_Z_MIN = 2;
const int iRAND_Z_MAX = 4;
const float fRAND_X_RATE = 2.0f;


clsEndEnemMgr::clsEndEnemMgr()
{
	m_pEnemy = nullptr;
	m_iEnemMax = 0;
}

clsEndEnemMgr::~clsEndEnemMgr()
{
	Release();
}

void clsEndEnemMgr::Create(
	HWND hWnd, 
	ID3D11Device* pDevice11, 
	ID3D11DeviceContext* pContext11 )
{
	m_pEnemy = new clsEndEnemy;
	m_pEnemy->Create( hWnd, pDevice11, pContext11 );

	CD3DXSKINMESH_INIT si;//skin_Init.
	si.hWnd = hWnd;
	si.pDevice = pDevice11;
	si.pDeviceContext = pContext11;

	m_pEnemy->m_pModel = new clsD3DXSKINMESH;
	m_pEnemy->m_pModel->Init( &si );

	m_pEnemy->AttachModel(
		clsResource::GetInstance()->GetSkinModels(
			clsResource::enSK_MODEL_ENEMY ) );

	m_pEnemy->SetScale( MODEL_SCALE );

	m_pEnemy->SetAnimSpeed( fANIM_SPD );


	m_pEnemy->ChangeAnimSet( iANIM_NO );

}

void clsEndEnemMgr::Init( D3DXVECTOR3 vPlayerPos, int DiscNum )
{
	if( DiscNum > iEND_ENEMY_MAX ){
		DiscNum = iEND_ENEMY_MAX;
	}
	m_iEnemMax = DiscNum;
	m_pEnemy->Init();

	for( int i=0; i<iEND_ENEMY_MAX; i++ ){
		vEndPos[i] = { 0.0f, 0.0f, 0.0f };
		vEndPos[i] = vPlayerPos;

		//ƒuƒŒ.
		std::mt19937 Mt( Rnd() );
		std::uniform_int_distribution<> RandX( iRAND_X_MIN, iRAND_X_MAX );
		std::uniform_int_distribution<> RandZ( iRAND_Z_MIN, iRAND_Z_MAX );
		vEndPos[i].x += static_cast<float>( RandX( Mt ) ) / fRAND_X_RATE;
		vEndPos[i].z += static_cast<float>( RandZ( Mt ) ) * static_cast<float>( i + 1 );
	}

}

void clsEndEnemMgr::Update()
{
	m_pEnemy->Update();
}

void clsEndEnemMgr::Render( 
	D3DXMATRIX& mView, D3DXMATRIX& mProj,
	D3DXVECTOR3& vLight, D3DXVECTOR3& vEye )
{
	//for•¶‚Å‰Á‘¬‚·‚é‚Ì‚ð—}‚¦‚é.
	m_pEnemy->SetAnimSpeed( static_cast<double>( fANIM_SPD ) / static_cast<double>( m_iEnemMax ) );
	for( int i=0; i<m_iEnemMax; i++ ){
		m_pEnemy->SetPosition( vEndPos[i] );
		m_pEnemy->Update();
		m_pEnemy->Render( mView, mProj, vLight, vEye );
	}
}




void clsEndEnemMgr::Release()
{
	if( m_pEnemy != nullptr ){
		delete m_pEnemy;
		m_pEnemy = nullptr;
	}
}


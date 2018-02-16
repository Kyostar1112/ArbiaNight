#include "Resource.h"
#include "EndEnemy.h"


const float fFLOOR_Y = 0.01f;


clsEndEnemy::clsEndEnemy()
{
	m_pModel = nullptr;
	m_pShadow = nullptr;
	m_fFloorY = fFLOOR_Y;
}

clsEndEnemy::~clsEndEnemy()
{
	Release();
}


void clsEndEnemy::Create( HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11 )
{
	m_pShadow = new clsShadow;
	m_pShadow->Init( pDevice11, pContext11 );


	Init();
}

void clsEndEnemy::Init()
{
	
}


void clsEndEnemy::Update()
{

//	UpDateModel();
	m_pShadow->SetShadow( m_vPos, m_fFloorY );
}




void clsEndEnemy::Release()
{
	if( m_pShadow != nullptr ){
		delete m_pShadow;
		m_pShadow = nullptr;
	}

	if( m_pModel != nullptr ){
		DetatchModel();
		delete m_pModel;
		m_pModel = nullptr;
	}
}


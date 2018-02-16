#include "Resource.h"

clsResource::clsResource()
{
	m_hWnd = NULL;
	m_pDevice11 = NULL;
	m_pCotext11 = NULL;
	m_ppStaticModels = NULL;
	ZeroMemory( m_FilePath,sizeof( m_FilePath ) );
}

clsResource::~clsResource()
{
	for( int i=0; i<enST_MODEL_MAX; i++ ){
		ReleaseStaticModel( (enStaticModel)i );
	}
	for( int i=0; i<enSK_MODEL_MAX; i++ ){
		ReleaseSkinModel( (enSkinModel)i );
	}
	//���ү�����߲���̈�����.
	if( m_ppSkinModels ){
		delete[] m_ppSkinModels;
		m_ppSkinModels = NULL;
	}
	//��è��ү�����߲���̈�����.
	if( m_ppStaticModels ){
		delete[] m_ppStaticModels;
		m_ppStaticModels = NULL;
	}


	m_pCotext11 = NULL;
	m_pDevice11 = NULL;
	m_hWnd = NULL;
}


//==================================================.
//	������.
//==================================================.
HRESULT clsResource::InitStaticModel( HWND hWnd,
			ID3D11Device* pDevice,
			ID3D11DeviceContext* pContext)
{
	m_hWnd = hWnd;
	m_pDevice11 = pDevice;
	m_pCotext11 = pContext;
	//��è��ү�����߲���̈���m��.
	m_ppStaticModels = new clsDX9Mesh*[ enST_MODEL_MAX ];
	for( int i=0; i<enST_MODEL_MAX; i++ ){
		m_ppStaticModels[i] = NULL;
	}

	return S_OK;
}
HRESULT clsResource::InitSkinModel( HWND hWnd,
			ID3D11Device* pDevice,
			ID3D11DeviceContext* pContext)
{
	m_Si.hWnd = hWnd;
	m_Si.pDevice = pDevice;
	m_Si.pDeviceContext = pContext;
	//���ү�����߲���̈���m��.
	m_ppSkinModels = new clsD3DXSKINMESH*[ enSK_MODEL_MAX ];
	for( int i=0; i<enSK_MODEL_MAX; i++ ){
		m_ppSkinModels[i] = NULL;
	}

	return S_OK;
}



//==================================================.
//	���ٓǍ�.
//==================================================.
// Static Model.
HRESULT clsResource::CreateStaticModel(
	LPSTR fileName, enStaticModel enModel )
{
	//�񋓑͈͓̂̔�?.
	if( !IsRangeStaticModel( enModel ) ){
		return E_FAIL;
	}
	//�����ް������邩.
	if( m_ppStaticModels[ enModel ] != NULL ){
		return E_FAIL;
	}

	//���ٓǍ�.
	m_ppStaticModels[ enModel ] = new clsDX9Mesh;
	m_ppStaticModels[ enModel ]->Init(
		m_hWnd, m_pDevice11, m_pCotext11, fileName );

	return S_OK;
}
//	Skin Model.
HRESULT clsResource::CreateSkinModel( 
	LPSTR fileName, enSkinModel enModel )
{
	//�񋓑͈͓̂̔���.
	if ( !IsRangeSkinModel( enModel ) ){
		return E_FAIL;
	}

	//�����ް������邩.
	if ( m_ppSkinModels[ enModel ] != NULL ){
		return E_FAIL;
	}

	//���ٓǍ�.
	m_ppSkinModels[ enModel ] = new clsD3DXSKINMESH;
	m_ppSkinModels[ enModel ]->Init( &m_Si );
	m_ppSkinModels[ enModel ]->CreateFromX( fileName );

	return S_OK;
}

//==================================================.
//	���.
//==================================================.
//	Static Model.
HRESULT clsResource::ReleaseStaticModel( enStaticModel enModel )
{
	//�񋓑͈͓̂̔�?.
	if( !IsRangeStaticModel( enModel ) ){
		return E_FAIL;
	}
	//�����ް������邩.
	if( m_ppStaticModels[ enModel ] == NULL ){
		return E_FAIL;
	}

	delete m_ppStaticModels[ enModel ];
	m_ppStaticModels[ enModel ] = NULL;

	return S_OK;
}
//	Skin Model.
HRESULT clsResource::ReleaseSkinModel( enSkinModel enModel )
{
	//�񋓑͈͓̂̔�?.
	if( !IsRangeSkinModel( enModel ) ){
		return E_FAIL;
	}
	//�����ް������邩.
	if( m_ppSkinModels[ enModel ] == NULL ){
		return E_FAIL;
	}

	delete m_ppSkinModels[ enModel ];
	m_ppSkinModels[ enModel ] = NULL;

	return S_OK;
}

//==================================================.
//	���ق��߲���擾.
//==================================================.
//	Static Model.
clsDX9Mesh* clsResource::GetStaticModels(
	enStaticModel enModel )
{
	//�񋓑͈͓̂̔�?.
	if( !IsRangeStaticModel( enModel ) ){
		return NULL;
	}
	//�����ް������邩.
	if( m_ppStaticModels[ enModel ] == NULL ){
		return NULL;
	}
	
	//���ق��߲���Ԃ�.
	return m_ppStaticModels[ enModel ];
	//return (clsDX9Mesh*)S_OK;	//�厖��.
}
//	Skin Model.
clsD3DXSKINMESH* clsResource::GetSkinModels(enSkinModel enModel)
{
	//�񋓑͈͓̂̔�?.
	if ( !IsRangeSkinModel( enModel ) ){
		return NULL;
	}

	//�����ް������邩.
	if ( m_ppSkinModels[ enModel ] == NULL ){
		return NULL;
	}

	//���ق��߲���Ԃ�.
	return m_ppSkinModels[ enModel ];
}


//==================================================.
//	�͈͓�����������֐�.
//==================================================.
bool clsResource::IsRangeStaticModel( enStaticModel enModel )
{
	if( 0 <= enModel && enModel < enST_MODEL_MAX ){
		return true;//�͈͓�.
	}
	return false;	//�͈͊O.
}
bool clsResource::IsRangeSkinModel( enSkinModel enModel )
{
	if ( 0 <= enModel && enModel < enSK_MODEL_MAX ){
		return true;
	}
	return false;
}

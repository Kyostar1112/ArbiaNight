#include "Effects.h"
#include "Global.h"

//�ő�`����ײĐ�.(��΂��Ȃ�int�^�ɂ���)
const /*int32_t*/ int g_RenderSpriteMax = 8192;
//�̪�ĊǗ��p�ݽ�ݽ�ő吔.
const int g_EffectInstanceMax = 4096;


//�̪��̧�ق�ؽ�.
const wchar_t g_strFileNameList[ clsEffects::enEfcType_Max ][128] =
{
	L"Data\\Effekseer\\tex\\asiato.efk",
	L"Data\\Effekseer\\tex\\arbia_kougeki.efk",
	L"Data\\Effekseer\\tex\\syougekiha.efk",
	L"Data\\Effekseer\\tex\\kougeki.efk",

	L"Data\\Effekseer\\tex\\Teki_kougeki.efk",
	L"Data\\Effekseer\\tex\\yarare.efk",

	L"Data\\Effekseer\\tex\\hibana.efk",
	L"Data\\Effekseer\\tex\\pen_kaze.efk",

	L"Data\\Effekseer\\tex\\takara_hasira.efk",
	L"Data\\Effekseer\\tex\\takara_nakami.efk",

	L"Data\\Effekseer\\tex\\tobira_sunabokori.efk",
};


clsEffects::clsEffects()
{
//	ZeroMemory( this, sizeof( clsEffects ) );
	m_pManager = nullptr;
	m_pRender = nullptr;
	m_pSound = nullptr;
	m_pXA2 = nullptr;
	m_pXA2Master = nullptr;
	for( int i=0; i<enEfcType_Max; i++ ){
		m_pEffect[i] = nullptr;
	}
}

clsEffects::~clsEffects()
{
	Destroy();
}


//==================================================
//	�\�z�֐�.
//==================================================
HRESULT clsEffects::Create( ID3D11Device* pDevice, ID3D11DeviceContext* pContext )
{
	//XAudio2�̏��������s��.
	if( FAILED( XAudio2Create( &m_pXA2 ) ) ){
		ERR_MSG( "XAudio2�쐬���s", "clsEffects::Create()" );
		return E_FAIL;
	}
	if( FAILED( m_pXA2->CreateMasteringVoice( &m_pXA2Master ) ) ){
		ERR_MSG( "MasteringVoice�쐬���s", "clsEffects::Create()" );
		return E_FAIL;
	}


	//�`��p�ݽ�ݽ�̐���.
	m_pRender = ::EffekseerRendererDX11::Renderer::Create(
		pDevice, pContext, g_RenderSpriteMax );

	//�̪�ĊǗ��p�ݽ�ݽ.
	m_pManager = ::Effekseer::Manager::Create( g_EffectInstanceMax );

	//�`��p�ݽ�ݽ����`��@�\��ݒ�.
	m_pManager->SetSpriteRenderer( m_pRender->CreateSpriteRenderer() );
	m_pManager->SetRibbonRenderer( m_pRender->CreateRibbonRenderer() );
	m_pManager->SetRingRenderer( m_pRender->CreateRingRenderer() );
	m_pManager->SetModelRenderer( m_pRender->CreateModelRenderer() );

	//�`��ݽ�ݽ����ø����̓Ǎ��@�\��ݒ�.
	//�Ǝ��g���\�A���݂�̧�ق���ǂݍ���ł���.
	m_pManager->SetTextureLoader( m_pRender->CreateTextureLoader() );
	m_pManager->SetModelLoader( m_pRender->CreateModelLoader() );

	//���Đ��p�ݽ�ݽ�̐���.
	m_pSound = ::EffekseerSound::Sound::Create( m_pXA2, 16, 16 );


	//���Đ��p�ݽ�ݽ����Đ��@�\��ݒ�.
	m_pManager->SetSoundPlayer( m_pSound->CreateSoundPlayer() );

	//���Đ��p�ݽ�ݽ���绳����ް��̓Ǎ��@�\��ݒ�.
	//�Ǝ��g���\�A���݂�̧�ق���ǂݍ���ł���.
	m_pManager->SetSoundLoader( m_pSound->CreateSoundLoader() );


	return S_OK;
}


//==================================================
//	�j���֐�.
//==================================================
HRESULT clsEffects::Destroy()
{
	//�̪���ް����.
	ReleaseData();

	//��ɴ̪�ĊǗ��p�ݽ�ݽ��j��.
	m_pManager->Destroy();

	//���ɉ��Đ��p�ݽ�ݽ��j��.
	m_pSound->Destory();

	//�`��p�ݽ�ݽ��j��.
	m_pRender->Destory();

	//XAudio2�̉��.
	if( m_pXA2Master != NULL ){
		m_pXA2Master->DestroyVoice();
		m_pXA2Master = NULL;
	}
	ES_SAFE_RELEASE( m_pXA2 );

	return S_OK;
}


//==================================================
//	�ް��Ǎ��֐�.
//==================================================
HRESULT clsEffects::LoadData()
{
	////�̪�Ă̓Ǎ�.
	//m_pEffect =
	//	::Effekseer::Effect::Create( 
	//		m_pManager, (const EFK_CHAR*)L"Data\\Effekseer\\mari.efk" );
	//if( m_pEffect == NULL ){
	//	ERR_MSG( "�̪��̧�ٓǍ����s", "clsEffects::LoadData()" );
	//	return E_FAIL;
	//}

	//�̪�Ă̓Ǎ�.
	for( int i=0; i<enEfcType_Max; i++ ){
		m_pEffect[i] =
			::Effekseer::Effect::Create( 
				m_pManager, 
				(const EFK_CHAR*)g_strFileNameList[i] );
		if( m_pEffect[i] == NULL ){
			char strMsg[128];
			wsprintf( strMsg, "clsEffects::LoadData()\n%ls",
				g_strFileNameList[i] );

			ERR_MSG( strMsg, "�̪��̧�ٓǍ����s" );
			return E_FAIL;
		}
	}

	return S_OK;
}

//==================================================
//	�ް�����֐�.
//==================================================
HRESULT clsEffects::ReleaseData()
{
	//�̪�Ă̔j��.
	for( int i=0; i<enEfcType_Max; i++ ){
		ES_SAFE_RELEASE( m_pEffect[i] );
	}

	return S_OK;
}

//==================================================
//	�`��.
//==================================================
void clsEffects::Render( D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vEye )
{
	//�ޭ��s��ݒ�.
	SetViewMatrix( mView );

	//��ۼު���ݍs��ݒ�.
	SetProjectionMatrix( mProj );

	//�̪�Ă̍X�V����.
	m_pManager->Update();

	//-----------------------------
	//	Effekseer�����ݸ�.
	//-----------------------------
	//�̪�Ă̕`��J�n�������s��.
	m_pRender->BeginRendering();

	//�̪�Ă̕`����s��.
	m_pManager->Draw();

	//�̪�Ă̕`��I���������s��.
	m_pRender->EndRendering();


}

//==================================================
//	�ޭ��s��ݒ�.
//==================================================
void clsEffects::SetViewMatrix( D3DXMATRIX& mView )
{
	//�ޭ�(���)�s��.
	::Effekseer::Matrix44 tmpEsCamMat;

	//DirectX Matrix �� Effekseer Matrix.
	tmpEsCamMat = MatrixDxToEfk( &mView );

	//�ޭ��s���ݒ�.
	m_pRender->SetCameraMatrix( tmpEsCamMat );

}

//==================================================
//	��ۼު���ݍs��ݒ�.
//==================================================
void clsEffects::SetProjectionMatrix( D3DXMATRIX& mProj )
{
	//��ۼު���ݍs��.
	::Effekseer::Matrix44 tmpEsPrjMat;

	//DirectX Matrix �� Effekseer Matrix.
	tmpEsPrjMat = MatrixDxToEfk( &mProj );

	//��ۼު���ݍs���ݒ�.
	m_pRender->SetProjectionMatrix( tmpEsPrjMat );

}








//==================================================
//	�޸���ϊ��֐�(1)	DirectX Vector3 �� Effekseer Vector3.
//==================================================
::Effekseer::Vector3D clsEffects::Vector3DDxToEfk( const D3DXVECTOR3* pSrcVec3Dx )
{
	return ::Effekseer::Vector3D(
		pSrcVec3Dx->x,
		pSrcVec3Dx->y,
		pSrcVec3Dx->z );
}
//==================================================
//	�޸���ϊ��֐�(2)	Effekseer Matrix �� DirectX Matrix.
//==================================================
D3DXVECTOR3 clsEffects::Vector3EfkToDx( const ::Effekseer::Vector3D* pSrcVec3Efk )
{
	return D3DXVECTOR3(
		pSrcVec3Efk->X,
		pSrcVec3Efk->Y,
		pSrcVec3Efk->Z );
}

//==================================================
//	�s��ϊ��֐�(1)	DirectX Matrix �� Effekseer Matrix.
//==================================================
::Effekseer::Matrix44 clsEffects::MatrixDxToEfk(
				const D3DXMATRIX* pSrcMatDx )
{
	::Effekseer::Matrix44 OutMatEfk;

#if 0

	for( int i=0; i<4; i++ ){
		for( int j=0; j<4; j++ ){
			OutMatEfk.Values[i][j] = pSrcMatDx->m[i][j];
		}
	}

#else

	OutMatEfk.Values[0][0] = pSrcMatDx->_11;
	OutMatEfk.Values[0][1] = pSrcMatDx->_12;
	OutMatEfk.Values[0][2] = pSrcMatDx->_13;
	OutMatEfk.Values[0][3] = pSrcMatDx->_14;

	OutMatEfk.Values[1][0] = pSrcMatDx->_21;
	OutMatEfk.Values[1][1] = pSrcMatDx->_22;
	OutMatEfk.Values[1][2] = pSrcMatDx->_23;
	OutMatEfk.Values[1][3] = pSrcMatDx->_24;

	OutMatEfk.Values[2][0] = pSrcMatDx->_31;
	OutMatEfk.Values[2][1] = pSrcMatDx->_32;
	OutMatEfk.Values[2][2] = pSrcMatDx->_33;
	OutMatEfk.Values[2][3] = pSrcMatDx->_34;

	OutMatEfk.Values[3][0] = pSrcMatDx->_41;
	OutMatEfk.Values[3][1] = pSrcMatDx->_42;
	OutMatEfk.Values[3][2] = pSrcMatDx->_43;
	OutMatEfk.Values[3][3] = pSrcMatDx->_44;

#endif

	return OutMatEfk;
}
//==================================================
//	�s��ϊ��֐�(2)	Effekseer Matrix �� DirectX Matrix.
//==================================================
D3DXMATRIX clsEffects::MatrixEfkToDx(
				const ::Effekseer::Matrix44* pSrcMatEfk )
{
	D3DXMATRIX OutMatDx;

#if 0

	for( int i=0; i<4; i++ ){
		for( int j=0; j<4; j++ ){
			OutMatDx.m[i][j] = pSrcMatEfk->Values[i][j];
		}
	}

#else

	OutMatDx._11 = pSrcMatEfk->Values[0][0];
	OutMatDx._12 = pSrcMatEfk->Values[0][1];
	OutMatDx._13 = pSrcMatEfk->Values[0][2];
	OutMatDx._14 = pSrcMatEfk->Values[0][3];
			
	OutMatDx._21 = pSrcMatEfk->Values[1][0];
	OutMatDx._22 = pSrcMatEfk->Values[1][1];
	OutMatDx._23 = pSrcMatEfk->Values[1][2];
	OutMatDx._24 = pSrcMatEfk->Values[1][3];
			
	OutMatDx._31 = pSrcMatEfk->Values[2][0];
	OutMatDx._32 = pSrcMatEfk->Values[2][1];
	OutMatDx._33 = pSrcMatEfk->Values[2][2];
	OutMatDx._34 = pSrcMatEfk->Values[2][3];
			
	OutMatDx._41 = pSrcMatEfk->Values[3][0];
	OutMatDx._42 = pSrcMatEfk->Values[3][1];
	OutMatDx._43 = pSrcMatEfk->Values[3][2];
	OutMatDx._44 = pSrcMatEfk->Values[3][3];

#endif

	return OutMatDx;
}


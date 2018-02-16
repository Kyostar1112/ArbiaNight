#include "SpShadow.h"

//�����̧�ٖ�(�ިڸ�؂��܂�)(\\).
const char SHADER_NAME[] = "Shader\\Mesh.hlsl";
const char TEX_FILE_NAME[] = "Data\\Image\\shadow.png";

//============================================================
//�ݽ�׸�.
//============================================================
clsShadow::clsShadow()
{
//	//������.
//	ZeroMemory( this, sizeof( clsShadow ) );
	m_fYaw = m_fPitch = m_fRoll = 0.0f;
	m_vPos = { 0.0f, 0.0f, 0.0f };
	m_bDispFlg = true;

	m_pVertexShader = NULL;	
	m_pVertexLayout = NULL;	
	m_pPixelShader = NULL;		
	m_pConstantBuffer = NULL;	
	m_pVertexBuffer = NULL;	
	m_pTexture = NULL;		
	m_pSampleLinear = NULL;

	m_fScale = fDEFAULT_SHADOW_SCALE;
}

//============================================================
//�޽�׸�.
//============================================================
clsShadow::~clsShadow()
{
	//�����ł͉�����Ȃ�.
	m_pDevice11 = NULL;
	m_pDeviceContext11 = NULL;
}


//============================================================
//	���ٍ쐬.clsSprite
//============================================================
HRESULT clsShadow::InitModel()
{
	float itaW = 0.5f;
	float w, h;
	w = 1.0f;
	h = 1.0f;

	//�����(�l�p�`)�̒��_���쐬.
	SpriteVertex vertices[] = 
	{
		//���_���W(x,y,z).					//UV���W( u, v ).
		D3DXVECTOR3(-itaW, 0.0f,-itaW ),	D3DXVECTOR2( 0.0f,    h ),	//���_1.
		D3DXVECTOR3(-itaW, 0.0f, itaW ),	D3DXVECTOR2( 0.0f, 0.0f ),	//���_2.
		D3DXVECTOR3( itaW, 0.0f,-itaW ),	D3DXVECTOR2(	w,	  h ),	//���_3.
		D3DXVECTOR3( itaW, 0.0f, itaW ),	D3DXVECTOR2(	w, 0.0f )	//���_4.
	};
	//�ő�v�f�����Z�o����.
	UINT uVerMax = sizeof(vertices) / sizeof(vertices[0]);

	//�ޯ̧�\����.
	D3D11_BUFFER_DESC bd;
	bd.Usage			= D3D11_USAGE_DEFAULT;		//�g�p�@(��̫��).
	bd.ByteWidth		= sizeof( SpriteVertex ) * uVerMax;//���_����(���_*3).
	bd.BindFlags		= D3D11_BIND_VERTEX_BUFFER;	//���_�ޯ̧�Ƃ��Ĉ���.
	bd.CPUAccessFlags	= 0;						//CPU����ͱ������Ȃ�.
	bd.MiscFlags		= 0;						//���̑����׸�(���g�p).
	bd.StructureByteStride	= 0;					//�\���̻���(���g�p).

	//���ؿ���ް��\����.
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem	= vertices;	//����؂̒��_���.

	//���_�ޯ̧�̍쐬.
	if( FAILED(
		m_pDevice11->CreateBuffer(
			&bd, &InitData, &m_pVertexBuffer ) ) )
	{
		MessageBox( NULL, "���_�ޯ̧�쐬���s", "clsShadow::InitModel", MB_OK );
		return E_FAIL;
	}


	//���_�ޯ̧���.
	UINT stride = sizeof( SpriteVertex );//�ް��Ԋu.
	UINT offset = 0;//�J�n�ʒu.
	m_pDeviceContext11->IASetVertexBuffers(
		0, 1, 
		&m_pVertexBuffer, &stride, &offset );


	//ø����p�̻���װ�\����.
	D3D11_SAMPLER_DESC	SamDesc;
	ZeroMemory( &SamDesc, sizeof( SamDesc ) );
	//�Ʊ̨���(���^���).
	//	POINT:���������e��.
	SamDesc.Filter	= D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	//ׯ��ݸ�Ӱ��.
	//	WRAP:�J��Ԃ�.
	//	MIRROR	:���]�J��Ԃ�.
	//	CLAMP	:�[�̖͗l���������΂�.
	//	BORDER	;�ʓr���E�F�����߂�.
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP; 
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	//����װ�쐬.
	if( FAILED(
		m_pDevice11->CreateSamplerState(
			&SamDesc, &m_pSampleLinear ) ) )//(out)����װ.
	{
		MessageBox( NULL, "����׍쐬���s", "clsShadow::InitModel", MB_OK );
		return E_FAIL;
	}

	//ø����쐬.
	if( FAILED(
		D3DX11CreateShaderResourceViewFromFile(
			m_pDevice11,		//ؿ�����g�p�������޲��ւ��߲��.
			TEX_FILE_NAME,	//̧�ٖ�(�߽���K�v).
			NULL, NULL,
			&m_pTexture,	//(out)ø���.
			NULL ) ) )
	{
		MessageBox( NULL, "ø����쐬���s", "clsShadow::InitModel", MB_OK );
		return E_FAIL;
	}


	return S_OK;
}


//============================================================
//�`��(�����ݸ�)(��DX9MESH����Main����2���݂���̂Œ���).
//============================================================
void clsShadow::Render( D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3 &vEye )
{
	//ܰ��ލs��.
	D3DXMATRIX	mWorld;
	D3DXMATRIX	mScale, mYaw, mPitch, mRoll, mTrans;

	//ܰ��ޕϊ�(�\���ʒu��ݒ肷��).
	D3DXMatrixIdentity( &mWorld );	//������:�P�ʍs��쐬.

	//�g�k.
	D3DXMatrixScaling( &mScale,
		m_fScale, m_fScale, m_fScale );

	//��].
	D3DXMatrixRotationX( &mPitch,	m_fPitch ); //X����].
	D3DXMatrixRotationY( &mYaw,		m_fYaw );	//Y����].
	D3DXMatrixRotationZ( &mRoll,	m_fRoll );	//Z����].

	//���s�ړ�.
	D3DXMatrixTranslation( &mTrans,
		m_vPos.x, m_vPos.y, m_vPos.z );

	//����(�g�kx��]x�ړ�).
	mWorld = mScale * mRoll * mYaw * mPitch * mTrans;

	//�g�p���鼪��ނ̓o�^.
	m_pDeviceContext11->VSSetShader( m_pVertexShader, NULL, 0 );
	m_pDeviceContext11->PSSetShader( m_pPixelShader,  NULL, 0 );

	////����ް�ޗp.
	//D3DXMATRIX CancelRotation = mView;//�ޭ�(���)�s��.
	//CancelRotation._41 =
	//	CancelRotation._42 = CancelRotation._43 = 0;//xyz��0�ɂ���.
	////CancelRotation�̋t�s������߂�.
	//D3DXMatrixInverse( &CancelRotation, NULL, &CancelRotation );
	//mWorld = CancelRotation * mWorld;



	//����ނ̺ݽ����ޯ̧�Ɋe���ް���n��.
	D3D11_MAPPED_SUBRESOURCE pData;
	SHADOW_CONSTANT_BUFFER cb;	//�ݽ����ޯ̧.
	//�ޯ̧�����ް��̏������J�n����map.
	if( SUCCEEDED(
		m_pDeviceContext11->Map(
			m_pConstantBuffer, 0,
			D3D11_MAP_WRITE_DISCARD, 0, &pData ) ) )
	{
		//ܰ���,���,��ۼު���ݍs���n��.
		D3DXMATRIX m = mWorld * mView * mProj;
		D3DXMatrixTranspose( &m, &m );	//�s���]�u����.
					//�s��̌v�Z���@��DirectX��GPU�ňقȂ邽��.
		cb.mWVP = m;

		//�װ.
		D3DXVECTOR4 vColor( 1.0f, 1.0f, 1.0f, 1.0f );
		cb.vColor = vColor;

		//ø������W.
		D3DXVECTOR4 texUV( 0.0f, 0.0f, 0.0f, 0.0f );
		
		texUV.x = texUV.y = 0.0f;

		cb.vUV = texUV;



		memcpy_s( pData.pData, pData.RowPitch,
			(void*)( &cb ), sizeof( cb ) );

		m_pDeviceContext11->Unmap( m_pConstantBuffer, 0 );
	}

	//���̺ݽ����ޯ̧���ǂ̼���ނŎg����?.
	m_pDeviceContext11->VSSetConstantBuffers(
		2, 1, &m_pConstantBuffer );
	m_pDeviceContext11->PSSetConstantBuffers(
		2, 1, &m_pConstantBuffer );

	//���_�ޯ̧���.
	UINT stride = sizeof( SpriteVertex );
	UINT offset = 0;
	m_pDeviceContext11->IASetVertexBuffers(
		0, 1, &m_pVertexBuffer, &stride, &offset );

	//���_���߯�ڲ��Ă��.
	m_pDeviceContext11->IASetInputLayout( m_pVertexLayout );

	//����è�ށE���ۼް���.
	m_pDeviceContext11->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ø����𼪰�ނɓn��.
	m_pDeviceContext11->PSSetSamplers(
		0, 1, &m_pSampleLinear );	//����װ���.
	m_pDeviceContext11->PSSetShaderResources(
		0, 1, &m_pTexture );		//ø����𼪰�ނɓn��.

	//��̧�����ޗp�����޽ðč쐬&�ݒ�.
	SetBlend( true );


	//����è�ނ������ݸ�.
	m_pDeviceContext11->Draw( 4, 0 );

	//��̧�����ނ𖳌��ɂ���.
	SetBlend( false );

}



//============================================================
//	�e�Z�b�g.
//============================================================
void clsShadow::SetShadow(  D3DXVECTOR3 vPos, float fFloor, float fScaleMax )
{
	SetPos( vPos, fFloor );
	ShadScale( vPos.y, fFloor, fScaleMax );
}



//============================================================
//	���W�Z�b�g.
//============================================================
void clsShadow::SetPos( D3DXVECTOR3 vPos, float fFloor )//Y���W�͏��̍����ōX�V.
{
	const float fUp = 0.03125f;//������ǂꂾ����������?.
	m_vPos = vPos;
	m_vPos.y = fFloor + fUp;
}

//============================================================
//	�e�T�C�Y.
//============================================================
void clsShadow::ShadScale( float fPosY,float fFloor, float fScaleMax )
{
	const float fMAX_SCALE_HEIGHT = 0.75f;//�e���������Ȃ�Ȃ��n�ォ��̍���.

	const float fSHADOW_Y = fFloor;
	const float fSHADOW_Y_2 = fSHADOW_Y - fMAX_SCALE_HEIGHT;

	//���ޏ�����(�ő廲��).
	m_fScale = fScaleMax;

	//�傫���Ȃ肷���Ȃ����߂�IF.
	if( fPosY >= fSHADOW_Y ){
		//�n�ʂƂ̋���.
		float fSadLgth = fPosY - fSHADOW_Y_2;

		//�������ŏ������Ȃ肷���Ȃ��悤�ɂ���.
		fSadLgth = sqrtf( fSadLgth );

		//			�t��.
		m_fScale *= 1.0f / fSadLgth ;//���̂������قǉe���������Ȃ�.
	}
}

#include "Sprite2d.h"


//============================================================
//	�萔.
//============================================================

//�����̧�ٖ�(�ިڸ�؂��܂�)(\\).
const string SHADER_NAME = "Shader\\Sprite2D.hlsl";

clsSprite2D::clsSprite2D()
	: m_vPos( 0.0f, 0.0f, 0.0f )
	, m_AnimCount( 0 )
	, m_bDispFlg( false )
	, m_fAlpha( 1.0f )
	, m_pTexture( NULL )
	, m_pVertexShader( NULL )
	, m_pVertexLayout( NULL )
	, m_pPixelShader( NULL )
	, m_pConstantBuffer( NULL )
	, m_pVertexBuffer( NULL )
	, m_pSampleLinear( NULL )
{
//	ZeroMemory( this, sizeof( clsSprite2D ) );
//	m_fAlpha = 1.0f;
//	m_fPatternNo.x = 0.0f;
//	m_fPatternNo.y = 0.0f;

	m_SState.Base.h		= 0.0f;
	m_SState.Base.w		= 0.0f;
	m_SState.Disp.h		= 0.0f;
	m_SState.Disp.w		= 0.0f;
	m_SState.Stride.h	= 0.0f;
	m_SState.Stride.w	= 0.0f;

	m_fPatternNo.x	= 0.0f;
	m_fPatternNo.y	= 0.0f;
}

clsSprite2D::~clsSprite2D()
{
	// �����[�X�֐����Ƃ肠�����A�f�X�g���N�^�ɓ˂�����.
	Release();
}


//============================================================
//	������.
//============================================================
HRESULT clsSprite2D::Create( ID3D11Device* pDevice11,
	ID3D11DeviceContext* pContext11,
	LPSTR fileName,
	float SetStrideW,
	float SetStrideH)
{
	m_sFileName = fileName;
	m_pDevice11 = pDevice11;
	m_pDeviceContext11 = pContext11;

	m_SState.Stride.w = SetStrideW;
	m_SState.Stride.h = SetStrideH;

	SetPos( -WND_W, -WND_H );

	m_BlackMode = Idle;

	// ���̍\���̂̒��ɉ摜�̏�񂪓���
	D3DXIMAGE_INFO info;

	// filename�͂��̂܂�܁A�Ώۂ̉摜�t�@�C����
	D3DXGetImageInfoFromFile(m_sFileName.c_str(), &info);

	SetSs( static_cast<float>(info.Width), static_cast<float>(info.Height) );

	if( FAILED( InitShader() ) ){
		return E_FAIL;
	}
	if( FAILED( InitModel( m_SState ) ) ){
		return E_FAIL;
	}
	if( FAILED( CreateTexture( (LPSTR)m_sFileName.c_str(), &m_pTexture ) ) ){
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	HLSĻ�ق�ǂݍ��ݼ���ނ��쐬����.
//	HLSL:HIGE-LEVEL-SHADER-LANGUAGE.
//============================================================
HRESULT clsSprite2D::InitShader()
{
	ID3DBlob* pCompiledShader = NULL;
	ID3DBlob* pErrors = NULL;

	UINT uCompileFlag = 0;

#ifdef _DEBUG
	uCompileFlag
		= D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#endif//#ifdef _DEBUG


	//HLSL�����ްï������ނ�����ނ��쐬.
	if( FAILED(
		D3DX11CompileFromFile(
			SHADER_NAME.c_str(),	//�����̧�ٖ�(HLSĻ��).
			NULL,			//ϸے�`�̔z��ւ��߲��(���g�p).
			NULL,			//�ݸٰ��̧�ق���������̪���ւ��߲��(���g�p).
			"VS_Main",			//����޴��ذ�߲�Ċ֐��̖��O.
			"vs_5_0",		//����ނ����ق��w�肷�镶����(���̧��).
			uCompileFlag,	//����޺��߲��׸�.
			0,				//�̪�ĺ��߲��׸�(���g�p).
			NULL,			//�گ������߲���̪���ւ��߲��(���g�p).
			&pCompiledShader,//����ނ��i�[������؂ւ��߲��.
			&pErrors,		//�װ�ƌx���ꗗ���i�[������؂ւ��߲��.
			NULL ) ) )		//�߂�l�ւ��߲��(���g�p).
	{
		MessageBox(NULL, "hlsl(vs)�ǂݍ��ݎ��s", "clsSprite2D::InitShader", MB_OK );
		return E_FAIL;
	}
	SAFE_RELEASE( pErrors );

	//��L�ō쐬��������ނ���u�ްï������ށv���쐬.
	if( FAILED(
		m_pDevice11->CreateVertexShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			NULL,
			&m_pVertexShader ) ) )//(out)�ްï�������.
	{
		MessageBox( NULL, "vs�쐬���s", "clsSprite2D::InitShader", MB_OK );
		return E_FAIL;
	}

	//���_���߯�ڲ��Ă��`.
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{
			"POSITION",						//�ʒu.
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,	//DXGI��̫�ϯ�(32bit float�^*3).
			0,
			0,								//�ް��̊J�n�ʒu.
			D3D11_INPUT_PER_VERTEX_DATA, 0
		},
		{
			"TEXCOORD",					//ø����ʒu.
			0,
			DXGI_FORMAT_R32G32_FLOAT,	//DXGI��̫�ϯ�(32bit float�^*2).
			0,
			12,							//ø����ް��̊J�n�ʒu(���_�ް���float�^*3=12bite�Ȃ̂�+12).
			D3D11_INPUT_PER_VERTEX_DATA, 0
		}
	};
	//���_���߯�ڲ��Ă̔z��v�f�����Z�o.
	UINT numElements = sizeof( layout ) / sizeof( layout[0] );//.

	//���_���߯�ڲ��Ă̍쐬.
	if( FAILED(
		m_pDevice11->CreateInputLayout(
			layout,
			numElements,
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			&m_pVertexLayout ) ) )//(out)���_���߯�ڲ���.
	{
		MessageBox( NULL, "���_���߯�ڲ��č쐬���s", "clsSprite2D::InitShader", MB_OK );
		return E_FAIL;
	}
	SAFE_RELEASE( pCompiledShader );





	//HLSL�����߸�ټ���ނ�����ނ��쐬.
	if( FAILED(
		D3DX11CompileFromFile(
			SHADER_NAME.c_str(),	//�����̧�ٖ�(HLSĻ��).
			NULL,
			NULL,
			"PS_Main",			//����޴��ذ�߲�Ċ֐��̖��O.
			"ps_5_0",		//����ނ����ق��w�肷�镶����(���̧��).
			uCompileFlag,	//����޺��߲��׸�.
			0,
			NULL,
			&pCompiledShader,//����ނ��i�[������؂ւ��߲��.
			&pErrors,
			NULL ) ) )
	{
		MessageBox( NULL, "hlsl(ps)�ǂݍ��ݎ��s", "clsSprite2D::InitShader", MB_OK );
		return E_FAIL;
	}
	SAFE_RELEASE( pErrors );

	//��L�ō쐬��������ނ���u�߸�ټ���ށv���쐬.
	if( FAILED(
		m_pDevice11->CreatePixelShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			NULL,
			&m_pPixelShader ) ) )//(out)�߸�ټ����.
	{
		MessageBox( NULL, "ps�쐬���s", "clsSprite2D::InitShader", MB_OK );
		return E_FAIL;
	}
	SAFE_RELEASE( pCompiledShader );//����މ��.


	//�ݽ����ޯ̧(�萔)�ޯ̧�쐬�@����ނɓ���̐��l�𑗂��ޯ̧.
	D3D11_BUFFER_DESC cb;
	cb.BindFlags	= D3D11_BIND_CONSTANT_BUFFER;;			//�ݽ��ޯ̧���w��.
	cb.ByteWidth	= sizeof( SPRITE2D_CONSTANT_BUFFER );//�ݽ����ޯ̧�̻���.
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;				//�������݂ű���.
	cb.MiscFlags	= 0;					//���̑����׸�(���g�p).
	cb.StructureByteStride	= 0;			//�\���̻̂���(���g�p)
	cb.Usage		= D3D11_USAGE_DYNAMIC;	//�g�p���@:���ڏ�������.

	//�ݽ����ޯ̧�쐬.
	if( FAILED(
		m_pDevice11->CreateBuffer(
			&cb,
			NULL,
			&m_pConstantBuffer ) ) )
	{
		MessageBox( NULL, "�ݽ����ޯ̧�쐬���s", "clsSprite2D::InitShader", MB_OK );
		return E_FAIL;
	}




	return S_OK;
}

//============================================================
//	���ٍ쐬.
//============================================================
HRESULT clsSprite2D::InitModel( SPRITE_STATE ss )
{
	float fW = ss.Disp.w;	//�\�����ײĕ�.
	float fH = ss.Disp.h;	//�\�����ײč���.
	float fU = (ss.Base.w / ss.Stride.w)/ss.Base.w;	//��ς�����̕�.
	float fV = (ss.Base.h / ss.Stride.h)/ss.Base.h;	//��ς�����̍���.

	//�����(�l�p�`)�̒��_���쐬.
	Sprite2DVertex vertices[] =
	{
		//���_���W(x,y,z).					//UV���W( u, v ).
		D3DXVECTOR3( 0.0f,   fH, 0.0f ),	D3DXVECTOR2( 0.0f,	 fV ),	//���_1(����).
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),	D3DXVECTOR2( 0.0f, 0.0f ),	//���_2(����).
		D3DXVECTOR3(   fW,	 fH, 0.0f ),	D3DXVECTOR2(   fU,	 fV ),	//���_3(�E��).
		D3DXVECTOR3(   fW, 0.0f, 0.0f ),	D3DXVECTOR2(   fU, 0.0f )	//���_4(�E��).
	};
	//�ő�v�f�����Z�o����.
	UINT uVerMax = sizeof(vertices) / sizeof(vertices[0]);

	//�ޯ̧�\����.
	D3D11_BUFFER_DESC bd;
	bd.Usage			= D3D11_USAGE_DEFAULT;		//�g�p�@(��̫��).
	bd.ByteWidth		= sizeof( Sprite2DVertex ) * uVerMax;//���_����(���_*4).
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
		MessageBox( NULL, "���_�ޯ̧�쐬���s", "clsSprite2D::InitModel", MB_OK );
		return E_FAIL;
	}


	//���_�ޯ̧���.
	UINT stride = sizeof( Sprite2DVertex );//�ް��Ԋu.
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
		MessageBox( NULL, "����׍쐬���s", "clsSprite2D::InitModel", MB_OK );
		return E_FAIL;
	}



	return S_OK;
}

//============================================================
//	ø����쐬.
//============================================================
HRESULT clsSprite2D::CreateTexture( LPSTR fileName,
	ID3D11ShaderResourceView** pTex )
{
	//ø����쐬.
	if( FAILED(
		D3DX11CreateShaderResourceViewFromFile(
			m_pDevice11,		//ؿ�����g�p�������޲��ւ��߲��.
			fileName,	//̧�ٖ�(�߽���K�v).
			NULL, NULL,
			pTex,	//(out)ø���.
			NULL ) ) )
	{
		ERR_MSG( fileName, "clsSprite2D::CreateTexture" );
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//�`��(�����ݸ�)(��DX9MESH����Main����2���݂���̂Œ���).
//============================================================
void clsSprite2D::Render()
{
	//ܰ��ލs��.
	D3DXMATRIX	mWorld;

	//ܰ��ޕϊ�(�\���ʒu��ݒ肷��).
	D3DXMatrixIdentity( &mWorld );	//������:�P�ʍs��쐬.

	D3DXMATRIX mScale;
	//�g�k.
	{
		D3DXMatrixIdentity( &mScale );	//������:�P�ʍs��쐬.
		float x = (m_SState.Disp.w/m_SState.Base.w);
		float y = (m_SState.Disp.h/m_SState.Base.h);
		D3DXMatrixScaling( &mScale, x, y, 1.0f );

	}

	//���s�ړ�.
	D3DXMATRIX mTrans;
	D3DXMatrixIdentity( &mTrans );	//������:�P�ʍs��쐬.
	D3DXMatrixTranslation( &mTrans,
		m_vPos.x, m_vPos.y, m_vPos.z );

	//Matrix���Z.
	mWorld = mScale * mTrans;

	//�g�p���鼪��ނ̓o�^.
	m_pDeviceContext11->VSSetShader( m_pVertexShader, NULL, 0 );
	m_pDeviceContext11->PSSetShader( m_pPixelShader,  NULL, 0 );

	//����ނ̺ݽ����ޯ̧�Ɋe���ް���n��.
	D3D11_MAPPED_SUBRESOURCE pData;
	SPRITE2D_CONSTANT_BUFFER cd;	//�ݽ����ޯ̧.
	//�ޯ̧�����ް��̏������J�n����map.
	if( SUCCEEDED(
		m_pDeviceContext11->Map(
			m_pConstantBuffer, 0,
			D3D11_MAP_WRITE_DISCARD, 0, &pData ) ) )
	{
		//ܰ��ލs���n��.
		D3DXMATRIX m = mWorld;
		D3DXMatrixTranspose( &m, &m );	//�s���]�u����.
					//�s��̌v�Z���@��DirectX��GPU�ňقȂ邽��.
		cd.mW = m;

		//�ޭ��߰Ă̕��A������n��.
		cd.fViewPortWidth = WND_W;
		cd.fViewPortHeight= WND_H;

		//��̧�l��n��.
		cd.fAlpha = m_fAlpha;

		//UV���W.
		//1��������̊����ɺϔԍ����|���Ĉʒu��ݒ肷��.
		WHSIZE_FLOAT wf;
		wf.w = (m_SState.Base.w / m_SState.Stride.w)/m_SState.Base.w;
		wf.h = (m_SState.Base.h / m_SState.Stride.h)/m_SState.Base.h;
		cd.vUV.x = wf.w * m_fPatternNo.x;
		cd.vUV.y = wf.h * m_fPatternNo.y;

		memcpy_s( pData.pData, pData.RowPitch,
			(void*)( &cd ), sizeof( cd ) );

		m_pDeviceContext11->Unmap( m_pConstantBuffer, 0 );
	}

	//���̺ݽ����ޯ̧���ǂ̼���ނŎg����?.
	m_pDeviceContext11->VSSetConstantBuffers(
		0, 1, &m_pConstantBuffer );
	m_pDeviceContext11->PSSetConstantBuffers(
		0, 1, &m_pConstantBuffer );

	//���_�ޯ̧���.
	UINT stride = sizeof( Sprite2DVertex );
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

void clsSprite2D::Flashing( float ChaAmo )
{
	if (m_fAlpha > 1)
	{
		m_bFlashing = true;
	}
	if (m_fAlpha < 0)
	{
		m_bFlashing = false;
	}
	if (m_bFlashing)
	{
		m_fAlpha -= ChaAmo;
	}else
	{
		m_fAlpha += ChaAmo;
	}
}

bool clsSprite2D::Release()
{
	SAFE_RELEASE( m_pTexture );
	SAFE_RELEASE( m_pSampleLinear );

	SAFE_RELEASE( m_pPixelShader );

	SAFE_RELEASE( m_pVertexShader );
	SAFE_RELEASE( m_pVertexLayout );

	SAFE_RELEASE( m_pVertexBuffer );

	SAFE_RELEASE( m_pConstantBuffer );

	m_pDeviceContext11 = NULL;
	m_pDevice11 = NULL;

	return true;
}
#include "Sprite.h"

//�����̧�ٖ�(�ިڸ�؂��܂�)(\\).
const char SHADER_NAME[] = "Shader\\Mesh.hlsl";


//============================================================
//�ݽ�׸�.
//============================================================
clsSprite::clsSprite()
{
	//������.
//	ZeroMemory( this, sizeof( clsSprite ) );
	m_pVertexShader		= nullptr;	
	m_pVertexLayout		= nullptr;	
	m_pPixelShader		= nullptr;		
	m_pConstantBuffer	= nullptr;
	m_pVertexBuffer		= nullptr;
	m_pTexture			= nullptr;		
	m_pSampleLinear		= nullptr;

	m_fScale = 1.0f;
}

//============================================================
//�޽�׸�.
//============================================================
clsSprite::~clsSprite()
{
	//�����ł͉�����Ȃ�.
	m_pDevice11 = NULL;
	m_pDeviceContext11 = NULL;
}

//============================================================
//������.
//============================================================
HRESULT clsSprite::Init( ID3D11Device* pDevice11,
	ID3D11DeviceContext* pContext11 )
{
	m_pDevice11 = pDevice11;
	m_pDeviceContext11 = pContext11;

	//����ލ쐬.
	if( FAILED( InitShader() ) ){
		return E_FAIL;
	}
	//����غ�ݍ쐬.
	if( FAILED( InitModel() ) ){
		return E_FAIL;
	}





	return S_OK;
}

//============================================================
//	HLSĻ�ق�ǂݍ��ݼ���ނ��쐬����.
//	HLSL:HIGE-LEVEL-SHADER-LANGUAGE.
//============================================================
HRESULT clsSprite::InitShader()
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
			SHADER_NAME,	//�����̧�ٖ�(HLSĻ��).
			NULL,			//ϸے�`�̔z��ւ��߲��(���g�p).
			NULL,			//�ݸٰ��̧�ق���������̪���ւ��߲��(���g�p).
			"VS_Ita",			//����޴��ذ�߲�Ċ֐��̖��O.
			"vs_5_0",		//����ނ����ق��w�肷�镶����(���̧��).
			uCompileFlag,	//����޺��߲��׸�.
			0,				//�̪�ĺ��߲��׸�(���g�p).
			NULL,			//�گ������߲���̪���ւ��߲��(���g�p).
			&pCompiledShader,//����ނ��i�[������؂ւ��߲��.
			&pErrors,		//�װ�ƌx���ꗗ���i�[������؂ւ��߲��.
			NULL ) ) )		//�߂�l�ւ��߲��(���g�p).
	{
		MessageBox(NULL, "hlsl(vs)�ǂݍ��ݎ��s", "�װ", MB_OK );
		return E_FAIL;
	}
	SAFE_RELEASE( pErrors );

	//��L�ō쐬��������ނ���u�ްï������ށv���쐬.
	if( FAILED(
		m_pDevice11->CreateVertexShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			NULL,
			&m_pVertexShader) ) )//(out)�ްï�������.
	{
		MessageBox( NULL, "vs�쐬���s", "�װ", MB_OK );
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
		MessageBox(NULL, "���_���߯�ڲ��č쐬���s", "�װ", MB_OK );
		return E_FAIL;
	}
	SAFE_RELEASE( pCompiledShader );





	//HLSL�����߸�ټ���ނ�����ނ��쐬.
	if( FAILED(
		D3DX11CompileFromFile(
			SHADER_NAME,	//�����̧�ٖ�(HLSĻ��).
			NULL,
			NULL,
			"PS_Ita",			//����޴��ذ�߲�Ċ֐��̖��O.
			"ps_5_0",		//����ނ����ق��w�肷�镶����(���̧��).
			uCompileFlag,	//����޺��߲��׸�.
			0,
			NULL,
			&pCompiledShader,//����ނ��i�[������؂ւ��߲��.
			&pErrors,
			NULL ) ) )
	{
		MessageBox( NULL, "hlsl(ps)�ǂݍ��ݎ��s", "�װ", MB_OK );
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
		MessageBox( NULL, "ps�쐬���s", "�װ", MB_OK );
		return E_FAIL;
	}
	SAFE_RELEASE( pCompiledShader );//����މ��.


	//�ݽ����ޯ̧(�萔)�ޯ̧�쐬�@����ނɓ���̐��l�𑗂��ޯ̧.
	//�����ł͕ϊ��s��n���p.
	//����ނ�World,View,Projection�s���n��.
	D3D11_BUFFER_DESC cb;
	cb.BindFlags	= D3D11_BIND_CONSTANT_BUFFER;;			//�ݽ��ޯ̧���w��.
	cb.ByteWidth	= sizeof( SPRITESHADER_CONSTANT_BUFFER );//�ݽ����ޯ̧�̻���.
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
		MessageBox( NULL, "�ݽ����ޯ̧�쐬���s", "�װ", MB_OK );
		return E_FAIL;
	}




	return S_OK;
}

//============================================================
//	���ٍ쐬.
//============================================================
HRESULT clsSprite::InitModel()
{
	float itaW = 0.5f;
	float w, h;
	w = h = ( 1.0f / 8.0f );
	w = h = 1.0f;

	//�����(�l�p�`)�̒��_���쐬.
	SpriteVertex vertices[] = 
	{
		//���_���W(x,y,z).					//UV���W( u, v ).
		D3DXVECTOR3(-itaW,-itaW, 0.0f ),	D3DXVECTOR2( 0.0f,    h ),	//���_1.
		D3DXVECTOR3(-itaW, itaW, 0.0f ),	D3DXVECTOR2( 0.0f, 0.0f ),	//���_2.
		D3DXVECTOR3( itaW,-itaW, 0.0f ),	D3DXVECTOR2(	w,	  h ),	//���_3.
		D3DXVECTOR3( itaW, itaW, 0.0f ),	D3DXVECTOR2(	w, 0.0f )	//���_4.
	};
	//�ő�v�f�����Z�o����.
	UINT uVerMax = sizeof(vertices) / sizeof(vertices[0]);

	//�ޯ̧�\����.
	D3D11_BUFFER_DESC bd;
	bd.Usage			= D3D11_USAGE_DEFAULT;		//�g�p�@(��̫��).
	bd.ByteWidth		= sizeof( SpriteVertex ) * uVerMax;//���_����(���_*4).
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
		MessageBox( NULL, "���_�ޯ̧�쐬���s", "�װ", MB_OK );
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
		MessageBox( NULL, "����׍쐬���s", "�װ", MB_OK );
		return E_FAIL;
	}

	//ø����쐬.
	if( FAILED(
		D3DX11CreateShaderResourceViewFromFile(
			m_pDevice11,		//ؿ�����g�p�������޲��ւ��߲��.
			"Data\\Image\\CheckPointSet\\Chi.png",	//̧�ٖ�(�߽���K�v).
			NULL, NULL,
			&m_pTexture,	//(out)ø���.
			NULL ) ) )
	{
		MessageBox( NULL, "ø����쐬���sw", "InitModel()", MB_OK );
		return E_FAIL;
	}


	return S_OK;
}

//============================================================
//�`��(�����ݸ�)(��DX9MESH����Main����2���݂���̂Œ���).
//============================================================
void clsSprite::Render( D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3 &vEye )
{
	//ܰ��ލs��.
	D3DXMATRIX	mWorld, mScale, mTrans;
	//ܰ��ޕϊ�(�\���ʒu��ݒ肷��).
	D3DXMatrixIdentity( &mWorld );	//������:�P�ʍs��쐬.

	//�g�k.
	D3DXMatrixScaling( &mScale, m_fScale, m_fScale, m_fScale );

	//���s�ړ�.
	D3DXMatrixTranslation( &mTrans,
		m_vPos.x, m_vPos.y, m_vPos.z );

	//���Z.
	mWorld = mScale * mTrans;

	//�g�p���鼪��ނ̓o�^.
	m_pDeviceContext11->VSSetShader( m_pVertexShader, NULL, 0 );
	m_pDeviceContext11->PSSetShader( m_pPixelShader,  NULL, 0 );

	//����ް�ޗp.
	D3DXMATRIX CancelRotation = mView;//�ޭ�(���)�s��.
	CancelRotation._41 =
		CancelRotation._42 = CancelRotation._43 = 0;//xyz��0�ɂ���.
	//CancelRotation�̋t�s������߂�.
	D3DXMatrixInverse( &CancelRotation, NULL, &CancelRotation );
	mWorld = CancelRotation * mWorld;



	//����ނ̺ݽ����ޯ̧�Ɋe���ް���n��.
	D3D11_MAPPED_SUBRESOURCE pData;
	SPRITESHADER_CONSTANT_BUFFER cd;	//�ݽ����ޯ̧.
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
		cd.mWVP = m;

		//�װ.
		D3DXVECTOR4 vColor( 1.0f, 1.0f, 1.0f, 1.0f );
		cd.vColor = vColor;

		//ø������W.
		D3DXVECTOR4 texUV( 0.0f, 0.0f, 0.0f, 0.0f );
//		if( m_AnimCount % 8 == 0 ){
//			texUV.x += 1.0f / 8.0f;
//			m_AnimCount = 0;
//			if( texUV.x >= 1.0f ){
//				texUV.x = 0.0f;
//				texUV.y += 1.0f / 8.0f;
//			}
//		}
//		m_AnimCount ++;

		cd.vUV = texUV;



		memcpy_s( pData.pData, pData.RowPitch,
			(void*)( &cd ), sizeof( cd ) );

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



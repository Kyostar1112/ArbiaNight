#include "Particle.h"

const char SHADER_NAME[] = "Shader\\PointSprite.hlsl";


//============================================================
//	�ݽ�׸�.
//============================================================
clsParticle::clsParticle( int MaxParticle,			//�߰è�ٍő吔.
						  D3DXVECTOR3 &vEmitPos )	//���ˈʒu.
{
	ZeroMemory( this, sizeof( clsParticle ) );

	m_iMaxParticle	= MaxParticle;
	m_vEmitPos		= vEmitPos;

	//�߰è�ِ����̔z����쐬.
	m_pParticleArray = new PART[m_iMaxParticle];

	//�߰è�ِ����J��Ԃ�(�߰è�ق̏�����).
	for( int i=0; i<MaxParticle; i++ ){
		m_pParticleArray[i].vPos = m_vEmitPos;	//���ˈʒu(�����ʒu).
		m_pParticleArray[i].vDir				//����.
			= D3DXVECTOR3( 
				(2.0f*( (float)rand() / (float)RAND_MAX ) -1.0f ) / 100.0f,		//X:-0.01f�`0.01.
						(float)rand() / (float)RAND_MAX,						//Y: 0.0�`1.0.
				(2.0f*( (float)rand() / (float)RAND_MAX ) -1.0f ) / 100.0f );	//Z:-0.01f�`0.01.
		D3DXVec3Normalize(
			&m_pParticleArray[i].vDir,
			&m_pParticleArray[i].vDir );//���K��.

		//���x.
		m_pParticleArray[i].fSpeed = 0.2f;
			//= ( 5 + ( (float)rand() / (float)RAND_MAX ) ) * 0.001f;

		//�J�n�ڰ�.
		m_pParticleArray[i].iBirthFrame = rand();

	}
}

//============================================================
//	�޽�׸�.
//============================================================
clsParticle::~clsParticle()
{
	
}


//============================================================
//	������.
//============================================================
HRESULT clsParticle::Init(
	ID3D11Device* pDevice11,
	ID3D11DeviceContext* pContext11 )
{
	m_pDevice11 = pDevice11;
	m_pDeviceContext11 = pContext11;

	if( FAILED( InitShader() ) ){
		return E_FAIL;
	}
	if( FAILED( InitPointSprite() ) ){
		return E_FAIL;
	}
	if( FAILED( InitTexture( "Data\\Image\\shadow.png" ) ) ){
		return E_FAIL;
	}



	return S_OK;
}



//============================================================
//	�߲�Ľ��ײď�����.
//============================================================
HRESULT clsParticle::InitPointSprite()
{
	//�ްï���ޯ̧�쐬.
	PSpriteVertex vertices[] =
	{
		D3DXVECTOR3( -0.5f, 0.5f, 0.0f ),
	};
	D3D11_BUFFER_DESC bd;
	bd.Usage		= D3D11_USAGE_DEFAULT;
	bd.ByteWidth	= sizeof( PSpriteVertex ) * 1;
	bd.BindFlags	= D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags= 0;
	bd.MiscFlags	= 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	if( FAILED( 
		m_pDevice11->CreateBuffer(
			&bd, &InitData, &m_pVertexBuffer ) ) )
	{
		MessageBox( NULL, "���_�ޯ̧�쐬���s", "InitPointSprite:Init", MB_OK );
		return E_FAIL;
	}

	//�ްï���ޯ̧���.
	UINT stride = sizeof( PSpriteVertex );
	UINT offset = 0;
	m_pDeviceContext11->IASetVertexBuffers(
		0, 1, &m_pVertexBuffer, &stride, &offset );



	return S_OK;
}


//============================================================
//	HLSĻ�ق�ǂݍ��ݼ���ނ��쐬����.
//	HLSL:HIGE-LEVEL-SHADER-LANGUAGE.
//============================================================n
HRESULT clsParticle::InitShader()
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
			"VS",		//����޴��ذ�߲�Ċ֐��̖��O.
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
//		{
//			"TEXCOORD",					//ø����ʒu.
//			0,
//			DXGI_FORMAT_R32G32_FLOAT,	//DXGI��̫�ϯ�(32bit float�^*2).
//			0,
//			12,							//ø����ް��̊J�n�ʒu(���_�ް���float�^*3=12bite�Ȃ̂�+12).
//			D3D11_INPUT_PER_VERTEX_DATA, 0
//		}
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



	//HLSL����޵��ؼ���ނ�����ނ��쐬.
	if( FAILED(
		D3DX11CompileFromFile(
			SHADER_NAME,	//�����̧�ٖ�(HLSĻ��).
			NULL,
			NULL,
			"GS_Point",			//����޴��ذ�߲�Ċ֐��̖��O.
			"gs_5_0",		//����ނ����ق��w�肷�镶����(���̧��).
			uCompileFlag,	//����޺��߲��׸�.
			0,
			NULL,
			&pCompiledShader,//����ނ��i�[������؂ւ��߲��.
			&pErrors,
			NULL ) ) )
	{
		MessageBox( NULL, "hlsl(gs)�ǂݍ��ݎ��s", "�װ", MB_OK );
		return E_FAIL;
	}
	SAFE_RELEASE( pErrors );

	//��L�ō쐬��������ނ���u�޵��ؼ���ށv���쐬.
	if( FAILED(
		m_pDevice11->CreateGeometryShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			NULL,
			&m_pGeometryShader ) ) )//(out)�޵��ؼ����.
	{
		MessageBox( NULL, "gs�쐬���s", "�װ", MB_OK );
		return E_FAIL;
	}
	SAFE_RELEASE( pCompiledShader );//����މ��.


	//HLSL�����߸�ټ���ނ�����ނ��쐬.
	if( FAILED(
		D3DX11CompileFromFile(
			SHADER_NAME,	//�����̧�ٖ�(HLSĻ��).
			NULL,
			NULL,
			"PS",			//����޴��ذ�߲�Ċ֐��̖��O.
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
	cb.ByteWidth	= sizeof( PSPRITESHADER_CONSTANT_BUFFER );//�ݽ����ޯ̧�̻���.
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
//	�`��(�����ݸ�)(��DX9MESH����Main����2���݂���̂Œ���).
//============================================================
void clsParticle::Render( D3DXMATRIX &mView, D3DXMATRIX &mProj, D3DXVECTOR3 &vEye, D3DXVECTOR3 &vPos )
{
	D3DXMATRIX mWorld;

	//ܰ�����ݽ̫��.
	//	����m�F����(�v�C��).
//	static float x = -1.0f;
	float fScale = 0.1f;
//	x += 0.001f;	//�������E�ֈړ�.

	D3DXMATRIX mScale, mTrans;
	//�g��E�k��.
	D3DXMatrixScaling( &mScale, fScale, fScale, fScale );
//	//���s�ړ�.
//	D3DXMatrixTranslation( &mTrans, x, 1.0f, 0.0f );
	D3DXMatrixTranslation( &mTrans, vPos.x, vPos.y, vPos.z );
	mWorld = mScale * mTrans;

	//�g�p���鼪��ނ̾��.
	m_pDeviceContext11->VSSetShader( m_pVertexShader,	NULL, 0 );	//���_�����.
	m_pDeviceContext11->GSSetShader( m_pGeometryShader,	NULL, 0 );	//�޵��ؼ����.
	m_pDeviceContext11->PSSetShader( m_pPixelShader,	NULL, 0 );	//�߸�ټ����.

	//����ނ̺ݽ����ޯ̧�Ɋe���ް���n��.
	D3D11_MAPPED_SUBRESOURCE pData;
	PSPRITESHADER_CONSTANT_BUFFER cb;
	if( SUCCEEDED( m_pDeviceContext11->Map(
		m_pConstantBuffer, 0,
		D3D11_MAP_WRITE_DISCARD, 0, &pData ) ) )
	{
		//ܰ���,�ޭ�,��ۼު���݂̍����s���n��.
		D3DXMATRIX m = mWorld * mView * mProj;
		D3DXMatrixTranspose( &m, &m );
		cb.mWVP = m;

		memcpy_s( pData.pData, pData.RowPitch,
			(void*)(&cb), sizeof( cb ) );
		m_pDeviceContext11->Unmap( m_pConstantBuffer, 0 );
	}

	//���̺ݽ����ޯ̧���ǂ̼���ނŎg����?.
	m_pDeviceContext11->VSSetConstantBuffers( 0, 1, &m_pConstantBuffer );
	m_pDeviceContext11->GSSetConstantBuffers( 0, 1, &m_pConstantBuffer );
	m_pDeviceContext11->PSSetConstantBuffers( 0, 1, &m_pConstantBuffer );

	//���_���߯�ڲ��Ă��.
	m_pDeviceContext11->IASetInputLayout( m_pVertexLayout );
	//����è�ށE���ۼް���.
	m_pDeviceContext11->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_POINTLIST );

	//ø����𼪰�ނɓn��.
	m_pDeviceContext11->PSSetSamplers(
		0, 1, &m_pSampleLinear );
	m_pDeviceContext11->PSSetShaderResources(
		0, 1, &m_pTexture );

	//���ߐݒ�.
	SetBlend( true );

	//����è�ނ������ݸ�.
	m_pDeviceContext11->Draw( 1, 0 );

	//����ޖ�����(�����).
	DetachShader();

	//���ߐݒ薳��.
	SetBlend( false );
}



//============================================================
//	����ޖ�����(�����).
//============================================================
void clsParticle::DetachShader()
{
	//�e����ނ����������.
	m_pDeviceContext11->VSSetShader( NULL, NULL, 0 );	//���_�����.
	m_pDeviceContext11->HSSetShader( NULL, NULL, 0 );	//�ټ����.

	//  �`�`�` ï�ڰ� �`�`�` (�㉺�̊Ԃ̏���).

	m_pDeviceContext11->DSSetShader( NULL, NULL, 0 );	//��Ҳݼ����.
	m_pDeviceContext11->GSSetShader( NULL, NULL, 0 );	//�޵��ؼ����.
//	m_pDeviceContext11->GSSetConstantBuffers( 0, 0, NULL );//�����Ă��Ȃ��Ă�.

	//  �`�`�` ׽�ײ�� �`�`�` (�㉺�̊Ԃ̏���).

	m_pDeviceContext11->PSSetShader( NULL, NULL, 0 );	//�߸�ټ����.

}

//============================================================
//	ø����Ǎ�&�쐬.
//============================================================
HRESULT clsParticle::InitTexture( char *pFileName )
{
	//ø����p����װ�쐬.
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory( &SamDesc,
		sizeof( D3D11_SAMPLER_DESC ) );
	SamDesc.Filter		= D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU	= D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV	= D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW	= D3D11_TEXTURE_ADDRESS_WRAP;

	if( FAILED( m_pDevice11->CreateSamplerState(
		&SamDesc, &m_pSampleLinear ) ) )
	{
		MessageBox( NULL, "����װ�쐬���s", "clsParticle::InitTexture", MB_OK );
		return E_FAIL;
	}

	//ø����̓Ǎ�.
	if( FAILED( D3DX11CreateShaderResourceViewFromFile(
		m_pDevice11, pFileName, NULL, NULL,
		&m_pTexture, NULL ) ) )
	{
		MessageBox( NULL, pFileName, "ø����Ǎ����s(clsParticle)", MB_OK );
		return E_FAIL;
	}


	return S_OK;
}


//============================================================
//�߰è�ق̈ړ�.
//============================================================
void clsParticle::Run()
{
	m_Frame ++;	//�ڰѶ���.

	//�߰è�ِ��J��Ԃ�.
	for( int i=0; i<m_iMaxParticle; i++ ){
		//�ڰѶ��Ă��J�n�ڰ�(�����)���傫��.
		if( m_Frame > m_pParticleArray[i].iBirthFrame ){
			//����x���x�ňړ�����l���Z�o.
			m_pParticleArray[i].vPos
				+= m_pParticleArray[i].vDir
					* m_pParticleArray[i].fSpeed;

//			//�d��.
//			m_pParticleArray[i].vDir
//				+= D3DXVECTOR3( 0.0f, -0.000098f, 0.0f );
//			//�n�ʂł��޳���.
//			if( m_pParticleArray[i].vPos.y < 0.0f ){
//				m_pParticleArray[i].vDir.y
//					= -m_pParticleArray[i].vDir.y;
//			}

			//���̍����܂ŏ㏸������.
			if( m_pParticleArray[i].vPos.y > 5.0f ){
				m_pParticleArray[i].vPos.y = 0.0f;
				m_pParticleArray[i].fSpeed = -0.2f;
			}
			//���̍����܂ŉ��~������.
			if( m_pParticleArray[i].vPos.y < 0.0f ){
				m_pParticleArray[i].vPos.y = 5.0f;
				m_pParticleArray[i].fSpeed = -0.2f;
			}

		}
	}

}

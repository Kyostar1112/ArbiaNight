#include "DebugText.h"

//�����̧�ٖ�(�߽���܂�).
const char SHADER_NAME[] = "Shader\\DebugText.hlsl";

//============================================================
//	�ݽ�׸�.
//============================================================
clsDebugText::clsDebugText()
{
	ZeroMemory( this, sizeof( clsDebugText ) );	//������.
	
	m_fScale = 1.0f;
}


//============================================================
//	�޽�׸�.
//============================================================
clsDebugText::~clsDebugText()
{

}


//============================================================
//	�������֐�.
//============================================================
HRESULT clsDebugText::Init( ID3D11DeviceContext* pContext,
							DWORD dwWidth, DWORD dwHeight,
							float fSize, D3DXVECTOR4 vColor )
{
	m_fAlpha = vColor.w;
	m_vColor = vColor;
	m_fScale = fSize / 25.0f;

	//95�������J��Ԃ�.
	for( int i=0; i<95; i++ ){
		m_fKerning[i] = 10.0f;
	}
	//���޲���÷�Ă��߰.
	m_pDeviceContext11 = pContext;
	m_pDeviceContext11->GetDevice( &m_pDevice11 );

	//window����.
	m_dwWindowWidth = dwWidth;
	m_dwWindowHeight= dwHeight;

	//̫�Ė��ɸ����(��`)�쐬.
	float left = 0.0f, top = 0.0f, right = 0.0f, bottom = 0.0f;
	int cnt = 0;
	for( int k=0; k<10; k++ ){
		for( int i=0; i<10; i++ ){
			left	= k * WDIMENSION;
			top		= i * DIMENSION;
			right	= left + m_fKerning[cnt];
			bottom	= top + DIMENSION;

			left	/= TEX_DIMENSION;
			top		/= TEX_DIMENSION;
			right	/= TEX_DIMENSION;
			bottom	/= TEX_DIMENSION;

			TextVertex vertices[] =
			{
				D3DXVECTOR3(	  0.0f,	DIMENSION, 0.0f ), D3DXVECTOR2( left, bottom ),		//���_1.
				D3DXVECTOR3(	  0.0f,		 0.0f, 0.0f ), D3DXVECTOR2( left, top ),		//���_2.
				D3DXVECTOR3( DIMENSION, DIMENSION, 0.0f ), D3DXVECTOR2( right, bottom ),	//���_3.
				D3DXVECTOR3( DIMENSION,		 0.0f, 0.0f ), D3DXVECTOR2( right, top )		//���_4.
			};
			D3D11_BUFFER_DESC bd;
			bd.Usage		= D3D11_USAGE_DEFAULT;
			bd.ByteWidth	= sizeof( TextVertex ) * 4;
			bd.BindFlags	= D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags=0;
			bd.MiscFlags	= 0;

			D3D11_SUBRESOURCE_DATA InitData;
			InitData.pSysMem = vertices;
			if( FAILED( m_pDevice11->CreateBuffer(
				&bd, &InitData, &m_pVertexBuffer[cnt]) ) )
			{
				MessageBox( NULL,
					"���_�ޯ̧�쐬���s(DebugText:Init)",
					"error", MB_OK );
				return E_FAIL;
			}
			cnt ++;
		}
	}

	//ø����p����׍쐬.
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory( &SamDesc, sizeof( D3D11_SAMPLER_DESC ) );
	//ø���̨���Ɠ\��t�����̎w��.
	SamDesc.Filter	= D3D11_FILTER_MIN_MAG_MIP_POINT;
	SamDesc.AddressU= D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV= D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW= D3D11_TEXTURE_ADDRESS_WRAP;
	if( FAILED( m_pDevice11->CreateSamplerState(
		&SamDesc, &m_pSampleLinear) ) )
	{
		MessageBox( NULL,
			"����ٍ쐬���s(DebugText:Init)",
			"", MB_OK );
		return E_FAIL;
	}

	//̫�Ă�ø����쐬.
	if( FAILED(
		D3DX11CreateShaderResourceViewFromFile(
			m_pDevice11,
			"Data\\DebugText\\ascii.png",
			NULL, NULL,
			&m_pAsciiTexture, NULL ) ) )
	{
		MessageBox( NULL,
			"̫��ø����쐬���s(DebugText:Init)",
			"error", MB_OK );
		return E_FAIL;
	}

//============================================================
	//hlsļ�ٓǍ�.
//============================================================
	ID3DBlob*	pCompileShader = NULL;
	ID3DBlob*	pErrors	= NULL;
	if( FAILED( D3DX11CompileFromFile(
		SHADER_NAME, NULL, NULL,
		"VS", "vs_5_0", 0, 0,
		NULL, &pCompileShader,
		&pErrors, NULL ) ) )
	{
		MessageBox( NULL, "hlsl�Ǎ����s(VS)", "DebugText:Init", MB_OK );
		return E_FAIL;
	}
	SAFE_RELEASE( pErrors );

	if( FAILED( m_pDevice11->CreateVertexShader(
		pCompileShader->GetBufferPointer(),
		pCompileShader->GetBufferSize(),
		NULL, &m_pVertexShader ) ) )
	{
		SAFE_RELEASE( pCompileShader );
		MessageBox( NULL, "�ްï���ޯ̧�쐬���s", "DebugText:Init", MB_OK );
		return E_FAIL;
	}

	//���_���߯�ڲ��Ă��`.
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
			0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,
			0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = sizeof( layout ) / sizeof( layout[0] );

	//���_���߯�ڲ��č쐬.
	if( FAILED( m_pDevice11->CreateInputLayout(
		layout, numElements,
		pCompileShader->GetBufferPointer(),
		pCompileShader->GetBufferSize(),
		&m_pVertexLayout ) ) )
	{
		MessageBox( NULL, "���_���߯�ڲ��č쐬", "DebugText:Init", MB_OK );
		return E_FAIL;
	}

	//�߸�ټ���ލ쐬.
	if( FAILED( D3DX11CompileFromFile(
		SHADER_NAME, NULL, NULL,
		"PS", "ps_5_0", 0, 0,
		NULL, &pCompileShader,
		&pErrors, NULL ) ) )
	{
		MessageBox( NULL, "hlsl�Ǎ����s(PS)", "DebugText:Init", MB_OK );
		return E_FAIL;
	}
	SAFE_RELEASE( pErrors );


	if( FAILED( m_pDevice11->CreatePixelShader(
		pCompileShader->GetBufferPointer(),
		pCompileShader->GetBufferSize(),
		NULL, &m_pPixelShader ) ) )
	{
		SAFE_RELEASE( pCompileShader );
		MessageBox( NULL, "�߸�ټ���ލ쐬���s", "DebugText:Init", MB_OK );
		return E_FAIL;
	}
	SAFE_RELEASE( pCompileShader );

	//�ݽ����ޯ̧�쐬.
	D3D11_BUFFER_DESC cb;
	cb.BindFlags	= D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth	= sizeof( TEXT_CONSTANT_BUFFER );
	cb.CPUAccessFlags=D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags	= 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if( FAILED(m_pDevice11->CreateBuffer(
		&cb, NULL, &m_pConstantBuffer ) ) )
	{
		MessageBox( NULL, "�ݽ����ޯ̧�쐬", "DebugText:Init", MB_OK );
		return E_FAIL;
	}




	return S_OK;
}


//============================================================
//	����(��̧������)�ݒ�̐؂�ւ�.
//============================================================
void clsDebugText::SetBlend( bool flg )
{
	//��̧�����ޗp�����޽ðč\����.
	//pnģ�ٓ��ɱ�̧��񂪂���̂ŁA
	//���߂���悤�������޽ðĂ�ݒ肷��.
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory( &blendDesc, sizeof( D3D11_BLEND_DESC ) );//������.

	blendDesc.IndependentBlendEnable
		= false;//false:RenderTarget[0]�����ް�݂̂��g�p����.
				//true :RenderTarget[0�`7]���g�p�ł���.
				//      (���ް���ޯĖ��ɓƗ����������ޏ���)
	blendDesc.AlphaToCoverageEnable
		= false;//true :��̧ĩ���گ�ނ��g�p����.
	blendDesc.RenderTarget[0].BlendEnable
		= flg;	//true :��̧�����ނ��g�p����.
	blendDesc.RenderTarget[0].SrcBlend	//���f�ނɑ΂���ݒ�.
		= D3D11_BLEND_SRC_ALPHA;		//	��̧�����ނ��w��.
	blendDesc.RenderTarget[0].DestBlend	//�d�˂�f�ނɑ΂���ݒ�.
		= D3D11_BLEND_INV_SRC_ALPHA;	//	��̧�����ނ̔��]���w��.

	blendDesc.RenderTarget[0].BlendOp	//�����޵�߼��.
		= D3D11_BLEND_OP_ADD;			//	ADD:���Z����.

	blendDesc.RenderTarget[0].SrcBlendAlpha	//���f�ނ̱�̧�ɑ΂���ݒ�.
		= D3D11_BLEND_ONE;					//	���̂܂܎g�p.
	blendDesc.RenderTarget[0].DestBlendAlpha//�d�˂�f�ނ̱�̧�ɑ΂���ݒ�.
		= D3D11_BLEND_ZERO;					//	�������Ȃ�.

	blendDesc.RenderTarget[0].BlendOpAlpha	//��̧�������޵�߼��.
		= D3D11_BLEND_OP_ADD;				//	ADD:���Z����.

	blendDesc.RenderTarget[0].RenderTargetWriteMask	//�߸�ٖ��̏�������Ͻ�.
		= D3D11_COLOR_WRITE_ENABLE_ALL;				//	�S�Ă̐���(RGBA)�ւ��ް��̊i�[��������.

	//�����޽ðč쐬.
	if( FAILED(
		m_pDevice11->CreateBlendState(
			&blendDesc, &m_pBlendState ) ) )
	{
		MessageBox( NULL, "�����޽ðč쐬���s", "�װ", MB_OK );
	}

	//�����޽ðĂ̐ݒ�.
	UINT mask = 0xffffffff;	//Ͻ��l.
	m_pDeviceContext11->OMSetBlendState(
		m_pBlendState, NULL, mask );

}


//============================================================
//	�����ݸފ֐�.
//============================================================
void clsDebugText::Render( char* text, int x, int y )
{
	//�ޭ���ݽ̫��.
	D3DXVECTOR3	vEye( 0.0f, 0.0f,-1.0f );
	D3DXVECTOR3	vLook(0.0f, 0.0f, 0.0f );
	D3DXVECTOR3	vUp(  0.0f, 1.0f, 0.0f );
	D3DXMatrixLookAtLH(
		&m_mView, &vEye, &vLook, &vUp );


#if 0
	//��ۼު������ݽ̫��(�Œ�).
	D3DMATRIX mOtho = {
		2.0f / (float)( m_dwWindowWidth ), 0.0f, 0.0f, 0.0f,
		0.0f, -2.0f / (float)( m_dwWindowHeight), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 1.0f
	};
#else
	D3DXMATRIX mOtho;
	D3DXMatrixIdentity( &mOtho );//�P�ʍs��.
	mOtho._11	= 2.0f / (float)( m_dwWindowWidth );
	mOtho._22	= -2.0f / (float)( m_dwWindowHeight );
	mOtho._41	= -1.0f;
	mOtho._42	= 1.0f;
#endif
	m_mProj = mOtho;

	//����è�ށE���ۼް.
	m_pDeviceContext11->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
	//���_���߯�ڲ��Ă��.
	m_pDeviceContext11->IASetInputLayout(
		m_pVertexLayout );

	//�g�p���鼪��ނ̓o�^.
	m_pDeviceContext11->VSSetShader(
		m_pVertexShader, NULL, 0 );
	m_pDeviceContext11->PSSetShader(
		m_pPixelShader, NULL, 0 );

	//���̺ݽ����ޯ̧���g������ނ̓o�^.
	m_pDeviceContext11->VSSetConstantBuffers(
		0, 1, &m_pConstantBuffer );
	m_pDeviceContext11->PSSetConstantBuffers(
		0, 1, &m_pConstantBuffer );

	//ø����𼪰�ނɓn��.
	m_pDeviceContext11->PSSetSamplers(
		0, 1, &m_pSampleLinear );
	m_pDeviceContext11->PSSetShaderResources(
		0, 1, &m_pAsciiTexture );


	SetBlend( true );
	//��������ٰ��.
	for( int i=0; i<strlen( text ); i++ ){
		char font = text[i];
		int index = font - 32;	//̫�Ĳ��ޯ���쐬.

		//̫�������ݸ�.
		RenderFont( index, x, y );

		x += m_fKerning[index];
	}
	SetBlend( false );



}


//============================================================
//̫�������ݸފ֐�.
//============================================================
void clsDebugText::RenderFont( int FontIndex, int x, int y )
{
	//ܰ��ޕϊ�.
	D3DXMATRIX mWorld;
	D3DXMatrixIdentity( &mWorld );
	D3DXMatrixTranslation(
		&mWorld, (float)x, (float)y,
		-100.0f );	//Z(-100)�Ŏ�O�\���\.

	//����ނ̺ݽ����ޯ̧�Ɋe���ް���n��.
	D3D11_MAPPED_SUBRESOURCE	pData;
	TEXT_CONSTANT_BUFFER		cb;
	if( SUCCEEDED( m_pDeviceContext11->Map(
		m_pConstantBuffer, 0,
		D3D11_MAP_WRITE_DISCARD, 0, &pData ) ) )
	{
		//ܰ���,�ޭ�,��ۼު���݂̍����s���n��.
		D3DXMATRIX m = mWorld * m_mView * m_mProj;
		D3DXMatrixTranspose( &m, &m );
		cb.mWVP = m;
		//�װ��n��.
		cb.vColor = m_vColor;
		//�����x��n��.
		cb.fAlpha.x = m_fAlpha;

		memcpy_s( pData.pData, pData.RowPitch,
			(void*)(&cb), sizeof(cb) );
		m_pDeviceContext11->Unmap(
			m_pConstantBuffer, 0 );
	}
	//�ްï���ޯ̧���.
	UINT stride = sizeof( TextVertex );
	UINT offset = 0;
	m_pDeviceContext11->IASetVertexBuffers(
		0, 1, &m_pVertexBuffer[FontIndex],
		&stride, &offset );

	//�`��.
	UINT ColoKey = 0xffffffff;
	m_pDeviceContext11->OMSetBlendState(
		m_pBlendState, NULL, ColoKey );
	m_pDeviceContext11->Draw( 4, 0 );
	m_pDeviceContext11->OMSetBlendState(
		0, NULL, ColoKey );


}
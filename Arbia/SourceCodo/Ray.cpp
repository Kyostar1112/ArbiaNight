#include "Ray.h"

//�����̧�ٖ�(�ިڸ�؂��܂�)(\\).
const char SHADER_NAME[] = "Shader\\Ray.hlsl";
//���ذ�߲�Ė�(�ިڸ�؂��܂�)(\\).
const char ENT_VER_NAME[] = "VS";
const char ENT_PIX_NAME[] = "PS";

clsRay::clsRay()
{
	ZeroMemory( this, sizeof( clsRay ) );
}

clsRay::~clsRay()
{
	SAFE_RELEASE( m_pVertexBuffer );
	SAFE_RELEASE( m_pConstantBuffer );
	SAFE_RELEASE( m_pPixelShader );
	SAFE_RELEASE( m_pVertexLayout );
	SAFE_RELEASE( m_pVertexShader );
}


//============================================================
//	������.
//============================================================
HRESULT clsRay::Init( ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11 )
{
	m_pDevice11 = pDevice11;
	m_pDeviceContext11 = pContext11;

	if( FAILED( InitShader() ) ){
		return E_FAIL;
	}
	if( FAILED( InitModel() ) ){
		return E_FAIL;
	}

	return S_OK;
}


//============================================================
//�`��.
//============================================================
void clsRay::Render( D3DXMATRIX& mView, D3DXMATRIX& mProj )
{
	//ܰ��ލs��.
	D3DXMATRIX	mWorld;

	//��]�s��A�ړ��s��.
	D3DXMATRIX mRot, mTran;

//��]�s��쐬(�ްсA�ð�ގ���).
D3DXMatrixRotationY( &mRot, m_Ray.fYaw );


	//���s�ړ��쐬.
	D3DXMatrixTranslation( &mTran,
		m_Ray.vPos.x, m_Ray.vPos.y, m_Ray.vPos.z );

	//ܰ��ލs��쐬.
	mWorld = mRot * mTran;

	//�g�p���鼪��ނ̓o�^.
	m_pDeviceContext11->VSSetShader( m_pVertexShader, NULL, 0 );
	m_pDeviceContext11->PSSetShader( m_pPixelShader,  NULL, 0 );


	//����ނ̺ݽ����ޯ̧�Ɋe���ް���n��.
	D3D11_MAPPED_SUBRESOURCE pData;
	SHADER_CONSTANT_BUFFER cd;	//�ݽ����ޯ̧.
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
		cd.vColor = D3DXVECTOR4 ( 1.0f, 0.0f, 1.0f, 1.0f );



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
	UINT stride = sizeof( MODEL_VERTEX );	//�ް��̊Ԋu.
	UINT offset = 0;
	m_pDeviceContext11->IASetVertexBuffers(
		0, 1, &m_pVertexBuffer, &stride, &offset );

	//���_���߯�ڲ��Ă��.
	m_pDeviceContext11->IASetInputLayout( m_pVertexLayout );

	//����è�ށE���ۼް���.
	m_pDeviceContext11->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_LINELIST );

	//����è�ނ������ݸ�.
	m_pDeviceContext11->Draw( 2, 0 );

}


//============================================================
//	HLSĻ�ق�ǂݍ��ݼ���ނ��쐬����.
//	HLSL:HIGE-LEVEL-SHADER-LANGUAGE.
//============================================================
HRESULT clsRay::InitShader()
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
			ENT_VER_NAME,		//����޴��ذ�߲�Ċ֐��̖��O.
			"vs_5_0",		//����ނ����ق��w�肷�镶����(���̧��).
			uCompileFlag,	//����޺��߲��׸�.
			0,				//�̪�ĺ��߲��׸�(���g�p).
			NULL,			//�گ������߲���̪���ւ��߲��(���g�p).
			&pCompiledShader,//����ނ��i�[������؂ւ��߲��.
			&pErrors,		//�װ�ƌx���ꗗ���i�[������؂ւ��߲��.
			NULL ) ) )		//�߂�l�ւ��߲��(���g�p).
	{
		MessageBox(NULL, "hlsl(vs)�ǂݍ��ݎ��s", "clsRay::InitShader", MB_OK );
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
		MessageBox( NULL, "vs�쐬���s", "clsRay::InitShader", MB_OK );
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
		MessageBox(NULL, "���_���߯�ڲ��č쐬���s", "clsRay::InitShader", MB_OK );
		return E_FAIL;
	}
	SAFE_RELEASE( pCompiledShader );



	//HLSL�����߸�ټ���ނ�����ނ��쐬.
	if( FAILED(
		D3DX11CompileFromFile(
			SHADER_NAME,	//�����̧�ٖ�(HLSĻ��).
			NULL,
			NULL,
			ENT_PIX_NAME,		//����޴��ذ�߲�Ċ֐��̖��O.
			"ps_5_0",		//����ނ����ق��w�肷�镶����(���̧��).
			uCompileFlag,	//����޺��߲��׸�.
			0,
			NULL,
			&pCompiledShader,//����ނ��i�[������؂ւ��߲��.
			&pErrors,
			NULL ) ) )
	{
		MessageBox( NULL, "hlsl(ps)�ǂݍ��ݎ��s", "clsRay::InitShader", MB_OK );
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
		MessageBox( NULL, "ps�쐬���s", "clsRay::InitShader", MB_OK );
		return E_FAIL;
	}
	SAFE_RELEASE( pCompiledShader );//����މ��.


	//�ݽ����ޯ̧(�萔)�ޯ̧�쐬�@����ނɓ���̐��l�𑗂��ޯ̧.
	//�����ł͕ϊ��s��n���p.
	//����ނ�World,View,Projection�s���n��.
	D3D11_BUFFER_DESC cb;
	cb.BindFlags	= D3D11_BIND_CONSTANT_BUFFER;;			//�ݽ��ޯ̧���w��.
	cb.ByteWidth	= sizeof( SHADER_CONSTANT_BUFFER );//�ݽ����ޯ̧�̻���.
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
		MessageBox( NULL, "�ݽ����ޯ̧�쐬���s", "clsRay::InitShader", MB_OK );
		return E_FAIL;
	}


	return S_OK;
}


//============================================================
//	ڲ������.
//============================================================
HRESULT clsRay::InitModel()
{
	//ڲ���ްï���ޯ̧�쐬.
	D3D11_BUFFER_DESC	bd;
	ZeroMemory( &bd, sizeof( bd ) );
	bd.Usage		= D3D11_USAGE_DEFAULT;
	bd.ByteWidth	= sizeof( MODEL_VERTEX ) * 2;//2�_��.
	bd.BindFlags	= D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags	= 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = m_Ray.vPoint;//ڲ�̍��W���.
	if( FAILED(
		m_pDevice11->CreateBuffer(
			&bd, &InitData, &m_pVertexBuffer ) ) )
	{
		ERR_MSG( "���_�ޯ̧�쐬���s", "clsRay::InitLine" );
		return E_FAIL;
	}


	return S_OK;
}




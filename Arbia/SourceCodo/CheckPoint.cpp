#include "CheckPoint.h"

const int iSTAY_TIME = 120;


const float fFLOAT_MAX = 0.25f * 0.25f * 0.25f;//�ő呬�x.
const float fACC = fFLOAT_MAX * fFLOAT_MAX * 2.0f;//�����x.

clsCheckPoint::clsCheckPoint()
{
	m_sFileName = nullptr;
}

clsCheckPoint::~clsCheckPoint()
{
}

//������.
HRESULT clsCheckPoint::Create( ID3D11Device* pDevice11,
	ID3D11DeviceContext* pContext11,
	LPSTR sFileName )
{
	m_pDevice11 = pDevice11;
	m_pDeviceContext11 = pContext11;
	m_sFileName = sFileName;

	//����ލ쐬.
	if( FAILED( InitShader() ) ){
		return E_FAIL;
	}
	//����غ�ݍ쐬.
	if( FAILED( InitModel() ) ){
		return E_FAIL;
	}

	Init();

	return S_OK;
}

////���ٍ쐬.
HRESULT clsCheckPoint::InitModel()
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
			m_sFileName,	//̧�ٖ�(�߽���K�v).
			NULL, NULL,
			&m_pTexture,	//(out)ø���.
			NULL ) ) )
	{
		MessageBox( NULL, "ø����쐬���s", "InitModel()", MB_OK );
		return E_FAIL;
	}


	return S_OK;
}


void clsCheckPoint::Init()
{
	m_bMobe = false;
	m_enMode = enM_AHEAD;
	m_iTimer = 0;
	m_fFloat = fFLOAT_MAX;
	m_bAcc = false;
}


bool clsCheckPoint::Stay()
{
	//�߂�l.
	bool bReturn = false;

	//�ҋ@.
	m_iTimer ++;
	if( m_iTimer > iSTAY_TIME ){
		m_enMode = enM_OUT;
		bReturn = true;
	}

	//�ӂ�ӂ�.
	if( m_bAcc ){
		m_fFloat += fACC; 
	}
	else{
		m_fFloat -= fACC;
	}

	//�I�[�o�[������.
	if( m_fFloat > fFLOAT_MAX ){
		m_fFloat = fFLOAT_MAX ;
		m_bAcc = false;
	}
	else if( m_fFloat < -fFLOAT_MAX ){
		m_fFloat = -fFLOAT_MAX ;
		m_bAcc = true;
	}

	m_vPos.y += m_fFloat;

	return bReturn;
}
#include "Sp2DJewel.h"


clsJewel::clsJewel()
{
	m_fScale = 1.0f;
}

clsJewel::~clsJewel()
{
}


//============================================================
//	���ٍ쐬.
//============================================================
HRESULT clsJewel::InitModel( SPRITE_STATE ss )
{
	float fW = ss.Disp.w;	//�\�����ײĕ�.
	float fH = ss.Disp.h;	//�\�����ײč���.
	float fU = (ss.Base.w / ss.Stride.w)/ss.Base.w;	//��ς�����̕�.
	float fV = (ss.Base.h / ss.Stride.h)/ss.Base.h;	//��ς�����̍���.
	
	//���S����ɂ��邽�߂�.
	fW /= 2.0f;
	fH /= 2.0f;

	//�����(�l�p�`)�̒��_���쐬.
	Sprite2DVertex vertices[] =
	{
		//���_���W(x,y,z).					//UV���W( u, v ).
		D3DXVECTOR3(-fW, fH, 0.0f ),	D3DXVECTOR2( 0.0f,	 fV ),	//���_1(����).
		D3DXVECTOR3(-fW,-fH, 0.0f ),	D3DXVECTOR2( 0.0f, 0.0f ),	//���_2(����).
		D3DXVECTOR3( fW, fH, 0.0f ),	D3DXVECTOR2(   fU,	 fV ),	//���_3(�E��).
		D3DXVECTOR3( fW,-fH, 0.0f ),	D3DXVECTOR2(   fU, 0.0f )	//���_4(�E��).
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
		MessageBox( NULL, "����׍쐬���s", "clsJewel::InitModel", MB_OK );
		return E_FAIL;
	}



	return S_OK;
}


//============================================================
//�`��(�����ݸ�)(��DX9MESH����Main����2���݂���̂Œ���).
//============================================================
void clsJewel::Render()
{
	//ܰ��ލs��.
	D3DXMATRIX	mWorld;
	//ܰ��ޕϊ�(�\���ʒu��ݒ肷��).
	D3DXMatrixIdentity( &mWorld );	//������:�P�ʍs��쐬.

	//�g�k.
	D3DXMATRIX mScale;
	D3DXMatrixIdentity( &mScale );	//������:�P�ʍs��쐬.
	D3DXMatrixScaling( &mScale, m_fScale, m_fScale, m_fScale );

	//���s�ړ�.
	D3DXMATRIX mTrans;
	D3DXMatrixIdentity( &mTrans );	//������:�P�ʍs��쐬.
	D3DXMatrixTranslation( &mTrans,
		m_vPos.x, m_vPos.y, m_vPos.z );

	//�g�p���鼪��ނ̓o�^.
	m_pDeviceContext11->VSSetShader( m_pVertexShader, NULL, 0 );
	m_pDeviceContext11->PSSetShader( m_pPixelShader,  NULL, 0 );


	//Matrix���Z.
	mWorld = mScale * mTrans;

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


void clsJewel::UpDateSpriteSs()
{
	SPRITE_STATE ss = m_SState;
	float fW = ss.Disp.w;	//�\�����ײĕ�.
	float fH = ss.Disp.h;	//�\�����ײč���.
	float fU = (ss.Base.w / ss.Stride.w)/ss.Base.w;	//��ς�����̕�.
	float fV = (ss.Base.h / ss.Stride.h)/ss.Base.h;	//��ς�����̍���.

	//���S����ɂ��邽�߂�.
	fW /= 2.0f;
	fH /= 2.0f;

	//�����(�l�p�`)�̒��_���쐬.
	Sprite2DVertex vertices[] =
	{
		//���_���W(x,y,z).					//UV���W( u, v ).
		D3DXVECTOR3(-fW, fH, 0.0f ),	D3DXVECTOR2( 0.0f,	 fV ),	//���_1(����).
		D3DXVECTOR3(-fW,-fH, 0.0f ),	D3DXVECTOR2( 0.0f, 0.0f ),	//���_2(����).
		D3DXVECTOR3( fW, fH, 0.0f ),	D3DXVECTOR2(   fU,	 fV ),	//���_3(�E��).
		D3DXVECTOR3( fW,-fH, 0.0f ),	D3DXVECTOR2(   fU, 0.0f )	//���_4(�E��).
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
		MessageBox( NULL, "���_�ޯ̧�쐬���s,", "clsJewel::UpDateSpriteSs", MB_OK );
	}
}

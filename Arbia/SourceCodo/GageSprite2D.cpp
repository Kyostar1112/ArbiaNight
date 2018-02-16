#include "GageSprite2D.h"

//�����̧�ٖ�(�ިڸ�؂��܂�)
const char SHADER_NAME[] = "Shader\\Sprite2D.hlsl";

//�ݽ�׸�.
clsGageSprite2D::clsGageSprite2D()
{
	ZeroMemory(this, sizeof(clsGageSprite2D));
	//��̧�l�̐ݒ�.
	m_fAlpha = 1.0f;//0:����_1:�s����.
}

//�޽�׸�.
clsGageSprite2D::~clsGageSprite2D()
{
}

//������.
HRESULT clsGageSprite2D::Init(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11, LPSTR FileName, GAGE_SPRITE_STATE ss)
{
	m_pDevice11 = pDevice11;
	m_pDeviceContext11 = pContext11;

	m_GSState = ss;

	if (FAILED(InitShader()))
	{
		return E_FAIL;
	}
	if (FAILED(InitModel(ss)))
	{
		return E_FAIL;
	}
	if (FAILED(CreateTexture(FileName, &m_pTexture)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//======================================
//	HLSĻ�ق�ǂݍ��ݼ���ނ��쐬����.
//	HLSL:HIGH-LEVEL-SHADER-LANGUAGE.
//======================================
HRESULT clsGageSprite2D::InitShader()
{
	ID3DBlob* pCompiledShader = NULL;
	ID3DBlob* pErrors = NULL;
	UINT uCompileFlag = 0;

#ifdef _DEBUG
	uCompileFlag
		= D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#endif//#ifdef _DEBUG

	//HLSL�����ްï������ނ�����ނ��쐬.
	if (FAILED(
		D3DX11CompileFromFile(
		SHADER_NAME,		//�����̧�ٖ�(HLSĻ��)
		NULL,				//ϸے�`�̔z��ւ��߲��(���g�p)
		NULL,				//�ݸٰ��̧�ق���������̪���ւ��߲��(���g�p)
		"VS_Main",			//����޴��ذ�߲�Ċ֐��̖��O.
		"vs_5_0",			//����ނ����ق��w�肷�镶����(���̧��)
		uCompileFlag,		//����޺��߲��׸�.
		0,					//�̪�ĺ��߲��׸�(���g�p)
		NULL,				//�گ������߲���̪���ւ��߲��(���g�p)
		&pCompiledShader,	//����ނ��i�[������؂ւ��߲��.
		&pErrors,			//�װ�ƌx���ꗗ���i�[������؂ւ��߲��.
		NULL)))				//�߂�l�ւ��߲��(���g�p)
	{
		MessageBox(NULL, "hlsl�Ǎ����s", "�װ", MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);

	//��L�ō쐬��������ނ���u�ްï������ށv���쐬.
	if (FAILED(
		m_pDevice11->CreateVertexShader(
		pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(),
		NULL,
		&m_pVertexShader)))//(out)�ްï�������.
	{
		MessageBox(NULL, "vs�쐬���s", "�װ", MB_OK);
		return E_FAIL;
	}

	//���_���߯�ڲ��Ă��`.
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{
			"POSITION",					//�ʒu.
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,//DXGI��̫�ϯ�(32bit float�^*3)
			0,
			0,							//�ް��̊J�n�ʒu.
			D3D11_INPUT_PER_VERTEX_DATA, 0
		},
		{
			"TEXCOORD",					//ø����ʒu.
			0,
			DXGI_FORMAT_R32G32_FLOAT,	//DXGI��̫�ϯ�(32bit float�^*2)
			0,
			12,							//ø����ް��̊J�n�ʒu.
			D3D11_INPUT_PER_VERTEX_DATA, 0
		}
	};
	//���_���߯�ڲ��Ă̔z��v�f�����Z�o.
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	//���_���߯�ڲ��Ă̍쐬.
	if (FAILED(
		m_pDevice11->CreateInputLayout(
		layout,
		numElements,
		pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(),
		&m_pVertexLayout)))//(out)���_���߯�ڲ���.
	{
		MessageBox(NULL, "���_���߯�ڲ��č쐬���s", "�װ", MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);


	//HLSL�����߸�ټ���ނ�����ނ��쐬.
	if (FAILED(
		D3DX11CompileFromFile(
		SHADER_NAME,	//�����̧�ٖ�(HLSĻ��)
		NULL, NULL,
		"PS_Main",		//����޴��ذ�߲�Ċ֐��̖��O.
		"ps_5_0",		//����ނ����ق��w�肷�镶����(���̧��)
		uCompileFlag,	//����޺��߲��׸�.
		0, NULL,
		&pCompiledShader,//����ނ��i�[������؂ւ��߲��.
		&pErrors,
		NULL)))
	{
		MessageBox(NULL, "hlsl(ps)�Ǎ����s", "�װ", MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);

	//��L�ō쐬��������ނ���u�߸�ټ���ށv���쐬.
	if (FAILED(
		m_pDevice11->CreatePixelShader(
		pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(),
		NULL,
		&m_pPixelShader)))//(out)�߸�ټ����.
	{
		MessageBox(NULL, "ps�쐬���s", "�װ", MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);//����މ��.

	//�ݽ���(�萔)�ޯ̧�쐬 ����ނɓ���̐��l�𑗂��ޯ̧.
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		//�ݽ����ޯ̧���w��.
	cb.ByteWidth = sizeof(SPRITE_CONSTANT_BUFFER);	//�ݽ����ޯ̧�̻���.
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;		//�������݂ű���.
	cb.MiscFlags = 0;				//���̑����׸�(���g�p).
	cb.StructureByteStride = 0;		//�\���̻̂���(���g�p).
	cb.Usage = D3D11_USAGE_DYNAMIC;	//�g�p���@:���ڏ�������.

	//�ݽ����ޯ̧�쐬.
	if (FAILED(
		m_pDevice11->CreateBuffer(
		&cb,
		NULL,
		&m_pConstantBuffer)))
	{
		MessageBox(NULL, "�ݽ����ޯ̧�쐬���s", "�װ", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

//================================================
//	���ٍ쐬.
//================================================
HRESULT clsGageSprite2D::InitModel(GAGE_SPRITE_STATE ss)
{
	float fW = ss.Disp.w;	//�\�����ײĕ�.
	float fH = ss.Disp.h;	//�\�����ײč���.
	float fU = ss.Stride.w / ss.Disp.w;	//1�ς�����̕�.
	float fV = ss.Stride.h / ss.Disp.h;	//1�ς�����̍���.
	
	//�����(�l�p�`)�̒��_���쐬.
	SpriteVertex vertices[] =
	{
		//���_���W(x,y,z)_______________/ UV���W(u,v).
		D3DXVECTOR3(0.0f, fH, 0.0f), D3DXVECTOR2(0.0f, fV),			//���_1 : ����.
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	D3DXVECTOR2(0.0f, 0.0f),	//���_2 : ����.
		D3DXVECTOR3(fW, fH, 0.0f), D3DXVECTOR2(fU,fV),				//���_3 : �E��.
		D3DXVECTOR3(fW, 0.0f, 0.0f), D3DXVECTOR2(fU, 0.0f)			//���_4 : �E��.
	};
	//�ő�v�f�����Z�o����.
	UINT uVerMax = sizeof(vertices) / sizeof(vertices[0]);

	//�ޯ̧�\����.
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;					//�g�p��(��̫��).
	bd.ByteWidth = sizeof(SpriteVertex) * uVerMax;	//���_����(���_�~4).
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;		//���_�ޯ̧�Ƃ��Ĉ���.
	bd.CPUAccessFlags = 0;		//CPU����ͱ������Ȃ�.
	bd.MiscFlags = 0;			//���̑����׸�(���g�p).
	bd.StructureByteStride = 0;	//�\���̻̂���(���g�p).

	//���ؿ���ް��\����.
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;//����؂̒��_���.

	//���_�ޯ̧�̍쐬.
	if (FAILED(m_pDevice11->CreateBuffer(&bd, &InitData, &m_pVertexBuffer)))
	{
		MessageBox(NULL, "���_�ޯ̧�쐬���s", "�װ", MB_OK);
		return E_FAIL;
	}

	//���_�ޯ̧���.
	UINT stride = sizeof(SpriteVertex);//�ް��Ԋu.
	UINT offset = 0;
	m_pDeviceContext11->IASetVertexBuffers(0, 1,&m_pVertexBuffer, &stride, &offset);

	//ø����p�̻���װ�\����.
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(SamDesc));
	//�Ʊ̨��-(���`���)
	//	POINT:���������e��.
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	//ׯ��ݸ�Ӱ��.
	//	WRAP   : �J��Ԃ�
	//	MIRROR : ���]�J��Ԃ�.
	//	CLAMP  : �[�̖͗l�������L�΂�.
	//	BORDER : �ʓr���E�F�����߂�.
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	//����װ�쐬.
	if (FAILED(m_pDevice11->CreateSamplerState(&SamDesc, &m_pSampleLinear)))//(out)����װ.
	{
		MessageBox(NULL, "����׍쐬���s", "�װ", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

//ø����쐬.
HRESULT clsGageSprite2D::CreateTexture(LPSTR FileName, ID3D11ShaderResourceView** pTex)
{
	//ø����쐬.
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(
		m_pDevice11,//ؿ�����g�p�������޲��ւ��߲��.
		FileName,	//̧�ٖ�.
		NULL, NULL,
		pTex,		//(out)ø���.
		NULL)))
	{
		ERR_MSG("clsGageSprite2D::CreateTexture()", "�װ");
		return E_FAIL;
	}

	return S_OK;
}

//����غ�݂���ʂ������ݸ�.
void clsGageSprite2D::Render()
{
	//ܰ��ލs��.
	D3DXMATRIX	mWorld;

	//ܰ��ޕϊ�(�\���ʒu��ݒ肷��)
	D3DXMatrixIdentity(&mWorld);	//������:�P�ʍs��쐬.

	//���s�ړ�.
	D3DXMatrixTranslation(&mWorld, m_vPos.x, m_vPos.y, m_vPos.z);

	//�g�p���鼪��ނ̓o�^.
	m_pDeviceContext11->VSSetShader(m_pVertexShader, NULL, 0);
	m_pDeviceContext11->PSSetShader(m_pPixelShader, NULL, 0);

	//����ނ̺ݽ����ޯ̧�Ɋe���ް���n��.
	D3D11_MAPPED_SUBRESOURCE pData;
	SPRITE_CONSTANT_BUFFER cd;	//�ݽ����ޯ̧.
	//�ޯ̧�����ް��̏������J�n����map.
	if (SUCCEEDED(m_pDeviceContext11->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//ܰ��ލs���n��.
		D3DXMATRIX m = mWorld;
		D3DXMatrixTranspose(&m, &m);	//�s���]�u����.					
		//�s��̌v�Z���@��DirectX��GPU�ňقȂ��.
		cd.mW = m;

		//�ޭ��߰Ă̕��A������n��.
		cd.fViewPortWidth = WND_W;
		cd.fViewPortHeight = WND_H;

		//��̧�l��n��.
		cd.fAlpha = m_fAlpha;

		//UV���W��n��.
		cd.vUV.x = m_fUVStart.w;
		cd.vUV.y = m_fUVStart.h;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cd), sizeof(cd));

		m_pDeviceContext11->Unmap(m_pConstantBuffer, 0);
	}

	//���̺ݽ����ޯ̧���ǂ̼���ނŎg�����H.
	m_pDeviceContext11->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pDeviceContext11->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	//���_�ޯ̧���.
	UINT stride = sizeof(SpriteVertex);
	UINT offset = 0;
	m_pDeviceContext11->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	//���_���߯�ڲ��Ă��.
	m_pDeviceContext11->IASetInputLayout(m_pVertexLayout);

	//����è�ށE���ۼް���.
	m_pDeviceContext11->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ø����𼪰�ނɓn��.
	m_pDeviceContext11->PSSetSamplers(0, 1, &m_pSampleLinear);	//�����-���.
	m_pDeviceContext11->PSSetShaderResources(0, 1, &m_pTexture);//ø����𼪰�ނɓn��.

	//��̧�����ޗp�����޽ðč쐬���ݒ�.
	SetBlend(true);

	//����è�ނ������ݸ�.
	m_pDeviceContext11->Draw(4, 0);

	//��̧�����ނ𖳌��ɂ���.
	SetBlend(false);
}
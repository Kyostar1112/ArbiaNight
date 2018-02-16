#ifndef _DEBUG_TEXT_H_
#define _DEBUG_TEXT_H_

//�x���ɂ��Ă̺��ޕ��͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning( disable:4005 )	

//============================================================
//	�ݸٰ��.
//============================================================
#include	<Windows.h>

#include	<D3DX11.h>
#include	<D3D11.h>

#include	<D3DX10.h>//�uD3DX�`�v�̒�`�g�p���ɕK�v.
#include	<D3D10.h>

#include	"MyMacro.h"


//============================================================
//	ײ����.
//============================================================
#pragma comment( lib, "winmm.lib" )

#pragma comment( lib, "d3dx11.lib" )
#pragma comment( lib, "d3d11.lib" )

#pragma comment( lib, "d3dx10.lib" )//�uD3DX�`�v�̒�`�g�p���ɕK�v.


//============================================================
//	�萔.
//============================================================
#define DIMENSION		(12.0f)
#define WDIMENSION		(10.0f)
#define TEX_DIMENSION	(128.0f)


//�\����.
struct  TEXT_CONSTANT_BUFFER
{
	D3DXMATRIX	mWVP;
	D3DXVECTOR4	vColor;
	D3DXVECTOR4	fAlpha;
};

//÷�Ă̈ʒu���.
struct TextVertex
{
	D3DXVECTOR3	Pos;	//�ʒu.
	D3DXVECTOR2	Tex;	//ø������W.
};


//÷�ĸ׽.
class clsDebugText
{
private:
	//�����؂Ɉ��.
	ID3D11Device*			m_pDevice11;		//���޲���޼ު��.
	ID3D11DeviceContext*	m_pDeviceContext11;	//���޲���÷��.

	//�����ق̎�ނ��Ƃɗp��.
	ID3D11VertexShader*		m_pVertexShader;	//���_�����.
	ID3D11InputLayout*		m_pVertexLayout;	//���_ڲ���.
	ID3D11PixelShader*		m_pPixelShader;		//�߸�ټ����.
	ID3D11Buffer*			m_pConstantBuffer;	//�ݽ����ޯ̧.

	//�����ق��Ƃɗp��.
	ID3D11Buffer*			m_pVertexBuffer[100];	//���_�ޯ̧(100��).

	ID3D11ShaderResourceView*	m_pAsciiTexture;//����ø���.
	ID3D11SamplerState*			m_pSampleLinear;//ø����̻���װ:/ø����Ɋe��̨����������.

	ID3D11BlendState*			m_pBlendState;	//�����޽ð�.


	DWORD	m_dwWindowWidth;	//����޳��.
	DWORD	m_dwWindowHeight;	//����޳����.

	float	m_fKerning[100];	//���ݸ�(100��).
	float	m_fScale;			//�g�k�n(25pixel��� 25pixel=1.0f).
	float	m_fAlpha;			//���ߒl.
	D3DXVECTOR4	m_vColor;	/*(^��^)*/	//�F.

	D3DXMATRIX m_mView;	//�ޭ��s��.
	D3DXMATRIX m_mProj;	//��ۼު���ݍs��.
	



public:
	clsDebugText();	//�ݽ�׸�.
	~clsDebugText();//�޽�׸�.

	HRESULT Init( ID3D11DeviceContext* pContext,
		DWORD dwWidth, DWORD dwHeight,
		float fSize, D3DXVECTOR4 vColor );



	//����(��̧������)�ݒ�̐؂�ւ�.
	void SetBlend( bool flg );

	//�����ݸފ֐�.
	void Render( char* text, int x, int y );

	//̫�������ݸފ֐�.
	void RenderFont( int FontIndex, int x, int y );


};


#endif//#define _DEBUG_TEXT_H_
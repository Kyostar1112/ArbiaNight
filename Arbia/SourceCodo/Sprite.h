#ifndef _SPRITE_H_
#define _SPRITE_H_

//�x���ɂ��Ă̺��ޕ��͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning( disable:4005 )	

//============================================================
//	�ݸٰ��.
//============================================================
#include "Common.h"//���ʸ׽.


//============================================================
//	ײ����.
//============================================================



//============================================================
//	�萔.
//============================================================


//============================================================
//	�\����.
//============================================================
//�ݽ����ޯ̧�̱��ؑ��̒�`(Simple.hlsl).
//����ޓ��̺ݽ����ޯ̧�ƈ�v���Ă���K�v����.
struct SPRITESHADER_CONSTANT_BUFFER
{
	D3DXMATRIX	mWVP;		//ܰ���,�ޭ�,�ˉe�̍����ϊ��s��.
	D3DXVECTOR4	vColor;		//�װ(RGBA�̌^�ɍ��킹��) : ø����̏ォ��F���ڂ���(�Ԃ��ۂ��������邽�߂Ƃ�).
	D3DXVECTOR4	vUV;		//UV���W.
};

////���_�̍\����.
//struct SpriteVertex
//{
//	D3DXVECTOR3 vPos;	//���_���W(x,y,z).
//	D3DXVECTOR2 vTex;	//ø������W.
//};




//============================================================
//	���ײĸ׽.
//============================================================
class clsSprite
	: public clsCommon
{
public:

	D3DXVECTOR3		m_vPos;	//�ʒu.

	int		m_AnimCount;//UV��۰�.

	bool	m_bDispFlg;//�\���׸�.


	clsSprite();	//�ݽ�׸�.
	virtual ~clsSprite();	//�޽�׸�.

	//������.
	HRESULT Init( ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11 );

	//����ލ쐬.
	HRESULT InitShader();
	////���ٍ쐬.
	virtual HRESULT InitModel();

	//�`��(�����ݸ�)(��DX9MESH����Main����2���݂���̂Œ���).
	virtual void Render( D3DXMATRIX& mView, D3DXMATRIX& mProj,
				 D3DXVECTOR3 &vEye );

	void SetScale( float fScale ){
		m_fScale = fScale;
	}

protected:

	//�����ق̎�ނ��Ƃɗp��.
	ID3D11VertexShader*		m_pVertexShader;	//���_�����.
	ID3D11InputLayout*		m_pVertexLayout;	//���_ڲ���.
	ID3D11PixelShader*		m_pPixelShader;		//�߸�ټ����.
	ID3D11Buffer*			m_pConstantBuffer;	//�ݽ����ޯ̧.

	//�����ق��Ƃɗp��.
	ID3D11Buffer*			m_pVertexBuffer;	//���_�ޯ̧.

	ID3D11ShaderResourceView*	m_pTexture;		//ø���.
	ID3D11SamplerState*			m_pSampleLinear;//ø����̻���װ:/ø����Ɋe��̨����������.



	float m_fScale;


};


#endif	//#ifndef _SPRITE_H_

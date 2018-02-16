#ifndef _C_GAGESPRITE_2D_H_
#define _C_GAGESPRITE_2D_H_

//�x���ɂ��Ă̺��ޕ��͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning( disable:4005 )

#include "Common.h"//���ʸ׽.

#define ALIGN16 _declspec(align(16))

//========================================================
//	�\����.
//========================================================
//�ݽ����ޯ̧�̱��ؑ��̒�`(Sprite2D.hlsl)
//������ޓ��̺ݽ����ޯ̧�ƈ�v���Ă���K�v����.
struct SPRITE_CONSTANT_BUFFER
{
	ALIGN16 D3DXMATRIX	mW;				//ܰ��ލs��.
	ALIGN16 float		fViewPortWidth;	//�ޭ��߰ĕ�.
	ALIGN16 float		fViewPortHeight;//�ޭ��߰č���.
	ALIGN16 float		fAlpha;			//��̧�l(���߂Ŏg�p).
	ALIGN16 D3DXVECTOR2	vUV;			//UV���W.
};
//���ײč\����.
struct GAGE_SPRITE_STATE
{
	WHSIZE_FLOAT	Disp;	//�\��������.
	WHSIZE_FLOAT	Stride;	//1�ς�����̕�����.
};

/*************************************************
*	Sprite2D�׽.
**/
class clsGageSprite2D : public clsCommon //���ʸ׽���p��.
{
public:

	clsGageSprite2D();	//�ݽ�׸�.
	~clsGageSprite2D();	//�޽�׸�.
	//������.
	HRESULT Init(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11, LPSTR FileName, GAGE_SPRITE_STATE ss);

	//����ލ쐬.
	HRESULT InitShader();
	//���ٍ쐬.
	HRESULT InitModel(GAGE_SPRITE_STATE ss);
	//ø����쐬.
	HRESULT CreateTexture(LPSTR FileName, ID3D11ShaderResourceView** pTex);

	//�`��(�����ݸ�)
	void Render();

	void SetPos( D3DXVECTOR3 Pos )
	{
		m_vPos = Pos;
	}
	
	void SetAlpha( float Alpha )
	{
		m_fAlpha = Alpha;
	}

	//���̃p�^�[��.
	void SetPatarnU( float Patarn )
	{
		m_fUVStart.w = Patarn;
	}

	//�c�̃p�^�[��.
	void SetPatarnV( float Patarn )
	{
		m_fUVStart.h = Patarn;
	}

private:

	D3DXVECTOR3		m_vPos;			//�ʒu.

	float			m_fAlpha;		//��̧�l.

	GAGE_SPRITE_STATE	m_GSState;	//���ײď��.
	WHSIZE_FLOAT		m_fUVStart;	//���摜���Ŕ͈͎w����J�n����ʒu.

	//�����ق̎�ނ��Ƃɗp��.
	ID3D11VertexShader*		m_pVertexShader;//���_�����.
	ID3D11InputLayout*		m_pVertexLayout;//���_ڲ���.
	ID3D11PixelShader*		m_pPixelShader;	//�߸�ټ����.
	ID3D11Buffer*			m_pConstantBuffer;//�ݽ����ޯ̧.

	//�����ق��Ƃɗp��.
	ID3D11Buffer*			m_pVertexBuffer;//���_�ޯ̧.

	ID3D11ShaderResourceView*	m_pTexture;//ø���.
	ID3D11SamplerState*			m_pSampleLinear;//ø����̻����-:ø����[�Ɋe��̨����������.

};

#endif//#ifndef _C_GAGESPRITE_2D_H_
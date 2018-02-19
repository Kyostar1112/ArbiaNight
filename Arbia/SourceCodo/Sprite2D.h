#ifndef _SPRITE_2D_H_
#define _SPRITE_2D_H_

//�x���ɂ��Ă̺��ޕ��͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning( disable:4005 )

using namespace std;

//============================================================
//	�ݸٰ��.
//============================================================
#include "Common.h"//���ʸ׽.
#include <memory>
#include <string>
#include <d3dx9tex.h>
#define ALIGN16 _declspec( align( 16 ) )


//============================================================
//	�\����.
//============================================================
//�ݽ����ޯ̧�̱��ؑ��̒�`(Sprite2D.hlsl).
//����ޓ��̺ݽ����ޯ̧�ƈ�v���Ă���K�v����.
struct SPRITE2D_CONSTANT_BUFFER
{
	ALIGN16 D3DXMATRIX	mW;				//ܰ��ލs��.
	ALIGN16 float		fViewPortWidth;	//�ޭ��߰ĕ�.
	ALIGN16 float		fViewPortHeight;//�ޭ��߰č���.
	ALIGN16 float		fAlpha;			//��̧�l(����).
	ALIGN16 D3DXVECTOR2 vUV;			//UV���W.
};
//���_�̍\����.
struct Sprite2DVertex
{
	D3DXVECTOR3	vPos;	//�ʒu.
	D3DXVECTOR2	vTex;	//ø������W.
};
//////���ײč\����.
//struct SPRITE_STATE
//{
//	WHSIZE_FLOAT	Disp;	//�\��������.
//	WHSIZE_FLOAT	Base;	//���摜����.
//	WHSIZE_FLOAT	Stride;	//��R�}������̍���.
//};//m_SState.
//���ײč\����.
struct SPRITE_STATE
{
	WHSIZE_FLOAT	Disp;	//�\��������.
	WHSIZE_FLOAT	Base;	//���摜����.
	//WHSIZE_FLOAT	Stride;	//��R�}������̍���.
	WHSIZE_FLOAT	Stride;	//�R�}�̐�.
};//m_SState.
enum en_BlackMode
{
	Idle = 0,
	In,
	Change,
	Out,
};


//============================================================
//	���ײ�2D�׽.
//============================================================
class clsSprite2D
	: public clsCommon
{

public:
	clsSprite2D();	//�ݽ�׸�.
	virtual ~clsSprite2D();	//�޽�׸�.

	//������.
	HRESULT Create( ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11,
		LPSTR fileName,
		float SetStrideW = 1.0f,
		float SetStrideH = 1.0f);

	//�X�v���C�g����ʊO��.
	void Init()
	{
		m_vPos = D3DXVECTOR3( WND_W, WND_H, 0.0f );
	}

	void SetPos( D3DXVECTOR3 Pos )
	{
		m_vPos = Pos;
	}

	void AddPosX( float Add )
	{
		m_vPos.x += Add;
	}

	void AddPosY( float Add )
	{
		m_vPos.y += Add;
	}

	void AddPosZ( float Add )
	{
		m_vPos.z += Add;
	}

	void SetPosX( float PosX )
	{
		m_vPos.x = PosX;
	}

	void SetPosY( float PosY )
	{
		m_vPos.y = PosY;
	}

	void SetPosZ( float PosZ )
	{
		m_vPos.z = PosZ;
	}

	void SetPos( float x, float y, float z = 0.0f )
	{
		m_vPos.x = x;
		m_vPos.y = y;
		m_vPos.z = z;
	}

	void SetAlpha( float Alpha )
	{
		m_fAlpha = Alpha;
	}

	void AddAlpha( float Alpha )
	{
		m_fAlpha += Alpha;
	}

	//���̃p�^�[��.
	void SetPatarnU( float Patarn )
	{
		m_fPatternNo.x = Patarn;
	}

	//�c�̃p�^�[��.
	void SetPatarnV( float Patarn )
	{
		m_fPatternNo.y = Patarn;
	}

	void SetSs(SPRITE_STATE ss)
	{
		m_SState = ss;
	}

	//SPRITE_STATE�ɃZ�b�g.
	void SetSs(
		float BaseW,			//���摜����.
		float BaseH,		    //���摜��.
		float DispW = -1,	    //�\������.//��������ĂȂ�������Base�ɍ��킹��.
		float DispH = -1       //�\����.//��������ĂȂ�������Base�ɍ��킹��.
		)
	{
		m_SState.Base.h		= BaseH;		//���摜����.
		m_SState.Base.w		= BaseW;		//���摜��.
		if (DispH < 0)
		{
			m_SState.Disp.h = m_SState.Base.h;
		}
		else
		{
			m_SState.Disp.h		= DispH;		//�\������.
		}
		if (DispW < 0)
		{
			m_SState.Disp.w		= m_SState.Base.w;	//�\����.
		}
		else
		{
			m_SState.Disp.w		= DispW;		//�\����.
		}
	}

	void SetDispH( float DispH )
	{
		m_SState.Disp.h = DispH;
	}

	void SetDispW( float DispW )
	{
		m_SState.Disp.w = DispW;
	}

	void AddDispH( float DispH )
	{
		m_SState.Disp.h += DispH;
	}

	void AddDispW( float DispW )
	{
		m_SState.Disp.w += DispW;
	}

	void MulDisp( float Disp )
	{
		MulPoint = Disp;
		m_SState.Disp.w = MulPoint * m_SState.Base.w;
		m_SState.Disp.h = MulPoint * m_SState.Base.h;
	}

	float GetAlpha()
	{
		return m_fAlpha;
	}

	SPRITE_STATE GetSs()
	{
		return m_SState;
	}

	WHSIZE_FLOAT GetCenterDisp()
	{
		WHSIZE_FLOAT tmp;
		tmp.w = m_SState.Disp.w/2;
		tmp.h = m_SState.Disp.h/2;
		return tmp;
	}

	D3DXVECTOR3 GetPos()
	{
		return m_vPos;
	}

	//�_�ŗp.
	void Flashing( float ChaAmo );

	//�`��(�����ݸ�)(��DX9MESH����Main����2���݂���̂Œ���).
	virtual void Render();
	en_BlackMode m_BlackMode;

	bool Release();


protected:

	//����ލ쐬.
	HRESULT InitShader();
	////���ٍ쐬.
	virtual HRESULT InitModel( SPRITE_STATE ss );
	//ø����쐬.
	HRESULT CreateTexture( LPSTR fileName,
		ID3D11ShaderResourceView** pTex );


	bool			m_bFlashing;

	float			MulPoint = 1.0f;//�|���Z�p�̕ϐ�.

	string			m_sFileName;

	D3DXVECTOR3		m_vPos;	//�ʒu.

	int				m_AnimCount;//UV��۰�.

	bool			m_bDispFlg;//�\���׸�.

	float			m_fAlpha;	//��̧�l.



	SPRITE_STATE	m_SState;	//���ײď��.
	POINTFLOAT		m_fPatternNo;//Ͻ�ڔԍ�.


	//�����ق̎�ނ��Ƃɗp��.
	ID3D11VertexShader*		m_pVertexShader;	//���_�����.
	ID3D11InputLayout*		m_pVertexLayout;	//���_ڲ���.
	ID3D11PixelShader*		m_pPixelShader;		//�߸�ټ����.
	ID3D11Buffer*			m_pConstantBuffer;	//�ݽ����ޯ̧.
	ID3D11ShaderResourceView*	m_pTexture;		//ø���.

	//�����ق��Ƃɗp��.
	ID3D11Buffer*			m_pVertexBuffer;	//���_�ޯ̧.

	ID3D11SamplerState*		m_pSampleLinear;//ø����̻���װ:/ø����Ɋe��̨����������.
};


#endif//#define _SPRITE_2D_H_

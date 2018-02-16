#ifndef _PARTICLE_H_
#define _PARTICLE_H_

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
//�ݽ����ޯ̧�̱��ؑ��̒�`(PointSprite.hlsl).
//����ޓ��̺ݽ����ޯ̧�ƈ�v���Ă���K�v����.
struct PSPRITESHADER_CONSTANT_BUFFER
{
	D3DXMATRIX	mWVP;	//ܰ���,�ޭ�,�ˉe�̍����ϊ��s��.
//	D3DXVECTOR4	vColor;	//�װ(RGBA�̌^�ɍ��킹��) : ø����̏ォ��F���ڂ���(�Ԃ��ۂ��������邽�߂Ƃ�).
//	D3DXVECTOR4	vUV;	//UV���W.
};

//���_�̍\����.
struct PSpriteVertex
{
	D3DXVECTOR3 vPos;	//���_���W(x,y,z).
//	D3DXVECTOR2 vTex;	//ø������W.
};


//�߰è�ٗp�\����.
struct PART
{
	D3DXVECTOR3 vPos;	//�ʒu.
	D3DXVECTOR3 vDir;	//����.
	float		fSpeed;	//���x.
	int			iBirthFrame;//�J�n�ڰ�.

	//�\���̂̏�����(�ݽ�׸�).
	PART(){
		ZeroMemory( this, sizeof( PART ) );
	}
};



//============================================================
//	�߰è�ٸ׽.
//============================================================
class clsParticle
	: public clsCommon	//���ʸ׽�p��
{

public:


	clsParticle(){
		ZeroMemory( this, sizeof( clsParticle ) );//�ݽ�׸�.
	};	
	//���ް۰�ފ֐�.
	clsParticle( int MaxParticle, D3DXVECTOR3 &vEmitPos );//�ݽ�׸�.
	~clsParticle();	//�޽�׸�.

	//������.
	HRESULT Init( ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11 );

	//����ލ쐬.
	HRESULT InitShader();
	////�߲�Ľ��ײč쐬.
	HRESULT InitPointSprite();
	//ø����Ǎ�&�쐬.
	HRESULT InitTexture( char *pFileName );



	//�`��(�����ݸ�)(��DX9MESH����Main����2���݂���̂Œ���).
	void Render( D3DXMATRIX &mView, D3DXMATRIX &mProj,
				 D3DXVECTOR3 &vEye, D3DXVECTOR3 &vPos );


	//����ޖ�����(�����).
	void DetachShader();

	//�߰è�ق̈ړ�.
	void Run();



	D3DXVECTOR3		m_vPos;	//�ʒu.

	int		m_AnimCount;	//UV��۰�.

	bool	m_bDispFlg;		//�\���׸�.

	D3DXVECTOR3		m_vEmitPos;		//���ˈʒu.
	PART*			m_pParticleArray;//�߰è�ٔz��.
	int				m_Frame;		//�ڰѐ�.




	//�߰è�وʒu�̎擾.
	D3DXVECTOR3& GetParticlePos( int index ){
		//�z��͈̔͂��ǂ�������.
		if( 0 <= index && index < m_iMaxParticle ){
			return m_pParticleArray[index].vPos;
		}
		//�͈͊O�̎��͐擪��Ԃ�.
		return m_pParticleArray[index].vPos;
	}
	//�߰è�ٍő吔�̎擾.
	int GetMaxParticle(){ return m_iMaxParticle; }

private:
	//�����ق̎�ނ��Ƃɗp��.
	ID3D11VertexShader*		m_pVertexShader;	//���_�����.
	ID3D11InputLayout*		m_pVertexLayout;	//���_ڲ���.

	ID3D11GeometryShader*	m_pGeometryShader;	//�޵��ؼ����.

	ID3D11PixelShader*		m_pPixelShader;		//�߸�ټ����.
	ID3D11Buffer*			m_pConstantBuffer;	//�ݽ����ޯ̧.

	//�����ق��Ƃɗp��.
	ID3D11Buffer*			m_pVertexBuffer;	//���_�ޯ̧.

	ID3D11ShaderResourceView*	m_pTexture;		//ø���.
	ID3D11SamplerState*			m_pSampleLinear;//ø����̻���װ:/ø����Ɋe��̨����������.

	int				m_iMaxParticle;	//�߰è�ٍő吔.



};


#endif	//#ifndef __PARTICLE_H__H_

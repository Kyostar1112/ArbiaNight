#ifndef _CRAY_H_
#define _CRAY_H_

#include "Common.h"	//���ʸ׽.

//ڲ�׽(�\���݂̂��s��).
class clsRay
	: public clsCommon	//���ʸ׽�p��.
{
public:
//============================================================
//	�\����.
//============================================================
	//�ݽ����ޯ̧�̱��ؑ��̒�`(Ray.hlsl).
	//����ޓ��̺ݽ����ޯ̧�ƈ�v���Ă���K�v����.
	struct SHADER_CONSTANT_BUFFER
	{
		D3DXMATRIX	mWVP;		//ܰ���,�ޭ�,�ˉe�̍����ϊ��s��.
		D3DXVECTOR4	vColor;		//�װ(RGBA�̌^�ɍ��킹��) : ø����̏ォ��F���ڂ���(�Ԃ��ۂ��������邽�߂Ƃ�).
	};

	//���_�\����.
	struct MODEL_VERTEX
	{
		D3DXVECTOR3 vPos;	//�ʒu.
	};

	//ڲ�\����.
	struct RAY
	{
		D3DXVECTOR3 vPoint[2];	//�n�_�A�I�_.
		D3DXVECTOR3 vDirection;	//����.
		D3DXVECTOR3 vPos;		//�ʒu.
		FLOAT		fYaw;		//Y��]��.
		RAY()
		{
			ZeroMemory( this, sizeof( RAY ) );
			//vDirection;	= 0;//�����������������̂����Ȃ�.
		}
	};
	RAY						m_Ray;	//ڲ�\����.

	clsRay();
	~clsRay();

	//������.
	HRESULT Init( ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11 );

	//�`��.
	void Render( D3DXMATRIX& mView, D3DXMATRIX& mProj );


private:
	//����ޏ�����.
	HRESULT InitShader();
	//ڲ������.
	HRESULT InitModel();

	//�����ق̎�ނ��Ƃɗp��.
	ID3D11VertexShader*		m_pVertexShader;	//���_�����.
	ID3D11InputLayout*		m_pVertexLayout;	//���_ڲ���.
	ID3D11PixelShader*		m_pPixelShader;		//�߸�ټ����.
	ID3D11Buffer*			m_pConstantBuffer;	//�ݽ����ޯ̧.

	//�����ق��Ƃɗp��.
	ID3D11Buffer*			m_pVertexBuffer;	//���_�ޯ̧.


};




#endif//#ifndef _CRAY_H_.
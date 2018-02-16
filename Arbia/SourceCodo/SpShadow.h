#ifndef _SP_SHADOW_H_
#define _SP_SHADOW_H_

//�x���ɂ��Ă̺��ޕ��͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning( disable:4005 )	

//============================================================
//	�ݸٰ��.
//============================================================
#include "Sprite.h"

//============================================================
//	ײ����.
//============================================================



//============================================================
//	�萔.
//===========================================================

const float fDEFAULT_SHADOW_SCALE = 0.825f;



//============================================================
//	�\����.
//============================================================
//�ݽ����ޯ̧�̱��ؑ��̒�`(Simple.hlsl).
//����ޓ��̺ݽ����ޯ̧�ƈ�v���Ă���K�v����.
struct SHADOW_CONSTANT_BUFFER
{
	D3DXMATRIX	mWVP;		//ܰ���,�ޭ�,�ˉe�̍����ϊ��s��.
	D3DXVECTOR4	vColor;		//�װ(RGBA�̌^�ɍ��킹��) : ø����̏ォ��F���ڂ���(�Ԃ��ۂ��������邽�߂Ƃ�).
	D3DXVECTOR4	vUV;		//UV���W.
};




//============================================================
//	�e�׽.
//============================================================
class clsShadow
	: public clsSprite
{

public:

	float			m_fYaw;		//��](Y��).
	float			m_fPitch;	//��](X��).
	float			m_fRoll;	//��](Z��).



	clsShadow();	//�ݽ�׸�.
	~clsShadow();	//�޽�׸�.

	////���ٍ쐬.
	virtual HRESULT InitModel();

	//�`��(�����ݸ�)(��DX9MESH����Main����2���݂���̂Œ���).
	virtual void Render( D3DXMATRIX& mView, D3DXMATRIX& mProj,
				 D3DXVECTOR3 &vEye );



	//�e�Z�b�g.
	void SetShadow( D3DXVECTOR3 vPos, float fFloor, float fScaleMax = fDEFAULT_SHADOW_SCALE );


private:



	//���W�Z�b�g.
	void SetPos( D3DXVECTOR3 vPos, float fFloor );//Y���W�͏��̍����ōX�V.
	//�����ŉe�̃T�C�Y�ω�.
	void ShadScale( float fPosY, float fFloor, float fScaleMax );


};


#endif	//#ifndef _SP_SHADOW_H_

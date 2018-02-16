#ifndef _C_PENDULUM_H_
#define _C_PENDULUM_H_


#include "CharaSkin.h"
#include "Sound.h"

#include "Effects.h"

//Ҳ݂Ŏg����.
const char PEND_BONE_NAME[] = "PendHitCenter"; 




class clsPend
	: public clsCharaSkin
{
public:
	clsPend();
	virtual ~clsPend();


	void Create( HWND hWnd, int iNo, int iPower );

	virtual void Init();

	//�����ݸ�.
	virtual void Render( D3DXMATRIX& mView, D3DXMATRIX& mProj,
		D3DXVECTOR3& vLight, D3DXVECTOR3& vEye );


	//����(�����).
	void Move( float fEarZ );




	//���߃t���O�̐ݒ�.
	void SetAlphaFlg( float fPlayerZ );


	
	//�{�[��pos.
	void GetBonePos( 
		const char* cBoneName,
		D3DXVECTOR3 vBonePos = D3DXVECTOR3( -100.0f, -100.0f, -100.0f ) );

	//�Ήԕ`��t���O�Z�b�g.
	void SetFireDisp( bool bFlg ){
		m_bFireDisp = bFlg;
	}


private:

	//���ʉ�.
	void PlaySe( float fEarZ );
	clsSound*	m_pSe;


	float m_fMovePower;
	bool m_bRigtFlg;

	int		m_iInitFlg;//�������t���O.


	//���ߒl�̐ݒ�.
	void SetAlpha();
	//����.
	float	m_fAlpha;
	bool	m_bAlpha;//���f����Render()�ɓn������.
	bool	m_bAlphaChange;//���ߒl���ǂ���ɕς��Ă��邩.


	//�G�t�F�N�g.
	//���O�ȗ��p.
	clsEffects*				m_pEffect;
	//�n���h�� eh = EffekseerHandle.
	::Effekseer::Handle		m_ehFire;
	::Effekseer::Handle		m_ehWind;

	//�G�t�F�N�g�Đ�.
	void PlayEffFire();
	void PlayEffWind( bool bRight );
	bool m_bFireDisp;//�Ήԕ`��ӂ炮.


};



#endif//#ifndef _C_PENDULUM_H_
#ifndef _DOOR_MANAGER_H_
#define _DOOR_MANAGER_H_

#include "CharaStatic.h"
#include "Enemy.h"

#include "Sound.h"
#include "Effects.h"



class clsDoorMgr
	: public clsGameObject
{
public:
	clsDoorMgr();
	~clsDoorMgr();

	void Create( HWND hWnd, ID3D11Device* pDevice, 
		ID3D11DeviceContext* pContext, int iNo = -1 );
	void Init();
	void ReStart();

	void Release();
	void UpDateModel(){};

	//�`��.
	virtual void Render( D3DXMATRIX &mView, D3DXMATRIX &mProj,
		D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye );

	virtual void SetPosition( D3DXVECTOR3 vPos );


	void Update( float fEarZ );

	//�R��ꂽ�Ƃ�.
	//�߂�l�̓v���C���[�̏������ʒu�̍X�V���W.
	D3DXVECTOR3 DoorBreak();


	//�����蔻��p.
	void SetColPos( D3DXVECTOR3 vPos );


	//���߃t���O�̐ݒ�.
	void SetAlphaFlg( float fPlayerZ );


	//��Ƃ̕ǂ����蔻��p.
	clsCharaStatic*	GetGateColPointer(){
		return m_pGate;
	}
	clsCharaStatic*	GetWallColPointer(){
		return m_pColWall;
	}
	//�R���邠���蔻��.
	COL_STATE* GetDoorHitColPointer(){
		return &ColState;
	}

	bool GetDoorBroken(){
		return m_bBreak;
	}


	float GetAlp(){
		return m_fAlpha;
	}
	bool GetAlpFlg(){
		return m_bAlpha;
	}
	bool GetAlpChange(){
		return m_bAlphaChange;
	}

private:

	//���f��.
	clsCharaStatic*	m_pGate;//�啔��.
	clsCharaSkin*	m_pDoor;//������.

	clsCharaStatic*	m_pColWall;//�j�󂳂��O�̕ǔ���.


	//�����蔻��p.
	COL_STATE	ColState;
	bool		m_bBreak;

	//���ߒl�̐ݒ�.
	void SetAlpha();
	//����.
	float	m_fAlpha;
	bool	m_bAlpha;//���f����Render()�ɓn������.
	bool	m_bAlphaChange;//���ߒl���ǂ���ɕς��Ă��邩.


	//��Ұ��ݔԍ�.
	enum enAnimation
	{
		enANIM_IDLE = 0,//�󂳂��̂�҂��Ă���.
		enANIM_BREAK,	//����.
		enANIM_DEAD,	//���������Ȃ�.

		enANIM_MAX 	//�ő�.
	};
	enAnimation m_enAnimNo;
	void Animation();
	//�A�j���[�V�������[�h��ύX.
	void ChangeAnimMode( enAnimation anim );
	double m_dAnimTimer;


	//���ʉ�.
	void PlaySe( /*enSound enSe*/ );
	clsSound*	m_pSe;
	float		m_fEarZ;

	//�G�t�F�N�g.
	//���O�ȗ��p.
	clsEffects*				m_pEffect;
	//�n���h�� eh = EffekseerHandle.
	::Effekseer::Handle		m_ehDust;//��.
	//�G�t�F�N�g�Đ�.
	void PlayEff();
	//�h�A�j�󂩂�G�t�F�N�g�Đ��܂ł̃��O.
	int		m_iEffTimer;
	bool	m_bEffTimer;//m_iEffTimer��������Ƃ���?.
};



#endif//#ifndef _DOOR_MANAGER_H_
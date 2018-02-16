#ifndef _GOAL_MANAGER_H_
#define _GOAL_MANAGER_H_

#include "CharaStatic.h"
#include "CharaSkin.h"

#include "Sound.h"

#include "Effects.h"

class clsGoalMgr
	: public clsGameObject
{
public:
	clsGoalMgr();
	~clsGoalMgr();


	void Create( HWND hWnd, ID3D11Device* pDevice, 
		ID3D11DeviceContext* pContext );
	virtual void Init();
	void Release();
	virtual void UpDateModel(){};

	//�`��.
	virtual void Render( D3DXMATRIX &mView, D3DXMATRIX &mProj,
		D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye );

	virtual void SetPosition( D3DXVECTOR3 vPos );


	void Move( float fEarZ );

	//�����J����.
	void BoxBreak();


	//�����蔻��p.
	void SetColPos( D3DXVECTOR3 vPos );



	//�n�`�����蔻��p.
	clsCharaStatic*	GetFloorColPointer(){
		return m_pFloor;
	}
	//��Ray�����蔻��p.
	clsCharaStatic*	GetTrBoxColPointer(){
		return m_pTrBoxCol;
	}

	//�����R���邠���蔻��.
	COL_STATE* GetBoxHitColPointer(){
		return &ColState;
	}

	//���͋󂢂Ă��邩?.
	bool GetBoxOpened(){
		return m_bOpen;
	}

	//�󔠂̍��W(��Ηp).
	D3DXVECTOR3 GetBoxPos(){
		return m_pTreasurer->GetPosition();
	}

private:
	enum enSound
	{
		enSOUND_OPEN = 0,
		enSOUND_CHAIN,

		enSOUND_MAX,
	};
	//���ʉ�.
	void PlaySe( enSound enSe );
	clsSound**	m_ppSe;
	int			m_iSeMax;

	//���f��.
	clsCharaStatic*	m_pFloor;//������.
	clsCharaSkin*	m_pTreasurer;//��.
	clsCharaStatic*	m_pTrBoxCol;//�󔠂ɏd�Ȃ�Ȃ��p( Ray ).


	//���̂����蔻��p.
	COL_STATE	ColState;
	bool		m_bOpen;


	//��Ұ��ݔԍ�.
	enum enAnimation
	{
		enANIM_IDLE = 0,//�J������̂�҂��Ă���.
		enANIM_OPEN,	//�J��.
		enANIM_DEAD,	//���������Ȃ�.

		enANIM_MAX 	//�ő�.
	};
	enAnimation m_enAnimNo;
	void Animation();
	//�A�j���[�V�������[�h��ύX.
	void ChangeAnimMode( enAnimation anim );
	double m_dAnimTimer;



	//�G�t�F�N�g.
	//���O�ȗ��p.
	clsEffects*				m_pEffect;
	//�n���h�� eh = EffekseerHandle.
	::Effekseer::Handle		m_ehOpen;
	::Effekseer::Handle		m_ehLoop;


};

#endif//#ifndef _GOAL_MANAGER_H_
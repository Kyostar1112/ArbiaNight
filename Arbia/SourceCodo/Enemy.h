#ifndef _C_ENEMY_H_
#define _C_ENEMY_H_


#include "CharaSkin.h"

#include "Collision.h"

#include "Effects.h"

const int TURN_POS_NO_MAX = 4;





class clsEnemy
		: public clsCharaSkin
{
public:
//�G�̓����̎��.
	enum enENEMY_MOVE
	{
		enEM_WALK = 0,
		enEM_RUN,
		enEM_ATK,
		enEM_STOP,
		enEM_DEATH,
		enEM_WIN,
	};//m_enMove.

clsEnemy();
	~clsEnemy();

	void Create( HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11, int iNo, int jNo );
	virtual void Init( float fStartZ );

	//�G����.
	void Move( float fEarZ );
	//���S����.
	void Dead( bool FlgPlayerJumpAtk = false );



	//���.
	void SetTurnPos( float x, float z, float SecondX, float SecondZ, bool bReverse, bool bSecond );
	void Turn( int TargetNo );




	//���Pos���.
	void AddTurnPos( D3DXVECTOR3 vPos ){
		for( int i=0; i<TURN_POS_NO_MAX; i++ ){
			m_colTurn[i].vPos += vPos;
		}
	}

	//��Ԏ擾.
	enENEMY_MOVE GetMove(){
		return m_enMove;
	}

	//����.
	bool Discover( bool bSoundFlg = true );
	//�߂�.
	void Back();
	//������.
	void Lost();
	//�U��.
	void Attack();

	//����.
	void Win();


	COL_STATE	m_colSub;	//���G,�U���͈�.
	COL_STATE	m_colTurn[TURN_POS_NO_MAX];	//�p.
	int			m_iTarNo;	//TargetNumber.//�ǂ�������Pos��No.




	//�U���̏u�ԃt���O��Ԃ�.
	bool GetAttackImpact(){
		return m_bAtkImpact;
	}


	//�ǂ�������Ƃ��ɕK�v.
	void GetSarchTarget( D3DXVECTOR3 vPos ){
		m_vTargetPos = vPos;
	}

private:

	void Release();

	//�����蔻��.
	clsCollision*	m_pCollision;

	//�����������Z���W(���ꂪ������̍L���̒��S�_).
	float m_fStartZ;

	//�G�����q��.
	void Move_Walk ();
	void Move_Run  ();
	void Move_Atk  ();
	void Move_Stop ();
	void Move_Death();//���S�̓���.


	//�ڕW�Ƃ̊p�x.
	float OpponentDirect( D3DXVECTOR3 Attker, D3DXVECTOR3 Target );//



	//�����������̔����𔻒肷��.
	bool isLostRange();

	//������.
	void Winner();



	void UpdateDir();

	virtual void UpdateColState();//Ѱ�ނ̍Ō�Ɏg��.

	enENEMY_MOVE m_enMove;

	bool		m_bDead;
	int			m_iStopTimer;
	int			m_iAtkTimer;
	bool		m_bAtkImpact;//�U���̏u��.
	bool		m_bWin;//�U���I����ɏ������[�V�����ֈڍs����t���O.



	//������������ɒǂ������Ȃ��^�C�}�[.
	int m_iReDiscTimer;//ReDiscoverTimer.

	//�ǂ�������Ƃ��ɕK�v.
	D3DXVECTOR3 m_vTargetPos;//��ڲ԰�̍��W������.

	//��Ұ��ݔԍ�.
	enum enAnimation
	{
		enANIM_IDLE = 0,

		enANIM_WALKING,

		enANIM_RUNING,

		enANIM_ATK,

		enANIM_WIN,

		enANIM_DEAD,	//�|���.
		enANIM_HAND_OUT,//�肪������.
		enANIM_LOSE,	//�|��Ă�i �|��I�����{ �s�� } �j.

		enANIM_MAX 	//�ő�.
	};
	enAnimation m_enAnimNo;
	void Animation();
	//�A�j���[�V�������[�h��ύX.
	void ChangeAnimMode( enAnimation anim );

	//���̎��.
	enum enSound
	{
		enSOUND_DCOVER = 0,//����.//DISCOVER.
		enSOUND_CHANCE,
		enSOUND_SWING,
		enSOUND_DOWN,

		enSOUND_MAX,	//�ő吔.
	};
	//���ʉ�.
	void PlaySe( enSound enSe );
	clsSound**	m_ppSe;
	float		m_fEarZ;	//���̈ʒu(�g���b�v�Q�ƈႢ�����ɂ���̂���΂������̂�).

	//�G�t�F�N�g.
	//���O�ȗ��p.
	clsEffects*				m_pEffect;
	//�n���h�� eh = EffekseerHandle.
	::Effekseer::Handle		m_ehSlash;//�a��.
	//�G�t�F�N�g�Đ�.
	void PlayEff();

};


#endif//#ifndef _C_ENEMY_H_
#ifndef _C_PLAYER_H_
#define _C_PLAYER_H_


#include "CharaSkin.h"
#include "Sound.h"
#include "CXInput.h"
#include "Effects.h"


const int iEFFECT_PLAYER_STEP_MAX = 4;

struct EFF_STEP
{
	::Effekseer::Handle		ehStep;//����.
	D3DXVECTOR3				vPos;
};



class clsPlayer
	: public clsCharaSkin
{
public:
	clsPlayer();
	~clsPlayer();

	//���@�����̎��.
	enum enPLAYER_MOVE
	{
		enPM_IDLE	= 0,//��~.
		enPM_RUN,		//����.
		enPM_ATK,		//�U��.
		enPM_JUM_ATK,	//�ެ��ߍU��.
		enPM_DEAD		//н.
	};//m_enMove

	void Create( HWND hWnd, 
		ID3D11Device* pDevice11, 
		ID3D11DeviceContext* pContext11,
		clsXInput* pXinput );
	virtual void Init();


	COL_STATE* GetPointerSubCol(){
		return &m_colSub;
	}

	//���W�R������Update.
	void UpdateDir();

	void Input();

	void Update( float fEarZ );

	void Rerease();

	void Dead();

	//�W�����v�J�n.
	void SetJump( bool bDropout = false );

	//�X�e�[�W�X�^�[�g.
	void Spawn();
	//����.
	void ReSpawn();
	//�����n�_�X�V.
	void UpdateReSpawnPos( D3DXVECTOR3 vPos ){
		m_vReSpawnPos = vPos;
	}




	//Get�ذ��.
	bool GetDead(){
		return m_bDead;
	}
	bool GetDirNorth(){
		return m_bDirNorth;
	}
	//���Ƃ̂����蔻��p.
	float GetColToFloorRange(){
		const float r = 0.375f;
		return r;
	}

	//.m_bLanding.
	bool GetGroundFlg(){
		return m_bLanding;
	};
	void SetGroundFlg( bool bFlg ){
		m_bLanding = bFlg;
	};


	//�J���������グ��?(�W�����v�U�����Ȃ猩�グ��).
	bool isCamLookUp(){
		if( m_enMove == enPM_JUM_ATK ){
			return true;
		}
		return false;
	}

	//�U���̏u�ԃt���O��Ԃ�.
	bool GetAttackImpact(){
		return m_bAtkImpact;
	}


	//�w�̍�����Ԃ��i�V��̂����蔻��p�j.
	float GetHeight();//const float COL_PLAYER_H  = 2.0f;.
	//�V��ɓ���ł�����.
	void HeadHitToCeiling();

	//�c�@.
	int GetHp(){
		return m_iHp;
	}

	//�����Ɨ��Ƃ����t���O�Ԃ�.
	bool isJumpAtk(){
		if( m_enMove == enPM_JUM_ATK ){
			return true;
		}
		return false;
	}
	//�����Ɨ��Ƃ��~�����t���O.
	bool GetJumpAtkImpact();



	//���C���ȊO.
	void InitTitleScene();
	void MoveTitleScene();
	void MoveResultScene();
	void InitOverScene();
	void MoveOverScene();
	void InitEndScene();
	void MoveEndScene( float fRuRange );

	int		m_iTitleTimer;
	bool	m_bTitleSpnFlg;


private:


	//�ʏ�U���J�n.
	void Kick( bool bMovie = false );

	virtual void UpdateColState();//Ѱ�ނ̍Ō�Ɏg��.

	//�����֐�.
	void Deceleration();


	//�q��.
	void Input_Walk();
	void Input_Action();
	void Input_ActionJump();
	void Input_ActionAtk();

	void MoveWalk();
	void MoveAction();
	void MoveActionJump();
	void MoveActionAtk();


	clsXInput* m_pXInput;

	//����͈�.
	COL_STATE	m_colSub;	//���G,�U���͈�.

	enPLAYER_MOVE m_enMove;

	bool	m_bDead;
	bool	m_bJump;//jump.
	bool	m_bLanding;//���n���ۂ�.

	float	m_fJumpEnagy;//j_energy.

	int		m_iJumpTimer;//Player_JumpTimer

	bool	m_bJumpAtkTopFlg;//���_�ł����������Ȃ�.
	bool	m_bJumpSpdDown;//�W�����v���Ɍ������Ă悢��.

	bool	m_bDirNorth;//�k�����׸�.

	D3DXVECTOR3 m_vReSpawnPos;//�����n�_.

	int		m_iHp;//�c�@��.

	float	m_fOldY;



	//����A�j���[�V�����p�t���O.
	bool	m_bRunning;//�����Ă��邩�ۂ�.
	bool	m_bAtkImpact;//�U���̏u��.



	//��Ұ��ݔԍ�.
	enum enAnimation
	{
		enANIM_IDLE = 0,

		enANIM_RUN_START,	//�E���X�^�[�g.
		enANIM_RUNNING_R,	//�E�����O�ɏo�Ă���.
		enANIM_RUNNING_L,
		enANIM_RUN_END_R,	//enANIM_RUNNING_R����Ȃ�.
		enANIM_RUN_END_L,	//enANIM_RUNNING_L����Ȃ�.

		enANIM_JUMP_START,	
		enANIM_JUMP_UP,		//�㏸.
		enANIM_JUMP_U_TURN,	//�㉺�^���G�l���M�[�̓]��.
		enANIM_JUMP_FALL,	//���~.
		enANIM_JUMP_STMP,	//���n���n���Ɉړ�����͂��Ă�Ȃ�Đ�����Ȃ�(���胂�[�V�����ɍs��).

		enANIM_ATK_MOVIE,
		enANIM_ATK_ACT,

		enANIM_JUMP_ATK_SPN,	//�󒆉�].
		enANIM_JUMP_ATK_FALL,	//����.
		enANIM_JUMP_ATK_STMP,	//���n.
		enANIM_JUMP_ATK_STND,	//�N���オ��.

		enANIM_DEAD,//�|���.
		enANIM_LOSE,//�|��Ă�i �|��I�����{ �s�� } �j.

		enANIM_MAX 	//�ő�.
	};

	enAnimation m_enAnimNo;
	void Animation();
	//�A�j���[�V�������[�h��ύX.
	void ChangeAnimMode( enAnimation anim );


	//���̎��.
	enum enPlayerSound
	{
		enPS_RUN = 0,
		enPS_JUMP,
		enPS_ATK,
		enPS_JUMP_ATK_SPN,
		enPS_JUMP_ATK_STMP,
		enPS_HEAD_HIT,
		enPS_DEAD,

		enPS_MAX,	//�ő吔.
	};
	//���ʉ�.
	void PlaySe( enPlayerSound enSe );
	clsSound**	m_ppSe;
	float		m_fEarZ;	//���̈ʒu(�g���b�v�Q�ƈႢ�����ɂ���̂���΂������̂�).

	void SetSe( HWND hWnd );



	//�G�t�F�N�g.
	//���O�ȗ��p.
	clsEffects*				m_pEffect;
	//�n���h�� eh = EffekseerHandle.
	::Effekseer::Handle		m_ehWave;//�Ռ��g.
	EFF_STEP				m_EffStep[iEFFECT_PLAYER_STEP_MAX];//����4.
	::Effekseer::Handle		m_ehKick;//�L�b�N.

	//���ՃG�t�F�N�g�Đ�.
	void PlayStepEff();
	//�Ռ��g.
	void PlayWaveEff();
	//�L�b�N�Đ�.
	void PlayKickEff();



	//�ړ��⏕.
	bool InputUp();
	bool InputDown();
	bool InputLeft();
	bool InputRight();
};




#endif//#ifndef _C_PLAYER_H_
#include "Player.h"

#include <Windows.h>

//-----�U��-----//.
//����ł�.
const unsigned short usVIB_HEAD_POWER = INPUT_VIBRATION_MAX / 4;
const int iVIB_HEAD_TIME = 10;
//�W�����v�U�����n.
const unsigned short usVIB_JATK_POWER = INPUT_VIBRATION_MAX;
const int iVIB_JATK_TIME = 20;
//���S.
const unsigned short usVIB_DEAD_POWER = INPUT_VIBRATION_MAX;
//const int iVIB_DEAD_TIME = 180;
const int iVIB_DEAD_TIME = -1;
const int iVIB_DEAD_DEC = 511;//1�t���[���łǂꂾ����܂邩.



//----- �� -----//.
//����.
#define ALIAS_NAME_RUN "AlbiaRun"
#define  FILE_PATH_RUN "SE\\100Arbia\\010Run.wav"
const	  int iVOL_RUN = 1000;

//��ї���.
#define ALIAS_NAME_JUMP "AlbiaJump"
#define  FILE_PATH_JUMP "SE\\100Arbia\\020Jump.wav"
const	  int iVOL_JUMP = 1000;

//�L�b�N.
#define ALIAS_NAME_ATK "AlbiaAtk"
#define  FILE_PATH_ATK "SE\\100Arbia\\200Atk.wav"
const	  int iVOL_ATK = 1000;

//�󒆃|�[�Y.
#define ALIAS_NAME_JUMP_ATK_SPN "AlbiaJumpAtk"
#define  FILE_PATH_JUMP_ATK_SPN "SE\\100Arbia\\600JumpAtkSpn.wav"
const	  int iVOL_JUMP_ATK_SPN = 1000;

//�����Ɨ��Ƃ����n.
#define ALIAS_NAME_JUMP_ATK_STMP "AlbiaJumpStmp"
#define  FILE_PATH_JUMP_ATK_STMP "SE\\100Arbia\\610JumpAtkStep.wav"
const	  int iVOL_JUMP_ATK_STMP = 1000;

//������.
#define ALIAS_NAME_HEAD_HIT "AlbiaHeadHit"
#define  FILE_PATH_HEAD_HIT "SE\\100Arbia\\700HeadHit.wav"
const	  int iVOL_HEAD_HIT = 1000;

//����.
#define ALIAS_NAME_DEAD "AlbiaDead"
#define  FILE_PATH_DEAD "SE\\100Arbia\\900Dead.wav"
const	  int iVOL_DEAD = 1000;



//���ق̓s��(�O�����).
const float fMODEL_BACK_TURN = (float)M_PI;
//�A�j�����x.
const double fANIM_SPD = 0.03125 / 2.0;
const double fANIM_SPD_IDLE = fANIM_SPD / 2.0;


//�X�^�[�g�n�_.
const D3DXVECTOR3 vSTART_POSITION = { 0.0f, 0.0f, 9.0f };


//�c�@.
const int iMAX_HP = 10;


//===== �����蔻�� =====//.
const float fCOL_PLAYER_H  = 2.0f;
const float fCOL_PLAYER_RANGE  = 0.25f;

//===== Box =====//.
const float fCOL_PLAYER_BOX_XZ = 0.5f / 2.0f;
const float fCOL_PLAYER_BOX_Y = fCOL_PLAYER_H / 2.0f;
const float fCOL_PLAYER_BOX_CENTER_Y = fCOL_PLAYER_H / 2.0f;

//===== ��ڲ԰�̍U�� =====//.
const int	iCOL_PLAYER_KICK_THETA = 120;
//const float	COL_PLAYER_KICK_RANGE = 1.25f;
const float	fCOL_PLAYER_KICK_RANGE = 2.0f;
//===== �����蔻�� �I��� =====//.


//����.
const float fLOW_SPD_CHANGE = 0.025f;

//�W�����v�J�n.
const float fJUMP_START_POWER = 0.2f;
//�ެ��ߏ㏸�̏������.
const int iJUNP_TIME_UP_TIME = 14;
//�W�����v��������.
const float fGRAVITY = 0.02f;//gravity.
//�ő嗎�����x.
const float fDROP_DOWN_SPD_MAX = -0.2f;


//�ŏ��̃t���[���ɕK�v.
float fLAND_PLAYER_ZERO = 0.0f;



//�����Ɨ��Ƃ�.
const float fJUMP_STK_PER_ENGY_S = 0.1875f;//Permission����.
const float fJUMP_STK_PER_ENGY_E = -0.0625f;//Permission����.
const float fJUMP_ATK_START_ENAGY = 0.15f;//�����㏸��.
//�����x.
const float fSPD_UP_POWER = 0.0625f;
const float fJUMP_ATK_GRAVITY_SPN = 0.005f;			//�㏸���x.
const float fJUMP_ATK_GRAVITY_DOWN_START = 0.3625f;	//���~�J�n�̑��x.
const float fJUMP_ATK_GRAVITY_DOWN_PLUS = 0.035f;	//���~�����x.



//���݂̃A�j���[�V�������I������( �A�j��No.�Ɋ|����{ ���̃A�j���ɂȂ�قǒx���̂� } ).
const int iANIM_FIN_RATE = 3;//.
//���艟��( ���̃A�j�������c�肪���� ).
const int iEXCEPTION_ANIM_END_RATE = 2; //��O�A�j���̃A�j���[�V�����I�����Ԃ̃��[�g.

//���C���ȊO.
const int iTITLE_KICK_START_TIMER = 45;
const int iTITLE_SPN_START_TIMER = 65;
const float fTITLE_SPN_SPD = -(float)M_PI_4 / 8.0f;
const float fOVER_INIT_ROT_Y = 0.75f;

//�G�t�F�N�g.
const float fEFFECT_SPD_WAVE = 4.0f;
const D3DXVECTOR3 vEFFECT_SCALE_WAVE = { 1.0f, 1.0f, 1.0f };
const char cSTEP_EFFECT_MAX = 4;
const float fEFFECT_KICK_UP_OFFSET = 1.0f;
const float fEFFECT_SPD_KICK = 1.5f;
const D3DXVECTOR3 vEFFECT_SCALE_KICK = { 0.1875f, 0.1875f, 0.1875f };
const int iEFFECT_KICK_RAG = 15;
const float fEFFECT_STEP_UP_OFFSET = 0.01f;//�n�ʂ���̕�����.


clsPlayer::clsPlayer()
{
	m_dAnimSpeed = fANIM_SPD;
	
	m_pXInput = nullptr;
	m_ppSe = nullptr;
	m_pEffect = nullptr;
}

clsPlayer::~clsPlayer()
{
	Rerease();
}

void clsPlayer::Create( HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11, clsXInput* pXinput )
{
	if( m_pXInput == nullptr ){
		m_pXInput = pXinput;
	}

	SetSe( hWnd );
	m_iHp = iMAX_HP;
	Init();
	if( m_pShadow == nullptr ){
		m_pShadow = new clsShadow;
		m_pShadow->Init( pDevice11, pContext11 );
	}

	if( m_pDevice == nullptr ) m_pDevice = pDevice11;
	if( m_pContext == nullptr ) m_pContext = pContext11;


	if( m_pEffect == nullptr ){
		m_pEffect = clsEffects::GetInstance();
	}


}


void clsPlayer::Init()
{
	m_dAnimSpeed = fANIM_SPD;
	m_bDead = false;

	m_bJump = false;
	m_bLanding = true;
	m_fJumpEnagy = 0.0f;
	m_iJumpTimer = 0;
	m_bJumpAtkTopFlg = false;//���_�ł����������Ȃ�.
	m_bRunning = false;
	m_bAtkImpact = false;

	m_fSpd = 1.0f;
	m_fYawTarget = 0.0f;

	m_fFloorY = fLAND_PLAYER_ZERO;

	m_enMove = enPM_IDLE;
	m_enDir = enDirection_Stop;

	//�����蔻��.
	//�{��.
	ColState.fRange = fCOL_PLAYER_RANGE;
	ColState.fHeight = fCOL_PLAYER_H;

	//Box�p.
	ColState.vRangeHalf.x = ColState.vRangeHalf.z = fCOL_PLAYER_BOX_XZ;
	ColState.vRangeHalf.y = fCOL_PLAYER_BOX_Y;
	ColState.fCenterY = fCOL_PLAYER_BOX_CENTER_Y;
	ColState.fCenterX = 0.0f;

	//Sub.
	m_colSub.fRange = fCOL_PLAYER_KICK_RANGE;
	m_colSub.fHeight = fCOL_PLAYER_H;
	m_colSub.iSarchTheta = iCOL_PLAYER_KICK_THETA;

	//��Ұ���.
	ChangeAnimMode( enANIM_IDLE );

}
//�X�e�[�W�X�^�[�g.
void clsPlayer::Spawn()
{
	m_vReSpawnPos = vSTART_POSITION;
	ReSpawn();
	m_iHp = iMAX_HP;
	m_vRot.y = m_fYawTarget = (float)M_PI;
}
//����.
void clsPlayer::ReSpawn()
{
	Init();
	m_iHp --;
	m_vPos = m_vReSpawnPos;
	m_vRot.y = m_fYawTarget = 0.0f;
	m_fOldY = m_vPos.y;
}

void clsPlayer::Rerease()
{
	if( m_pShadow != nullptr ){
		delete m_pShadow;
		m_pShadow = nullptr;
	}

	m_pEffect = nullptr;

	if( m_ppSe != nullptr ){
		for( int i=0; i<enPS_MAX; i++ ){
			delete m_ppSe[i];
			m_ppSe[i] = nullptr;
		}
		delete[]m_ppSe;
		m_ppSe = nullptr;
	}

	if( m_pModel != nullptr ){
		delete m_pModel;
		m_pModel = nullptr;
	}

	m_pXInput = nullptr;
}
//============================================================
//	����.
//============================================================
void clsPlayer::Input()
{
	if( m_enMove != enPM_ATK	 &&
		m_enMove != enPM_JUM_ATK &&
		m_enMove != enPM_DEAD )
	{
		//�ړ�.
		Input_Walk();
		//�����.
		Input_Action();
	}

	//�f�o�b�O�p.
	if( GetAsyncKeyState( VK_SPACE ) & 0x1 ){
		m_iHp = 0;
	}
}
//------------------------------.
//	���́i�ړ��j.
//------------------------------.
void clsPlayer::Input_Walk()
{
	if( m_pXInput == nullptr ) return;
	//���͂���Ă��邩.
	bool bInputMovePlus = true;
	bool bInputMoveStick = true;


	//�\����.
	float closButnTarYaw = m_fYawTarget;//�ڕW�p�x�ꎞ�ۑ�.
	m_enDir = enDirection_Foward;
	m_enMove = enPM_RUN;
	m_bJumpSpdDown = false;
	//��.
	if( InputUp() ){
		closButnTarYaw = fMODEL_BACK_TURN + 0.0f;
		if( InputRight() ){
			closButnTarYaw += (float)M_PI_4;
		}
		else if( InputLeft() ){
			closButnTarYaw -= (float)M_PI_4;
		}
	}
	//��.
	else if( InputDown() ){
		closButnTarYaw = fMODEL_BACK_TURN + (float)M_PI;
		if( InputRight() ){
			closButnTarYaw -= (float)M_PI_4;
		}
		else if( InputLeft() ){
			closButnTarYaw += (float)M_PI_4;
		}
	}
	//�E.
	else if( InputRight() ){
		closButnTarYaw = fMODEL_BACK_TURN + (float)M_PI_2;
	}
	//��.
	else if( InputLeft() ){
		closButnTarYaw = fMODEL_BACK_TURN + (float)( M_PI + M_PI_2 );
	}
	//���������Ă��Ȃ�.
	else{
		if( !m_bJump ){
			m_enMove = enPM_IDLE;
			m_enDir = enDirection_Stop;
//			m_fSpd = 0.0f;
		}
		m_bJumpSpdDown = true;
		bInputMovePlus = false;
	}

	//�\�����ɐG�ꂽ�Ȃ�.
	if( !m_bJumpSpdDown ){
		//�è�������t�ȊO.
		if( ThetaCheck( m_vRot.y, m_fYawTarget, 270 ) ){
			//�ڕW�̕�����ς���.
			m_fYawTarget = closButnTarYaw;
			ThetaOverGuard( m_fYawTarget );
		}
		//�è���t����.
		else{
			m_bJumpSpdDown = true;
		}
	}

	//�è��.
	if( m_pXInput->GetLStickSlope() != clsXInput::enSS_NOTHING ){
		m_enMove = enPM_RUN;
		m_bJumpSpdDown = false;
		m_enDir = enDirection_Foward;

		//�è�������t�ȊO.
		if( ThetaCheck( m_vRot.y, m_fYawTarget, 270 ) ){
			//�ڕW�̕�����ς���.
			m_fYawTarget = m_pXInput->GetLStickTheta();
			ThetaOverGuard( m_fYawTarget );
		}
		//�è���t����.
		else{
			m_bJumpSpdDown = true;
		}
	}
	else{
		bInputMoveStick = false;
	}

	//�\���L�[���X�e�B�b�N�����͂������Ȃ�.
	if( !bInputMovePlus && !bInputMoveStick ){
		//����.
		if( !m_bJump ){
			m_fSpd = 0.0f;
			//�A�j���[�V����(����I���).
			if( m_bRunning ){
				if( m_enAnimNo == enANIM_ATK_ACT ){}
				else if( m_enAnimNo == enANIM_RUNNING_L ){
					ChangeAnimMode( enANIM_RUN_END_L );
				}
				else if( m_enAnimNo == enANIM_RUNNING_R ){
					ChangeAnimMode( enANIM_RUN_END_R );
				}
				else if( m_enAnimNo == enANIM_RUN_START ){
					//�U���͗�O.
					if( m_enMove != enPM_ATK ){	
						ChangeAnimMode( enANIM_RUN_END_R );
					}
				}
			}
		}
		m_bRunning = false;//����A�j���[�V�����p�t���O.
	}
	//�ǂ��炩���͂��Ă���Ȃ�.
	else{
		//����.
		if( !m_bJump ){
			//����n��.
			if( !m_bRunning ){
				//�U�����͏���.
				if( m_enAnimNo != enANIM_ATK_ACT ){
					ChangeAnimMode( enANIM_RUN_START );
				}
			}
		}
		m_bRunning = true;
	}


}
//------------------------------.
//	���́i����݁j.
//------------------------------.
void clsPlayer::Input_Action()
{
	//�ެ���.
	Input_ActionJump();
	//�U��.
	Input_ActionAtk();
}
//	���́o ����� �i�ެ��߁j�p.
void clsPlayer::Input_ActionJump()
{
	if( m_pXInput == nullptr ) return;
	//�ެ��ߊJ�n.
	if( m_pXInput->IsPressEnter( XINPUT_A ) ||
		GetAsyncKeyState( 'Z' ) & 0x1 )
	{
		if( !m_bJump ){
			SetJump();
		}
	}

	//�ެ��ߏ㏸���f.
	if( m_bJump ){
		if( m_pXInput->IsPressExit( XINPUT_A ) ){
			m_iJumpTimer = iJUNP_TIME_UP_TIME;
			ChangeAnimMode( enANIM_JUMP_U_TURN );
		}
	}
}
//	���́o ����� �i�U���j�p.
void clsPlayer::Input_ActionAtk()
{
	if( m_pXInput == nullptr ) return;
	if( m_pXInput->IsPressEnter( XINPUT_X ) ||
		GetAsyncKeyState( 'X' ) )
	{
		//�ެ��ߍU��.
		if( m_bJump ){
			//�ެ��߂̒��_?.
			if( m_bJumpAtkTopFlg ){
				//���_�߂��𔻒肷��if��.
				if( m_fJumpEnagy < fJUMP_STK_PER_ENGY_S &&
					m_fJumpEnagy > fJUMP_STK_PER_ENGY_E )
				{
					m_enMove = enPM_JUM_ATK;
					m_bLanding = false;//���n���ۂ�.
					m_fJumpEnagy = fJUMP_ATK_START_ENAGY;
					ChangeAnimMode( enANIM_JUMP_ATK_SPN );
					m_bAtkImpact = true;
					PlaySe( enPS_JUMP_ATK_SPN );
				}
			}
		}
		//�ʏ�U��.
		else{
			Kick();
		}
	}
}

//============================================================
//	��������.
//============================================================
void clsPlayer::Update( float fEarZ )
{
	if( m_pEffect == nullptr || m_pShadow == nullptr ) return;

	//�L�b�N�G�t�F�N�g�����Ă���.
	if( m_pEffect->PlayCheck( m_ehKick ) ){
		D3DXVECTOR3 vEffPos = m_vPos;
		vEffPos.y += fEFFECT_KICK_UP_OFFSET;
		m_pEffect->SetLocation( m_ehKick, vEffPos );
	}

	//���̈ʒu���o����.
	m_fEarZ = fEarZ;

	//�����Ɨ��Ƃ��p.
	m_fOldY = m_vPos.y;

	MoveWalk();
	MoveAction();

	SetSpeed();
	UpdateDir();
	UpDateModel();

	UpdatePos();

	UpdateColState();

	Animation();

	m_pShadow->SetShadow( m_vPos, m_fFloorY );
}
//------------------------------.
//	���������i�ړ��j.
//------------------------------.
void clsPlayer::MoveWalk()
{

	//�k�����׸�(��ׂ��k�Ɠ�ǂ���������Ă邩).
	if( ThetaCheck( (float)M_PI, m_vRot.y, 90 ) ){
		m_bDirNorth = true;
	}
	else if( ThetaCheck( 0.0f, m_vRot.y, 90 ) ){
		m_bDirNorth = false;
	}

	//���x�ύX.
	if( m_bJump ){
		if( m_bJumpSpdDown ){
			Deceleration();
		}
		else{
			float TarSpd = m_fSpd;
			if( m_enMove == enPM_RUN ){
				TarSpd = 1.0f;
			}
			//����.
			if( m_fSpd == 0.0f )	m_fSpd = 0.1f;
			else m_fSpd += fSPD_UP_POWER;
			if( m_fSpd > TarSpd )	m_fSpd = TarSpd;
		}
	}
	else{
		if( m_enMove == enPM_RUN ){
			m_fSpd = 1.0f;
		}
	}

	//�U�����.
	if( m_bJump ){
		if( !m_bJumpSpdDown ){
			//��u�ŐU������Ȃ�(���X�ɐU�����)if().
			YawSpnToTarg( m_vRot.y, m_fYawTarget, 0.0625f );
		}
		else if( m_fSpd == 0.0f ){
			//��u�ŐU�����.
			m_vRot.y = m_fYawTarget;
		}
	}
	else{
		//��u�ŐU�����.
		m_vRot.y = m_fYawTarget;
	}
	ThetaOverGuard( m_vRot.y );


	//���ꂩ�痎���鎩�R����.
	//�ެ��ߒ��ł͂Ȃ���.
	if( !m_bJump ){
		//���ɑ��ꂪ�Ȃ���.
		if( m_bDropout ){
			SetJump( true );
		}
	}

	UpdateDir();
}
//------------------------------.
//	���������i����݁j.
//------------------------------.
void clsPlayer::MoveAction()
{
	//�ެ���.
	if( m_enMove != enPM_JUM_ATK ){
		MoveActionJump();
	}
	//�U��.
	MoveActionAtk();
}
//	���������o ����� �i�ެ��߁j�p.
void clsPlayer::MoveActionJump()
{	
	//���ʼެ��ߍs���r��.
	if( m_bJump ){
		m_iJumpTimer ++;
		//�������x����.
		if( m_iJumpTimer > iJUNP_TIME_UP_TIME ){
			m_fJumpEnagy -= fGRAVITY;
		}
		else if( m_iJumpTimer == iJUNP_TIME_UP_TIME ){
			ChangeAnimMode( enANIM_JUMP_U_TURN );
		}
		//���������Ȃ肷���Ȃ�.
		if( m_fJumpEnagy < fDROP_DOWN_SPD_MAX ){
			m_fJumpEnagy = fDROP_DOWN_SPD_MAX;
		}
		//����.
		m_vPos.y += m_fJumpEnagy;
		//���n.
		if( m_vPos.y < m_fFloorY ){
			m_vPos.y = m_fFloorY;
			m_bJump = false;
			SetDropoutFlg( false );
			if( m_bRunning ){
				ChangeAnimMode( enANIM_RUNNING_R );
			}
			else{
				ChangeAnimMode( enANIM_JUMP_STMP );
			}
			PlaySe( enPS_RUN );
			PlayStepEff();
		}
	}
}
//	���������o ����� �i�U���j�p.
void clsPlayer::MoveActionAtk()
{
	if( m_pXInput == nullptr ) return;

	//�����֐�.
	Deceleration();

	//�ʏ�U��.
	if( m_enMove == enPM_ATK ){
//		//�U���I���i�A�j���I�����Ɉ����z���j.
	}
	//�ެ��ߍU��.
	else if( m_enMove == enPM_JUM_ATK ){
		//�󒆋@��.
		if( !m_bLanding ){
			//�㏸��.
			if( m_fJumpEnagy > 0.0f ){
				m_fJumpEnagy -= fJUMP_ATK_GRAVITY_SPN;
				//�~���ɐ؂�ւ��u��.
				if( m_fJumpEnagy <= 0.0f ){
					m_fJumpEnagy = -fJUMP_ATK_GRAVITY_DOWN_START;
					ChangeAnimMode( enANIM_JUMP_ATK_FALL );
				}
			}
			else{
				m_fJumpEnagy -= fJUMP_ATK_GRAVITY_DOWN_PLUS;
			}

			m_vPos.y += m_fJumpEnagy;
			//���n.
			if( m_vPos.y < m_fFloorY ){
				m_vPos.y = m_fFloorY;
				m_bLanding = true;
				m_bJump = false;
				m_bAtkImpact = false;
				ChangeAnimMode( enANIM_JUMP_ATK_STMP );
				PlaySe( enPS_JUMP_ATK_STMP );
				m_pXInput->SetVibPowerL( usVIB_JATK_POWER, iVIB_JATK_TIME );//�U��.
				//�Ռ��g�G�t�F�N�g.
				PlayWaveEff();
			}
		}
//		//�Ռ��g�����オ��(�A�j���I���ֈ����z��).
	}
}


//============================================================
//	�~�X�i���S�j.
//============================================================
void clsPlayer::Dead()
{
	if( m_pXInput == nullptr ) return;
	m_enMove = enPM_DEAD;
	ChangeAnimMode( enANIM_DEAD );
	m_bDead = true;
	PlaySe( enPS_DEAD );
	m_pXInput->SetVibPowerL( usVIB_DEAD_POWER, iVIB_DEAD_TIME, iVIB_DEAD_DEC );//�U��.
	m_pXInput->SetVibPowerR( usVIB_DEAD_POWER, iVIB_DEAD_TIME, iVIB_DEAD_DEC );//�U��.
}






//============================================================
//	�����֐�.
//============================================================
void clsPlayer::Deceleration()
{
	m_fSpd -= fLOW_SPD_CHANGE;
	if( m_fSpd < 0.0f )	m_fSpd = 0.0f;
}


//============================================================
//	���W�R������Update.
//============================================================
void clsPlayer::UpdateDir()
{
	if( m_pModel == nullptr ) return;
	m_pModel->m_enDir = m_enDir;
}


//============================================================
//	Ѱ�ނ̍Ō�Ɏg��.
//============================================================
void clsPlayer::UpdateColState()
{
	ColState.vPos = m_vPos;
	ColState.fYaw = m_vRot.y;

	//Sub�����蔻��.
	m_colSub.vPos = m_vPos;
	m_colSub.fYaw = m_vRot.y;
}


//============================================================
//	�W�����v�J�n.
//============================================================
void clsPlayer::SetJump( bool bDropout )
{
	m_bJump = true;
	//�܂��Ƃ��ȼެ���.
	if( !bDropout ){
		m_fJumpEnagy = fJUMP_START_POWER;
		m_iJumpTimer = 0;
		m_bJumpAtkTopFlg = true;
		ChangeAnimMode( enANIM_JUMP_START );
		PlaySe( enPS_JUMP );
		PlayStepEff();
	}
	//���ꓥ�݊O������.
	else{
		m_fJumpEnagy = 0;
		m_iJumpTimer = iJUNP_TIME_UP_TIME;
		m_bJumpAtkTopFlg = false;
		ChangeAnimMode( enANIM_JUMP_FALL );
	}
	SetDropoutFlg ( false );
}

//============================================================
//	�A�j���[�V����.
//============================================================
void clsPlayer::Animation()
{
#if 1
	//���[�v���Ȃ����[�V����.
	if( m_enAnimNo == enANIM_RUN_START		||
		m_enAnimNo == enANIM_RUNNING_R		||
		m_enAnimNo == enANIM_RUNNING_L		||
		m_enAnimNo == enANIM_RUN_END_R		||
		m_enAnimNo == enANIM_RUN_END_L		||
		m_enAnimNo == enANIM_JUMP_START		||
		m_enAnimNo == enANIM_JUMP_U_TURN	||
		m_enAnimNo == enANIM_JUMP_STMP		||
		m_enAnimNo == enANIM_ATK_ACT		||
		m_enAnimNo == enANIM_ATK_MOVIE		||
		m_enAnimNo == enANIM_JUMP_ATK_SPN	||
		m_enAnimNo == enANIM_JUMP_ATK_STMP	||
		m_enAnimNo == enANIM_JUMP_ATK_STND	||
		m_enAnimNo == enANIM_DEAD			||
		m_enAnimNo == enANIM_LOSE )
	{
		//�A�j���[�V�������ԉ��Z.
		m_dAnimTimer += m_pModel->GetAnimSpeed();
	}

	bool bAnimEndFlg = false;

	//�A�j���[�V�����I�����?.
	if( m_enAnimNo == enANIM_RUNNING_R ){
		if( m_pModel->GetAnimPeriod( m_enAnimNo ) - ( dANIM_ONE_FRAME_OVER_SOLUTION * (double)( m_enAnimNo * m_enAnimNo / iANIM_FIN_RATE * iEXCEPTION_ANIM_END_RATE ) ) <= m_dAnimTimer ){
			bAnimEndFlg = true;
		}
	}
	else{
		if( m_pModel->GetAnimPeriod( m_enAnimNo ) - ( dANIM_ONE_FRAME_OVER_SOLUTION * (double)( m_enAnimNo * m_enAnimNo / iANIM_FIN_RATE ) ) <= m_dAnimTimer ){
			bAnimEndFlg = true;
		}
	}

	//�A�j���[�V�������I�������.
	if( bAnimEndFlg ){
		//���[�v���Ȃ����[�V����.
		switch( m_enAnimNo )
		{
		//����.
		case enANIM_RUN_START:
			ChangeAnimMode( enANIM_RUNNING_R );
			PlaySe( enPS_RUN );
			//�G�t�F�N�g.
			PlayStepEff();	
			break;
		case enANIM_RUNNING_R:
			ChangeAnimMode( enANIM_RUNNING_L );
			PlaySe( enPS_RUN );
			//�G�t�F�N�g.
			PlayStepEff();	
			break;
		case enANIM_RUNNING_L:
			ChangeAnimMode( enANIM_RUNNING_R );
			PlaySe( enPS_RUN );
			//�G�t�F�N�g.
			PlayStepEff();	
			break;
		case enANIM_RUN_END_R:
		case enANIM_RUN_END_L:
			ChangeAnimMode( enANIM_IDLE );
			break;

		//�W�����v.
		case enANIM_JUMP_START:
			ChangeAnimMode( enANIM_JUMP_UP );
			break;
		case enANIM_JUMP_U_TURN:
			ChangeAnimMode( enANIM_JUMP_FALL );
			break;
		case enANIM_JUMP_STMP://���n.
			ChangeAnimMode( enANIM_IDLE );
			break;

		//�U��.
		case enANIM_ATK_MOVIE:
			PlaySe( enPS_ATK );
			PlayKickEff();
			ChangeAnimMode( enANIM_ATK_ACT );
			break;
		case enANIM_ATK_ACT:
			//�U���I��.
			m_bRunning = false;
			m_enMove = enPM_IDLE;
			ChangeAnimMode( enANIM_IDLE );
			m_bAtkImpact = false;
			break;
		//�W�����v�U��.
		case enANIM_JUMP_ATK_SPN:
			ChangeAnimMode( enANIM_JUMP_ATK_FALL );
			break;
		case enANIM_JUMP_ATK_STMP:
			ChangeAnimMode( enANIM_JUMP_ATK_STND );
			break;
		case enANIM_JUMP_ATK_STND:
			m_enMove = enPM_IDLE;
			m_bLanding = false;
			m_bRunning = false;
			ChangeAnimMode( enANIM_IDLE );//�A�j���Z�b�g.
			break;

		//�����.
		case enANIM_DEAD:
			ChangeAnimMode( enANIM_LOSE );//�A�j���Z�b�g.
			break;
		//�����.
		case enANIM_LOSE:
			ChangeAnimMode( enANIM_LOSE );//�A�j���Z�b�g.
			break;
		}
	}
#else
	m_dAnimTimer += m_pModel->GetAnimSpeed();
	if( m_pModel->GetAnimPeriod( m_enAnimNo ) < m_dAnimTimer ){
		m_enAnimNo = (enAnimation)( (int)m_enAnimNo + 1 );
		if( m_enAnimNo >= enANIM_MAX ){
			m_enAnimNo = enANIM_IDLE;
		}
		ChangeAnimMode( m_enAnimNo );
	}
#endif
}

//============================================================
//	�A�j���[�V�������[�h��ύX.
//============================================================
void clsPlayer::ChangeAnimMode( enAnimation anim )
{
	//��΂��Ȃ�.
	if( anim == enANIM_DEAD ||
		anim == enANIM_LOSE)
	{
	}
	//��΂�.
	else if( m_bDead )
	{
		return;
	}

	if( anim == enANIM_IDLE )	m_dAnimSpeed = fANIM_SPD_IDLE;
	else						m_dAnimSpeed = fANIM_SPD;
	m_dAnimTimer = 0.0;
	m_enAnimNo = anim;
	ChangeAnimSet( m_enAnimNo );//�A�j���Z�b�g.

}



//���ʉ��Đ�.
void clsPlayer::PlaySe( enPlayerSound enSe )
{
	if( m_ppSe == nullptr ) return;
	//�Đ����鋗���Ȃ�.
	int vol = ChangeVolumeDistance( m_fEarZ, m_vPos.z );
	if( vol ){
		m_ppSe[enSe]->GetMaxVolRate( vol );
		m_ppSe[enSe]->SeekToStart();
		m_ppSe[enSe]->SetVolume( vol );
		m_ppSe[enSe]->Play();
	}
	//�Đ����Ȃ������Ȃ�.
	else{
		m_ppSe[enSe]->SetVolume( 0 );
	}
}

void clsPlayer::SetSe( HWND hWnd )
{
	if( m_ppSe != nullptr ) return;
	clsSound::SOUND_DATA tmpSData[enPS_MAX] =
	{
		{ ALIAS_NAME_RUN,			FILE_PATH_RUN,			iVOL_RUN			},
		{ ALIAS_NAME_JUMP,			FILE_PATH_JUMP,			iVOL_JUMP			},
		{ ALIAS_NAME_ATK,			FILE_PATH_ATK,			iVOL_ATK			},
		{ ALIAS_NAME_JUMP_ATK_SPN,	FILE_PATH_JUMP_ATK_SPN,	iVOL_JUMP_ATK_SPN	},
		{ ALIAS_NAME_JUMP_ATK_STMP,	FILE_PATH_JUMP_ATK_STMP,iVOL_JUMP_ATK_STMP	},
		{ ALIAS_NAME_HEAD_HIT,		FILE_PATH_HEAD_HIT,		iVOL_HEAD_HIT		},
		{ ALIAS_NAME_DEAD,			FILE_PATH_DEAD,			iVOL_DEAD			},
	};

	m_ppSe = new clsSound*[enPS_MAX];
	for( int i=0; i<enPS_MAX; i++ ){
		m_ppSe[i] = new clsSound;
		//�����ʏ�����.
		m_ppSe[i]->SetVolume( 0 );
		//���O.
		char cAliasName[STR_BUFF_MAX] = "";
		strcat_s( cAliasName, sizeof( cAliasName ), tmpSData[i].sAlias );
		//�쐬.
		m_ppSe[i]->Open( tmpSData[i].sPath, cAliasName, hWnd );
		//�ő剹�ʐݒ�.
		m_ppSe[i]->SetMaxVolume( tmpSData[i].iMaxVolume );
	}
}



//�w�̍�����Ԃ��i�V��̂����蔻��p�j.
float clsPlayer::GetHeight(){
	return fCOL_PLAYER_H;
}

//�V��ɓ���ł�����.
void clsPlayer::HeadHitToCeiling()
{
	if( m_pXInput == nullptr ) return;
	if( m_fJumpEnagy > 0.0f){
		m_fJumpEnagy = 0.0f;
	}
	else{
		m_fJumpEnagy -= fGRAVITY;
	}
	m_iJumpTimer = iJUNP_TIME_UP_TIME;
	m_bJumpAtkTopFlg = false;
	PlaySe( enPS_HEAD_HIT );
	m_pXInput->SetVibPowerL( usVIB_HEAD_POWER, iVIB_HEAD_TIME );//�U��.
}

//�ʏ�U���J�n.
void clsPlayer::Kick( bool bMovie )
{
	m_enMove = enPM_ATK;
	if( bMovie ) ChangeAnimMode( enANIM_ATK_MOVIE );
	else{
		ChangeAnimMode( enANIM_ATK_ACT );
		PlaySe( enPS_ATK );
		PlayKickEff();
	}
	m_bAtkImpact = true;

}


//�����Ɨ��Ƃ��t���O.
bool clsPlayer::GetJumpAtkImpact()
{
	if( isJumpAtk() ){
		//������.
		if( m_fOldY > m_vPos.y ){
			return true;
		}
	}

	return false;
}


//�Ռ��g�G�t�F�N�g.
void clsPlayer::PlayWaveEff()
{
	if( m_pEffect == nullptr ) return;
	if( !m_pEffect->PlayCheck( m_ehWave ) ){
		D3DXVECTOR3 vEffPos = m_vPos;
		vEffPos.y += fEFFECT_STEP_UP_OFFSET;

		m_ehWave = m_pEffect->Play( clsEffects::enEfcType_WAVE, vEffPos );
		m_pEffect->SetSpd( m_ehWave, fEFFECT_SPD_WAVE );
		m_pEffect->SetScale( m_ehWave, vEFFECT_SCALE_WAVE );

		//���ʂ̑��Ղ�.
		PlayStepEff();
	}
}

//���ՃG�t�F�N�g�Đ�.
void clsPlayer::PlayStepEff()
{
	if( m_pEffect == nullptr ) return;
	for( char i=0; i<iEFFECT_PLAYER_STEP_MAX; i++ ){
		if( !m_pEffect->PlayCheck( m_EffStep[i].ehStep ) ){
			m_EffStep[i].vPos = m_vPos;
			m_EffStep[i].vPos.y += fEFFECT_STEP_UP_OFFSET;

			m_EffStep[i].ehStep = m_pEffect->Play( clsEffects::enEfcType_STEP, m_EffStep[i].vPos );

			break;
		}
	}
}



//�L�b�N�Đ�.
void clsPlayer::PlayKickEff()
{
	if( m_pEffect == nullptr ) return;
	//�L�b�N�G�t�F�N�g.
//	if( !m_pEffect->PlayCheck( m_ehKick ) ){
		D3DXVECTOR3 vEffPos = m_vPos;
		vEffPos.y += fEFFECT_KICK_UP_OFFSET;
		D3DXVECTOR3 vEffRot = m_vRot;
		vEffRot.y += fMODEL_BACK_TURN - static_cast<float>( M_PI_2 );

		m_ehKick = m_pEffect->Play( clsEffects::enEfcType_ARBIA_ATK, vEffPos );

		m_pEffect->SetSpd( m_ehKick, fEFFECT_SPD_KICK );
		m_pEffect->SetScale( m_ehKick, vEFFECT_SCALE_KICK );
		m_pEffect->SetRotation( m_ehKick, vEffRot );
//	}
}



//���C���ȊO.
void clsPlayer::InitTitleScene()
{
	if( m_pShadow == nullptr ) return;
	Spawn();
	ReSpawn();
	m_pShadow->SetShadow( m_vPos, m_fFloorY );
	m_iTitleTimer = 0;
	m_bTitleSpnFlg = false;
	m_bDropout = false;
}


void clsPlayer::MoveTitleScene()
{
	m_iTitleTimer ++;
	//�A���r�A�̓���.
	if( m_iTitleTimer == iTITLE_KICK_START_TIMER ){
		//�L�b�N.
		Kick( true );
	}
	else if( m_iTitleTimer > iTITLE_SPN_START_TIMER ){
		//�N�����Ɖ��.
		//�^�k�������Ă��鎞�͖���.
		if( !m_bTitleSpnFlg ){
			m_fYawTarget += fTITLE_SPN_SPD;
			//����������������.
			if( m_vRot.y < (float)M_PI &&
				m_vRot.y != 0.0f )
			{
				//��]���~�܂�.
				m_vRot.y = (float)M_PI;
				m_bTitleSpnFlg = true;
			}
		}
	}
	Update( m_vPos.z );
}





void clsPlayer::InitOverScene()
{
	m_vPos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_vRot.y = fOVER_INIT_ROT_Y;
	//�|��Ă��郂�[�V����.
	ChangeAnimMode( enANIM_DEAD );
}


void clsPlayer::MoveOverScene()
{
	Animation();
}

void clsPlayer::MoveResultScene()
{
	Update( m_vPos.z );
	Animation();
	if( m_enAnimNo == enANIM_RUNNING_L ){
		m_enAnimNo = enANIM_RUN_END_L;
	}
	else if( m_enAnimNo == enANIM_RUNNING_R ){
		m_enAnimNo = enANIM_RUN_END_R;
	}

}

void clsPlayer::InitEndScene()
{
	Spawn();
	m_pShadow->SetShadow( m_vPos, m_fFloorY );
	//��O������.
	m_vRot.y += static_cast<float>( M_PI );
	m_enMove = enPM_RUN;
	ChangeAnimMode( enANIM_RUNNING_R );

}

void clsPlayer::MoveEndScene( float fRuRange )
{
	Animation();

	//�G�t�F�N�g������.
	for( char i=0; i<iEFFECT_PLAYER_STEP_MAX; i++ ){
		if( m_pEffect->PlayCheck( m_EffStep[i].ehStep ) ){
			m_EffStep[i].vPos.z += fRuRange;
			m_pEffect->SetLocation( m_EffStep[i].ehStep, m_EffStep[i].vPos );
		}
	}
}



//�ړ��⏕.
bool clsPlayer::InputUp  ()
{
	if( m_pXInput == nullptr ) return false;

	if( m_pXInput->IsPressStay( XINPUT_UP ) ) return true;
	if( GetAsyncKeyState( VK_UP ) & 0x8000 ) return true;

	return false;
}
bool clsPlayer::InputDown()
{
	if( m_pXInput == nullptr ) return false;

	if( m_pXInput->IsPressStay( XINPUT_DOWN ) ) return true;
	if( GetAsyncKeyState( VK_DOWN ) & 0x8000 ) return true;

	return false;
}
bool clsPlayer::InputLeft()
{
	if( m_pXInput == nullptr ) return false;

	if( m_pXInput->IsPressStay( XINPUT_LEFT ) ) return true;
	if( GetAsyncKeyState( VK_LEFT ) & 0x8000 ) return true;

	return false;
}
bool clsPlayer::InputRight()
{
	if( m_pXInput == nullptr ) return false;

	if( m_pXInput->IsPressStay( XINPUT_RIGHT ) ) return true;
	if( GetAsyncKeyState( VK_RIGHT ) & 0x8000 ) return true;

	return false;
}






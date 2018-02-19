#include "Enemy.h"

//	//��Ұ���.
//	ChangeAnimSet( (int) );

//----- �� -----//.
//����.
#define ALIAS_NAME_DCOVER "EnemyDiscover"
#define  FILE_PATH_DCOVER "SE\\200Enemy\\300Discover2.wav"
const	  int iVOL_DCOVER = 750;//750.

//�U�肩�Ԃ�.
#define ALIAS_NAME_CHANCE "EnemyChance"
#define  FILE_PATH_CHANCE "SE\\200Enemy\\400Chance3.wav"
const	  int iVOL_CHANCE = 500;//500.

//�X�C���O.
#define ALIAS_NAME_SWING "EnemySwing"
#define  FILE_PATH_SWING "SE\\200Enemy\\500Swing2.wav"
const	  int iVOL_SWING = 1000;

//�o�^�b.
#define ALIAS_NAME_DOWN "EnemyDown"
#define  FILE_PATH_DOWN "SE\\200Enemy\\900Down.wav"
const	  int iVOL_DOWN = 1000;




//===== �����蔻�� =====//.
const float fCOL_ENEMY_RANGE = 0.5f;

const float fCOL_ENEMY_BOX_X = 0.5f / 2.0f;
const float fCOL_ENEMY_BOX_Y = 2.0f;
const float fCOL_ENEMY_BOX_Z = 1.0f / 2.0f;
const float fCOL_ENEMY_BOX_CENTER = 1.0f;

//===== �G����݋��_ =====//.
//===== Box =====//.
const float fCOL_ENEMY_TURN_POS_BOX_X = 0.5f / 2.0f;
const float fCOL_ENEMY_TURN_POS_BOX_Y = 1.0f / 2.0f;
const float fCOL_ENEMY_TURN_POS_BOX_Z = 0.5f / 2.0f;
const float fCOL_ENEMY_TURN_POS_BOX_CENTER = 1.0f;

//===== �G�̍��G,�U�� =====//.
const float fCOL_ENEMY_SUB_HEIGHT = 1.0f;	//����.

const float fCOL_ENEMY_SUB_RANGE_SARCH = 6.0f;		//���G����.
const int iCOL_ENEMY_SUB_THETA_SARCH = 90;			//���G�p�x.

const float fCOL_ENEMY_SUB_RANGE_ATK_START = 1.75f;	//�U���J�n����.
const float fCOL_ENEMY_SUB_RANGE_ATK_AREA = 2.0f;	//�U���͈͋���.
const int iCOL_ENEMY_SUB_THETA_ATK_AREA = 140;		//�U���͈͊p�x. 

const float fENEMY_HEIGHT = 2.0f;
const int iENEMY_SARCH_THETA = 90;
//===== �����蔻�� �I��� =====//.



//������̍L���i�o��ʒu���牜�A��O�ɂ�����H�j.
const float fWORKING_RANGE = 6.0f - 1.0f;//�O��6�}�X���ǂ�������.




//���ق̓s��.
const float fMODEL_BACK_TURN = (float)M_PI;//TestPlusTheta



//���x.
const float fWALK_SPD = 1.0f / 6.5f;
const float fRUN_SPD = 1.0f / 2.0f;
const float fTURN_SPD = 0.1f;

//Timer.
const int iSTOP_TIME = 60;
const int iATK_TIME = 50;
const int iATK_IMPACT_TIME = 25;//30.
const int iRE_DISCOVER_TIME = 30;//�Ĕ����܂ł̎���.


//�G�t�F�N�g.
const float fEFFECT_OFFSET_POS_Y_SLASH = 1.0f;
const D3DXVECTOR3 vEFFECT_SCALE_SLASH = { -0.25f, -0.25f, -0.25f };


clsEnemy::clsEnemy()
{
	m_pCollision = nullptr;
	m_ppSe = nullptr;
	m_pEffect = nullptr;
}

clsEnemy::~clsEnemy()
{
	Release();
}


void clsEnemy::Release()
{
	m_pEffect = nullptr;

	if( m_pShadow != nullptr ){
		delete m_pShadow;
		m_pShadow = nullptr;
	}


	if( m_ppSe != nullptr ){
		for( int i=0; i<enSOUND_MAX; i++ ){
			delete m_ppSe[i];
			m_ppSe[i] = nullptr;
		}
		delete[] m_ppSe;
		m_ppSe = nullptr;
	}

	if( m_pCollision != nullptr ){
		delete m_pCollision;
		m_pCollision = nullptr;
	}
}

void clsEnemy::Create( HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11, int iNo, int jNo )
{
	if( m_pCollision != nullptr ||
		m_pShadow != nullptr ||
		m_ppSe != nullptr ||
		m_pEffect != nullptr )
	{
		return;
	}

	//�����蔻��.
	m_pCollision = new clsCollision;
	//�G�p.
	ColState.vPos = m_vPos;
	ColState.fRange = fCOL_ENEMY_RANGE;
	ColState.fYaw = m_vRot.y;
	ColState.fHeight = fENEMY_HEIGHT;
	ColState.iSarchTheta = iENEMY_SARCH_THETA;

	//Box.
	ColState.vRangeHalf = D3DXVECTOR3( 
		fCOL_ENEMY_BOX_X, fCOL_ENEMY_BOX_Y, fCOL_ENEMY_BOX_Z );
	ColState.fCenterY = fCOL_ENEMY_BOX_CENTER;


	//Sub.
	m_colSub.fRange = fCOL_ENEMY_SUB_RANGE_SARCH;
	m_colSub.fHeight = fCOL_ENEMY_SUB_HEIGHT;
	m_colSub.iSarchTheta = iCOL_ENEMY_SUB_THETA_SARCH;


	//TurnPos.
	for( char i=0; i<TURN_POS_NO_MAX; i++ ){
		m_colTurn[i].vRangeHalf =
			D3DXVECTOR3( fCOL_ENEMY_TURN_POS_BOX_X, fCOL_ENEMY_TURN_POS_BOX_Y, fCOL_ENEMY_TURN_POS_BOX_Z );
		m_colTurn[i].fCenterY = fCOL_ENEMY_TURN_POS_BOX_CENTER;
	}

	//��.
	clsSound::SOUND_DATA tmpSData[enSOUND_MAX] =
	{
		{ ALIAS_NAME_DCOVER,	FILE_PATH_DCOVER,	iVOL_DCOVER	},
		{ ALIAS_NAME_CHANCE,	FILE_PATH_CHANCE,	iVOL_CHANCE	},
		{ ALIAS_NAME_SWING,		FILE_PATH_SWING,	iVOL_SWING	},
		{ ALIAS_NAME_DOWN,		FILE_PATH_DOWN,		iVOL_DOWN	},
	};
	m_ppSe = new clsSound*[enSOUND_MAX];
	for( int i=0; i<enSOUND_MAX; i++ ){
		m_ppSe[i] = new clsSound;
		//�����ʏ�����.
		m_ppSe[i]->SetVolume( 0 );
		//���O.
		char cAliasName[STR_BUFF_MAX] = "";
		strcat_s( cAliasName, sizeof( cAliasName ), tmpSData[i].sAlias );
		//�}�l�[�W���[�ԍ�.
		char cMgrNumber[] = "  ";
		_itoa_s( iNo, cMgrNumber, 10 );
		//���O�Ɣԍ�����.
		strcat_s( cAliasName, sizeof( cAliasName ), cMgrNumber );
		//�̔ԍ�.
		char cCharaNumber[] = "  ";
		_itoa_s( jNo, cCharaNumber, 10 );
		//���O�Ɣԍ�����.
		strcat_s( cAliasName, sizeof( cAliasName ), cCharaNumber );
		//�쐬.
		m_ppSe[i]->Open( tmpSData[i].sPath, cAliasName, hWnd );
		//�ő剹�ʐݒ�.
		m_ppSe[i]->SetMaxVolume( tmpSData[i].iMaxVolume );
	}
	m_pShadow = new clsShadow;
	m_pShadow->Init( pDevice11, pContext11 );

	m_pEffect = clsEffects::GetInstance();


}


void clsEnemy::Init( float fStartZ )
{
	m_bDead = false;
	m_enMove = enEM_WALK;
	m_fSpd = fWALK_SPD;
	m_bWin = false;

	m_fFloorY = m_vPos.y;

	m_iReDiscTimer = 0;

	//������̒��S�_.
	m_fStartZ = fStartZ;

	//Sub.
	m_colSub.fRange = fCOL_ENEMY_SUB_RANGE_SARCH;
	m_colSub.fHeight = fCOL_ENEMY_SUB_HEIGHT;
	m_colSub.iSarchTheta = iCOL_ENEMY_SUB_THETA_SARCH;

	//TurnPos.
	for( int i=0; i<TURN_POS_NO_MAX; i++ ){
		m_colTurn[i].vPos = m_vPos;
	}

	//��Ұ���.
	ChangeAnimMode( enANIM_WALKING );

}


//==================================================
//	�G����.
//==================================================
void clsEnemy::Update( float fEarZ )
{
	m_fEarZ = fEarZ;

	switch( m_enMove )
	{
		case enEM_WALK:
			MoveWalk();
			break;
		case enEM_RUN:
			MoveRun();
			break;
		case enEM_ATK:
			MoveAtk();
			break;
		case enEM_STOP:
			MoveStop();
			break;
		case enEM_DEATH:
			MoveDeath();
			break;
		case enEM_WIN:
			break;
		default:{
			Back();
			break;
		}
	}

	ThetaOverGuard( m_vRot.y );

	//��].
	YawSpnToTarg( m_vRot.y, m_fYawTarget, fTURN_SPD );


	SetSpeed();
	UpdateDir();
	UpDateModel();

	//���W�ړ�.
	UpdatePos();

	//�����蔻��.
	UpdateColState();

	Animation();

	//�e.
	if( m_pShadow == nullptr ) return;
	m_pShadow->SetShadow( m_vPos, m_fFloorY );
}

void clsEnemy::MoveWalk()
{
	if( m_pCollision == nullptr ) return;

	m_enDir = enDirection_Foward;
	//�����ޯĂ�����.
	m_fYawTarget = OpponentDirect( m_vPos, m_colTurn[m_iTarNo].vPos );
	ThetaOverGuard( m_vRot.y );


	//���Pos�Ƃ̂����蔻��.
	for( char i=0; i<TURN_POS_NO_MAX; i++ ){
		if( m_pCollision->HitBox(
			&ColState,
			&m_colTurn[i] ) )
		{
			Turn( i );
		}
	}

	//�A�������̉��ււ̕z��.
	if( m_iReDiscTimer > 0 ){	
		m_iReDiscTimer --;
	}
}
void clsEnemy::MoveRun()
{
	//�����ޯĂ�����.
	m_fYawTarget = OpponentDirect( m_vPos, m_vTargetPos );
	ThetaOverGuard( m_vRot.y );

	//������߂�(������).
	if( isLostRange() ){
		Lost();
	}
}
void clsEnemy::MoveAtk()
{
	m_bAtkImpact = false;//�U���̏u�Ԕ��f�t���O������.
	m_iAtkTimer ++;
	
	//�U���̃C���p�N�g.
	if( m_iAtkTimer == iATK_IMPACT_TIME ){
		m_bAtkImpact = true;
		PlaySe( enSOUND_SWING );
		PlayEff();
	}
}
void clsEnemy::MoveStop()
{
	m_iStopTimer ++;
	if( m_iStopTimer > iSTOP_TIME ){
		Back();
	}
}
//���S�̓���.
void clsEnemy::MoveDeath()
{
}////���S�̓����I���.

//.
void clsEnemy::Turn( int TargetNo )
{
	if( m_iTarNo == TargetNo ){
		m_iTarNo ++;
		if( m_iTarNo >= TURN_POS_NO_MAX ){
			m_iTarNo = 0;
		}
	}
}





//==================================================
//	�ړ��̊p�Z�b�g.
//==================================================
void clsEnemy::SetTurnPos( float x, float z, float SecondX, float SecondZ, bool bReverse, bool bSecond )
{
	//�t��]�p.
	float fRev = 1.0f;
	if( bReverse ){
		fRev = -1.0f;
	}

	//TurnPos.
	for( int i=0; i<TURN_POS_NO_MAX; i++ ){
		m_colTurn[i].vPos = m_vPos;
	}


	// 0 3.
	// 1 2.
	m_colTurn[0].vPos.x -= x * fRev;
	m_colTurn[1].vPos.x -= x * fRev;
	m_colTurn[2].vPos.x += x * fRev;
	m_colTurn[3].vPos.x += x * fRev;
	m_colTurn[0].vPos.x -= SecondX;
	m_colTurn[1].vPos.x -= SecondX;
	m_colTurn[2].vPos.x -= SecondX;
	m_colTurn[3].vPos.x -= SecondX;

	m_colTurn[0].vPos.z += z + SecondZ;
	m_colTurn[1].vPos.z -= z - SecondZ;
	m_colTurn[2].vPos.z -= z - SecondZ;
	m_colTurn[3].vPos.z += z + SecondZ;

	if( bSecond ){
		m_iTarNo = TURN_POS_NO_MAX / 2;
	}
	else{
		m_iTarNo = 0;
	}
	//�ړI�n����������.
	m_vRot.y = OpponentDirect( m_vPos, m_colTurn[m_iTarNo].vPos );

}




//============================================================
//	�ڕW�Ƃ̊p�x.
//============================================================
float clsEnemy::OpponentDirect( D3DXVECTOR3 Attker, D3DXVECTOR3 Target)
{
	float vX, vZ;

	vX = Target.x - Attker.x;
	vZ = Target.z - Attker.z;


	double thetaTar = atan2( (double)-vZ, (double)vX ) + M_PI_2 - fMODEL_BACK_TURN;	//����Ƃ̊p�x.
	ThetaOverGuard( thetaTar );
	return (float)thetaTar;
}



//============================================================
//	���W�R������Update.
//============================================================
void clsEnemy::UpdateDir()
{
	if( m_pModel == nullptr ) return;
	m_pModel->m_enDir = m_enDir;
}




//============================================================
//	����.
//============================================================
bool clsEnemy::Discover( bool bSoundFlg )
{
	//�͈͊O�ł̘A�������h�~.
	if( m_iReDiscTimer > 0 ){
		return false;
	}

	m_enMove = enEM_RUN;
	m_fSpd = fRUN_SPD;

	//Sub(�U���J�n�͈�).
	m_colSub.fRange = fCOL_ENEMY_SUB_RANGE_ATK_START;
	m_colSub.iSarchTheta = iCOL_ENEMY_SUB_THETA_ATK_AREA;

	//��Ұ���.
	ChangeAnimMode( enANIM_RUNING );

	if( bSoundFlg ){
		PlaySe( enSOUND_DCOVER );
	}
	
	return true;
}

//============================================================
//	�߂�.
//============================================================
void clsEnemy::Back()
{
	if( m_pCollision == nullptr ) return;

	m_enMove = enEM_WALK;
	m_fSpd = fWALK_SPD;

	//Sub.
	m_colSub.fRange = fCOL_ENEMY_SUB_RANGE_SARCH;
	m_colSub.iSarchTheta = iCOL_ENEMY_SUB_THETA_SARCH;

	//��ԋ߂��߲�Ă�T��.
	float fRange = m_pCollision->LengthComp( m_vPos, m_colTurn[0].vPos );
	m_iTarNo = 0;
	for( char i=1; i<TURN_POS_NO_MAX; i++ )
	{
		if( fRange > m_pCollision->LengthComp( m_vPos, m_colTurn[i].vPos ) )
		{
			fRange = m_pCollision->LengthComp( m_vPos, m_colTurn[i].vPos );
			m_iTarNo = i;
		}
	}

	//��Ұ���.
	ChangeAnimMode( enANIM_WALKING );
}
//============================================================
//	������.
//============================================================
void clsEnemy::Lost()
{
	m_enMove = enEM_STOP;
	m_fSpd = 0.0f;

	m_iReDiscTimer = iRE_DISCOVER_TIME;

	m_iStopTimer = 0;

	//��Ұ���.
	ChangeAnimMode( enANIM_IDLE );
}



//============================================================
//	�U��.
//============================================================
void clsEnemy::Attack()
{
	m_enMove = enEM_ATK;
	m_fSpd = 0.0f;
	m_iAtkTimer = 0;

	//Sub.
	m_colSub.fRange = fCOL_ENEMY_SUB_RANGE_ATK_AREA;
	m_colSub.iSarchTheta = iCOL_ENEMY_SUB_THETA_ATK_AREA;

	//��Ұ���.
	ChangeAnimMode( enANIM_ATK );

	PlaySe( enSOUND_CHANCE );

}

//============================================================
//	����.
//============================================================
void clsEnemy::Win()
{
	m_bWin = true;
}
//============================================================
//	������.
//============================================================
void clsEnemy::Winner()
{
	m_enMove = enEM_WIN;
	m_fSpd = 0.0f;

	//��Ұ���.
	ChangeAnimMode( enANIM_WIN );
}

//==================================================
//	���S����.
//==================================================
void clsEnemy::Dead( bool FlgPlayerJumpAtk )
{
	m_bDead = true;
	m_enMove = enEM_DEATH;
	m_fSpd = 0.0f;

	//��Ұ���.
	ChangeAnimMode( enANIM_DEAD );
}



//============================================================
//	�����������̔����𔻒肷��.
//============================================================
bool clsEnemy::isLostRange()
{
	//������͈̔͊O.
	if( m_vPos.z > m_fStartZ + fWORKING_RANGE ||
		m_vPos.z < m_fStartZ - fWORKING_RANGE )
	{
		return true;
	}

	return false;
}






//============================================================
//	Ѱ�ނ̍Ō�Ɏg��.
//============================================================
void clsEnemy::UpdateColState()
{
	ColState.vPos = m_vPos;
	ColState.fYaw = m_vRot.y;

	//Sub�����蔻��.
	m_colSub.vPos = m_vPos;
	m_colSub.fYaw = m_vRot.y;
}


//�A�j���[�V����.
void clsEnemy::Animation()
{
	if( m_pModel == nullptr ) return;

	//���[�v���Ȃ����[�V����.
	if( m_enAnimNo == enANIM_ATK ||
		m_enAnimNo == enANIM_DEAD ||
		m_enAnimNo == enANIM_HAND_OUT )
	{
		//�A�j���[�V�������ԉ��Z.
		m_dAnimTimer += m_pModel->GetAnimSpeed();
	}


	//���݂̃A�j���[�V�������I������.
	if( m_pModel->GetAnimPeriod( m_enAnimNo ) - ( dANIM_ONE_FRAME_OVER_SOLUTION * (double)( m_enAnimNo * m_enAnimNo ) ) <= m_dAnimTimer )
	{
		//���[�v���Ȃ����[�V����.
		switch( m_enAnimNo )
		{
		//�U���I��.
		case enANIM_ATK:
			if( m_bWin )Winner();
			else		Discover( false );		
			break;
		//�����.
		case enANIM_DEAD:
			ChangeAnimMode( enANIM_HAND_OUT );
			PlaySe( enSOUND_DOWN );
			break;
		//�肪������.
		case enANIM_HAND_OUT:
			ChangeAnimMode( enANIM_LOSE );
			break;
		}	
	}
}

//============================================================
//	�A�j���[�V�������[�h��ύX.
//============================================================
void clsEnemy::ChangeAnimMode( enAnimation anim ){
	m_enAnimNo = anim;
	ChangeAnimSet( m_enAnimNo );//�A�j���Z�b�g.
	m_dAnimTimer = 0.0;
}


//���ʉ��Đ�.
void clsEnemy::PlaySe( enSound enSe )
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

//�G�t�F�N�g�Đ�.
void clsEnemy::PlayEff()
{
	if( m_pEffect == nullptr ) return;

	D3DXVECTOR3 vEffPos = m_vPos;
	vEffPos.y += fEFFECT_OFFSET_POS_Y_SLASH;
	D3DXVECTOR3 vEffRot = m_vRot;
	vEffRot.y += fMODEL_BACK_TURN - static_cast<float>( M_PI_2 );

	m_ehSlash = m_pEffect->Play( clsEffects::enEfcType_ENEMY_ATK, vEffPos );
	m_pEffect->SetScale( m_ehSlash, vEFFECT_SCALE_SLASH );
	m_pEffect->SetRotation( m_ehSlash, vEffRot );
}

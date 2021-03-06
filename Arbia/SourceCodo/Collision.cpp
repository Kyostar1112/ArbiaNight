#define _USE_MATH_DEFINES
#include <math.h>

#include "Collision.h"
#include "CollisionRay.h"


//----- 音 -----//.
//----- アルビア.
//キック.
#define ALIAS_NAME_ARBIA_KICK "ColArbiaKick"
#define  FILE_PATH_ARBIA_KICK "SE\\500Collider\\100ArbiaKickHit.wav"
const	  int iVOL_ARBIA_KICK = 1000;

//ジャンプ攻撃.
#define ALIAS_NAME_ARBIA_JATK "ColArbiaJumpAtk"
#define  FILE_PATH_ARBIA_JATK "SE\\500Collider\\110ArbiaJumpAtkHit.wav"
const	  int iVOL_ARBIA_JATK = 1000;

//衝突.
#define ALIAS_NAME_ENEMY_HIT "ColEnemyHit"
#define  FILE_PATH_ENEMY_HIT "SE\\500Collider\\200EnemyHit3.wav"
const	  int iVOL_ENEMY_HIT = 1000;

//剣.
#define ALIAS_NAME_ENEMY_SRASH "ColEnemySrash"
#define  FILE_PATH_ENEMY_SRASH "SE\\500Collider\\210EnemySrashHit.wav"
const	  int iVOL_ENEMY_SRASH = 1000;

//槍.
#define ALIAS_NAME_SPIA "ColSpia"
#define  FILE_PATH_SPIA "SE\\500Collider\\300SpiaHit2.wav"
const	  int iVOL_SPIA = 1000;

//ペンデュラム.
#define ALIAS_NAME_PEND "ColPendulum"
#define  FILE_PATH_PEND "SE\\500Collider\\400PendHit.wav"
const	  int iVOL_PEND = 1000;

//落下.
#define ALIAS_NAME_DROP_DOWN "ColDropDown"
#define  FILE_PATH_DROP_DOWN "SE\\500Collider\\900DropDown.wav"
const	  int iVOL_DROP_DOWN = 250;//250.




//ﾓﾃﾞﾙの都合.
const float fMODEL_BACK_TURN = (float)M_PI;//TestPlusTheta

//回転値の上限.
#define THETA_MAX static_cast<float>( M_PI * 2.0 )



clsCollision::clsCollision()
{
	m_pRay = new clsCollisionRay;
	m_ppSe = nullptr;
}

clsCollision::~clsCollision()
{
	Release();
}

void clsCollision::Release()
{
	if( m_ppSe != nullptr ){
		for( int i=0; i<enSOUND_MAX; i++ ){
			delete m_ppSe[i];
			m_ppSe[i] = nullptr;
		}
		delete[] m_ppSe;
		m_ppSe = nullptr;
	}


	if( m_pRay != nullptr ){
		delete m_pRay;
		m_pRay = nullptr;
	}
}




//BOXのあたり判定.
bool clsCollision::HitBox( COL_STATE* Attker, COL_STATE* Target )
{
	if( Attker->vPos.z + Attker->vRangeHalf.z > Target->vPos.z - Target->vRangeHalf.z &&
		Attker->vPos.z - Attker->vRangeHalf.z < Target->vPos.z + Target->vRangeHalf.z )
	{
		float attkerPosY = Attker->vPos.y + Attker->fCenterY;
		float TargetPosY = Target->vPos.y + Target->fCenterY;
		if(	attkerPosY + Attker->vRangeHalf.y > TargetPosY - Target->vRangeHalf.y &&
			attkerPosY - Attker->vRangeHalf.y < TargetPosY + Target->vRangeHalf.y )
		{
			float attkerPosX = Attker->vPos.x + Attker->fCenterX;
			float TargetPosX = Target->vPos.x + Target->fCenterX;
			if( attkerPosX + Attker->vRangeHalf.x > TargetPosX - Target->vRangeHalf.x &&
				attkerPosX - Attker->vRangeHalf.x < TargetPosX + Target->vRangeHalf.x )
			{
				return true;
			}
		}
	}

	return false;
}



//============================================================
//	対象との距離を算出する.
//============================================================
float clsCollision::LengthComp( D3DXVECTOR3 Attker, D3DXVECTOR3 Target )
{
	float vX, vZ, LengthA_T;

	vX = Target.x - Attker.x;
	vZ = Target.z - Attker.z;

	vX *= vX;
	vZ *= vZ;

	LengthA_T = sqrtf( vX + vZ );

	return LengthA_T;
}

////============================================================
//	円柱.
////============================================================
bool clsCollision::HitCylind( COL_STATE* Attacker, COL_STATE* Target )
{
	//高さが同じ前提.
	if( Attacker->vPos.y					 < Target->vPos.y + Target->fHeight &&
		Attacker->vPos.y + Attacker->fHeight > Target->vPos.y )
	{
		//円.
		if( LengthComp( Attacker->vPos, Target->vPos ) <= Attacker->fRange + Target->fRange ){
			return true;
		}
	}
	return false;
}

//============================================================
//	目標との角度.
//============================================================
float clsCollision::SetTarYaw( D3DXVECTOR3 Attker, D3DXVECTOR3 Target)
{
	float vX, vZ;

	vX = Target.x - Attker.x;
	vZ = Target.z - Attker.z;


	double thetaTar = atan2( (double)-vZ, (double)vX ) + M_PI_2 - fMODEL_BACK_TURN;	//相手との角度.
	ThetaOverGuard( thetaTar );
	return (float)thetaTar;
}

////============================================================
//	角度判定.
////============================================================
bool clsCollision::ThetaCheck( double dMyTheta, double dTargTheta,
								int iSarchTheta )
{
	double d_thetaArea_h = (double)iSarchTheta / 180.0 * M_PI / 2.0;
	double thetaSearchR, thetaSearchL;
	thetaSearchR = dMyTheta - d_thetaArea_h;
	thetaSearchL = dMyTheta + d_thetaArea_h;

	//角度が合っていたら.
	if( thetaSearchL > dTargTheta &&
		thetaSearchR < dTargTheta )
	{
		return true;
	}
	////一周対策(0と360の境目).
	else{
		if( dMyTheta < dTargTheta ){
			dTargTheta -= M_PI * 2.0;
			if( thetaSearchL > dTargTheta &&
				thetaSearchR < dTargTheta )
			{
				return true;
			}
		}
		else if( dMyTheta > dTargTheta ){
			dTargTheta += M_PI * 2.0;
			if( thetaSearchL > dTargTheta &&
				thetaSearchR < dTargTheta )
			{
				return true;
			}
		}
	}

	return false;
}

////============================================================
//	扇形ﾁｪｯｸ.
////============================================================
bool clsCollision::HitSect( COL_STATE* Attacker, COL_STATE* Target )
{
	float vX, vZ, R;

	vX = Target->vPos.x - Attacker->vPos.x;
	vZ = Target->vPos.z - Attacker->vPos.z;


	R = Attacker->fRange;


	//円柱.
	if( HitCylind( Attacker, Target ) )
	{
		//角度の割り出し.
		double thetaAtt = (double)Attacker->fYaw - fMODEL_BACK_TURN;	//攻撃者の角度.
		ThetaOverGuard( thetaAtt );

		double thetaTar = atan2( (double)( -vZ ), (double)vX ) + M_PI_2;	//相手との角度.
		ThetaOverGuard( thetaTar );

		//角度判定.
		if( ThetaCheck( thetaAtt, thetaTar, Attacker->iSarchTheta ) ){
			return true;
		}//角度判定終わり.
	}//円判定終わり.

	return false;
}




//============================================================
//	360〜0に納める.
//============================================================
void clsCollision::ThetaOverGuard( float& theta )
{
	if( theta > THETA_MAX ){
		theta -= THETA_MAX;
	}
	else if( theta < 0.0f ){
		theta += THETA_MAX;
	}
}
void clsCollision::ThetaOverGuard( double& theta )
{
	if( theta > THETA_MAX ){
		theta -= THETA_MAX;
	}
	else if( theta < 0.0 ){
		theta += THETA_MAX;
	}
}


//============================================================
//	壁のあたり判定ﾗｯﾌﾟ.
//============================================================
void clsCollision::WallJudge( clsCharaSkin* pWalker, clsCharaStatic* pWall )
{
	m_pRay->WallJudge( pWalker, pWall );
}



//============================================================
//	床のあたり判定ﾗｯﾌﾟ.
//============================================================
bool clsCollision::FloorJudge( 
	clsCharaSkin* pWalker, 
	float fRange,
	float& fLandY,
	clsCharaStatic* pFloor,
	bool& bFlg )
{
	bool bJudgeflg;
	bool bGround;
	bJudgeflg = m_pRay->FloorJudge( pWalker, fRange, fLandY, pFloor, bGround );
	bFlg = bGround;
	return bJudgeflg;
}

//============================================================
//	天井との判定.
//============================================================
bool clsCollision::CeilingJudge( 
	clsCharaSkin* pWalker, 
	float fWalkerHeight,
	clsCharaStatic* pFloor )
{
	bool bReturn = m_pRay->CeilingJudge( pWalker, fWalkerHeight, pFloor );
	return bReturn;
}


//効果音再生.
void clsCollision::PlaySe( enSound enSe )
{
	if( m_ppSe == nullptr ){
		return;
	}
	int vol = 1000;
	m_ppSe[enSe]->GetMaxVolRate( vol );
	m_ppSe[enSe]->SeekToStart();
	m_ppSe[enSe]->SetVolume( vol );
	m_ppSe[enSe]->Play();
}


void clsCollision::CreateSe( HWND hWnd )
{
	if( m_ppSe != nullptr ) return;

	clsSound::SOUND_DATA tmpSData[enSOUND_MAX] =
	{
		{ ALIAS_NAME_ARBIA_KICK,	FILE_PATH_ARBIA_KICK,	iVOL_ARBIA_KICK	},
		{ ALIAS_NAME_ARBIA_JATK,	FILE_PATH_ARBIA_JATK,	iVOL_ARBIA_JATK	},
		{ ALIAS_NAME_ENEMY_HIT,		FILE_PATH_ENEMY_HIT,	iVOL_ENEMY_HIT	},
		{ ALIAS_NAME_ENEMY_SRASH,	FILE_PATH_ENEMY_SRASH,	iVOL_ENEMY_SRASH},
		{ ALIAS_NAME_SPIA,			FILE_PATH_SPIA,			iVOL_SPIA		},
		{ ALIAS_NAME_PEND,			FILE_PATH_PEND,			iVOL_PEND		},
		{ ALIAS_NAME_DROP_DOWN,		FILE_PATH_DROP_DOWN,	iVOL_DROP_DOWN	},
	};
	m_ppSe = new clsSound*[enSOUND_MAX];
	for( int i=0; i<enSOUND_MAX; i++ ){
		m_ppSe[i] = new clsSound;
		//現音量初期化.
		m_ppSe[i]->SetVolume( 0 );
		//名前.
		char cAliasName[STR_BUFF_MAX] = "";
		strcat_s( cAliasName, sizeof( cAliasName ), tmpSData[i].sAlias );
//		//番号.
//		char cNumber[] = "  ";
//		_itoa_s( iNo, cNumber, 10 );
//		//名前と番号合体.
//		strcat_s( cAliasName, sizeof( cAliasName ), cNumber );
		//作成.
		m_ppSe[i]->Open( tmpSData[i].sPath, cAliasName, hWnd );
		//最大音量設定.
		m_ppSe[i]->SetMaxVolume( tmpSData[i].iMaxVolume );
	}
}



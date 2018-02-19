#include "Enemy.h"

//	//ｱﾆﾒｰｼｮﾝ.
//	ChangeAnimSet( (int) );

//----- 音 -----//.
//発見.
#define ALIAS_NAME_DCOVER "EnemyDiscover"
#define  FILE_PATH_DCOVER "SE\\200Enemy\\300Discover2.wav"
const	  int iVOL_DCOVER = 750;//750.

//振りかぶり.
#define ALIAS_NAME_CHANCE "EnemyChance"
#define  FILE_PATH_CHANCE "SE\\200Enemy\\400Chance3.wav"
const	  int iVOL_CHANCE = 500;//500.

//スイング.
#define ALIAS_NAME_SWING "EnemySwing"
#define  FILE_PATH_SWING "SE\\200Enemy\\500Swing2.wav"
const	  int iVOL_SWING = 1000;

//バタッ.
#define ALIAS_NAME_DOWN "EnemyDown"
#define  FILE_PATH_DOWN "SE\\200Enemy\\900Down.wav"
const	  int iVOL_DOWN = 1000;




//===== あたり判定 =====//.
const float fCOL_ENEMY_RANGE = 0.5f;

const float fCOL_ENEMY_BOX_X = 0.5f / 2.0f;
const float fCOL_ENEMY_BOX_Y = 2.0f;
const float fCOL_ENEMY_BOX_Z = 1.0f / 2.0f;
const float fCOL_ENEMY_BOX_CENTER = 1.0f;

//===== 敵のﾀｰﾝ拠点 =====//.
//===== Box =====//.
const float fCOL_ENEMY_TURN_POS_BOX_X = 0.5f / 2.0f;
const float fCOL_ENEMY_TURN_POS_BOX_Y = 1.0f / 2.0f;
const float fCOL_ENEMY_TURN_POS_BOX_Z = 0.5f / 2.0f;
const float fCOL_ENEMY_TURN_POS_BOX_CENTER = 1.0f;

//===== 敵の索敵,攻撃 =====//.
const float fCOL_ENEMY_SUB_HEIGHT = 1.0f;	//高さ.

const float fCOL_ENEMY_SUB_RANGE_SARCH = 6.0f;		//索敵距離.
const int iCOL_ENEMY_SUB_THETA_SARCH = 90;			//索敵角度.

const float fCOL_ENEMY_SUB_RANGE_ATK_START = 1.75f;	//攻撃開始距離.
const float fCOL_ENEMY_SUB_RANGE_ATK_AREA = 2.0f;	//攻撃範囲距離.
const int iCOL_ENEMY_SUB_THETA_ATK_AREA = 140;		//攻撃範囲角度. 

const float fENEMY_HEIGHT = 2.0f;
const int iENEMY_SARCH_THETA = 90;
//===== あたり判定 終わり =====//.



//持ち場の広さ（登場位置から奥、手前にいくら？）.
const float fWORKING_RANGE = 6.0f - 1.0f;//前後6マス分追いかける.




//ﾓﾃﾞﾙの都合.
const float fMODEL_BACK_TURN = (float)M_PI;//TestPlusTheta



//速度.
const float fWALK_SPD = 1.0f / 6.5f;
const float fRUN_SPD = 1.0f / 2.0f;
const float fTURN_SPD = 0.1f;

//Timer.
const int iSTOP_TIME = 60;
const int iATK_TIME = 50;
const int iATK_IMPACT_TIME = 25;//30.
const int iRE_DISCOVER_TIME = 30;//再発見までの時間.


//エフェクト.
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

	//当たり判定.
	m_pCollision = new clsCollision;
	//敵用.
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

	//音.
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
		//現音量初期化.
		m_ppSe[i]->SetVolume( 0 );
		//名前.
		char cAliasName[STR_BUFF_MAX] = "";
		strcat_s( cAliasName, sizeof( cAliasName ), tmpSData[i].sAlias );
		//マネージャー番号.
		char cMgrNumber[] = "  ";
		_itoa_s( iNo, cMgrNumber, 10 );
		//名前と番号合体.
		strcat_s( cAliasName, sizeof( cAliasName ), cMgrNumber );
		//個体番号.
		char cCharaNumber[] = "  ";
		_itoa_s( jNo, cCharaNumber, 10 );
		//名前と番号合体.
		strcat_s( cAliasName, sizeof( cAliasName ), cCharaNumber );
		//作成.
		m_ppSe[i]->Open( tmpSData[i].sPath, cAliasName, hWnd );
		//最大音量設定.
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

	//持ち場の中心点.
	m_fStartZ = fStartZ;

	//Sub.
	m_colSub.fRange = fCOL_ENEMY_SUB_RANGE_SARCH;
	m_colSub.fHeight = fCOL_ENEMY_SUB_HEIGHT;
	m_colSub.iSarchTheta = iCOL_ENEMY_SUB_THETA_SARCH;

	//TurnPos.
	for( int i=0; i<TURN_POS_NO_MAX; i++ ){
		m_colTurn[i].vPos = m_vPos;
	}

	//ｱﾆﾒｰｼｮﾝ.
	ChangeAnimMode( enANIM_WALKING );

}


//==================================================
//	敵動き.
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

	//回転.
	YawSpnToTarg( m_vRot.y, m_fYawTarget, fTURN_SPD );


	SetSpeed();
	UpdateDir();
	UpDateModel();

	//座標移動.
	UpdatePos();

	//あたり判定.
	UpdateColState();

	Animation();

	//影.
	if( m_pShadow == nullptr ) return;
	m_pShadow->SetShadow( m_vPos, m_fFloorY );
}

void clsEnemy::MoveWalk()
{
	if( m_pCollision == nullptr ) return;

	m_enDir = enDirection_Foward;
	//自ﾀｰｹﾞｯﾄを向く.
	m_fYawTarget = OpponentDirect( m_vPos, m_colTurn[m_iTarNo].vPos );
	ThetaOverGuard( m_vRot.y );


	//ﾀｰﾝPosとのあたり判定.
	for( char i=0; i<TURN_POS_NO_MAX; i++ ){
		if( m_pCollision->HitBox(
			&ColState,
			&m_colTurn[i] ) )
		{
			Turn( i );
		}
	}

	//連続発見の解禁への布石.
	if( m_iReDiscTimer > 0 ){	
		m_iReDiscTimer --;
	}
}
void clsEnemy::MoveRun()
{
	//自ﾀｰｹﾞｯﾄを向く.
	m_fYawTarget = OpponentDirect( m_vPos, m_vTargetPos );
	ThetaOverGuard( m_vRot.y );

	//あきらめる(見失い).
	if( isLostRange() ){
		Lost();
	}
}
void clsEnemy::MoveAtk()
{
	m_bAtkImpact = false;//攻撃の瞬間判断フラグ初期化.
	m_iAtkTimer ++;
	
	//攻撃のインパクト.
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
//死亡の動き.
void clsEnemy::MoveDeath()
{
}////死亡の動き終わり.

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
//	移動の角セット.
//==================================================
void clsEnemy::SetTurnPos( float x, float z, float SecondX, float SecondZ, bool bReverse, bool bSecond )
{
	//逆回転用.
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
	//目的地を向かせる.
	m_vRot.y = OpponentDirect( m_vPos, m_colTurn[m_iTarNo].vPos );

}




//============================================================
//	目標との角度.
//============================================================
float clsEnemy::OpponentDirect( D3DXVECTOR3 Attker, D3DXVECTOR3 Target)
{
	float vX, vZ;

	vX = Target.x - Attker.x;
	vZ = Target.z - Attker.z;


	double thetaTar = atan2( (double)-vZ, (double)vX ) + M_PI_2 - fMODEL_BACK_TURN;	//相手との角度.
	ThetaOverGuard( thetaTar );
	return (float)thetaTar;
}



//============================================================
//	ラジコン操作Update.
//============================================================
void clsEnemy::UpdateDir()
{
	if( m_pModel == nullptr ) return;
	m_pModel->m_enDir = m_enDir;
}




//============================================================
//	発見.
//============================================================
bool clsEnemy::Discover( bool bSoundFlg )
{
	//範囲外での連続発見防止.
	if( m_iReDiscTimer > 0 ){
		return false;
	}

	m_enMove = enEM_RUN;
	m_fSpd = fRUN_SPD;

	//Sub(攻撃開始範囲).
	m_colSub.fRange = fCOL_ENEMY_SUB_RANGE_ATK_START;
	m_colSub.iSarchTheta = iCOL_ENEMY_SUB_THETA_ATK_AREA;

	//ｱﾆﾒｰｼｮﾝ.
	ChangeAnimMode( enANIM_RUNING );

	if( bSoundFlg ){
		PlaySe( enSOUND_DCOVER );
	}
	
	return true;
}

//============================================================
//	戻る.
//============================================================
void clsEnemy::Back()
{
	if( m_pCollision == nullptr ) return;

	m_enMove = enEM_WALK;
	m_fSpd = fWALK_SPD;

	//Sub.
	m_colSub.fRange = fCOL_ENEMY_SUB_RANGE_SARCH;
	m_colSub.iSarchTheta = iCOL_ENEMY_SUB_THETA_SARCH;

	//一番近いﾎﾟｲﾝﾄを探す.
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

	//ｱﾆﾒｰｼｮﾝ.
	ChangeAnimMode( enANIM_WALKING );
}
//============================================================
//	見失う.
//============================================================
void clsEnemy::Lost()
{
	m_enMove = enEM_STOP;
	m_fSpd = 0.0f;

	m_iReDiscTimer = iRE_DISCOVER_TIME;

	m_iStopTimer = 0;

	//ｱﾆﾒｰｼｮﾝ.
	ChangeAnimMode( enANIM_IDLE );
}



//============================================================
//	攻撃.
//============================================================
void clsEnemy::Attack()
{
	m_enMove = enEM_ATK;
	m_fSpd = 0.0f;
	m_iAtkTimer = 0;

	//Sub.
	m_colSub.fRange = fCOL_ENEMY_SUB_RANGE_ATK_AREA;
	m_colSub.iSarchTheta = iCOL_ENEMY_SUB_THETA_ATK_AREA;

	//ｱﾆﾒｰｼｮﾝ.
	ChangeAnimMode( enANIM_ATK );

	PlaySe( enSOUND_CHANCE );

}

//============================================================
//	勝利.
//============================================================
void clsEnemy::Win()
{
	m_bWin = true;
}
//============================================================
//	勝利者.
//============================================================
void clsEnemy::Winner()
{
	m_enMove = enEM_WIN;
	m_fSpd = 0.0f;

	//ｱﾆﾒｰｼｮﾝ.
	ChangeAnimMode( enANIM_WIN );
}

//==================================================
//	死亡処理.
//==================================================
void clsEnemy::Dead( bool FlgPlayerJumpAtk )
{
	m_bDead = true;
	m_enMove = enEM_DEATH;
	m_fSpd = 0.0f;

	//ｱﾆﾒｰｼｮﾝ.
	ChangeAnimMode( enANIM_DEAD );
}



//============================================================
//	見失う処理の発動を判定する.
//============================================================
bool clsEnemy::isLostRange()
{
	//持ち場の範囲外.
	if( m_vPos.z > m_fStartZ + fWORKING_RANGE ||
		m_vPos.z < m_fStartZ - fWORKING_RANGE )
	{
		return true;
	}

	return false;
}






//============================================================
//	ﾑｰﾌﾞの最後に使う.
//============================================================
void clsEnemy::UpdateColState()
{
	ColState.vPos = m_vPos;
	ColState.fYaw = m_vRot.y;

	//Subあたり判定.
	m_colSub.vPos = m_vPos;
	m_colSub.fYaw = m_vRot.y;
}


//アニメーション.
void clsEnemy::Animation()
{
	if( m_pModel == nullptr ) return;

	//ループしないモーション.
	if( m_enAnimNo == enANIM_ATK ||
		m_enAnimNo == enANIM_DEAD ||
		m_enAnimNo == enANIM_HAND_OUT )
	{
		//アニメーション時間加算.
		m_dAnimTimer += m_pModel->GetAnimSpeed();
	}


	//現在のアニメーションを終えたら.
	if( m_pModel->GetAnimPeriod( m_enAnimNo ) - ( dANIM_ONE_FRAME_OVER_SOLUTION * (double)( m_enAnimNo * m_enAnimNo ) ) <= m_dAnimTimer )
	{
		//ループしないモーション.
		switch( m_enAnimNo )
		{
		//攻撃終了.
		case enANIM_ATK:
			if( m_bWin )Winner();
			else		Discover( false );		
			break;
		//やられる.
		case enANIM_DEAD:
			ChangeAnimMode( enANIM_HAND_OUT );
			PlaySe( enSOUND_DOWN );
			break;
		//手が落ちる.
		case enANIM_HAND_OUT:
			ChangeAnimMode( enANIM_LOSE );
			break;
		}	
	}
}

//============================================================
//	アニメーションモードを変更.
//============================================================
void clsEnemy::ChangeAnimMode( enAnimation anim ){
	m_enAnimNo = anim;
	ChangeAnimSet( m_enAnimNo );//アニメセット.
	m_dAnimTimer = 0.0;
}


//効果音再生.
void clsEnemy::PlaySe( enSound enSe )
{
	if( m_ppSe == nullptr ) return;

	//再生する距離なら.
	int vol = ChangeVolumeDistance( m_fEarZ, m_vPos.z );
	if( vol ){
		m_ppSe[enSe]->GetMaxVolRate( vol );
		m_ppSe[enSe]->SeekToStart();
		m_ppSe[enSe]->SetVolume( vol );
		m_ppSe[enSe]->Play();
	}
	//再生しない距離なら.
	else{
		m_ppSe[enSe]->SetVolume( 0 );
	}
}

//エフェクト再生.
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

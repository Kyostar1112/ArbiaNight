#ifndef _C_PLAYER_H_
#define _C_PLAYER_H_


#include "CharaSkin.h"
#include "Sound.h"
#include "CXInput.h"
#include "Effects.h"


const int iEFFECT_PLAYER_STEP_MAX = 4;

struct EFF_STEP
{
	::Effekseer::Handle		ehStep;//足跡.
	D3DXVECTOR3				vPos;
};



class clsPlayer
	: public clsCharaSkin
{
public:
	clsPlayer();
	~clsPlayer();

	//自機動きの種類.
	enum enPLAYER_MOVE
	{
		enPM_IDLE	= 0,//停止.
		enPM_RUN,		//走り.
		enPM_ATK,		//攻撃.
		enPM_JUM_ATK,	//ｼﾞｬﾝﾌﾟ攻撃.
		enPM_DEAD		//ﾐｽ.
	};//m_enMove

	void Create( HWND hWnd, 
		ID3D11Device* pDevice11, 
		ID3D11DeviceContext* pContext11,
		clsXInput* pXinput );
	virtual void Init();


	COL_STATE* GetPointerSubCol(){
		return &m_colSub;
	}

	//ラジコン操作Update.
	void UpdateDir();

	void Input();

	void Update( float fEarZ );

	void Rerease();

	void Dead();

	//ジャンプ開始.
	void SetJump( bool bDropout = false );

	//ステージスタート.
	void Spawn();
	//復活.
	void ReSpawn();
	//復活地点更新.
	void UpdateReSpawnPos( D3DXVECTOR3 vPos ){
		m_vReSpawnPos = vPos;
	}




	//Getｼﾘｰｽﾞ.
	bool GetDead(){
		return m_bDead;
	}
	bool GetDirNorth(){
		return m_bDirNorth;
	}
	//床とのあたり判定用.
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


	//カメラが見上げる?(ジャンプ攻撃中なら見上げる).
	bool isCamLookUp(){
		if( m_enMove == enPM_JUM_ATK ){
			return true;
		}
		return false;
	}

	//攻撃の瞬間フラグを返す.
	bool GetAttackImpact(){
		return m_bAtkImpact;
	}


	//背の高さを返す（天井のあたり判定用）.
	float GetHeight();//const float COL_PLAYER_H  = 2.0f;.
	//天井に頭を打ったら.
	void HeadHitToCeiling();

	//残機.
	int GetHp(){
		return m_iHp;
	}

	//かかと落とし中フラグ返す.
	bool isJumpAtk(){
		if( m_enMove == enPM_JUM_ATK ){
			return true;
		}
		return false;
	}
	//かかと落とし降下中フラグ.
	bool GetJumpAtkImpact();



	//メイン以外.
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


	//通常攻撃開始.
	void Kick( bool bMovie = false );

	virtual void UpdateColState();//ﾑｰﾌﾞの最後に使う.

	//減速関数.
	void Deceleration();


	//子分.
	void Input_Walk();
	void Input_Action();
	void Input_ActionJump();
	void Input_ActionAtk();

	void MoveWalk();
	void MoveAction();
	void MoveActionJump();
	void MoveActionAtk();


	clsXInput* m_pXInput;

	//ｷｯｸ範囲.
	COL_STATE	m_colSub;	//索敵,攻撃範囲.

	enPLAYER_MOVE m_enMove;

	bool	m_bDead;
	bool	m_bJump;//jump.
	bool	m_bLanding;//陸地か否か.

	float	m_fJumpEnagy;//j_energy.

	int		m_iJumpTimer;//Player_JumpTimer

	bool	m_bJumpAtkTopFlg;//頂点でしか発動しない.
	bool	m_bJumpSpdDown;//ジャンプ中に減速してよいか.

	bool	m_bDirNorth;//北向きﾌﾗｸﾞ.

	D3DXVECTOR3 m_vReSpawnPos;//復活地点.

	int		m_iHp;//残機数.

	float	m_fOldY;



	//走りアニメーション用フラグ.
	bool	m_bRunning;//走っているか否か.
	bool	m_bAtkImpact;//攻撃の瞬間.



	//ｱﾆﾒｰｼｮﾝ番号.
	enum enAnimation
	{
		enANIM_IDLE = 0,

		enANIM_RUN_START,	//右足スタート.
		enANIM_RUNNING_R,	//右足が前に出ている.
		enANIM_RUNNING_L,
		enANIM_RUN_END_R,	//enANIM_RUNNING_Rからつなぐ.
		enANIM_RUN_END_L,	//enANIM_RUNNING_Lからつなぐ.

		enANIM_JUMP_START,	
		enANIM_JUMP_UP,		//上昇.
		enANIM_JUMP_U_TURN,	//上下運動エネルギーの転換.
		enANIM_JUMP_FALL,	//下降.
		enANIM_JUMP_STMP,	//着地着地時に移動を入力してるなら再生されない(走りモーションに行く).

		enANIM_ATK_MOVIE,
		enANIM_ATK_ACT,

		enANIM_JUMP_ATK_SPN,	//空中回転.
		enANIM_JUMP_ATK_FALL,	//落下.
		enANIM_JUMP_ATK_STMP,	//着地.
		enANIM_JUMP_ATK_STND,	//起き上がり.

		enANIM_DEAD,//倒れる.
		enANIM_LOSE,//倒れてる（ 倒れ終わった{ 不動 } ）.

		enANIM_MAX 	//最大.
	};

	enAnimation m_enAnimNo;
	void Animation();
	//アニメーションモードを変更.
	void ChangeAnimMode( enAnimation anim );


	//音の種類.
	enum enPlayerSound
	{
		enPS_RUN = 0,
		enPS_JUMP,
		enPS_ATK,
		enPS_JUMP_ATK_SPN,
		enPS_JUMP_ATK_STMP,
		enPS_HEAD_HIT,
		enPS_DEAD,

		enPS_MAX,	//最大数.
	};
	//効果音.
	void PlaySe( enPlayerSound enSe );
	clsSound**	m_ppSe;
	float		m_fEarZ;	//耳の位置(トラップ群と違い引数にするのがやばかったので).

	void SetSe( HWND hWnd );



	//エフェクト.
	//名前省略用.
	clsEffects*				m_pEffect;
	//ハンドル eh = EffekseerHandle.
	::Effekseer::Handle		m_ehWave;//衝撃波.
	EFF_STEP				m_EffStep[iEFFECT_PLAYER_STEP_MAX];//足跡4.
	::Effekseer::Handle		m_ehKick;//キック.

	//足跡エフェクト再生.
	void PlayStepEff();
	//衝撃波.
	void PlayWaveEff();
	//キック再生.
	void PlayKickEff();



	//移動補助.
	bool InputUp();
	bool InputDown();
	bool InputLeft();
	bool InputRight();
};




#endif//#ifndef _C_PLAYER_H_
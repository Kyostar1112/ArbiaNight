#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "Global.h"

#include "Sound.h"


class clsCharaSkin;
class clsCharaStatic;

class clsCollisionRay;






//�����蔻��p�ð��.
struct COL_STATE
{
	//����.
	D3DXVECTOR3 vPos;

	//�~�֌W�p.
	float		fYaw;
	float		fRange;
	float		fHeight;
	int			iSarchTheta;

	//BOX�p.
	D3DXVECTOR3 vRangeHalf;	//���S����̒���.
	float		fCenterY;	//Y�̒��S�ւ̋���(��l���Ȃ瑫������͂�Ԃ�܂�).
	float		fCenterX;	//X�̒��S�ւ̋���(�Ǒ��Ȃ瑄�̕��̍������甼��);

	COL_STATE(){
		ZeroMemory( this, sizeof( COL_STATE ) );
	}
};



class clsCollision
{
public:
	clsCollision();
	~clsCollision();

	void CreateSe( HWND hWnd );

	void Release();


	//BOX�̂����蔻��.
	bool HitBox( COL_STATE* Attker, COL_STATE* Target );


	//�ΏۂƂ̋������Z�o����(�~�Ƃ��Ă��g����).
	float LengthComp( D3DXVECTOR3 Attker, D3DXVECTOR3 Target );

	//�~��.
	bool HitCylind( COL_STATE* Attacker, COL_STATE* Target );

	//�ڕW�Ƃ̊p�x.
	float SetTarYaw( D3DXVECTOR3 Attker, D3DXVECTOR3 Target);//OpponentDirect

	//�p�x����.
	bool ThetaCheck( double dMyTheta, double dTargTheta, int iSarchTheta );

	//��`����.
	bool HitSect( COL_STATE* Attacker, COL_STATE* Target );






	//�ǂ̂����蔻��֘A.
	void WallJudge( clsCharaSkin* pWalker, clsCharaStatic* pWall );


	//���Ƃ̔���.
	bool FloorJudge( 
		clsCharaSkin* pWalker, 
		float fRange,
		float& fLandY,//���ɏ��������true���Ԃ��Ă���.
		clsCharaStatic* pFloor,
		bool& bFlg );

	//�V��Ƃ̔���.
	bool CeilingJudge( 
		clsCharaSkin* pWalker, 
		float fWalkerHeight,
		clsCharaStatic* pFloor );



	//----- �ڐG���ʉ� -----///.
	//���̎��.
	enum enSound
	{
		enSOUND_ARBIA_KICK = 0,
		enSOUND_ARBIA_JATK,

		enSOUND_ENEMY,
		enSOUND_ENEMY_SRASH,

		enSOUND_SPIA,
		enSOUND_PEND,

		enSOUND_DROP_DOWN,

		enSOUND_MAX,	//�ő吔.
	};


	//���Đ�.
	void PlaySe( enSound enSe );



private:
	////360�`0�ɔ[�߂�.
	void ThetaOverGuard( float& theta );
	void ThetaOverGuard( double& theta );

	clsCollisionRay*	m_pRay;



	//���ʉ�.
	clsSound**	m_ppSe;
};

#endif//#ifndef _COLLISION_H_
#ifndef _COLLISION_RAY_H_
#define _COLLISION_RAY_H_

#include "Global.h"


#include "CharaStatic.h"
#include "CharaSkin.h"




class clsCollisionRay
{
public:
	clsCollisionRay();
	~clsCollisionRay();


	//�ǂ̂����蔻��֘A.
	void WallJudge( clsCharaSkin* pWalker, clsCharaStatic* pWall );

	//���Ƃ̔���.
	bool FloorJudge( 
		clsCharaSkin* pWalker, 
		float fRange,	//���a.
		float& fLandY,	//���ɏ��������true���Ԃ��Ă���.
		clsCharaStatic* pFloor,
		bool& bGround );//�ڒn�t���O.

	//�V��Ƃ̔���.
	bool CeilingJudge( 
		clsCharaSkin* pWalker, 
		float fWalkerHeight,
		clsCharaStatic* pFloor );

private:
	bool Intersect(
		clsCharaSkin* pAttacker, clsCharaStatic* pTarget,
		float* pfDistance, D3DXVECTOR3* pvIntersect );
	//�����ʒu����غ�݂̒��_��������.
	HRESULT FindVerticesOnPoly(
		LPD3DXMESH pTarget, DWORD dwPolyIndex,
		D3DXVECTOR3* pVecVertices );
	//��]�l����.
	void DirOverGuard( float* fYaw );	
};

#endif//#ifndef _COLLISION_RAY_H_.
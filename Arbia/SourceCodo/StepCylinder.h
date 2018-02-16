#ifndef _STEP_CYLINDER_H_
#define _STEP_CYLINDER_H_

#include "CharaStatic.h"


class clsStepCyl
	: public clsCharaStatic
{
public:
	clsStepCyl();
	~clsStepCyl();

	//�����̊m��.
	void CreateMove( bool bNorth = true );

	virtual void Init();

	//����.
	void Move();

	//�L����������Ă��鎞�ɓ������ʂ�Ԃ�.
	D3DXVECTOR3 GetCarryRange(){
		return D3DXVECTOR3( 0.0f, 0.0f, m_fMovePower );
	}
	float GetCarryRangeZ(){
		return m_fMovePower;
	}

private:

	float	m_fMovePower;//�ړ���.
	bool	m_bNorthFlg;//true : �k����.
	bool	m_bInitFlg;	//�ǂ����������邩�̃t���O.

	D3DXVECTOR3 m_vStartPos;
	float		m_fGoalPosZ;

};


#endif//#ifndef _STEP_CYLINDER_H_
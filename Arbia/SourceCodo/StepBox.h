#ifndef _STEP_BOX_H_
#define _STEP_BOX_H_

#include "CharaStatic.h"

class clsStepBox
	: public clsCharaStatic
{
public:
	clsStepBox();
	~clsStepBox();

	//�����̊m��.
	void CreateMove( bool bRight, bool bEast );

	virtual void Init();

	//����.
	void Move();

	//�L����������Ă��鎞�ɓ������ʂ�Ԃ�.
	D3DXVECTOR3 GetCarryRange(){
		return D3DXVECTOR3( m_fMovePower, 0.0f, 0.0f );
	}
	float GetCarryRangeX(){
		return m_fMovePower;
	}


private:

	float	m_fMovePower;//�ړ���.
	bool	m_bRightFlg;//true : �E��.
	bool	m_bEastFlg;//true : ������.
	bool	m_bInitFlg;	//�ǂ����������邩�̃t���O.

	D3DXVECTOR3 m_vStartPos;

};

#endif//#ifndef _STEP_BOX_H_
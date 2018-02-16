#ifndef _SP_2D_TIMER_H_
#define _SP_2D_TIMER_H_

#include "NumGroup.h"


class clsTimer
	: public clsNumGrp
{
public:

	//��P�^�ڂ̑��x ��P�^�ڂ̑��x �^�C�}�[���ۂ�.
	virtual void Create( ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11 );

	virtual void ReSet();

	//���𑝂₷.
	virtual void PlusNum();

	void AddPosX( float fMove );

	//���オ��( �J��オ�� )�m�F.
	bool Carrying();

	//����ݒ�p.
	void Rimit();
private:

	bool m_bCarrying;//���オ��t���O.

};




#endif//#ifndef _SP_2D_TIMER_H_
#ifndef _C_SPIA_FLOOR_H_
#define _C_SPIA_FLOOR_H_

#include "CharaStatic.h"




class clsSpiaFloor
	: public clsCharaStatic
{
public:
	clsSpiaFloor();
	virtual ~clsSpiaFloor();

	//�����̎��.
	enum enSpeaFloorMode
	{
		enSFM_UNDER = 0,
		enSFM_UP,
		enSFM_TOP,
		enSFM_DOWN,
	};

	//���̎��.
	enum enSound
	{
		enSOUND_VIB = 0,
		enSOUND_UP,
		enSOUND_DOWN,
		  
		enSOUND_MAX,	//�ő吔.
	};

	virtual void Init( bool bFlg = false );//true = �������.

	enSound Move();

	enSpeaFloorMode GetMode(){
		return m_Mode;
	}

private:



	enSpeaFloorMode m_Mode;
	int		m_iTimer;
	float	m_fChangeRange;
	float	m_fRootY;
	bool	m_bVib;
	bool	m_bSpnRight;

};

#endif//#ifndef _C_SPIA_FLOOR_H_
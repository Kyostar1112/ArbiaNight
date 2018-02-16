#ifndef _C_SPIA_WALL_H_
#define _C_SPIA_WALL_H_

#include "CharaStatic.h"




class clsSpiaWall
	: public clsCharaStatic
{
public:
	clsSpiaWall();
	virtual ~clsSpiaWall();

	enum enSpeaWallMode
	{
		enSWM_STOP = 0,		//�~�܂��Ă���i��������ł�or�o�Ă���j.
		enSWM_MOVE_RIGHT,	//�E�֔�яo��.
		enSWM_MOVE_LEFT,
		enSWM_DOWN,			//��������.
	};

	//���̎��.
	enum enSound
	{
		enSOUND_VIB = 0,
		enSOUND_UP,
		enSOUND_DOWN,
		  
		enSOUND_MAX,	//�ő吔.
	};

	//�ŏ��̏�����.
	void Create( bool bRightFlg, int iNo );

	virtual void Init( D3DXVECTOR3 vInitPos, bool bRightFlg = false );//true = .


	bool Move();

	void GoRight(){
		m_enMode = enSWM_MOVE_RIGHT;
	}
	void GoLeft(){
		m_enMode = enSWM_MOVE_LEFT;
	}
	void GoDown(){
		m_enMode = enSWM_DOWN;
	}

	D3DXVECTOR3 GetTest(){
		return ColState.vRangeHalf;
	}

private:

	virtual void UpdateColState();//Ѱ�ނ̍Ō�Ɏg��.
	
	
	//�U������.
	void Vibration();

	D3DXVECTOR3 m_vInitPos;


	bool	m_bRight;//�E���t���O.

	enSpeaWallMode m_enMode;
	int		m_iTimer;
	float	m_fChangeRange;//�ړ���(��яo�������̃X�g�b�v�ʒu�̌���Ɏg��).
	float	m_fRootY;
	bool	m_bVib;	//�����������E�ɍs�������֍s����.

	bool	m_bSpnRight;//��]���E��].

};

#endif//#ifndef _C_SPIA_WALL_H_
#ifndef _SPIA_WALL_MANAGER_H_
#define _SPIA_WALL_MANAGER_H_

#include "SpiaWall.h"

#include "Sound.h"


class clsSpiaWallMgr
	: public clsGameObject
{
public:
	clsSpiaWallMgr();
	~clsSpiaWallMgr();

	void CreateSpia( HWND hWnd, int iNo, int iMoveMode );
	void Init();
	void Release();
	void UpDateModel(){};

	virtual void SetPosition( D3DXVECTOR3 vPos );


	void Render( D3DXMATRIX &mView, D3DXMATRIX &mProj,
				 D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye );

	void Move( float fEarZ );
	void MoveMutualL();
	void MoveMutualR();
	void MoveCloseL();
	void MoveCloseR();



	//���b�v.
	void GoRight();
	void GoLeft();
	//0:��, 1:�E, 2:����, ����ȊO:����.
	void GoDown( int iRight );
	int		m_iTimer;


	//�Q�b�g�V���[�Y.

	COL_STATE* GetPointerSpiaCol( bool bRight, int i );

	int GetSpiaMax(){
		return m_iSpiaMax;
	}
	clsCharaStatic*	GetWallPointer();

	clsCharaStatic* GetWallLCol(){
		return m_pSpiaWall[0];
	}
	clsCharaStatic* GetWallRCol(){
		return m_pSpiaWall[1];
	}

	D3DXVECTOR3 GetTestL(){
		return m_ppSpiaL[0]->GetTest();
	}
	D3DXVECTOR3 GetTestR(){
		return m_ppSpiaR[0]->GetTest();
	}

private:

	enum  enMode
	{
		enMODE_MUTUAL_L = 1,//����(������).
		enMODE_MUTUAL_R = 2,

		enMODE_CLOSE_L = 3,		//����(������).
		enMODE_CLOSE_R = 4,
	};
	enMode	m_enMoveMode;


	//���ʉ�.
	void PlaySe( clsSpiaWall::enSound enSe );
	clsSound**	m_ppSe;
	float		m_fEarZ;


	int				m_iSpiaMax;
	clsSpiaWall**	m_ppSpiaL;
	clsSpiaWall**	m_ppSpiaR;

	clsCharaStatic* m_pSpiaWall[2];//���E�̓�̕ǔ���.


};


#endif//#ifndef _SPIA_WALL_MANAGER_H_
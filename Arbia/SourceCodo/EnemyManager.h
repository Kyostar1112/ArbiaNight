#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

#include "Enemy.h"
//�ǂ�����.




class clsEnemyMgr
	: public clsGameObject
{
public:

	enum enENEMY_MGR_MODE
	{
		enEMM_1X = 1,	//1�l��X���ړ�.
		enEMM_1Z,
		enEMM_1SQ_L,	//��l�Ŏl�p�ړ�����].
		enEMM_1SQ_R,	

		enEMM_2X,		//��l��X���ŕ���.
		enEMM_2X_RE,	//��l��X���Ō݂��Ⴂ.
		enEMM_2Z,
		enEMM_2Z_RE,
		enEMM_2SQ_L,	//��l�Ŏl�p�ړ�����].
		enEMM_2SQ_R,

		enEMM_DOOR,		//�Ō�ɓo�ꂷ��h�A�Ŏ���.

		enEMM_MAX,
	};//m_enMode.

	clsEnemyMgr();
	~clsEnemyMgr();

	void CreateEnemy( HWND hWnd, ID3D11Device* pDevice, ID3D11DeviceContext* pContext, int mode, int iMgrID );
	virtual void Init(){};//�������K�v�ɂȂ����̂ł���Ȃ�.
	void Init( bool bFirst );
	void UpDateModel();


	virtual void SetPosition( D3DXVECTOR3 vPos );
	COL_STATE* GetPointerEnemyCol( int i );
	COL_STATE* GetPointerEnemySubCol( int i );




	void Render( D3DXMATRIX &mView, D3DXMATRIX &mProj,
				 D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye );

	void Move( float fEarZ );



	int GetEnemyMax(){
		return m_iEnemyMax;
	}

	//��Ԏ擾.
	clsEnemy::enENEMY_MOVE GetEnemyMove( int j ){
		return m_ppEnemy[j]->GetMove();
	}


	//�������Ŏg��.
	D3DXVECTOR3 GetEnemyPos( int j ){
		return m_ppEnemy[j]->GetPosition();
	}
	//���G���a�������o��.
	float GetSarchRange( int j ){
		return m_ppEnemy[j]->m_colSub.fRange;
	}

	//ׯ��.
	//����.
	bool Discover( int j ){
		return m_ppEnemy[j]->Discover();
	}
	//������.
	void Lost( int j ){
		m_ppEnemy[j]->Lost();
	}
	//�U��.
	void Attack( int j ){
		m_ppEnemy[j]->Attack();
	}
	//���S.
	void Dead( int j ){
		m_ppEnemy[j]->Dead();
	}

	//����.
	void Win( int j ){
		m_ppEnemy[j]->Win();
	}

	//�h�A���S�J�n.
	void DoorTimerStart(){
		m_bDoor = true;
	}
	//�h�A�Ŏ��ʐl?.
	bool GetDoorDeader(){
		if( m_enMode == enEMM_DOOR ){
			return true;
		}
		return false;
	}


	//clsEnemy::�ǂ�������Ƃ��ɕK�v��ׯ��.
	void GetSarchTarget( D3DXVECTOR3 vPos ){
		for( int i=0; i<m_iEnemyMax; i++ ){
			m_ppEnemy[i]->GetSarchTarget( vPos );
		}
	}



	//�U���̏u�ԃt���O��Ԃ�.
	bool GetAttackImpact( int j ){
		return m_ppEnemy[j]->GetAttackImpact();
	};


	//���N��.
	int GetWalkRangeMax();


private:
	clsEnemy**	m_ppEnemy;

	void SetTurnPos( enENEMY_MGR_MODE mode, int i );//�ړ��̊p���.


	void Release();

	int			m_iEnemyMax;//�G�̐�.
//	clsEnemy**	m_ppEnemy;


	enENEMY_MGR_MODE m_enMode;

	D3DXVECTOR3 m_vTurnPos[4];	//�p.



	//�h�A.
	bool	m_bDoor;
	int		m_iDoorTimer;

};


#endif//#ifndef _ENEMY_MANAGER_H_
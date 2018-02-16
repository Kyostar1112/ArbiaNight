#ifndef _COVOR_MANAGER_H_
#define _COVOR_MANAGER_H_

//#include "Covor.h"
#include "CharaStatic.h"

#include "Sound.h"


const char cCOVER_MAX = 2; 




class clsCoverMgr
	: public clsGameObject
{
public:
	clsCoverMgr();
	~clsCoverMgr();

	enum enCoverMove
	{
		enCM_FLOOR,	//���Ă���i�s���j.
		enCM_VIB,	//�h���.
		enCM_OPEN,	//�J���i����j.
		enCM_HOLL,	//���i�J���Ă���j.
		enCM_CLOSE,	//����i����j.
	};


	void CreateCover( HWND hWnd, int iNo );
	void Init();
	void Release();
	void UpDateModel(){};



	virtual void Render( D3DXMATRIX &mView, D3DXMATRIX &mProj,
		D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye );



	//����.
	void Move( float fEarZ );
	//����.
	void StmpCovor( float fEarZ );
	//��������.
	void StmpCovorStrong( float fEarZ );




	//Main�ł����蔻��̔��f�Ŏg��.
	enCoverMove GetCoverMove(){
		return m_enMove;
	}
	char GetCoverMax(){
		return cCOVER_MAX;
	}
	clsCharaStatic* GetCoverPointer( char j ){
		return m_ppCover[j];
	}

	//����?.
	bool isCanStmp(){
		if( m_enMove == enCM_FLOOR ||
			m_enMove == enCM_VIB )
		{
			return true;
		}
		return false;
	}

private:

	//���̎��.
	enum enSound
	{
		enSOUND_VIB = 0,
		enSOUND_OPEN,
		  
		enSOUND_MAX,	//�ő吔.
	};

	//���ʉ�.
	void PlaySe( enSound enSe, float fEarZ );
	clsSound***	m_pppSe;

	clsCharaStatic** m_ppCover;//pp�����Ǎ��E�̓����.
	enCoverMove m_enMove;
	int			m_iTimer;

};

#endif//#ifndef _COVOR_MANAGER_H_
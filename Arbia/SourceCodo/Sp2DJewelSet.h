#ifndef _SP_2D_JEWEL_SET_H_
#define _SP_2D_JEWEL_SET_H_

#include "Sp2DJewel.h"

#include "Sound.h"

class clsJewerSet
{
public:
	clsJewerSet();
	~clsJewerSet();

	void Create( HWND hWnd,
		ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11,
		int iNo );

	void Move();



	//�~�܂邾��.
	void Stop(){
		m_vMove = { 0.0f, 0.0f, 0.0f };
		m_fAcc = 0.0f;
	};

	//�ăX�^�[�g�O��.
	void ReSet();


	void SetMove( D3DXVECTOR3 vMove, float fAcc ){
		m_vMove = vMove;
		m_fAcc = fAcc;
	}

	bool GetDown(){
		return m_bDown;
	}

	//----- ���b�v -----//.
	void Init(){
		m_smpModel->Init();
	};


	void SetScale( float fScale ){
		m_fScale = fScale;
		m_smpModel->m_fScale = m_fScale;
	}

	void AddScale( float fScale );

	void Render(){
		m_smpModel->Render();
	};

	void SetPos( D3DXVECTOR3 vPos ){
		m_smpModel->SetPos( vPos );
	};
	D3DXVECTOR3 GetPos(){
		return m_smpModel->GetPos();
	}

	void SetPosX( float fX ){
		m_smpModel->SetPosX( fX );
	}

	void SetGetFlg( bool bFlg ){
		m_bGet = bFlg;
	}
	bool GetGetFlg(){
		return m_bGet;
	}

//	//���̎��.
//	enum enSound
//	{
//		enS_UP = 0,//��΂��㏸���n�߂�.
////		enS_SHINE,
//
//		enS_MAX,	//�ő吔.
//	};

	void PlaySe( /*clsJewerSet::enSound enSe*/ ){
//		m_pSe[enSe]->Stop();
		m_pSe->SeekToStart();
		m_pSe->Play();
	}

private:

	unique_ptr<clsJewel> m_smpModel;
	bool m_bDown;//�~����.
	bool m_bEnd;
	D3DXVECTOR3 m_vMove;
	float		m_fAcc;
	bool		m_bGet;//��ɓ������?.


	float m_fScale;



	//���ʉ�.
	clsSound*	m_pSe;
	void SetSe( HWND hWnd, int iNo );


};


#endif//#ifndef _SP_2D_JEWEL_SET_H_
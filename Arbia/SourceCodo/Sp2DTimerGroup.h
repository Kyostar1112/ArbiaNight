#ifndef _SP2D_TIMER_GROUP_H_
#define _SP2D_TIMER_GROUP_H_

#include "Sp2DTimer.h"
#include "Mymacro.h"
#include "Common.h"//���ʸ׽.
#include <memory>

#include "Sound.h"

class clsTimerGrp
{
public:
	clsTimerGrp();
	~clsTimerGrp();

	//�ŏ��̏�����.
	void Create( HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11 );
	
	//���ڈȍ~�̏�����.
	virtual void ReSet();


	void Move();

	void Render();


	void SetPos( D3DXVECTOR3 vPos );
	void AddPos( D3DXVECTOR3 vPos );
	void AddPosY( float fPos );

	void SetStop( bool bStop ){
		m_bStop = bStop;
	}

	//4���̐����ŕԂ�( ���P�^�͕�, ���񌅂͕b{ �R���}�b�͖��� } ).
	int GetTime();

private:

	D3DXVECTOR3 m_vPos;

	clsTimer*		m_Timer[3];
	clsSprite2D*	m_Colon[2];//:( �R���� ).

	bool m_bRimitFlg;//true�ɂȂ�ƃJ�E���g���Ȃ�.

	bool m_bStop;//true�ŃJ�E���g���Ȃ�.
	bool m_bStopOld;




	clsSound* m_pSe;

};

#endif//#ifndef _SP2D_TIMER_GROUP_H_
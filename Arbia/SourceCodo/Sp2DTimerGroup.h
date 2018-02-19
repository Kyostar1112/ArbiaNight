#ifndef _SP2D_TIMER_GROUP_H_
#define _SP2D_TIMER_GROUP_H_

#include "Sp2DTimer.h"
#include "Mymacro.h"
#include "Common.h"//���ʸ׽.
#include <memory>

#include "Sound.h"


const char cTIMER_GROUP_TIMER_NUM = 3;
const char cTIMER_GROUP_COLON_NUM = cTIMER_GROUP_TIMER_NUM - 1;

class clsTimerGrp
{
public:
	clsTimerGrp();
	~clsTimerGrp();

	//�ŏ��̏�����.
	void Create( HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11 );
	
	//���ڈȍ~�̏�����.
	virtual void ReSet();


	void Update();

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

	clsTimer*		m_Timer[cTIMER_GROUP_TIMER_NUM];
	clsSprite2D*	m_Colon[cTIMER_GROUP_COLON_NUM];//:( �R���� ).

	bool m_bRimitFlg;//true�ɂȂ�ƃJ�E���g���Ȃ�.

	bool m_bStop;//true�ŃJ�E���g���Ȃ�.
	bool m_bStopOld;




	clsSound* m_pSe;

};

#endif//#ifndef _SP2D_TIMER_GROUP_H_
#include "StepBox.h"

//�����ړ����� : Constant Speed Range.
const float fCONST_SPD_RANGE = 1.0f;
//�����ړ����x.
const float fSPD_MAX = 1.0f / 16.0f;

//�����x.
const float fACCEL = fSPD_MAX / 32.0f;


//�X�e�[�W��.
const float fSTAGE_WIDTH = 10.0f;
const float fSTAGE_WIDTH_HARF = fSTAGE_WIDTH / 2.0f;


clsStepBox::clsStepBox()
{
}

clsStepBox::~clsStepBox()
{
}


void clsStepBox::CreateMove( bool bRight, bool bEast )
{
	//��_.
	m_vStartPos = m_vPos;
	//�t���O.
	m_bInitFlg = bEast;
	//�֌�����Start�Ȃ�.
	if( bRight ){
		m_vStartPos.x += fSTAGE_WIDTH_HARF;
	}
	else{
		m_vStartPos.x -= fSTAGE_WIDTH_HARF;
	}


	Init();
}

void clsStepBox::Init()
{
	m_bEastFlg = m_bInitFlg;//true : ������.

	m_fMovePower = -fSPD_MAX;
	m_vPos = m_vStartPos;
	//��֌�����Start�Ȃ�.
	if( m_bInitFlg ){
		m_fMovePower *= -1.0f;		//�ړ��ʋt�].
	}
}


//����.
void clsStepBox::Move()
{
	//����.
	if( m_bEastFlg ){
		//����.
		m_fMovePower += fACCEL;
		//���x����.
		if( m_fMovePower > fSPD_MAX ){
			m_fMovePower = fSPD_MAX;
		}
		//�����]��.
		if( m_vPos.x > m_vStartPos.x + fCONST_SPD_RANGE ){
			m_bEastFlg = false;
		}

		
	}
	//����GO.
	else{
		m_fMovePower -= fACCEL;
		
		if( m_fMovePower < -fSPD_MAX ){
			m_fMovePower = -fSPD_MAX;
		}

		if( m_vPos.x < m_vStartPos.x - fCONST_SPD_RANGE ){
			m_bEastFlg = true;
		}
	}

	//�ړ�.
	m_vPos.x += m_fMovePower;
}

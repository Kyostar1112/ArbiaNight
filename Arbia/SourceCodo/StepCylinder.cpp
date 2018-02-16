#include "StepCylinder.h"

//�����ړ����� : Constant Speed Range.
const float fCONST_SPD_RANGE = 6.0f;
//�����ړ����x.
const float fSPD_MAX = 1.0f / 32.0f;

//�����x.
const float fACCEL = fSPD_MAX / 32.0f;


clsStepCyl::clsStepCyl()
{
}

clsStepCyl::~clsStepCyl()
{
}

void clsStepCyl::CreateMove( bool bNorth )
{
	//��_.
	m_vStartPos = m_vPos;
	m_fGoalPosZ = m_vStartPos.z + fCONST_SPD_RANGE;
	//�t���O.
	m_bInitFlg = bNorth;
	Init();
//	m_vRot.y = (float)M_PI_2;
}

void clsStepCyl::Init()
{
	m_bNorthFlg = m_bInitFlg;//true : �k����.

	m_fMovePower = -fSPD_MAX;
	m_vPos = m_vStartPos;
	//��֌�����Start�Ȃ�.
	if( m_bInitFlg ){
		m_fMovePower *= -1.0f;		//�ړ��ʋt�].
		m_vPos.z = m_fGoalPosZ;//�ʒu����������.
	}
}

//����.
void clsStepCyl::Move()
{
	//�k��GO.
	if( m_bNorthFlg ){
		//����.
		m_fMovePower += fACCEL;
		//���x����.
		if( m_fMovePower > fSPD_MAX ){
			m_fMovePower = fSPD_MAX;
		}

		//�����]��.
		if( m_vPos.z > m_fGoalPosZ ){
			m_bNorthFlg = false;
		}
	}
	//���GO.
	else{
		m_fMovePower -= fACCEL;
		
		if( m_fMovePower < -fSPD_MAX ){
			m_fMovePower = -fSPD_MAX;
		}

		if( m_vPos.z < m_vStartPos.z ){
			m_bNorthFlg = true;
		}
	}

	//�ړ�.
	m_vPos.z += m_fMovePower;
}


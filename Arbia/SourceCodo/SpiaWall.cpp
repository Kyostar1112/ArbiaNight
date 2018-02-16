#include "SpiaWall.h"


////===== �����蔻�� =====//.
const float COL_SPIA_BOX_X = 1.0f;//2.3
const float COL_SPIA_BOX_Y = 0.5f;//1.
const float COL_SPIA_BOX_Z = COL_SPIA_BOX_Y;
////===== �����蔻�� �I��� =====//.



//���.
const int iVIB_TIME = 60;//Vibration�U��.
const int iVIB_INTER_TIME = 4;//Vibration Intervar���t���[���Ɉ��h���?.

//���x.
const float fUP_SPD = 0.75f;
const float fDOWN_YAW = 0.1f;
const float fDOWN_SPD = -0.05f;

//����(������).
const float fVIB_RANGE = 0.25f;
const float fSPIA_TOP = 3.5f;

clsSpiaWall::clsSpiaWall()
{
//	m_enMode = enSWM_ROAD;
//	m_iTimer = 0;
//	m_fChangeRange = 0.0f;
}

clsSpiaWall::~clsSpiaWall()
{
}


//�ŏ��̏�����.
void clsSpiaWall::Create( bool bRightFlg, int iNo )
{
	//��]�����ݒ�.
	if( iNo % 2 == 0 ){
		m_bSpnRight = true;
	}
	else{
		m_bSpnRight = false;
	}

	//Box�p�����蔻��.
	ColState.vRangeHalf.x = COL_SPIA_BOX_X;
	ColState.vRangeHalf.y = COL_SPIA_BOX_Y;
	ColState.vRangeHalf.z = COL_SPIA_BOX_Z;
	ColState.fCenterY = ColState.vRangeHalf.y / 2.0f;
	ColState.fCenterY = 0.0f;
	if( bRightFlg ){
		ColState.fCenterX = -ColState.vRangeHalf.x;
	}
	else{
		ColState.fCenterX = ColState.vRangeHalf.x;
	}
	ColState.fCenterX = 0.0f;

	Init( m_vPos, bRightFlg );
}

void clsSpiaWall::Init( D3DXVECTOR3 vInitPos, bool bRightFlg )
{
	m_enMode = enSWM_STOP;
	m_iTimer = 0;
	m_fChangeRange = 0.0f;
	m_fRootY = m_vPos.y;
	m_bVib = bRightFlg;
	m_bRight = bRightFlg;
	m_vInitPos = vInitPos;
}

bool clsSpiaWall::Move()
{
	bool bSoundTop = false;//��яo�����t���O.
	switch( m_enMode )
	{
	case enSWM_MOVE_RIGHT:
		m_iTimer ++;
		//��������.
		if( m_iTimer < iVIB_TIME ){
			Vibration();
		}
		//��яo��.
		else{
			m_vPos.x += fUP_SPD;
			m_fChangeRange += fUP_SPD;
			if( m_fChangeRange >= fSPIA_TOP ){
				m_fChangeRange = fSPIA_TOP;
				m_enMode = enSWM_STOP;
				m_iTimer = 0;
				bSoundTop = true;
			}
		}
		break;

	case enSWM_MOVE_LEFT://����.
		m_iTimer ++;
		//��������.
		if( m_iTimer < iVIB_TIME ){
			Vibration();
		}
		//��яo��.
		else{
			m_vPos.x -= fUP_SPD;
			m_fChangeRange += fUP_SPD;
			if( m_fChangeRange >= fSPIA_TOP ){
				m_fChangeRange = fSPIA_TOP;
				m_enMode = enSWM_STOP;
				m_iTimer = 0;
				bSoundTop = true;
			}
		}
		break;

	case enSWM_DOWN:
		if( m_bSpnRight ){
			m_vRot.y += fDOWN_YAW;
		}
		else{
			m_vRot.y += -fDOWN_YAW;
		}

		if( !m_bRight ){
			m_vPos.x += fDOWN_SPD;
			if( m_vPos.x < m_vInitPos.x ){
				m_vPos.x = m_vInitPos.x;
				m_fChangeRange = 0.0f;
				m_enMode = enSWM_STOP;
			}
		}
		else{
			m_vPos.x -= fDOWN_SPD;
			if( m_vPos.x > m_vInitPos.x ){
				m_vPos.x = m_vInitPos.x;
				m_fChangeRange = 0.0f;
				m_enMode = enSWM_STOP;
			}
		}
		break;

//	//�ی�.
//	default:
//		m_enMode = enSWM_DOWN;
//		break;
	}



	UpdateColState();

	return bSoundTop;
}



//�U������.
void clsSpiaWall::Vibration()
{
	if( m_iTimer % iVIB_INTER_TIME == 0 ){
		if( m_bVib ){
			m_vPos.x -= fVIB_RANGE;
			m_bVib = false;
		}
		else{
			m_vPos.x += fVIB_RANGE;
			m_bVib = true;
		}
	}
}

//�����蔻��X�V.
void clsSpiaWall::UpdateColState()
{
	ColState.vPos = m_vPos;
//	if( m_bRight ){
//		ColState.vPos.x -= ColState.vRangeHalf.x / 2.0f;
//	}
//	else{
//		ColState.vPos.x += ColState.vRangeHalf.x / 2.0f;
//	}

}
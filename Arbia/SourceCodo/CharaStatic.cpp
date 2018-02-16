#include "CharaStatic.h"



clsCharaStatic::clsCharaStatic()
{
}

clsCharaStatic::~clsCharaStatic()
{
}



//�����ݸފ֐�.
void clsCharaStatic::Render( D3DXMATRIX &mView, D3DXMATRIX &mProj,
	D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye,
	D3DXVECTOR4 vColor , bool alphaFlg )
{

	//���W�X�V����.
	UpDateModel();
	
	//ү���������ݸފ֐����Ă�.
	m_pModel->Render( mView, mProj, vLight, vEye, vColor, alphaFlg );
}

//�����ް��֘A�t���֐�clsDX9Mesh
void clsCharaStatic::AttachModel( clsDX9Mesh* pModel )
{
	if( pModel != NULL ){
		m_pModel = pModel;
	}
}

//�����ް��֘A�t�������֐�.
void clsCharaStatic::DetatchModel()
{
	if( m_pModel != NULL ){
		m_pModel = NULL;
	}
}




//���W���]�l���X�V����.
void clsCharaStatic::UpDateModel()
{
	if( m_pModel == NULL ){
		return;
	}

	m_pModel->m_vPos	= m_vPos;
	m_pModel->m_fYaw	= m_vRot.y;
	m_pModel->m_fPitch= m_vRot.x;
	m_pModel->m_fRoll	= m_vRot.z;
	m_pModel->m_fScale= m_fScale;
}


//============================================================
//	�ʒu�X�V�֐�.
//============================================================
void clsCharaStatic::UpdatePos()
{
	//��׸��ړ�����(׼޺�)
	D3DXMATRIX mYaw;
	D3DXMatrixRotationY( &mYaw, m_vRot.y );

	//Z���޸�ق�p��.
	D3DXVECTOR3	vecAxisZ( 0.0f, 0.0f, 1.0f );

	//Z���޸�ق��̂��̂���]��Ԃɂ��ϊ�����.
	D3DXVec3TransformCoord(
		&vecAxisZ,	//(out)
		&vecAxisZ,
		&mYaw );	//Y����]�s��.

	//�����ɂ���Đi�s������l��ݒ�.
	switch( m_enDir )
	{
	case enDirection_Stop:
		break;
	case enDirection_Foward:	//�O�i.
		//����������*�i�߂�l(0.1f).
		m_vPos -= vecAxisZ * 0.15f * m_fSpd;
//		m_fWalkLangth -= 0.15f * m_fSpd;
		break;
	case enDirection_BackWard:	//���.
		m_vPos += vecAxisZ * 0.15f * m_fSpd;
//		m_fWalkLangth -= 0.15f * m_fSpd;
		break;
	//case enDirection_LeftTurn:
	//	break;
	//case enDirection_RightTurn:
	//	break;
	//default:
	//	break;
	}
	//m_enDir = enDirection_Stop;//��~.

}

//==================================================
//	�ʒu�X�V�֐�.
//==================================================
void clsCharaStatic::UpdateColState()
{
	ColState.vPos = m_vPos;
	ColState.fYaw = m_vRot.y;
}
//==================================================
//	�����蔻��p.
//==================================================
void clsCharaStatic::SetColPos( D3DXVECTOR3* vPos )
{
	ColState.vPos = *vPos;
}



//==================================================
//	�����蔻��̏��̃A�h���X�擾.
//==================================================
COL_STATE* clsCharaStatic::GetPointerCol()
{
	return &ColState;
}




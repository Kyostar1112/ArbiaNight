#include <math.h>
#include "Pendulum.h"


//��.
const char ALIAS_NAME[] = "PendSe";
const char FILE_PATH[] = "SE\\300Trap\\200Pendulum.wav";
const int iVOL = 1000;


//===== �����蔻�� =====//.
//===== Box =====//.
const float fCOL_PEND_BOX_X = 6.0f / 2.0f;
const float fCOL_PEND_BOX_Y = 4.0f / 2.0f;
const float fCOL_PEND_BOX_Z = 0.875f / 2.0f;
const float fCOL_PEND_BOX_CENTER_Y = 0.0f;
//===== �����蔻�� �I��� =====//.




const float fPEND_SPN_POWER_MAX = 0.025f;//�h���X�s�[�h�̏��.
const float fPEND_SPN_POWER_UP = 0.0005f;//�����x.
const float fPEND_YAW_MAX = 0.0f;




//----- ���� ------//
//���ߋ��E��Z.
const float fALPHA_BORDER_Z = 0.5f;

//���ߑ��x.
const float fALPHA_SPD = 1.0f / 64.0f;

//��Ԕ������Ă�.
const float fALPHA_LIMIT = 0.25f;


//����.
const float fHEIGHT_OFFSET = 12.0f;


//�G�t�F�N�g.
const float fEFFECT_SPD_FIRE = 1.125f;
const D3DXVECTOR3 vEFFECT_SCALE_FIRE = { 0.5f, 0.5f, 0.5f };



clsPend::clsPend()
{
	m_pSe = nullptr;
	m_pEffect = nullptr;
}

clsPend::~clsPend()
{
	m_pEffect = nullptr;

	if( m_pSe != nullptr ){
		m_pSe->Stop();
		m_pSe->Close();
		delete m_pSe;
		m_pSe = nullptr;
	}
}

void clsPend::Create( HWND hWnd, int iNo, int iPower  )
{
	Init();
	m_bFireDisp = false;

	//�����蔻���ݒ�( ���肦�Ȃ����ɓ���Ȃ���1�t���[���ڂ� 0, 0, 0 �ɗ��� ).
	float initPos = -100.0f;
	ColState.vPos = { initPos, initPos, initPos };
	//Box�p.
	ColState.vRangeHalf.x = fCOL_PEND_BOX_X;
	ColState.vRangeHalf.y = fCOL_PEND_BOX_Y;
	ColState.vRangeHalf.z = fCOL_PEND_BOX_Z;
	ColState.fCenterY = fCOL_PEND_BOX_CENTER_Y;
	ColState.fCenterX = 0.0f;

	if( m_pSe == nullptr ){
		//���N���X.
		m_pSe = new clsSound;
		//�����ʏ�����.
		m_pSe->SetVolume( 0 );
		//���O.
		char cAliasName[STR_BUFF_MAX] = "";
		strcat_s( cAliasName, sizeof( cAliasName ), ALIAS_NAME );
		//�ԍ�.
		char cNumber[] = "  ";
		_itoa_s( iNo, cNumber, 10 );
		//���O�Ɣԍ�����.
		strcat_s( cAliasName, sizeof( cAliasName ), cNumber );
		//�쐬.
		m_pSe->Open( FILE_PATH, cAliasName, hWnd );
		//�ő剹�ʐݒ�.
		m_pSe->SetMaxVolume( iVOL );
	}


	//�������t���O�Z�b�g.
	if( iPower <= 0 ){
		iPower = 1;
	}
	 m_iInitFlg = iPower;

	if( m_pEffect == nullptr ){
		m_pEffect = clsEffects::GetInstance();
	}
}


void clsPend::Init()
{
	//�G�N�Z���ɓ����Ă��鐔�����傫���ƍŏ��̗h�ꂪ�x���.
	m_vRot.z = 0.0f;
	//��̎��i�ŏ��͉E�ɍs���j.
	if( m_iInitFlg % 2 ){
		m_fMovePower = fPEND_SPN_POWER_MAX;
		m_bRigtFlg = true;
		m_vRot.z -= (float)( m_iInitFlg * 0.01 );
	}
	//�����̎��i�ŏ��͍��ɍs���j.
	else{
		m_fMovePower = -fPEND_SPN_POWER_MAX;
		m_bRigtFlg = false;
		m_vRot.z += (float)( ( m_iInitFlg - 1 ) * 0.01 );
	}


	m_fAlpha = 1.0f;
	m_bAlpha = false;
	m_bAlphaChange = false;
}

//============================================================
//	�U��q����.
//============================================================
void clsPend::Update( float fEarZ )
{
	//�U���.
	m_vRot.z += m_fMovePower;

	//�E�ɐU���.
	if( m_bRigtFlg ){
		//����.
		m_fMovePower += fPEND_SPN_POWER_UP;
		//�����Ȃ肷���Ȃ�.
		if( m_fMovePower > fPEND_SPN_POWER_MAX ){
			m_fMovePower = fPEND_SPN_POWER_MAX;
			//���].
			if( m_vRot.z > fPEND_YAW_MAX ){
				m_bRigtFlg = false;
				PlaySe( fEarZ );
				PlayEffFire();
				PlayEffWind( m_bRigtFlg );
			}
		}
	}
	//���ɐU���.
	else{
		m_fMovePower -= fPEND_SPN_POWER_UP;
		if( m_fMovePower < -fPEND_SPN_POWER_MAX ){
			m_fMovePower = -fPEND_SPN_POWER_MAX;
			if( m_vRot.z < -fPEND_YAW_MAX ){
				m_bRigtFlg = true;
				PlaySe( fEarZ );
				PlayEffFire();
				PlayEffWind( m_bRigtFlg );
			}
		}
	}
	//���ߒl�ݒ�.
	SetAlpha();
}


//============================================================
//	�����ݸ�.
//============================================================
void clsPend::Render( D3DXMATRIX& mView, D3DXMATRIX& mProj,
	D3DXVECTOR3& vLight, D3DXVECTOR3& vEye )
{
	if( m_pModel == nullptr || m_pAnimCtrl == nullptr ){
		return;
	}

	UpDateModel();

	m_pModel->Render(
		mView, mProj, vLight, vEye,
		D3DXVECTOR4( 1.0f, 1.0f, 1.0f, m_fAlpha ), m_bAlpha, m_pAnimCtrl );
}


//============================================================
//	���ߒl�̐ݒ�.
//============================================================
void clsPend::SetAlphaFlg( float fPlayerZ )
{
	//���ߒ�.
	if( m_bAlphaChange ){
		//���߃t���OON.
		m_bAlpha = true;
		//�v���C���[�����ɂ���Ȃ�.
		if( fPlayerZ > m_vPos.z + fALPHA_BORDER_Z ){
			return;
		}
		//���̉��J�n.
		m_bAlphaChange = false;
	}
	//���ߒ��ł͂Ȃ�.
	else{
		//�v���C���[����O�ɂ���Ȃ�.
		if( fPlayerZ < m_vPos.z + fALPHA_BORDER_Z ){
			return;
		}
		//���ߊJ�n.
		m_bAlphaChange = true;
	}
}

//============================================================
//	���ߒl�̐ݒ�.
//============================================================
void clsPend::SetAlpha()
{
	//���ߒ�.
	if( m_bAlphaChange ){
		m_fAlpha -= fALPHA_SPD;
		if( m_fAlpha < fALPHA_LIMIT ){
			m_fAlpha = fALPHA_LIMIT;
		}
	}
	//���̉���.
	else{
		m_fAlpha += fALPHA_SPD;
		if( m_fAlpha > 1.0f ){
			m_fAlpha = 1.0f;
			m_bAlpha = false;
		}
	}
}




//============================================================
//	�{�[��pos.
//============================================================
void clsPend::GetBonePos( const char* cBoneName, D3DXVECTOR3 vBonePos )
{
	if( m_pModel == nullptr ) return;

	//�{�[�����W.
	char* boneName =  (char*)cBoneName;
	if( m_pModel->GetPosFromBone( boneName, &vBonePos ) ){
		SetColPos( &vBonePos );
	}
}



//============================================================
//	���ʉ�.
//============================================================
void clsPend::PlaySe( float fEarZ )
{
	if( m_pSe == nullptr ) return;

	//�Đ����鋗���Ȃ�.
	int vol = ChangeVolumeDistance( fEarZ, m_vPos.z );
	if( vol ){
		m_pSe->GetMaxVolRate( vol );
		m_pSe->SeekToStart();
		m_pSe->SetVolume( vol );
		m_pSe->Play();
	}
	//�Đ����Ȃ������Ȃ�.
	else{
		m_pSe->SetVolume( 0 );
	}
}

//�G�t�F�N�g�Đ�.
void clsPend::PlayEffFire()
{
	if( m_pEffect == nullptr || !m_bFireDisp ) return;

	if( !m_pEffect->PlayCheck( m_ehFire ) ){
		D3DXVECTOR3 vEffPos = m_vPos;
		vEffPos.y -= fHEIGHT_OFFSET;

		m_ehFire = m_pEffect->Play( clsEffects::enEfcType_PEND_FIRE, vEffPos );
		m_pEffect->SetScale( m_ehFire, vEFFECT_SCALE_FIRE );
		m_pEffect->SetSpd( m_ehFire, fEFFECT_SPD_FIRE );
	}
}
//���G�t�F�N�g.
void clsPend::PlayEffWind( bool bRight )
{
	if( m_pEffect == nullptr ) return;

	if( !m_pEffect->PlayCheck( m_ehWind ) ){
		D3DXVECTOR3 vEffPos = m_vPos;
		vEffPos.y -= fHEIGHT_OFFSET;


		m_ehWind = m_pEffect->Play( clsEffects::enEfcType_PEND_WIND, vEffPos );
//		m_pEffect->SetScale( m_ehWind, vEFFECT_SCALE_FIRE );
//		m_pEffect->SetSpd( m_ehWind, 1.125f );
	}
}

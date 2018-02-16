#include "DxInput.h"

LPDIRECTINPUT8 pDI2 = NULL;			// DxInput�I�u�W�F�N�g.
LPDIRECTINPUTDEVICE8 pPad2 = NULL;	// �f�o�C�X(�R���g���[��)�I�u�W�F�N�g.

//========== �è���̓|����ƍő�l ==========.
const LONG STICK_MAX = 1000;
const float STICK_RUN = 975;
const float STICK_WALK = 250;




// �W���C�X�e�B�b�N�񋓊֐�.
BOOL CALLBACK EnumJoysticksCallBack( const DIDEVICEINSTANCE *pdidInstance, VOID *pContext )
{
	HRESULT hRlt;	// �֐����A�l.

	// �f�o�C�X(�R���g���[��)�̍쐬.
	hRlt = pDI2->CreateDevice(
		pdidInstance->guidInstance,	// �f�o�C�X�̔ԍ�.
		&pPad2,	// (out)�쐬�����f�o�C�X�I�u�W�F�N�g.
		NULL );
	if( hRlt != DI_OK ){
		return DIENUM_CONTINUE;	// ���̃f�o�C�X��v��.
	}
	return DIENUM_STOP;	// �񋓒�~.
}

// �I�u�W�F�N�g�̗񋓊֐�.
BOOL CALLBACK EnumObjectsCallBack( const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext )
{
	// ��(�X�e�B�b�N)�������Ă��邩�H.
	if( pdidoi->dwType & DIDFT_AXIS )
	{
		// ���͏��͈̔͂�ݒ肷��.
		DIPROPRANGE diprg;	// �͈͐ݒ�\����.

		diprg.diph.dwSize = sizeof( DIPROPRANGE );			// �\���̂̃T�C�Y.
		diprg.diph.dwHeaderSize = sizeof( DIPROPHEADER );	// �w�b�_�[���̃T�C�Y.
		diprg.diph.dwObj = pdidoi->dwType;					// ��(�I�u�W�F�N�g).
		diprg.diph.dwHow = DIPH_BYID;						// dwObj�ɐݒ肳�����̂�.
															// �I�u�W�F�N�g�̎�ނ��H�C���X�^���X�ԍ����H.

		diprg.lMax = +STICK_MAX;	// �ő�l.
		diprg.lMin = -STICK_MAX;	// �ŏ��l.

		// �͈͂�ݒ�.
		if( FAILED( pPad2->SetProperty(
					DIPROP_RANGE,	// �͈�.
					&diprg.diph ) ) )// �͈͐ݒ�\����.
		{
			return DIENUM_STOP;
		}
	}
	return DIENUM_CONTINUE;
}


//============================================================
//	DxInput�׽.
//============================================================


//�ݽ�׸�.
clsDxInput::clsDxInput()
	: m_pDI( NULL )
	, m_pPad( NULL )
{
}

//�޽�׸�.
clsDxInput::~clsDxInput()
{
}



//============================================================
//	DirectInput�̏����ݒ�B.
//============================================================
bool clsDxInput::initDI( HWND hWnd )
{
	HRESULT hRlt;	// �֐����A�l.
	hRlt = DirectInput8Create(
			GetModuleHandle(NULL),	// DxInput���쐬����A�v���̃n���h��.
			DIRECTINPUT_VERSION,	// �Œ�FDxInput�̃o�[�W����.
			IID_IDirectInput8,		// �Œ�FUnicode��Ansi�̋�ʗp.
			(VOID**)&m_pDI,			// (out)DxInput�I�u�W�F�N�g.
			NULL);					// NULL�Œ�.
	if( hRlt != DI_OK ){
		MessageBox(NULL, "DxInput�̍쐬�Ɏ��s",	"clsDxInput::initDI", MB_OK);
		return false;
	}

	pDI2 = m_pDI;

	// ���p�\�ȃR���g���[����T��(�񋓂���).
	hRlt = (*m_pDI).EnumDevices(
			DI8DEVCLASS_GAMECTRL,	// �S�ẴQ�[���R���g���[��.
			EnumJoysticksCallBack,	// �R���g���[���̗񋓊֐�.
			NULL,					// �R�[���o�b�N�֐�����̒l.
			DIEDFL_ATTACHEDONLY);	// �q�����Ă����ɂ̂�.
	if( hRlt != DI_OK ){
		MessageBox(NULL, "���۰ׂ̊m�F�Ɏ��s", "clsDxInput::initDI", MB_OK);
	}

	m_pPad = pPad2;

	// �R���g���[���̐ڑ��m�F.
	if( pPad2 == NULL ){
		//MessageBox( NULL, "���۰ׂ��ڑ�����Ă��܂���", "clsDxInput::initDI", MB_OK );
	}
	else {
		// �R���g���[���\���̂̃f�[�^�t�H�[�}�b�g���쐬.
		hRlt = pPad2->SetDataFormat(
				&c_dfDIJoystick2);	//�Œ�.
		if( hRlt != DI_OK ){
			MessageBox( NULL, "�ް�̫�ϯĂ̍쐬���s", "clsDxInput::initDI", MB_OK );
		}
		// (���̃f�o�C�X�Ƃ�)�������x���̐ݒ�.
		hRlt = pPad2->SetCooperativeLevel(
				hWnd,
				DISCL_EXCLUSIVE |	// �r���A�N�Z�X.
				DISCL_FOREGROUND );	// �t�H�A�O���E���h�A�N�Z�X��.
		if( hRlt != DI_OK ){
			MessageBox( NULL, "�������ق̐ݒ莸�s", "clsDxInput::initDI", MB_OK );
		}
		// �g�p�\�ȃI�u�W�F�N�g(�{�^���Ȃ�)�̗�.
		hRlt = pPad2->EnumObjects(
			EnumObjectsCallBack,	// �I�u�W�F�N�g�񋓊֐�.
			(VOID*)hWnd,			// �R�[���o�b�N�֐��ɑ�����.
			DIDFT_ALL );			// �S�ẴI�u�W�F�N�g.
		if( hRlt != DI_OK ){
			MessageBox( NULL, "��޼ު�Ă̗񋓂Ɏ��s", "clsDxInput::initDI", MB_OK );
		}
	}

	return true;
}


//============================================================
//	���͏��X�V�֐�.
//============================================================
HRESULT clsDxInput::UpdateInputState()
{
	HRESULT hRslt;	//�֐����A�l.
	DIJOYSTATE2 js;	//�ޮ��è�����\����.

	//1frem�O�̏��.
	m_uInputStateOld = m_uInputState;

	//���͏��̏�����.
	InitInputState();

	//�ޮ��è���̐ڑ��m�F.
	if( m_pPad == NULL ){
		return E_FAIL;
	}

	//�ޮ��è�����ύX����Ă��邩���m�F.
	hRslt = m_pPad->Poll();
	if( hRslt != DI_OK && hRslt != DI_NOEFFECT )//DI_NOEFFECT:�m�F�s�v�����޲�.
	{
		//���۰ׂւ̱��������擾����.
		hRslt = m_pPad->Acquire();
		while( hRslt == DIERR_INPUTLOST ){
			hRslt = m_pPad->Acquire();
		}
		return S_OK;
	}

	//�ޮ��è�����璼���ް����擾.
	hRslt = m_pPad->GetDeviceState(
				sizeof( DIJOYSTATE2 ),	//�擾����.
				&js );					//(out)�擾�ް�.
	if( hRslt != DI_OK ){
		return hRslt;
	}

//****************************************************//

	////����۸޽è��(�è���̌X���(�V��)�̒l��600,-600�Ƃ��čl����).
	//if( js.lX > STICK_PLAY ){
	//	//�E��.
	//	AddInputState( enPKey_Right );
	//}
	//else if( js.lX < -STICK_PLAY ){
	//	//����.
	//	AddInputState( enPKey_Left );
	//}
	//if( js.lY < -STICK_PLAY ){
	//	//�㷰.
	//	AddInputState( enPKey_Up );
	//}
	//else if( js.lY > STICK_PLAY ){
	//	//����.
	//	AddInputState( enPKey_Down );
	//}

	//�è���p�x.
	m_fStickTheta = GetStickTheta( js.lY, js.lX );
	//�è���̌X��.
	m_fStickSlope = GetStickSlope( js.lY, js.lX );
	//�è���̌X������|����𔻒肷��.
	m_enStickSlope = GetStickSlopeMode( m_fStickSlope );


	//�\����.
	switch( js.rgdwPOV[0] )
	{
	case 4500://�E��.
		AddInputState( enPKey_Up );
		AddInputState( enPKey_Right );
		break;
	case 13500://�E��.
		AddInputState( enPKey_Down );
		AddInputState( enPKey_Right );
		break;
	case 22500://����.
		AddInputState( enPKey_Down );
		AddInputState( enPKey_Left );
		break;
	case 31500://����.
		AddInputState( enPKey_Up );
		AddInputState( enPKey_Left );
		break;
	case 0://��.
		AddInputState( enPKey_Up );
		break;
	case 9000://�E.
		AddInputState( enPKey_Right );
		break;
	case 18000://��.
		AddInputState( enPKey_Down );
		break;
	case 27000://��.
		AddInputState( enPKey_Left );
		break;
	}




	//����(�񋓑̂����݂̐��������Ă��Ή����y�ȏ�����).
	//��ٰ�ߊJ�n�ʒu�������Ώۂ����݂ɐݒ肷��.
	for( int iKey=enPKey_A; iKey<enPKey_Max; iKey++ ){
		if( js.rgbButtons[ iKey - enPKey_A ] & 0x80 ){
			AddInputState( (enPKey)iKey );
		}
	}



	return S_OK;
}


//============================================================
//	���͏���ǉ�����֐�.add:������.
//============================================================
void clsDxInput::AddInputState( enPKey enKey )
{
	// << ��ĉ��Z�q:���ɼ��.
	m_uInputState |= 1 << enKey;
	//m_uInputState = m_uInputState | ( 1 << enKey );�@�Ɠ���.

}

//============================================================
//	���͏�������������֐�.
//============================================================
void clsDxInput::InitInputState()
{
	m_uInputState = 0;
}



//============================================================
//	�è���̊p�x.
//============================================================
float clsDxInput::GetStickTheta( LONG lY, LONG lX )
{
	double Theta = 0.0;
	Theta = atan2( (double)lY, (double)lX );

	Theta -= M_PI_2;

	return (float)Theta;
}


//============================================================
//	�è���̌X��.
//============================================================
float clsDxInput::GetStickSlope( LONG lY, LONG lX )
{
	lY *= lY;
	lX *= lX;

	float slope = sqrtf( (float)lY + (float)lX );

	return slope;
}

//============================================================
//	�è���̌X������|����𔻒肷��.
//============================================================
enPStickSlopeMode clsDxInput::GetStickSlopeMode( float slope )
{
	enPStickSlopeMode mode = enPSSM_Stand;
	
	if( slope > abs( STICK_RUN ) ){
		mode = enPSSM_High;
	}
	else if( slope > abs( STICK_WALK ) ){
		mode = enPSSM_Low;
	}
	return mode;
}


//============================================================
//	������������֐�(�P����).
//		��UpdateInputState()�֐��ŏ�񂪍X�V����Ă��邱�Ƃ��O��.
//============================================================
bool clsDxInput::IsPressKeyEnter( enPKey enKey )
{
	if( ( m_uInputState >> enKey ) & 1 ){
		if( !( ( m_uInputStateOld >> enKey ) & 1 ) ){
				return true;
		}
	}
	return false;
}
//============================================================
//	������������֐�(������).
//		��UpdateInputState()�֐��ŏ�񂪍X�V����Ă��邱�Ƃ��O��.
//============================================================
bool clsDxInput::IsPressKeyStay( enPKey enKey )
{
	if( ( m_uInputState >> enKey ) & 1 ){
		return true;
	}
	return false;
}
//============================================================
//	������������֐�(����).
//		��UpdateInputState()�֐��ŏ�񂪍X�V����Ă��邱�Ƃ��O��.
//============================================================
bool clsDxInput::IsPressKeyExit( enPKey enKey )
{
	if( ( m_uInputStateOld >> enKey ) & 1 ){
		if( !( ( m_uInputState >> enKey ) & 1 ) ){
				return true;
		}
	}
	return false;
}



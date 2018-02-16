#ifndef _DX_INPUT_H_
#define _DX_INPUT_H_

//========================================================================================
//
//	��[dinput.h]��Ǎ��ލۂɂ��Ȃ���΂����Ȃ����ƁB.
//
//		[°�]��[��߼��]��[��ۼު�Ă���ѿح����]��.
//			[�S��]��[VC++ �ިڸ��]��[�ިڸ�؂�\��������ۼު��]��.
//				[�ݸٰ�� ̧��].
//					C:\Program Files\Microsoft DirectX SDK (June 2010)\Include
//				[ײ���� ̧��].
//					C:\Program Files\Microsoft DirectX SDK (June 2010)\Lib\x86
//
//		[��ۼު��]��[�����������è]��[�\�������è]��.
//			[�ݶ]��[����]��[�ǉ��̈ˑ�̧��].
//					dxguid.lib dinput8.lib			��DirectInput �Ŏg�p����K�v�Œ���B.
//
//		�ǉ��ˑ�̧�ق́A���L�� #pragma comment( lib, "����.lib") �ő�p�\�B.
//		���̃v���W�F�N�g�ɃR�[�h���ڐA���邱�Ƃ��l����Ƃ�����̕����y�ł悢�B.
//
//========================================================================================
#define _USE_MATH_DEFINES
#include <math.h>

#include <dinput.h>	// DirectInput�p.

// DirectX �֌W�B.
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "dinput8.lib" )	// �R���g���[������Ŏg�p�B.

//�񋓑̐錾.
//�����.
enum enPKey
{
	enPKey_Up,
	enPKey_Down,
	enPKey_Left,
	enPKey_Right,

	enPKey_A,
	enPKey_B,
	enPKey_X,
	enPKey_Y,
	enPKey_LB,
	enPKey_RB,
	enPKey_BACK,
	enPKey_START,
	enPKey_LSTICK,
	enPKey_RSTICK,

	enPKey_Max	//���ő吔.
};

//�è���̓|�����ɂ�铮��̕ω�.
enum enPStickSlopeMode
{
	enPSSM_Stand = 0,
	enPSSM_Low,
	enPSSM_High
};



class clsDxInput
{
public:
	clsDxInput();
	~clsDxInput();

	//DirectInput�����ݒ�.
	bool initDI( HWND hWnd );

	//���͏��X�V�֐�.
	HRESULT UpdateInputState();

	//���͏���ǉ�����֐�.add:������.
	void AddInputState( enPKey enKey );

	//���͏�������������֐�.
	void InitInputState();

	//������������֐�.
	bool IsPressKeyEnter( enPKey enKey );
	bool IsPressKeyStay( enPKey enKey );
	bool IsPressKeyExit( enPKey enKey );

	//�è���̊p�x.
	float GetStickTheta( LONG lY, LONG lX );
	//�è���̌X��.
	float GetStickSlope( LONG lY, LONG lX );

	//�è���̌X������|����𔻒肷��.
	enPStickSlopeMode	GetStickSlopeMode( float slope );


	float				m_fStickTheta;//Ҳ݂ɓn���p�x.
	enPStickSlopeMode	m_enStickSlope;//Ҳ݂ɓn���è���̓|���.

private:
	LPDIRECTINPUT8		 m_pDI; //DxInput��޼ު��.
	LPDIRECTINPUTDEVICE8 m_pPad;//���޲�(���۰�)��޼ު��.

	unsigned int	m_uInputState;//���͏��.
	unsigned int	m_uInputStateOld;//���͏��.
	float m_fStickSlope;//�è������.

};


#endif//#ifndef _DX_INPUT_H_

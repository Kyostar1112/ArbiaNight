#ifndef _C_XINPUT_H_
#define _C_XINPUT_H_

#include <Windows.h>
#include <Xinput.h>

#pragma comment( lib, "xinput.lib" )

//�l.
#define INPUT_TRIGGER_MIN	(0)
#define INPUT_TRIGGER_MAX	(255)
#define INPUT_THUMB_MIN		(-32768)
#define INPUT_THUMB_MAX		(32767)
#define INPUT_VIBRATION_MIN	(0)
#define INPUT_VIBRATION_MAX	(65535)



//�L�[.
#define XINPUT_UP		( XINPUT_GAMEPAD_DPAD_UP )
#define XINPUT_DOWN		( XINPUT_GAMEPAD_DPAD_DOWN )
#define XINPUT_LEFT		( XINPUT_GAMEPAD_DPAD_LEFT )
#define XINPUT_RIGHT	( XINPUT_GAMEPAD_DPAD_RIGHT )
#define XINPUT_START	( XINPUT_GAMEPAD_START )
#define XINPUT_BACK		( XINPUT_GAMEPAD_BACK )
#define XINPUT_LSTICK	( XINPUT_GAMEPAD_LEFT_THUMB )
#define XINPUT_RSTICK	( XINPUT_GAMEPAD_RIGHT_THUMB )
#define XINPUT_LB		( XINPUT_GAMEPAD_LEFT_SHOULDER )
#define XINPUT_RB		( XINPUT_GAMEPAD_RIGHT_SHOULDER )
#define XINPUT_A		( XINPUT_GAMEPAD_A )
#define XINPUT_B		( XINPUT_GAMEPAD_B )
#define XINPUT_X		( XINPUT_GAMEPAD_X )
#define XINPUT_Y		( XINPUT_GAMEPAD_Y )


class clsXInput
{
public:
	//�è���̓|�����ɂ�铮��̕ω�.
	enum enSTICK_SLOPE
	{
		enSS_NOTHING = 0,
		enSS_LOW,
		enSS_HIGH
	};

	clsXInput(){
		ZeroMemory( this, sizeof( clsXInput ) );
	}
	~clsXInput(){}

	bool UpdateStatus();
	bool UpdateKeyStatus();

	bool IsPressEnter( const WORD _padKey );
	bool IsPressStay( const WORD _padKey );
	bool IsPressExit( const WORD _padKey );


	void EndProc(){
		SetVibration( 0, 0 );
//		XInputEnable( false );
	}

	BYTE GetLTrigger(){
		return m_state.Gamepad.bLeftTrigger;
	}
	BYTE GetRTrigger(){
		return m_state.Gamepad.bRightTrigger;
	}
	SHORT GetLThumbX(){
		return m_state.Gamepad.sThumbLX;
	}
	SHORT GetLThumbY(){
		return m_state.Gamepad.sThumbLY;
	}
	SHORT GetRThumbX(){
		return m_state.Gamepad.sThumbRX;
	}
	SHORT GetRThumbY(){
		return m_state.Gamepad.sThumbRY;
	}


	//���X�e�B�b�N�̊p�x.
	float GetLStickTheta();
	//�E�X�e�B�b�N�̊p�x.
	float GetRStickTheta();

	//�e�X�e�B�b�N�̓|���.
	enSTICK_SLOPE GetLStickSlope();
	enSTICK_SLOPE GetRStickSlope();


	//�U����^���悤.
	void SetVibPowerL( int iVibL, int iTime, int iVibDecL = 0 );
	void SetVibPowerR( int iVibR, int iTime, int iVibDecR = 0 );

private:
	//�U��.
	bool SetVibration( WORD LMotorSpd, WORD RMotorSpd );

	//�X�e�B�b�N�̊p�x.
	float GetStickTheta( SHORT lY, SHORT lX );
	//�X�e�B�b�N�̌X��.
	float GetStickSlope( SHORT lY, SHORT lX );


	DWORD				m_padId;
	XINPUT_STATE		m_state;
	XINPUT_STATE		m_stateOld;//���f�p.
	XINPUT_KEYSTROKE	m_keystroke;
	XINPUT_VIBRATION	m_vibration;


	//�U���⏕.
	void VibSafe( int &iVibPower, int &iVibDec );//�͈͓��Ɏ��߂�.
	void VibDecrease( int &iVibPower, int iDecPower );//����.
	void VibTimerCnt();//�^�C�}�[�J�E���g.
	int		m_iVibL;//�U����.
	int		m_iVibR;
	int		m_iVibDecL;//���������.
	int		m_iVibDecR;
	int		m_iVibTimerL;//���܂鎞��.
	int		m_iVibTimerR;
	

};

#endif//#ifndef _C_XINPUT_H_



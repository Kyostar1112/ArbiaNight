#ifndef _C_GAME_OBJ_
#define _C_GAME_OBJ_


#define _USE_MATH_DEFINES
#include <math.h>


#include "Global.h"








class clsGameObject
{
public:
	clsGameObject();
	virtual ~clsGameObject();

	virtual void Init() = 0;

	//�����ް��֘A�t��.
	virtual void AttachModel(){};
	//�����ް��֘A�t������.
	virtual void DetatchModel(){};

	//�`��.
	virtual void Render(){};


	//�ʒu�ݒ�.
	virtual void SetPosition( D3DXVECTOR3 vPos );//SpiaMge��virtual.
	void SetPositionX( float fPosX );
	void SetPositionY( float fPosY );
	void SetPositionZ( float fPosZ );
	//�擾.
	D3DXVECTOR3 GetPosition();
	float GetPositionX();
	float GetPositionY();
	float GetPositionZ();
	//��������.
	void AddPosition( D3DXVECTOR3 vMove );
	void AddPositionX( float fMoveX );
	void AddPositionY( float fMoveY );
	void AddPositionZ( float fMoveZ );


	//��]�ݒ�.
	//�ݒ�.
	void SetRotation( D3DXVECTOR3 vRot );
	void SetRotationY( float fRotY );
	void SetRotationZ( float fRotZ );
	//�擾.
	D3DXVECTOR3 GetRotation();
	float GetRotationX();
	float GetRotationY();
	float GetRotationZ();
	//��������.
	void AddRotation( D3DXVECTOR3 vMove );
	void AddRotationY( float fMoveY );
	void AddRotationZ( float fMoveZ );


	//�g�k�ݒ�.
	void SetScale( float fScale );
	float GetScale();


	//�����ŉ��ʂ�ς���.
	int ChangeVolumeDistance( float fEarPosZ, float fThisPosZ );


protected:

	//���W���]�l���X�V����.
	virtual void UpDateModel() = 0;
	//360�`0�ɔ[�߂�.
	void ThetaOverGuard( float& theta );
	void ThetaOverGuard( double& theta );

//public:
	D3DXVECTOR3		m_vPos;		//�ʒu.
	D3DXVECTOR3		m_vRot;		//��].
	float			m_fScale;	//�g�k.

private:


};



#endif//#ifndef _C_GAME_OBJ_
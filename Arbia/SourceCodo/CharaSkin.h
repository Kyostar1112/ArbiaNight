#ifndef _C_CHARA_SKIN_H_
#define _C_CHARA_SKIN_H_

#include "GameObject.h"
#include "D3DXSKINMESH.h"//���ү���׽.

#include "Collision.h"


#include "SpShadow.h"

const float NOT_YAW_UPDATE = -999.0f;

//�A�j���[�V������t���[���H�����ݖ��̂��艟���̉���.
const double dANIM_ONE_FRAME_OVER_SOLUTION = 0.001;


class clsCharaSkin
	: public clsGameObject
{
public:
	clsCharaSkin();
	virtual ~clsCharaSkin();

	virtual void Init(){}

	//�����ݸ�.
	virtual void Render( D3DXMATRIX& mView, D3DXMATRIX& mProj,
		D3DXVECTOR3& vLight, D3DXVECTOR3& vEye,
		D3DXVECTOR4 &vColor = D3DXVECTOR4( 1.0f, 1.0f, 1.0f ,1.0f ),
		bool alphaFlg = false );

	//�����ް��̊֘A�t��.
	virtual void AttachModel( clsD3DXSKINMESH* pModel );
	//�����ް��֘A�t������.
	virtual void DetatchModel();


	//��Ұ��ݍő吔���擾.
	int GetAnimSetMax();
	//��Ұ��ݐؑ�.
	void ChangeAnimSet( int index, double dStatPos = 0.0 );
	//��Ұ��ݑ��x�ݒ�.
	void SetAnimSpeed( double dSpeed ){ m_dAnimSpeed = dSpeed; }



	//�ʒu�X�V�֐�.
	void UpdatePos();
	enDirection		m_enDir;	//����.
	float	m_fSpd;
	float	m_fYawTarget;
	float	m_fFloorY;	//���n���鍂��.


	//��߰�ޕύX.
	void SetSpeed(){
		m_pModel->m_fSpd = m_fSpd;
	}
	void AddSpeed( float fPlusSpd ){
		m_pModel->m_fSpd = m_fSpd + fPlusSpd;
	}


	//�p�x����.
	bool ThetaCheck( double dMyTheta, double dTargTheta, int iSarchTheta );

	//�����蔻��p.
	COL_STATE* GetPointerCol();


	clsD3DXSKINMESH*			m_pModel;//���ү������.



	D3DXVECTOR3	m_vRay;			//ڲ�̈ʒu.
	D3DXVECTOR3	m_vAxis;		//��]��.
//	LPD3DXMESH	m_pMeshForRay;	//ڲ��ү���p.


	//�����t���O�Z�b�g.
	void SetDropoutFlg( bool flg );

	//�����蔻��p.
	void SetColPos( D3DXVECTOR3* vPos, float fYaw = NOT_YAW_UPDATE );


protected:

	LPD3DXANIMATIONCONTROLLER	m_pAnimCtrl;//��Ұ��ݐ���p.
	double						m_dAnimSpeed;//��Ұ��ݑ��x.
	double						m_dAnimTimer;//�A�j���[�V��������.

	//��u�ŐU������Ȃ�(���X�ɐU�����).
	void YawSpnToTarg( 
		float& NowYaw, float TarYaw, 
		float TurnSpd, float TurnStop = 0.1f );


	//���W���]�l���X�V����.
	virtual void UpDateModel();

	//�����蔻��p.
	COL_STATE ColState;
	virtual void UpdateColState();//Ѱ�ނ̍Ō�Ɏg��.
//	float	m_fHeight;
//	int		m_iSarchTheta;


	bool		m_bDropout;	//�����t���O.

	clsShadow* m_pShadow;


private:

};



#endif//#ifndef _C_CHARA_SKIN_H_
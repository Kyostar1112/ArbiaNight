#ifndef _C_CHARA_STATIC_H_
#define _C_CHARA_STATIC_H_


#include "GameObject.h"
#include "DX9Mesh.h"

#include "Collision.h"

class clsCharaStatic
	: public clsGameObject
{
public:
	clsCharaStatic();
	virtual ~clsCharaStatic();

	virtual void Init(){};



	//�����ް��֘A�t���֐�clsDX9Mesh
	virtual void AttachModel( clsDX9Mesh* pModel );

	//�����ް��֘A�t�������֐�.
	virtual void DetatchModel();

	//�����ݸފ֐�.
	virtual void Render( D3DXMATRIX &mView, D3DXMATRIX &mProj,
				D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye,
				D3DXVECTOR4 vColor = D3DXVECTOR4( 1.0f,1.0f,1.0f,1.0f ),
				bool alphaFlg = false );

	//�ʒu�X�V�֐�.
	void UpdatePos();
	enDirection		m_enDir;	//����.
	float			m_fSpd;

	//�����蔻��p.
	COL_STATE* GetPointerCol();

	clsDX9Mesh*		m_pModel;

//	LPD3DXMESH	m_pMeshForRay;	//ڲ��ү���p.


	//�����蔻��p.
	void SetColPos( D3DXVECTOR3* vPos );




protected:

	//�����蔻��p.
	COL_STATE ColState;
	virtual void UpdateColState();//Ѱ�ނ̍Ō�Ɏg��.



	//���W���]�l���X�V����.
	virtual void UpDateModel();

};


#endif//#ifndef _C_CHARA_STATIC_H_
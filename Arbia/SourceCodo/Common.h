#ifndef _C_COMMON_H_
#define _C_COMMON_H_


//�ݸٰ��.
#include "Global.h"

//���_�̍\����.
struct SpriteVertex
{
	D3DXVECTOR3 vPos;	//�ʒu.
	D3DXVECTOR2 vTex;	//ø������W.
};

//�������\����.
struct WHSIZE_FLOAT
{
	float w;
	float h;
};

//���ʸ׽(�e�׽).
class clsCommon
{
public:
	clsCommon(){};
	virtual ~clsCommon(){};

	//����(��̧������)�ݒ�̐؂�ւ�.
	void SetBlend( bool flg );


	//�����؂Ɉ��.
	ID3D11Device*			m_pDevice11;		//���޲���޼ު��.
	ID3D11DeviceContext*	m_pDeviceContext11;	//���޲���÷��.

	ID3D11BlendState*		m_pBlendState;	//�����޽ð�.


private:

};

#endif//#define _C_COMMON_H_

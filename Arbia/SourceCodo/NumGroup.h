#ifndef _NUM_GROUP_H_
#define _NUM_GROUP_H_

#include "Sprite2D.h"
#include "Mymacro.h"
#include "Common.h"//���ʸ׽.
#include <memory>


using namespace std;



class clsNumGrp
{
public:
	clsNumGrp();
	~clsNumGrp();

	//�ŏ��̏�����( �N���X����������� ).
	//��P�^�ڂ̑��x ��P�^�ڂ̑��x �^�C�}�[���ۂ�.
	virtual void Create( ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11 );

	//���ڈȍ~�̏�����.
	virtual void ReSet();

	void SetPos( D3DXVECTOR3 vPos );
	void AddPos( D3DXVECTOR3 vPos );

	void Move();

	void Render();

	//���𑝂₷.
	virtual void PlusNum();
	//�������炷.
	void MinusNum();
	//�������ߑł�.
	void SetNum( int iNum );


	int GetTime(){
		return m_iRealNum;
	}

protected:


	//���Z�b�g : Set Parameter.
	void SetParam( int iRealNum );

	//�����l�����W�n�ɕϊ�.
	float ConvNum( float fRendNum, bool bSixFlg = false );//conversion : �ϊ�.

	D3DXVECTOR3 m_vPos;

	//�񌅌Œ�.
	clsSprite2D*	NumImage[2];
	int				m_iRealNum;//�����l.
	float			m_fRendNum[2];//�`��( ��ʂɌ����� )�̐��l( m_iRealNum����P�^������ɕ������ꂽ���� ).
	float			m_fNumU[2];//���W�l.


	//�^�[�Q�b�g�Ɏ����l���߂Â��� : approach_to_target.
	void	ApproachTargetNum();
	int		m_iDiffNum;//���Ƃǂꂭ�炢�ŖړI�B������?.

	bool	 m_bSixDecimal;//6�i��?.

	int		m_iMax;//�ő�l.
};


#endif//#ifndef _NUM_GROUP_H_
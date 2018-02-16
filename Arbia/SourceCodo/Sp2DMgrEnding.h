#ifndef _SP_2D_MANAGER_ENDING_SCENE_TXT_H_
#define _SP_2D_MANAGER_ENDING_SCENE_TXT_H_

#include"Sp2DMgrPushButn.h"
#include"Sprite2D.h"

class clsSp2dMgrEnding
{
public:
	clsSp2dMgrEnding();
	~clsSp2dMgrEnding();

	void Create(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);
	void Init();
	void Render();
	void Release();

	bool GetEndRollEnd()
	{
		return m_bEndingEnd;
	}
	void SetPushButtun(bool bPushButtun)
	{
		m_bPushButtun=bPushButtun;
	}

private:

	bool m_bEndingEnd;//true�ŏI��.

	bool m_bPushButtun;//�{�^����������Ă��邩.

	unique_ptr<clsSprite2D> m_smpEndRoll;
	unique_ptr<clsSprite2D> m_smpThank;

	unique_ptr<clsPushTxt>  m_smpPushTxt;
};

#endif//#ifndef _SP_2D_MANAGER_ENDING_SCENE_TXT_H_
#ifndef _SP2D_MANAGER_TITLE_SCENE_H_
#define _SP2D_MANAGER_TITLE_SCENE_H_

#include "Sp2DMgrPushButn.h"
#include "MyMacro.h"

class clsSp2dMgrTitle
{
public:
	clsSp2dMgrTitle();
	~clsSp2dMgrTitle();
	void Create(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);
	void Init();
	void Render();
	void Release();
	void Transmission();
	void SetTransmissionFlg(bool TransmissionFlg)
	{
		m_bTransmissionFlg = TransmissionFlg;
	}
private:
	bool m_bTransmissionFlg;//True�Ȃ瓧�߂��Ă���false�Ȃ牽�����Ȃ�.
	//�^�C�g���p.
	unique_ptr<clsSprite2D> m_smpTitleLogo;	//�^�C�g�����S�˂��ł��.
	unique_ptr<clsPushTxt> m_smpPushTxt;	//PUSH KET�˂��ł��.
};
#endif //#ifndef _SP2D_MANAGER_TITLE_SCENE_H_

#ifndef _SP_2D_MANAGER_OVER_SCENE_TXT_H_
#define _SP_2D_MANAGER_OVER_SCENE_TXT_H_

#include"Sprite2D.h"

class clsSp2dMgrOverTxt
{
public:
	clsSp2dMgrOverTxt();
	~clsSp2dMgrOverTxt();

	void Create(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);
	void Init();
	void Render();
	void Release();

private:
	
	float m_fSpeed = 5.0f;
	float m_fAccel = -0.01f;


	unique_ptr<clsSprite2D> m_smpOverTxt;

};

#endif//#ifndef _SP_2D_MANAGER_OVER_SCENE_TXT_H_
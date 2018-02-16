#include "Sp2DMgrOver.h"

clsSp2dMgrOver::clsSp2dMgrOver()
{
}

clsSp2dMgrOver::~clsSp2dMgrOver()
{
}

void clsSp2dMgrOver::Create(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_smpPushTxt = make_unique<clsPushTxt>();
	m_smpOverTxt = make_unique<clsSp2dMgrOverTxt>();

	m_smpPushTxt->Create(pDevice11, pContext11);
	m_smpOverTxt->Create(pDevice11, pContext11);

}

void clsSp2dMgrOver::Init()
{
	m_smpPushTxt->Init();
	m_smpOverTxt->Init();
}

void clsSp2dMgrOver::Render()
{
	m_smpPushTxt->Render();
	m_smpOverTxt->Render();
}

void clsSp2dMgrOver::Release()
{
	m_smpPushTxt->Release();
	m_smpPushTxt.reset();
	m_smpPushTxt = NULL;

	m_smpOverTxt->Release();
	m_smpOverTxt.reset();
	m_smpOverTxt = NULL;
}
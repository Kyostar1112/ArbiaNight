#include "Sp2DMgrOverTxt.h"
//íËêî.
namespace ConstantOver
{
	const WHSIZE_FLOAT CENTER_POS = { WND_W / 2, WND_H / 2 };
}

clsSp2dMgrOverTxt::clsSp2dMgrOverTxt()
{
}

clsSp2dMgrOverTxt::~clsSp2dMgrOverTxt()
{
}

void clsSp2dMgrOverTxt::Create(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_smpOverTxt = make_unique<clsSprite2D>();
	m_smpOverTxt->Create(pDevice11, pContext11, "Data\\Image\\GameOver.png");
}

void clsSp2dMgrOverTxt::Init()
{
	m_smpOverTxt->Init();
	m_smpOverTxt->SetPosX(ConstantOver::CENTER_POS.w - m_smpOverTxt->GetCenterDisp().w);
	m_smpOverTxt->SetPosY(-1 * (m_smpOverTxt->GetSs().Disp.h));
	m_smpOverTxt->SetAlpha(1.0f);

	m_fSpeed = 5.0f;
	m_fAccel = -0.03f;
}
void clsSp2dMgrOverTxt::Render()
{
	//GETKEY_DOWN('U')
	//{
	//	m_fSpeed = 5.0f;
	//	m_fAccel = -0.03f;
	//}

	if (WND_H / 2 - m_smpOverTxt->GetCenterDisp().h > m_smpOverTxt->GetPos().y)
	{
		if (m_fSpeed > 0.0f)
		{
			m_fSpeed += m_fAccel;
		}
		m_smpOverTxt->AddPosY(m_fSpeed);
	}

	m_smpOverTxt->Render();
}

void clsSp2dMgrOverTxt::Release()
{
	m_smpOverTxt->Release();

}

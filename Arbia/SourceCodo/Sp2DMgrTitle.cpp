#include "Sp2DMgrTitle.h"

//�萔.
namespace ConstantTitle
{
	const WHSIZE_FLOAT CENTER_POS = { WND_W / 2, WND_H / 2 };

	const float ADJUSTTITLELOGOH = 100.0f;

	const float AlphaPoint = -0.01f;
}

clsSp2dMgrTitle::clsSp2dMgrTitle()
{
}

clsSp2dMgrTitle::~clsSp2dMgrTitle()
{
	Release();
}

void clsSp2dMgrTitle::Create(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_smpTitleLogo = make_unique<clsSprite2D>();	//�^�C�g�����S�˂��ł��.
	m_smpPushTxt = make_unique<clsPushTxt>();	//PUSH KET�˂��ł��.
	m_smpPushTxt->Create(pDevice11, pContext11);

	//���S�T�C�Y��2�{�ɂ���.
	m_smpTitleLogo->Create(pDevice11, pContext11, "Data\\Image\\TitleLogo.png");
	m_smpTitleLogo->MulDisp(2.0f);
}

void clsSp2dMgrTitle::Init()
{
	m_smpTitleLogo->Init();
	m_smpPushTxt->Init();
	m_smpTitleLogo->SetAlpha(1.0f);
	m_bTransmissionFlg = false;
}

void clsSp2dMgrTitle::Render()
{
	m_smpTitleLogo->SetPos(ConstantTitle::CENTER_POS.w - m_smpTitleLogo->GetCenterDisp().w,
		ConstantTitle::CENTER_POS.h - m_smpTitleLogo->GetCenterDisp().h - ConstantTitle::ADJUSTTITLELOGOH);
	m_smpTitleLogo->Render();

	m_smpPushTxt->Render();
	Transmission();
}
void clsSp2dMgrTitle::Transmission()
{
	if (m_bTransmissionFlg)
	{
		m_smpTitleLogo->AddAlpha(ConstantTitle::AlphaPoint);
		m_smpPushTxt->AddAlpha(ConstantTitle::AlphaPoint);
	}
}

void clsSp2dMgrTitle::Release()
{
	m_smpTitleLogo.reset();

	m_smpPushTxt.reset();

}
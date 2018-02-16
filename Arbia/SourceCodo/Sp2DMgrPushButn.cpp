#include "Sp2DMgrPushButn.h"

//íËêî.
namespace ConstantPushTxt
{
	const WHSIZE_FLOAT CENTER_POS = { WND_W/2, WND_H/2 };

	float ADJUSTPUSHTXTH   = 285.0f;

	float ADJUSTABUTTONW   = -60.0f;
	float ADJUSTABUTTONH   = 50.0f;
}
clsPushTxt::clsPushTxt()
{
}

clsPushTxt::~clsPushTxt()
{
}

void clsPushTxt::Create(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_smpAButton             = make_unique<clsSprite2D>();	//AÉ{É^Éì.
	m_smpPushTxt             = make_unique<clsSprite2D>();	//PUSH KETÇÀÇ•Ç≈Ç‚ÇÒÇ∑.

	m_smpPushTxt->Create( pDevice11, pContext11, "Data\\Image\\PushButtun.png");
	m_smpPushTxt->MulDisp(0.5f);
	m_smpPushTxt->SetAlpha(1.0f);

	m_smpAButton->Create(pDevice11, pContext11, "Data\\Image\\AButtun.png");
	m_smpAButton->SetDispW(m_smpPushTxt->GetSs().Disp.w/4);
	m_smpAButton->SetDispH(m_smpPushTxt->GetSs().Disp.w/4);
	m_smpAButton->SetAlpha(1.0f);
}

void clsPushTxt::Init()
{
	m_smpPushTxt->Init();
	m_smpAButton->Init();
	m_smpPushTxt->SetAlpha(1.0f);
	m_smpAButton->SetAlpha(1.0f);
	m_enAlphaMode = clsPushTxt::Flassing;
}

void clsPushTxt::Render()
{

	float XPos = ConstantPushTxt::CENTER_POS.w - m_smpPushTxt->GetCenterDisp().w/2 - m_smpPushTxt->GetSs().Disp.w/2 - ConstantPushTxt::ADJUSTABUTTONW;

	m_smpPushTxt->SetPos(XPos,
		ConstantPushTxt::CENTER_POS.h - m_smpPushTxt->GetCenterDisp().h + ConstantPushTxt::ADJUSTPUSHTXTH);
	m_smpPushTxt->Render();

	m_smpAButton->SetPos(m_smpPushTxt->GetPos().x + m_smpPushTxt->GetSs().Disp.w + ConstantPushTxt::ADJUSTABUTTONW,
		m_smpPushTxt->GetPos().y + ConstantPushTxt::ADJUSTABUTTONH);
	m_smpAButton->Render();

	switch (m_enAlphaMode)
	{
		case clsPushTxt::Flassing:
			m_smpPushTxt->Flashing(0.01f);
			m_smpAButton->Flashing(0.01f);
			break;
		case clsPushTxt::Out:
			m_smpPushTxt->AddAlpha(m_fAlphaPoint);
			m_smpAButton->AddAlpha(m_fAlphaPoint);
			break;
		default:
			break;
	}
}

void clsPushTxt::AddAlpha(float AlphaPoint)
{
	SetAlphaMode(clsPushTxt::Out);
	m_fAlphaPoint = AlphaPoint;
}

void clsPushTxt::Release()
{
	m_smpAButton->Release();
	m_smpAButton.reset();
	m_smpAButton = NULL;

	m_smpPushTxt->Release();
	m_smpPushTxt.reset();
	m_smpPushTxt = NULL;
}
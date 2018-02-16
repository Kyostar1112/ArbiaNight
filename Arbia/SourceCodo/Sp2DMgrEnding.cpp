#include "Sp2DMgrEnding.h"
//定数.
namespace ConstantEnding
{
	const WHSIZE_FLOAT CENTER_POS = { WND_W / 2, WND_H / 2 };
//	const float NONPUSH_SCL_SPD = -7.0f;
	const float NONPUSH_SCL_SPD = -1.5f;
	const float PUSH_SCL_SPD = -20.0f;
	const float THANK_TXT_POS_Y = 40.0f;
}

#ifdef Tahara
const float fTHANK_YOU_FINAL_POS_Y = 160.0f;	//最終的な「ありがとう」の位置.
const float fTHANK_YOU_FIRST_POS_Y_PLUS = 400.0f;//０から上↑にしたことでずらす初期座標.
#endif //#ifdef Tahara


clsSp2dMgrEnding::clsSp2dMgrEnding()
{
}

clsSp2dMgrEnding::~clsSp2dMgrEnding()
{
}

void clsSp2dMgrEnding::Create(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_smpPushTxt = make_unique<clsPushTxt>();
	m_smpPushTxt->Create(pDevice11, pContext11);

	m_smpEndRoll = make_unique<clsSprite2D>();
	m_smpEndRoll->Create(pDevice11, pContext11, "Data\\Image\\StaffLool.png");

	m_smpThank = make_unique<clsSprite2D>();
	m_smpThank->Create(pDevice11, pContext11, "Data\\Image\\EndingThankYou.png");
}
void clsSp2dMgrEnding::Init()
{
	//m_smpEndingNameTxt->
	//m_smpEndingSiteTxt->
	//m_smpEndingThankTxt->
	m_bEndingEnd = false;
	m_bPushButtun= false;
	m_smpEndRoll->MulDisp(0.5f);

	m_smpThank->MulDisp(0.5f);

	m_smpEndRoll->SetPos(WND_W/2 - m_smpEndRoll->GetSs().Disp.w/2,WND_H);

	m_smpThank->SetPos(WND_W/2 - m_smpThank->GetSs().Disp.w/2,m_smpEndRoll->GetSs().Disp.h+m_smpEndRoll->GetPos().y + fTHANK_YOU_FIRST_POS_Y_PLUS );

}
void clsSp2dMgrEnding::Render()
{
	if ( m_smpThank->GetPos().y > fTHANK_YOU_FINAL_POS_Y  )
	{
		if (m_bPushButtun)
		{
			m_smpEndRoll->AddPosY(ConstantEnding::PUSH_SCL_SPD);
		}
		else
		{
			m_smpEndRoll->AddPosY(ConstantEnding::NONPUSH_SCL_SPD);
		}
	}
	else
	{
		m_bEndingEnd = true;
	}

	m_smpThank->SetPosY(m_smpEndRoll->GetSs().Disp.h+m_smpEndRoll->GetPos().y + fTHANK_YOU_FIRST_POS_Y_PLUS );

	m_smpEndRoll->Render();

	m_smpThank->Render();

	if (m_bEndingEnd)
	{
		m_smpPushTxt->Render();
	}
}

void clsSp2dMgrEnding::Release()
{
	SAFE_RELEASE(m_smpEndRoll);
	SAFE_RELEASE(m_smpPushTxt);
}

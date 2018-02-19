#include "Sp2DMgrMain.h"

#ifdef Tahara
const float fLIVES_X = static_cast<float>( WND_W - 128 );
const float fDISCOVER_X = 500.0f;//������UI.
#endif //#ifdef Tahara



//namespace MainScene{
//	const WHSIZE_FLOAT ICONPOS = { 1050.0f, 5.0f };
//	const WHSIZE_FLOAT ICONSIZE = { 108.0f, 108.0f };
//
//	const WHSIZE_FLOAT CENTER_POS = { WND_W / 2, WND_H / 2 };
//}

clsSp2dMgrMain::clsSp2dMgrMain()
{
	m_smpActTxt = make_unique<clsActTxt>();	//�W�����v�A�U���˂��ł��.
	m_smpXButton = make_unique<clsSprite2D>();	//X�{�^���˂��ł��.
	m_smpAButton = make_unique<clsSprite2D>();	//A�{�^��.

#ifdef Tahara
	m_smpTimerGrp	= make_unique<clsTimerGrp>();
	m_smpDisc		= make_unique<clsDiscover>();
	m_smpLives		= make_unique<clsLives>();
#endif //#ifdef Tahara
}

clsSp2dMgrMain::~clsSp2dMgrMain()
{
	Release();
}

void clsSp2dMgrMain::Create( HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{

	m_smpActTxt->Create(pDevice11, pContext11, "Data\\Image\\MainTxt.png");

	m_smpXButton->Create(pDevice11, pContext11, "Data\\Image\\XButtun.png");
	m_smpAButton->Create(pDevice11, pContext11, "Data\\Image\\AButtun.png");

#ifdef Tahara
	//����.
	m_smpTimerGrp->Create( hWnd, pDevice11, pContext11 );
	m_smpDisc->Create( pDevice11, pContext11 );
	m_smpLives->Create( pDevice11, pContext11 );
#endif//#ifdef Tahara

}

//����ʂ�.
void clsSp2dMgrMain::Init()
{
	m_smpActTxt->Init();

	//�A�N�V����
	m_smpActTxt->SetDispH(m_smpActTxt->GetSs().Base.h / 2);
	m_smpActTxt->SetDispW(m_smpActTxt->GetSs().Base.w / 2);
	m_smpXButton->SetDispH(m_smpActTxt->GetCenterDisp().h);
	m_smpXButton->SetDispW(m_smpActTxt->GetCenterDisp().h);
	m_smpAButton->SetDispH(m_smpActTxt->GetCenterDisp().h);
	m_smpAButton->SetDispW(m_smpActTxt->GetCenterDisp().h);

	m_smpActTxt->SetPos(0.0f, MainScene::CENTER_POS.h - m_smpActTxt->GetCenterDisp().h);
	m_smpXButton->SetPos(m_smpActTxt->GetPos().x + m_smpActTxt->GetSs().Disp.w, m_smpActTxt->GetCenterDisp().h + m_smpActTxt->GetPos().y);
	m_smpAButton->SetPos(m_smpActTxt->GetPos().x + m_smpActTxt->GetSs().Disp.w, m_smpActTxt->GetPos().y);

	m_smpActTxt->SetPosX(-1 * (m_smpXButton->GetSs().Disp.w +
		m_smpActTxt->GetSs().Disp.w));

	m_smpXButton->SetPosX((m_smpActTxt->GetPos().x +
		m_smpActTxt->GetSs().Disp.w));

	m_smpAButton->SetPosX((m_smpActTxt->GetPos().x +
		m_smpActTxt->GetSs().Disp.w));
	m_smpAButton->SetAlpha(1.0f);

	m_fMoveTopTxtPoint = 0.0f;


#ifdef Tahara
	//����.
	m_smpTimerGrp->SetPos( D3DXVECTOR3( 0.0f, -MainScene::ICONSIZE.h, 0.0f ) );
	m_smpDisc->SetPos( D3DXVECTOR3( fDISCOVER_X, -MainScene::ICONSIZE.h, 0.0f ) );
	m_smpLives->SetPos( D3DXVECTOR3( MainScene::ICONPOS.w, -MainScene::ICONSIZE.h, 0.0f ) );

	ReSetTimer();
	ReSetLives();
	ReSetDisc();


#endif//#ifdef Tahara

}



//( ���C��UI�� )�^�C�g���ł̏�����.
void clsSp2dMgrMain::InitTitle()
{
	m_smpActTxt->SetPos(0.0f, MainScene::CENTER_POS.h - m_smpActTxt->GetCenterDisp().h);
	m_smpXButton->SetPos(m_smpActTxt->GetPos().x + m_smpActTxt->GetSs().Disp.w, m_smpActTxt->GetCenterDisp().h + m_smpActTxt->GetPos().y);
	m_smpAButton->SetPos(m_smpActTxt->GetPos().x + m_smpActTxt->GetSs().Disp.w, m_smpActTxt->GetPos().y);

	m_smpActTxt->SetPosX(-1 * (m_smpXButton->GetSs().Disp.w +
		m_smpActTxt->GetSs().Disp.w));

	m_smpXButton->SetPosX((m_smpActTxt->GetPos().x +
		m_smpActTxt->GetSs().Disp.w));

	m_smpAButton->SetPosX((m_smpActTxt->GetPos().x +
		m_smpActTxt->GetSs().Disp.w));
	m_smpAButton->SetAlpha(1.0f);

	m_fMoveTopTxtPoint = 0.0f;


#ifdef Tahara
	//����.
	m_smpTimerGrp->SetPos( D3DXVECTOR3( 0.0f, -MainScene::ICONSIZE.h, 0.0f ) );
	m_smpDisc->SetPos( D3DXVECTOR3( fDISCOVER_X, -MainScene::ICONSIZE.h, 0.0f ) );
	m_smpLives->SetPos( D3DXVECTOR3( MainScene::ICONPOS.w, -MainScene::ICONSIZE.h, 0.0f ) );

	ReSetTimer();
	ReSetLives();
	ReSetDisc();


#endif//#ifdef Tahara

}


void clsSp2dMgrMain::Render()
{
	MoveTopTxt();

	m_smpActTxt->Move(m_smpXButton->GetSs().Disp.w);

	m_smpXButton->SetPosX((m_smpActTxt->GetPos().x +
		m_smpActTxt->GetSs().Disp.w));

	m_smpAButton->SetPosX((m_smpActTxt->GetPos().x +
		m_smpActTxt->GetSs().Disp.w));

	m_smpActTxt->Render();

	m_smpXButton->Render();

	m_smpAButton->Render();

#ifdef Tahara
	m_smpTimerGrp->Update();
	m_smpTimerGrp->Render();
	m_smpDisc->Update();
	m_smpDisc->Render();
	m_smpLives->Update();
	m_smpLives->Render();
#endif//#ifdef Tahara
}

void clsSp2dMgrMain::ActTxtMove()
{
	m_smpActTxt->Move(m_smpXButton->GetSs().Disp.w);
	m_smpXButton->SetPosX((m_smpActTxt->GetPos().x +
		m_smpActTxt->GetSs().Disp.w));
	m_smpAButton->SetPosX((m_smpActTxt->GetPos().x +
		m_smpActTxt->GetSs().Disp.w));
}
void clsSp2dMgrMain::ActTxtMoveIn()
{
	m_smpActTxt->InStart();
}
void clsSp2dMgrMain::ActTxtMoveOut()
{
	m_smpActTxt->OutStart();
}

void clsSp2dMgrMain::Release()
{
	m_smpActTxt->Release();
	m_smpXButton->Release();
	m_smpAButton->Release();
#ifdef Tahara
	//����.
	if (m_smpLives) {
		m_smpLives.reset();
	}
	if (m_smpDisc) {
		m_smpDisc.reset();
	}
	if (m_smpTimerGrp) {
		m_smpTimerGrp.reset();
	}
#endif//#ifdef Tahara
}
#include"UiManager.h"

//�萔.
const WHSIZE_FLOAT CENTER_POS = { WND_W / 2, WND_H / 2 };

const WHSIZE_FLOAT ICONSIZE = { 180.0f, 180.0f };

const WHSIZE_FLOAT ICONPOS  = { 980.0f, 5.0f };

const WHSIZE_FLOAT NUMSIZE  = { 64.0f, 64.0f };


clsUiManagar::clsUiManagar()
{
	//ZeroMemory(this,sizeof(this));
}

clsUiManagar::~clsUiManagar()
{
	Delete();
}

void clsUiManagar::Init( HWND hWnd,ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_smpBlack = make_unique<clsSprite2D>();  //�Ó]�p.

	m_smpWhite = make_unique<clsSprite2D>(); //�Ó]�p.

	//�����̃V�[���Ŏg���ꍇ�͂���.

	m_smpTitleScene = make_unique<clsSp2dMgrTitle>();	 //�^�C�g���p.

	m_smpMainScene = make_unique<clsSp2dMgrMain>();
	m_smpActTxt  = make_unique<clsActTxt>();	//�W�����v�A�U���˂��ł��.
	m_smpXButton = make_unique<clsSprite2D>();	//X�{�^���˂��ł��.
	m_smpAButton = make_unique<clsSprite2D>();	//A�{�^��.

	//�Q�[���I�[�o�p.
	m_smpOverScene = make_unique<clsSp2dMgrOver>();
	m_smpOverScene->Create( pDevice11, pContext11 );

	//���U���g�p.
	m_smpResult = make_unique<clsSp2dMgrReslt>();

	//�G���f�B���O.
	m_smpEndingScene = make_unique<clsSp2dMgrEnding>();

	m_smpBlack->Create(pDevice11, pContext11, "Data\\Image\\Black.png");

	m_smpWhite->Create(pDevice11, pContext11, "Data\\Image\\White.png");

	//�^�C�g���V�[��.
	m_smpTitleScene->Create(pDevice11, pContext11);

	//���C���V�[��.
	m_smpMainScene->Create( hWnd, pDevice11, pContext11);

	m_smpActTxt->Create(pDevice11, pContext11, "Data\\Image\\MainTxt.png");

	m_smpXButton->Create(pDevice11, pContext11, "Data\\Image\\XButtun.png");
	m_smpAButton->Create(pDevice11, pContext11, "Data\\Image\\AButtun.png");


	//���U���g�p.
	m_smpResult->Create( hWnd, pDevice11, pContext11 );

	//�G���f�B���O�p.
	m_smpEndingScene->Create(pDevice11, pContext11);
	Init();

}
void clsUiManagar::RenderTitle()
{
	RenderMain();
	m_smpTitleScene->Render();
	BlackOut();
}
void clsUiManagar::RenderMain()
{
	m_smpMainScene->Render();
	BlackOut();
}
void clsUiManagar::RenderOver()
{
	m_smpOverScene->Render();
	BlackOut();
}
void clsUiManagar::RenderResult()
{
	RenderMain();
	m_smpResult->Render();
	BlackOut();
}
void clsUiManagar::RenderEnding()
{
	m_smpEndingScene->Render();
	BlackOut();
}

void clsUiManagar::SceneTitle()
{
}
void clsUiManagar::SceneMain()
{
	GETKEY_DOWN('U')
		m_smpMainScene->ActTxtMoveIn();
	GETKEY_DOWN('Y')
		m_smpMainScene->ActTxtMoveOut();

	m_smpActTxt->Move();
}

void clsUiManagar::SceneOver()
{
}
void clsUiManagar::SceneResult()
{
	m_smpResult->UpDate();
}
void clsUiManagar::SceneEnding()
{
}
void clsUiManagar::ChangeTitleInit()
{
	m_smpTitleScene->Init();
	m_smpMainScene->ActTxtMoveOut();

#ifdef Tahara
	m_smpMainScene->InitTitle();
	SetTimerStop( true );//�^�C�g����ʂł͓������Ȃ�.
	AddPosYUiSet( -fINIT_MAIN_UI_TRIO_ADD_POS_Y );


#endif //Tahara
}
void clsUiManagar::ChangeMainInit()
{
	m_smpMainScene->Init();
	m_smpMainScene->ActTxtMoveIn();

}

void clsUiManagar::ChangeResultInit()
{
	Init();
	m_smpResult->StartSet();

	m_smpAButton->SetAlpha(1.0f);
}
void clsUiManagar::ChangeOverInit()
{
	Init();

//	m_smpGameOverTxt->SetPosX(CENTER_POS.w - m_smpGameOverTxt->GetCenterDisp().w);
//	m_smpGameOverTxt->SetPosY(-1 * (m_smpGameOverTxt->GetSs().Disp.h));

//	m_smpAButton->SetAlpha(1.0f);
}
void clsUiManagar::ChangeEndingInit()
{
	Init();
}

void clsUiManagar::BlackStart(float ChaAmo, bool Color)
{
	if ( m_smpBlack->m_BlackMode == Idle && Color )
	{
		m_fChangePoint = ChaAmo;
		m_bColor = Color;
		m_smpBlack->m_BlackMode = In;
		m_smpBlack->SetAlpha(0.0f);
	}
	else if ( m_smpWhite->m_BlackMode == Idle && !Color )
	{
		m_fChangePoint = ChaAmo;
		m_bColor = Color;
		m_smpWhite->m_BlackMode = In;
		m_smpWhite->SetAlpha(0.0f);
	}
}
void clsUiManagar::BlackOut()
{
	if (m_bColor)
	{
		if (m_smpBlack->m_BlackMode != Idle)
		{
			if (m_smpBlack->m_BlackMode == Change)
			{
				m_smpBlack->m_BlackMode = Out;
			}
			float tmp = m_smpBlack->GetAlpha();
			m_smpBlack->SetPos(0.0f, 0.0f);
			if (m_smpBlack->m_BlackMode == In){
				m_smpBlack->AddAlpha(m_fChangePoint);
				if (tmp > 1.0f){
					m_smpBlack->m_BlackMode = Change;
				}
			}
			else
			{
				if (m_smpBlack->m_BlackMode == Out)
				{
					if (m_smpBlack->GetAlpha() > 0.0f)
					{
						m_smpBlack->AddAlpha(-1 * m_fChangePoint);
					}
					else
					{
						m_smpBlack->m_BlackMode = Idle;
						m_smpBlack->Init();
					}
				}
			}
			m_smpBlack->Render();
		}
	}
	else{
		if (m_smpWhite->m_BlackMode != Idle)
		{
			m_smpWhite->SetPos(0.0f, 0.0f);
			if (m_smpWhite->m_BlackMode == Change)
			{
				m_smpWhite->m_BlackMode = Out;
			}
			float tmp = m_smpWhite->GetAlpha();
			if (m_smpWhite->m_BlackMode == In)
			{
				m_smpWhite->AddAlpha(m_fChangePoint);
				if (tmp > 1.0f)
				{
					m_smpWhite->m_BlackMode = Change;
				}
			}
			else
			{
				if (m_smpWhite->m_BlackMode == Out)
				{
					if (m_smpWhite->GetAlpha() > 0.0f)
					{
						m_smpWhite->AddAlpha(-1 * m_fChangePoint);
					}
					else
					{
						m_smpWhite->m_BlackMode = Idle;
						m_smpWhite->Init();
					}
				}
			}
			m_smpWhite->Render();
		}
	}
}

void clsUiManagar::Init()
{
	m_smpBlack->Init();	//�Ó]�p.
	m_smpActTxt->Init();

	m_smpTitleScene->Init();	//�^�C�g���p.

	m_smpActTxt->Init();	//�W�����v�A�U���˂��ł��.
	m_smpXButton->Init();	//X�{�^���˂��ł��.
	m_smpAButton->Init();	//A�{�^��.
	//�Q�[���I�[�o�p.
	m_smpOverScene->Init();	//�Q�[���I�[�o�[�e�L�X�g�˂��ł��.

	//���U���g�p.
	m_smpResult->Init();	//���U���g�e�L�X�g�˂��ł��.

	//�G���f�B���O.
	m_smpEndingScene->Init();
}
void clsUiManagar::Delete()
{
#if 1

	if (m_smpBlack) {
		m_smpBlack.reset();
	}
	if (m_smpWhite) {
		m_smpWhite.reset();
	}

	//�^�C�g���p.
	//if (m_smpTitleLogo){
	//	m_smpTitleLogo.reset();
	//}
	//if (m_smpPushTxt){
	//	m_smpPushTxt.reset();
	//}

	if (m_smpMainScene){
		m_smpMainScene.reset();
	}

	if (m_smpActTxt){
		m_smpActTxt.reset();
	}

	if (m_smpXButton){
		m_smpXButton.reset();
	}

	if (m_smpAButton){
		m_smpAButton.reset();
	}

	//�Q�[���I�[�n�J�[�p.
	if (m_smpOverScene){
		m_smpOverScene.reset();
	}

	//���U���g�p.
	if (m_smpResult){
		m_smpResult.reset();
	}

	//�G���f�B���O�p.
	if (m_smpEndingScene){
		m_smpEndingScene.reset();
	}


#endif // 0
}
#include "Main.h"
#include <stdio.h>

//====��邱�ƃ��X�g==========================================
	//Pendulum��Init()���.
	//���m�̂���(�A���r�A�̍U��).
//============================================================


//��۰��ٕϐ�.
clsMain* g_pClsMain = nullptr;


//-----�U��-----//.
//�A���r�A�̏R��q�b�g.
const unsigned short usVIB_KICK_POWER = INPUT_VIBRATION_MAX;
const int iVIB_KICK_TIME = 15;
//�h�A�j��.
const unsigned short usVIB_DOOR_POWER = INPUT_VIBRATION_MAX;
const int iVIB_DOOR_TIME = 30;
//���Ƃ����M�V�M�V.
const unsigned short usVIB_COVER_POWER = INPUT_VIBRATION_MAX / 10;
const int iVIB_COVER_TIME = 82;
const int iVIB_COVER_DEC = 128;



//BGM.
//�N��.
#define ALIAS_NAME_BGM_START_UP "StartUp"
#define  FILE_PATH_BGM_START_UP "BGM\\000StartUp\\StartUp.mp3"
const int	  iVOL_BGM_START_UP = 250;

//�^�C�g��.
#define ALIAS_NAME_BGM_TITLE "Title"
#define  FILE_PATH_BGM_TITLE "BGM\\100Title\\100Title.mp3"
const int	  iVOL_BGM_TITLE = 350;

//���C��.
#define ALIAS_NAME_BGM_MAIN "Main"
#define  FILE_PATH_BGM_MAIN "BGM\\200Main\\010Stage.mp3"
const int	  iVOL_BGM_MAIN = 250;

//���U���g.
#define ALIAS_NAME_BGM_RESULT "Result"
#define  FILE_PATH_BGM_RESULT "BGM\\300Result\\200ResultJingle.mp3"
const int	  iVOL_BGM_RESULT = 750;

//�N���A.
#define ALIAS_NAME_BGM_CLEAR "Clear"
#define  FILE_PATH_BGM_CLEAR "BGM\\400Clear\\100EndRoll.mp3"
const int	  iVOL_BGM_CLEAR = 200;

//�I�[�o�[.
#define ALIAS_NAME_BGM_OVER "Over"
#define  FILE_PATH_BGM_OVER "BGM\\500Over\\100Bye.mp3"
const int	  iVOL_BGM_OVER = 300;


//SE.
//���邢���.
#define ALIAS_NAME_SE_ENTER "Enter"
#define  FILE_PATH_SE_ENTER "SE\\700Button\\100Enter.wav"
const int	  iVOL_SE_ENTER = 300;

//�Â����.
#define ALIAS_NAME_SE_EXIT "Exit"
#define  FILE_PATH_SE_EXIT "SE\\700Button\\200Exit.wav"
const int	  iVOL_SE_EXIT = 300;


//���C�g����.
const D3DXVECTOR3 vLIGHT_DIR = { 0.0f, 0.01f, 0.02f };

//�J�����̂��.
const float fZOOM = D3DX_PI / 4.0f;

//�`����E����.
const float fRENDER_LIMIT = 150.0f;


//���S�V�[������.
const int iDEAD_TIME = 90;


//�Ó]���x.
const float fBLACK_SPD_SLOW = 0.0125f;
const float fBLACK_SPD_FAST = 0.05f;




const int iPAT_SMOK_MAX = 500;


//----- �z�u�p -----//
const float fSTAGE_WIDHT = 10.0f;
const float fWALL_HIT_RANGE = fSTAGE_WIDHT / 2.0f - 0.75f;
//�������S�������鍂��.
const float fDROP_DOWN_Y = -6.0f;

//��O���E.
const float fPLAYER_BACK_LIMIT = 4.0f;
//�J��������O�ɂ��Ȃ�Z���W.
const float fCAMERA_NOT_BACK = 12.0f;

//�J�����̏�������.
const D3DXVECTOR3 vCAMERA_INIT_OFFSET = { 0.0f, 4.9f, -7.0f };
//�J�����̎��_�̈ʒu.
const float fLOOK_OFFSET_Z = 5.0f;
const float fLOOK_OFFSET_Y = 3.0625f;//.
//----- �z�u�p�I��� -----//

//----- �����蔻��̔��f���� -----//
const float fONE_BROCK_HIT_AREA = 1.0f;//���⏰�A��.3.0f.
const float fGOAL_TREASURE_HIT_AREA = 32.0f;//�S�[���̔��̉�����.


//�X�e�[�W�쐬�p�萔.

const float WALL_SPACE			= 0.8f;	//�ǂƂ̌��E����.

const int	STAGEPATARUNSETMAX	= 12;

const float PENDPOSY			= 12.0f;//Pendulum��_�̍���.

const int	COVEREREA			= 12;	//���Ƃ����̊W.
const int	ENEMYEREA			= 13;	//�G�̍s���͈�.
const int	ENEMYEREACENTER		= 6;	//�G��Csv�̐ݒu�ꏊ.
const int	CILMOVEEREA			= 15;	//�ۏ��̈ړ��͈�.
const int	CILMOVEEREACENTER	= 4;	//�ۏ���Csv�̐ݒu�ꏊ.

//�X�e�[�W�쐬�p�萔�I��.

//��}�X�̑傫��.
const float fONE_BLOCK_SIZE = 1.0f;


//----- �G���f�B���O -----//.
const int iENDING_STAGE_MAX = 256;
const D3DXVECTOR3 vENDING_INIT_STAGE_POS = { 0.0f, 0.0f, 0.0f };
const D3DXVECTOR3 vENDING_INIT_CEILING_POS = { 0.0f, 7.0f, 0.0f };
//�G���f�B���O�̃X�N���[������.
const float fEND_SCROL_SPD = 0.125f;
//�X�N���[�����E.
const float fEND_SCROL_LIMIT = 128.0f;

//�G���f�B���O->�^�C�g��.
const D3DXVECTOR3 vTITLE_INIT_STAGE_POS = { 0.0f, 0.0f, 2.0f };
const D3DXVECTOR3 vTITLE_INIT_CEILING_POS = { 0.0f, 7.0f, 2.0f };


#ifdef Inoue
int		g_iPngNum;
vector<string> g_vsFilePath;	//������D&D�����t�@�C��������.
bool	g_bFileActive = false;	//�t�@�C������ꂽ���ǂ���.

bool	g_bStageRead;

int		g_ControlNum = 0;

#endif//Inoue.
//============================================================
//�G�t�F�N�g.
//�G�̂���G�t�F�N�g�̐�.
const char cEFF_KICK_HIT_MAX = 2;

//�傫��.
const float fEFF_SCALE = 0.25f;
const D3DXVECTOR3 vEFF_KICK_HIT_SCALE = { fEFF_SCALE, fEFF_SCALE, fEFF_SCALE };
const D3DXVECTOR3 vEFF_SLASH_HIT_SCALE = { fEFF_SCALE, fEFF_SCALE, fEFF_SCALE };

//�����グ��.
const float fEFF_UP_OFFSET = 1.0f;



//============================================================




//============================================================
//	Ҳ݊֐�.
//============================================================
INT WINAPI WinMain(
	HINSTANCE hInstance,		//�ݽ�ݔԍ�(����޳�̔ԍ�).
	HINSTANCE hPrevInstance,
	PSTR lpCmdLine,
	INT nCmdShow )
{
	g_pClsMain = new clsMain;	//������&�׽�̐錾.

	//�׽�����݂��Ă��邩����.
	if( g_pClsMain != nullptr ){
		//����޳�쐬����.
		if( SUCCEEDED(
			g_pClsMain->InitWindow(
				hInstance,
				0, 0,
				WND_W, WND_H,
				WND_TITLE ) ) )
		{
			//Dx11�p�̏�����
			if( SUCCEEDED( g_pClsMain->InitD3D() ) ){
				//ү����ٰ��.
				g_pClsMain->Loop();
			}
		}
		//�I��.
		g_pClsMain->DestroyD3D();//Direct3D�̉��.

		delete g_pClsMain;		//�׽�̔j��.
	}

	return 0;
}


//============================================================
//	����޳��ۼ��ެ.
//============================================================
LRESULT CALLBACK WndProc(
	HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam )
{
	//��ۼ��ެ.
	return g_pClsMain->MsgProc( hWnd, uMsg, wParam, lParam );
}


//============================================================
//	Ҳݸ׽.
//============================================================

//============================================================
//	�ݽ�׸�.
//============================================================
clsMain::clsMain()
{
	ZeroMemory( this, sizeof( clsMain ) );

	m_hWnd = nullptr;

	m_pDevice		= nullptr;	//���޲���޼ު��.
	m_pDeviceContext= nullptr;	//���޲���÷��.
	m_pSwapChain	= nullptr;	//�ܯ������.

	m_pBackBuffer_TexRTV	= nullptr;//���ް���ޯ��ޭ�.
	m_pBackBuffer_DSTex		= nullptr;//�ޯ��ޯ̧.
	m_pBackBuffer_DSTexDSV	= nullptr;//���߽��ݼ��ޭ�.


	//ײĕ���.
	m_vLight = vLIGHT_DIR;

	//�X�e�[�W�Ǎ��S����.
	g_bStageRead = false;
	m_fAlphaPoint = 1.0f;
}

//============================================================
//	�޽�׸�.
//============================================================
clsMain::~clsMain()
{

}

//============================================================
//����޳�������֐�.
//============================================================
HRESULT clsMain::InitWindow(
	HINSTANCE hInstance,	//�ݽ�ݽ.
	INT x, INT y,			//����޳��x,y���W.
	INT width, INT height,	//����޳�̕�,����.
	LPSTR WindowName )		//����޳��.
{
	//����޳�̒�`.
	WNDCLASSEX wc;
	ZeroMemory( &wc, sizeof( wc ) );//������.

	wc.cbSize			= sizeof( wc );
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= WndProc;
	wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon( NULL, IDI_APPLICATION );
	wc.hCursor			= LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground	= (HBRUSH)GetStockObject( LTGRAY_BRUSH );
	wc.lpszClassName	= APR_NAME;
	wc.hIconSm			= LoadIcon( NULL, IDI_APPLICATION );

	//����޳�׽��Windows�ɓo�^.
	if( !RegisterClassEx( &wc ) ){
		MessageBox( NULL, "�E�B���h�E�N���X�m�o�^�Ƀ~�X", "clsMainInitWindow", MB_OK );
		return E_FAIL;
	}

	//����޳�̍쐬.
	m_hWnd = CreateWindow(
		APR_NAME,			//���ؖ�.
		WindowName,			//����޳����.
		WS_OVERLAPPEDWINDOW,//����޳���.
		0, 0,				//�\�����W.
		width, height,		//����޳�̕�,����.
		NULL,				//�e����޳�����.
		NULL,				//�ƭ��ݒ�.
		hInstance,			//�ݽ�ݽ�ԍ�.
		NULL );				//����޳�쐬���ɔ����������Ăɓn���ް�.

	if( !m_hWnd ){
		MessageBox( NULL, "����޳�쐬�Ƀ~�X", "clsMain::InitWindow", MB_OK );
		return E_FAIL;
	}
#ifdef Inoue
#ifdef _DEBUG
	DragAcceptFiles(
		m_hWnd,    // �o�^����E�B���h�E
		true // �A�N�Z�v�g�I�v�V����
	   );
#endif	//#ifdef _DEBUG
#endif//#ifdef Inoue

	//����޳�̕\��.
	ShowWindow( m_hWnd, SW_SHOW );
	UpdateWindow( m_hWnd );

	//�}�E�X�J�[�\���̔�\��.
#ifndef _DEBUG
	ShowCursor(false);
#endif//#ifndef _DEBUG

	return S_OK;
}

//============================================================
//	����޳�֐�(ү���ޖ��̏���).
//============================================================
LRESULT clsMain::MsgProc(
	HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam )
{
    HDROP hDrop;
    UINT uFileNo;
	switch( uMsg )
	{
	case WM_DESTROY:	//����޳�j����.
		//���ع���݂̏I����Windows�ɒʒm����.
		PostQuitMessage( 0 );
		break;
	case WM_DROPFILES:
		g_bFileActive = true;
		hDrop = (HDROP)wParam;
		uFileNo = DragQueryFile( (HDROP)wParam, 0xFFFFFFFF, NULL, 0 );
		char Path[MAX_PATH];
		for (int i = 0; i < (int)uFileNo; i++){
			DragQueryFile( hDrop, i, Path, sizeof( Path ) );
			g_vsFilePath.push_back(Path);
		}
		DragFinish( hDrop );
		break;
	case WM_KEYDOWN:	//���ް�ނ������ꂽ�Ƃ�.
		//���ʂ̏���.
		switch( (char)wParam )
		{
		case VK_ESCAPE:	//ESC��.
			if( MessageBox( NULL,
				"�ްт��I�����܂���?", "Message",
				MB_YESNO ) == IDYES )
			{
				//����޳��j������.
				DestroyWindow( hWnd );
			}
			break;
		}
		break;
	}

	//Ҳ݂ɕԂ����.
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}


//============================================================
//	ү����ٰ�߂Ʊ��ع���ݏ����̓����.
//============================================================
void clsMain::Loop()
{
	//BGM�쐬.
	CreateSound();
	//�N�����Đ�.
	m_pBgm[enBGM_START_UP]->Play();

	m_pXInput = new clsXInput;

	//�����蔻��.
	m_pCollision = new clsCollision;
	m_pCollision->CreateSe( m_hWnd );


#ifdef START_LOADING_DISPLAY
	//���b�V����X�v���C�g�Ȃǂ̓Ǎ�.
	NowLoading();
#else
	//ү���ǂݍ��݊֐����܂Ƃ߂�����.
	ReadMesh();
	//���C���V�[��������(���u��).
	InitMain( true );
#endif//#ifndef START_LOADING_DISPLAY


	//----------------------------------------------------------
	//	�ڰ�ڰ�.
	//----------------------------------------------------------
	float fRate		= 0.0f;	//ڰ�.
	float fFPS		= 60.0f;//FPS�l.
	DWORD sync_old	= timeGetTime();	//�ߋ�����.
	DWORD sync_now;
	//���ԏ����ׁ̈A�ŏ��P�ʂ�1�ؕb�ɕύX.
	timeBeginPeriod( 1 );


	//ү����ٰ��.
	MSG msg = { 0 };
	ZeroMemory( &msg, sizeof( msg ) );

	while( msg.message != WM_QUIT )
	{
		Sleep( 1 );
		sync_now = timeGetTime();	//���ݎ��Ԃ��擾.

		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ){
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		fRate = 1000.0f / fFPS;	//���z���Ԃ��Z�o.

		if( sync_now - sync_old >= fRate ){
			sync_old = sync_now;	//���ݎ��Ԃɒu������.

			//���ع���ݏ����͂���������.
			AppMain();
		}
	}
	//���ع���݂̏I��.
	timeEndPeriod( 1 );	//����.
}

//============================================================
//	���ع����Ҳݏ���.
//============================================================
void clsMain::AppMain()
{
	//���۰ד��͏��X�V.
	m_pXInput->UpdateStatus();

#ifdef Inoue
	if (g_bFileActive)
	{
		for (size_t i = 0; i < g_vsFilePath.size(); i++)
		{
			m_pTestData->Init((char*)g_vsFilePath[i].c_str());
			m_pTestData->Read();
			if (m_pTestData->GetExtension() == x)
			{
				m_pResource->ReleaseStaticModel(m_pResource->enST_MODEL_TEST);
				m_pResource->CreateStaticModel((LPSTR)m_pTestData->GetFilePath().c_str(),
					m_pResource->enST_MODEL_TEST);
			}
			else if (m_pTestData->GetExtension() == png)
			{
				m_vsmpSpriteTest.push_back(make_unique<clsSprite2D>());
				m_vsmpSpriteTest[g_iPngNum]->Create(m_pDevice, m_pDeviceContext, (LPSTR)m_pTestData->GetFilePath().c_str());
				m_vsmpSpriteTest[g_iPngNum]->SetPos(WND_W / 2 - m_vsmpSpriteTest[g_iPngNum]->GetSs().Disp.w / 2, WND_H / 2 - m_vsmpSpriteTest[g_iPngNum]->GetSs().Disp.h / 2);
				g_iPngNum++;
			}
		}
		g_vsFilePath.clear();
	}
	g_bFileActive = false;


	switch( m_enScene )
	{
		case enSCENE_TITLE:
			SceneTitle();
			m_smpUiManagar->SceneTitle();
			GETKEY_DOWN( 'O' )
			{
				m_smpUiManagar->BlackStart( 0.01f );
				InitMain( true );
			}
			break;
		case enSCENE_MAIN:
			SceneMain();
			m_smpUiManagar->SceneMain();
			GETKEY_DOWN( 'O' )
			{
				m_smpUiManagar->BlackStart( 0.01f );
				m_enScene = enSCENE_OVER;
			}
			break;
		case enSCENE_OVER:
			SceneOver();
			m_smpUiManagar->SceneOver();
			GETKEY_DOWN( 'O' )
			{
				m_smpUiManagar->BlackStart( 0.01f );
				m_enScene = enSCENE_RESULT;
			}
			break;
		case enSCENE_RESULT:
			SceneResult();
			m_smpUiManagar->SceneResult();
			GETKEY_DOWN( 'O' )
			{
				m_smpUiManagar->BlackStart( 0.01f );
				m_enScene = enSCENE_ENDROLL;
			}
			break;
		case enSCENE_ENDROLL:
			SceneEnding();
			m_smpUiManagar->SceneEnding();
			GETKEY_DOWN( 'O' )
			{
				m_smpUiManagar->BlackStart( 0.01f );
				m_enScene = enSCENE_TITLE;
			}
			break;
	}

#endif//Inoue.

	if (GetAsyncKeyState('I') & 0x0001){
		m_fAlphaPoint = 1.0f;
		for (size_t i = 0; i < m_vsmpSpriteTest.size(); i++)
		{
			if (m_vsmpSpriteTest[i])
			{
				m_vsmpSpriteTest[i].release();
				m_vsmpSpriteTest[i] = NULL;
			}
		}
		m_vsmpSpriteTest.clear();
		m_SpriteControlNum = 0;
		g_iPngNum = 0;
		InitMain(true);
	}

	GETKEY_DOWN('M'){
		if (ControlMode < 1 && 0 < m_vsmpSpriteTest.size()){
			ControlMode++;
		}
		else{
			ControlMode = 0;
		}
	}

	static char blkZYFlg = 0;
	switch ( ControlMode )
	{
	case 0:
#if _DEBUG
		//��K�ʒu�̈ړ�.
		GETKEY_STAY( 'A' ) 	m_ppBlkAry[0]->AddPositionX( -0.1f );
		GETKEY_STAY( 'D' )	m_ppBlkAry[0]->AddPositionX(  0.1f );
		GETKEY_STAY( 'W' )	m_ppBlkAry[0]->AddPositionY(  0.1f );
		GETKEY_STAY( 'S' )	m_ppBlkAry[0]->AddPositionY( -0.1f );
		GETKEY_STAY( 'E' )	m_ppBlkAry[0]->AddPositionZ(  0.1f );
		GETKEY_STAY( 'Q' )	m_ppBlkAry[0]->AddPositionZ( -0.1f );
#endif //#if _DEBUG

		GETKEY_DOWN( 'B' ){
			blkZYFlg ++;
			if( blkZYFlg >= 3 )	blkZYFlg = 0;
		}
		break;
	case 1:
		//�X�v���C�g�ړ��A�g�k.
		if (!m_vsmpSpriteTest.empty())
		{
			GETKEY_STAY('A'){ m_vsmpSpriteTest[m_SpriteControlNum]->AddPosX(-5.0f); }
			GETKEY_STAY('D'){ m_vsmpSpriteTest[m_SpriteControlNum]->AddPosX(5.0f);	}
			GETKEY_STAY('W'){ m_vsmpSpriteTest[m_SpriteControlNum]->AddPosY(-5.0f); }
			GETKEY_STAY('S'){ m_vsmpSpriteTest[m_SpriteControlNum]->AddPosY(5.0f);	}
			GETKEY_STAY('Q'){
				m_fAlphaPoint-=0.01f;
				m_vsmpSpriteTest[m_SpriteControlNum]->MulDisp(m_fAlphaPoint);
			}
			GETKEY_STAY('E'){
				m_fAlphaPoint+=0.01f;
				m_vsmpSpriteTest[m_SpriteControlNum]->MulDisp(m_fAlphaPoint);
			}
			GETKEY_DOWN('N'){
				if (m_SpriteControlNum < m_vsmpSpriteTest.size() - 1){
					m_SpriteControlNum++;
				}
				else{
					m_SpriteControlNum = 0;
				}
			}
			GETKEY_DOWN('B'){
				if (m_SpriteControlNum > 0){
					m_SpriteControlNum--;
				}
				else{
					m_SpriteControlNum = m_vsmpSpriteTest.size() - 1;
				}
			}
		}
		break;
	case 2:
		//���C�g�̕����̑���.
		GETKEY_STAY( 'A' ) 	m_vLight.x += 0.01f;
		GETKEY_STAY( 'D' )	m_vLight.x -= 0.01f;
		GETKEY_STAY( 'W' )	m_vLight.y += 0.01f;
		GETKEY_STAY( 'S' )	m_vLight.y -= 0.01f;
		GETKEY_STAY( 'E' )	m_vLight.z += 0.01f;
		GETKEY_STAY( 'Q' )	m_vLight.z -= 0.01f;
		GETKEY_STAY( 'I' )	m_vLight = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );

	break;
	default:
		break;
	}

#if _DEBUG
	for( char blk_no=0; blk_no<m_iBlkAryMax; blk_no++ ){
		m_ppBlkAry[blk_no]->SetPosition( m_ppBlkAry[0]->GetPosition() );
		if( blkZYFlg == 0 ){
			m_ppBlkAry[blk_no]->AddPositionZ( (float)blk_no );
		}
		else if( blkZYFlg == 1 ){
			m_ppBlkAry[blk_no]->AddPositionY( (float)blk_no );
		}
		else{
			m_ppBlkAry[blk_no]->AddPositionX( (float)blk_no );
		}

		//�M�U�M�U.
		if( blkZYFlg <= 1 ){
			if( blk_no % 2 != 0 ){
				m_ppBlkAry[blk_no]->AddPositionX( 1.0f );
			}
		}
		else if( blkZYFlg == 2 ){
			if( blk_no % 2 != 0 ){
				m_ppBlkAry[blk_no]->AddPositionY( 1.0f );
			}
		}
	}
#endif //#if _DEBUG


	GETKEY_DOWN( VK_F1 ){
		m_smpStageDataExcel->Open( m_hWnd );
	}
	GETKEY_DOWN( VK_F2 ) {
		m_smpStageDataReadMe->Open( m_hWnd );
	}


	GETKEY_DOWN( 'P' ){
		StageModelSet();
		InitMain( true );
	}


	//�����ݸ�.
	Render();
}

//============================================================
//	�`��(�����ݸ�).
//	���(���)����ʂ������ݸ�(�`��).
//	(��DX9MESH����Main����2���݂���̂Œ���).
//============================================================
void clsMain::Render()
{
	//��ʂ̸ر.
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };//�ر�F(RGBA��)(0.0f~1.0f).
	//�װ�ޯ��ޯ̧.
	m_pDeviceContext->ClearRenderTargetView(
		m_pBackBuffer_TexRTV, ClearColor );
	//���߽��ݼ��ޭ��ޯ��ޯ̧.
	m_pDeviceContext->ClearDepthStencilView(
		m_pBackBuffer_DSTexDSV,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f, 0 );

	//��׊֐�.
	Camera();
	//��ۼު���݊֐�.
	Proj();


	switch( m_enScene )
	{
	case enSCENE_TITLE:
		RenderTitle();
		SetDepth( false );	//Zý�:OFF.
		m_smpUiManagar->RenderTitle();
		SetDepth( true );	//Zý�:ON.
		break;
	case enSCENE_MAIN:
		RenderMain();
		SetDepth( false );	//Zý�:OFF.
		m_smpUiManagar->RenderMain();
		SetDepth( true );	//Zý�:ON.
		break;
	case enSCENE_OVER:
		RenderOver();
		SetDepth( false );	//Zý�:OFF.
		m_smpUiManagar->RenderOver();
		SetDepth( true );	//Zý�:ON.
		break;
	case enSCENE_RESULT:
		RenderResult();
		SetDepth( false );	//Zý�:OFF.
		m_smpUiManagar->RenderResult();
		SetDepth( true );	//Zý�:ON.
		break;
	case enSCENE_ENDROLL:
		RenderEnding();
		SetDepth( false );	//Zý�:OFF.
		m_smpUiManagar->RenderEnding();
		SetDepth( true );	//Zý�:ON.
		break;
	}




#if _DEBUG
	//���ޯ��÷��.
	RenderDebugText();
#endif//#if _DEBUG

	for (char i = 0; i < m_vsmpSpriteTest.size(); i++){
		m_vsmpSpriteTest[i]->Render();
	}
	//�����ݸނ��ꂽ�Ұ�ނ�\��.
	m_pSwapChain->Present( 0, 0 );
}


//============================================================
//	DirectX������.
//============================================================
HRESULT clsMain::InitD3D()
{
	//---------------------------------------------------
	//	���޲��ƽܯ�����݊֌W.
	//---------------------------------------------------

	//�ܯ�����ݍ\����.
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof( sd ) );
	sd.BufferCount		= 1;		//�ޯ��ޯ̧�̐�.
	sd.BufferDesc.Width	= WND_W;
	sd.BufferDesc.Height= WND_H;
	sd.BufferDesc.Format= DXGI_FORMAT_R8G8B8A8_UNORM;
									//̫�ϯ�(32�ޯĶװ).
	sd.BufferDesc.RefreshRate.Numerator = 60;
									//��گ��ڰ�(����) ��FPS:60.
	sd.BufferDesc.RefreshRate.Denominator = 1;
									//��گ��ڰ�(���q).
	sd.BufferUsage		= DXGI_USAGE_RENDER_TARGET_OUTPUT;
									//�g����(�\����).
	sd.OutputWindow		= m_hWnd;	//����޳�����.
	sd.SampleDesc.Count	= 1;		//�������ق̐�.
	sd.SampleDesc.Quality=0;		//�������ق̸��è.
	sd.Windowed			= TRUE;		//����޳Ӱ��(�ٽ�����FALSE).


	//�쐬�����݂�@�\���ق̗D����w��.
	//	(GPU����߰Ă���@�\��Ă̒�`).
	//	D3D_FEATURE_LEVEL�񋓑̂̔z��.
	//	D3D_FEATURE_LEVEL_10_1:Direct3D 10.1��GPU����.
	D3D_FEATURE_LEVEL	pFeatureLevels	= D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL*	pFeatureLevel	= nullptr;	//�z��̗v�f��.


	//���޲��ƽܯ�����݂̍쐬.
	//	ʰ�޳��(GPU)���޲��ō쐬.
	if( FAILED(
		D3D11CreateDeviceAndSwapChain(
			NULL,					//���޵�������ւ��߲��.
			D3D_DRIVER_TYPE_HARDWARE,//�쐬�������޲��̎��.
			NULL,					//��ĳ��׽�ײ�ް����������DLL�������.
			0,						//�L���ɂ��������ڲ԰.
			&pFeatureLevels,		//�쐬�����݂�@�\���ق̏������w�肷��z��.
			1,						//���̗v�f��.
			D3D11_SDK_VERSION,		//SDK���ް�ޮ�.
			&sd,					//�ܯ�����݂̏��������Ұ����߲��.
			&m_pSwapChain,			//(out)�����ݸނɎg�p���ꂽ�ܯ������.
			&m_pDevice,				//(out)�쐬���ꂽ���޲�.
			pFeatureLevel,			//�@�\���ق̔z��ɂ���ŏ��̗v�f��\���߲��.
			&m_pDeviceContext ) ) )	//(out)���޲���÷��.
	{
		//WARP���޲��̍쐬.
		// D3D_FEATURE_LEVEL_9_1 �` D3D_FEATURE_LEVEL_10_1.
		if( FAILED(
			D3D11CreateDeviceAndSwapChain(
				NULL, D3D_DRIVER_TYPE_WARP,
				NULL, 0, &pFeatureLevels, 1,
				D3D11_SDK_VERSION, &sd,
				&m_pSwapChain, &m_pDevice,
				pFeatureLevel, &m_pDeviceContext ) ) )
		{
			//�̧�ݽ���޲��̍쐬.
			//	DirectX SDK���ݽİق���Ă��Ȃ��Ǝg���Ȃ�.
			if( FAILED(
				D3D11CreateDeviceAndSwapChain(
					NULL, D3D_DRIVER_TYPE_REFERENCE,
					NULL, 0, &pFeatureLevels, 1,
					D3D11_SDK_VERSION, &sd,
					&m_pSwapChain, &m_pDevice,
					pFeatureLevel, &m_pDeviceContext ) ) )
			{
				MessageBox( NULL, "���޲��ƽܯ�����݂̍쐬�Ƀ~�X", "error(main.cpp)", MB_OK );
				return E_FAIL;
			}
		}
	}


	//�e��ø�����ƁA����ɕt�т���e���ޭ�(���)���쐬.

	//---------------------------------------------------
	//	�ޯ��ޯ̧����:�װ�ޯ̧�ݒ�.
	//---------------------------------------------------

	//�ޯ��ޯ̧ø�������擾(���ɂ���̂ō쐬�͂Ȃ�).
	ID3D11Texture2D *pBackBuffer_Tex;
	m_pSwapChain->GetBuffer(
		0,
		__uuidof(ID3D11Texture2D),	//__uuidof:���Ɋ֘A�t����GUID���擾.
									//		   Texture2D�̗B��̕��Ƃ��Ĉ���.
		(LPVOID*)&pBackBuffer_Tex );//(out)�ޯ��ޯ̧ø���.

	//����ø�����ɑ΂����ް���ޯ��ޭ�(RTV)���쐬.
	m_pDevice->CreateRenderTargetView(
		pBackBuffer_Tex,
		NULL,
		&m_pBackBuffer_TexRTV );//(out)RTV.
	//�ޯ��ޯ̧ø���������.
	SAFE_RELEASE( pBackBuffer_Tex );//ϸۓ��ɾк�݂�����̂ł���Ȃ��������ڂ̓���ł��Ă���.

	//---------------------------------------------------
	//	�ޯ��ޯ̧����:���߽(�[�x)��ݼي֌W.
	//---------------------------------------------------

	//���߽(�[��or�[�x)��ݼ��ޭ��p��ø�������쐬.
	D3D11_TEXTURE2D_DESC descDepth;

	descDepth.Width				= WND_W;					//��.
	descDepth.Height			= WND_H;					//����.
	descDepth.MipLevels			= 1;						//Я��ϯ������:1.
	descDepth.ArraySize			= 1;						//�z��:1.
	descDepth.Format			= DXGI_FORMAT_D32_FLOAT;	//32�ޯ�̫�ϯ�.
	descDepth.SampleDesc.Count	= 1;						//�������ق̐�.
	descDepth.SampleDesc.Quality= 0;						//�������ق̸��è.
	descDepth.Usage				= D3D11_USAGE_DEFAULT;		//�g�p���@:��̫��.
	descDepth.BindFlags			= D3D11_BIND_DEPTH_STENCIL;	//�[�x(��ݼقƂ��Ďg�p).
	descDepth.CPUAccessFlags	= 0;						//CPU���籸�����Ȃ�.
	descDepth.MiscFlags			= 0;						//���̑��ݒ�Ȃ�.

	m_pDevice->CreateTexture2D(
		&descDepth,
		NULL,
		&m_pBackBuffer_DSTex );//(out)���߽��ݼٗpø���.

	//����ø����ɑ΂����߽��ݼ��ޭ�(DSV)���쐬.
	m_pDevice->CreateDepthStencilView(
		m_pBackBuffer_DSTex,
		NULL,
		&m_pBackBuffer_DSTexDSV );//(out)DSV.

	//���ް���ޯ��ޭ������߽��ݼ��ޭ����߲��ײ݂ɾ��.
	m_pDeviceContext->OMSetRenderTargets(
		1,
		&m_pBackBuffer_TexRTV,
		m_pBackBuffer_DSTexDSV );


	//�[�xý�(Zý�)��L���ɂ���.
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory( &depthStencilDesc,
		sizeof( D3D11_DEPTH_STENCIL_DESC ) );
	depthStencilDesc.DepthEnable = true;

	if( SUCCEEDED( m_pDevice->CreateDepthStencilState(
		&depthStencilDesc, &m_pDepthStencilState ) ) )
	{
		m_pDeviceContext->OMSetDepthStencilState(
			m_pDepthStencilState, 1 );
	}

	//�ޭ��߰Ă̐ݒ�.
	D3D11_VIEWPORT vp;
	vp.Width	= WND_W;//��.
	vp.Height	= WND_H;//����.
	vp.MinDepth	= 0.0f;	//�ŏ��[�x(��O).
	vp.MaxDepth	= 1.0f;	//�ő�[�x(��).
	vp.TopLeftX	= 0.0f;	//����ʒux.
	vp.TopLeftY	= 0.0f;	//����ʒuy.
	m_pDeviceContext->RSSetViewports( 1, &vp );

	//Sp2D�p.
	SetViewPort10( &vp );

	//׽�ײ��(�ʂ̓h��Ԃ���)�ݒ�.
	D3D11_RASTERIZER_DESC rdc;
	ZeroMemory(&rdc, sizeof( rdc ) );
	rdc.FillMode = D3D11_FILL_SOLID;	//�h��Ԃ�(�د��).
	rdc.CullMode = D3D11_CULL_NONE;
					//D3D11_CULL_NONE :��ݸނ�؂�(���w�ʂ�`�悷��).
					//D3D11_CULL_BACK :�w�ʂ�`�悵�Ȃ�.
					//D3D11_CULL_FRONT:���ʂ�`�悵�Ȃ�.
	rdc.FrontCounterClockwise	= FALSE;
								//�|���S���̕\�������肷���׸�.
								//TRUE :�����Ȃ�O����,�E���Ȃ������.
								//FALSE:���̋t�ɂȂ�.
	rdc.DepthClipEnable	= FALSE;	//�����ɂ��Ă̸د��ݸޗL��.

	ID3D11RasterizerState* pIr	= nullptr;
	m_pDevice->CreateRasterizerState( &rdc, &pIr );
	m_pDeviceContext->RSSetState( pIr );
	SAFE_RELEASE( pIr );

	return S_OK;
}

//============================================================
//	Direct3D�I������.
//============================================================
void clsMain::DestroyD3D()
{
#if _DEBUG
	//�f�o�b�O�e�L�X�g.
	if( m_pText != nullptr ){
		delete m_pText;
		m_pText = nullptr;
	}

	if( m_pRayH != nullptr ){
		delete m_pRayH;
		m_pRayH = nullptr;
	}
	if( m_pRayFB != nullptr ){
		delete m_pRayFB;
		m_pRayFB = nullptr;
	}
	if( m_pRayV != nullptr ){
		delete m_pRayV;
		m_pRayV = nullptr;
	}
	if( m_pParticle != nullptr ){
		delete m_pParticle;
		m_pParticle = nullptr;
	}

	//��K�̍폜.
	if( m_ppBlkAry != nullptr ){
		for( int i=0; i<m_iBlkAryMax; i++ ){
			//�����ް��̊֘A�t��.
			m_ppBlkAry[i]->DetatchModel();
			//�j��.
			delete m_ppBlkAry[i];
			m_ppBlkAry[i] = nullptr;
		}
		//�߲���z��j��.
		delete[] m_ppBlkAry;
		m_ppBlkAry = nullptr;
	}
	//�ő吔������.
	m_iBlkAryMax = 0;


#endif //#if _DEBUG

#ifdef Inoue
	//�X�e�[�W(��)�̍폜.
	if(!m_vsmpWall.empty()){
		for( int i=0; i<m_vsmpWall.size(); i++ ){
			//�����ް��̊֘A�t��.
			m_vsmpWall[i]->DetatchModel();
			//�j��.
			m_vsmpWall[i].reset();
		}
		//vector�̔j��.
		m_vsmpWall.clear();
		m_vsmpWall.shrink_to_fit();
	}
	//�X�e�[�W(��)�̍폜.
	if(!m_vsmpFloor.empty()){
		for( int i=0; i<m_vsmpFloor.size(); i++ ){
			//�����ް��̊֘A�t��.
			m_vsmpFloor[i]->DetatchModel();
			//�j��.
			m_vsmpFloor[i].reset();
		}
		//vector�̔j��.
		m_vsmpFloor.clear();
		m_vsmpFloor.shrink_to_fit();
	}

	//�X�e�[�W(��������)�̍폜.
	if(!m_vsmpStepCil.empty()){
		for( int i=0; i<m_vsmpStepCil.size(); i++ ){
			//�����ް��̊֘A�t��.
			m_vsmpStepCil[i]->DetatchModel();
			//�j��.
			m_vsmpStepCil[i].reset();
		}
		//vector�̔j��.
		m_vsmpStepCil.clear();
		m_vsmpStepCil.shrink_to_fit();
	}

	//�X�e�[�W(��������)�̍폜.
	if(!m_vsmpStepCil.empty()){
		for( int i=0; i<m_vsmpStepCil.size(); i++ ){
			//�����ް��̊֘A�t��.
			m_vsmpStepBox[i]->DetatchModel();
			//�j��.
			m_vsmpStepBox[i].reset();
		}
		//vector�̔j��.
		m_vsmpStepCil.clear();
		m_vsmpStepCil.shrink_to_fit();
	}

	//�X�e�[�W(�G)�̍폜.
	if(!m_vsmpEnemyMgr.empty()){
		for( int i=0; i<m_vsmpEnemyMgr.size(); i++ ){
			//�����ް��̊֘A�t��.
			m_vsmpEnemyMgr[i]->DetatchModel();
			//�j��.
			m_vsmpEnemyMgr[i].reset();
		}
		//vector�̔j��.
		m_vsmpEnemyMgr.clear();
		m_vsmpEnemyMgr.shrink_to_fit();
	}

	//�X�e�[�W(�y���f������)�̍폜.
	if(!m_vsmpPend.empty()){
		for( int i=0; i<m_vsmpPend.size(); i++ ){
			//�����ް��̊֘A�t��.
			m_vsmpPend[i]->DetatchModel();
			//�j��.
			m_vsmpPend[i].reset();
		}
		//vector�̔j��.
		m_vsmpPend.clear();
		m_vsmpPend.shrink_to_fit();
	}
	//�X�e�[�W(����)�̍폜.
	if(!m_vsmpSpiaFloorMgr.empty()){
	for( int i=0; i<m_vsmpSpiaFloorMgr.size(); i++ ){
			//�����ް��̊֘A�t��.
			m_vsmpSpiaFloorMgr[i]->DetatchModel();
			//�j��.
			m_vsmpSpiaFloorMgr[i].reset();
		}
		//vector�̔j��.
		m_vsmpSpiaFloorMgr.clear();
		m_vsmpSpiaFloorMgr.shrink_to_fit();
	}

	//�X�e�[�W(����)�̍폜.
	if(!m_vsmpSpiaWallMgr.empty()){
		for( int i=0; i<m_vsmpSpiaWallMgr.size(); i++ ){
			//�����ް��̊֘A�t��.
			m_vsmpSpiaWallMgr[i]->DetatchModel();
			//�j��.
			m_vsmpSpiaWallMgr[i].reset();
		}
		//vector�̔j��.
		m_vsmpSpiaWallMgr.clear();
		m_vsmpSpiaWallMgr.shrink_to_fit();
	}
	//�X�e�[�W(���Ƃ����̊W)�̍폜.
	if(m_vsmpCoverMgr.empty()){
		for( int i=0; i<m_vsmpCoverMgr.size(); i++ ){
			//�����ް��̊֘A�t��.
			m_vsmpCoverMgr[i]->DetatchModel();
			//�j��.
			m_vsmpCoverMgr[i].reset();
		}
		//vector�̔j��.
		m_vsmpCoverMgr.clear();
		m_vsmpCoverMgr.shrink_to_fit();
	}

	//�X�v���C�g�N���X���.
	if(!m_vsmpSpriteTest.empty()){
		for (size_t i = 0; i < m_vsmpSpriteTest.size(); i++)
		{
			m_vsmpSpriteTest[i].reset();
		}
		m_vsmpSpriteTest.clear();
		m_vsmpSpriteTest.shrink_to_fit();
	}

	//̧�ٓǍ��׽���.
	if( m_smpStageData != NULL ){
		m_smpStageData.reset();
		m_smpStageData = NULL;
	}

	//Excel.
	if( m_smpStageDataExcel != NULL ){
		m_smpStageDataExcel.reset();
		m_smpStageDataExcel = NULL;
	}

	//UiManager.
	if( m_smpUiManagar != NULL ){
		m_smpUiManagar.reset();
		m_smpUiManagar = NULL;
	}
#endif //ifdef Inoue.

#ifdef Tahara

	if( m_pEndEnemy != nullptr ){
		delete m_pEndEnemy;
		m_pEndEnemy = nullptr;
	}

	if( m_pCheck != nullptr ){
		delete m_pCheck;
		m_pCheck = nullptr;
	}

	//ARBIA.
	if( m_pPlayer != nullptr ){
		m_pPlayer->DetatchModel();
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}


	////Effekseer�̔j��.
	//clsEffects::GetInstance()->Destroy();
	m_pEffect = nullptr;



	//�����蔻��.
	if( m_pCollision != nullptr ){
		delete m_pCollision;
		m_pCollision = nullptr;
	}

	//���۰ד���.
	if( m_pXInput != nullptr ){
		m_pXInput->EndProc();
		XInputEnable( false );
		delete m_pXInput;
		m_pXInput = nullptr;
	}

	//SE�����.
	if( m_pSe != nullptr ){
		for( int i=0; i<enSe_MAX; i++ ){
			m_pSe[i]->Stop();
			m_pSe[i]->Close();
			delete m_pSe[i];
			m_pSe[i] = nullptr;
		}
	}

	//BGM�����.
	if( m_pBgm != nullptr ){
		for( int i=0; i<enBGM_MAX; i++){
			m_pBgm[i]->Stop();
			m_pBgm[i]->Close();
			delete m_pBgm[i];
			m_pBgm[i] = nullptr;
		}
	}
#endif //#ifdef Tahara

	SAFE_RELEASE( m_pBackBuffer_DSTexDSV );
	SAFE_RELEASE( m_pBackBuffer_DSTex );
	SAFE_RELEASE( m_pBackBuffer_TexRTV );
	SAFE_RELEASE( m_pSwapChain );
	SAFE_RELEASE( m_pDeviceContext );
	SAFE_RELEASE( m_pDevice );
}



#if _DEBUG

////============================================================
//	�̨��쐬.
////============================================================
HRESULT clsMain::InitSphere( clsDX9Mesh* pMesh, float fScale )
{
	LPDIRECT3DVERTEXBUFFER9 pVB = nullptr;	//���_�ޯ̧.
	void*	pVertices = nullptr;	//���_.
	D3DXVECTOR3	vCenter;		//���S.
	float	fRadius;			//���a.

	//���_�ޯ̧���擾.
	if( FAILED( pMesh->m_pMesh->GetVertexBuffer( &pVB ) ) ){
		return E_FAIL;
	}

	//ү���̒��_�ޯ̧��ۯ�����.
	if( FAILED( pVB->Lock( 0, 0, &pVertices, 0 ) ) ){
		SAFE_RELEASE( pVB );
		return E_FAIL;
	}

	//ү���̊O�ډ~�̒��S�Ɣ��a���v�Z����.
	D3DXComputeBoundingSphere(
		(D3DXVECTOR3*)pVertices,
		pMesh->m_pMesh->GetNumVertices(),	//���_�̐�.
		D3DXGetFVFVertexSize( pMesh->m_pMesh->GetFVF()),	//���_�̏��.
		&vCenter,	//(out)���S���W.
		&fRadius );	//(out)���a.

	//��ۯ�.
	pVB->Unlock();
	SAFE_RELEASE( pVB );

	//���S�Ɣ��a���\���̂ɐݒ�.
	pMesh->m_Sphere.vCenter	= vCenter;
	pMesh->m_Sphere.fRadius	= fRadius * fScale;


	return S_OK;
}

////============================================================
//	�޳��ިݸ��ޯ���쐬.
////============================================================
HRESULT clsMain::InitBBox( clsDX9Mesh* pMesh )
{
	LPDIRECT3DVERTEXBUFFER9 pVB = nullptr;
	VOID* pVertices = nullptr;
	D3DXVECTOR3 Max, Min;

	//ү���̒��_�ޯ̧��ۯ�����.
	if( FAILED( pMesh->m_pMesh->GetVertexBuffer( &pVB ) ) ){
		MessageBox( NULL, "���_�ޯ̧�擾���s", "clsMain::InitBBox()", MB_OK );
		return E_FAIL;
	}
	if( FAILED( pVB->Lock( 0, 0, &pVertices, 0 ) ) ){
		MessageBox( NULL, "���_�ޯ̧��ۯ��Ɏ��s", "clsMain::InitBBox()", MB_OK );
		return E_FAIL;
	}
	//ү�����̒��_�ʒu�̍ő�ƍŏ�����������.
	D3DXComputeBoundingBox(
		(D3DXVECTOR3*)pVertices,
		pMesh->m_pMesh->GetNumVertices(),
		D3DXGetFVFVertexSize(
			pMesh->m_pMesh->GetFVF() ),
			&Min, &Max );	//(out)�ŏ��A�ő咸�_.
	pVB->Unlock();			//��ۯ�.
	SAFE_RELEASE( pVB );	//�g�p�ϒ��_�ޯ̧�̉��.

	pMesh->m_BBox.vPosMax = Max;
	pMesh->m_BBox.vPosMin = Min;

	//���޸��,���̒���(���̏ꍇ�ޯ���̊e���a)������������.
	pMesh->m_BBox.fLengthX = ( Max.x - Min.x ) / 2.0f;
	pMesh->m_BBox.fLengthY = ( Max.y - Min.y ) / 2.0f;
	pMesh->m_BBox.fLengthZ = ( Max.z - Min.z ) / 2.0f;


	return S_OK;
}
#endif //#if _DEBUG



////============================================================
//	ү���ǂݍ��݊֐�(�܂Ƃ߂�).
////============================================================
HRESULT clsMain::ReadMesh()
{


	m_pTestData = make_unique<clsFile>();

#ifdef Inoue

	m_smpUiManagar = make_unique<clsUiManagar>();
	m_smpUiManagar->Init( m_hWnd, m_pDevice, m_pDeviceContext );

	m_smpStageDataExcel = make_unique<clsFile>();
	m_smpStageDataExcel->Init( "Data\\Text\\StageData.xlsm" );

	m_smpStageData = make_unique<clsFile>();
	m_smpStageData->Init( "Data\\Text\\StageData.csv" );

	m_smpStageDataExcelStageMax = make_unique<clsFile>();
	m_smpStageDataExcelStageMax->Init( "Data\\Text\\StageDataMax.csv" );

	m_smpStageDataReadMe = make_unique<clsFile>();
	m_smpStageDataReadMe->Init( "Data\\Text\\ReadMe.txt" );
#endif //#ifdef Inoue.





//���[�h�Ɉڍs.
/*

	//ؿ���׽.
	m_pResource = clsResource::GetInstance();

	m_pResource->InitStaticModel( m_hWnd, m_pDevice, m_pDeviceContext);
	m_pResource->InitSkinModel( m_hWnd, m_pDevice, m_pDeviceContext);

	//=====Static Model=====.
	m_pResource->CreateStaticModel(
		"Data\\Test\\Test.x",
		clsResource::enST_MODEL_Plane );

	m_pResource->CreateStaticModel(
		"Data\\Stage\\kabe.X",
		clsResource::enST_MODEL_WALL );

	m_pResource->CreateStaticModel(
		"Data\\Stage\\yuka.X",
		clsResource::enST_MODEL_FLOOR_NORMAL );

	m_pResource->CreateStaticModel(
		"Data\\Stage\\yuka_hanbun_L.X",
		clsResource::enST_MODEL_FLOOR_HALF_L );

	m_pResource->CreateStaticModel(
		"Data\\Stage\\yuka_hanbun_R.X",
		clsResource::enST_MODEL_FLOOR_HALF_R );

	//�y���f��������.
	m_pResource->CreateStaticModel(
		"Data\\Stage\\yuka_kizu.X",
		clsResource::enST_MODEL_FLOOR_PEND );

	//�c�ړ���.
	m_pResource->CreateStaticModel(
		"Data\\Stage\\StepCylinder.X",
		clsResource::enST_MODEL_STEP_CIL );
	//���ړ���.
	m_pResource->CreateStaticModel(
		"Data\\Stage\\StepBox.X",
		clsResource::enST_MODEL_STEP_BOX );

	//�h�A���f�����m�F����.
	m_pResource->CreateStaticModel(
		"Data\\Stage\\mon.X",
		clsResource::enST_MODEL_MON);
	m_pResource->CreateStaticModel(
		"Data\\Stage\\tobira.X",
		clsResource::enST_MODEL_TOBIRA );

	//�S�[�����f�����m�F����.
	m_pResource->CreateStaticModel(
		"Data\\Stage\\gool.X",
		clsResource::enST_MODEL_GOOL );

	m_pResource->CreateStaticModel(
		"Data\\Trap\\Spia.x",
		clsResource::enST_MODEL_SPIA );

	m_pResource->CreateStaticModel(
		"Data\\Trap\\SpiaWallHit.x",
		clsResource::enST_MODEL_SPIA_WALL );

	m_pResource->CreateStaticModel(
		"Data\\Trap\\hasira.x",
		clsResource::enST_MODEL_SPIA_WALL_HASIRA );

	m_pResource->CreateStaticModel(
		"Data\\Trap\\otosiana_L.x",
		clsResource::enST_MODEL_COVER_L );

	m_pResource->CreateStaticModel(
		"Data\\Trap\\otosiana_R.x",
		clsResource::enST_MODEL_COVER_R );

	m_pResource->CreateStaticModel(
		"Data\\Jikken\\1_1_1_kijyun.x",
		clsResource::enST_MODEL_BLOCK );

	m_pResource->CreateStaticModel(
		"Data\\Stage\\tobira.X",
		clsResource::enST_MODEL_TEST );

	//=====Skin Model=====.
	m_pResource->CreateSkinModel(
		"Data\\Player\\Arbia.X",
		clsResource::enSK_MODEL_PLAYER );

	m_pResource->CreateSkinModel(
		"Data\\Stage\\tobira.X",
		clsResource::enSK_MODEL_DOOR );

	m_pResource->CreateSkinModel(
		"Data\\Enemy\\Enemy.X",
		clsResource::enSK_MODEL_ENEMY );

	m_pResource->CreateSkinModel(
		"Data\\Trap\\Pendulum.X",
		clsResource::enSK_MODEL_PENDULUM );
*/


	//�v���C���[.
	{
		m_pPlayer = new clsPlayer;
		m_pPlayer->Create( m_hWnd, m_pDevice, m_pDeviceContext, m_pXInput );
		m_pPlayer->Init();

		CD3DXSKINMESH_INIT si;//skin_Init.
		si.hWnd = m_hWnd;
		si.pDevice = m_pDevice;
		si.pDeviceContext = m_pDeviceContext;

		m_pPlayer->m_pModel = new clsD3DXSKINMESH;
		m_pPlayer->m_pModel->Init( &si );

		//���ي֘A�t��.
		m_pPlayer->
			AttachModel( m_pResource->GetSkinModels( clsResource::enSK_MODEL_PLAYER ) );

		m_pPlayer->SetPosition(
			D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) );

		float LocalScale = 0.1f;
		m_pPlayer->SetScale( LocalScale );

//		m_pPlayer->SetAnimSpeed( 0.01 );
	}


	//�`�F�b�N�|�C���g����( �ŏ��̓z�͍��Ȃ�{ MOVIE�p } ).
	m_pCheck = new clsCheckPointMgr;
	m_pCheck->Create( m_hWnd, m_pDevice, m_pDeviceContext );
	m_pCheck->Init();




	//�G���f�B���O�V�[���ł̓G�\���N���X.
	m_pEndEnemy = new clsEndEnemMgr;
	m_pEndEnemy->Create( m_hWnd, m_pDevice, m_pDeviceContext );



	//�񋓑̂̃X�e�[�W�̈�ԍŏ�.
	iWallModelNumZero = m_pResource->EtoI( clsResource::enST_MODEL_WALL_MIN );
	iFloorModelNumZero = m_pResource->EtoI( clsResource::enST_MODEL_FLOOR_MIN );



	//���f���̕R�Â�.
	StageModelSet();




#if _DEBUG
	//ؿ����K.
	//��׸���׽.
	m_iBlkAryMax = 100;
	m_ppBlkAry = new clsCharaStatic*[m_iBlkAryMax];
	//��׸׽���߲���̔z������.
	for( int i=0; i<m_iBlkAryMax; i++ ){
		m_ppBlkAry[i] = new clsCharaStatic;

		//�����ް��֘A�t��.
		m_ppBlkAry[i]->AttachModel(
			m_pResource->GetStaticModels( clsResource::enST_MODEL_BLOCK ) );

		m_ppBlkAry[i]->SetPosition(
			D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) );
	}

	//�߰è�ق̏�����500��.
//	m_pParticle = new clsParticle;	//���͂������Ďg���Ă�����.
	m_pParticle = new clsParticle( iPAT_SMOK_MAX, D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) );
	m_pParticle->Init( m_pDevice, m_pDeviceContext );
	m_pParticle->m_bDispFlg = false;

	//ڲ�\���̏�����(����).
	m_pRayV = new clsRay;
	m_pRayV->m_Ray.vPoint[0] = D3DXVECTOR3( 0.0f,-5.0f, 0.0f);
	m_pRayV->m_Ray.vPoint[1] = D3DXVECTOR3( 0.0f, 5.0f, 0.0f);
	m_pRayV->Init( m_pDevice, m_pDeviceContext );
	//ڲ�\���̏�����(�O��).
	m_pRayFB = new clsRay;
	m_pRayFB->m_Ray.vPoint[0] = D3DXVECTOR3( 0.0f, 0.0f,-5.0f);
	m_pRayFB->m_Ray.vPoint[1] = D3DXVECTOR3( 0.0f, 0.0f, 5.0f);
	m_pRayFB->Init( m_pDevice, m_pDeviceContext );
	//ڲ�\���̏�����(���E).
	if( m_pRayH == nullptr ){
		m_pRayH = new clsRay;
		int r = sizeof( clsRay );
		m_pRayH->m_Ray.vPoint[0] = D3DXVECTOR3(-5.0f, 0.0f, 0.0f);
		m_pRayH->m_Ray.vPoint[1] = D3DXVECTOR3( 5.0f, 0.0f, 0.0f);
		m_pRayH->Init( m_pDevice, m_pDeviceContext );
	}

	//���ޯ��÷�Ă̏�����.
	m_pText = new clsDebugText;
	D3DXVECTOR4 vColor( 1.0f, 1.0f, 1.0f, 1.0f );
	if( FAILED( m_pText->Init(
		m_pDeviceContext,
		WND_W, WND_H, 50.0f,
		vColor ) ) )
	{
		MessageBox( NULL, "���ޯ��÷�č쐬���s", "clsMain::Loop", MB_OK );
	}
#endif //#if _DEBUG


	return S_OK;
}



//============================================================
//	�[�xý�(Zý�)ON/OFF�ؑ�.
//============================================================
void clsMain::SetDepth( bool bFlg )
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory( &depthStencilDesc,
		sizeof( D3D11_DEPTH_STENCIL_DESC ) );
	depthStencilDesc.DepthEnable = bFlg;

	m_pDevice->CreateDepthStencilState(
		&depthStencilDesc, &m_pDepthStencilState );
	m_pDeviceContext->OMSetDepthStencilState(
		m_pDepthStencilState, 1 );
}

#if _DEBUG
////============================================================
//	�Փ˔���֐�.
////============================================================
bool clsMain::Collision( clsDX9Mesh* pAttacker, clsDX9Mesh* pTarget)
{
	//2�̕��̂̒��S�Ԃ̋��������߂�.
	D3DXVECTOR3 vLength
		= pTarget->m_vPos - pAttacker->m_vPos;
	//�����ɕϊ�����.
	float Length = D3DXVec3Length( &vLength );

	//2���̊Ԃ̋������A2���̂̔��a�𑫂������̂��.
	//�������Ƃ������Ƃ́A�̨����m���d�Ȃ��Ă���.
	//(�Փ˂��Ă���)�Ƃ�������.
	if( Length <=
		pAttacker->m_Sphere.fRadius + pTarget->m_Sphere.fRadius )
	{
		return true;//�Փ˂���.
	}
	return false;	//�Փ˂��Ă��Ȃ�.
}
//============================================================
//	�ޯ���Փ˔���֐�.
//============================================================
bool clsMain::BBoxCollision( clsDX9Mesh* pAttacker, clsDX9Mesh* pTarget )
{
	//�U�����p��2�̒��_��p�ӂ�����������.
	D3DXVECTOR3 vecMaxAtk, vecMinAtk;	//�ő�A�ŏ����_.
	vecMaxAtk = pAttacker->m_BBox.vPosMax
				+ pAttacker->m_vPos;
	vecMinAtk = pAttacker->m_BBox.vPosMin
				+ pAttacker->m_vPos;

	//�ڕW���p��2�̒��_��p�ӂ�����������.
	D3DXVECTOR3 vecMaxTrg, vecMinTrg;	//�ő�A�ŏ����_.
	vecMaxTrg = pTarget->m_BBox.vPosMax
				+ pTarget->m_vPos;
	vecMinTrg = pTarget->m_BBox.vPosMin
				+ pTarget->m_vPos;

	//2�̕��̂��ꂼ��̍ő�A�ŏ��ʒu�Ƃ���,.
	//4�̏�񂪂���΁A�Փ˂����o�ł���.
	if( vecMinAtk.x < vecMaxTrg.x  &&  vecMaxAtk.x > vecMinTrg.x &&
		vecMinAtk.y < vecMaxTrg.y  &&  vecMaxAtk.y > vecMinTrg.y &&
		vecMinAtk.z < vecMaxTrg.z  &&  vecMaxAtk.z > vecMinTrg.z )
	{
		return true;//�Փ˂��Ă���.
	}

	return false;	//�Փ˂��Ă��Ȃ�.
}
#endif //#if _DEBUG


//============================================================
//	�ް݂̍��W���Ƃ�.
//============================================================
void clsMain::GetPosFromBone( clsD3DXSKINMESH* skinMesh, char BoneName[], D3DXVECTOR3& Pos )
{
	D3DXVECTOR3 vBonePos;
	if( skinMesh->GetPosFromBone( BoneName, &vBonePos ) ){
		Pos = vBonePos;
	}
}


//============================================================
//	ڲ��ү���̂����蔻��.
//============================================================
bool clsMain::Intersect(
	clsDX9Mesh* pAttacker,		//��̂̕���.
	clsDX9Mesh* pTarget,		//�Ώۂ̂̕���.
	float* pfDistance,			//(out)����.
	D3DXVECTOR3* pvIntersect )	//(out)�������W.
{
	D3DXMATRIXA16	matRot;	//��]�s��.

	//��]�s����v�Z.
	D3DXMatrixRotationY( &matRot, pAttacker->m_fYaw );

	//���޸�ق�p��.
	D3DXVECTOR3 vecAxisZ;
	//Z���޸�ق��̂��̂����݂̉�]��Ԃɂ��ϊ�����.
	D3DXVec3TransformCoord(
		&vecAxisZ, &pAttacker->m_vAxis, &matRot );

	D3DXVECTOR3 vecStart, vecEnd, vecDistance;
	//ڲ�̊J�n�I���ʒu��Attacker�ƍ��킹��.
	vecStart = vecEnd = pAttacker->m_vRay;
	//Attacker�̍��W�ɉ�]���W����������.
	vecEnd += vecAxisZ * 1.0f;

	//�Ώۂ������Ă��镨�̂ł��A�Ώۂ�world�s��́A.
	//�t�s���p����΁A������ڲ��������.
	D3DXMATRIX matWorld;
	D3DXMatrixTranslation(
		&matWorld,
		pTarget->m_vPos.x,
		pTarget->m_vPos.y,
		pTarget->m_vPos.z );

	//�t�s������߂�.
	D3DXMatrixInverse( &matWorld, NULL, &matWorld );
	D3DXVec3TransformCoord(
		&vecStart, &vecStart, &matWorld );
	D3DXVec3TransformCoord(
		&vecEnd, &vecEnd, &matWorld );

	//���������߂�.
	vecDistance = vecEnd - vecStart;

	BOOL bHit = false;	//�����׸�.

	DWORD dwIndex = 0;	//���ޯ���ԍ�.
	D3DXVECTOR3 vVertex[3];	//���_���W.
	FLOAT U = 0, V = 0;	//(out)�d�S˯č��W.

	//ү����ڲ�̌����𒲂ׂ�.
	D3DXIntersect(
		pTarget->m_pMesh,//�Ώ�ү��.
		&vecStart,		//�J�n�ʒu.
		&vecDistance,	//ڲ�̋���.
		&bHit,			//(out)���茋��.
		&dwIndex,		//(out)bHit��True���Aڲ�̎��_�ɁB.
						//�ł��߂��̖ʂ̲��ޯ���l�ւ��߲��.
		&U, &V,			//(out)�d�S˯č��W.
		pfDistance,		//���ޯĂƂ̋���.
		NULL, NULL );

	if( bHit ){
		//���������Ƃ�.
		FindVerticesOnPoly(
			pTarget->m_pMeshForRay, dwIndex, vVertex );
		//�d�S���W��������_���Z�o.
		//۰�ٌ�_p�́A v0 + U*(v1-v0) + V*(v2-v0)�ŋ��܂�.
		*pvIntersect =
			vVertex[0]
			+ U * ( vVertex[1] - vVertex[0] )
			+ V * ( vVertex[2] - vVertex[0] );

		return true;
	}
	return false;
}

//============================================================
//	�����ʒu����غ�݂̒��_��������.
//		�����_���W��۰�ٍ��W.
//============================================================
HRESULT clsMain::FindVerticesOnPoly(
	LPD3DXMESH pTarget, DWORD dwPolyIndex,
	D3DXVECTOR3* pVecVertices )
{
	//���_���̃o�޲Đ����擾.
	DWORD dwStride = pTarget->GetNumBytesPerVertex();
	//���_�����擾.
	DWORD dwVertexAmt = pTarget->GetNumVertices();
	//�ʐ����擾.
	DWORD dwPolyAmt = pTarget->GetNumFaces();

	WORD* pwPoly = nullptr;

	//���ޯ���ޯ̧��ۯ�(�Ǎ�Ӱ��).
	pTarget->LockIndexBuffer(
		D3DLOCK_READONLY, (VOID**)&pwPoly );
	BYTE*	pbVertices = nullptr;	//���_(�޲Č^)
	FLOAT*	pfVertices = nullptr;	//���_(float�^)
	LPDIRECT3DVERTEXBUFFER9 VB = nullptr;	//���_�ޯ̧.
	pTarget->GetVertexBuffer( &VB );	//���_���̎擾.

	//���_�ޯ̧��ۯ�.
	if( SUCCEEDED(
		VB->Lock( 0, 0, (VOID**)&pbVertices, 0 ) ) )
	{
		////��غ�݂̒��_��1�ڂ��擾.
		//pfVertices
		//	= (FLOAT*)&pbVertices[ dwStride * pwPoly[ dwPolyIndex * 3 ] ];
		//pVecVertices[0].x = pfVertices[0];
		//pVecVertices[0].y = pfVertices[1];
		//pVecVertices[0].z = pfVertices[2];
		////��غ�݂̒��_��2�ڂ��擾.
		//pfVertices
		//	= (FLOAT*)&pbVertices[ dwStride * pwPoly[ dwPolyIndex * 3 + 1 ] ];
		//pVecVertices[1].x = pfVertices[0];
		//pVecVertices[1].y = pfVertices[1];
		//pVecVertices[1].z = pfVertices[2];
		////��غ�݂̒��_��3�ڂ��擾.
		//pfVertices
		//	= (FLOAT*)&pbVertices[ dwStride * pwPoly[ dwPolyIndex * 3 + 2 ] ];
		//pVecVertices[2].x = pfVertices[0];
		//pVecVertices[2].y = pfVertices[1];
		//pVecVertices[2].z = pfVertices[2];

		////��غ�݂̒��_��1�`3�ڂ��擾.
		for( int i=0; i<3; i++ ){
			pfVertices
				= (FLOAT*)&pbVertices[ dwStride * pwPoly[ dwPolyIndex * 3 + i ] ];
			pVecVertices[i].y = pfVertices[1];
			pVecVertices[i].z = pfVertices[2];
			pVecVertices[i].x = pfVertices[0];
		}

		//ۯ�����.
		pTarget->UnlockIndexBuffer();
		VB->Unlock();
	}
	VB->Release();

	return S_OK;
}


//============================================================
//	�ǂ̂����蔻��֘A.
//============================================================
void clsMain::WallJudge( clsDX9Mesh* pAttacker, clsDX9Mesh* pWall )
{
	const char MAX = 4;//.���̐�
	const float HitHeight = 0.375f;	//���ޱ�̑�������̍���.

	FLOAT		fDistance[MAX] = { 0.0f, 0.0f, 0.0f, 0.0f };	//����.
	D3DXVECTOR3	vIntersect[MAX];//��_���W.
	float		fDis, fYaw;		//�����Ɖ�].


	pAttacker->m_vRay = pAttacker->m_vPos;
	pAttacker->m_vRay.y += HitHeight;

#if 0
	//���޸�ق̕����O��E��.
	D3DXVECTOR3 Axis[MAX] ={D3DXVECTOR3( 0.0f, 0.0f, 1.0f ),
							D3DXVECTOR3( 0.0f, 0.0f,-1.0f ),
							D3DXVECTOR3( 1.0f, 0.0f, 0.0f ),
							D3DXVECTOR3(-1.0f, 0.0f, 0.0f ) };
	//ڲ�̌����ɂ�蓖����ǂ܂ł̋��������߂�.
	//���޸�ّO��E��.
	for( char i=0; i<MAX; i++ ){
		pAttacker->m_vAxis = Axis[i];
		Intersect( pAttacker, pWall, &fDistance[i], &vIntersect[i] );
	}
#else
	//���޸�ّO.
	pAttacker->m_vAxis = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
	Intersect( pAttacker, pWall, &fDistance[0], &vIntersect[0] );
	//���޸�ٌ�.
	pAttacker->m_vAxis = D3DXVECTOR3( 0.0f, 0.0f,-1.0f );
	Intersect( pAttacker, pWall, &fDistance[1], &vIntersect[1] );
	//���޸�ىE.
	pAttacker->m_vAxis = D3DXVECTOR3( 1.0f, 0.0f, 0.0f );
	Intersect( pAttacker, pWall, &fDistance[2], &vIntersect[2] );
	//���޸�ٍ�.
	pAttacker->m_vAxis = D3DXVECTOR3(-1.0f, 0.0f, 0.0f );
	Intersect( pAttacker, pWall, &fDistance[3], &vIntersect[3] );
#endif

	//��Βl.
	fYaw = fabs( pAttacker->m_fYaw );
	DirOverGuard( &fYaw );


	//�O���ǂɐڋ�.
	fDis = fDistance[0];
	if( fDis < WALL_SPACE && fDis > 0.01f ){
		if( pAttacker->m_fYaw < 0.0f ){
			//���v���.
			if( fYaw >= 0.785f && fYaw < 2.355f ){		//�E����.
				pAttacker->m_vPos.x += WALL_SPACE - fDis;
			}
			else if( fYaw >= 2.355f && fYaw < 3.925f ){	//�O����.
				pAttacker->m_vPos.z += WALL_SPACE - fDis;
			}
			else if( fYaw >= 3.925f && fYaw < 5.495f ){	//������.
				pAttacker->m_vPos.x -= WALL_SPACE - fDis;
			}
			else{										//������.
				pAttacker->m_vPos.z -= WALL_SPACE - fDis;
			}
		}
		else{
			//�����v���.
			if( fYaw >= 0.785f && fYaw < 2.355f ){		//�E����.
				pAttacker->m_vPos.x -= WALL_SPACE - fDis;
			}
			else if( fYaw >= 2.355f && fYaw < 3.925f ){	//�O����.
				pAttacker->m_vPos.z += WALL_SPACE - fDis;
			}
			else if( fYaw >= 3.925f && fYaw < 5.495f ){	//������.
				pAttacker->m_vPos.x += WALL_SPACE - fDis;
			}
			else{										//������.
				pAttacker->m_vPos.z -= WALL_SPACE - fDis;
			}
		}
	}

	//��낪�ǂɐڋ�.
	fDis = fDistance[1];
	if( fDis < WALL_SPACE && fDis > 0.01f ){
		//���v���.
		if( pAttacker->m_fYaw < 0.0f ){
			if( fYaw >= 0.785f && fYaw < 2.355f ){		//�E����.
				pAttacker->m_vPos.x -= WALL_SPACE - fDis;
			}
			else if( fYaw >= 2.355f && fYaw < 3.925f ){	//�O����.
				pAttacker->m_vPos.z -= WALL_SPACE - fDis;
			}
			else if( fYaw >= 3.925f && fYaw < 5.495f ){	//������.
				pAttacker->m_vPos.x += WALL_SPACE - fDis;
			}
			else{										//������.
				pAttacker->m_vPos.z += WALL_SPACE - fDis;
			}
		}
		//�����v���.
		else{
			if( fYaw >= 0.785f && fYaw < 2.355f ){		//�E����.
				pAttacker->m_vPos.x += WALL_SPACE - fDis;
			}
			else if( fYaw >= 2.355f && fYaw < 3.925f ){	//�O����.
				pAttacker->m_vPos.z -= WALL_SPACE - fDis;
			}
			else if( fYaw >= 3.925f && fYaw < 5.495f ){	//������.
				pAttacker->m_vPos.x -= WALL_SPACE - fDis;
			}
			else{										//������.
				pAttacker->m_vPos.z += WALL_SPACE - fDis;
			}
		}
	}

	//�E���ǂɐڋ�.
	fDis = fDistance[2];
	if( fDis < WALL_SPACE && fDis > 0.01f ){
		//���v���.
		if( pAttacker->m_fYaw < 0.0f ){
			if( fYaw >= 0.785f && fYaw < 2.355f ){		//�E����.
				pAttacker->m_vPos.z -= WALL_SPACE - fDis;
			}
			else if( fYaw >= 2.355f && fYaw < 3.925f ){	//�O����.
				pAttacker->m_vPos.x += WALL_SPACE - fDis;
			}
			else if( fYaw >= 3.925f && fYaw < 5.495f ){	//������.
				pAttacker->m_vPos.z += WALL_SPACE - fDis;
			}
			else{										//������.
				pAttacker->m_vPos.x -= WALL_SPACE - fDis;
			}
		}
		//�����v���.
		else{
			if( fYaw >= 0.785f && fYaw < 2.355f ){		//�E����.
				pAttacker->m_vPos.z += WALL_SPACE - fDis;
			}
			else if( fYaw >= 2.355f && fYaw < 3.925f ){	//�O����.
				pAttacker->m_vPos.x += WALL_SPACE - fDis;
			}
			else if( fYaw >= 3.925f && fYaw < 5.495f ){	//������.
				pAttacker->m_vPos.z -= WALL_SPACE - fDis;
			}
			else{										//������.
				pAttacker->m_vPos.x -= WALL_SPACE - fDis;
			}
		}
	}

	//�����ǂɐڋ�.
	fDis = fDistance[3];
	if( fDis < WALL_SPACE && fDis > 0.01f ){
		//���v���.
		if( pAttacker->m_fYaw < 0.0f ){
			if( fYaw >= 0.785f && fYaw < 2.355f ){		//�E����.
				pAttacker->m_vPos.z += WALL_SPACE - fDis;
			}
			else if( fYaw >= 2.355f && fYaw < 3.925f ){	//�O����.
				pAttacker->m_vPos.x -= WALL_SPACE - fDis;
			}
			else if( fYaw >= 3.925f && fYaw < 5.495f ){	//������.
				pAttacker->m_vPos.z -= WALL_SPACE - fDis;
			}
			else{										//������.
				pAttacker->m_vPos.x += WALL_SPACE - fDis;
			}
		}
		//�����v���.
		else{
			if( fYaw >= 0.785f && fYaw < 2.355f ){		//�E����.
				pAttacker->m_vPos.z -= WALL_SPACE - fDis;
			}
			else if( fYaw >= 2.355f && fYaw < 3.925f ){	//�O����.
				pAttacker->m_vPos.x -= WALL_SPACE - fDis;
			}
			else if( fYaw >= 3.925f && fYaw < 5.495f ){	//������.
				pAttacker->m_vPos.z += WALL_SPACE - fDis;
			}
			else{										//������.
				pAttacker->m_vPos.x += WALL_SPACE - fDis;
			}
		}
	}
}

//============================================================
//	��]�l����.
//============================================================
void clsMain::DirOverGuard( float* fYaw )
{
	if( *fYaw > (float)( D3DX_PI * 2.0 ) ){
		*fYaw -= (float)( D3DX_PI * 2.0 );
	}
	else{
		return;
	}

	//�ċA.
	if( *fYaw > (float)( D3DX_PI * 2.0 ) ){
		DirOverGuard( fYaw );
	}
}


//============================================================
//	��׊֐�.
//============================================================
void clsMain::Camera()
{

////----------------------------.
////	��גǏ]������������.
////----------------------------.
////��׈ʒu(���@�̔w������)�̈ʒu.
//m_Camera.vEye = m_Camera.vLook = m_pOldPlayer->m_vPos;
//m_Camera.fYaw = m_pOldPlayer->m_fYaw;
////Y����]�s��̍쐬.
//D3DXMatrixRotationY( &m_Camera.mRot, m_Camera.fYaw );
////���޸��.
//D3DXVECTOR3 vecAxisZ( 0.0f, 0.0f, 1.0f );
////Z���޸�ق��̂��̂���].
//D3DXVec3TransformCoord( &vecAxisZ, &vecAxisZ, &m_Camera.mRot );
//m_Camera.vEye	-= vecAxisZ * 4.0f;//���@�̔w����.
//m_Camera.vLook	+= vecAxisZ * 2.0f;//���@�̑O��.
//m_Camera.vEye.y		+= 2.0f;
//m_Camera.vLook.y	+= 0.2f;
////----------------------------.
////	��גǏ]���������܂�.
////----------------------------.


	//�ޭ�(���)�ϊ�.
	D3DXVECTOR3 vUpVec	( 0.0f, 1.0f, 0.0f );	//����ʒu.
	D3DXMatrixLookAtLH(
		&m_mView,	//(out)�ޭ��v�Z����.
		&m_Camera.vEye, &m_Camera.vLook, &vUpVec );

}
//============================================================
//	��ۼު���݊֐�.
//============================================================
void clsMain::Proj()
{
	//��ۼު����(�ˉe�s��)�ϊ�.
	D3DXMatrixPerspectiveFovLH(
		&m_mProj,			//(out)��ۼު���݌v�Z����.
		fZOOM,	//y�����̎���(׼ޱݎw��)������傫�������王�삪�����Ȃ�.
		(FLOAT)WND_W / (FLOAT)WND_H,//���߸Ĕ�(��/����).
		0.1f,				//�߂��ޭ����ʂ�z�l.
		fRENDER_LIMIT );	//�����ޭ����ʂ�z�l.100.f

}


//============================================================
//============================================================
//				�V�[���������V���[�Y.
//============================================================
//============================================================
//============================================================
//	�^�C�g���p������.
//============================================================
void clsMain::InitTitle()
{
	InitMain( true, true );


	//�������J�����ʒu.
	const D3DXVECTOR3 vCAM_INIT_TITLE_POS =
		{ 0.7f, 2.4f, 6.7f };
	const D3DXVECTOR3 vLOOK_INIT_TITLE_POS =
		{ -1.4f, 1.55f, 9.6f };
	m_Camera.vEye = vCAM_INIT_TITLE_POS;
	m_Camera.vLook = vLOOK_INIT_TITLE_POS;

	//�V�[��.
	m_enScene = enSCENE_TITLE;
	m_enTitleSceneMode = en_TSM_IDLE;
	//UI.
	m_smpUiManagar->ChangeTitleInit();

	m_ResUiState.Init();

	//�������X�V.
	m_smpUiManagar->SetDisc( m_ResUiState.iDisc );
	m_smpUiManagar->SetLives( m_ResUiState.iLives );

	//BGM.
	m_pBgm[enBGM_MAIN]->Stop();
	m_pBgm[enBGM_ENDROLL]->Stop();
	m_pBgm[enBGM_OVER]->Stop();

	m_pBgm[enBGM_TITLE]->SeekToStart();
	m_pBgm[enBGM_TITLE]->Play( true );


	//�v���C���[.
	m_pPlayer->InitTitleScene();

	//�G���h���[���ŕ��ꂽ��C��.
	m_vsmpWall[0]->SetPosition( vTITLE_INIT_STAGE_POS );
	m_vsmpFloor[0]->SetPosition( vTITLE_INIT_STAGE_POS );
	m_vsmpCeiling[0]->SetPosition( vENDING_INIT_CEILING_POS );


	//�h�A.
	for( int i=0; i<m_vsmpDoorMgr.size(); i++ ){
		m_vsmpDoorMgr[i]->Init();
	}

}
//============================================================
//	�X�e�[�W�J�n�p������.
//============================================================
void clsMain::InitMain( bool bFirstFlg, bool bTitle )
{
	//����̏�����.
	if( bFirstFlg ){
		//�V�[��.
		m_enScene = enSCENE_MAIN;
		if( !bTitle ){
			m_smpUiManagar->ChangeMainInit();
		}
		//BGM.
		m_pBgm[enBGM_TITLE]->Stop();
		m_pBgm[enBGM_MAIN]->Stop();
		m_pBgm[enBGM_MAIN]->SeekToStart();
		m_pBgm[enBGM_MAIN]->SetVolume( iVOL_BGM_MAIN );
		m_pBgm[enBGM_MAIN]->Play( true );
		//�v���C���[.
		m_pPlayer->Spawn();
		//�h�A(0�̓^�C�g��).
		for( int i=1; i<m_vsmpDoorMgr.size(); i++ ){
			m_vsmpDoorMgr[i]->Init();
		}
		//����.
		m_smpUiManagar->ReSetTimer();
		m_smpUiManagar->SetTimerStop( true );
		//������.
		m_smpUiManagar->ReSetDisc();
		//�c�@.
		m_smpUiManagar->ReSetLives();
	}
	//�������̏�����.
	else{
		//�v���C���[.
		m_pPlayer->ReSpawn();
		//�h�A(0�̓^�C�g��).
		for( int i=0; i<m_vsmpDoorMgr.size(); i++ ){
			m_vsmpDoorMgr[i]->ReStart();
		}
		//�^�C�}������.
		m_smpUiManagar->SetTimerStop( false );
	}
	m_iRespawnTimer = 0;

	//�c�@.
	m_smpUiManagar->SetLives( m_pPlayer->GetHp() );

	//�J����.
	D3DXVECTOR3 vCamInitPos = m_pPlayer->GetPosition() + vCAMERA_INIT_OFFSET;
	m_Camera.vEye = m_vCameraTarget = vCamInitPos;
	m_fLookOffset = 0.0f;

	//�ۏ�.
	for( int i=0; i<m_vsmpStepCil.size(); i++ ){
		m_vsmpStepCil[i]->Init();
	}
	//�l�p��.
	for( int i=0; i<m_vsmpStepBox.size(); i++ ){
		m_vsmpStepBox[i]->Init();
	}


	//�G.
	for( int i=0; i<m_vsmpEnemyMgr.size(); i++ ){
		m_vsmpEnemyMgr[i]->Init( bFirstFlg );
	}


	//����.
	for( int i=0; i<m_vsmpSpiaFloorMgr.size(); i++ ){
		m_vsmpSpiaFloorMgr[i]->Init();
	}
	//�Ǒ�.
	for( int i=0; i<m_vsmpSpiaWallMgr.size(); i++ ){
		m_vsmpSpiaWallMgr[i]->Init();
	}



	//�U��q.
	for( int i=0; i<m_vsmpPend.size(); i++ ){
		m_vsmpPend[i]->Init();
	}

	//���Ƃ���.
	for( int i=0; i<m_vsmpCoverMgr.size(); i++ ){
		m_vsmpCoverMgr[i]->Init();
	}

	//�S�[��.
	for( int i=0; i<m_vsmpGoalMgr.size(); i++ ){
		m_vsmpGoalMgr[i]->Init();
	}

	//�y���f�������̉Ήԗp.
	if( bFirstFlg ){
		//���̏�Ȃ�ΉΉ�.
		for( int i=0; i<m_vsmpPend.size(); i++ ){
			for( int j=0; j<m_vsmpFloor.size(); j++ ){
				//����.
				if( m_vsmpPend[i]->GetPositionZ() > m_vsmpFloor[j]->GetPositionZ() - ( fONE_BLOCK_SIZE / 2.0f ) &&
					m_vsmpPend[i]->GetPositionZ() < m_vsmpFloor[j]->GetPositionZ() + ( fONE_BLOCK_SIZE / 2.0f ) )
				{
					m_vsmpPend[i]->SetFireDisp( true );
					break;
				}
				//�ʂ�߂�����.
				else if( m_vsmpPend[i]->GetPositionZ() < m_vsmpFloor[j]->GetPositionZ() + ( fONE_BLOCK_SIZE / 2.0f ) ){
					//���̃y���f�����������.
					m_vsmpPend[i]->SetFireDisp( false );
					break;
				}
			}
		}
	}

}
//============================================================
//	�Q�[���I�[�o�[�p������.
//============================================================
void clsMain::InitOver()
{
	//�J�����������ʒu.
	const D3DXVECTOR3 vCAM_INIT_OVER_POS = { 0.55f, 3.619998f, -4.024998f };
	const D3DXVECTOR3 vLOOK_INIT_OVER_POS = { 0.3f, 1.762501f, 0.375f };

	//�V�[��.
	m_enScene = enSCENE_OVER;
	//UI.
	m_smpUiManagar->ChangeOverInit();
	//BGM.
	m_pBgm[enBGM_MAIN]->Stop();
	m_pBgm[enBGM_OVER]->SeekToStart();
	m_pBgm[enBGM_OVER]->Play( true );

	m_pPlayer->InitOverScene();


	m_Camera.vEye = vCAM_INIT_OVER_POS;
	m_Camera.vLook = vLOOK_INIT_OVER_POS;

}
//============================================================
//	���ʗp������.
//============================================================
void clsMain::InitResult()
{
	//�V�[��.
	m_enScene = enSCENE_RESULT;
	m_enResultSceneMode = enRSM_SILENCE;

	//�󔠂̉�ʏ�̍��W���΂̏o���ʒu�ɂ���.
	m_smpUiManagar->SetJewelAppPos(
		ConvDimPos(
			m_smpUiManagar->GetJewelAppPos(),
			m_vsmpGoalMgr[0]->GetBoxPos() ) );

	//���U���g���Z�b�g.
	UpDateJewelState();
	SetJewelState();

	m_smpUiManagar->ChangeResultInit();

	m_smpUiManagar->SetTimerStop( true );


	//BGM.
	m_iResultTimer = 0;
	m_pBgm[enBGM_MAIN]->Stop();
//	m_pBgm[enBGM_RESULT]->SeekToStart();
//	m_pBgm[enBGM_RESULT]->Play( true );


}
//============================================================
//	�N���A�p������.
//============================================================
void clsMain::InitEndroll()
{
	//�V�[��.
	m_enScene = enSCENE_ENDROLL;
	//UI.
	m_smpUiManagar->ChangeEndingInit();
	//BGM.
	m_pBgm[enBGM_RESULT]->Stop();
	m_pBgm[enBGM_MAIN]->Stop();
	m_pBgm[enBGM_ENDROLL]->SeekToStart();
	m_pBgm[enBGM_ENDROLL]->Play( true );



	//�������J�����ʒu.
	const D3DXVECTOR3 vCAM_INIT_END_POS =
		{ -2.35f, 1.95f, 3.5f };
	const D3DXVECTOR3 vLOOK_INIT_END_POS =
		{ -1.6f, 2.15f, 6.4f };
	m_Camera.vEye = vCAM_INIT_END_POS;
	m_Camera.vLook = vLOOK_INIT_END_POS;


	//�v���C���[.
	m_pPlayer->InitEndScene();


	//�S�[��.
	for( int i=0; i<m_vsmpGoalMgr.size(); i++ ){
		m_vsmpGoalMgr[i]->Init();
	}

	//�G���f�B���O�V�[���̔w�i�X�N���[��.
	m_fEndScrol = 0.0f;

	//�G�Ɍ���������( �����_�[�Ŏg�� ).
	m_iEnemyDiscNum = m_ResUiState.iDisc;
	m_pEndEnemy->Init( m_pPlayer->GetPosition(), m_iEnemyDiscNum );

}



//============================================================
//	���.
//============================================================
void clsMain::CameraMgr()
{
	if( m_pPlayer != nullptr ){
		CameraTargetSet();
		Stoker( m_Camera.vEye, m_vCameraTarget );
		CameraLookSet();
	}
}
void clsMain::CameraTargetSet()
{
	float CamTarStopPointN, CamTarStopPointS;
	CamTarStopPointN = 7.0f;
	CamTarStopPointS = 15.0f;
	const float fCAM_SOUTH_OFFSET = CamTarStopPointS - CamTarStopPointN;//�k�����ɔ�ׂē�ւ͂ǂꂾ�������邩.
	const float fCAMERA_OFFSET_MOVE_Y = 0.05f; //�O��؂�ւ����̃J�����ړ���.

	const float fCAMERA_OFFSET_MOVE_BACK_LIMIT = 0.125f; //��Ԏ�O���̃J�����ړ���.


	//��{�ʒu.
	m_vCameraTarget.z = m_pPlayer->GetPositionZ() - CamTarStopPointN;
	//�����ɂ��I�t�Z�b�g.
	m_vCameraTarget.z += m_fLookOffset;

	//��Ԏ�O.
	if( m_pPlayer->GetPositionZ() <= fCAMERA_NOT_BACK )
	{
		m_fLookOffset += fCAMERA_OFFSET_MOVE_BACK_LIMIT;
		if( m_fLookOffset > 0 ){
			m_fLookOffset = 0.0f;
		}
	}
	//�k����.
	else if( m_pPlayer->GetDirNorth() )
	{
		m_fLookOffset += fCAMERA_OFFSET_MOVE_Y;
		if( m_fLookOffset > 0 ){
			m_fLookOffset = 0.0f;
		}
	}
	//�����.
	else{
		m_fLookOffset -= fCAMERA_OFFSET_MOVE_Y;
		if( m_fLookOffset < -fCAM_SOUTH_OFFSET ){
			m_fLookOffset = -fCAM_SOUTH_OFFSET;
		}
	}

//	//�X�e�[�W�̈�Ԏ�O�ł͊��.
//	if( m_pPlayer->GetPositionZ() <= CAMERA_NOT_BACK ){
//		m_vCameraTarget.z += CamTarMovSpdN;
//		if( m_vCameraTarget.z > player_z - CamTarStopPointN ){
//			m_vCameraTarget.z = player_z - CamTarStopPointN;
//		}
//	}
}
bool clsMain::Stoker( D3DXVECTOR3& Pos, D3DXVECTOR3 TargetPos )
{
	//��ׂ����ޯĂ�ǂ�������.
	const float CamMoveStop = 0.0078125f;	//��~����.
	const float CamMoveStep = 0.05f;	//����������ƶ�׈ړ����x���Ȃ�.

	//���ǂ蒅����?�t���O.
	bool bX, bY, bZ;
	bX = bY = bZ = false;

	//����.
	float lCamMove = CameraLengthComp( Pos.x, TargetPos.x );
	//�������v�Z���Ķ�גǏ].
	if( abs( lCamMove ) > CamMoveStop ){
		Pos.x += lCamMove * CamMoveStep;
	}
	else{
		bX = true;
	}
	lCamMove = CameraLengthComp( Pos.z, TargetPos.z );
	if( abs( lCamMove ) > CamMoveStop ){
		Pos.z += lCamMove * CamMoveStep;
	}
	else{
		bY = true;
	}
	lCamMove = CameraLengthComp( Pos.y, TargetPos.y );
	if( abs( lCamMove ) > CamMoveStop ){
		Pos.y += lCamMove * CamMoveStep;
	}
	else{
		bZ = true;
	}

	return bX & bY & bZ;
}

void clsMain::CameraLookSet()
{
	const float LOOK_JUMP_OFFSET_Y_RATE = 4.0f;

	//���̏�p����.
	if( m_pPlayer->m_fFloorY >= 0.0f ){
		m_fCameraLookFloorOld = m_fCameraLookFloor;
		if( m_fCameraLookFloorOld > 0.0f ) m_fCameraLookFloorOld = 0.0f;
	}
	if( m_fCameraLookFloorOld < 0.0f ){
		m_fCameraLookFloorOld = m_pPlayer->m_fFloorY;
	}


	//���_���s.
	m_vLookTarget = m_Camera.vEye;
	m_vLookTarget.z += fLOOK_OFFSET_Z;

	//���鍂���ް�.
	m_fCameraLookFloor = m_pPlayer->m_fFloorY;
	m_vLookTarget.y = m_fCameraLookFloorOld;

	//���鍂����������̍���.
	m_vLookTarget.y += fLOOK_OFFSET_Y;


	//�ެ��߱����Ō��グ��.
	if( m_pPlayer->isCamLookUp() ){
		if( m_pPlayer->GetPositionY() > m_vLookTarget.y ){
			float look_offset_y = m_pPlayer->GetPositionY()
				- m_vLookTarget.y;
			look_offset_y /= LOOK_JUMP_OFFSET_Y_RATE;
			m_vLookTarget.y += look_offset_y;
		}
	}

	m_Camera.vLook = m_vLookTarget;
}
float clsMain::CameraLengthComp( float Attker, float Target )
 {
	float Langth = Target - Attker;

	return Langth;
 }




//============================================================
//	��u�ŐU������Ȃ�(���X�ɐU�����).
//============================================================
void clsMain::YawSpnToTarg( float& NowYaw, float TarYaw, float TurnSpd, float TurnStop )
{
	//3600������.
	if( TarYaw - NowYaw > (float)M_PI ){
		TarYaw -= (float)( M_PI * 2.0 );
	}
	else if( TarYaw - NowYaw < (float)( -M_PI ) ){
		TarYaw += (float)( M_PI * 2.0 );
	}

	//�p�x���߂Â�.
	if( abs( TarYaw - NowYaw ) > TurnStop ){
		if( NowYaw < TarYaw ){
			NowYaw += TurnSpd;
		}
		else if( NowYaw > TarYaw ){
			NowYaw -= TurnSpd;
		}
	}
}


void clsMain::CreateSound()
{
	//BGM.
	{
		//�T�E���h�\����.
		clsSound::SOUND_DATA tmpSData[enBGM_MAX] =
		{
			{ ALIAS_NAME_BGM_START_UP,	FILE_PATH_BGM_START_UP, iVOL_BGM_START_UP	},
			{ ALIAS_NAME_BGM_TITLE,		FILE_PATH_BGM_TITLE,	iVOL_BGM_TITLE		},
			{ ALIAS_NAME_BGM_MAIN,		FILE_PATH_BGM_MAIN,		iVOL_BGM_MAIN		},
			{ ALIAS_NAME_BGM_RESULT,	FILE_PATH_BGM_RESULT,	iVOL_BGM_RESULT		},
			{ ALIAS_NAME_BGM_CLEAR,		FILE_PATH_BGM_CLEAR,	iVOL_BGM_CLEAR		},
			{ ALIAS_NAME_BGM_OVER,		FILE_PATH_BGM_OVER,		iVOL_BGM_OVER		},
		};
		for( int i=0; i<enBGM_MAX; i++ ){
			m_pBgm[i] = new clsSound;
			//���O.
			char cAliasName[STR_BUFF_MAX] = "";
			strcat_s( cAliasName, sizeof( cAliasName ), tmpSData[i].sAlias );
			//�쐬.
			m_pBgm[i]->Open( tmpSData[i].sPath, cAliasName, m_hWnd );
	//		//�ő剹�ʐݒ�.
	//		m_pBgm[i]->SetMaxVolume( tmpSData[i].iMaxVolume );
			//�����ʏ�����.
			m_pBgm[i]->SetVolume( tmpSData[i].iMaxVolume );
		}
	}


	//SE.
	{
		//�T�E���h�\����.
		clsSound::SOUND_DATA tmpSData[enSe_MAX] =
		{
			{ ALIAS_NAME_SE_ENTER,	FILE_PATH_SE_ENTER, iVOL_SE_ENTER	},
			{ ALIAS_NAME_SE_EXIT,	FILE_PATH_SE_EXIT,	iVOL_SE_EXIT	},
		};
		for( int i=0; i<enSe_MAX; i++ ){
			m_pSe[i] = new clsSound;
			//���O.
			char cAliasName[STR_BUFF_MAX] = "";
			strcat_s( cAliasName, sizeof( cAliasName ), tmpSData[i].sAlias );
			//�쐬.
			m_pSe[i]->Open( tmpSData[i].sPath, cAliasName, m_hWnd );
	//		//�ő剹�ʐݒ�.
	//		m_pBgm[i]->SetMaxVolume( tmpSData[i].iMaxVolume );
			//�����ʏ�����.
			m_pSe[i]->SetVolume( tmpSData[i].iMaxVolume );
		}
	}
}




//============================================================
//	for���̏����̖��ʂ����炷.
//============================================================
//�����蔻��.
bool clsMain::isCutOutForHit( float fPlayerZ, float fObjZ, float fBack, float fOpposite ){
	float fOffsetBack = 17.0f;	//��(��O)�ɂǂꂾ�����肷�邩.
	float fOffsetOpposite = fOffsetBack;	//�O(��)�ɂǂꂾ�����肷�邩.
#if 0
	//�w�苗���ȓ��Ȃ�.
	if( abs( fPlayerZ - fObjZ ) <= fOffset ){
		return true;
	}
#else
	if( fBack > 0.0f ){
		fOffsetBack = fBack;
	}
	if( fOpposite > 0.0f ){
		fOffsetOpposite = fOpposite;
	}

	if( -fOffsetBack < ( fObjZ - fPlayerZ ) ){
		if( ( fPlayerZ - fObjZ ) < fOffsetOpposite ){
			return true;
		}
	}
#endif
	return false;
}
//����.
bool clsMain::isCutOutForMove( float fPlayerZ, float fObjZ, float fBack, float fOpposite ){
	float fOffsetBack = 32.0f;	//��ɂǂꂾ�����肷�邩.
	float fOffsetOpposite = fRENDER_LIMIT;	//�O�ɂǂꂾ�����肷�邩.
	if( fBack ){
		fOffsetBack = fBack;
	}
	if( fOpposite ){
		fOffsetOpposite = fOpposite;
	}

	if( -fOffsetBack < ( fObjZ - fPlayerZ ) ){
		if( ( fObjZ - fPlayerZ ) < fOffsetOpposite ){
			return true;
		}
	}

	return false;
}

void clsMain::StageSet()
{
	StagePatarunSet tmp;
	if ( !m_vStageDataPatarnSet.empty() )
	{
		m_vStageDataPatarnSet.clear();
	}

	m_vsmpWall.reserve(m_smpStageDataExcelStageMax->GetDataArray()[0]);
	m_vsmpFloor.reserve(m_smpStageDataExcelStageMax->GetDataArray()[1]);
	m_vsmpEnemyMgr.reserve(m_smpStageDataExcelStageMax->GetDataArray()[2]);
	m_vsmpStepCil.reserve(m_smpStageDataExcelStageMax->GetDataArray()[3]);
	m_vsmpStepBox.reserve(m_smpStageDataExcelStageMax->GetDataArray()[4]);
	m_vsmpDoorMgr.reserve(m_smpStageDataExcelStageMax->GetDataArray()[5]);
	m_vsmpPend.reserve(m_smpStageDataExcelStageMax->GetDataArray()[6]);
	m_vsmpSpiaFloorMgr.reserve(m_smpStageDataExcelStageMax->GetDataArray()[7]);
	m_vsmpSpiaWallMgr.reserve(m_smpStageDataExcelStageMax->GetDataArray()[8]);
	m_vsmpCoverMgr.reserve(m_smpStageDataExcelStageMax->GetDataArray()[9]);
	m_vsmpGoalMgr.reserve(m_smpStageDataExcelStageMax->GetDataArray()[10]);
	m_vsmpTest.reserve(m_smpStageDataExcelStageMax->GetDataArray()[11]);

	m_vsmpCeiling.reserve(m_iStageDataMax);

	m_vStageDataPatarnSet.reserve(m_smpStageData->GetDataArrayNumMax()/STAGEPATARUNSETMAX);

	for( int i=0; i<m_smpStageData->GetDataArrayNumMax(); i += STAGEPATARUNSETMAX )
	{
		m_smpStageData->GetDataArray( &tmp.iWall,		i );
		m_smpStageData->GetDataArray( &tmp.iFloor,		i + 1 );
		m_smpStageData->GetDataArray( &tmp.iEnemy,		i + 2 );
		m_smpStageData->GetDataArray( &tmp.iStepCil,	i + 3 );
		m_smpStageData->GetDataArray( &tmp.iStepBox,	i + 4 );
		m_smpStageData->GetDataArray( &tmp.bDoor,		i + 5 );
		m_smpStageData->GetDataArray( &tmp.iPend,		i + 6 );
		m_smpStageData->GetDataArray( &tmp.bSpiaFloor,	i + 7 );
		m_smpStageData->GetDataArray( &tmp.iSpiaWall,	i + 8 );
		m_smpStageData->GetDataArray( &tmp.bCover,		i + 9 );
		m_smpStageData->GetDataArray( &tmp.bGoal,		i + 10 );
		m_smpStageData->GetDataArray( &tmp.bTest,		i + 11 );

		m_vStageDataPatarnSet.push_back( tmp );
	}
}

void clsMain::StageModelSet()
{
	//Csv�̃f�[�^�Ǎ�.
	m_smpStageData->Read();

	//���\�[�X�X�e�[�W.
	m_iStageDataMax = m_smpStageData->GetDataArrayNumMax()/STAGEPATARUNSETMAX;
	m_iStageDataMaxMax = m_iStageDataMax;

	m_smpStageDataExcelStageMax->Read();

	//csv����̃f�[�^���\���̂�.
	StageSet();

	//�p�[�c�̔ԍ��U��p.
	int StageWallNum             = 0;
	int StageFloorNum            = 0;
	int StageEnemyNum            = 0;
	int StageMoveFloorViticulNum = 0;
	int StageMoveFloorSideNum    = 0;
	int StageDoarNum             = 0;
	int StagePendNum             = 0;
	int StageSpearFloorNum       = 0;
	int StageSpearWallNum        = 0;
	int StageCoverNum            = 0;
	int StageGoalNum             = 0;
	int	CeilingNum	             = 0;
	int	StageTestStNum           = 0;
	int	StageTestSkNum           = 0;

#ifdef Tahara
	bool bCilBig = true;
#endif//#ifdef Tahara

	StageDetatchModelSet();


	//�X�e�[�W���߲���̔z������.
	for( int StageNum = 0; StageNum < m_iStageDataMaxMax; StageNum++ )
	{
		//�K��̃X�e�[�W�ł̃|�W�Ƒ傫��.
		D3DXVECTOR3 SetPos( 0.0f, 0.0f, 1.0f+( StageNum * 1.0f ) );
		float SetScale = 1.0f;

		//�����̍쐬.
		m_vsmpCeiling.push_back( make_unique<clsCharaStatic>() );
		//�����ް��֘A�t���̓}�l�[�W���[���ł��̂Ńt���E��.
		m_vsmpCeiling[CeilingNum]->AttachModel( m_pResource->GetStaticModels( m_pResource->enST_MODEL_CEILING ) );
		m_vsmpCeiling[CeilingNum]->SetPosition( SetPos );
		m_vsmpCeiling[CeilingNum]->AddPositionY( 7.0f );	//�ǂƍ��킹�邽��.
		m_vsmpCeiling[CeilingNum]->SetScale( SetScale );
		CeilingNum++;

		//���Ƃ����̊W�̍쐬.
		if ( m_vStageDataPatarnSet[StageNum].bCover)
		{
			m_vsmpCoverMgr.push_back( make_unique<clsCoverMgr>() );
			m_vsmpCoverMgr[StageCoverNum]->CreateCover( m_hWnd, StageCoverNum );
			//�����ް��֘A�t���̓}�l�[�W���[���ł��̂Ńt���E��.
			m_vsmpCoverMgr[StageCoverNum]->SetPosition(SetPos);
			m_vsmpCoverMgr[StageCoverNum]->SetScale(SetScale);
			m_vsmpCoverMgr[StageCoverNum]->Init();
			StageCoverNum++;
		}

		//�G�쐬.
		if ( m_vStageDataPatarnSet[StageNum].iEnemy > 0)
		{
			m_vsmpEnemyMgr.push_back( make_unique<clsEnemyMgr>() );
			m_vsmpEnemyMgr[StageEnemyNum]->CreateEnemy( m_hWnd, m_pDevice, m_pDeviceContext,
				m_vStageDataPatarnSet[StageNum].iEnemy, StageEnemyNum );
			//�����ް��֘A�t���̓}�l�[�W���[���ł��̂Ńt���E��.
			m_vsmpEnemyMgr[StageEnemyNum]->SetPosition( SetPos );
			m_vsmpEnemyMgr[StageEnemyNum]->SetScale( SetScale );
			StageEnemyNum++;
		}

		//�c�ړ��̊ۏ��쐬.
		if ( m_vStageDataPatarnSet[StageNum].iStepCil != 0)
		{
			{
#ifdef Tahara
				//�����̏������p.
				bool bInitCil = true;
				if( m_vStageDataPatarnSet[StageNum].iStepCil < 0 ){
					bInitCil = false;
					m_vStageDataPatarnSet[StageNum].iStepCil *= -1;//�t�����̏؂̃}�C�i�X�͂����ŊO��.
				}
#endif//#ifdef Tahara
				m_vsmpStepCil.push_back( make_unique<clsStepCyl>() );
				m_vsmpStepCil[StageMoveFloorViticulNum]->SetPosition( SetPos );
#ifdef Tahara
				if( bCilBig ){
					m_vsmpStepCil[StageMoveFloorViticulNum]->AttachModel( m_pResource->GetStaticModels( m_pResource->enST_MODEL_STEP_CIL_BIG ) );
					bCilBig = false;
				}
				else{
					m_vsmpStepCil[StageMoveFloorViticulNum]->AttachModel( m_pResource->GetStaticModels( m_pResource->enST_MODEL_STEP_CIL ) );
				}
#else
				m_vsmpStepCil[StageMoveFloorViticulNum]->AttachModel( m_pResource->GetStaticModels( m_pResource->enST_MODEL_STEP_CIL ) );
#endif//#ifdef Tahara
				m_vsmpStepCil[StageMoveFloorViticulNum]->SetPositionX( (float)m_vStageDataPatarnSet[StageNum].iStepCil - fSTAGE_WIDHT / 2.0f );
				m_vsmpStepCil[StageMoveFloorViticulNum]->SetScale( SetScale );
				m_vsmpStepCil[StageMoveFloorViticulNum]->CreateMove( bInitCil );
				StageMoveFloorViticulNum++;
			}
		}
		if (m_vStageDataPatarnSet[StageNum].iWall > 0)
		{
			m_vsmpWall.push_back( make_unique<clsWall>() );
			int ResauseModelNum;
			ResauseModelNum = m_vStageDataPatarnSet[StageNum].iWall;
			ResauseModelNum = ResauseModelNum + iWallModelNumZero;
			//�����ް��֘A�t��.
			m_vsmpWall[StageWallNum]->AttachModel(m_pResource->GetStaticModels(m_pResource->ItoE(ResauseModelNum)));
			m_vsmpWall[StageWallNum]->SetPosition(SetPos);
			m_vsmpWall[StageWallNum]->SetScale(SetScale);
			StageWallNum++;
		}

		//���쐬.
		if (m_vStageDataPatarnSet[StageNum].iFloor > 0)//csv����`.
		{
			m_vsmpFloor.push_back( make_unique<clsFloor>() );
			int ResauseModelNum;
			ResauseModelNum = m_vStageDataPatarnSet[StageNum].iFloor;
			ResauseModelNum = ResauseModelNum + iFloorModelNumZero;
			//�����ް��֘A�t��.
			m_vsmpFloor[StageFloorNum]->AttachModel(m_pResource->GetStaticModels(m_pResource->ItoE(ResauseModelNum)));
			m_vsmpFloor[StageFloorNum]->SetPosition(SetPos);
			m_vsmpFloor[StageFloorNum]->SetScale(SetScale);
			StageFloorNum++;
		}

		//���ړ��̎l�p���쐬.
		if ( m_vStageDataPatarnSet[StageNum].iStepBox > 0 )
		{
			//�E�������A��������.
			bool bRight = false;
			bool bEast = false;
			//2���傫���Ȃ�Ȃ獶.
			if( m_vStageDataPatarnSet[StageNum].iStepBox > 2 ){
				bRight = true;
			}
			//��Ȃ�.//����.
			if( m_vStageDataPatarnSet[StageNum].iStepBox % 2 ){
				bEast = true;
			}
			m_vsmpStepBox.push_back( make_unique<clsStepBox>() );
			m_vsmpStepBox[StageMoveFloorSideNum]->SetPosition( SetPos );
			m_vsmpStepBox[StageMoveFloorSideNum]->AttachModel( m_pResource->GetStaticModels( m_pResource->enST_MODEL_STEP_BOX ) );
			m_vsmpStepBox[StageMoveFloorSideNum]->CreateMove( bRight, bEast );
			m_vsmpStepBox[StageMoveFloorSideNum]->SetScale( SetScale );
			StageMoveFloorSideNum++;
		}

		//�h�A�̍쐬.
		if ( m_vStageDataPatarnSet[StageNum].bDoor )
		{
			m_vsmpDoorMgr.push_back( make_unique<clsDoorMgr>() );
			m_vsmpDoorMgr[StageDoarNum]->Create( m_hWnd, m_pDevice, m_pDeviceContext, StageDoarNum );
			//�����ް��֘A�t���̓}�l�[�W���[���ł��̂Ńt���E��.
			m_vsmpDoorMgr[StageDoarNum]->SetPosition( SetPos );
			m_vsmpDoorMgr[StageDoarNum]->SetScale( SetScale );
			StageDoarNum++;
			continue;
		}

		//�y���f�������̍쐬.
		if ( m_vStageDataPatarnSet[StageNum].iPend > 0 )
		{
			m_vsmpPend.push_back( make_unique<clsPend>() );
			m_vsmpPend[StagePendNum]->Create( m_hWnd, StagePendNum, m_vStageDataPatarnSet[StageNum].iPend );
			m_vsmpPend[StagePendNum]->AttachModel( m_pResource->GetSkinModels( m_pResource->enSK_MODEL_PENDULUM ) );
			m_vsmpPend[StagePendNum]->Init();
			m_vsmpPend[StagePendNum]->SetPosition( SetPos );
			m_vsmpPend[StagePendNum]->SetPositionY( PENDPOSY );
			m_vsmpPend[StagePendNum]->SetScale( SetScale );
			StagePendNum++;
			continue;
		}

		//�����̍쐬.
		if ( m_vStageDataPatarnSet[StageNum].bSpiaFloor )
		{
			m_vsmpSpiaFloorMgr.push_back( make_unique<clsSpiaFlorMgr>() );
			m_vsmpSpiaFloorMgr[StageSpearFloorNum]->CreateSpia( m_hWnd, StageSpearFloorNum );
			//�����ް��֘A�t���̓}�l�[�W���[���ł��̂Ńt���E��.
			m_vsmpSpiaFloorMgr[StageSpearFloorNum]->SetPosition( SetPos );
			m_vsmpSpiaFloorMgr[StageSpearFloorNum]->SetScale( SetScale );
			StageSpearFloorNum++;
			continue;
		}

		//���ǂ̍쐬.
		if ( m_vStageDataPatarnSet[StageNum].iSpiaWall )
		{
			m_vsmpSpiaWallMgr.push_back( make_unique<clsSpiaWallMgr>() );
			m_vsmpSpiaWallMgr[StageSpearWallNum]->CreateSpia( m_hWnd, StageSpearWallNum, m_vStageDataPatarnSet[StageNum].iSpiaWall );
			//�����ް��֘A�t���̓}�l�[�W���[���ł��̂Ńt���E��.
			m_vsmpSpiaWallMgr[StageSpearWallNum]->SetPosition( SetPos );
			m_vsmpSpiaWallMgr[StageSpearWallNum]->SetScale( SetScale );
			StageSpearWallNum++;
			continue;
		}


		//�S�[���̍쐬.
		if ( m_vStageDataPatarnSet[StageNum].bGoal )
		{
			m_vsmpGoalMgr.push_back( make_unique<clsGoalMgr>() );
			//�����ް��֘A�t���̓}�l�[�W���[���ł��̂Ńt���E��.
			m_vsmpGoalMgr[StageGoalNum]->Create( m_hWnd, m_pDevice, m_pDeviceContext );
			m_vsmpGoalMgr[StageGoalNum]->SetPosition( SetPos );
			m_vsmpGoalMgr[StageGoalNum]->SetScale( SetScale );
			StageGoalNum++;
			continue;
		}

		//�e�X�g���f���p.
		if ( m_vStageDataPatarnSet[StageNum].bTest )
		{
			m_vsmpTest.push_back( make_unique<clsCharaStatic>() );
			m_vsmpTest[StageTestStNum]->AttachModel( m_pResource->GetStaticModels( m_pResource->enST_MODEL_TEST ) );
			m_vsmpTest[StageTestStNum]->SetPosition( SetPos );
			m_vsmpTest[StageTestStNum]->SetScale( SetScale );
			StageTestStNum++;
		}
	}
}


void clsMain::StageDetatchModelSet()
{
	//�ǕR�Â�����.
	if(!m_vsmpWall.empty())
	{
		for ( int i = 0; i < m_vsmpWall.size(); i++ )
		{
			m_vsmpWall[i]->DetatchModel();
		}
		m_vsmpWall.clear();
		m_vsmpWall.shrink_to_fit();
	}
	//���R�Â�����.
	if(!m_vsmpFloor.empty())
	{
		for ( int i = 0; i<m_vsmpFloor.size(); i++ )
		{
			m_vsmpFloor[i]->DetatchModel();
		}
		m_vsmpFloor.clear();
		m_vsmpFloor.shrink_to_fit();
	}
	//�G�R�Â�����.
	if(!m_vsmpEnemyMgr.empty())
	{
		for ( int i = 0; i< m_vsmpEnemyMgr.size(); i++ )
		{
			m_vsmpEnemyMgr[i]->DetatchModel();
		}
		m_vsmpEnemyMgr.clear();
		m_vsmpEnemyMgr.shrink_to_fit();
	}
	//�ړ����ەR�Â�����.
	if(!m_vsmpStepCil.empty())
	{
		for ( int i = 0; i<m_vsmpStepCil.size(); i++ )
		{
			m_vsmpStepCil[i]->DetatchModel();
		}
		m_vsmpStepCil.clear();
		m_vsmpStepCil.shrink_to_fit();
	}
	//�ړ����l�p�R�Â�����.
	if(!m_vsmpStepBox.empty())
	{
		for (int i = 0; i< m_vsmpStepBox.size(); i++)
		{
			m_vsmpStepBox[i]->DetatchModel();
		}
		m_vsmpStepBox.clear();
		m_vsmpStepBox.shrink_to_fit();
	}
	//�y���f�������R�Â�����.
	if(!m_vsmpPend.empty())
	{
		for (int i = 0; i < m_vsmpPend.size(); i++ )
		{
			m_vsmpPend[i]->DetatchModel();
		}
		m_vsmpPend.clear();
		m_vsmpPend.shrink_to_fit();
	}
	//�h�A�R�Â�����.
	if(!m_vsmpDoorMgr.empty())
	{
		for (int i = 0; i < m_vsmpDoorMgr.size(); i++ )
		{
			m_vsmpDoorMgr[i]->DetatchModel();
		}
		m_vsmpDoorMgr.clear();
		m_vsmpDoorMgr.shrink_to_fit();
	}
	//�����R�Â�����.
	if(!m_vsmpSpiaFloorMgr.empty())
	{
		for (int i = 0; i < m_vsmpSpiaFloorMgr.size(); i++ )
		{
			m_vsmpSpiaFloorMgr[i]->DetatchModel();
		}
		m_vsmpSpiaFloorMgr.clear();
		m_vsmpTest.shrink_to_fit();
	}
	//�Ǒ��R�Â�����.
	if(!m_vsmpSpiaWallMgr.empty())
	{
		for (int i = 0; i < m_vsmpSpiaWallMgr.size(); i++ )
		{
			m_vsmpSpiaWallMgr[i]->DetatchModel();
		}
		m_vsmpSpiaWallMgr.clear();
		m_vsmpSpiaWallMgr.shrink_to_fit();
	}
	//���Ƃ����̊W�R�Â�����.
	if(!m_vsmpCoverMgr.empty())
	{
		for (int i = 0; i < m_vsmpCoverMgr.size(); i++ )
		{
			m_vsmpCoverMgr[i]->DetatchModel();
		}
		m_vsmpCoverMgr.clear();
		m_vsmpTest.shrink_to_fit();
	}
	//�S�[���R�Â�����.
	if(!m_vsmpGoalMgr.empty())
	{
		for (int i = 0; i < m_vsmpGoalMgr.size(); i++ )
		{
			m_vsmpGoalMgr[i]->DetatchModel();
		}
		m_vsmpGoalMgr.clear();
		m_vsmpTest.shrink_to_fit();
	}

	//�����R�Â�����.
	if(!m_vsmpCeiling.empty())
	{
		for (int i = 0; i < m_vsmpCeiling.size(); i++ )
		{
			m_vsmpCeiling[i]->DetatchModel();
		}
		m_vsmpCeiling.clear();
		m_vsmpTest.shrink_to_fit();
	}

	//���f���e�X�g�R�Â�����.
	if(!m_vsmpTest.empty())
	{
		for ( int i=0; i<m_vsmpTest.size(); i++ )
		{
			m_vsmpTest[i]->DetatchModel();
		}
		m_vsmpTest.clear();
		m_vsmpTest.shrink_to_fit();
	}

}

void clsMain::StageModelSetErrMsg( int StageNum, const char* ERR_MSG )
{
	string ErrMsg;
	stringstream ss;	//�ϊ��p.
	ErrMsg = ERR_MSG ;
	ErrMsg += "\n";
	ss << StageNum+1;
	ErrMsg += ss.str();
	ErrMsg += "�s��";
	ERR_MSG( ErrMsg.c_str(), "Csv�̔z�u�G���[" );
	ss.str( "" ); // �o�b�t�@���N���A����.
	ss.clear( stringstream::goodbit );// �X�g���[���̏�Ԃ��N���A����B���̍s���Ȃ��ƈӐ}�ʂ�ɓ��삵�Ȃ�.
}

void clsMain::SceneTitle()
{
	//�J�����̍ŏI�n�_.
	const D3DXVECTOR3 vCAM_GO_MAIN_TARGET = m_pPlayer->GetPosition() + vCAMERA_INIT_OFFSET;
	const float fLOOK_GO_MAIN_TARGET_Y = 3.0625f;
	const D3DXVECTOR3 vLOOK_GO_MAIN_TARGET = {  vCAM_GO_MAIN_TARGET.x,
												fLOOK_GO_MAIN_TARGET_Y,
												vCAM_GO_MAIN_TARGET.z + fLOOK_OFFSET_Z };

	//���[�v.
	if( m_pBgm[enBGM_TITLE]->IsStopped() ){
		m_pBgm[enBGM_TITLE]->SeekToStart();
		m_pBgm[enBGM_TITLE]->Play( true );
	}


	bool bPushEnter = false;
	if( m_pXInput->IsPressEnter( XINPUT_A ) )bPushEnter = true;
	GETKEY_DOWN( 'Z' ) bPushEnter = true;
	GETKEY_DOWN( 'A' ) bPushEnter = true;

	//���[�h.
	switch( m_enTitleSceneMode )
	{
	case en_TSM_IDLE:
		//�Ó]���ł͂Ȃ�.
		if( m_smpUiManagar->GetBlackIdle() ){
			//�j��J�n.
			if( bPushEnter ){
				m_enTitleSceneMode = en_TSM_BREAK_DOOR;
				m_pSe[enSe_EXIT]->SeekPlay();
			}
		}
		break;

	case en_TSM_BREAK_DOOR:
		{
			//�J�����ǂ�������.
			if( Stoker( m_Camera.vEye, vCAM_GO_MAIN_TARGET ) &&
				Stoker( m_Camera.vLook, vLOOK_GO_MAIN_TARGET ) )
			{
				//�ǂ������I�������.
				m_enTitleSceneMode = en_TSM_GO_MAIN;
			}
			//�^�C�g���̓���������.
			m_pPlayer->MoveTitleScene();

			//�h�A�R�j��.
			if( m_pPlayer->GetAttackImpact() ){
				//���ĂȂ��Ƃ�.
				if( !m_vsmpDoorMgr[0]->GetDoorBroken() ){
					//�^�C�g������.
					m_smpUiManagar->SetTitleTransFlg( true );
					//�L�b�N�͈̔�.
					if( m_pCollision->HitSect(
						m_pPlayer->GetPointerSubCol(),
						m_vsmpDoorMgr[0]->GetDoorHitColPointer() ) )
					{
						//���C���̏�̃e�L�X�g�����ɗ��Ƃ�.
						m_smpUiManagar->TopMainTxtMoveStart();
						//�h�A�̔j��ƕ����ʒu�X�V.
						m_pPlayer->UpdateReSpawnPos( m_vsmpDoorMgr[0]->DoorBreak() );
						//�G�t�F�N�g�̓A���r�A�ƃh�A�̒��Ԓn�_( �R�����ꏊ )�ɏo��.
						PlayEffKick( GetMidWay( m_pPlayer->GetPosition(), m_vsmpDoorMgr[0]->GetPosition() ) );
						//�U��.
						m_pXInput->SetVibPowerL( usVIB_DOOR_POWER, iVIB_DOOR_TIME );
						m_pXInput->SetVibPowerR( usVIB_DOOR_POWER, iVIB_DOOR_TIME );
						break;
					}
				}
			}
			//��.
			bool bGroundFlg = false;
			m_vsmpDoorMgr[0]->Update( m_pPlayer->GetPositionZ() );
			for( int i=0; i<m_vsmpFloor.size(); i++ ){
				if( isCutOutForHit( m_pPlayer->GetPositionZ(), m_vsmpFloor[i]->GetPositionZ() ) ){
					if( m_pCollision->FloorJudge(
						m_pPlayer, m_pPlayer->GetColToFloorRange(), m_pPlayer->m_fFloorY,
						m_vsmpFloor[i].get(),
						bGroundFlg ) )
					{
						//break���Ȃ��ƕʂ̏��̏��ɏ㏑�������.
						break;
					}
				}
			}
			m_pPlayer->SetGroundFlg( bGroundFlg );
		}
		break;

	case en_TSM_GO_MAIN:
		//���C����.
		InitMain( true );
		m_enTitleSceneMode = en_TSM_IDLE;
		break;

	default:
		m_enTitleSceneMode = en_TSM_GO_MAIN;
		break;
	}


}

void clsMain::SceneMain()
{
	//���[�v.
	if( m_pBgm[enBGM_MAIN]->IsStopped() ){
		m_pBgm[enBGM_MAIN]->SeekToStart();
		m_pBgm[enBGM_MAIN]->Play( true );
	}

	//----- ���@ -----//.
	m_pPlayer->Input();

	m_pPlayer->Update( GetEar() );

	//��O�K�[�h.
	if( m_pPlayer->GetPositionZ() < fPLAYER_BACK_LIMIT ){
		m_pPlayer->SetPositionZ( fPLAYER_BACK_LIMIT );
	}
	//��.
	if( m_pPlayer->GetPositionX() > fWALL_HIT_RANGE ){
		m_pPlayer->SetPositionX( fWALL_HIT_RANGE );
	}
	else if( m_pPlayer->GetPositionX() < -fWALL_HIT_RANGE ){
		m_pPlayer->SetPositionX( -fWALL_HIT_RANGE );
	}


	//----- ��� -----//.
	CameraMgr();

	//----- ���̈ʒu -----//.
	SetEar( m_pPlayer->GetPositionZ(), m_Camera.vEye.z );


	//----- �G -----//.
	for( int i=0; i<m_vsmpEnemyMgr.size(); i++ ){
		//����.
		m_vsmpEnemyMgr[i]->Update( GetEar() );

		if( isCutOutForHit( m_pPlayer->GetPositionZ(), m_vsmpEnemyMgr[i]->GetPositionZ() ) ){
			//��ڲ԰��Pos�����ޯĂɾ��.
			m_vsmpEnemyMgr[i]->GetSarchTarget( m_pPlayer->GetPosition() );

			//�G�̂����蔻��.
			for( int j=0; j<m_vsmpEnemyMgr[i]->GetEnemyMax(); j++ )
			{
				//�G������Ă����画�肵�Ȃ�.
				if( m_vsmpEnemyMgr[i]->GetEnemyMove( j ) != clsEnemy::enEM_DEATH ){
					//���@�������Ă�Ƃ�.
					if( !m_pPlayer->GetDead() ){
						//===== ���ł������Ă��邠���蔻�� =====//.
						//���@����G�ւ̍U��.
						//�U����.
						if( m_pPlayer->GetAttackImpact() ){
							//�����Ɨ��Ƃ���.
							if( m_pPlayer->isJumpAtk() ){
								//�~����.
								if( m_pPlayer->GetJumpAtkImpact() ){
									//�L�b�N�͈̔�.
									if( m_pCollision->HitCylind(
										m_pPlayer->GetPointerSubCol(),
										m_vsmpEnemyMgr[i]->GetPointerEnemyCol( j ) ) )
									{
										m_vsmpEnemyMgr[i]->Dead( j );
										m_pCollision->PlaySe( clsCollision::enSOUND_ARBIA_KICK );
										m_pXInput->SetVibPowerR( usVIB_KICK_POWER, iVIB_KICK_TIME );
										//�G�̏ꏊ�ɃG�t�F�N�g�o��.
										PlayEffKick( m_vsmpEnemyMgr[i]->GetEnemyPos( j ) );
										break;
									}
								}
							}
							//�ʏ�L�b�N.
							else{
								//�L�b�N�͈̔͂ɓG������.
								if( m_pCollision->HitSect(
									m_pPlayer->GetPointerSubCol(),
									m_vsmpEnemyMgr[i]->GetPointerEnemyCol( j ) ) )
								{
									m_vsmpEnemyMgr[i]->Dead( j );
									m_pCollision->PlaySe( clsCollision::enSOUND_ARBIA_KICK );
									m_pXInput->SetVibPowerR( usVIB_KICK_POWER, iVIB_KICK_TIME );
									PlayEffKick( m_vsmpEnemyMgr[i]->GetEnemyPos( j ) );
									break;
								}
							}
							//�G�ɐڐG�œG������.
							if( m_pCollision->HitCylind(
								m_pPlayer->GetPointerCol(),
								m_vsmpEnemyMgr[i]->GetPointerEnemyCol( j ) ) )
							{
								m_vsmpEnemyMgr[i]->Dead( j );
								m_pCollision->PlaySe( clsCollision::enSOUND_ARBIA_KICK );
								m_pXInput->SetVibPowerR( usVIB_KICK_POWER, iVIB_KICK_TIME );
								PlayEffKick( m_vsmpEnemyMgr[i]->GetEnemyPos( j ) );
								break;
							}
						}
						//���@���U�����ȊO.
						else{
							//�G�ɐڐG�Ŏ��@������.
							if( m_pCollision->HitCylind(
								m_pPlayer->GetPointerCol(),
								m_vsmpEnemyMgr[i]->GetPointerEnemyCol( j ) ) )
							{
								m_pPlayer->Dead();
								m_vsmpEnemyMgr[i]->Lost( j );
								PlayEffSlash( m_pPlayer->GetPosition() );
								m_pCollision->PlaySe( clsCollision::enSOUND_ENEMY );
								break;
							}
						}


						//===== ���[�h�ʂ����蔻�� =====//.
						switch( m_vsmpEnemyMgr[i]->GetEnemyMove( j ) )
						{
						case clsEnemy::enEM_WALK:
							//���@����.
							//�͈͓�.
							if( m_pCollision->HitSect(
								m_vsmpEnemyMgr[i]->GetPointerEnemySubCol( j ),
								m_pPlayer->GetPointerCol() ) )
							{
								//�G����������ԂŌ���������.
								if( m_vsmpEnemyMgr[i]->Discover( j ) ){
									//�������X�V.
									m_ResUiState.iDisc ++;
									m_smpUiManagar->SetDisc( m_ResUiState.iDisc );
								}
							}
							break;
						case clsEnemy::enEM_RUN:
							//�U���J�n�͈�.
							if( m_pCollision->HitSect(
								m_vsmpEnemyMgr[i]->GetPointerEnemySubCol( j ),
								m_pPlayer->GetPointerCol() ) )
							{
								m_vsmpEnemyMgr[i]->Attack( j );
							}
							break;
						case clsEnemy::enEM_ATK:
							//�U���̃C���p�N�g(����̂��鎞�Ԃ�?).
							if( m_vsmpEnemyMgr[i]->GetAttackImpact( j ) ){
								//�U���͈�.
								if( m_pCollision->HitSect(
									m_vsmpEnemyMgr[i]->GetPointerEnemySubCol( j ),
									m_pPlayer->GetPointerCol() ) )
								{
									m_pPlayer->Dead();
									m_vsmpEnemyMgr[i]->Win( j );
									m_pCollision->PlaySe( clsCollision::enSOUND_ENEMY_SRASH );
									//�G�t�F�N�g.
									PlayEffSlash( m_pPlayer->GetPosition() );
								}
							}
							break;
						}
					}
				}
			}
		}
	}
	//----- �G �I��� -----//.




	//----- ���� -----//.
	for( int i=0; i<m_vsmpSpiaFloorMgr.size(); i++ ){
		//����.
		m_vsmpSpiaFloorMgr[i]->Update( GetEar() );

		if( isCutOutForHit( m_pPlayer->GetPositionZ(), m_vsmpSpiaFloorMgr[i]->GetPositionZ(), fONE_BROCK_HIT_AREA, fONE_BROCK_HIT_AREA ) ){
			//�����Ă�Ƃ�.
			if( !m_pPlayer->GetDead() ){
				//���Ƃ̂����蔻��.
				for( int j=0; j<m_vsmpSpiaFloorMgr[i]->GetSpiaMax(); j++ )
				{
					if( m_pCollision->HitCylind(
						m_vsmpSpiaFloorMgr[i]->GetPointerSpiaCol( j ),
						m_pPlayer->GetPointerCol() ) )
					{
						m_pPlayer->Dead();
						m_pCollision->PlaySe( clsCollision::enSOUND_SPIA );
						//�G�t�F�N�g.
						PlayEffSlash( m_pPlayer->GetPosition() );
						break;
					}
				}
			}
			//���@�Ƒ��ǂ̂����蔻��.
			m_pCollision->WallJudge( m_pPlayer, m_vsmpSpiaFloorMgr[i]->GetWallPointer() );
		}
	}


	//----- �Ǒ� -----//.
	for ( int i=0; i<m_vsmpSpiaWallMgr.size(); i++ ){
		//����.
		m_vsmpSpiaWallMgr[i]->Update( GetEar() );

		if( isCutOutForHit( m_pPlayer->GetPositionZ(), m_vsmpSpiaWallMgr[i]->GetPositionZ(), fONE_BROCK_HIT_AREA, fONE_BROCK_HIT_AREA ) ){
			//�����Ă�Ƃ�.
			if( !m_pPlayer->GetDead() ){
				//���Ƃ̂����蔻��.
				for( int j=0; j<m_vsmpSpiaWallMgr[i]->GetSpiaMax(); j++ )
				{
					//����.
					if( m_pCollision->HitBox(
						m_vsmpSpiaWallMgr[i]->GetPointerSpiaCol( false, j ),
						m_pPlayer->GetPointerCol() ) )
					{
						m_pPlayer->Dead();
						m_pCollision->PlaySe( clsCollision::enSOUND_SPIA );
						//�G�t�F�N�g.
						PlayEffSlash( m_pPlayer->GetPosition() );
						break;
					}
					//�E��.
					if( m_pCollision->HitBox(
						m_vsmpSpiaWallMgr[i]->GetPointerSpiaCol( true, j ),
						m_pPlayer->GetPointerCol() ) )
					{
						m_pPlayer->Dead();
						m_pCollision->PlaySe( clsCollision::enSOUND_SPIA );
						//�G�t�F�N�g.
						PlayEffSlash( m_pPlayer->GetPosition() );
						break;
					}
				}
			}

			//��.
			m_pCollision->WallJudge( m_pPlayer, m_vsmpSpiaWallMgr[i]->GetWallLCol() );
			m_pCollision->WallJudge( m_pPlayer, m_vsmpSpiaWallMgr[i]->GetWallRCol() );
		}
	}

	//----- �U��q -----//.
	char* cPendBoneName = (char*)PEND_BONE_NAME;//�ްݖ�.
	for( int i=0; i<m_vsmpPend.size(); i++ ){
		//�U��q����.
		m_vsmpPend[i]->Update( GetEar() );
		//���ߊ�ݒ�.
		m_vsmpPend[i]->SetAlphaFlg( m_pPlayer->GetPositionZ() );

		//�U��q�̂����蔻��.
		if( isCutOutForHit( m_pPlayer->GetPositionZ(), m_vsmpPend[i]->GetPositionZ(), fONE_BROCK_HIT_AREA, fONE_BROCK_HIT_AREA ) ){
			//���W��Ă����ް�ł���Ă���i1�ڰђx��邯�ǋ����Ăˁj.
			if( !m_pPlayer->GetDead() ){
				//˯�.
				if( m_pCollision->HitBox(
					m_vsmpPend[i]->GetPointerCol(),
					m_pPlayer->GetPointerCol() ) )
				{
					m_pPlayer->Dead();
					m_pCollision->PlaySe( clsCollision::enSOUND_PEND );
					//�G�t�F�N�g.
					PlayEffSlash( m_pPlayer->GetPosition() );
					break;
				}
			}
		}
	}




	//========== �n�`�Ƃ̂����蔻�� ==========//.

//	//----- ���@�ƕǂ̕ǂ����蔻�� -----//.
//	for( int i=0; i<m_vpWall.size(); i++ ){
//		if( isCutOutForHit( m_pPlayer->GetPositionZ(), m_vpWall[i]->GetPositionZ() ) ){
//			m_pCollision->WallJudge( m_pPlayer, m_vpWall[i] );
//		}
//	}
	//----- ���@�Ə��Ƃ̕ǂ����蔻�� -----//.
	for( int i=0; i<m_vsmpFloor.size(); i++ ){
		if( isCutOutForHit( m_pPlayer->GetPositionZ(), m_vsmpFloor[i]->GetPositionZ(), fONE_BROCK_HIT_AREA, fONE_BROCK_HIT_AREA ) ){
			m_pCollision->WallJudge( m_pPlayer, m_vsmpFloor[i].get() );
		}
	}
	//----- ���@�Ɗۑ���̕ǂ����蔻�� -----//.
	for( int i=0; i<m_vsmpStepCil.size(); i++ ){
		if( isCutOutForHit( m_pPlayer->GetPositionZ(), m_vsmpStepCil[i]->GetPositionZ() ) ){
			m_pCollision->WallJudge( m_pPlayer, m_vsmpStepCil[i].get() );
		}
	}
	//----- ���@�Ǝl�p����̕ǂ����蔻�� -----//.
	for( int i=0; i<m_vsmpStepBox.size(); i++ ){
		if( isCutOutForHit( m_pPlayer->GetPositionZ(), m_vsmpStepBox[i]->GetPositionZ(), fONE_BROCK_HIT_AREA, fONE_BROCK_HIT_AREA ) ){
			m_pCollision->WallJudge( m_pPlayer, m_vsmpStepBox[i].get() );
		}
	}
	//----- �S�[���̕ǂ����蔻��Ɠ��� -----//.
	for( int i=0; i<m_vsmpGoalMgr.size(); i++ ){
		if( /*isCutOutForHit( m_pPlayer->GetPositionZ(), m_vsmpGoalMgr[i]->GetPositionZ(), fONE_BROCK_HIT_AREA, fGOAL_TREASURE_HIT_AREA )*/ 1 ){
			m_pCollision->WallJudge( m_pPlayer, m_vsmpGoalMgr[i]->GetFloorColPointer() );
			m_pCollision->WallJudge( m_pPlayer, m_vsmpGoalMgr[i]->GetTrBoxColPointer() );
			//�R�j���.
			if( m_pPlayer->GetAttackImpact() ){
				//���ĂȂ��Ƃ�.
				if( !m_vsmpGoalMgr[i]->GetBoxOpened() ){
					//�L�b�N�͈̔�.
					if( m_pCollision->HitSect(
						m_pPlayer->GetPointerSubCol(),
						m_vsmpGoalMgr[i]->GetBoxHitColPointer() ) )
					{
						//�����J����.
						m_vsmpGoalMgr[i]->BoxBreak();

						m_pXInput->SetVibPowerL( usVIB_DOOR_POWER, iVIB_DOOR_TIME );
						m_pXInput->SetVibPowerR( usVIB_DOOR_POWER, iVIB_DOOR_TIME );
						break;
					}
				}
			}
			m_vsmpGoalMgr[i]->Update( GetEar() );
		}
	}


	//----- ���@�Ɩ�Ƃ̕ǂ����蔻��Ɠ��� -----//.
	for( int i=0; i<m_vsmpDoorMgr.size(); i++ ){
		//���ĂȂ��Ƃ�.
		if( !m_vsmpDoorMgr[i]->GetDoorBroken() ){
			if( isCutOutForHit( m_pPlayer->GetPositionZ(), m_vsmpDoorMgr[i]->GetPositionZ() ) ){
				//���̕ǔ���.
				m_pCollision->WallJudge( m_pPlayer, m_vsmpDoorMgr[i]->GetWallColPointer() );
				//�R�j���.
				if( m_pPlayer->GetAttackImpact() ){
					//�����Ɨ��Ƃ���.
					if( m_pPlayer->isJumpAtk() ){
						//�~����.
						if( m_pPlayer->GetJumpAtkImpact() ){
							//�L�b�N�͈̔�.
							if( m_pCollision->HitSect(
								m_pPlayer->GetPointerSubCol(),
								m_vsmpDoorMgr[i]->GetDoorHitColPointer() ) )
							{
								//�h�A�̔j��ƕ����ʒu�X�V.
								m_pPlayer->UpdateReSpawnPos( m_vsmpDoorMgr[i]->DoorBreak() );
								//�G�t�F�N�g�̓A���r�A�ƃh�A�̒��Ԓn�_( �R�����ꏊ )�ɏo��.
								PlayEffKick( GetMidWay( m_pPlayer->GetPosition(), m_vsmpDoorMgr[i]->GetPosition() ) );
								//�`�F�b�N�|�C���g����.
								if( m_pCheck != nullptr ){
									m_pCheck->Init();
									m_pCheck->Start( m_vsmpDoorMgr[i]->DoorBreak().z );
								}
								//�h�A��j���ĕ��m��|��.
								for( int j=0; j<m_vsmpEnemyMgr.size(); j++ ){
									//�h�A�Ŏ��ʐl.
									if( m_vsmpEnemyMgr[j]->GetDoorDeader() ){
										if( isCutOutForHit( m_vsmpEnemyMgr[j]->GetPositionZ(), m_vsmpDoorMgr[i]->GetPositionZ() ) ){
											m_vsmpEnemyMgr[j]->DoorTimerStart();
											m_pCollision->PlaySe( clsCollision::enSOUND_ARBIA_KICK );
											PlayEffKick( m_vsmpEnemyMgr[j]->GetEnemyPos( 0 ) );
										}
									}
								}
								m_pXInput->SetVibPowerL( usVIB_DOOR_POWER, iVIB_DOOR_TIME );
								m_pXInput->SetVibPowerR( usVIB_DOOR_POWER, iVIB_DOOR_TIME );
								break;
							}
						}
					}
					//�ʏ�U��.
					else{
						//�L�b�N�͈̔�.
						if( m_pCollision->HitSect(
							m_pPlayer->GetPointerSubCol(),
							m_vsmpDoorMgr[i]->GetDoorHitColPointer() ) )
						{
							//�h�A�̔j��ƕ����ʒu�X�V.
							m_pPlayer->UpdateReSpawnPos( m_vsmpDoorMgr[i]->DoorBreak() );
							//�G�t�F�N�g�̓A���r�A�ƃh�A�̒��Ԓn�_( �R�����ꏊ )�ɏo��.
							PlayEffKick( GetMidWay( m_pPlayer->GetPosition(), m_vsmpDoorMgr[i]->GetPosition() ) );
							//�`�F�b�N�|�C���g����.
							if( m_pCheck != nullptr ){
								m_pCheck->Init();
								m_pCheck->Start( m_vsmpDoorMgr[i]->DoorBreak().z );
							}
							//�h�A��j���ĕ��m��|��.
							for( int j=0; j<m_vsmpEnemyMgr.size(); j++ ){
								//�h�A�Ŏ��ʐl.
								if( m_vsmpEnemyMgr[j]->GetDoorDeader() ){
									if( isCutOutForHit( m_vsmpEnemyMgr[j]->GetPositionZ(), m_vsmpDoorMgr[i]->GetPositionZ() ) ){
										m_vsmpEnemyMgr[j]->DoorTimerStart();
										m_pCollision->PlaySe( clsCollision::enSOUND_ARBIA_KICK );
										PlayEffKick( m_vsmpEnemyMgr[j]->GetEnemyPos( 0 ) );
									}
								}
							}
							m_pXInput->SetVibPowerL( usVIB_DOOR_POWER, iVIB_DOOR_TIME );
							m_pXInput->SetVibPowerR( usVIB_DOOR_POWER, iVIB_DOOR_TIME );
							break;
						}
					}
				}
			}
		}
		//���Ă��鎞.
		else{
			if( isCutOutForHit( m_pPlayer->GetPositionZ(), m_vsmpDoorMgr[i]->GetPositionZ() ) ){
				//�ŏ��̖��������ƃ^�C�}�[�������o��.
				if( !i ){
					if( m_pPlayer->GetPositionZ() > m_vsmpDoorMgr[i]->GetPositionZ() ){
						m_smpUiManagar->SetTimerStop( false );
					}
				}
				//��߂̖��������ƃA�N�V������������������.
				else if( i == 1 ){
					if( m_pPlayer->GetPositionZ() > m_vsmpDoorMgr[i]->GetPositionZ() ){
						m_smpUiManagar->ActTxtOut();
					}
				}

				//�ǔ���.
				m_pCollision->WallJudge( m_pPlayer, m_vsmpDoorMgr[i]->GetGateColPointer() );
				//�V��ɓ���łƃv���C���[�̏㉺�ړ��ʔ��].
				if( m_pCollision->CeilingJudge(
					m_pPlayer,
					m_pPlayer->GetHeight(),
					m_vsmpDoorMgr[i]->GetGateColPointer() ) )
				{
					m_pPlayer->HeadHitToCeiling();
				}
			}
			//����.
			m_vsmpDoorMgr[i]->SetAlphaFlg( GetEar() );
			//����.
			m_vsmpDoorMgr[i]->Update( GetEar() );
		}
	}

	//�`�F�b�N�|�C���g����.
	if( m_pCheck != nullptr ){
		m_pCheck->Update();
	}



	//========== ���@�Ə��̂����蔻�� ==========//.
	m_pPlayer->m_fFloorY = 0.0f;//�n�ʂ̍���������.
	bool bGroundFlg = false;
	bool bCutGroundCheck = false;	//�n�ʂ̏�ɂ���Ȃ炻��ȏ�̃`�F�b�N�͂���Ȃ��̂ŁA���̂��߂̃t���O.
	m_pPlayer->SetGroundFlg( bGroundFlg );


	//----- ���Ƃ����̊W -----//.//���Ƃ����͍ŏ��ɔ��肵�Ȃ��ƃ_��.
	//���ɕ����Ă�Ƃ�.
	if( !bCutGroundCheck ){
		//���Ƃ����̐�����.
		for( int i=0; i<m_vsmpCoverMgr.size(); i++ ){
			//����.
			m_vsmpCoverMgr[i]->Update( GetEar() );
			if( isCutOutForHit( m_pPlayer->GetPositionZ(), m_vsmpCoverMgr[i]->GetPositionZ() ) ){
				//�J���Ă��鎞�͏��Ȃ�.
				if( m_vsmpCoverMgr[i]->isCanStmp() )
				{
					for( char j=0; j<m_vsmpCoverMgr[i]->GetCoverMax(); j++ ){
						if( m_pCollision->FloorJudge(
							m_pPlayer, m_pPlayer->GetColToFloorRange(), m_pPlayer->m_fFloorY,
							m_vsmpCoverMgr[i]->GetCoverPointer( j ),
							bGroundFlg ) )
						{
							//���n���̂�.
							if( bGroundFlg ){
								//�����Ɨ��Ƃ��ŏ��.
								if( m_pPlayer->isJumpAtk() ){
									//�}�ɊJ��.
									m_vsmpCoverMgr[i]->StmpCovorStrong( GetEar() );
								}
								//���ʂɏ��.
								else{
									//��������.
									m_vsmpCoverMgr[i]->StmpCovor( GetEar() );
									m_pXInput->SetVibPowerL( usVIB_COVER_POWER, iVIB_COVER_TIME, iVIB_COVER_DEC );
								}
							}
							bCutGroundCheck = true;
							//2�dfor���̒E�o�p�i���ꂪ����̂�break�͂���Ȃ��o ���ł͕��ʂ�break���Ă��闝�R�́A�ǐ�����������ł� �p�j.
							i = m_vsmpCoverMgr.size() - 1;
							j = m_vsmpCoverMgr[i]->GetCoverMax() - 1;
						}
					}
				}
			}
		}
		m_pPlayer->SetGroundFlg( bGroundFlg );
	}

	//----- ���ʏ� -----//.
	if( !bCutGroundCheck ){
		for( int i=0; i<m_vsmpFloor.size(); i++ ){
			if( isCutOutForHit( m_pPlayer->GetPositionZ(), m_vsmpFloor[i]->GetPositionZ(), fONE_BROCK_HIT_AREA, fONE_BROCK_HIT_AREA ) ){
				if( m_pCollision->FloorJudge(
					m_pPlayer, m_pPlayer->GetColToFloorRange(), m_pPlayer->m_fFloorY,
					m_vsmpFloor[i].get(),
					bGroundFlg ) )
				{
					bCutGroundCheck = true;
					//break���Ȃ��ƕʂ̏��̏��ɏ㏑�������.
					break;
				}
			}
		}
		m_pPlayer->SetGroundFlg( bGroundFlg );
	}

	//----- �����ۑ��� -----//.
	for( int i=0; i<m_vsmpStepCil.size(); i++ ){
		m_vsmpStepCil[i]->Update();	//�����͊O�ɏo���Ă����Ȃ���break�̂����ŏ���Ă��鑫��ȊO���~�܂��Ă��܂�.
	}
	if( !bCutGroundCheck ){
		for( int i=0; i<m_vsmpStepCil.size(); i++ ){
			if( isCutOutForHit( m_pPlayer->GetPositionZ(), m_vsmpStepCil[i]->GetPositionZ() ) ){
				if( m_pCollision->FloorJudge(
					m_pPlayer, m_pPlayer->GetColToFloorRange(), m_pPlayer->m_fFloorY,
					m_vsmpStepCil[i].get(),
					bGroundFlg ) )
				{
					bCutGroundCheck = true;
					//����Ă�����^��.
					if( bGroundFlg ){
						//����̈ړ��ʂ��X�V.
						m_pPlayer->AddPositionZ( m_vsmpStepCil[i]->GetCarryRangeZ() );
					}
					//break���Ȃ��ƕʂ̏��̏��ɏ㏑�������.
					break;
				}
			}
		}
		m_pPlayer->SetGroundFlg( bGroundFlg );
	}


	//----- �����l�p���� -----//.
	for( int i=0; i<m_vsmpStepBox.size(); i++ ){
		m_vsmpStepBox[i]->Update();	//�����͊O�ɏo���Ă����Ȃ���break�̂����ŏ���Ă��鑫��ȊO���~�܂��Ă��܂�.
	}
	if( !bCutGroundCheck ){
		for( int i=0; i<m_vsmpStepBox.size(); i++ ){
			if( isCutOutForHit( m_pPlayer->GetPositionZ(), m_vsmpStepBox[i]->GetPositionZ(), fONE_BROCK_HIT_AREA, fONE_BROCK_HIT_AREA ) ){
				if( m_pCollision->FloorJudge(
					m_pPlayer, m_pPlayer->GetColToFloorRange(), m_pPlayer->m_fFloorY,
					m_vsmpStepBox[i].get(),
					bGroundFlg ) )
				{
					bCutGroundCheck = true;
					//����Ă�����^��.
					if( bGroundFlg ){
						//����̈ړ��ʂ��X�V.
						m_pPlayer->AddPositionX( m_vsmpStepBox[i]->GetCarryRangeX() );
					}
					//break���Ȃ��ƕʂ̏��̏��ɏ㏑�������.
					break;
				}
			}
		}
		m_pPlayer->SetGroundFlg( bGroundFlg );
	}

	//----- �S�[���� -----//.
	if( !bCutGroundCheck ){
		for( int i=0; i<m_vsmpGoalMgr.size(); i++ ){
			if( /*isCutOutForHit( m_pPlayer->GetPositionZ(), m_vsmpGoalMgr[i]->GetPositionZ(), fONE_BROCK_HIT_AREA, fGOAL_TREASURE_HIT_AREA )*/ 1 ){
				//��.
				if( m_pCollision->FloorJudge(
					m_pPlayer, m_pPlayer->GetColToFloorRange(), m_pPlayer->m_fFloorY,
					m_vsmpGoalMgr[i]->GetTrBoxColPointer(),
					bGroundFlg ) )
				{
					bCutGroundCheck = true;
					//break���Ȃ��ƕʂ̏��̏��ɏ㏑�������.
					break;
				}
				//������.
				if( m_pCollision->FloorJudge(
					m_pPlayer, m_pPlayer->GetColToFloorRange(), m_pPlayer->m_fFloorY,
					m_vsmpGoalMgr[i]->GetFloorColPointer(),
					bGroundFlg ) )
				{
					bCutGroundCheck = true;
					//break���Ȃ��ƕʂ̏��̏��ɏ㏑�������.
					break;
				}
			}
		}
		m_pPlayer->SetGroundFlg( bGroundFlg );
	}



	//���񂾂�߂��Ă���.
	if( m_pPlayer->GetDead() ){
		//�^�C�}�[�Ƃ߂�.
		m_smpUiManagar->SetTimerStop( true );
		m_iRespawnTimer ++;
		if( m_iRespawnTimer > iDEAD_TIME ){
			//�V�[��������(���X�|�[��).
			if( m_pPlayer->GetHp() > 0 ){
				if( m_smpUiManagar->GetBlackIdle() ){
					//�Ó];
					m_smpUiManagar->BlackStart( fBLACK_SPD_FAST );
				}
				else if( m_smpUiManagar->GetBlackEnd() ){
					InitMain();
				}
			}
			//�Q�[���I�[�o�[.
			else{
				if( m_smpUiManagar->GetBlackIdle() ){
					//�Ó];
					m_smpUiManagar->BlackStart( fBLACK_SPD_SLOW );
				}
				else if( m_smpUiManagar->GetBlackEnd() ){
					InitOver();
				}
			}
		}
	}
	//�����Ă��鎞��.
	else{
		//���ɗ�������.
		if( m_pPlayer->GetPositionY() < fDROP_DOWN_Y ){
			m_pPlayer->Dead();
//			m_pCollision->PlaySe( clsCollision::enSOUND_DROP_DOWN );
		}

		//�S�[��.
		if ( !m_vsmpGoalMgr.empty() )
		{
			if( m_vsmpGoalMgr[0]->GetBoxOpened() ){
				InitResult();
//				//�Ó]�J�n.
//				m_smpUiManagar->BlackStart( fBLACK_SPD_SLOW, false );
//				//�Ó]�I��.
//				if( m_smpUiManagar->GetBlackEnd() ){
//					InitResult();
//				}
			}
		}
	}
}
void clsMain::SceneResult()
{
	const int iSILENCE_TIME = 30;

	switch( m_enResultSceneMode )
	{
	case enRSM_SILENCE://�Â��ɂȂ�.
		//���U���gBGM�i�s.
		m_iResultTimer ++;
		if( m_iResultTimer > iSILENCE_TIME ){
			//�W���O���Đ�.
			m_pBgm[enBGM_RESULT]->SeekToStart();
			m_pBgm[enBGM_RESULT]->Play( true );

			m_iResultTimer = 0;
			m_enResultSceneMode = enRSM_JINGLE;
		}
		break;

	case enRSM_JINGLE:
		//�W���O�����~�܂�����.
		if( m_pBgm[enBGM_RESULT]->IsStopped() ){
			//UI�̗p���I����Ă�����.
			if( m_smpUiManagar->isCanBgmRePlay() ){
				m_pBgm[enBGM_RESULT]->Stop();
				m_pBgm[enBGM_MAIN]->Play( true );
				m_enResultSceneMode = enRSM_LOOP;
			}
		}
		break;

	case enRSM_LOOP:
		//���[�v.
		if( m_pBgm[enBGM_MAIN]->IsStopped() ){
			m_pBgm[enBGM_MAIN]->SeekToStart();
			m_pBgm[enBGM_MAIN]->Play( true );
		}
		break;

	default:
		m_enResultSceneMode = enRSM_SILENCE;
		break;
	}

	m_pPlayer->MoveResultScene();

	//----- ��� -----//.
	CameraMgr();

	//----- ���̈ʒu -----//.
	SetEar( m_pPlayer->GetPositionZ(), m_Camera.vEye.z );

	//----- �S�[���̕ǂ����蔻��Ɠ��� -----//.
	for( int i=0; i<m_vsmpGoalMgr.size(); i++ ){
		m_pCollision->WallJudge( m_pPlayer, m_vsmpGoalMgr[i]->GetFloorColPointer() );
		m_pCollision->WallJudge( m_pPlayer, m_vsmpGoalMgr[i]->GetTrBoxColPointer() );
		m_vsmpGoalMgr[i]->Update( GetEar() );
	}
	//----- �S�[���� -----//.
	bool bGroundFlg = false;
	bool bCutGroundCheck = false;	//�n�ʂ̏�ɂ���Ȃ炻��ȏ�̃`�F�b�N�͂���Ȃ��̂ŁA���̂��߂̃t���O.
	if( !bCutGroundCheck ){
		for( int i=0; i<m_vsmpGoalMgr.size(); i++ ){
			if( /*isCutOutForHit( m_pPlayer->GetPositionZ(), m_vsmpGoalMgr[i]->GetPositionZ(), fONE_BROCK_HIT_AREA, fGOAL_TREASURE_HIT_AREA )*/ 1 ){
				//��.
				if( m_pCollision->FloorJudge(
					m_pPlayer, m_pPlayer->GetColToFloorRange(), m_pPlayer->m_fFloorY,
					m_vsmpGoalMgr[i]->GetTrBoxColPointer(),
					bGroundFlg ) )
				{
					bCutGroundCheck = true;
					//break���Ȃ��ƕʂ̏��̏��ɏ㏑�������.
					break;
				}
				//������.
				if( m_pCollision->FloorJudge(
					m_pPlayer, m_pPlayer->GetColToFloorRange(), m_pPlayer->m_fFloorY,
					m_vsmpGoalMgr[i]->GetFloorColPointer(),
					bGroundFlg ) )
				{
					bCutGroundCheck = true;
					//break���Ȃ��ƕʂ̏��̏��ɏ㏑�������.
					break;
				}
			}
		}
		m_pPlayer->SetGroundFlg( bGroundFlg );
	}


	//�󔠂̉�ʏ�̍��W���΂̏o���ʒu�ɂ���.
	m_smpUiManagar->SetJewelAppPos(
		ConvDimPos(
			m_smpUiManagar->GetJewelAppPos(),
			m_vsmpGoalMgr[0]->GetBoxPos() ) );




	//����{�^��.
	bool bPushEnter = false;
	if( m_pXInput->IsPressEnter( XINPUT_A ) )bPushEnter = true;
	GETKEY_DOWN( 'Z' ) bPushEnter = true;
	GETKEY_DOWN( 'A' ) bPushEnter = true;

	if( m_smpUiManagar->GetBlackIdle() ){
		//�X�^�b�t���[���ւ�.
		if( bPushEnter ){
			//���U���g�̏I��.
			if( m_smpUiManagar->isCanResEnd() ){
				m_smpUiManagar->BlackStart( fBLACK_SPD_SLOW );
				m_pSe[enSe_EXIT]->SeekPlay();
			}
			//���U���g���ŏI��Ԃ�.
			else{
				m_smpUiManagar->ResEndPos();
			}
		}
	}
	//�Ó]�I��.
	else if( m_smpUiManagar->GetBlackEnd() ){
		InitEndroll();
	}
}
void clsMain::SceneEnding()
{
	//���[�v.
	if( m_pBgm[enBGM_ENDROLL]->IsStopped() ){
		m_pBgm[enBGM_ENDROLL]->SeekToStart();
		m_pBgm[enBGM_ENDROLL]->Play( true );
	}

	//�e�X�g.
	if( GetAsyncKeyState( 'Y' ) & 0x8000 ) m_Camera.vLook.y += 0.05f;
	if( GetAsyncKeyState( 'H' ) & 0x8000 ) m_Camera.vLook.y -= 0.05f;
	if( GetAsyncKeyState( 'J' ) & 0x8000 ) m_Camera.vLook.x += 0.05f;
	if( GetAsyncKeyState( 'G' ) & 0x8000 ) m_Camera.vLook.x -= 0.05f;
	if( GetAsyncKeyState( 'U' ) & 0x8000 ) m_Camera.vLook.z += 0.05f;
	if( GetAsyncKeyState( 'T' ) & 0x8000 ) m_Camera.vLook.z -= 0.05f;

	if( GetAsyncKeyState( 'W' ) & 0x8000 ) m_Camera.vEye.y += 0.05f;
	if( GetAsyncKeyState( 'S' ) & 0x8000 ) m_Camera.vEye.y -= 0.05f;
	if( GetAsyncKeyState( 'D' ) & 0x8000 ) m_Camera.vEye.x += 0.05f;
	if( GetAsyncKeyState( 'A' ) & 0x8000 ) m_Camera.vEye.x -= 0.05f;
	if( GetAsyncKeyState( 'E' ) & 0x8000 ) m_Camera.vEye.z += 0.05f;
	if( GetAsyncKeyState( 'Q' ) & 0x8000 ) m_Camera.vEye.z -= 0.05f;
	if( GetAsyncKeyState( 'W' ) & 0x8000 ) m_Camera.vLook.y += 0.05f;
	if( GetAsyncKeyState( 'S' ) & 0x8000 ) m_Camera.vLook.y -= 0.05f;
	if( GetAsyncKeyState( 'D' ) & 0x8000 ) m_Camera.vLook.x += 0.05f;
	if( GetAsyncKeyState( 'A' ) & 0x8000 ) m_Camera.vLook.x -= 0.05f;
	if( GetAsyncKeyState( 'E' ) & 0x8000 ) m_Camera.vLook.z += 0.05f;
	if( GetAsyncKeyState( 'Q' ) & 0x8000 ) m_Camera.vLook.z -= 0.05f;



	m_pPlayer->MoveEndScene( fEND_SCROL_SPD );

	m_fEndScrol += fEND_SCROL_SPD;
	if( m_fEndScrol > 0 ){
		m_fEndScrol -= fEND_SCROL_LIMIT;
	}


	m_pEndEnemy->Update();

	//�Z����.
	bool bPushEnterEnter = false;
	if( m_pXInput->IsPressEnter( XINPUT_A ) )bPushEnterEnter = true;
	GETKEY_DOWN( 'Z' ) bPushEnterEnter = true;
	GETKEY_DOWN( 'A' ) bPushEnterEnter = true;

	//������.
	bool bPushEnterStay = false;
	if( m_pXInput->IsPressStay( XINPUT_A ) )bPushEnterStay = true;
	GETKEY_STAY( 'Z' ) bPushEnterStay = true;
	GETKEY_STAY( 'A' ) bPushEnterStay = true;


	//�Ó]�������Ă��Ȃ�.
	if( m_smpUiManagar->GetBlackIdle() ){
		//����.
		m_smpUiManagar->SetPushButtun( bPushEnterStay );
		//�X�^�b�t���[�����I�������.
		if ( m_smpUiManagar->GetEndRollEnd() ){
			//�I��.
			if( bPushEnterEnter ){
				//�^�C�g����.
				m_smpUiManagar->BlackStart( fBLACK_SPD_SLOW, false );
				m_pSe[enSe_ENTER]->SeekPlay();
			}
		}
	}
	//�Ó]�I��.
	else if( m_smpUiManagar->GetBlackEnd() ){
		InitTitle();
	}
}
void clsMain::SceneOver()
{
	m_pPlayer->MoveOverScene();


	bool bPushEnter = false;
	if( m_pXInput->IsPressEnter( XINPUT_A ) )bPushEnter = true;
	GETKEY_DOWN( 'Z' ) bPushEnter = true;
	GETKEY_DOWN( 'A' ) bPushEnter = true;

	if( m_smpUiManagar->GetBlackIdle() ){
		//�^�C�g����.
		if( bPushEnter ){
			//
			m_smpUiManagar->BlackStart( fBLACK_SPD_SLOW );
			m_pSe[enSe_ENTER]->SeekPlay();
		}
	}
	//�Ó]�I��.
	else if( m_smpUiManagar->GetBlackEnd() ){
		InitTitle();
	}
}

//==========
void clsMain::RenderTitle()
{
	//��.
	if ( !m_vsmpWall.empty() ){
		for ( int i=0; i<m_vsmpWall.size(); i++ ){
			m_vsmpWall[i]->Render( m_mView, m_mProj, m_vLight, m_Camera.vEye );
		}
	}
	//��.
	if ( !m_vsmpFloor.empty() ){
		for ( int i=0; i<m_vsmpFloor.size(); i++ ){
			m_vsmpFloor[i]->Render( m_mView, m_mProj, m_vLight, m_Camera.vEye );
		}
	}



	//�v���C���[(�A���r�A)�\��.
	m_pPlayer->Render( m_mView, m_mProj, m_vLight, m_Camera.vEye );

	//�h�A.
	if ( !m_vsmpDoorMgr.empty() ){
		for ( int i=0; i<m_vsmpDoorMgr.size(); i++ ){
			m_vsmpDoorMgr[i]->Render( m_mView, m_mProj, m_vLight, m_Camera.vEye );
		}
	}

	//�G�t�F�N�V�[�A.
	m_pEffect->Render( m_mView, m_mProj, m_Camera.vEye );


}
void clsMain::RenderMain()
{

#ifdef Inoue
	//��.
	if ( !m_vsmpWall.empty() ){
		for ( int i=0; i<m_vsmpWall.size(); i++ ){
			m_vsmpWall[i]->Render( m_mView, m_mProj, m_vLight, m_Camera.vEye );
		}
	}
	//��.
	if ( !m_vsmpFloor.empty() ){
		for ( int i=0; i<m_vsmpFloor.size(); i++ ){
			m_vsmpFloor[i]->Render( m_mView, m_mProj, m_vLight, m_Camera.vEye );
		}
	}
	//����ی^.
	if ( !m_vsmpStepCil.empty() ){
		for ( int i=0; i<m_vsmpStepCil.size(); i++ ){
			m_vsmpStepCil[i]->Render( m_mView, m_mProj, m_vLight, m_Camera.vEye );
		}
	}
	//����l�p�^.
	if ( !m_vsmpStepBox.empty() ){
		for ( int i=0; i<m_vsmpStepBox.size(); i++ ){
			m_vsmpStepBox[i]->Render( m_mView, m_mProj, m_vLight, m_Camera.vEye );
		}
	}
	//���Ƃ���.
	if ( !m_vsmpCoverMgr.empty() ){
		for ( int i=0; i<m_vsmpCoverMgr.size(); i++ ){
			m_vsmpCoverMgr[i]->Render( m_mView, m_mProj, m_vLight, m_Camera.vEye );
		}
	}
	//�S�[��.
	if ( !m_vsmpGoalMgr.empty() ){
		for ( int i=0; i<m_vsmpGoalMgr.size(); i++ ){
			m_vsmpGoalMgr[i]->Render( m_mView, m_mProj, m_vLight, m_Camera.vEye );
		}
	}

#endif //#ifdef Inoue.


	//�v���C���[(�A���r�A)�\��.
	m_pPlayer->Render( m_mView, m_mProj, m_vLight, m_Camera.vEye );


#ifdef Inoue
	//�G.
	if ( !m_vsmpEnemyMgr.empty() ){
		for (int i=0; i<m_vsmpEnemyMgr.size(); i++ ){
			m_vsmpEnemyMgr[i]->Render( m_mView, m_mProj, m_vLight, m_Camera.vEye );
		}
	}
	//����.
	if ( !m_vsmpSpiaFloorMgr.empty() ){
		for ( int i=0; i<m_vsmpSpiaFloorMgr.size(); i++ ){
			m_vsmpSpiaFloorMgr[i]->Render( m_mView, m_mProj, m_vLight, m_Camera.vEye );
		}
	}
	//�Ǒ�.
	if ( !m_vsmpSpiaWallMgr.empty() ){
		for ( int i=0; i<m_vsmpSpiaWallMgr.size(); i++ ){
			m_vsmpSpiaWallMgr[i]->Render( m_mView, m_mProj, m_vLight, m_Camera.vEye );
		}
	}
	//����.
	if ( !m_vsmpCeiling.empty() ){
		for (int i = 0; i < m_vsmpCeiling.size(); i++ )
		{
			m_vsmpCeiling[i]->Render( m_mView, m_mProj, m_vLight, m_Camera.vEye );
		}
	}

#endif //#ifdef Inoue

	//�G�t�F�N�V�[�A.
	m_pEffect->Render( m_mView, m_mProj, m_Camera.vEye );

#ifdef Inoue

	//�y���f������(�t���Ȃ͓̂��߂̓s��).
	if ( !m_vsmpPend.empty() ){
		for ( int i=m_vsmpPend.size()-1; i>=0; i-- ){
			m_vsmpPend[i]->Render( m_mView, m_mProj, m_vLight, m_Camera.vEye );
			m_vsmpPend[i]->GetBonePos( PEND_BONE_NAME );
		}
	}
	//�h�A(�t���Ȃ͓̂��߂̓s��).
	if ( !m_vsmpDoorMgr.empty() ){
		for ( int i=m_vsmpDoorMgr.size()-1; i>=0; i-- ){
			m_vsmpDoorMgr[i]->Render( m_mView, m_mProj, m_vLight, m_Camera.vEye );
		}
	}

	//�`�F�b�N�|�C���g����.
	if( m_pCheck != nullptr ){
		m_pCheck->Render( m_mView, m_mProj, m_Camera.vEye );
	}


	if ( !m_vsmpTest.empty() ){
		for ( int i=0; i<m_vsmpTest.size(); i++ ){
			m_vsmpTest[i]->Render( m_mView, m_mProj, m_vLight, m_Camera.vEye );
		}
	}
#endif //#ifdef Inoue.





#ifdef _DEBUG
	//��K.
	for( int i=0; i<m_iBlkAryMax; i++ ){
		m_ppBlkAry[i]->Render( m_mView, m_mProj, m_vLight, m_Camera.vEye );
	}

	//ڲ�̕\��(����).
	m_pRayV->m_Ray.vPos = m_pPlayer->GetPosition();
	//��]�l�����@�ɍ��킹��.
	m_pRayV->m_Ray.fYaw = m_pPlayer->GetRotationY();
		m_pRayV->Render( m_mView, m_mProj );

	//ڲ�̕\��(�O��).
	m_pRayFB->m_Ray.vPos = m_pPlayer->GetPosition();
	//��]�l�����@�ɍ��킹��.
	m_pRayFB->m_Ray.fYaw = m_pPlayer->GetRotationY();
		m_pRayFB->Render( m_mView, m_mProj );

	//ڲ�̕\��(���E).
	m_pRayH->m_Ray.vPos = m_pPlayer->GetPosition();
	//��]�l�����@�ɍ��킹��.
	m_pRayH->m_Ray.fYaw = m_pPlayer->GetRotationY();
		m_pRayH->Render( m_mView, m_mProj );


//	//�߰è�ق̕\��.
//	if( m_pParticle->m_bDispFlg ){
//		SetDepth( false );	//Zý�:OFF.
//		//���߰è��1�����߲�Ľ��ײ�1���Ƃ���500���`��.
//		int particleMax = m_pParticle->GetMaxParticle();
//		for( int i=0; i<particleMax; i++ ){
//			//���݂�i�Ԗڂ̗��̈ʒu���擾.
//			D3DXVECTOR3 vParticlePos = m_pParticle->GetParticlePos( i );
//			//i�Ԗڂ̗���\��.
//			m_pParticle->Render( m_mView, m_mProj, m_Camera.vEye, vParticlePos );
//		}
//		//�߰è�ق̈ړ�����.
//		m_pParticle->Run();
//		SetDepth( true );	//Zý�:ON.
//	}





#endif//#if _DEBUG



}
void clsMain::RenderOver()
{
	//�v���C���[(�A���r�A)�\��.
	m_pPlayer->Render( m_mView, m_mProj, m_vLight, m_Camera.vEye );
	//�G�t�F�N�V�[�A.
	m_pEffect->Render( m_mView, m_mProj, m_Camera.vEye );

}
void clsMain::RenderResult()
{
	RenderMain();
	//�G�t�F�N�V�[�A.
	m_pEffect->Render( m_mView, m_mProj, m_Camera.vEye );

}
void clsMain::RenderEnding()
{
	//�ǂƏ��ƓV��( ���̖������ꂢ�ȏ� ).
	if ( !m_vsmpWall.empty() && !m_vsmpFloor.empty() && !m_vsmpCeiling.empty() ){
		m_vsmpWall[0]->SetPosition( vENDING_INIT_STAGE_POS );
		m_vsmpFloor[0]->SetPosition( vENDING_INIT_STAGE_POS );
		m_vsmpCeiling[0]->SetPosition( vENDING_INIT_CEILING_POS );
		m_vsmpWall[0]->AddPositionZ( m_fEndScrol );
		m_vsmpFloor[0]->AddPositionZ( m_fEndScrol );
		m_vsmpCeiling[0]->AddPositionZ( m_fEndScrol );
		for( int i=0; i<iENDING_STAGE_MAX; i++ ){
			m_vsmpWall[0]->Render( m_mView, m_mProj, m_vLight, m_Camera.vEye );
			m_vsmpFloor[0]->Render( m_mView, m_mProj, m_vLight, m_Camera.vEye );
			m_vsmpCeiling[0]->Render( m_mView, m_mProj, m_vLight, m_Camera.vEye );
			m_vsmpWall[0]->AddPositionZ( fONE_BLOCK_SIZE );
			m_vsmpFloor[0]->AddPositionZ( fONE_BLOCK_SIZE );
			m_vsmpCeiling[0]->AddPositionZ( fONE_BLOCK_SIZE );
		}
	}

	//�v���C���[(�A���r�A)�\��.
	m_pPlayer->Render( m_mView, m_mProj, m_vLight, m_Camera.vEye );

	//�ǂ�������G.
	m_pEndEnemy->Render( m_mView, m_mProj, m_vLight, m_Camera.vEye );

	//�G�t�F�N�V�[�A.
	m_pEffect->Render( m_mView, m_mProj, m_Camera.vEye );

}

void clsMain::RenderDebugText()
{
#if _DEBUG


	//NULL����.
	if ( m_pText != nullptr ){
		char strDbgTxt[256];
		int dbgtxty = 50;
		int dbgTxtX = 20;

		int YajirusiY;

		sprintf_s(strDbgTxt,
			"Ply:x[%f],y[%f],z[%f],",
			m_pPlayer->GetPositionX(),
			m_pPlayer->GetPositionY(),
			m_pPlayer->GetPositionZ() );

		m_pText->Render(strDbgTxt, 0, dbgtxty);
		dbgtxty += 10;


		sprintf_s(strDbgTxt,
			"m_fEndScrol:[%f]",
			m_fEndScrol );

		m_pText->Render(strDbgTxt, 0, dbgtxty);
		dbgtxty += 10;

		//�ǂ�����X�V����?.
		sprintf_s(strDbgTxt, "Control Mode");
		m_pText->Render(strDbgTxt, dbgtxty, dbgtxty);
		dbgtxty += 10;

		YajirusiY = dbgtxty;
		sprintf_s(strDbgTxt, "jyougiu  Mode");
		m_pText->Render(strDbgTxt, dbgtxty, dbgtxty);
		dbgtxty += 10;

		sprintf_s(strDbgTxt, "Png Mode");
		m_pText->Render(strDbgTxt, dbgtxty, dbgtxty);
		dbgtxty += 10;

		//���.
		switch (ControlMode){
			case 0:
				break;
			case 1:
				YajirusiY += 10;
				break;
		}
		sprintf_s(strDbgTxt, "->");
		m_pText->Render(strDbgTxt, dbgTxtX, YajirusiY);

		if (!m_vsmpSpriteTest.empty())
		{
			//PngDisp.
			sprintf_s(strDbgTxt,
				"PngDispScale[%d]:W[%f],H[%f]",
				m_SpriteControlNum,
				m_vsmpSpriteTest[m_SpriteControlNum]->GetSs().Disp.w,
				m_vsmpSpriteTest[m_SpriteControlNum]->GetSs().Disp.h);

			m_pText->Render(strDbgTxt, dbgTxtX, dbgtxty);
			dbgtxty += 10;

			//PngDisp.
			sprintf_s(strDbgTxt,
				"PngPos[%d]:X[%f],Y[%f]",
				m_SpriteControlNum,
				m_vsmpSpriteTest[m_SpriteControlNum]->GetPos().x,
				m_vsmpSpriteTest[m_SpriteControlNum]->GetPos().y);

			m_pText->Render(strDbgTxt, dbgTxtX, dbgtxty);
			dbgtxty += 10;
		}

		sprintf_s(strDbgTxt,
			"camera:x[%f],y[%f],z[%f],",
			m_Camera.vEye.x,
			m_Camera.vEye.y,
			m_Camera.vEye.z);

		m_pText->Render(strDbgTxt, 0, dbgtxty);
		dbgtxty += 10;
		sprintf_s(strDbgTxt,
			"look:x[%f],y[%f],z[%f],",
			m_Camera.vLook.x,
			m_Camera.vLook.y,
			m_Camera.vLook.z);

		m_pText->Render(strDbgTxt, 0, dbgtxty);
		dbgtxty += 10;

		//dbgtxty += 10;
		//if( m_pBgm[0]->IsStopped() ){
		//	sprintf_s( strDbgTxt, "Stopped" );
		//	m_pText->Render( strDbgTxt, 0, dbgtxty );
		//}
		//if( m_pBgm[0]->IsPlaying() ){
		//	sprintf_s( strDbgTxt, "Playingn" );
		//	m_pText->Render( strDbgTxt, 0, dbgtxty );
		//}
	}

#endif //#if _DEBUG

}

#ifdef START_LOADING_DISPLAY
//========/ ۰�މ�� /========//
void clsMain::NowLoading()
{
	LoadSpriteInit();
	//ؿ���׽.
	m_pResource = clsResource::GetInstance();


	//------------------------------
	//	Effekseer�׽.
	//------------------------------
	clsEffects::GetInstance()->Create( m_pDevice, m_pDeviceContext );
	clsEffects::GetInstance()->LoadData();

	m_pEffect = clsEffects::GetInstance();
	//�������Ȃ��ƂȂ�������͍Đ�����Ȃ�.
	PlayEffKick( { 0.0f, 0.0f, 0.0f } );
	m_pEffect->Stop( m_ehKickHit );



	for (LoadStep = 0; LoadStep <= 6; LoadStep++)
	{
		m_pLoadGage->SetPos( D3DXVECTOR3(WND_W / 2.0f - (ss_LoadGage.Disp.w/2.0f), 453.0f , -2.0f) );
		LoadGageUVTarget = (0.5f - (0.5f / 100.0f) * LoadGage);
		m_pLoadGage->SetPatarnU( LoadGageUVTarget );

		LoadRender();
		switch (LoadStep)
		{
		case 0:
			m_pResource->InitStaticModel( m_hWnd, m_pDevice, m_pDeviceContext);
			m_pResource->InitSkinModel( m_hWnd, m_pDevice, m_pDeviceContext);
			LoadGage += 10;
			break;
			//=====Static Model=====.
		case 1:
			m_pResource->CreateStaticModel(
				"Data\\Test\\Test.x",
				clsResource::enST_MODEL_Plane );
			//�ʏ��.
			m_pResource->CreateStaticModel(
				"Data\\Stage\\kabe.X",
				clsResource::enST_MODEL_WALL );

			//�ǖʖ�����.
			m_pResource->CreateStaticModel(
				"Data\\Stage\\kabe_2.X",
				clsResource::enST_MODEL_WALL_NOT_WALL );

			//�ǖʖ����ʏ폰.
			m_pResource->CreateStaticModel(
				"Data\\Stage\\yuka_2.X",
				clsResource::enST_MODEL_FLOOR_NOT_WALL_NORMAL );

			//�ǖʖ������̔�����.
			m_pResource->CreateStaticModel(
				"Data\\Stage\\yuka_hanbun_L_2.X",
				clsResource::enST_MODEL_FLOOR_NOT_WALL_HALF_L );

			//�ǖʖ����E�̔�����.
			m_pResource->CreateStaticModel(
				"Data\\Stage\\yuka_hanbun_R_2.X",
				clsResource::enST_MODEL_FLOOR_NOT_WALL_HALF_R );

			//�ǖʖ����y���f��������.
			m_pResource->CreateStaticModel(
				"Data\\Stage\\yuka_kizu_2.X",
				clsResource::enST_MODEL_FLOOR_NOT_WALL_PEND );

			//�ʏ폰.
			m_pResource->CreateStaticModel(
				"Data\\Stage\\yuka.X",
				clsResource::enST_MODEL_FLOOR_NORMAL );

			//���̔�����.
			m_pResource->CreateStaticModel(
				"Data\\Stage\\yuka_hanbun_L.X",
				clsResource::enST_MODEL_FLOOR_HALF_L );

			//�E�̔�����.
			m_pResource->CreateStaticModel(
				"Data\\Stage\\yuka_hanbun_R.X",
				clsResource::enST_MODEL_FLOOR_HALF_R );
			//�y���f��������.
			m_pResource->CreateStaticModel(
				"Data\\Stage\\yuka_kizu.X",
				clsResource::enST_MODEL_FLOOR_PEND );
			//�c�ړ���.
			m_pResource->CreateStaticModel(
				"Data\\Stage\\StepCylinder.X",
				clsResource::enST_MODEL_STEP_CIL );
			m_pResource->CreateStaticModel(
				"Data\\Stage\\StepCylinder_Big.X",
				clsResource::enST_MODEL_STEP_CIL_BIG );
			//���ړ���.
			m_pResource->CreateStaticModel(
				"Data\\Stage\\StepBox.X",
				clsResource::enST_MODEL_STEP_BOX );

			//�h�A���f�����m�F����.
			m_pResource->CreateStaticModel(
				"Data\\Stage\\mon.X",
				clsResource::enST_MODEL_MON);
			LoadGage += 50;
			break;
		case 2:
			//�S�[�����f�����m�F����.
			m_pResource->CreateStaticModel(
				"Data\\TrRoom\\gool.X",
				clsResource::enST_MODEL_GOOL );
			//�󔠂̂����蔻��
			m_pResource->CreateStaticModel(
				"Data\\TrRoom\\TrBoxCol.X",
				clsResource::enST_MODEL_TR_BOX_COL );

			//���ʑ�.
			m_pResource->CreateStaticModel(
				"Data\\Trap\\Spia.x",
				clsResource::enST_MODEL_SPIA );
			//�Ǒ�.
			m_pResource->CreateStaticModel(
				"Data\\Trap\\SpiaOfWall.x",
				clsResource::enST_MODEL_SPIA_OF_WALL );

			//���̒������̕ǔ���p.
			m_pResource->CreateStaticModel(
				"Data\\Trap\\SpiaWallHit.x",
				clsResource::enST_MODEL_SPIA_WALL );

			//�����̗��Ƃ����̊W.
			m_pResource->CreateStaticModel(
				"Data\\Trap\\otosiana_L.x",
				clsResource::enST_MODEL_COVER_L );

			//�E���̗��Ƃ����̊W.
			m_pResource->CreateStaticModel(
				"Data\\Trap\\otosiana_R.x",
				clsResource::enST_MODEL_COVER_R );

			//��K�p�̃u���b�N.
			m_pResource->CreateStaticModel(
				"Data\\Jikken\\1_1_1_kijyun.x",
				clsResource::enST_MODEL_BLOCK );

			//�V��.
			m_pResource->CreateStaticModel(
				"Data\\Stage\\Ceiling.X",
				clsResource::enST_MODEL_CEILING );

			//�e�X�g�p.
			m_pResource->CreateStaticModel(
				"Data\\Stage\\tobira.X",
				clsResource::enST_MODEL_TEST );

			//=====Skin Model=====.
			//�A���r�A.
			m_pResource->CreateSkinModel(
				"Data\\Player\\Arbia.X",
				clsResource::enSK_MODEL_PLAYER );

			//�h�A.
			m_pResource->CreateSkinModel(
				"Data\\Stage\\tobira.X",
				clsResource::enSK_MODEL_DOOR );

			//�G.
			m_pResource->CreateSkinModel(
				"Data\\Enemy\\Enemy.X",
				clsResource::enSK_MODEL_ENEMY );
			//�y���f������.
			m_pResource->CreateSkinModel(
				"Data\\Trap\\Pendulum.X",
				clsResource::enSK_MODEL_PENDULUM );
			//��.
			m_pResource->CreateSkinModel(
				"Data\\TrRoom\\TrRoomBox.X",
				clsResource::enSK_MODEL_TR_BOX );
			LoadGage += 10;
			break;
		case 3:
			LoadGage += 10;
			break;
		case 4:
			LoadGage += 10;
			break;
		case 5:
			ReadMesh();
			LoadGage += 10;
			break;
		case 6:
			//�^�C�g���p�̏�����������.
			InitTitle();
			m_pBgm[enBGM_START_UP]->Stop();
			LoadGage += 10;
			break;
		default:
			break;
		}
	}
}

// ۰�މ�ʏ����� //
void clsMain::LoadSpriteInit()
{
	m_pLoadBack = make_unique<clsSprite2D>();
	m_pLoadBack->Create(m_pDevice, m_pDeviceContext, "Data\\Load\\Black.png");
	m_pLoadBack->SetPos( D3DXVECTOR3 (0.0f, 0.0f, 0.0f) );
	m_pLoadBack->SetPatarnU( 0.0f );
	m_pLoadBack->SetPatarnV( 0.0f );
	m_pLoadBack->SetAlpha( 1.0f );

	m_pLoadTxt = new clsSprite2D;
	m_pLoadTxt->Create(m_pDevice, m_pDeviceContext, "Data\\Load\\LoadBack.png");
	m_pLoadTxt->SetDispW(m_pLoadTxt->GetSs().Base.w/2);
	m_pLoadTxt->SetDispH(m_pLoadTxt->GetSs().Base.h/2);
	m_pLoadTxt->SetPos( WND_W/2-m_pLoadTxt->GetSs().Disp.w/2 , m_pLoadTxt->GetSs().Disp.h );

	m_pLoadTxt->SetPatarnU( 0.0f );
	m_pLoadTxt->SetPatarnV( 0.0f );
	m_pLoadTxt->SetAlpha( 1.0f );

	ss_LoadGage.Disp.w = 960.0f;
	ss_LoadGage.Disp.h = 50.0f;
	ss_LoadGage.Stride.w = ss_LoadGage.Disp.w/2;
	ss_LoadGage.Stride.h = ss_LoadGage.Disp.h;
	m_pLoadGage = new clsGageSprite2D;
	m_pLoadGage->Init(m_pDevice, m_pDeviceContext, "Data\\Load\\LoadGarge2.png", ss_LoadGage);
	m_pLoadGage->SetPos( D3DXVECTOR3(0.0f, 0.0f, 0.0f ) );
	m_pLoadGage->SetPatarnU( 0.0f );
	m_pLoadGage->SetPatarnV( 0.0f );
	m_pLoadGage->SetAlpha( 1.0f );

	m_pLoadGageBack = make_unique<clsSprite2D>();
	m_pLoadGageBack->Create(m_pDevice, m_pDeviceContext, "Data\\Load\\LoadGargeType.png");
	m_pLoadGageBack->SetDispW(960.0f);
	m_pLoadGageBack->SetDispH(50.0f);
	m_pLoadGageBack->SetPos( D3DXVECTOR3(WND_W / 2.0f - (ss_LoadGage.Disp.w/2.0f), 453.0f , -2.0f) );
	m_pLoadGageBack->SetAlpha( 1.0f );

	LoadGage = 0;
	LoadGageUVTarget = 0.0f;
}

// ۰�މ�ʕ\�� //
void clsMain::LoadRender()
{
	//��ʂ̸ر.
	float ClearColor[4] = { 0.0f, 0.0f, 1.0f, 1.0f };//�ر�F(RGBA��:255�̔䗦�ŏo��)
	//�װ�ޯ��ޯ̧.
	m_pDeviceContext->ClearRenderTargetView(m_pBackBuffer_TexRTV, ClearColor);
	//���߽��ݼ��ޯ��ޯ̧.
	m_pDeviceContext->ClearDepthStencilView(m_pBackBuffer_DSTexDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	SetDepth(false);
	m_pLoadBack->Render();

	m_pLoadGageBack->Render();

	m_pLoadGage->Render();

	m_pLoadTxt->Render();

	SetDepth(true);

	//�����ݸނ��ꂽ�Ұ�ނ�\��.
	m_pSwapChain->Present(0, 0);
}

#endif //#ifdef START_LOADING_DISPLAY



//�G�t�F�N�g�Đ�.
void clsMain::PlayEffKick( D3DXVECTOR3 vPos )
{
//	if( !m_pEffect->PlayCheck( m_ehKickHit ) ){

		D3DXVECTOR3 vEffPos = vPos;
		vEffPos.y += fEFF_UP_OFFSET;

		m_ehKickHit = m_pEffect->Play( clsEffects::enEfcType_KICK_HIT, vEffPos );
		m_pEffect->SetScale( m_ehKickHit, vEFF_KICK_HIT_SCALE );
//	}
}
void clsMain::PlayEffSlash( D3DXVECTOR3 vPos )
{
	if( !m_pEffect->PlayCheck( m_ehSlashHit ) ){

		D3DXVECTOR3 vEffPos = vPos;
		vEffPos.y += fEFF_UP_OFFSET;

		m_ehSlashHit = m_pEffect->Play( clsEffects::enEfcType_SLASH_HIT, vEffPos );
	}
	m_pEffect->SetScale( m_ehSlashHit, vEFF_SLASH_HIT_SCALE );
}


#ifdef Tahara
//ConvDimPos�̎��O����.
void clsMain::SetViewPort10( D3D11_VIEWPORT* Vp )
{
	m_ViewPort.TopLeftX = Vp->TopLeftX;
	m_ViewPort.TopLeftY = Vp->TopLeftY;
	m_ViewPort.MaxDepth = Vp->MaxDepth;
	m_ViewPort.MinDepth = Vp->MinDepth;
	m_ViewPort.Width = Vp->Width;
	m_ViewPort.Height = Vp->Height;
};

//3D���W�̃X�N���[��( 2D )���W�ϊ�.dimensions(����) conversion(�ϊ�)
D3DXVECTOR3 clsMain::ConvDimPos( D3DXVECTOR3 v2DPos, D3DXVECTOR3 v3DPos )
{
	D3DXMATRIX mWorld;
	D3DXMatrixIdentity( &mWorld );
	D3DXVec3Project( &v2DPos, &v3DPos, &m_ViewPort, &m_mProj, &m_mView, &mWorld );
	return v2DPos;
}
#endif//#ifdef Tahara

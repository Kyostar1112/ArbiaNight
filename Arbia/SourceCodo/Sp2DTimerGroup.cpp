#include "Sp2DTimerGroup.h"


#define FILE_PATH_SCOLON "Data\\Image\\Colon.png"

//----- �� -----//.
//����.
#define ALIAS_NAME "TImerCountStart"
#define  FILE_PATH "SE\\400Ui\\100Timer.wav"
const	  int iVOL = 1000;


//�^�C�}�[�̐�.
const char cTIMEER_NUM = cTIMER_GROUP_TIMER_NUM;
//�R�����̐�.
const char cCOLON_NUM = cTIMER_GROUP_COLON_NUM;
//�����̕�����.
const float fNUM_DISP = 64.0f;
//�R�����̕�����.
const float fCOLON_DISP = fNUM_DISP / 2.0f;
//�񌅖ڂ����ɂ��炷.
const float fOFFSET_LEFT_SECOND = fNUM_DISP / 2.0f;
//�R�������W���炵.
const float fOFFSET_COLON_X = 72.0f;
const float fOFFSET_COLON_Y = 16.0f;
//��P�^�̏��.
const int iTIMER_NUM_MAX = 59;



clsTimerGrp::clsTimerGrp()
{
	for( char i=0; i<cTIMEER_NUM; i++ ){
		m_Timer[i] = nullptr;
	}
	for( char i=0; i<cCOLON_NUM; i++ ){
		m_Colon[i] = nullptr;
	}
	m_pSe = nullptr;
}

clsTimerGrp::~clsTimerGrp()
{
	if( m_pSe != nullptr ){
		m_pSe->Stop();
		m_pSe->Close();
		delete m_pSe;
		m_pSe = nullptr;
	}

	if( m_Colon != nullptr ){
		for( char i=0; i<cCOLON_NUM; i++ ){
			if( m_Colon[i] != nullptr ){
				delete m_Colon[i];
				m_Colon[i] = nullptr;
			}
		}
	}
	if( m_Timer != nullptr ){
		for( char i=0; i<cTIMEER_NUM; i++ ){
			if( m_Timer[i] != nullptr ){
				delete m_Timer[i];
				m_Timer[i] = nullptr;
			}
		}
	}
}


void clsTimerGrp::Create( HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11 )
{
	m_vPos = { 0.0f, 0.0f, 0.0f };

	for( char i=0; i<cTIMEER_NUM; i++ ){
		m_Timer[i] = new clsTimer;
		m_Timer[i]->Create( pDevice11, pContext11 );
	}
	for( char i=0; i<cCOLON_NUM; i++ ){
		m_Colon[i] = new clsSprite2D;
		m_Colon[i]->Create( pDevice11, pContext11, FILE_PATH_SCOLON );
		m_Colon[i]->SetSs(
			m_Colon[i]->GetSs().Base.w,
			m_Colon[i]->GetSs().Base.h,
			fCOLON_DISP, fCOLON_DISP );

		m_Colon[i]->UpDateSpriteSs();
	}

	//���ʉ�.
	m_pSe = new clsSound;
	m_pSe->SetVolume( iVOL );
	//���O.
	char cAliasName[STR_BUFF_MAX] = "";
	strcat_s( cAliasName, sizeof( cAliasName ), ALIAS_NAME );
	//�쐬.
	m_pSe->Open( FILE_PATH, cAliasName, hWnd );


	ReSet();
}
void clsTimerGrp::ReSet()
{
	for( char i=0; i<cTIMEER_NUM; i++ ){
		m_Timer[i]->ReSet();
	}
	m_bRimitFlg = false;
	m_bStop = m_bStopOld = false;
}

void clsTimerGrp::SetPos( D3DXVECTOR3 vPos )
{
	const float fOffsetPlus = 2.5f;
	m_vPos = vPos;
	
	for( char i=0; i<cTIMEER_NUM; i++ ){
		m_Timer[i]->SetPos( vPos );
	}

	//1�ԏ�̌��ȊO���E�ɂ��炷.
	float fOffset = 0.0f;
	for( char i=cTIMEER_NUM-1; i>=0; i-- ){
		m_Timer[i]->AddPosX( fOFFSET_LEFT_SECOND * fOffset );
		fOffset += fOffsetPlus;
	}


	//�u:�v.
	for( char i=0; i<cCOLON_NUM; i++ ){
		m_Colon[i]->SetPos( vPos );
	}

	fOffset = 0.0f;
	for( char i=0; i<cCOLON_NUM; i++ ){
		m_Colon[i]->AddPosX( fOFFSET_LEFT_SECOND * fOffset + fOFFSET_COLON_X );
		m_Colon[i]->AddPosY( fOFFSET_COLON_Y );
		fOffset += fOffsetPlus;
	}
}
void clsTimerGrp::AddPos( D3DXVECTOR3 vPos )
{
	m_vPos += vPos;
	SetPos( m_vPos );
}
void clsTimerGrp::AddPosY( float fPos )
{
	m_vPos.y += fPos;
	SetPos( m_vPos );
}


void clsTimerGrp::Update()
{
	//�J�E���g.
	if( !m_bRimitFlg && !m_bStop ){
		m_Timer[0]->PlusNum();
	}
	//�J�E���g���n�߂�.
	if( !m_bStop && m_bStopOld ){
		m_pSe->SeekPlay();
	}

	m_bStopOld = m_bStop;


	for( char i=0; i<cTIMEER_NUM; i++ ){
		if( m_Timer[i]->Carrying() ){
			//�I�[�o�[���Ȃ�?.
			if( i + 1 < cTIMEER_NUM ){
				m_Timer[ i + 1 ]->PlusNum();
			}
			//���.
			else{
				for( char j=0; j<cTIMEER_NUM; j++ ){
					m_Timer[j]->Rimit();
					m_bRimitFlg = true;
				}
			}
		}
		m_Timer[i]->Update();
	}
}

void clsTimerGrp::Render()
{
	for( char i=0; i<cTIMEER_NUM; i++ ){
		m_Timer[i]->Render();
	}
	for( char i=0; i<cCOLON_NUM; i++ ){
		m_Colon[i]->Render();
	}

}


int clsTimerGrp::GetTime()
{
	int Time = 0;
	Time +=	m_Timer[2]->GetTime() * 100;
	Time +=	m_Timer[1]->GetTime();
	return Time;
}

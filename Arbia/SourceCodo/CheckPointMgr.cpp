#include "CheckPointMgr.h"



//��.
const char ALIAS_NAME[] = "CheckPoint";
const char FILE_PATH[] = "SE\\600Result\\010JewelUp.wav";
const int VOL = 1000;



//������.
const char cSTRING_MAX = 8;

const LPSTR sFILE_PATH[cSTRING_MAX] =
{
	{ "Data\\Image\\CheckPointSet\\Chi.png"	},
	{ "Data\\Image\\CheckPointSet\\Le.png"	},
	{ "Data\\Image\\CheckPointSet\\Ltu.png"	},
	{ "Data\\Image\\CheckPointSet\\Ku.png"	},
	{ "Data\\Image\\CheckPointSet\\Po.png"	},
	{ "Data\\Image\\CheckPointSet\\I.png"	},
	{ "Data\\Image\\CheckPointSet\\NN.png"	},
	{ "Data\\Image\\CheckPointSet\\To.png"	},
};


const D3DXVECTOR3 vINIT_POS = { 0.0f, -100.0f, 0.0f };
const D3DXVECTOR3 vSTART_POS = { 10.0f, 4.0f, 0.0f };

//�����T�C�Y.
const float fSIZE = 0.5f;

//�����ƕ����̊Ԋu.
const float fOFFSET = 0.5f;

//�����ƕ����̉��s�Ԋu.
const float fOFFSET_Z = 0.25f * 0.25f * 0.25f * 0.25f;


//�����̈ړ����x.
const float fSTRING_SPD = -1.5f;

//�������~�܂�X���W.
const float fSTOP_POS_X[cSTRING_MAX] =
{
	{-( fOFFSET * 4 - ( fOFFSET / 2.0f ) ) },
	{-( fOFFSET * 3 - ( fOFFSET / 2.0f ) ) },
	{-( fOFFSET * 2 - ( fOFFSET / 2.0f ) ) },
	{-( fOFFSET * 1 - ( fOFFSET / 2.0f ) ) },
	{ ( fOFFSET * 1 - ( fOFFSET / 2.0f ) ) },
	{ ( fOFFSET * 2 - ( fOFFSET / 2.0f ) ) },
	{ ( fOFFSET * 3 - ( fOFFSET / 2.0f ) ) },
	{ ( fOFFSET * 4 - ( fOFFSET / 2.0f ) ) },
};



clsCheckPointMgr::clsCheckPointMgr()
{
	m_ppModel = nullptr;
	m_pSe = nullptr;
}

clsCheckPointMgr::~clsCheckPointMgr()
{
	Release();
}
void clsCheckPointMgr::Release()
{
	if( m_pSe != nullptr ){
		m_pSe->Stop();
		m_pSe->Close();
		delete m_pSe;
		m_pSe = nullptr;
	}

	if( m_ppModel != nullptr ){
		for( char i=0; i<cSTRING_MAX; i++ ){
			delete m_ppModel[i];
			m_ppModel[i] = nullptr;
		}
		delete[] m_ppModel;
		m_ppModel = nullptr;
	}
}

void clsCheckPointMgr::Create( HWND hWnd, ID3D11Device* pDevice11,
	ID3D11DeviceContext* pContext11 )
{
	m_ppModel = new clsCheckPoint*[cSTRING_MAX];
	for( char i=0; i<cSTRING_MAX; i++ ){
		m_ppModel[i] = new clsCheckPoint;
		m_ppModel[i]->Create( pDevice11, pContext11, sFILE_PATH[i] );
		m_ppModel[i]->SetScale( fSIZE );
	}

	//���N���X.
	m_pSe = new clsSound;
	//���O.
	char cAliasName[STR_BUFF_MAX] = "";
	strcat_s( cAliasName, sizeof( cAliasName ), ALIAS_NAME );
	//�쐬.
	m_pSe->Open( FILE_PATH, cAliasName, hWnd );
	//�ő剹�ʐݒ�.
	m_pSe->SetMaxVolume( VOL );
	//�����ʏ�����.
	m_pSe->SetVolume( VOL );

	Init();
}

void clsCheckPointMgr::Init()
{
	for( char i=0; i<cSTRING_MAX; i++ ){
		m_ppModel[i]->Init();
		m_ppModel[i]->m_vPos = D3DXVECTOR3( vINIT_POS );
		m_ppModel[i]->m_enMode = clsCheckPoint::enM_AHEAD;
	}

}

void clsCheckPointMgr::Start( float fPosZ )
{
	if( m_ppModel[0]->m_enMode != clsCheckPoint::enM_AHEAD ){
		return;
	}
	m_ppModel[0]->m_enMode = clsCheckPoint::enM_IN;

	for( char i=0; i<cSTRING_MAX; i++ ){
		m_ppModel[i]->m_vPos = vSTART_POS;
		m_ppModel[i]->m_vPos.z = fPosZ;
		//�d�Ȃ�h�~.
		m_ppModel[i]->m_vPos.z -= static_cast<float>( i ) * fOFFSET_Z;
	}

	m_ppModel[0]->SetMove( true );

	m_pSe->SeekToStart();
	m_pSe->Play();

}

void clsCheckPointMgr::Update()
{
	//if( m_enMode == clsCheckPoint::enM_AHEAD || m_enMode == clsCheckPoint::enM_END ){
	//	return;
	//}
	for( char i=0; i<cSTRING_MAX; i++ ){
		//������z����.
		if( m_ppModel[i]->GetMove() ){
			switch( m_ppModel[i]->m_enMode )
			{
			case clsCheckPoint::enM_IN:
				//������.
				m_ppModel[i]->m_vPos.x += fSTRING_SPD;
				//�����I���.
				if( m_ppModel[i]->m_vPos.x <= fSTOP_POS_X[i] ){
					m_ppModel[i]->m_enMode = clsCheckPoint::enM_STAY;
					m_ppModel[i]->m_vPos.x = fSTOP_POS_X[i];
					//���̎n��.fNEXT_MOVE_START_POS_X
					//�I�[�o�[���Ȃ�.
					if( i + 1 < cSTRING_MAX ){
						//���̓z���܂������ĂȂ��Ȃ�.
						if( !m_ppModel[i + 1]->GetMove() ){
							//���̂�𓮂���.
							m_ppModel[i + 1]->SetMove( true );
							m_ppModel[i + 1]->m_enMode = clsCheckPoint::enM_IN;
							m_pSe->SeekToStart();
							m_pSe->Play();
						}
					}
				}
				break;

			case clsCheckPoint::enM_STAY:
				//�������@�I���ۂɉ��炷.
				if( m_ppModel[i]->Stay() ){
					m_pSe->SeekToStart();
					m_pSe->Play();
				}
				break;

			case clsCheckPoint::enM_OUT:
				m_ppModel[i]->m_vPos.x += fSTRING_SPD;
				if( m_ppModel[i]->m_vPos.x <= -vSTART_POS.x ){
					m_ppModel[i]->m_enMode = clsCheckPoint::enM_END;
					m_ppModel[i]->SetMove( false );
				}
				break;

			}
		}
	}

}


void clsCheckPointMgr::Render( D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3 &vEye )
{
	for( char i=0; i<cSTRING_MAX; i++ ){
		m_ppModel[i]->Render( mView, mProj, vEye );
	}
}


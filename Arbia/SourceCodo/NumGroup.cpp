#include "NumGroup.h"


const int iSTR_BUFF_MAX = 256;

//��������̍���.
const float fNUM_ONE_HEIGHT = 180.0f;

#define FILE_PATH_TEN "Data\\Image\\NumberTen.png"




const char cNUM_MAX = cNUM_GROUP_NUM_MAX;//�����̌���.
const int iTEN_DECIMAL = 10;//10�i��.
const int iSIX_DECIMAL = 6;	//6 �i��.
const int iMAX = 99;


//������.
const float fNUM_DISP = 64.0f;
//�񌅖ڂ����ɂ��炷.
const float fOFFSET_LEFT_SECOND = fNUM_DISP / 2.0f;


const WHSIZE_FLOAT NUMSIZE  = { 64.0f, 64.0f };



clsNumGrp::clsNumGrp()
{
	for( char i=0; i<cNUM_MAX; i++ ){
		NumImage[i] = nullptr;
	}
}

clsNumGrp::~clsNumGrp()
{
	if( NumImage != nullptr ){
		for( char i=0; i<cNUM_MAX; i++ ){
			if( NumImage[i] != nullptr ){
				delete NumImage[i];
				NumImage[i] = nullptr;
			}
		}
	}
}



void clsNumGrp::Create( ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11 )
{
	m_bSixDecimal = false;

	for( char i=0; i<cNUM_MAX; i++ ){

		NumImage[i] = new clsSprite2D;

		NumImage[i]->Create( pDevice11, pContext11, FILE_PATH_TEN );

		NumImage[i]->SetSs(
			NumImage[i]->GetSs().Base.w,
			NumImage[i]->GetSs().Base.h,
			NUMSIZE.w, NUMSIZE.h,
			1.0f, iTEN_DECIMAL );

		NumImage[i]->UpDateSpriteSs();
	}
	//�ő�l.
	m_iMax = iMAX;

	ReSet();
}


void clsNumGrp::ReSet()
{
	m_iRealNum = 0;
	m_iDiffNum = 0;
}

void clsNumGrp::SetPos( D3DXVECTOR3 vPos )
{
	m_vPos = vPos;
	
	for( char i=0; i<cNUM_MAX; i++ ){
		NumImage[i]->SetPos( vPos );
	}

	//1�ԏ�̌��ȊO���E�ɂ��炷.
	float fOffset = 0.0f;
	for( char i=cNUM_MAX-1; i>=0; i-- ){
		NumImage[i]->AddPosX( fOFFSET_LEFT_SECOND * fOffset );
		fOffset += 1.0f;
	}
}
void clsNumGrp::AddPos( D3DXVECTOR3 vPos )
{
	m_vPos += vPos;
	SetPos( m_vPos );
}

void clsNumGrp::Update()
{
//	GETKEY_DOWN('G')PlusNum();
//	GETKEY_DOWN('T')PlusNum();
//	GETKEY_DOWN( 'F' )PlusNum();


	ApproachTargetNum();
	SetParam( m_iRealNum );
}


void clsNumGrp::Render()
{
	for( char i=0; i<cNUM_MAX; i++ ){
		NumImage[i]->Render();
	}
}

//�����l�����W�l�ɕϊ�.
float clsNumGrp::ConvNum( float fRendNum, bool bSixFlg )
{
	if( bSixFlg ){
		return ( (float) iSIX_DECIMAL - 1.0f ) - fRendNum;
	}
	return ( (float) iTEN_DECIMAL - 1.0f ) - fRendNum;
}


//���𑝂₷.
void clsNumGrp::PlusNum()
{
	m_iRealNum ++;

	if( m_iRealNum > m_iMax ){
		m_iRealNum = m_iMax;
	}
}
//�������炷.
void clsNumGrp::MinusNum()
{
	m_iRealNum --;

	if( m_iRealNum < 0 ){
		m_iRealNum = 0;
	}
}
//�������ߑł�.
void clsNumGrp::SetNum( int iTargetNum )
{
	//������SetNum( int )�ɂ���Ďw�肳�ꂽ��( ���񂾂񂱂�ɋ߂Â� )
	m_iDiffNum = iTargetNum - m_iRealNum;
}




//���Z�b�g.
void clsNumGrp::SetParam( int iRealNum )
{
	//��P�^������.
	float fNum = 0.0f;
	for( char i=0; i<cNUM_MAX; i++ ){
		fNum = (float)( iRealNum % iTEN_DECIMAL );
		m_fRendNum[i] = fNum;
		iRealNum /= iTEN_DECIMAL;
	}

	//�����������̂�������.
	bool bSixFlg = false;

	for( char i=0; i<cNUM_MAX; i++ ){
		//�����l�����W�l�ɕϊ�.
		m_fNumU[i] = ConvNum( m_fRendNum[i], bSixFlg );
		//���W�l�Z�b�g.
		NumImage[i]->SetPatarnV( m_fNumU[i] );
		//�^�C�}�[�Ȃ�2���ڂ�6�i��.
		if( m_bSixDecimal )	bSixFlg = true;
	}
}

//�^�[�Q�b�g�Ɏ����l���߂Â��� : approach_to_target.
void clsNumGrp::ApproachTargetNum()
{
	if( m_iDiffNum > 0 ){
		m_iRealNum ++;
		m_iDiffNum --;
	}
	else if( m_iDiffNum < 0 ){
		m_iRealNum --;
		m_iDiffNum ++;
	}
}



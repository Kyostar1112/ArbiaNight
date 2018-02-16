#include "Sp2DTimer.h"

#define FILE_PATH_TEN "Data\\Image\\NumberTen.png"
#define FILE_PATH_SIX "Data\\Image\\NumberSix.png"


const char cNUM_MAX = 2;//�����̌���.


const int iTEN_DECIMAL = 10;//10�i��.
const int iSIX_DECIMAL = 6;	//6 �i��.
const int iMAX = 60;

//������.
const float fNUM_DISP = 64.0f;
//�񌅖ڂ����ɂ��炷.
const float fOFFSET_LEFT_SECOND = fNUM_DISP / 2.0f;


const WHSIZE_FLOAT NUMSIZE  = { 64.0f, 64.0f };


//��P�^�̏��.
const int iTIMER_NUM_MAX = 59;


void clsTimer::Create( ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11 )
{
	m_bSixDecimal = true;

	for( char i=0; i<cNUM_MAX; i++ ){
		NumImage[i] = new clsSprite2D;
	}
	NumImage[0]->Create( pDevice11, pContext11, FILE_PATH_TEN ,1.0f, iTEN_DECIMAL);
	NumImage[1]->Create( pDevice11, pContext11, FILE_PATH_SIX ,1.0f, iSIX_DECIMAL );

	NumImage[0]->SetSs(
		NumImage[0]->GetSs().Base.w,
		NumImage[0]->GetSs().Base.h,
		NUMSIZE.w, NUMSIZE.h);

	NumImage[1]->SetSs(
		NumImage[1]->GetSs().Base.w,
		NumImage[1]->GetSs().Base.h,
		NUMSIZE.w, NUMSIZE.h);

	//�ő�l.
	m_iMax = iMAX;

	ReSet();
}

void clsTimer::ReSet()
{
	m_iRealNum = 0;
	m_iDiffNum = 0;
	m_bCarrying = false;
}



//���𑝂₷.
void clsTimer::PlusNum()
{
	m_iRealNum ++;

	if( m_iRealNum >= m_iMax ){
		m_iRealNum = 0;
		m_bCarrying = true;
	}
}



void clsTimer::AddPosX( float fMove )
{
	for( char i=0; i<cNUM_MAX; i++ ){
		NumImage[i]->AddPosX( fMove );
	}

}




//���オ��( �J��オ�� )�m�F.
bool clsTimer::Carrying(){
	if( m_bCarrying ){
		m_bCarrying = false;
		return true;
	}
	return false;
}



//����ݒ�p.
void clsTimer::Rimit(){
	m_iRealNum = iTIMER_NUM_MAX;
}




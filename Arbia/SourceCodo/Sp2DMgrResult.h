#ifndef _SP_2D_MANAGER_RESULT_SCENE_H_
#define _SP_2D_MANAGER_RESULT_SCENE_H_

#include "Sp2DMgrPushButn.h"
#include "Sp2DJewelSet.h"

#include "Sound.h"


const char cSTEAL_RESULT_MAX = 4;//���ʂ̍��ڂ̐�.
const char cJEWEL_NUM_PARTS = 3;//���ڂ��Ƃ̐��ʂ̍ő吔.
//��΂̍��v�� : ���ڐ� * ���ړ�����̍ő吔 + ����҃^�C���{�[�i�X��1.
const short sJEWEL_NUM_MAX = ( cSTEAL_RESULT_MAX * cJEWEL_NUM_PARTS ) - 2;


//UI�ɕ\�����邽�߂ɕK�v.
struct UI_STATE_RESULT
{
public:
	int iLives;
	int iTime;
	int iDisc;


	UI_STATE_RESULT(){
		iINIT_NUM = 1001;
		Init();
	}
	void Init(){
		iLives = 0;
		iTime = iDisc = iINIT_NUM;
	}

private:
	int iINIT_NUM;

};


class clsSp2dMgrReslt
{
public:
	clsSp2dMgrReslt();
	~clsSp2dMgrReslt();



	enum enResultMode
	{
		enM_BLACK = 0,
		enM_STEAL,
		enM_OTHER,
		enM_JEWEL,

		enM_PARF,//�p�[�t�F�N�g.

		enM_FINAL_SET,//�ŏI�ʒu.

		enM_END,//�����Ȃ�.


		enM_MAX
	};



	void Create( HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11 );

	void Init();

	//�V�[���̂͂��߂̏�����.
	void StartSet();

	void UpDate();

	void Render();
	void Release();

	void SetJewelAppPos( D3DXVECTOR3 vPos ){
		m_vJewelAppPos = vPos;
	}
	D3DXVECTOR3 GetJewelAppPos(){
		return m_vJewelAppPos;
	}

	//��ΕK�v���̔��f�ɕK�v�ȏ��������Ă���.
	void SetJewelState( UI_STATE_RESULT UiState ){
		m_UiState = UiState;
	}

	//BGM�čĐ����t���O�֐�.
	bool isCanBgmRePlay(){
		return m_bCanBgmRePlay;
	}

	//���艟������I����Ă���?.
	bool isCanEnd(){
		return m_bEndFlg;
	}

	//�����I�ɍŏI��Ԃɂ���.
	void ResEndPos(){
		m_enMode = enM_FINAL_SET;
	};

private:

	//��΂�Move��Acc�����߂�. Parb -> parabola : ������.
	void MakeParbPower(
		D3DXVECTOR3 &vMove, float &fAcc,
		D3DXVECTOR3 vStartPos, D3DXVECTOR3 vEndPos );


	//����.
	void BlackMove();
	void StealMove();
	void OtherMove();
	void JewelMove();
	void ParfeMove();//�p�[�t�F�N�g.

	void FinalPos( bool bInit = false );

	void NextMove(){
		m_enMode = static_cast<enResultMode>( m_enMode + 1 );
	}


	//�p�[�t�F�N�g���̃t���O.
	enum enParMode
	{
		enPM_SOUND = 0,
		enPM_PARFECT,
		enPM_JEWEL,
		enPM_END,
	};
	enParMode m_enParFlg;

	//��Ώ�����.
	void JewelSetReSet();

	//��Ώo�����̔��f.
	void JewelJudge();

	//���̕�΂𓮂�������.
	void NextJewerSet();

	//OtherMove()�Ŏg��.
	bool m_bOtherMove[cSTEAL_RESULT_MAX - 1];


	//�A�N�V�����V�[���𔼂ΉB���Ó]�i�������j.
	unique_ptr<clsSprite2D> m_smpBlack;

	//�u���񂾐��ʁv.
	unique_ptr<clsSprite2D> m_smpSteal;
	//���񂾐��ʂ̍���.
	unique_ptr<clsSprite2D> m_smpResult[cSTEAL_RESULT_MAX];//for( char i=0; i<cSTEAL_RESULT_MAX; i++ ){
	//��� : ���ڐ� * ���ړ�����̍ő吔 + ����҃^�C���{�[�i�X��1.
	unique_ptr<clsJewerSet> m_smpJewel[sJEWEL_NUM_MAX];	//for( char i=0; i<sJEWEL_NUM_MAX; i++ ){

	//�{�^���w��.
	unique_ptr<clsPushTxt> m_smpPushTxt;


	enResultMode m_enMode;

	D3DXVECTOR3 m_vJewelAppPos;//��Ώo���ʒu(�󔠂Əd�˂�).
	int			m_iJewelCnt;


	UI_STATE_RESULT m_UiState;

	bool m_bEndFlg;//���艟������I����Ă���?.

	bool m_bCanBgmRePlay;

	//���̎��.
	enum enSound
	{
		enS_HIT = 0,
		enS_OPEN,

		enS_STEAL,
		enS_OTHER,

		enS_LAST_JEWEL,

		enS_MAX,	//�ő吔.
	};
	//���ʉ�.
	clsSound*	m_pSeBox[enS_MAX];
	void SetSe( HWND hWnd );


};
#endif //#ifndef _SP_2D_MANAGER_RESULT_SCENE_H_

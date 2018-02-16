#ifndef _UI_MANAGER_H_
#define _UI_MANAGER_H_


#include "Mymacro.h"
#include "Sp2DMgrActTxt.h"

#include "Sp2DMgrTitle.h"
#include "Sp2DMgrMain.h"
#include "Sp2DMgrResult.h"
#include "Sp2DMgrOver.h"
#include "Sp2DMgrEnding.h"

#include "SceneManager.h"




using namespace std;


class clsUiManagar
{
public:
	clsUiManagar();
	~clsUiManagar();

	void Init( HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);
	void Delete();

	void ChangeTitleInit();
	void SceneTitle();
	void ChangeMainInit();
	void SceneMain();
	void ChangeResultInit();
	void SceneResult();
	void ChangeOverInit();
	void SceneOver();
	void ChangeEndingInit();
	void SceneEnding();



	void RenderTitle();
	void RenderMain();
	void RenderResult();
	void RenderOver();
	void RenderEnding();

	void BlackOut();
	void BlackStart(float ChaAmo, bool BFlg = true);

	//�Ó]�@�\�������Ă��邩�ǂ���byInoue.
	bool GetBlackIdle(){
		if( m_smpBlack->m_BlackMode == Idle &&
			m_smpWhite->m_BlackMode == Idle )
		{
			return true;
		}
		return false;
	}

	//�Ó]���������u�Ԃ�m�点��byTahara.
	bool GetBlackEnd(){
		if( m_smpBlack->m_BlackMode == Change ||
			m_smpWhite->m_BlackMode == Change )
		{
			return true;
		}
		return false;
	}

#ifdef Tahara

	//���b�v.
	void ReSetLives(){
		m_smpMainScene->ReSetLives();
	}
	void ReSetDisc(){
		m_smpMainScene->ReSetDisc();
	}
	void ReSetTimer(){
		m_smpMainScene->ReSetTimer();
	}
	void SetLives( int iHp ){
		m_smpMainScene->SetLives( iHp );
	}
	void SetDisc( int iDisc ){
		m_smpMainScene->SetDisc( iDisc );
	}

	void SetTimerStop( bool bStop ){
		m_smpMainScene->SetTimerStop( bStop );
	}

	//�O�_�Z�b�g.
	void AddPosYUiSet( float fMove ){
		m_smpMainScene->AddPosYUiSet( fMove );
	}

	//�A�N�V����������������.
	void ActTxtOut(){
		m_smpMainScene->ActTxtMoveOut();
	}

	//���.
	void SetJewelAppPos( D3DXVECTOR3 vPos ){
		m_smpResult->SetJewelAppPos( vPos );
	}
	D3DXVECTOR3 GetJewelAppPos(){
		return m_smpResult->GetJewelAppPos();
	}

	//���U���g�Ŏg��.
	bool isCanBgmRePlay(){
		return m_smpResult->isCanBgmRePlay();
	}
	bool isCanResEnd(){
		return m_smpResult->isCanEnd();
	}
	void ResEndPos(){
		m_smpResult->ResEndPos();
	}

	//���b�v + ���ԃZ�b�g.
	void SetJewelState( UI_STATE_RESULT ResUiState ){
		ResUiState.iTime = m_smpMainScene->GetTime();
		m_smpResult->SetJewelState( ResUiState );
	}

#endif//#ifdef Tahara


	//�^�C�g���̓��ߊJ�n.//True�Ȃ瓧�߂��Ă���false�Ȃ牽�����Ȃ�.
	void SetTitleTransFlg(bool TransFlg)
	{
		m_smpTitleScene->SetTransmissionFlg(TransFlg);
	}

	//EndRoll�̏I���m�F�p�֐�.
	bool GetEndRollEnd()
	{
		return m_smpEndingScene->GetEndRollEnd();
	}

	//�{�^����������Ă��邩�m�F�p�֐�.
	void SetPushButtun(bool PushButtun)
	{
		m_smpEndingScene->SetPushButtun(PushButtun);
	}

	//���C���̏�̃e�L�X�g�����ɂ��낵�ĕ\������֐�.
	void TopMainTxtMoveStart()
	{
#ifdef Tahara
		const float fUI_IN_SPD = 1.5f;
#endif //Tahara
		m_smpMainScene->MoveStartTopTxt(fUI_IN_SPD);
	}

private:

	float	m_fChangePoint;
	bool	m_bColor;

	void Init();


	unique_ptr<clsSprite2D> m_smpBlack;	//�Ó]�p.
	unique_ptr<clsSprite2D> m_smpWhite;	//�Ó]�p.

	//void ActTxtPosChange(bool );


	unique_ptr<clsSprite2D> m_smpXButton;	//X�{�^���˂��ł��.
	unique_ptr<clsSprite2D> m_smpAButton;	//A�{�^���˂��ł��.
	unique_ptr<clsActTxt>	m_smpActTxt;	//���C���̃W�����v�Ȃǂ̕���.

	//�^�C�g���p.
	unique_ptr<clsSp2dMgrTitle> m_smpTitleScene;

	//���C���p.
	unique_ptr<clsSp2dMgrMain> m_smpMainScene;

	//���U���g�p.
	unique_ptr<clsSp2dMgrReslt> m_smpResult;

	//�G���f�B���O�p.
	unique_ptr<clsSp2dMgrEnding> m_smpEndingScene;	//�N���W�b�g�˂��ł��.

	//�I�[�o�[�p.
	unique_ptr<clsSp2dMgrOver> m_smpOverScene;

	unique_ptr<clsSprite2D> m_pTestSpr2D;


};

#endif //#ifndef _UI_MANAGER_H_
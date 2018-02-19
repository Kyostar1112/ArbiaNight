#define _CRT_SECURE_NO_WARNINGS
//�x���ɂ��Ă̺��ޕ��͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning( disable:4005 )
//============================================================
//	�ݸٰ��.
//============================================================
#include <Windows.h>

#include <D3DX11.h>
#include <D3D11.h>

#include <D3DX10.h>//�uD3DX�`�v�̒�`�g�p���ɕK�v.
#include <D3D10.h>

#include "Global.h"
#include "MyMacro.h"

#if _DEBUG
#include "DebugText.h"
#include "Particle.h"
#include "Ray.h"		//ڲ�\���׽.
#endif//#if _DEBUG


#include "Sound.h"		//����޸׽.



#include "Effects.h"//Effekseer���Ǘ�����׽.


#include "Player.h"

#include "UiManager.h"

#include "Collision.h"

#include "Resource.h"

#include "File.h"

#include "Wall.h"
#include "Floor.h"
#include "StepCylinder.h"
#include "StepBox.h"
#include "DoorManager.h"
#include "Pendulum.h"
#include "SpiaFloorManager.h"
#include "SpiaWallManager.h"
#include "CoverManager.h"
#include "EnemyManager.h"
#include "GoalManager.h"

#include "GageSprite2D.h"

#include "SceneManager.h"

#include "EndEnemyMgr.h"

#include "CheckPointMgr.h"


//============================================================
//	ײ����.
//============================================================
#pragma comment( lib, "winmm.lib" )

#pragma comment( lib, "d3dx11.lib" )
#pragma comment( lib, "d3d11.lib" )

#pragma comment( lib, "d3dx10.lib" )//�uD3DX�`�v�̒�`�g�p���ɕK�v.



//============================================================
//	�萔.
//============================================================
#define WND_TITLE	"�����A���r�A"
#define APR_NAME	"Arbia"


//============================================================
//	�\����.
//============================================================
//��׏��.
struct CAMERA
{
	D3DXVECTOR3 vEye;	//��׈ʒu.
	D3DXVECTOR3 vLook;	//�����ʒu.
	float		fYaw;	//��]�l.
	D3DXMATRIX	mRot;	//��]�s��.
};

struct StagePatarunSet
{
	//��{�ǂ���.
	int  iWall;		// 0:�ǖ���1:�ʏ��.

	//����͓����ɏo�Ȃ�.
	int  iFloor;		// 0:������1:�ʏ폰 2:�������E��.
					// 3:���������� 4:�y���f��������.

	//��΂ɏ�����.
	int   iEnemy;		// 0:�����Ȃ��� 1�`:�G�̐ݒu.

	//��΂ɏ�����.
	int	 iStepCil;	// �c�ړ��̏� 0:�����Ȃ��� 1�ȏ�:���������o���̂Ƃ����W�����˂Ă���.
	int	 iStepBox;   // ���ړ��̏� 0:�����Ȃ��� 1�ȏ�:���������o���̂Ƃ����W�����˂Ă���.

	//���O�͏������O��ɂ���.
	bool bDoor;		// 0:�����Ȃ��� 1:���ݒu.
	//��΂ɕǂ�ς���悤��.
	int iPend;		// 0:�����Ȃ��� 1:�y���f�������ݒu.
	bool bSpiaFloor;	// 0:�����Ȃ��� 1:�����ݒu.
	//�������ł�����.
	int iSpiaWall;	// 0:�����Ȃ��� 1:���ǐݒu.

	//��΂ɏ�����.
	bool bCover;		// 0:�����Ȃ��� 1:���Ƃ����W�̐ݒu.

	//��΂ɏ�����.
	bool bGoal;		// 0:�����Ȃ��� 1:�S�[���̐ݒu.

	//�e�X�g�̃��f��.
	bool bTest;
};



//============================================================
//	Ҳݸ׽.
//============================================================
class clsMain
{
public:
	clsMain();	//�ݽ�׸�.
	~clsMain();	//�޽�׸�.


	//����޳�������֐�.
	HRESULT InitWindow(
		HINSTANCE hInstance,
		INT x, INT y, INT width, INT height,
		LPSTR WindowName);

	//����޳�֐�(ү���ޖ��̏���).
	LRESULT MsgProc(
		HWND hWnd, UINT uMsg,
		WPARAM wParam, LPARAM lParam );

	//ү����ٰ��.
	void Loop();
	//���ع����Ҳݏ���.
	void AppMain();
	//�`��(�����ݸ�)(��DX9MESH����Main����2���݂���̂Œ���).
	void Render();




	//DirectX������.
	HRESULT InitD3D();
	//Direct3D�I������.
	void DestroyD3D();

	//ү���ǂݍ��݊֐�(�܂Ƃ߂�).
	HRESULT ReadMesh();


#if _DEBUG
	//�̨��쐬.
	HRESULT InitSphere( clsDX9Mesh* pMesh, float fScale = 0.7f );
	//�̨��Փ˔���֐�.
	bool Collision( clsDX9Mesh* pAttacker, clsDX9Mesh* pTarget );

	//�޳��ިݸ��ޯ���쐬.
	HRESULT InitBBox( clsDX9Mesh* pMesh );
	//�ޯ���Փ˔���֐�.
	bool BBoxCollision( clsDX9Mesh* pAttacker, clsDX9Mesh* pTarget );
#endif //#if _DEBUG



	//ڲ��ү���̂����蔻��.
	bool Intersect(
		clsDX9Mesh* pAttacker, clsDX9Mesh* pTarget,
		float* pfDistance, D3DXVECTOR3* pvIntersect );
	//�����ʒu����غ�݂̒��_��������.
	HRESULT FindVerticesOnPoly(
		LPD3DXMESH pTarget, DWORD dwPolyIndex,
		D3DXVECTOR3* pVecVertices );
	//�ǂ̂����蔻��֘A.
	void WallJudge( clsDX9Mesh* pAttacker, clsDX9Mesh* pWall );
	//��]�l����.
	void DirOverGuard( float* fYaw );




	//�[�xý�(Zý�)�@ON/OFF�ؑ�.
	void SetDepth( bool bFlg );


	//�ް݂̍��W���Ƃ�(ׯ�ߊ֐�).
	void GetPosFromBone( clsD3DXSKINMESH* skinMesh, char BoneName[], D3DXVECTOR3& Pos );

	//��׊֐�.
	void Camera();
	//��ۼު���݊֐�.
	void Proj();



#ifdef Inoue

#ifdef START_LOADING_DISPLAY
	/*/ ۰�މ�ʏ��� /*/
	void NowLoading();
	/*/ ۰�މ�ʏ����� /*/
	void LoadSpriteInit();
	/*/ ۰�މ�ʕ\�� /*/
	void LoadRender();

	/*=*=*=*=*=*=*=*=| ���ײ�2D |=*=*=*=*=*=*=*=*/
	clsSprite2D* m_pLoadTxt;

	unique_ptr<clsSprite2D> m_pLoadBack;

	clsGageSprite2D* m_pLoadGage;
	GAGE_SPRITE_STATE ss_LoadGage;
	unique_ptr<clsSprite2D> m_pLoadGageBack;
	/*=*=*=*=*=*=*=*=| ���ײ�2D |=*=*=*=*=*=*=*=*/
	int LoadStep;
	int LoadGage;
	float LoadGageUVTarget;
#endif//#ifdef START_LOADING_DISPLAY


	unique_ptr<clsFile>	m_pTestData;

	unique_ptr<clsFile>	m_smpStageData;
	unique_ptr<clsFile>	m_smpStageDataExcel;
	unique_ptr<clsFile>	m_smpStageDataExcelStageMax;
	unique_ptr<clsFile>	m_smpStageDataReadMe;

	unique_ptr<clsUiManagar>	m_smpUiManagar;

	int			m_iStageDataMax;
	int			m_iStageDataMaxMax;

	int			ControlMode;

	vector<unique_ptr<clsWall>>			m_vsmpWall;		//(��)�\��.
	vector<unique_ptr<clsFloor>>		m_vsmpFloor;		//(��)�\��.
	vector<unique_ptr<clsEnemyMgr>>		m_vsmpEnemyMgr;	//(�G)�\��.
	vector<unique_ptr<clsStepCyl>>		m_vsmpStepCil;	//(�c���ړ�)�\��.
	vector<unique_ptr<clsStepBox>>		m_vsmpStepBox;	//(�����ړ�)�\��.
	vector<unique_ptr<clsDoorMgr>>		m_vsmpDoorMgr;	//(�h�A)�\��.
	vector<unique_ptr<clsPend>>			m_vsmpPend;		//(�y���f������)�\��.
	vector<unique_ptr<clsSpiaFlorMgr>>	m_vsmpSpiaFloorMgr;	//(����)�\��.
	vector<unique_ptr<clsSpiaWallMgr>>	m_vsmpSpiaWallMgr;	//(����)�\��.
	vector<unique_ptr<clsCoverMgr>>		m_vsmpCoverMgr;	//(���Ƃ����W)�\��.
	vector<unique_ptr<clsGoalMgr>>		m_vsmpGoalMgr;	//(�S�[��)�\��.

	vector<unique_ptr<clsCharaStatic>>	m_vsmpCeiling;	//(����)�\��.

	vector<unique_ptr<clsCharaStatic>>	m_vsmpTest;		//(���f���e�X�g)�\��.

	vector<StagePatarunSet>			 m_vStageDataPatarnSet;	//�z��1�ŃX�e�[�W�P�}�X��
	StagePatarunSet					 m_vStageDataMaxSet;	//Excel�̈�s�ڂɍő吔����.
	vector<unique_ptr<clsSprite2D>>  m_vsmpSpriteTest;
	int	m_SpriteControlNum;

	inline void StageSet();
	inline void StageModelSet();
	inline void StageModelSetErrMsg( int StageNum, const char* ERR_MSG );
	inline void StageDetatchModelSet();

	void SceneTitle();
	void SceneMain();
	void SceneResult();
	void SceneOver();
	void SceneEnding();

	void RenderTitle();
	void RenderMain();
	void RenderResult();
	void RenderOver();
	void RenderEnding();

	void RenderDebugText();

	int	TestDataCnt;

	int TestDataNum;

	int	 iWallModelNumZero;
	int	 iFloorModelNumZero;


#endif //Inoue


	enScene m_enScene;

	//�^�C�g���̏��.
	enum enTitleSceneMode
	{
		en_TSM_IDLE = 0,	//���͎�t.
		en_TSM_BREAK_DOOR,	//�h�A�j�󂵂J�����ړ�.
		en_TSM_GO_MAIN,		//�Q�[���̎n�܂�.

		en_TSM_MAX,
	};
	enTitleSceneMode m_enTitleSceneMode;

	//���U���g�̏��( BGM�� ).
	enum enResultSceneMode
	{
		enRSM_SILENCE = 0,
		enRSM_JINGLE,
		enRSM_LOOP,

		enRSM_MAX
	};
	enResultSceneMode m_enResultSceneMode;
	//���U���g�Ő�����.
	int m_iResultTimer;

	//�G�Ɍ���������( �����_�[�Ŏg�� ).
	int		m_iEnemyDiscNum;
	//�G���f�B���O�V�[���̔w�i�X�N���[��.
	float	m_fEndScrol;
	//�G���f�B���O�G.
	clsEndEnemMgr* m_pEndEnemy;


	//�V�[���̏�����.
	void InitTitle();
	//���C���V�[��(�X�e�[�W)�̏�����.
	void InitMain( bool bFirstFlg = false, bool bTitle = false );//bFirstFlg = ����(Main�V�[�����Ŏg���ꍇ��false, �^�C�g�����痈���ꍇ��true).
	void InitResult();
	void InitEndroll();
	void InitOver();


	//���.
	void CameraMgr();
		bool Stoker( D3DXVECTOR3& Pos, D3DXVECTOR3 TargetPos );
		void CameraTargetSet();
		void CameraLookSet();
		float CameraLengthComp( float Attker, float Target );
		float m_fCameraLookFloor;	//���鍂���̕ۑ��p.
		float m_fCameraLookFloorOld;//���ꂪ�^���ɂȂ��Ƃ��Ɏg����.





	//��u�ŐU������Ȃ�(���X�ɐU�����).
	void YawSpnToTarg(
		float& NowYaw, float TarYaw,
		float TurnSpd, float TurnStop = 0.1f );






private:
	HWND	m_hWnd;	//����޳�����.

	//�����؂Ɉ��.
	ID3D11Device*			m_pDevice;			//���޲���޼ު��.
	ID3D11DeviceContext*	m_pDeviceContext;	//���޲���÷��.
	IDXGISwapChain*			m_pSwapChain;		//�ܯ������.
	ID3D11RenderTargetView*	m_pBackBuffer_TexRTV;//���ް���ޯ��ޭ�.
	ID3D11Texture2D*		m_pBackBuffer_DSTex;//�ޯ��ޯ̧.
	ID3D11DepthStencilView*	m_pBackBuffer_DSTexDSV;//���߽��ݼ��ޭ�.



	D3DXVECTOR3		m_vLight;	//ײĂ̕���.

	D3DXMATRIX		m_mView;	//�ޭ�(���)�s��.
	D3DXMATRIX		m_mProj;	//��ۼު���ݍs��.

	CAMERA			m_Camera;//��׏��.

	D3DXVECTOR3		m_vCameraTarget;//��ׂ�����ׂ��ʒu.
	D3DXVECTOR3		m_vLookTarget;	//�����ʒu������ׂ��ʒu.

	float 			m_fLookOffset;

	//�[�x(Z)ýĐݒ�.
	ID3D11DepthStencilState* m_pDepthStencilState;


#ifdef Inoue
	//PngTest�p�ϐ�.
	float m_fAlphaPoint;
#endif //Inoue


#if _DEBUG
	//���ޯ��÷�ĸ׽.
	clsDebugText*	m_pText;

	//�߰è�ٗp.
	clsParticle*	m_pParticle;//�߰è��.

	//ڲ�\���׽.
	clsRay*			m_pRayV;	//����.
	clsRay*			m_pRayFB;	//�O��.
	clsRay*			m_pRayH;	//���E.


	//��K.
	int					m_iBlkAryMax;
	clsCharaStatic**	m_ppBlkAry;
#endif //#if _DEBUG


	//�ޮ��è��.
	clsXInput* m_pXInput;

	//�����蔻��.
	clsCollision*	m_pCollision;

	//��ڲ԰.
	clsPlayer*			m_pPlayer;
	int					m_iRespawnTimer;




	//ؿ���׽.
	clsResource*		m_pResource;



	//����޸׽.
	enum enBgm
	{
		enBGM_START_UP = 0,
		enBGM_TITLE,
		enBGM_MAIN,
		enBGM_RESULT,
		enBGM_ENDROLL,
		enBGM_OVER,

		enBGM_MAX,
	};
	clsSound*	m_pBgm[enBGM_MAX];
	enum enSe
	{
		enSe_ENTER,
		enSe_EXIT,

		enSe_MAX,
	};
	clsSound*	m_pSe[enSe_MAX];
	void CreateSound();




	//���ʉ��̉��ʂ����߂�Z�b�g.
	float m_fEar;	//��(���ʊ)�̈ʒu.
	void SetEar( float player, float cam ){
		const float fOffset = 2.0f;
		m_fEar = ( player + cam ) / 2.0f + fOffset;
	}
	float GetEar(){
		return m_fEar;
	}





	//for���̏����̖��ʂ����炷.
	//�����蔻��v�Z����?.//Used.
	bool isCutOutForHit( float fPlayerZ, float fObjZ, float fBack = -1.0f, float fOpposite = -1.0f );
	//�����v�Z����?.//�܂��g���Ă��Ȃ�.
	bool isCutOutForMove( float fPlayerZ, float fObjZ, float fBack = -1.0f, float fOpposite = -1.0f );



#ifdef Tahara
	//ConvDimPos�̎��O����.
	void SetViewPort10( D3D11_VIEWPORT* Vp );
	//3D���W�̃X�N���[��( 2D )���W�ϊ�.dimensions(����) conversion(�ϊ�)
	D3DXVECTOR3 ConvDimPos( D3DXVECTOR3 v2DPos, D3DXVECTOR3 v3DPos );
	//2DSp�p.
	D3D10_VIEWPORT m_ViewPort;



	//���U���g�̕�Ηp.
	UI_STATE_RESULT m_ResUiState;//���U���g�ɕK�v�ȏ��.
	//���b�v.
	void SetJewelState(){
		m_smpUiManagar->SetJewelState( m_ResUiState );
	}
	//���U���g�̕�Ηp����n����悤�ɉ��H����.
	void UpDateJewelState(){
		m_ResUiState.iLives = m_pPlayer->GetHp();
	}


	//�`�F�b�N�|�C���g.
	clsCheckPointMgr* m_pCheck;



#endif//#ifdef Tahara




	//�G�t�F�N�g.
	//���O�ȗ��p.
	clsEffects*				m_pEffect;
	::Effekseer::Handle		m_ehKickHit;	//���m�����ꂽ�Ƃ�(��̂܂ł��������ɏo�Ȃ�).
	::Effekseer::Handle		m_ehSlashHit;	//�G�̍U��������������.
	//�G�t�F�N�g�Đ�.
	void PlayEffKick( D3DXVECTOR3 pvPos );
	void PlayEffSlash( D3DXVECTOR3 pvPos );

	//���Ԓn�_.
	D3DXVECTOR3 GetMidWay( D3DXVECTOR3 vA, D3DXVECTOR3 vB ){
		return ( vA + vB ) / 2.0f;
	}

};